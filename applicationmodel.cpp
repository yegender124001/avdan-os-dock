﻿#include "applicationmodel.h"
#include "processprovider.h"
#include "utils.h"


ApplicationModel::ApplicationModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_iface(XWindowInterface::instance())
    , m_sysAppMonitor(SystemAppMonitor::self())
{
    connect(m_iface, &XWindowInterface::windowAdded, this, &ApplicationModel::onWindowAdded);
    connect(m_iface, &XWindowInterface::windowRemoved, this, &ApplicationModel::onWindowRemoved);
    connect(m_iface, &XWindowInterface::activeChanged, this, &ApplicationModel::onActiveChanged);

    initPinnedApplications();

    QTimer::singleShot(100, m_iface, &XWindowInterface::startInitWindows);
}

int ApplicationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_appItems.size();
}

QHash<int, QByteArray> ApplicationModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AppIdRole] = "appId";
    roles[IconNameRole] = "iconName";
    roles[VisibleNameRole] = "visibleName";
    roles[ActiveRole] = "isActive";
    roles[WindowCountRole] = "windowCount";
    roles[IsPinnedRole] = "isPinned";
    roles[DesktopFileRole] = "desktopFile";
    roles[FixedItemRole] = "fixed";
    return roles;
}

QVariant ApplicationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ApplicationItem *item = m_appItems.at(index.row());

    switch (role) {
    case AppIdRole:
        return item->id;
    case IconNameRole:
        return item->iconName;
    case VisibleNameRole:
        return item->visibleName;
    case ActiveRole:
        return item->isActive;
    case WindowCountRole:
        return item->wids.count();
    case IsPinnedRole:
        return item->isPinned;
    case DesktopFileRole:
        return item->desktopPath;
    case FixedItemRole:
        return item->fixed;
    default:
        return QVariant();
    }

    return QVariant();
}

void ApplicationModel::addItem(const QString &desktopFile)
{
    ApplicationItem *existsItem = findItemByDesktop(desktopFile);

    if (existsItem) {
        existsItem->isPinned = true;
        return;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    ApplicationItem *item = new ApplicationItem;
    QMap<QString, QString> desktopInfo = Utils::instance()->readInfoFromDesktop(desktopFile);
    item->iconName = desktopInfo.value("Icon");
    item->visibleName = desktopInfo.value("Name");
    item->exec = desktopInfo.value("Exec");
    item->desktopPath = desktopFile;
    item->isPinned = true;

    QFileInfo fi(desktopFile);
    item->id = fi.baseName();

    m_appItems << item;
    endInsertRows();

    savePinAndUnPinList();

    emit itemAdded();
    emit countChanged();
}

void ApplicationModel::removeItem(const QString &desktopFile)
{
    ApplicationItem *item = findItemByDesktop(desktopFile);

    if (item) {
        ApplicationModel::unPin(item->id);
    }
}

bool ApplicationModel::desktopContains(const QString &desktopFile)
{
    if (desktopFile.isEmpty())
        return false;

    return findItemByDesktop(desktopFile) != nullptr;
}

bool ApplicationModel::isDesktopPinned(const QString &desktopFile)
{
    ApplicationItem *item = findItemByDesktop(desktopFile);

    if (item) {
        return item->isPinned;
    }

    return false;
}

void ApplicationModel::clicked(const QString &id)
{
    ApplicationItem *item = findItemById(id);

    if (!item)
        return;

    if (item->wids.isEmpty()) {
        openNewInstance(item->id);
    }

    else if (item->wids.count() > 1) {
        item->currentActive++;

        if (item->currentActive == item->wids.count())
            item->currentActive = 0;

        m_iface->forceActiveWindow(item->wids.at(item->currentActive));
    } else if (m_iface->activeWindow() == item->wids.first()) {
        m_iface->minimizeWindow(item->wids.first());
    } else {
        m_iface->forceActiveWindow(item->wids.first());
    }
}

void ApplicationModel::raiseWindow(const QString &id)
{
    ApplicationItem *item = findItemById(id);

    if (!item)
        return;

    m_iface->forceActiveWindow(item->wids.at(item->currentActive));
}

bool ApplicationModel::openNewInstance(const QString &appId)
{
    ApplicationItem *item = findItemById(appId);

    if (!item)
        return false;

    if (!item->exec.isEmpty()) {
        QStringList args = item->exec.split(" ");
        QString exec = args.first();
        args.removeFirst();

        if (!args.isEmpty()) {
            ProcessProvider::startDetached(exec, args);
        } else {
            ProcessProvider::startDetached(exec);
        }
    } else {
        ProcessProvider::startDetached(appId);
    }

    return true;
}

void ApplicationModel::closeAllByAppId(const QString &appId)
{
    ApplicationItem *item = findItemById(appId);

    if (!item)
        return;

    for (quint64 wid : item->wids) {
        m_iface->closeWindow(wid);
    }
}

void ApplicationModel::pin(const QString &appId)
{
    ApplicationItem *item = findItemById(appId);

    if (!item)
        return;

    item->isPinned = true;

    handleDataChangedFromItem(item);
    savePinAndUnPinList();
}

void ApplicationModel::unPin(const QString &appId)
{
    ApplicationItem *item = findItemById(appId);

    if (!item)
        return;

    item->isPinned = false;
    handleDataChangedFromItem(item);

    if (item->wids.isEmpty()) {
        int index = indexOf(item->id);
        if (index != -1) {
            beginRemoveRows(QModelIndex(), index, index);
            m_appItems.removeAll(item);
            endRemoveRows();

            emit itemRemoved();
            emit countChanged();
        }
    }

    savePinAndUnPinList();
}

void ApplicationModel::updateGeometries(const QString &id, QRect rect)
{
    ApplicationItem *item = findItemById(id);

    if (!item)
        return;

    for (quint64 id : item->wids) {
        m_iface->setIconGeometry(id, rect);
    }
}

void ApplicationModel::move(int from, int to)
{
    if (from == to)
        return;

    m_appItems.move(from, to);

    if (from < to)
        beginMoveRows(QModelIndex(), from, from, QModelIndex(), to + 1);
    else
        beginMoveRows(QModelIndex(), from, from, QModelIndex(), to);

    endMoveRows();
}

ApplicationItem *ApplicationModel::findItemByWId(quint64 wid)
{
    for (ApplicationItem *item : m_appItems) {
        for (quint64 winId : item->wids) {
            if (winId == wid)
                return item;
        }
    }

    return nullptr;
}

ApplicationItem *ApplicationModel::findItemById(const QString &id)
{
    for (ApplicationItem *item : m_appItems) {
        if (item->id == id)
            return item;
    }

    return nullptr;
}

ApplicationItem *ApplicationModel::findItemByDesktop(const QString &desktop)
{
    for (ApplicationItem *item : m_appItems) {
        if (item->desktopPath == desktop)
            return item;
    }

    return nullptr;
}

bool ApplicationModel::contains(const QString &id)
{
    for (ApplicationItem *item : qAsConst(m_appItems)) {
        if (item->id == id)
            return true;
    }

    return false;
}

int ApplicationModel::indexOf(const QString &id)
{
    for (ApplicationItem *item : m_appItems) {
        if (item->id == id)
            return m_appItems.indexOf(item);
    }

    return -1;
}

void ApplicationModel::initPinnedApplications()
{
    QSettings settings(QSettings::UserScope, "avdan-de", "pinnedDock");
    QSettings systemSettings("/etc/avdan-de-dock-list.conf", QSettings::IniFormat);
    QSettings *set = (QFile(settings.fileName()).exists()) ? &settings
                                                           : &systemSettings;
    QStringList groups = set->childGroups();

    for (int i = 0; i < groups.size(); ++i) {
        for (const QString &id : groups) {
            set->beginGroup(id);
            int index = set->value("Index").toInt();

            if (index == i) {
                beginInsertRows(QModelIndex(), rowCount(), rowCount());
                ApplicationItem *item = new ApplicationItem;

                item->desktopPath = set->value("DesktopPath").toString();
                item->id = id;
                item->isPinned = true;

                if (!QFile(item->desktopPath).exists()) {
                    set->endGroup();
                    continue;
                }

                if (!item->desktopPath.isEmpty()) {
                    QMap<QString, QString> desktopInfo = Utils::instance()->readInfoFromDesktop(item->desktopPath);
                    item->iconName = desktopInfo.value("Icon");
                    item->visibleName = desktopInfo.value("Name");
                    item->exec = desktopInfo.value("Exec");
                }

                if (item->iconName.isEmpty())
                    item->iconName = set->value("Icon").toString();

                if (item->visibleName.isEmpty())
                    item->visibleName = set->value("VisibleName").toString();

                if (item->exec.isEmpty())
                    item->exec = set->value("Exec").toString();

                m_appItems.append(item);
                endInsertRows();

                emit itemAdded();
                emit countChanged();

                set->endGroup();
                break;
            } else {
                set->endGroup();
            }
        }
    }
}

void ApplicationModel::savePinAndUnPinList()
{
    QSettings settings(QSettings::UserScope, "avdan-de", "pinnedDock");
    settings.clear();

    int index = 0;

    for (ApplicationItem *item : m_appItems) {
        if (item->isPinned) {
            settings.beginGroup(item->id);
            settings.setValue("Index", index);
            settings.setValue("Icon", item->iconName);
            settings.setValue("VisibleName", item->visibleName);
            settings.setValue("Exec", item->exec);
            settings.setValue("DesktopPath", item->desktopPath);
            settings.endGroup();
            ++index;
        }
    }

    settings.sync();
}

void ApplicationModel::handleDataChangedFromItem(ApplicationItem *item)
{
    if (!item)
        return;

    QModelIndex idx = index(indexOf(item->id), 0, QModelIndex());

    if (idx.isValid()) {
        emit dataChanged(idx, idx);
    }
}

void ApplicationModel::onWindowAdded(quint64 wid)
{
    QMap<QString, QVariant> info = m_iface->requestInfo(wid);
    const QString id = info.value("id").toString();

    QString desktopPath = m_iface->desktopFilePath(wid);
    ApplicationItem *desktopItem = findItemByDesktop(desktopPath);

    if (!desktopPath.isEmpty() && desktopItem != nullptr) {
        desktopItem->wids.append(wid);

        desktopItem->isActive = info.value("active").toBool();

        if (desktopItem->id != id) {
            desktopItem->id = id;
            savePinAndUnPinList();
        }

        handleDataChangedFromItem(desktopItem);
    }

    else if (contains(id)) {
        for (ApplicationItem *item : m_appItems) {
            if (item->id == id) {
                item->wids.append(wid);

                item->isActive = info.value("active").toBool();
                handleDataChangedFromItem(item);
            }
        }
    }

    else {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        ApplicationItem *item = new ApplicationItem;
        item->id = id;
        item->iconName = info.value("iconName").toString();
        item->visibleName = info.value("visibleName").toString();
        item->isActive = info.value("active").toBool();
        item->wids.append(wid);

        if (!desktopPath.isEmpty()) {
            QMap<QString, QString> desktopInfo = Utils::instance()->readInfoFromDesktop(desktopPath);
            item->iconName = desktopInfo.value("Icon");
            item->visibleName = desktopInfo.value("Name");
            item->exec = desktopInfo.value("Exec");
            item->desktopPath = desktopPath;
        }

        m_appItems << item;
        endInsertRows();

        emit itemAdded();
        emit countChanged();
    }
}

void ApplicationModel::onWindowRemoved(quint64 wid)
{
    ApplicationItem *item = findItemByWId(wid);

    if (!item)
        return;

    item->wids.removeOne(wid);

    if (item->currentActive >= item->wids.size())
        item->currentActive = 0;

    handleDataChangedFromItem(item);

    if (item->wids.isEmpty()) {
        if (!item->isPinned) {
            int index = indexOf(item->id);

            if (index == -1)
                return;

            beginRemoveRows(QModelIndex(), index, index);
            m_appItems.removeAll(item);
            endRemoveRows();

            emit itemRemoved();
            emit countChanged();
        }
    }
}

void ApplicationModel::onActiveChanged(quint64 wid)
{
    for (ApplicationItem *item : m_appItems) {
        if (item->isActive != item->wids.contains(wid)) {
            item->isActive = item->wids.contains(wid);

            QModelIndex idx = index(indexOf(item->id), 0, QModelIndex());
            if (idx.isValid()) {
                emit dataChanged(idx, idx);
            }
        }
    }
}

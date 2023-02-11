#ifndef APPMODEL_H
#define APPMODEL_H

#include "applicationitem.h"
#include "systemappmonitor.h"
#include <QAbstractListModel>
#include "xwindowinterface.h"

class AppModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AppModel(QObject *parent = nullptr);

    enum Roles {
        AppIdRole = Qt::UserRole + 1,
        IconNameRole,
        VisibleNameRole,
        ActiveRole,
        WindowCountRole,
        IsPinnedRole,
        DesktopFileRole,
        FixedItemRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addItem(const QString &desktopFile);
    void removeItem(const QString &desktopFile);
    bool desktopContains(const QString &desktopFile);
    bool isDesktopPinned(const QString &desktopFile);

    Q_INVOKABLE void save() { savePinAndUnpinList(); }

    Q_INVOKABLE void clicked(const QString &id);
    Q_INVOKABLE void raiseWindow(const QString &id);

    Q_INVOKABLE bool openNewInstance(const QString &appId);

    Q_INVOKABLE void pin(const QString &appId);
    Q_INVOKABLE void unPin(const QString &appId);

    Q_INVOKABLE void updateGeometries(const QString &id, QRect rect);

    Q_INVOKABLE void move(int from, int to);
signals:
    void countChanged();
    void itemAdded();
    void itemRemoved();

private:
    ApplicationItem *findItembyDesktop(const QString &desktopFile);
    ApplicationItem *findItembyId(const QString &id);
    ApplicationItem *findItembyWId(const quint64 wid);

    bool contains(const QString &id);
    int indexOf(const QString &id);
    void initPinnedApplications();
    void savePinAndUnpinList();

    void handleDataChangedFromItem(ApplicationItem *item);

    void onWindowAdded(quint64 wid);
    void onWindowRemoved(quint64 wid);
    void onActiveChanged(quint64 wid);

    QList<ApplicationItem *> m_Items;
    XWindowInterface *m_iface;
    SystemAppMonitor *m_sysAppMonitor;
};

#endif // APPMODEL_H

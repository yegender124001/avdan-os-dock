#include "utils.h"
#include "qfileinfo.h"
#include "systemappmonitor.h"
#include <QFile>
#include <QMap>
static Utils *INSTANCE = nullptr;

Utils::Utils(QObject *parent)
    : QObject(parent)
    , m_sysAppMonitor(SystemAppMonitor::self())
{

}

Utils *Utils::instance()
{
    if (!INSTANCE)
        INSTANCE = new Utils;
    return INSTANCE;
}

QStringList Utils::commandFromPid(quint32 pid)
{
    QFile file(QString("/proc/%1/cmdline").arg(pid));

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray cmd = file.readAll();

        if(!cmd.isEmpty()) {
            int zeroIndex = cmd.indexOf('\0');
            int processNameStart = cmd.lastIndexOf('/', zeroIndex);
            if (processNameStart == -1 ){
                processNameStart = 0;
            } else {
                processNameStart++;
            }

            QString name = QString::fromLocal8Bit(cmd.mid(processNameStart, zeroIndex - processNameStart));

            name = name.split(' ').first();

            cmd.replace('\0',' ');
            QString command = QString::fromLocal8Bit(cmd).trimmed();

            if (command.split(' ').size() > 1) {
                command = command.split(' ').first();
            }

            return {command, name};
        }
    }

    return QStringList();
}

QString Utils::desktopPathFromMetadata(const QString &appId, quint32 pid, const QString &xWindowWMClassName)
{
    QStringList commands = commandFromPid(pid);

    // The value returned from the commandFromPid() may be empty.
    // Calling first() and last() below will cause the statusbar to crash.
    if (commands.isEmpty() || xWindowWMClassName.isEmpty())
        return "";

    QString command = commands.first();
    QString commandName = commands.last();

    if (command.isEmpty())
        return "";

    QString result;

    if (!appId.isEmpty() && !xWindowWMClassName.isEmpty()) {
        for (SystemAppItem *item : m_sysAppMonitor->applications()) {
            // Start search.
            const QFileInfo desktopFileInfo(item->path);

            bool isExecPath = QFile::exists(item->exec);
            bool founded = false;

            if (item->exec == command || item->exec == commandName) {
                founded = true;
            }

            // StartupWMClass=STRING
            // If true, it is KNOWN that the application will map at least one
            // window with the given string as its WM class or WM name hint.
            // ref: https://specifications.freedesktop.org/startup-notification-spec/startup-notification-0.1.txt
            if (item->startupWMClass.startsWith(appId, Qt::CaseInsensitive) ||
                item->startupWMClass.startsWith(xWindowWMClassName, Qt::CaseInsensitive))
                founded = true;

            if (!founded && item->iconName.startsWith(xWindowWMClassName, Qt::CaseInsensitive))
                founded = true;

            // Icon name and cmdline.
            if (!founded && (item->iconName == command || item->iconName == commandName))
                founded = true;

            // Exec name and cmdline.
            if (!founded && (item->exec == command || item->exec == commandName))
                founded = true;

            // Try matching mapped name against 'Name'.
            if (!founded && item->name.startsWith(xWindowWMClassName, Qt::CaseInsensitive))
                founded = true;

            // exec
            if (!founded && item->exec.startsWith(xWindowWMClassName, Qt::CaseInsensitive))
                founded = true;

            if (!founded && desktopFileInfo.baseName().startsWith(xWindowWMClassName, Qt::CaseInsensitive))
                founded = true;

            // For exec path.
            if (isExecPath && !founded && (command.contains(item->exec) || commandName.contains(item->exec))) {
                founded = true;
            }

            if (founded) {
                result = item->path;
                break;
            }
        }
    }

    return result;
}

QMap<QString, QString> Utils::readInfoFromDesktop(const QString &desktopFile)
{
    QMap<QString, QString> info;
    for (SystemAppItem *item : m_sysAppMonitor->applications()) {
        if (item->path == desktopFile) {
            info.insert("Icon", item->iconName);
            info.insert("Name", item->name);
            info.insert("Exec", item->exec);
        }
    }

    return info;
}


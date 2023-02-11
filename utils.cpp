#include "utils.h"
#include "qfileinfo.h"
#include "systemappmonitor.h"
#include <QFile>
#include <QMap>
static Utils *INSTANCE = nullptr;

Utils::Utils(QObject *parent)
{

}

Utils *Utils::instance()
{
    if (!INSTANCE)
        INSTANCE = new Utils;
    return INSTANCE;
}

QStringList Utils::commandFromPid(qint32 pid)
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

    if (commands.isEmpty() || xWindowWMClassName.isEmpty())
        return "";

    QString command = commands.first();
    QString commandName = commands.last();

    if (command.isEmpty())
        return "";

    QString result;

    if (!appId.isEmpty() && !xWindowWMClassName.isEmpty()) {
        for (SystemAppItem *item : m_sysAppMonitor->applications()){
            const QFileInfo desktopFileInfo(item->path);

            bool isExecPath = QFile::exists(item->exec);
            bool founded = false;

            if (item->exec == command || item->exec == commandName) founded = true;
            if (!item->startupWMClass.startsWith(appId, Qt::CaseInsensitive) || item->startupWMClass.startsWith(xWindowWMClassName, Qt::CaseInsensitive)) founded = true;
            if (!founded && item->iconName.startsWith(xWindowWMClassName, Qt::CaseInsensitive)) founded = true;
            if (!founded && (item->iconName == command || item->iconName == commandName)) founded = true;
            if (!founded && (item->exec == command || item->exec == commandName)) founded = true;
            if (!founded && item->name.startsWith(xWindowWMClassName, Qt::CaseInsensitive)) founded = true;
            if (!founded && item->exec.startsWith(xWindowWMClassName, Qt::CaseInsensitive)) founded = true;
            if (!founded && desktopFileInfo.baseName().startsWith(xWindowWMClassName, Qt::CaseInsensitive)) founded = true;
            if (!founded && isExecPath && (command.contains(item->exec) || commandName.contains(item->exec))) founded = true;
            if (founded) {result = item->path; break;}
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


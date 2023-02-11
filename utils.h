#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QIcon>
#include <QUrl>

class SystemAppMonitor;
class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);
    struct AppData{
        QString id;
        QString name;
        QString genericName;
        QIcon icon;
        QUrl url;
        bool skipTaskbar = false;
    };

    enum UrlComparisionMode {
        Strict = 0,
        IgniteQueryItems
    };

    static Utils *instance();

    QStringList commandFromPid(qint32 pid);
    QString desktopPathFromMetadata(const QString &appId, quint32 pid = 0,
                                    const QString &xWindowWMClassName = QString());
    QMap<QString, QString> readInfoFromDesktop(const QString &desktopFile);

private:
    SystemAppMonitor *m_sysAppMonitor;
};

#endif // UTILS_H

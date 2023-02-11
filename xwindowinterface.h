#ifndef XWINDOWINTERFACE_H
#define XWINDOWINTERFACE_H

#include <QObject>

#include <kwindowinfo.h>
#include <kwindoweffects.h>

class XWindowInterface : public QObject
{
    Q_OBJECT
public:
    explicit XWindowInterface(QObject *parent = nullptr);
    static XWindowInterface *instace();

    void enableBlueBehind(QWindow *view, bool enable = true, const QRegion &region = QRegion());

    WId activeWindow();
    void minimizeWindow(WId win);
    void closeWindow(WId id);
    void forceActiveWindow(WId win);

    QMap<QString, QVariant> requestInfo(quint64 wid);
    QString requestWindowClass(quint64 wid);
    bool isAcceptableWindow(quint64 wid);

    void startInitWindows();

    QString desktopFilePath(quint64 wid);

    void setIconGeometry(quint64 wid, const QRect &rect);

signals:
    void windowAdded(quint64 wid);
    void windowRemoved(quint64 wid);
    void activeChanged(quint64 wid);

private:
    void onWindowadded(quint64 wid);
};

#endif // XWINDOWINTERFACE_H

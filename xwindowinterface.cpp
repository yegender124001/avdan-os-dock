#include "xwindowinterface.h"
#include "utils.h"

#include <QTimer>
#include <QDebug>
#include <QtX11Extras/QX11Info>
#include <QWindow>
#include <QScreen>

#include <KWindowEffects>
#include <KWindowSystem>
#include <KWindowInfo>

// X11
#include <NETWM>

static XWindowInterface *INSTANCE = nullptr;

XWindowInterface *XWindowInterface::instance()
{
    if (!INSTANCE)
        INSTANCE = new XWindowInterface;

    return INSTANCE;
}

XWindowInterface::XWindowInterface(QObject *parent)
    : QObject(parent)
{
    connect(KWindowSystem::self(), &KWindowSystem::windowAdded, this, &XWindowInterface::onWindowadded);
    connect(KWindowSystem::self(), &KWindowSystem::windowRemoved, this, &XWindowInterface::windowRemoved);
    connect(KWindowSystem::self(), &KWindowSystem::activeWindowChanged, this, &XWindowInterface::activeChanged);
}

void XWindowInterface::enableBlurBehind(QWindow *view, bool enable, const QRegion &region)
{
    KWindowEffects::enableBlurBehind(view->winId(), enable, region);
}

WId XWindowInterface::activeWindow()
{
    return KWindowSystem::activeWindow();
}

void XWindowInterface::minimizeWindow(WId win)
{
    KWindowSystem::minimizeWindow(win);
}

void XWindowInterface::closeWindow(WId id)
{
    // FIXME: Why there is no such thing in KWindowSystem??
    NETRootInfo(QX11Info::connection(), NET::CloseWindow).closeWindowRequest(id);
}

void XWindowInterface::forceActiveWindow(WId win)
{
    KWindowSystem::forceActiveWindow(win);
}

QMap<QString, QVariant> XWindowInterface::requestInfo(quint64 wid)
{
    const KWindowInfo winfo { wid, NET::WMFrameExtents
                | NET::WMWindowType
                | NET::WMGeometry
                | NET::WMDesktop
                | NET::WMState
                | NET::WMName
                | NET::WMVisibleName,
                NET::WM2WindowClass
                | NET::WM2Activities
                | NET::WM2AllowedActions
                | NET::WM2TransientFor };
    QMap<QString, QVariant> result;
    const QString winClass = QString(winfo.windowClassClass());

    result.insert("iconName", winClass.toLower());
    result.insert("active", wid == KWindowSystem::activeWindow());
    result.insert("visibleName", winfo.visibleName());
    result.insert("id", winClass);

    return result;
}

QString XWindowInterface::requestWindowClass(quint64 wid)
{
    return KWindowInfo(wid, NET::Supported, NET::WM2WindowClass).windowClassClass();
}

bool XWindowInterface::isAcceptableWindow(quint64 wid)
{
    QFlags<NET::WindowTypeMask> ignoreList;
    ignoreList |= NET::DesktopMask;
    ignoreList |= NET::DockMask;
    ignoreList |= NET::SplashMask;
    ignoreList |= NET::ToolbarMask;
    ignoreList |= NET::MenuMask;
    ignoreList |= NET::PopupMenuMask;
    ignoreList |= NET::NotificationMask;

    KWindowInfo info(wid, NET::WMWindowType | NET::WMState, NET::WM2TransientFor | NET::WM2WindowClass);

    if (!info.valid())
        return false;

    if (NET::typeMatchesMask(info.windowType(NET::AllTypesMask), ignoreList))
        return false;

    if (info.hasState(NET::SkipTaskbar) || info.hasState(NET::SkipPager))
        return false;

    // WM_TRANSIENT_FOR hint not set - normal window
    WId transFor = info.transientFor();
    if (transFor == 0 || transFor == wid || transFor == (WId) QX11Info::appRootWindow())
        return true;

    info = KWindowInfo(transFor, NET::WMWindowType);

    QFlags<NET::WindowTypeMask> normalFlag;
    normalFlag |= NET::NormalMask;
    normalFlag |= NET::DialogMask;
    normalFlag |= NET::UtilityMask;

    return !NET::typeMatchesMask(info.windowType(NET::AllTypesMask), normalFlag);
}

void XWindowInterface::startInitWindows()
{
    for (auto wid : KWindowSystem::self()->windows()) {
        onWindowadded(wid);
    }
}

QString XWindowInterface::desktopFilePath(quint64 wid)
{
    const KWindowInfo info(wid, NET::Properties(), NET::WM2WindowClass | NET::WM2DesktopFileName);
    return Utils::instance()->desktopPathFromMetadata(info.windowClassClass(),
                                                      NETWinInfo(QX11Info::connection(), wid,
                                                                 QX11Info::appRootWindow(),
                                                                 NET::WMPid,
                                                                 NET::Properties2()).pid(),
                                                      info.windowClassName());
}

void XWindowInterface::setIconGeometry(quint64 wid, const QRect &rect)
{
    NETWinInfo info(QX11Info::connection(),
                    wid,
                    (WId) QX11Info::appRootWindow(),
                    NET::WMIconGeometry,
                    QFlags<NET::Property2>(1));
    NETRect nrect;
    nrect.pos.x = rect.x();
    nrect.pos.y = rect.y();
    nrect.size.height = rect.height();
    nrect.size.width = rect.width();
    info.setIconGeometry(nrect);
}

void XWindowInterface::onWindowadded(quint64 wid)
{
    if (isAcceptableWindow(wid)) {
        emit windowAdded(wid);
    }
}

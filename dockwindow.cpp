#include "dockwindow.h"
#include "qpainterpath.h"
#include <KWindowSystem/kwindowsystem.h>
#include <kwindoweffects.h>
#include <kx11extras.h>
#include <QScreen>
#include <QVector>
DockWindow::DockWindow()
{
    setColor(QColor("transparent"));
    setFlags(Qt::FramelessWindowHint);
    KX11Extras::setOnDesktop(winId(), NET::OnAllDesktops);
    KWindowSystem::setType(winId(), NET::Dock);
    connect(this, &QQuickWindow::widthChanged, this, &DockWindow::updateBlur);
    connect(this, &QQuickWindow::heightChanged, this, &DockWindow::updateBlur);
}

void DockWindow::enableStruts()
{
    const int topOffset = screen()->geometry().top();
    NETExtendedStrut strut;
    strut.bottom_width = height() - 1 + topOffset + 10;
    strut.bottom_start = 0;
    strut.bottom_end = screen()->geometry().width() - 1;
    KX11Extras::setExtendedStrut(winId(),
                                 strut.left_width,
                                 strut.left_start,
                                 strut.left_end,
                                 strut.right_width,
                                 strut.right_start,
                                 strut.right_end,
                                 strut.top_width,
                                 strut.top_start,
                                 strut.top_end,
                                 strut.bottom_width,
                                 strut.bottom_start,
                                 strut.bottom_end);
    updateBlur();
}

void DockWindow::updateBlur()
{
    QPainterPath path;
    path.addRoundedRect(QRect(0,0,width(),height()),windowRadius()*devicePixelRatio(),windowRadius()*devicePixelRatio());
    foreach (const QPolygonF &polygon, path.toFillPolygons()) {
        QRegion region = polygon.toPolygon();
        KWindowEffects::enableBlurBehind(this, true, region);
    }
}

const int DockWindow::windowRadius()
{
    return m_window_radius;
}

const bool DockWindow::windowBlur()
{
    return m_blur_enabled;
}

void DockWindow::setWindowRadius(int radius)
{
    if (radius == m_window_radius) return;
    m_window_radius = radius;
    emit windowRadiusChanged();
}

void DockWindow::setWindowBlur(bool value)
{
    if (value == m_blur_enabled) return;
    m_blur_enabled = value;
    emit windowBlurChanged();
}

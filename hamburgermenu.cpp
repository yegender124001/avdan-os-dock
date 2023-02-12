#include "hamburgermenu.h"
#include <kwindoweffects.h>
#include <kx11extras.h>
#include <QPainterPath>
#include <KWindowSystem>
HamburgerMenu::HamburgerMenu()
{
    setColor(QColor("transparent"));
    setFlags(Qt::FramelessWindowHint);
    KX11Extras::setOnDesktop(winId(), NET::OnAllDesktops);
    KWindowSystem::setType(winId(), NET::Menu);
    connect(this, &QQuickWindow::widthChanged, this, &HamburgerMenu::updateBlur);
    connect(this, &QQuickWindow::heightChanged, this, &HamburgerMenu::updateBlur);
}

const int HamburgerMenu::windowRadius()
{
    return m_window_radius;
}

const bool HamburgerMenu::windowBlur()
{
    return m_blur_enabled;
}

void HamburgerMenu::updateBlur()
{
    QPainterPath path;
    path.addRoundedRect(QRect(0,0,width(),height()),windowRadius()*devicePixelRatio(),windowRadius()*devicePixelRatio());
    foreach (const QPolygonF &polygon, path.toFillPolygons()) {
        QRegion region = polygon.toPolygon();
        KWindowEffects::enableBlurBehind(this, true, region);
    }
}

void HamburgerMenu::setWindowRadius(int radius)
{
    if (radius == m_window_radius) return;
    m_window_radius = radius;
    emit windowRadiusChanged();
}

void HamburgerMenu::setWindowBlur(bool value)
{
    if (value == m_blur_enabled) return;
    m_blur_enabled = value;
    emit windowBlurChanged();
}

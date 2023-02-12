#include "tooltip.h"
#include <kwindoweffects.h>
#include <kx11extras.h>
#include <QPainterPath>
Tooltip::Tooltip()
{
    setColor(QColor("transparent"));
    setFlags(Qt::FramelessWindowHint);
    KX11Extras::setOnDesktop(winId(), NET::OnAllDesktops);
    connect(this, &QQuickWindow::widthChanged, this, &Tooltip::updateBlur);
    connect(this, &QQuickWindow::heightChanged, this, &Tooltip::updateBlur);
}
const int Tooltip::windowRadius()
{
    return m_window_radius;
}

const bool Tooltip::windowBlur()
{
    return m_blur_enabled;
}

void Tooltip::updateBlur()
{
    QPainterPath path;
    path.addRoundedRect(QRect(0,0,width(),height()),windowRadius()*devicePixelRatio(),windowRadius()*devicePixelRatio());
    foreach (const QPolygonF &polygon, path.toFillPolygons()) {
        QRegion region = polygon.toPolygon();
        KWindowEffects::enableBlurBehind(this, true, region);
    }
}

void Tooltip::setWindowRadius(int radius)
{
    if (radius == m_window_radius) return;
    m_window_radius = radius;
    emit windowRadiusChanged();
}

void Tooltip::setWindowBlur(bool value)
{
    if (value == m_blur_enabled) return;
    m_blur_enabled = value;
    emit windowBlurChanged();
}

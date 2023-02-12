#ifndef HAMBURGERMENU_H
#define HAMBURGERMENU_H

#include <QQuickWindow>

class HamburgerMenu : public QQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(int windowRadius READ windowRadius WRITE setWindowRadius NOTIFY windowRadiusChanged)
    Q_PROPERTY(bool windowBlur READ windowBlur WRITE setWindowBlur NOTIFY windowBlurChanged)
public:
    HamburgerMenu();
    const int windowRadius();
    const bool windowBlur();
signals:
    void windowBlurChanged();
    void windowRadiusChanged();
public slots:
    Q_INVOKABLE void updateBlur();
    Q_INVOKABLE void setWindowRadius(int radius);
    Q_INVOKABLE void setWindowBlur(bool value);
private:
    bool m_blur_enabled = true;
    int m_window_radius = 5;
};

#endif

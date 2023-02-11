#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "appmodel.h"
#include "dockwindow.h"
#include <QQuickItem>
#include <QScreen>
#include <QQmlContext>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    qmlRegisterType<DockWindow>("Dock",1,0,"DockWindow");
    qmlRegisterType<AppModel>("Dock",1,0,"AppModel");
    DockWindow dock;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("DockWindow",&dock);
    engine.load(QUrl("qrc:/Dock.qml"));
    return app.exec();
}

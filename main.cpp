#include <QGuiApplication>
#include <QQuickWindow>
#include <QQmlApplicationEngine>
#include <buttoncontroller.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    QQmlApplicationEngine engine;

    ButtonController* button_controller = new ButtonController(&app);
    qmlRegisterSingletonInstance("fractalforge.ButtonController", 1, 0, "ButtonController", button_controller);

    const QUrl url(u"qrc:/Prototype/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

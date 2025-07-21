#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/controllers/dashboardcontroller.h"
#include "src/controllers/videocontroller.h"
#include "src/controllers/telemetrycontroller.h"
#include "src/models/telemetrymodel.h"
#include <QDebug>

#if QT_CONFIG(permissions)
#include <QPermission>
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    DashboardController dashboardController;
    VideoController videoController;
    TelemetryController telemetryController;

    engine.rootContext()->setContextProperty("dashboardController", &dashboardController);
    engine.rootContext()->setContextProperty("videoController", &videoController);
    engine.rootContext()->setContextProperty("telemetryController", &telemetryController);
    engine.rootContext()->setContextProperty("telemetryModel", telemetryController.telemetryModel());

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("MiniGCS", "Main");

    return app.exec();
}

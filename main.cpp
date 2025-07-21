#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/controllers/dashboardcontroller.h"
#include "src/controllers/videocontroller.h"
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

    engine.rootContext()->setContextProperty("dashboardController", &dashboardController);
    engine.rootContext()->setContextProperty("videoController", &videoController);

// #if QT_CONFIG(permissions)
//     QCameraPermission cameraPermission;
//     qApp->requestPermission(cameraPermission, [](const QPermission &permission) {
//         if (permission.status() == Qt::PermissionStatus::Denied)
//             qDebug() << "Camera Denied";
//         else
//             qDebug() << "Camera Permitted";
//     });
// #endif

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("MiniGCS", "Main");

    return app.exec();
}

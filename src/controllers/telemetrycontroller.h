#ifndef TELEMETRYCONTROLLER_H
#define TELEMETRYCONTROLLER_H

#pragma once

#include <QObject>
#include <QThread>
#include "../common/telemetrydata.h"

class TelemetryWorker;
class TelemetryModel;
class ITelemetrySource;

class TelemetryController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double latitude READ latitude NOTIFY telemetryChanged)
    Q_PROPERTY(double longitude READ longitude NOTIFY telemetryChanged)
    Q_PROPERTY(double altitude READ altitude NOTIFY telemetryChanged)
    Q_PROPERTY(double yaw READ yaw NOTIFY telemetryChanged)
    Q_PROPERTY(double groundSpeed READ groundSpeed NOTIFY telemetryChanged)
    Q_PROPERTY(int battery READ battery NOTIFY telemetryChanged)

public:
    explicit TelemetryController(QObject* parent = nullptr);
    ~TelemetryController();

    double latitude() const;
    double longitude() const;
    double altitude() const;
    double yaw() const;
    double groundSpeed() const;
    int battery() const;

    TelemetryModel* telemetryModel() const;

    Q_INVOKABLE void startTelemetry(const QString& jsonFilePath);

signals:
    void telemetryChanged();

private slots:
    void onTelemetryDataReceived(const TelemetryData& data);

private:
    void cleanupWorker();

    TelemetryModel* m_telemetryModel = nullptr;
    TelemetryWorker* m_worker = nullptr;
    QThread* m_workerThread = nullptr;

    TelemetryData m_currentData;
};


#endif // TELEMETRYCONTROLLER_H

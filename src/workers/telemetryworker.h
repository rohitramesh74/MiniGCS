#ifndef TELEMETRYWORKER_H
#define TELEMETRYWORKER_H

#pragma once

#include <QObject>
#include <QList>
#include <QTimer>
#include "../common/telemetrydata.h"

class ITelemetrySource;

class TelemetryWorker : public QObject
{
    Q_OBJECT

public:
    explicit TelemetryWorker(ITelemetrySource* source, const QString& filePath, QObject* parent = nullptr);
    ~TelemetryWorker();

public slots:
    void startReplay();

signals:
    void telemetryDataAvailable(const TelemetryData& data);
    void finished();

private:
    QList<TelemetryData> m_dataList;
    int m_currentIndex = 0;
    QTimer* m_replayTimer = nullptr;
};


#endif // TELEMETRYWORKER_H

#ifndef ITELEMETRYSOURCE_H
#define ITELEMETRYSOURCE_H

#pragma once

#include <QObject>
#include <QList>

struct TelemetryData;

class ITelemetrySource : public QObject
{
    Q_OBJECT
public:
    explicit ITelemetrySource(QObject* parent = nullptr) : QObject(parent) { }
    virtual ~ITelemetrySource() = default;

    virtual QList<TelemetryData> loadTelemetry(const QString& filePath) = 0;
};

#endif // ITELEMETRYSOURCE_H

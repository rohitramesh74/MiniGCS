#ifndef JSONTELEMETRYSOURCE_H
#define JSONTELEMETRYSOURCE_H

#pragma once

#include "itelemetrysource.h"

class JsonTelemetrySource : public ITelemetrySource
{
    Q_OBJECT
public:
    explicit JsonTelemetrySource(QObject* parent = nullptr);
    QList<TelemetryData> loadTelemetry(const QString& filePath) override;
};

#endif // JSONTELEMETRYSOURCE_H

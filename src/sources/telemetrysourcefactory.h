#ifndef TELEMETRYSOURCEFACTORY_H
#define TELEMETRYSOURCEFACTORY_H

#pragma once

#include <QString>
#include "itelemetrysource.h"

class TelemetrySourceFactory
{
public:
    static ITelemetrySource* create(const QString& type, QObject* parent = nullptr);
};

#endif // TELEMETRYSOURCEFACTORY_H

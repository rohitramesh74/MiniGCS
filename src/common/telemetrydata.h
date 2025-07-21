#ifndef TELEMETRYDATA_H
#define TELEMETRYDATA_H

#pragma once

struct TelemetryData
{
    double latitude = 0.0;
    double longitude = 0.0;
    double altitude = 0.0;
    double yaw = 0.0;
    double groundSpeed = 0.0;
    int battery = 0;
};

#endif // TELEMETRYDATA_H

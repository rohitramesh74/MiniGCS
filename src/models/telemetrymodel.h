#ifndef TELEMETRYMODEL_H
#define TELEMETRYMODEL_H

#pragma once

#include <QAbstractListModel>
#include "../common/telemetrydata.h"

class TelemetryModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(double latestLatitude READ latestLatitude NOTIFY latestTelemetryChanged)
    Q_PROPERTY(double latestLongitude READ latestLongitude NOTIFY latestTelemetryChanged)
    Q_PROPERTY(double latestAltitude READ latestAltitude NOTIFY latestTelemetryChanged)
    Q_PROPERTY(double latestYaw READ latestYaw NOTIFY latestTelemetryChanged)
    Q_PROPERTY(double latestGroundSpeed READ latestGroundSpeed NOTIFY latestTelemetryChanged)
    Q_PROPERTY(int latestBattery READ latestBattery NOTIFY latestTelemetryChanged)

public:
    enum TelemetryRoles {
        LatitudeRole = Qt::UserRole + 1,
        LongitudeRole,
        AltitudeRole,
        YawRole,
        GroundSpeedRole,
        BatteryRole
    };

    explicit TelemetryModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addTelemetryData(const TelemetryData& data);
    Q_INVOKABLE void clear();

    // Latest Data Accessors
    double latestLatitude() const;
    double latestLongitude() const;
    double latestAltitude() const;
    double latestYaw() const;
    double latestGroundSpeed() const;
    int latestBattery() const;

signals:
    void latestTelemetryChanged();

private:
    QList<TelemetryData> m_telemetryList;
    TelemetryData m_latestData;
};


#endif // TELEMETRYMODEL_H

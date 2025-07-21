#include "telemetrymodel.h"

TelemetryModel::TelemetryModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int TelemetryModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_telemetryList.size();
}

QVariant TelemetryModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_telemetryList.size())
        return QVariant();

    const TelemetryData& data = m_telemetryList.at(index.row());

    switch (role) {
    case LatitudeRole: return data.latitude;
    case LongitudeRole: return data.longitude;
    case AltitudeRole: return data.altitude;
    case YawRole: return data.yaw;
    case GroundSpeedRole: return data.groundSpeed;
    case BatteryRole: return data.battery;
    default: return QVariant();
    }
}

QHash<int, QByteArray> TelemetryModel::roleNames() const
{
    return {
        { LatitudeRole, "latitude" },
        { LongitudeRole, "longitude" },
        { AltitudeRole, "altitude" },
        { YawRole, "yaw" },
        { GroundSpeedRole, "groundSpeed" },
        { BatteryRole, "battery" }
    };
}

void TelemetryModel::addTelemetryData(const TelemetryData& data)
{
    beginInsertRows(QModelIndex(), m_telemetryList.size(), m_telemetryList.size());
    m_telemetryList.append(data);
    endInsertRows();

    m_latestData = data;
    emit latestTelemetryChanged();
}

void TelemetryModel::clear()
{
    beginResetModel();
    m_telemetryList.clear();
    endResetModel();

    m_latestData = TelemetryData();
    emit latestTelemetryChanged();
}

// Latest Data Getters
double TelemetryModel::latestLatitude() const { return m_latestData.latitude; }
double TelemetryModel::latestLongitude() const { return m_latestData.longitude; }
double TelemetryModel::latestAltitude() const { return m_latestData.altitude; }
double TelemetryModel::latestYaw() const { return m_latestData.yaw; }
double TelemetryModel::latestGroundSpeed() const { return m_latestData.groundSpeed; }
int TelemetryModel::latestBattery() const { return m_latestData.battery; }

#include "jsontelemetrysource.h"
#include "../common/telemetrydata.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

JsonTelemetrySource::JsonTelemetrySource(QObject *parent) : ITelemetrySource(parent) { }

QList<TelemetryData> JsonTelemetrySource::loadTelemetry(const QString& filePath)
{
    QList<TelemetryData> telemetryList;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open telemetry JSON file:" << filePath;
        return telemetryList;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON Parse Error in telemetry file:" << parseError.errorString();
        return telemetryList;
    }

    if (!doc.isArray()) {
        qWarning() << "Expected JSON array in telemetry file";
        return telemetryList;
    }

    QJsonArray jsonArray = doc.array();
    for (const QJsonValue& value : jsonArray) {
        if (!value.isObject())
            continue;

        QJsonObject obj = value.toObject();

        TelemetryData data;
        data.latitude = obj.value("latitude").toDouble();
        data.longitude = obj.value("longitude").toDouble();
        data.altitude = obj.value("altitude").toDouble();
        data.yaw = obj.value("yaw").toDouble();
        data.groundSpeed = obj.value("groundSpeed").toDouble();
        data.battery = obj.value("battery").toInt();

        telemetryList.append(data);
    }

    qDebug() << "Loaded" << telemetryList.size() << "telemetry entries from JSON.";
    return telemetryList;
}

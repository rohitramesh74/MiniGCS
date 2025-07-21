#include "telemetrysourcefactory.h"
#include "jsontelemetrysource.h"

ITelemetrySource* TelemetrySourceFactory::create(const QString& type, QObject* parent)
{
    if (type.compare("json", Qt::CaseInsensitive) == 0)
        return new JsonTelemetrySource(parent);

    // Future:
    // if (type == "csv") return new CsvTelemetrySource(parent);
    // if (type == "bin") return new BinaryTelemetrySource(parent);

    return nullptr;
}

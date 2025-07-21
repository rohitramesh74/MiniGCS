#include "telemetryworker.h"
#include "../sources/itelemetrysource.h"
#include <QDebug>

TelemetryWorker::TelemetryWorker(ITelemetrySource* source, const QString& filePath, QObject* parent)
    : QObject(parent)
{
    if (source) {
        m_dataList = source->loadTelemetry(filePath);
    } else {
        qWarning() << "TelemetryWorker initialized with null source!";
    }

    m_replayTimer = new QTimer(this);
    m_replayTimer->setInterval(100); // 10Hz = 100ms
    connect(m_replayTimer, &QTimer::timeout, this, [this]() {
        if (m_dataList.isEmpty())
            return;

        if (m_currentIndex >= m_dataList.size())
            m_currentIndex = 0;  // ✅ Loop back to first entry

        emit telemetryDataAvailable(m_dataList[m_currentIndex]);
        m_currentIndex++;
    });
}

TelemetryWorker::~TelemetryWorker()
{
    if (m_replayTimer && m_replayTimer->isActive()) {
        m_replayTimer->stop();
    }
}

void TelemetryWorker::startReplay()
{
    if (!m_dataList.isEmpty()) {
        m_currentIndex = 0;
        m_replayTimer->start();
    } else {
        qWarning() << "No telemetry data to replay!";
        emit finished();
    }
}

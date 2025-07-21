#include "telemetrycontroller.h"
#include "../models/telemetrymodel.h"
#include "../workers/telemetryworker.h"
#include "../sources/telemetrysourcefactory.h"
#include "../sources/itelemetrysource.h"

#include <QDebug>

TelemetryController::TelemetryController(QObject* parent)
    : QObject(parent)
{
    m_telemetryModel = new TelemetryModel(this);
}

TelemetryController::~TelemetryController()
{
    cleanupWorker();
}

double TelemetryController::latitude() const { return m_currentData.latitude; }
double TelemetryController::longitude() const { return m_currentData.longitude; }
double TelemetryController::altitude() const { return m_currentData.altitude; }
double TelemetryController::yaw() const { return m_currentData.yaw; }
double TelemetryController::groundSpeed() const { return m_currentData.groundSpeed; }
int TelemetryController::battery() const { return m_currentData.battery; }

TelemetryModel* TelemetryController::telemetryModel() const
{
    return m_telemetryModel;
}

void TelemetryController::startTelemetry(const QString& jsonFilePath)
{
    cleanupWorker();  // Stop any running worker before starting a new one

    ITelemetrySource* source = TelemetrySourceFactory::create("json", this);
    if (!source) {
        qWarning() << "Failed to create telemetry source!";
        return;
    }

    m_worker = new TelemetryWorker(source, jsonFilePath);
    m_workerThread = new QThread(this);

    m_worker->moveToThread(m_workerThread);

    connect(m_workerThread, &QThread::started, m_worker, &TelemetryWorker::startReplay);
    connect(m_worker, &TelemetryWorker::telemetryDataAvailable, this, &TelemetryController::onTelemetryDataReceived);
    connect(m_worker, &TelemetryWorker::finished, this, &TelemetryController::cleanupWorker);

    connect(m_workerThread, &QThread::finished, m_workerThread, &QObject::deleteLater);

    m_workerThread->start();
}

void TelemetryController::onTelemetryDataReceived(const TelemetryData& data)
{
    m_currentData = data;
    emit telemetryChanged();

    if (m_telemetryModel)
        m_telemetryModel->addTelemetryData(data);
}

void TelemetryController::cleanupWorker()
{
    if (m_worker) {
        m_worker->deleteLater();
        m_worker = nullptr;
    }

    if (m_workerThread) {
        m_workerThread->quit();
        m_workerThread->wait();
        m_workerThread = nullptr;
    }

    if (m_telemetryModel)
        m_telemetryModel->clear();
}

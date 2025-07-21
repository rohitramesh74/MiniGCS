#include "dashboardcontroller.h"

DashboardController::DashboardController(QObject* parent)
    : QObject(parent)
{
}

bool DashboardController::showTelemetry() const
{
    return m_showTelemetry;
}

bool DashboardController::showMap() const
{
    return m_showMap;
}

void DashboardController::setShowTelemetry(bool show)
{
    if (m_showTelemetry != show) {
        m_showTelemetry = show;
        emit showTelemetryChanged();
    }
}

void DashboardController::setShowMap(bool show)
{
    if (m_showMap != show) {
        m_showMap = show;
        emit showMapChanged();
    }
}

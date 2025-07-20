#include "dashboardcontroller.h"
#include <QDebug>

DashboardController::DashboardController(QObject *parent)
    : QObject(parent)
{
    m_availableResolutions = {
        QVariantMap{{"label", "1280x720"}, {"width", 1280}, {"height", 720}},
        QVariantMap{{"label", "1920x1080"}, {"width", 1920}, {"height", 1080}},
        QVariantMap{{"label", "640x480"}, {"width", 640}, {"height", 480}}
    };

    emit availableResolutionsChanged();
    emit videoHasAudioChanged();
}

QVariantList DashboardController::availableResolutions() const
{
    return m_availableResolutions;
}

bool DashboardController::videoHasAudio() const
{
    return m_videoHasAudio;
}

bool DashboardController::muted() const
{
    return m_muted;
}

void DashboardController::setMuted(bool muted)
{
    if (m_muted != muted) {
        m_muted = muted;
        emit mutedChanged();
        qDebug() << "Muted changed to:" << m_muted;
    }
}

void DashboardController::changeResolution(int width, int height)
{
    qDebug() << "Changing resolution to:" << width << "x" << height;
    // Placeholder for actual resolution handling
}

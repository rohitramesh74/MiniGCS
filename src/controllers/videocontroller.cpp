#include "videocontroller.h"
#include <QMediaDevices>
#include <QCameraDevice>
#include <QCameraFormat>
#include <QDebug>

VideoController::VideoController(QObject* parent)
    : QObject(parent)
{
    populateAvailableResolutions();

    m_audioInput = new QAudioInput(this);
    //m_audioInput->setActive(!m_muted);

    emit availableResolutionsChanged();
}

VideoController::~VideoController()
{
    // No manual cleanup needed, QObject handles it
}

QVariantList VideoController::availableResolutions() const
{
    return m_availableResolutions;
}

bool VideoController::isMuted() const
{
    return m_muted;
}

void VideoController::setMuted(bool muted)
{
    if (m_muted == muted)
        return;

    m_muted = muted;
    if (m_audioInput)
        //m_audioInput->setActive(!m_muted);

    emit mutedChanged();
}

void VideoController::changeResolution(int width, int height)
{
    qDebug() << "Requested resolution change to:" << width << "x" << height;
    // Note: Actual camera resolution change must be done in QML by setting camera.cameraFormat
    // You can emit a signal here if you want to inform QML to change it
}

void VideoController::populateAvailableResolutions()
{
    m_availableResolutions.clear();

    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    if (!cameras.isEmpty()) {
        const auto formats = cameras.first().videoFormats();
        for (const QCameraFormat& format : formats) {
            QSize res = format.resolution();
            QVariantMap entry;
            entry["label"] = QString("%1x%2").arg(res.width()).arg(res.height());
            entry["width"] = res.width();
            entry["height"] = res.height();
            if(!m_availableResolutions.contains(entry)) {
                m_availableResolutions.append(entry);
            }
        }
    }

    if (m_availableResolutions.isEmpty()) {
        m_availableResolutions = {
            QVariantMap{{"label", "1280x720"}, {"width", 1280}, {"height", 720}},
            QVariantMap{{"label", "640x480"}, {"width", 640}, {"height", 480}}
        };
    }
}

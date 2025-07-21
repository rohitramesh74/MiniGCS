#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#pragma once

#include <QObject>
#include <QAudioInput>
#include <QVariantList>

class VideoController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList availableResolutions READ availableResolutions NOTIFY availableResolutionsChanged)
    Q_PROPERTY(bool muted READ isMuted WRITE setMuted NOTIFY mutedChanged)

public:
    explicit VideoController(QObject* parent = nullptr);
    ~VideoController();

    QVariantList availableResolutions() const;
    bool isMuted() const;

    Q_INVOKABLE void changeResolution(int width, int height);
    Q_INVOKABLE void setMuted(bool muted);

signals:
    void availableResolutionsChanged();
    void mutedChanged();

private:
    void populateAvailableResolutions();

    QVariantList m_availableResolutions;
    QAudioInput* m_audioInput = nullptr;
    bool m_muted = false;
};

#endif // VIDEOCONTROLLER_H

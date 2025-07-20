#ifndef DASHBOARDCONTROLLER_H
#define DASHBOARDCONTROLLER_H

#pragma once

#include <QObject>
#include <QVariantList>

class DashboardController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList availableResolutions READ availableResolutions NOTIFY availableResolutionsChanged)
    Q_PROPERTY(bool videoHasAudio READ videoHasAudio NOTIFY videoHasAudioChanged)
    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged)

public:
    explicit DashboardController(QObject *parent = nullptr);

    QVariantList availableResolutions() const;
    bool videoHasAudio() const;
    bool muted() const;

    Q_INVOKABLE void changeResolution(int width, int height);

public slots:
    void setMuted(bool muted);

signals:
    void availableResolutionsChanged();
    void videoHasAudioChanged();
    void mutedChanged();

private:
    QVariantList m_availableResolutions;
    bool m_videoHasAudio = true;   // Placeholder
    bool m_muted = false;
};


#endif // DASHBOARDCONTROLLER_H

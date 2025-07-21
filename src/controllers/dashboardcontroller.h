#ifndef DASHBOARDCONTROLLER_H
#define DASHBOARDCONTROLLER_H

#pragma once

#include <QObject>

class DashboardController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool showTelemetry READ showTelemetry WRITE setShowTelemetry NOTIFY showTelemetryChanged)
    Q_PROPERTY(bool showMap READ showMap WRITE setShowMap NOTIFY showMapChanged)

public:
    explicit DashboardController(QObject* parent = nullptr);

    bool showTelemetry() const;
    bool showMap() const;

public slots:
    void setShowTelemetry(bool show);
    void setShowMap(bool show);

signals:
    void showTelemetryChanged();
    void showMapChanged();

private:
    bool m_showTelemetry = true;
    bool m_showMap = true;
};

#endif // DASHBOARDCONTROLLER_H

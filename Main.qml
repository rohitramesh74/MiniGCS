import QtQuick 6.5
import QtQuick.Controls 6.5
import QtQuick.Layouts 6.5
import QtMultimedia 6.5

import MiniGCS 1.0

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: "Mini Ground Control Station"

    // State from DashboardController
    property bool showTelemetry: dashboardController.showTelemetry
    property bool showMap: dashboardController.showMap

    // Video + Audio State from VideoController
    property bool isMuted: videoController.muted
    property var availableResolutions: videoController.availableResolutions

    // Camera Control (Pure QML)
    property bool cameraActive: true

    CaptureSession {
        id: captureSession
        camera: Camera {
            id: camera
            active: cameraActive
        }
        videoOutput: viewfinder
    }

    VideoOutput {
        id: viewfinder
        anchors.fill: parent
        // onFrameAvailable: {
        //     frameCount += 1
        // }
    }

    // Overlay Layer for Toolbar & Panels
    Item {
        anchors.fill: parent

        ToolBar {
            id: toolbar
            anchors.top: parent.top
            width: parent.width
            height: 40

            background: Rectangle {
                color: "#2c3e50"
            }

            RowLayout {
                anchors.fill: parent
                spacing: 4

                // Left Controls: Panels & Camera
                RowLayout {
                    Layout.alignment: Qt.AlignLeft
                    spacing: 4

                    ToolButton {
                        text: showTelemetry ? "🗖 Telemetry" : "🗕 Telemetry"
                        onClicked: dashboardController.setShowTelemetry(!showTelemetry)
                        width: 120
                    }

                    ToolButton {
                        text: showMap ? "🗖 Map" : "🗕 Map"
                        onClicked: dashboardController.setShowMap(!showMap)
                        width: 100
                    }

                    ToolButton {
                        text: cameraActive ? "⏹ Stop Camera" : "▶ Start Camera"
                        onClicked: cameraActive = !cameraActive
                        width: 120
                    }

                    ComboBox {
                        id: resolutionSelector
                        model: availableResolutions
                        textRole: "label"
                        width: 140
                        onActivated: {
                            videoController.changeResolution(
                                availableResolutions[index].width,
                                availableResolutions[index].height
                            )
                        }
                    }
                }

                // Spacer
                Item {
                    Layout.fillWidth: true
                }

                // Right-Aligned Mute Button
                ToolButton {
                    text: isMuted ? "🔇 Mute" : "🔊 Unmute"
                    onClicked: videoController.setMuted(!isMuted)
                    width: 100
                }
            }
        }

        // Telemetry Panel - Bottom Left
        // Rectangle {
        //     id: telemetryPanel
        //     visible: showTelemetry
        //     width: 200; height: 150
        //     color: "darkred"
        //     anchors.bottom: parent.bottom
        //     anchors.left: parent.left
        //     anchors.margins: 20

        //     Text {
        //         anchors.centerIn: parent
        //         text: "Telemetry Panel"
        //         color: "white"
        //     }
        // }
        TelemetryPanel {
            id: telemetryPanel
            visible: showTelemetry
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 20
        }


        // Map Panel - Bottom Right
        Rectangle {
            id: mapPanel
            visible: showMap
            width: 300; height: 200
            color: "darkgreen"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 20

            Text {
                anchors.centerIn: parent
                text: "Map Panel"
                color: "white"
            }
        }
    }
}

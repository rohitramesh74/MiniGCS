import QtQuick 6.5
import QtQuick.Controls 6.5
import QtQuick.Layouts 6.5
import QtMultimedia 6.5

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: "Mini Ground Control Station"

    property bool showTelemetry: true
    property bool showMap: true
    property bool isMuted: dashboardController.muted

    property var availableResolutions: dashboardController.availableResolutions
    property bool videoHasAudio: dashboardController.videoHasAudio

    // Base Video Layer
    Item {
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: "black"
            Text {
                anchors.centerIn: parent
                text: "Video Feed Placeholder"
                color: "white"
            }
        }
    }

    // Overlay Layer
    Item {
        anchors.fill: parent

        // Styled Toolbar at Top
        ToolBar {
            id: toolbar
            anchors.top: parent.top
            width: parent.width
            height: 40
            background: Rectangle {
                color: "#2c3e50"   // Dark Blue-Grey
            }

            RowLayout {
                anchors.fill: parent
                spacing: 4

                // Left Aligned Buttons Group
                RowLayout {
                    Layout.alignment: Qt.AlignLeft
                    spacing: 4

                    ToolButton {
                        text: showTelemetry ? "🗖 Telemetry" : "🗕 Telemetry"
                        onClicked: showTelemetry = !showTelemetry
                        width: 120
                    }

                    ToolButton {
                        text: showMap ? "🗖 Map" : "🗕 Map"
                        onClicked: showMap = !showMap
                        width: 100
                    }

                    ComboBox {
                        id: resolutionSelector
                        model: availableResolutions
                        textRole: "label"
                        width: 140
                        onActivated: {
                            dashboardController.changeResolution(availableResolutions[index].width, availableResolutions[index].height);
                        }
                    }
                }

                // Spacer to push Mute to Right
                Item {
                    Layout.fillWidth: true
                }

                // Right Aligned Mute Button
                ToolButton {
                    text: isMuted ? "🔇 Mute" : "🔊 Unmute"
                    visible: videoHasAudio
                    onClicked: {
                        isMuted = !isMuted;
                        dashboardController.setMuted(isMuted);
                    }
                    width: 100
                }
            }
        }

        // Telemetry Panel - Bottom Left
        Rectangle {
            id: telemetryPanel
            visible: showTelemetry
            width: 200; height: 150
            color: "darkred"
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 20

            Text {
                anchors.centerIn: parent
                text: "Telemetry Panel"
                color: "white"
            }
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

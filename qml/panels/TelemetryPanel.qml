import QtQuick 6.5
import QtQuick.Controls 6.5
import QtQuick.Layouts 6.5

Rectangle {
    id: telemetryPanel
    property alias latitudeText: latitudeValue.text
    property alias longitudeText: longitudeValue.text
    property alias altitudeText: altitudeValue.text
    property alias yawText: yawValue.text
    property alias groundSpeedText: groundSpeedValue.text
    property alias batteryValue: batteryBar.value

    visible: true
    width: 250; height: 200
    color: "#8e44ad"
    radius: 8

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 4

        Label {
            text: "Telemetry"
            font.bold: true
            font.pointSize: 14
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            Label { text: "Latitude:"; width: 100 }
            Label { id: latitudeValue; text: "N/A"; width: 100 }
        }
        RowLayout {
            Label { text: "Longitude:"; width: 100 }
            Label { id: longitudeValue; text: "N/A"; width: 100 }
        }
        RowLayout {
            Label { text: "Altitude:"; width: 100 }
            Label { id: altitudeValue; text: "N/A"; width: 100 }
        }
        RowLayout {
            Label { text: "Yaw:"; width: 100 }
            Label { id: yawValue; text: "N/A"; width: 100 }
        }
        RowLayout {
            Label { text: "Ground Speed:"; width: 100 }
            Label { id: groundSpeedValue; text: "N/A"; width: 100 }
        }

        RowLayout {
            Label { text: "Battery:"; width: 100 }
            ProgressBar {
                id: batteryBar
                from: 0
                to: 100
                value: 0
                width: 100
            }
        }
    }
}

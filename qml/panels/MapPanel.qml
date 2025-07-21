import QtQuick 6.5
import QtQuick.Controls 6.5
import QtQuick.Layouts 6.5
import QtLocation 6.5
import QtPositioning 6.5

Rectangle {
    id: mapPanel
    property alias centerCoordinate: telemetryMap.center
    property alias zoomLevel: telemetryMap.zoomLevel

    width: 300
    height: 300
    color: "#2c3e50"
    radius: 8

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: telemetryMap
        anchors.fill: parent
        plugin: mapPlugin
        zoomLevel: 16

        // Center on latest telemetry
        center: QtPositioning.coordinate(telemetryController.latitude, telemetryController.longitude)

        // Trail of telemetry data (30s history)
        MapItemView {
            model: telemetryModel

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(latitude, longitude)
                anchorPoint.x: 3
                anchorPoint.y: 3
                sourceItem: Rectangle {
                    width: 6
                    height: 6
                    color: "red"
                    radius: 3
                }
            }
        }

        // Current Position - Drone Icon
        MapQuickItem {
            id: droneMarker
            anchorPoint.x: 10
            anchorPoint.y: 10
            coordinate: QtPositioning.coordinate(telemetryController.latitude, telemetryController.longitude)

            sourceItem: Image {
                source: "qrc:/assets/icon/drone_icon.png"
                width: 20; height: 20
            }
        }
    }

    // Zoom Controls
    Column {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 5

        Button {
            text: "+"
            onClicked: telemetryMap.zoomLevel += 1
        }
        Button {
            text: "-"
            onClicked: telemetryMap.zoomLevel -= 1
        }
    }
}

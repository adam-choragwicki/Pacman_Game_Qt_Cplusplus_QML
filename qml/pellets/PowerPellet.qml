import QtQuick

Item {
    id: powerPelletRoot

    property int scaledWidth
    property int scaledHeight

    Rectangle {
        id: rectangleInPowerPellet

        color: "white"
        radius: 50 // circle

        anchors.centerIn: parent

        width: powerPelletRoot.scaledWidth
        height: powerPelletRoot.scaledHeight
    }
}

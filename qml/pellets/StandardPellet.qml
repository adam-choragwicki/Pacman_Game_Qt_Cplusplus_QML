import QtQuick

Item {
    id: standardPelletRoot

    property int scaledWidth
    property int scaledHeight

    Rectangle {
        id: rectangleInStandardPellet

        color: "white"
        radius: 50 // circle

        anchors.centerIn: parent

        width: standardPelletRoot.scaledWidth
        height: standardPelletRoot.scaledHeight
    }
}

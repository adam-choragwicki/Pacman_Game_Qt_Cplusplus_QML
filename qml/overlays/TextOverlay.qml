import QtQuick

Text {
    id: textOverlay
    objectName: "textOverlay" // Required for C++ lookup
    anchors.centerIn: parent
    visible: true

    required property real uiScale

    font.pixelSize: 40 * uiScale
    color: "red"

    text: "NULL"
}

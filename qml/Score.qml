import QtQuick

Text {
    required property real uiScale

    text: "Score: " + ScoreManager.score
    color: "white"
    font.pixelSize: 30 * uiScale
}

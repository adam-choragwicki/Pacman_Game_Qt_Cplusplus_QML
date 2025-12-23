import QtQuick

Item {
    id: endGameOverlayRoot
    visible: false
    property int currentIndex: 0

    property string message: "NULL" // to be filled from C++ dynamically
    property string score: "NULL" // to be filled from C++ dynamically

    signal playAgainClicked()
    signal quitClicked()

    required property real uiScale // scale propagated from UiScaler

    // Semi-transparent dark layer
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.9
    }

    // Centered dialog content
    Column {
        anchors.centerIn: parent
        spacing: 25 * uiScale
        width: parent.width * 0.5

        Text {
            text: endGameOverlayRoot.message
            color: "white"
            font.pixelSize: 64 * uiScale
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "SCORE\n" + endGameOverlayRoot.score
            color: "white"
            font.pixelSize: 40 * uiScale
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Repeater {
            model: ["PLAY AGAIN", "QUIT"]

            delegate: Rectangle {
                width: 400 * uiScale
                height: 100 * uiScale
                radius: 16 * uiScale
                anchors.horizontalCenter: parent.horizontalCenter

                color: index === endGameOverlayRoot.currentIndex ? "#3A3A3A" : "#2A2A2A"
                border.color: index === endGameOverlayRoot.currentIndex ? "#5BC0EB": "#00000000"
                border.width: 10 * uiScale

                Text {
                    anchors.centerIn: parent
                    text: modelData
                    color: "white"
                    font.pixelSize: 36 * uiScale
                    font.bold: true
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: endGameOverlayRoot.currentIndex = index
                    onClicked: {
                        if (index === 0) endGameOverlayRoot.playAgainClicked()
                        else endGameOverlayRoot.quitClicked()
                    }
                }
            }
        }
    }
}

import QtQuick

Window {
    id: mainWindow
    width: 614
    height: 740
    minimumWidth: 614
    minimumHeight: 740
    visible: true

    Component.onCompleted: {
        if (Controller.startInFullScreenEnabled) {
            console.log("Starting in fullscreen")
            mainWindow.showFullScreen()
        } else {
            console.log("Starting in windowed mode")
            mainWindow.showNormal()
        }
    }

    UiScaler {
        id: uiScaler
        target: gameArea
        referenceWidth: 614
        referenceHeight: 740
    }

    // Maintain the aspect ratio with black bars
    Rectangle {
        id: letterboxContainer
        anchors.fill: parent
        color: "black"

        // This Item keeps the correct scaling inside any window shape
        Item {
            id: gameViewport
            anchors.centerIn: parent

            readonly property real targetAspect: 614/740
            property real currentAspect: letterboxContainer.width / letterboxContainer.height

            // Maintain the aspect ratio and center it */
            width: currentAspect > targetAspect ? letterboxContainer.height * targetAspect : letterboxContainer.width
            height: currentAspect > targetAspect ? letterboxContainer.height : letterboxContainer.width / targetAspect

            GameArea {
                id: gameArea
                anchors.fill: parent
                uiScale: uiScaler.scale
            }
        }
    }

    // Overlays
    TextOverlay {
        visible: false
        uiScale: gameArea.uiScale
    }

    EndGameOverlay {
        visible: false
        objectName: "endGameOverlay"
        anchors.fill: parent
        uiScale: gameArea.uiScale

        onPlayAgainClicked: Controller.onPlayAgainClicked()
        onQuitClicked: Controller.onQuitClicked()
    }

    EscapeMenuOverlay {
        visible: false
        objectName: "escapeMenuOverlay"
        anchors.fill: parent
        uiScale: gameArea.uiScale

        onResumeClicked: Controller.onResumeClicked()
        onRestartClicked: Controller.onRestartClicked()
        onQuitClicked: Controller.onQuitClicked()
    }
}

import QtQuick

Item {
    id: gameAreaRoot

    required property real uiScale // scale propagated from UiScaler

    // onWidthChanged: {
    //     console.log("Game area width changed to " + width)
    // }
    //
    // onHeightChanged: {
    //     console.log("Game area height changed to " + height)
    // }

    Arena {
        id: arena
        anchors.fill: parent
        uiScale: gameAreaRoot.uiScale
    }

    Pacman {
        uiScale: gameArea.uiScale
    }

    BlueGhost {
        uiScale: gameArea.uiScale
    }

    OrangeGhost {
        uiScale: gameArea.uiScale
    }

    PurpleGhost {
        uiScale: gameArea.uiScale
    }

    RedGhost {
        uiScale: gameArea.uiScale
    }

    /* Standard pellets */
    Repeater {
        model: standardPelletsModel
        delegate: StandardPellet {
            x: model.xRole * uiScale
            y: model.yRole * uiScale
            scaledWidth: model.widthRole * uiScale
            scaledHeight: model.heightRole * uiScale
            visible: model.aliveRole
        }
    }

    /* Power pellets */
    Repeater {
        model: powerPelletsModel
        delegate: PowerPellet {
            x: model.xRole * uiScale
            y: model.yRole * uiScale
            scaledWidth: model.widthRole * uiScale
            scaledHeight: model.heightRole * uiScale
            visible: model.aliveRole
        }
    }

    Score {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15 * uiScale
        uiScale: gameArea.uiScale
    }

    // input handler
    GameInput {
        id: gameInput
        objectName: "gameInput"
        anchors.fill: parent
    }
}

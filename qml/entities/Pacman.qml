import QtQuick

Item {
    required property real uiScale // scale propagated from UiScaler

    x: pacman.x_ * uiScale
    y: pacman.y_ * uiScale

    Image {
        anchors.centerIn: parent

        property int direction: pacman.directionQML
        property int animationPhase: pacman.animationPhase

        width: pacman.diameter * uiScale
        height: pacman.diameter * uiScale
        smooth: true

        // Pacman has 4 animation frames: 0..3
        readonly property int frame: {
            if (animationPhase < 0)
                return 0
            return animationPhase % 4
        }

        // rotation is purely derived from the direction
        rotation: {
            switch (direction) {
                case 3:
                    return -90   // UP
                case 4:
                    return 90    // DOWN
                default:
                    return 0    // LEFT / RIGHT
            }
        }

        // mirror only applies for LEFT
        mirror: direction === 2

        source: {
            switch (frame) {
                case 0:
                    return "qrc:/images/pacman/pacman_right_close.png"
                case 1:
                    return "qrc:/images/pacman/pacman_right_open_1.png"
                case 2:
                    return "qrc:/images/pacman/pacman_right_open_2.png"
                case 3:
                    return "qrc:/images/pacman/pacman_right_open_3.png"
                default:
                    console.error("Pacman: invalid frame", frame)
                    return ""
            }
        }
    }
}

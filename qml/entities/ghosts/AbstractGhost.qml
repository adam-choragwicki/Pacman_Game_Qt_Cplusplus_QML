import QtQuick

Item {
    required property real uiScale // scale propagated from UiScaler

    // inputs (must be bound by concrete ghost)
    required property int diameter
    required property int direction            // 1..4
    required property int animationPhase        // 0..1

    // scared state 0 = normal, 1 = scared blue, 2 = scared white
    required property int ghostScaredState

    // example assetPrefix: "qrc:/images/ghosts/blue/ghost_blue_"
    required property string assetPrefix

    readonly property string scaredBluePrefix: "qrc:/images/ghosts/scared_blue/ghost_scared_blue_"
    readonly property string scaredWhitePrefix: "qrc:/images/ghosts/scared_white/ghost_scared_white_"

    Image {
        anchors.centerIn: parent

        width: diameter * uiScale
        height: diameter * uiScale
        smooth: true

        readonly property int frame: (animationPhase >= 0 ? (animationPhase % 2) : 0) + 1

        // choose a scared asset (non-directional) first, otherwise directional asset
        source: {
            // Scared state takes precedence; scared assets are non-directional and indexed by frame
            if (ghostScaredState === 1) { // scared blue
                return scaredBluePrefix.length > 0 ? (scaredBluePrefix + frame + ".png") : ""
            }
            if (ghostScaredState === 2) { // scared white
                return scaredWhitePrefix.length > 0 ? (scaredWhitePrefix + frame + ".png") : ""
            }

            // Normal (non-scared) behaviour (directional assets)
            switch (direction) {
                case 1: // RIGHT
                    return assetPrefix + "right_" + frame + ".png"
                case 2: // LEFT (mirror RIGHT asset)
                    return assetPrefix + "right_" + frame + ".png"
                case 3: // UP
                    return assetPrefix + "up_" + frame + ".png"
                case 4: // DOWN
                    return assetPrefix + "down_" + frame + ".png"
                default:
                    console.error("Ghost: invalid direction", direction)
                    return ""
            }
        }

        // only mirror in the normal LEFT state; scared sprites are not mirrored
        mirror: (ghostScaredState === 0) && (direction === 2)
    }
}

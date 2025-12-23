import QtQuick

AbstractGhost {
    x: purpleGhost.x_ * uiScale
    y: purpleGhost.y_ * uiScale

    diameter: purpleGhost.diameter
    direction: purpleGhost.directionQML
    animationPhase: purpleGhost.animationPhase

    assetPrefix: "qrc:/images/ghosts/purple/ghost_purple_"

    ghostScaredState: purpleGhost.scaredState
}

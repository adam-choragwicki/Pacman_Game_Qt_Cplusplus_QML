import QtQuick

AbstractGhost {
    x: redGhost.x_ * uiScale
    y: redGhost.y_ * uiScale

    diameter: redGhost.diameter
    direction: redGhost.directionQML
    animationPhase: redGhost.animationPhase

    assetPrefix: "qrc:/images/ghosts/red/ghost_red_"

    ghostScaredState: redGhost.scaredState
}

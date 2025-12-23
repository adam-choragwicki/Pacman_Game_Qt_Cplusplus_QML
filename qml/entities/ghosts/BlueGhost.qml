import QtQuick

AbstractGhost {
    x: blueGhost.x_ * uiScale
    y: blueGhost.y_ * uiScale

    diameter: blueGhost.diameter
    direction: blueGhost.directionQML
    animationPhase: blueGhost.animationPhase

    assetPrefix: "qrc:/images/ghosts/blue/ghost_blue_"

    ghostScaredState: blueGhost.scaredState
}

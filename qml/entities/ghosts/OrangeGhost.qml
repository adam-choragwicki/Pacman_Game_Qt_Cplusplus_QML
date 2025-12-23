import QtQuick

AbstractGhost {
    x: orangeGhost.x_ * uiScale
    y: orangeGhost.y_ * uiScale

    diameter: orangeGhost.diameter
    direction: orangeGhost.directionQML
    animationPhase: orangeGhost.animationPhase

    assetPrefix: "qrc:/images/ghosts/orange/ghost_orange_"

    ghostScaredState: orangeGhost.scaredState
}

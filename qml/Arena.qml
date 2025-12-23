import QtQuick

Item {
    id: arenaRoot

    required property real uiScale // scale propagated from UiScaler

    Image{
        width: 614 * uiScale
        height: 740 * uiScale

        smooth: true
        source: "qrc:/images/arena/arena.png"
    }
}

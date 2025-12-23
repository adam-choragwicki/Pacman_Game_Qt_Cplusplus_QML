import QtQuick

Item {
    property bool scalingEnabled: true

    // The root item whose size is used for scaling.
    required property Item target

    // Reference resolution for UI layout.
    required property int referenceWidth
    required property int referenceHeight

    // Scaling factors. UI scale should be based mostly on height for consistency.
    property real scale: scalingEnabled ? (target.height / referenceHeight) : 1.0

    function px(value: real): real {
        return value * scale
    }
}

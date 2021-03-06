import QtQuick 2.0
import "../../widgets" as Widgets

Item {
    id: mouseOptionsMenu

    width: parent.width
    height: parent.height

    Component.onCompleted: {
        sideText.text = wz.tr("Mouse Options")
    }

    Widgets.ImageButton {
        defaultSource: "image://imagemap/icon back"
        hoverSource: "image://imagemap/icon back hi"
        x: 5; y: 5
        onClicked: {
            createMenu("menu/options.qml");
        }
    }

    // Labels
    Column {
        id: labels
        width: 280
        anchors.top: parent.top
        anchors.topMargin: 56
        anchors.left: parent.left
        anchors.leftMargin: 30

        spacing: 15

        Widgets.LargeText { text: wz.tr("Reverse Rotation") }
        Widgets.LargeText { height: 60;  text: wz.tr("Trap Cursor") }
        Widgets.LargeText { text: wz.tr("Switch Mouse Buttons") }
        Widgets.LargeText { text: wz.tr("Rotate Screen") }
    }

    // Options
    Column {
        width: 165
        anchors.top: parent.top
        anchors.topMargin: 56
        anchors.left: labels.right

        spacing: 15
        Widgets.ClickSelect {
            width: parent.width;
            options: [wz.tr("Off"), wz.tr("On")]
            value: wz.config.get("mouseflip") ? 1 : 0;
            onValueChanged: wz.config.set("mouseflip", (value == 1))
        }
        Widgets.ClickSelect {
            width: parent.width; height: 60;
            options: [wz.tr("Off"), wz.tr("On")]
            value: wz.config.get("trapCursor") ? 1 : 0;
            onValueChanged: wz.config.set("trapCursor", (value == 1))
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: [wz.tr("Off"), wz.tr("On")]
            value: wz.config.get("RightClickOrders") ? 1 : 0;
            onValueChanged: wz.config.set("RightClickOrders", (value == 1))
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: [wz.tr("Right Mouse"), wz.tr("Middle Mouse")]
            value: wz.config.get("MiddleClickRotate") ? 1 : 0;
            onValueChanged: wz.config.set("MiddleClickRotate", (value == 1))
        }
    }
}

import QtQuick 2.9
import QtQuick.Window 2.2

Item {
    property alias background: frame.color;
    property alias radius: frame.radius;
    property alias border: frame.border;
    property alias input: input;

    /* 私有属性 */
    QtObject {
        id: self;
        property bool isMouseHover;
        property int cursorShape;
    }

    /* 背景框 */
    Rectangle {
        id: frame;
        anchors.fill: parent;
        color: "#ffffff";
        border.color: (input.focus || self.isMouseHover) ? "#c7e2f1" : "#e3e9ef";
        radius: 4;
    }

    /* 鼠标事件 */
    MouseArea {
        anchors.fill: input;
        hoverEnabled: true;
        onEntered: {
            self.isMouseHover = true;
            if ('undefined' !== typeof(cursorShape)) {
                self.cursorShape = cursorShape;
                cursorShape = Qt.IBeamCursor;
            }
        }
        onExited: {
            self.isMouseHover = false;
            if ('undefined' !== typeof(cursorShape)) {
               cursorShape = self.cursorShape;
            }
        }
    }

    /* 输入框 */
    TextInput {
        id: input;
        anchors.left: parent.left;
        anchors.leftMargin: frame.radius > 2 ? frame.radius - 1 : 1;
        anchors.right: parent.right;
        anchors.rightMargin: anchors.leftMargin;
        height: parent.height;
        verticalAlignment: Text.AlignVCenter;
        clip: true;
        selectByMouse: true;
        color: "#000000";
        selectionColor: "#3399ff";
        selectedTextColor: "#ffffff";
        font.pixelSize: height * 0.55;
    }
}

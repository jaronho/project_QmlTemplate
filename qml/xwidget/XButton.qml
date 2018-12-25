import QtQuick 2.9

Item {
    property alias radius: frame.radius;                            /* 按钮四个角弧度 */
    property color backgroundColorNormal: "#ebebeb";                /* 按钮常态时背景颜色 */
    property color backgroundColorHover: "#d9f0fc";                 /* 鼠标移到按钮上时背景颜色 */
    property color backgroundColorPress: "#c4e5f6";                 /* 鼠标按下时按钮背景颜色 */
    property color borderColorNormal: "#707070";                    /* 按钮常态边框颜色 */
    property color borderColorHover: "#3c7fb1";                     /* 鼠标移到按钮上时边框颜色 */
    property color borderColorPress: "#2c5a8c";                     /* 鼠标按下时按钮边框颜色 */
    property int borderWidth: 1;                                    /* 边框宽度 */
    property string imageSourceNormal: "";                          /* 按钮常态时图片资源 */
    property string imageSourceHover: "";                           /* 鼠标移到按钮上时图片资源 */
    property string imageSourcePress: "";                           /* 鼠标按下时按钮图片资源 */
    property alias textColor: hint.color;                           /* 按钮文字颜色 */
    property alias textOpacity: hint.opacity;                       /* 按钮文字透明度 */
    property alias font: hint.font;                                 /* 按钮文字 */
    property alias text: hint.text;                                 /* 按钮文字 */
    property var onButtonEnter: null;                               /* 鼠标移到按钮上的回调函数 */
    property var onButtonExit: null;                                /* 鼠标离开按钮上的回调函数 */
    property var onButtonPress: null;                               /* 鼠标按下时的回调函数 */
    property var onButtonRelease: null;                             /* 鼠标释放时的回调函数 */
    property var onButtonClick: null;                               /* 鼠标点击时的回调函数 */

    width: 50;
    height: 20;

    /* 私有属性 */
    QtObject {
        id: self;
        property bool isMouseHover;
        property bool isMousePress;

        function getBackgroundColor() {
            if (isMousePress) {
                return isMouseHover ? backgroundColorPress : backgroundColorHover;
            }
            return isMouseHover ? backgroundColorHover : backgroundColorNormal;
        }

        function getBorderColor() {
            if (isMousePress) {
                return isMouseHover ? borderColorPress : borderColorHover;
            }
            return isMouseHover ? borderColorHover : borderColorNormal;
        }

        function getImageSource() {
            if (0 === imageSourcePress.length) {
                if (0 === imageSourceHover.length) {
                    imageSourcePress = imageSourceNormal;
                } else {
                    imageSourcePress = imageSourceHover;
                }
            }
            if (0 === imageSourceHover.length) {
                if (0 === imageSourcePress.length) {
                    imageSourceHover = imageSourceNormal;
                } else {
                    imageSourceHover = imageSourcePress;
                }
            }
            if (isMousePress) {
                return isMouseHover ? imageSourcePress : imageSourceHover;
            }
            return isMouseHover ? imageSourceHover : imageSourceNormal;
        }
    }

    /* 背景框 */
    Rectangle {
        id: frame;
        anchors.fill: parent;
        color: self.getBackgroundColor();
        border.color: self.getBorderColor();
        radius: 4;
    }

    /* 背景图片 */
    Image {
        id: image;
        anchors.fill: parent;
        source: self.getImageSource();
    }

    /* 文本 */
    Text {
        id: hint;
        anchors.left: parent.left;
        anchors.leftMargin: frame.radius > 2 ? frame.radius - 1 : 1;
        anchors.right: parent.right;
        anchors.rightMargin: anchors.leftMargin;
        anchors.top: parent.top;
        anchors.topMargin: anchors.leftMargin;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: anchors.leftMargin;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        font.pixelSize: height * 0.7;
        color: "#000000";
        opacity: 1;
        text: "Button";
    }

    /* 鼠标事件 */
    MouseArea {
        anchors.fill: parent;
        hoverEnabled: true;
        onEntered: {
            self.isMouseHover = true;
            if ('function' === typeof(onButtonEnter)) {
                onButtonEnter();
            }
        }
        onExited: {
            self.isMouseHover = false;
            if ('function' === typeof(onButtonExit)) {
                onButtonExit();
            }
        }
        onPressed: {
            self.isMousePress = true;
            if ('function' === typeof(onButtonPress)) {
                onButtonPress();
            }
        }
        onReleased: {
            self.isMousePress = false;
            if ('function' === typeof(onButtonRelease)) {
                onButtonRelease();
            }
        }
        onClicked: {
            if ('function' === typeof(onButtonClick)) {
                onButtonClick();
            }
        }
    }
}

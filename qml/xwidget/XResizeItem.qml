import QtQuick 2.9
import QtQuick.Window 2.2

Item {
    /* 公有属性 */
    property var container;                 /* 挂载容器 */
    property int minWidth: width;           /* 最小宽度 */
    property int minHeight: height;         /* 最小高度 */
    property int maxWidth: width;           /* 最大宽度 */
    property int maxHeight: height;         /* 最大高度 */
    property bool moveFlag: true;           /* 是否可以移动 */
    property int borderSize: 5;             /* 有效边框大小,<=0时,大小不可以调整 */
    property bool showBorder: false;        /* 是否显示边框 */

    /* 私有属性 */
    QtObject {
        id: self;
        property bool mIsPressed: false;
        property point mPrePoint: Qt.point(0, 0);
    }

    width: container ? container.width : parent.width;
    height: container ? container.height : parent.height;

    /* 左上角 */
    Rectangle {
        id: left_top;
        width: borderSize;
        height: borderSize;
        anchors.left: parent.left;
        anchors.top: parent.top;
        /*MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: {
                if ('undefined' !== typeof(cursorShape)) {
                    cursorShape = Qt.SizeFDiagCursor;
                }
            }
            onPressed: press(mouse);
            onReleased: release();
            onPositionChanged: positionChange(mouse, 1);
        }*/
        color: showBorder ? "red" : "transparent";
    }

    /* 顶部 */
    Rectangle {
        id: top;
        height: borderSize;
        anchors.left: left_top.right;
        anchors.right: right_top.left;
        anchors.top: parent.top;
        /*MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: {
                if ('undefined' !== typeof(cursorShape)) {
                    cursorShape = Qt.SizeVerCursor;
                }
            }
            onPressed: press(mouse);
            onReleased: release();
            onMouseYChanged: positionChange(Qt.point(self.mPrePoint.x, mouseY), 2);
        }*/
        color: showBorder ? "blue" : "transparent";
    }

    /* 右上角 */
    Rectangle {
        id: right_top;
        width: borderSize;
        height: borderSize;
        anchors.right: parent.right;
        anchors.top: parent.top;
        /*MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: {
                if ('undefined' !== typeof(cursorShape)) {
                    cursorShape = Qt.SizeBDiagCursor;
                }
            }
            onPressed: press(mouse);
            onReleased: release();
            onPositionChanged: positionChange(mouse, 3);
        }*/
        color: showBorder ? "red" : "transparent";
    }

    /* 左边 */
    Rectangle {
        id: left;
        width: borderSize;
        anchors.left: parent.left;
        anchors.top: left_top.bottom;
        anchors.bottom: left_bottom.top;
        /*MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: {
                if ('undefined' !== typeof(cursorShape)) {
                    cursorShape = Qt.SizeHorCursor;
                }
            }
            onPressed: press(mouse);
            onReleased: release();
            onMouseXChanged: positionChange(Qt.point(mouseX, self.mPrePoint.y), 4);
        }*/
        color: showBorder ? "blue" : "transparent";
    }

    /* 中间 */
    Rectangle {
        id: center;
        anchors.left: left.right;
        anchors.right: right.left;
        anchors.top: top.bottom;
        anchors.bottom: bottom.top;
        MouseArea {
            property point clickPos;
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: {
                if ('undefined' !== typeof(cursorShape)) {
                    cursorShape = Qt.ArrowCursor;
                }
            }
            onPressed: clickPos = Qt.point(mouse.x, mouse.y);
            onPositionChanged: {
                if (pressed && container && moveFlag) {
                    var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y);
                    container.x += delta.x;
                    container.y += delta.y;

                }
            }
        }
        color: showBorder ? "green" : "transparent";
    }

    /* 右边 */
    Rectangle {
        id: right;
        width: borderSize;
        anchors.right: parent.right;
        anchors.top: right_top.bottom;
        anchors.bottom: right_bottom.top;
        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: {
                if ('undefined' !== typeof(cursorShape)) {
                    cursorShape = Qt.SizeHorCursor;
                }
            }
            onPressed: press(mouse);
            onReleased: release();
            onMouseXChanged: positionChange(Qt.point(mouseX, self.mPrePoint.y), 6);
        }
        color: showBorder ? "blue" : "transparent";
    }

    /* 左下角 */
    Rectangle {
        id: left_bottom;
        width: borderSize;
        height: borderSize;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        /*MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: {
                if ('undefined' !== typeof(cursorShape)) {
                    cursorShape = Qt.SizeBDiagCursor;
                }
            }
            onPressed: press(mouse);
            onReleased: release();
            onPositionChanged: positionChange(mouse, 7);
        }*/
        color: showBorder ? "red" : "transparent";
    }

    /* 底部 */
    Rectangle {
        id: bottom;
        height: borderSize;
        anchors.left: left_bottom.right;
        anchors.right: right_bottom.left;
        anchors.bottom: parent.bottom;
        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: {
                if ('undefined' !== typeof(cursorShape)) {
                    cursorShape = Qt.SizeVerCursor;
                }
            }
            onPressed: press(mouse);
            onReleased: release();
            onMouseYChanged: positionChange(Qt.point(self.mPrePoint.x, mouseY), 8);
        }
        color: showBorder ? "blue" : "transparent";
    }

    /* 右下角 */
    Rectangle {
        id: right_bottom;
        width: borderSize;
        height: borderSize;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: {
                if ('undefined' !== typeof(cursorShape)) {
                    cursorShape = Qt.SizeFDiagCursor;
                }
            }
            onPressed: press(mouse);
            onReleased: release();
            onPositionChanged: positionChange(mouse, 9);
        }
        color: showBorder ? "red" : "transparent";
    }

    function press(mouse) {
        self.mIsPressed = true;
        self.mPrePoint = Qt.point(mouse.x, mouse.y);
    }

    function release() {
        self.mIsPressed = false;
    }

    function positionChange(nowPoint, direct) {
        if (!self.mIsPressed || !container || borderSize <= 0) {
            return
        }
        var delta = Qt.point(nowPoint.x - self.mPrePoint.x, nowPoint.y - self.mPrePoint.y);
        var tmpX = container.x, tmpY = container.y;
        var tmpW = container.width, tmpH = container.height;
        if (1 === direct) {
            tmpX += delta.x;
            tmpY += delta.y;
            tmpW -= delta.x;
            tmpH -= delta.y;
        } else if (2 === direct) {
            tmpY += delta.y;
            tmpH -= delta.y;
        } else if (3 === direct) {
            tmpY += delta.y;
            tmpW += delta.x;
            tmpH -= delta.y;
        } else if (4 === direct) {
            tmpX += delta.x;
            tmpW -= delta.x;
        } else if (6 === direct) {
            tmpW += delta.x;
        } else if (7 === direct) {
            tmpX += delta.x;
            tmpW -= delta.x;
            tmpH += delta.y;
        } else if (8 === direct) {
            tmpH += delta.y;
        } else if (9 === direct) {
            tmpW += delta.x;
            tmpH += delta.y;
        }
        if (tmpW < minWidth) {
            if (1 === direct || 4 === direct || 7 === direct) {
                tmpX -= (minWidth - tmpW);
            }
            tmpW = minWidth;
        } else if (tmpW > maxWidth) {
            if (1 === direct || 4 === direct || 7 === direct) {
                tmpX += (tmpW - maxWidth);
            }
            tmpW = maxWidth;
        }
        if (tmpH < minHeight) {
            if (1 === direct || 2 === direct || 3 === direct) {
                tmpY -= (minHeight - tmpH);
            }
            tmpH = minHeight;
        } else if (tmpH > maxHeight) {
            if (1 === direct || 2 === direct || 3 === direct) {
                tmpY += (tmpH - maxHeight);
            }
            tmpH = maxHeight;
        }
        container.x = tmpX;
        container.y = tmpY;
        container.width = tmpW;
        container.height = tmpH;
    }
}

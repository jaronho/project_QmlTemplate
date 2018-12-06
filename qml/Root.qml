import QtQuick 2.9
import QtQuick.Window 2.2
import "ui" as UI
import "xwidget" as XWidget

Window {
    id: window;
    color: Qt.rgba(255, 255, 255, 120);

    property bool _isFixedSize: false;  /* 是否固定大小 */

    /* 加载完毕 */
    Component.onCompleted: {
        _isFixedSize = initializeWindow(0, 640, 480, 320, 240, 960, 720);
    }

    /* 连接器 */
    Connector {
        id: connector;
    }

    /* 处理器 */
    Processor {
        id: processor;
    }

    /* 显示器 */
    XWidget.XResizeItem {
        id: displayer;
        container: window;
        minWidth: window.minimumWidth;
        minHeight: window.minimumHeight;
        maxWidth: window.maximumWidth;
        maxHeight: window.maximumHeight;
        moveFlag: true;
        borderSize: _isFixedSize ? 0 : 3;
        showBorder: false;

        /* 背景层 */
        Item {
            id: layer_background;
            anchors.fill: parent;

            UI.UIBackground {
                id: ui_background;
                anchors.fill: parent;
            }
        }

        /* 场景层 */
        Item {
            id: layer_scene;
            anchors.left: parent.left;
            anchors.leftMargin: displayer.borderSize;
            anchors.top: parent.top;
            anchors.topMargin: displayer.borderSize;
            anchors.right: parent.right;
            anchors.rightMargin: displayer.borderSize;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: displayer.borderSize;

            UI.UIScene {
                id: ui_scene;
                anchors.fill: parent;
            }
        }
    }

    /***********************************************************************
     ******************************* 逻辑接口 *******************************
     ***********************************************************************/

    /* 初始化窗体 */
    function initializeWindow(sysframe, w, h, minW, minH, maxW, maxH) {
        minW = ('number' === typeof(minW) && minW <= w) ? minW : 0;
        minH = ('number' === typeof(minH) && minH <= h) ? minH : 0;
        var isFixedSize = false;
        if (sysframe) { /* 有系统边框 */
            if (w === minW && w === maxW && h === minH && h === maxH) { /* 固定大小 */
                flags = Qt.MSWindowsFixedSizeDialogHint | Qt.WindowMinMaxButtonsHint | Qt.WindowCloseButtonHint;
                isFixedSize = true;
            } else {    /* 可调大小 */
                isFixedSize = false;
            }
        } else {    /* 无系统边框 */
            if (w === minW && w === maxW && h === minH && h === maxH) { /* 固定大小 */
                flags = Qt.Window | Qt.FramelessWindowHint;
                isFixedSize = true;
            } else {    /* 可调大小 */
                flags = Qt.Window | Qt.FramelessWindowHint;
                isFixedSize = false;
            }
        }
        width = w;
        height = h;
        minimumWidth = minW;
        minimumHeight = minH;
        if ('number' === typeof(maxW)) {
            maximumWidth = maxW > w ? maxW : w;
        }
        if ('number' === typeof(maxH)) {
            maximumHeight = maxH > h ? maxH : h;
        }
        return isFixedSize;
    }
}

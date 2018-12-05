import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window;
    title: qsTr("QmlTemplate");
    color: "#EEEEEE";

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
    XResizeItem {
        id: displayer;
        container: window;
        minWidth: window.minimumWidth;
        minHeight: window.minimumHeight;
        maxWidth: window.maximumWidth;
        maxHeight: window.maximumHeight;
        moveFlag: true;
        borderSize: _isFixedSize ? 0 : 5;
        onBorderEntered: handleBorderEntered;
        showBorder: false;

        /* 主界面 */
        UIMain {
            id: ui_main;
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

    /* 处理进入边框 */
    function handleBorderEntered(direct) {
        if (1 === direct) {
            control.onSetCursor(8);
        } else if (2 === direct) {
            control.onSetCursor(5);
        } else if (3 === direct) {
            control.onSetCursor(7);
        } else if (4 === direct) {
            control.onSetCursor(6);
        } else if (5 === direct) {
            control.onSetCursor(0);
        } else if (6 === direct) {
            control.onSetCursor(6);
        } else if (7 === direct) {
            control.onSetCursor(7);
        } else if (8 === direct) {
            control.onSetCursor(5);
        } else if (9 === direct) {
            control.onSetCursor(8);
        }
    }
}

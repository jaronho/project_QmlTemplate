import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2
import "ui"

Item {
    id: root;
    anchors.fill: parent;

    /* 连接器 */
    Connector {
        id: connector;
    }

    /* 处理器 */
    Processor {
        id: processor;
    }

    /* 显示器 */
    Item {
        id: displayer;
        anchors.fill: parent;

        /* 背景层 */
        LayerBackground {
            id: layer_background;
            anchors.fill: parent;
        }

        /* 场景层 */
        LayerScene  {
            id: layer_scene;
            anchors.fill: parent;
        }

        /* 提示层 */
        LayerTips  {
            id: layer_tips;
            anchors.fill: parent;
        }

        /* 虚拟键盘 */
        InputPanel {
            id: virtualKeyboard;
            visible: false;
            anchors.right: parent.right;
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            onActiveChanged: {
                if (!active) {
                    visible = false;
                }
            }
            onVisibleChanged: {
                if ('function' === typeof(visibleCallback)) {
                    visibleCallback();
                }
            }
            property var visibleCallback: null;
        }

        /* 监听鼠标按下事件 */
        MouseArea {
            id: mouse_listener;
            anchors.fill: parent;
            propagateComposedEvents: true;
            onPressed: {
                mouse.accepted = false;
                if ('function' === typeof(pressedCallabck)) {
                    pressedCallabck();
                }
            }
            property var pressedCallabck: null;
        }
    }
}

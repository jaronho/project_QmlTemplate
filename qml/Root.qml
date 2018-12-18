import QtQuick 2.9
import QtQuick.Window 2.2
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
    }
}

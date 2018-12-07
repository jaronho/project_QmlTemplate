import QtQuick 2.9
import QtQuick.Window 2.2
import "ui" as UI

Item {
    id: root;
    width: xrw_width;
    height: xrw_height;

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
        UI.UIBackground {
            id: layer_background;
            anchors.fill: parent;
        }

        /* 场景层 */
        UI.UIScene  {
            id: layer_scene;
            anchors.left: parent.left;
            anchors.leftMargin: displayer.borderSize;
            anchors.top: parent.top;
            anchors.topMargin: displayer.borderSize;
            anchors.right: parent.right;
            anchors.rightMargin: displayer.borderSize;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: displayer.borderSize;
        }
    }
}

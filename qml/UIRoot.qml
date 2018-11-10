import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    width: 640;
    height: 480;
    title: qsTr("QmlTemplate");
    color: "#EEEEEE";

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
        id: root;
        anchors.fill: parent;

        // 主界面
        UIMain {
            id: main;
        }
    }
}

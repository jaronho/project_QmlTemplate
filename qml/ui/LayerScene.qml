import QtQuick 2.0

Rectangle {
    color: "#fafafa";

    UITitle {
        id: ui_title;
        width: parent.width;
        height: parent.height / 8;
    }

    Item {
        id: ui_content;
        width: parent.width;
        height: parent.height - ui_title.height;
        y: ui_title.height;

        UILogin {
            id: ui_login;
            anchors.fill: parent;
        }
    }
}

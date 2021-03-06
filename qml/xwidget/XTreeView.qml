import QtQuick 2.9
import "XTreeItem.js" as XTreeItem

Item {
    property string expandIcon: "";                         /* 扩展图标资源 */
    property string collapseIcon: "";                       /* 折叠图标资源 */
    property color backgroundNormal: "#ffffff";             /* 常态时背景颜色 */
    property color backgroundCurrent: "#308cc6";            /* 选中态时背景颜色 */
    property color textColorNormal: "#000000";              /* 常态时文本颜色 */
    property color textColorCurrent: "#ffffff";             /* 选中态时文本颜色 */
    property font itemFont: Qt.font({pointSize: 14});       /* 文本字体 */
    property int itemHeightOverflow: 4;                     /* 选项高度溢出大小 */
    property int intentSpace: 20;                           /* 缩进空间大小 */
    property var onCurrentItemChanged: null;                /* 选项改变时回调函数 */

    width: 400;
    height: 200;

    ListView {
        id: listview;
        anchors.fill: parent;
        clip: true;
        model: ListModel {
            id: listmodel;
        }
        delegate: Component {
            Column {
                Repeater {
                    model: childNodes;
                    delegate: delegateitem;
                }
            }
        }
        Component.onCompleted: {
            self.mRootItem.setExpanded(true);
            listmodel.append(self.mRootItem);
        }
    }

    Component {
        id: delegateitem;
        Column {
            Rectangle {
                id: itemrect;
                width: listview.width;
                height: itemrow.implicitHeight + itemHeightOverflow;
                color: XTreeItem.SF_NONE == selectionFlag ? backgroundNormal : backgroundCurrent;
                /* 获取当前节点 */
                function getItemById() {
                    var item = parentNode, paths = [id];
                    while (item) {
                        paths.splice(0, 0, item.id);
                        item = item.parentNode;
                    }
                    var children = [self.mRootItem];
                    for (var i = 0; i < paths.length; ++i) {
                        var bFound = false;
                        for (var j = 0; j < children.length; ++j) {
                            var child = children[j];
                            if (paths[i] === child.id) {
                                if (i == paths.length - 1) {
                                    return child;
                                } else {
                                    children = child.childNodes;
                                    bFound = true;
                                    break;
                                }
                            }
                        }
                        if (!bFound) {
                            return null;
                        }
                    }
                }
                /* 点击逻辑 */
                MouseArea {
                    anchors.fill: parent;
                    hoverEnabled: true;
                    onClicked: {
                        var item = itemrect.getItemById();
                        if (self.mCurrentItem) {
                            self.mCurrentItem.setSelectionFlag(XTreeItem.SF_NONE);
                        }
                        if (item) {
                            item.setSelectionFlag(XTreeItem.SF_CURRENT);
                        }
                    }
                    onDoubleClicked: {
                        if (childNodes.count > 0) {
                            var item = itemrect.getItemById();
                            item.setExpanded(!item.expanded);
                        } else {
                            mouse.accepted = false;
                        }
                    }
                }
                /* 显示项 */
                Row {
                    id: itemrow;
                    anchors.verticalCenter: itemrect.verticalCenter;
                    /* 缩进 */
                    Item {
                        width: getIndent();
                        height: parent.height;
                        function getIndent() {
                            var item = itemrect.getItemById();
                            return (item ? item.getLevel() - 1 : 0) * intentSpace;
                        }
                    }
                    /* 展开图标 */
                    MouseArea{
                        width: image_expand.width + 4;
                        height: image_expand.height + 4;
                        anchors.verticalCenter: itemrow.verticalCenter;
                        propagateComposedEvents: 0 === childNodes.count;
                        onClicked: {
                            if (childNodes.count > 0) {
                                var item = itemrect.getItemById();
                                item.setExpanded(!item.expanded);
                            } else {
                                mouse.accepted = false;
                            }
                        }
                        Image {
                            id: image_expand;
                            anchors.centerIn: parent;
                            source: expanded ? expandIcon : collapseIcon;
                            visible: childNodes.count > 0;
                        }
                    }
                    /* 节点图标 */
                    Image {
                        id: image_display;
                        anchors.verticalCenter: itemrow.verticalCenter;
                        source: displayIcon;
                    }
                    /* 节点文字 */
                    Text {
                        id: text_display;
                        anchors.verticalCenter: itemrow.verticalCenter;
                        text: displayText;
                        color: XTreeItem.SF_NONE == selectionFlag ? textColorNormal : textColorCurrent;
                        font: itemFont;
                    }
                }
            }
            /* 子节点 */
            Item {
                visible: expanded;
                width: repeaterSubNodes.implicitWidth;
                height: repeaterSubNodes.implicitHeight;
                Column {
                    id: repeaterSubNodes;
                    Repeater {
                        model: childNodes;
                        delegate: delegateitem;
                    }
                }
            }
        }
    }

    QtObject {
        id: self;
        property var mRootItem: new XTreeItem.XTreeItem("", "", null);
        property var mCurrentItem: null;

        onMCurrentItemChanged: {
            if ('function' === typeof(onCurrentItemChanged)) {
                onCurrentItemChanged();
            }
        }
    }

    /* 获取当前选中项 */
    function getCurrentItem() {
        return self.mCurrentItem;
    }

    /* 追加顶项 */
    function appendTopItem(icon, text, data) {
        var item = new XTreeItem.XTreeItem(icon, text, data);
        self.mRootItem.appendChild(item);
        if (1 === self.mRootItem.childrenCount()) {
            item.setSelectionFlag(XTreeItem.SF_CURRENT);
        }
        return item;
    }

    /* 追加子项 */
    function appendChildItem(parent, icon, text, data) {
        if (parent) {
            var item = new XTreeItem.XTreeItem(icon, text, data);
            parent.appendChild(item);
            return item;
        }
        return null;
    }

    /* 移除项 */
    function removeItem(item) {
        if (item && item.parentNode){
           item.parentNode.removeChild(item);
        }
    }

    /* 清除 */
    function clear() {
        while (self.mRootItem.childrenCount() > 0) {
            var item = self.mRootItem.childItemAt(0);
            if (item) {
                self.mRootItem.removeChild(item);
            }
        }
    }
}

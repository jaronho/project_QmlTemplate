import QtQuick 2.9

Item {
    property alias frameColor: frame.color;                         /* 输入框背景颜色 */
    property alias frameRadius: frame.radius;                       /* 输入框四个角弧度 */
    property color borderCorlorNormal: "#e3e9ef";                   /* 常态下边框颜色 */
    property color borderCorlorActive: "#c7e2f1";                   /* 激活时边框颜色 */
    property int borderWidth: 1;                                    /* 边框宽度 */
    property alias hintColor: hint.color;                           /* 提示文本颜色 */
    property alias hintOpacity: hint.opacity;                       /* 提示文本透明度 */
    property alias hintText: hint.text;                             /* 提示文本 */
    property alias inputReadOnly: input.readOnly;                   /* 是否只读 */
    property alias inputSelectByMouse: input.selectByMouse;         /* 是否可以选中 */
    property alias inputTextColor: input.color;                     /* 输入文本颜色 */
    property alias inputSelectionColor: input.selectionColor;       /* 选中区域点颜色 */
    property alias inputSelectedTextColor: input.selectedTextColor; /* 被选中点文本颜色 */
    property alias inputTextOpacity: input.opacity;                 /* 输入文本透明度 */
    property alias inputText: input.text;                           /* 输入文本 */
    property alias inputFontSize: input.font.pixelSize;             /* 输入框字体大小 */
    property var onInputTextEdited: null;                           /* 输入框编辑后的回调函数 */
    property var onInputEditingFinished: null;                      /* 输入按下返回键,回车键,失去焦点的回调函数 */
    property var onInputAccepted: null;                             /* 输入按下返回键,回车键的回调函数 */

    width: 100;
    height: 20;

    /* 私有属性 */
    QtObject {
        id: self;
        property bool isMouseHover;
        property int cursorShape;
    }

    /* 背景框 */
    Rectangle {
        id: frame;
        anchors.fill: parent;
        color: "#ffffff";
        border.color: (input.focus || self.isMouseHover) ? borderCorlorActive : borderCorlorNormal;
        border.width: borderWidth;
        radius: 4;
    }

    /* 鼠标事件 */
    MouseArea {
        anchors.fill: input;
        hoverEnabled: true;
        onEntered: {
            self.isMouseHover = true;
            if ('undefined' !== typeof(cursorShape)) {
                self.cursorShape = cursorShape;
                cursorShape = Qt.IBeamCursor;
            }
        }
        onExited: {
            self.isMouseHover = false;
            if ('undefined' !== typeof(cursorShape)) {
               cursorShape = self.cursorShape;
            }
        }
    }

    /* 提示 */
    Text {
        id: hint;
        anchors.fill: input;
        verticalAlignment: Text.AlignVCenter;
        font.pixelSize: input.font.pixelSize;
        visible: input.text.length > 0 ? false : true;
        color: "#7f7f7f";
        opacity: 0.65;
        text: "Enter words";
    }

    /* 输入框 */
    TextInput {
        id: input;
        anchors.left: parent.left;
        anchors.leftMargin: frame.radius > 2 ? frame.radius - 1 : 1;
        anchors.right: parent.right;
        anchors.rightMargin: anchors.leftMargin;
        height: parent.height;
        verticalAlignment: Text.AlignVCenter;
        clip: true;
        selectByMouse: true;
        color: "#000000";
        selectionColor: "#3399ff";
        selectedTextColor: "#ffffff";
        font.pixelSize: height * 0.55;
        onTextEdited: { /* 当文本被编辑后触发 */
            if ('function' === typeof(onInputTextEdited)) {
                onInputTextEdited();
            }
        }
        onEditingFinished: {    /* 当返回键,回车键被按下,或者失去焦点时触发 */
            if ('function' === typeof(onInputEditingFinished)) {
                onInputEditingFinished();
            }
        }
        onAccepted: {   /* 当返回键,回车键被按下时触发 */
            focus = false;
            if ('function' === typeof(onInputAccepted)) {
                onInputAccepted();
            }
        }
    }
}

/***********************************************************************
 ** Author:	jaron.ho
 ** Date:	2018-03-27
 ** Brief:  QML处理器
 ***********************************************************************/
import QtQuick 2.0
import "../script/jhsdk/Common.js" as Common
import "../script/jhsdk/Util.js" as Util

Item {
    /* QML定时器 */
    Timer {
        interval: 5;
        repeat: true;
        running: true;
        onTriggered: {
            Util.listen();
        }
    }

    /* 私有成员 */
    QtObject {
        id: self;
    }

    /***********************************************************************
     ******************************* 公共接口 *******************************
     ***********************************************************************/

    /* 处理初始成功 */
    function handleInitOk() {
    }
}

/**********************************************************************
* Author:	jaron.ho
* Date:		2017-09-12
* Brief:	控制器,负责向QML派发消息
**********************************************************************/
#include "Control.h"
#include <QDebug>

Control* Control::getInstance(void) {
    static Control* instance = nullptr;
    if (nullptr == instance) {
        instance = new Control();
    }
    return instance;
}

void Control::init(void) {
}

void Control::onLogRecord(QString str) {
}

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

void Control::setWindow(QQuickWindow* win) {
    mWin = win;
}

void Control::notifyInitOk(void) {
    emit sigInitOk();
}

void Control::onSetCursor(int cursor) {
    if (mWin && cursor >= 0 && cursor <= Qt::LastCursor) {
        mWin->setCursor(QCursor((Qt::CursorShape)cursor));
    }
}

void Control::onLogRecord(QString str) {
}

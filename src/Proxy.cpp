/**********************************************************************
* Author:	jaron.ho
* Date:		2017-09-12
* Brief:	代理器,负责C++与QML的交互
**********************************************************************/
#include "Proxy.h"
#include <QDebug>

Proxy* Proxy::getInstance(void) {
    static Proxy* instance = nullptr;
    if (nullptr == instance) {
        instance = new Proxy();
    }
    return instance;
}

void Proxy::init(void) {
}

void Proxy::notifyInitOk(void) {
    emit sigInitOk();
}

void Proxy::onLogRecord(QString str) {
}

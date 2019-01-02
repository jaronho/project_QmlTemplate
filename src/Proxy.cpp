/**********************************************************************
* Author:	jaron.ho
* Date:		2017-09-12
* Brief:	代理器,负责C++与QML的交互
**********************************************************************/
#include "Proxy.h"
#include <QByteArray>
#include <QCryptographicHash>
#include <QDebug>
#include "jhsdk/Global.h"

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

QString Proxy::getMachineCode(void) {
    static std::string sMachineCode;
    if (sMachineCode.empty()) {
        /* 拼接所有网卡点MAC地址 */
        std::string macs = "";
        std::vector<network_dev_st> networkDevList = devGetNetwork();
        for (size_t i = 0; i < networkDevList.size(); ++i) {
            if (0 == strcmp("lo", networkDevList[i].name)) {
                continue;
            }
            if (macs.length() > 0) {
                macs += "|";
            }
            macs += networkDevList[i].mac;
        }
        /* 计算MD5值 */
        QByteArray md5 = QCryptographicHash::hash(macs.c_str(), QCryptographicHash::Md5);
        sMachineCode = md5.toHex().data();
    }
    return sMachineCode.c_str();
}

void Proxy::log(const QString& str) {
    logRecord(str.toStdString());
}

void Proxy::err(const QString& str) {
    errRecord(str.toStdString());
}

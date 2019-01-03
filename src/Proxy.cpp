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
    return md5.toHex().data();
}

QString Proxy::getIPv4(void) {
    std::vector<network_dev_st> networkDevList = devGetNetwork();
    for (size_t i = 0; i < networkDevList.size(); ++i) {
        if (0 == strcmp("lo", networkDevList[i].name)) {
            continue;
        }
        return networkDevList[i].ipv4;
    }
    return "";
}

int Proxy::getCpuOccupy(void) {
    return 0;
}

int Proxy::getMemoryOccupy(void) {
    memory_dev_st memDev = devGetMemory();
    float occupy = (float)(memDev.total - memDev.available) / memDev.total;
    return (int)((occupy * 100) + 0.5);
}

int Proxy::getDiskOccupy(void) {
    return 0;
}

void Proxy::log(const QString& str) {
    logRecord(str.toStdString());
}

void Proxy::err(const QString& str) {
    errRecord(str.toStdString());
}

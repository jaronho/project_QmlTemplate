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

bool Proxy::callQml(QString objectName, QString methodName, QVariant* retValue,
                    QVariant val0, QVariant val1,
                    QVariant val2, QVariant val3,
                    QVariant val4, QVariant val5,
                    QVariant val6, QVariant val7,
                    QVariant val8, QVariant val9) {
    if (QGuiApplication::allWindows().isEmpty()) {
        return false;
    }
    QObject* obj = QGuiApplication::allWindows()[0]->findChild<QObject*>(objectName, Qt::FindChildrenRecursively);
    if (!obj) {
        return false;
    }
    return QMetaObject::invokeMethod(obj, methodName.toUtf8(), Qt::AutoConnection,
                                     retValue ? Q_RETURN_ARG(QVariant, *retValue) : QGenericReturnArgument(),
                                     val0.isValid() ? Q_ARG(QVariant, val0) : QGenericArgument(),
                                     val1.isValid() ? Q_ARG(QVariant, val1) : QGenericArgument(),
                                     val2.isValid() ? Q_ARG(QVariant, val2) : QGenericArgument(),
                                     val3.isValid() ? Q_ARG(QVariant, val3) : QGenericArgument(),
                                     val4.isValid() ? Q_ARG(QVariant, val4) : QGenericArgument(),
                                     val5.isValid() ? Q_ARG(QVariant, val5) : QGenericArgument(),
                                     val6.isValid() ? Q_ARG(QVariant, val6) : QGenericArgument(),
                                     val7.isValid() ? Q_ARG(QVariant, val7) : QGenericArgument(),
                                     val8.isValid() ? Q_ARG(QVariant, val8) : QGenericArgument(),
                                     val9.isValid() ? Q_ARG(QVariant, val9) : QGenericArgument());
}

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

float Proxy::getCpuOccupy(void) {
    cpu_dev_st cpuDev1 = devGetCPU();
    sleep(1);
    cpu_dev_st cpuDev2 = devGetCPU();
    unsigned long t1 = cpuDev1.user + cpuDev1.nice + cpuDev1.system + cpuDev1.idle + cpuDev1.iowait + cpuDev1.irq + cpuDev1.softirq;
    unsigned long t2 = cpuDev2.user + cpuDev2.nice + cpuDev2.system + cpuDev2.idle + cpuDev2.iowait + cpuDev2.irq + cpuDev2.softirq;
    unsigned long total = t2 - t1;
    unsigned long idle = cpuDev2.idle - cpuDev1.idle;
    float occupy = (float)(total - idle) / total;
    return occupy * 100;
}

float Proxy::getMemoryOccupy(void) {
    memory_dev_st memDev = devGetMemory();
    float occupy = (float)(memDev.total - memDev.available) / memDev.total;
    return occupy * 100;
}

float Proxy::getDiskOccupy(void) {
    disk_dev_st diskDev = devGetDisk("/");
    float occupy = (float)(diskDev.total - diskDev.available) / diskDev.total;
    return occupy * 100;
}

void Proxy::log(const QString& str) {
    logRecord(str.toStdString());
}

void Proxy::err(const QString& str) {
    errRecord(str.toStdString());
}

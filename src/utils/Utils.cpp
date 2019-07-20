/**********************************************************************
 * Author:	jaron.ho
 * Date:    2019-07-20
 * Brief:	工具类
 **********************************************************************/
#include "Utils.h"
#include <QGuiApplication>
#include <QQuickWindow>
#include <QTime>
/*********************************************************************/
bool Tools::isDigitString(const QString& src) {
    const char* s = src.toUtf8().data();
    while (*s && *s >= '0' && * s<= '9') {
        s++;
    }
    return !bool(*s);
}
/*********************************************************************/
bool Tools::callQml(QString objectName, QString methodName, QVariant* retValue,
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
/*********************************************************************/
void Tools::sleep(int msec) {
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
    }
}
/*********************************************************************/
QString Tools::hamcSha1(QByteArray key, QByteArray baseString) {
    int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard
    if (key.length() > blockSize) { // if key is longer than block size (64), reduce key length with SHA-1 compression
        key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
    }
    QByteArray innerPadding(blockSize, char(0x36)); // initialize inner padding with char"6"
    QByteArray outerPadding(blockSize, char(0x5c)); // initialize outer padding with char"/"
    // ascii characters 0x36 ("6") and 0x5c ("/") are selected because they have large
    // Hamming distance (http://en.wikipedia.org/wiki/Hamming_distance)
    for (int i = 0; i < key.length(); i++) {
        innerPadding[i] = innerPadding[i] ^ key.at(i); // XOR operation between every byte in key and innerpadding, of key length
        outerPadding[i] = outerPadding[i] ^ key.at(i); // XOR operation between every byte in key and outerpadding, of key length
    }
    // result = hash ( outerPadding CONCAT hash ( innerPadding CONCAT baseString ) ).toBase64
    QByteArray total = outerPadding;
    QByteArray part = innerPadding;
    part.append(baseString);
    total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
    QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
    return hashed.toBase64();
}
/*********************************************************************/

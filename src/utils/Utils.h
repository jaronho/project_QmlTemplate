/**********************************************************************
 * Author:	jaron.ho
 * Date:    2019-07-20
 * Brief:	工具类
 **********************************************************************/
#ifndef _UTILS_H_
#define _UTILS_H_

#include <QByteArray>
#include <QCryptographicHash>
#include <QString>
#include <QVariant>

class Utils {
public:
    /* 是否数字字符串 */
    static bool isDigitString(const QString& src);

    /* 调用QML函数接口 */
    static bool callQml(QString objectName, QString methodName, QVariant* retValue,
                        QVariant val0 = QVariant(), QVariant val1 = QVariant(),
                        QVariant val2 = QVariant(), QVariant val3 = QVariant(),
                        QVariant val4 = QVariant(), QVariant val5 = QVariant(),
                        QVariant val6 = QVariant(), QVariant val7 = QVariant(),
                        QVariant val8 = QVariant(), QVariant val9 = QVariant());

    /* 延迟等待(毫秒,在主线程中调用,不会阻塞主线程事件) */
    static void sleep(int msec);

    /* HAMC-SHA1加密算法 */
    static QString hamcSha1(QByteArray key, QByteArray baseString);
};

#endif	/* _UTILS_H_ */

/**********************************************************************
* Author:	jaron.ho
* Date:		2017-09-12
* Brief:	代理器,负责C++与QML的交互
**********************************************************************/
#ifndef _PROXY_H_
#define _PROXY_H_

#include <QGuiApplication>
#include <QObject>
#include <QQuickWindow>
#include <QString>
#include <QVariant>

class Proxy : public QObject {
    Q_OBJECT

private:
    /*
     * Brief:   单例模式,不允许外部实例化
     * Param:   void
     * Return:  void
     */
    Proxy(void) {}

public:
    /*
     * Brief:   调用QML函数接口
     * Param:   objectName - qml对象名
     *          methodName - 函数名
     *          retValue - 返回值(可为空指针)
     *          val0,val9 - 传入参数(最多支持9个参数)
     * Return:  bool
     */
    static bool callQml(QString objectName, QString methodName, QVariant* retValue,
                        QVariant val0 = QVariant(), QVariant val1 = QVariant(),
                        QVariant val2 = QVariant(), QVariant val3 = QVariant(),
                        QVariant val4 = QVariant(), QVariant val5 = QVariant(),
                        QVariant val6 = QVariant(), QVariant val7 = QVariant(),
                        QVariant val8 = QVariant(), QVariant val9 = QVariant());

    /*
     * Brief:   单例
     * Param:   void
     * Return:  Proxy*
     */
    static Proxy* getInstance(void);
    
public:
    /* 初始化 */
    void init(void);

    /* 通知初始成功 */
    void notifyInitOk(void);

signals:
    /*
     * Brief:   初始成功
     * Param:   void
     * Return:  void
     */
    void sigInitOk(void);

public slots:
    /* 获取机器码 */
    static QString getMachineCode(void);

    /* 获取IPv4地址 */
    static QString getIPv4(void);

    /* 获取CPU使用率 */
    static float getCpuOccupy(void);

    /* 获取内存使用率 */
    static float getMemoryOccupy(void);

    /* 获取磁盘使用率 */
    static float getDiskOccupy(void);

    /* 日志记录 */
    static void log(const QString& str);

    /* 错误记录 */
    static void err(const QString& str);
};

#endif // _PROXY_H_

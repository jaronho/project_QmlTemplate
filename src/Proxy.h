/**********************************************************************
* Author:	jaron.ho
* Date:		2017-09-12
* Brief:	代理器,负责C++与QML的交互
**********************************************************************/
#ifndef _PROXY_H_
#define _PROXY_H_

#include <QObject>
#include <QQuickWindow>

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
    static int getCpuOccupy(void);

    /* 获取内存使用率 */
    static int getMemoryOccupy(void);

    /* 获取磁盘使用率 */
    static int getDiskOccupy(void);

    /* 日志记录 */
    static void log(const QString& str);

    /* 错误记录 */
    static void err(const QString& str);
};

#endif // _PROXY_H_

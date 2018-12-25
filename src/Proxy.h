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
    /* 日志记录 */
    void onLogRecord(QString str);
};

#endif // _PROXY_H_

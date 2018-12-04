/**********************************************************************
* Author:	jaron.ho
* Date:		2017-09-12
* Brief:	控制器,负责向QML派发消息
**********************************************************************/
#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <QObject>
#include <QQuickWindow>

class Control : public QObject {
    Q_OBJECT

private:
    /*
     * Brief:   单例模式,不允许外部实例化
     * Param:   void
     * Return:  void
     */
    Control(void) : mWin(nullptr) {}

public:
    /*
     * Brief:   单例
     * Param:   void
     * Return:  Control*
     */
    static Control* getInstance(void);

public:
    /* 初始化 */
    void init(void);

    /* 设置窗体 */
    void setWindow(QQuickWindow* win);

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
    /* 设置鼠标 */
    void onSetCursor(int cursor);

    /* 日志记录 */
    void onLogRecord(QString str);

private:
    QQuickWindow* mWin;
};

#endif // _CONTROL_H_

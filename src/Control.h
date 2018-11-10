/**********************************************************************
* Author:	jaron.ho
* Date:		2017-09-12
* Brief:	控制器,负责向QML派发消息
**********************************************************************/
#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <QObject>
#include <time.h>

class Control : public QObject {
    Q_OBJECT

private:
    /*
     * Brief:   单例模式,不允许外部实例化
     * Param:   void
     * Return:  void
     */
    Control(void) {}

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

signals:
    /*
     * Brief:   初始化结束
     * Param:   void
     * Return:  void
     */
    void sigInit(void);

public slots:
    /* 日志记录 */
    void onLogRecord(QString str);

};

#endif // _CONTROL_H_

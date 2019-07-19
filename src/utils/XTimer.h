/**********************************************************************
 * Author:	jaron.ho
 * Date:    2019-07-19
 * Brief:	扩展定时器
 **********************************************************************/
#ifndef XTIMER_H
#define XTIMER_H

#include <functional>
#include <QTimer>

/* 定时器触发回调 */
#define XTIMER_TIMEOUT_CALLBACK std::function<void(XTimer* timer)>

/*
 * Brief:   扩展定时器
 */
class XTimer : public QTimer {
    Q_OBJECT

public:
    /* 构造函数 */
    XTimer(QObject* parent = nullptr);

    /* 连接触发回调 */
    QMetaObject::Connection connectTimeout(const QObject* receiver, XTIMER_TIMEOUT_CALLBACK callback, Qt::ConnectionType type = Qt::AutoConnection);

private slots:
    void onTimeout(void);

private:
    XTIMER_TIMEOUT_CALLBACK mTimeoutCallback;       /* 定时器触发回调 */
};

/* 定时动作结束回调 */
#define XTIMER_FINISH_CALLBACK std::function<void(const XTimerAction* act)>

/*
 * Brief:   定时动作(主线程调用),需要实现子类
 */
class XTimerAction : public QObject {
    Q_OBJECT

public:
     /*
     * Brief:	构造函数(需要在主线程中循环调用)
     * Param:	msec - 定时间隔(毫秒)
     *          count - 定时次数(0.无限次,>0.有限次)
     * Return:	void
     */
    XTimerAction(int msec, unsigned long count = 0, QObject* parent = nullptr);

    /*
     * Brief:	运行定时动作
     * Param:	autoDestroy - 定时动作结束时是否自动销毁
     * Return:	bool
     */
    bool run(bool autoDestroy = false);

    /*
     * Brief:	结束定时动作(视情况手动调用,一般通过onProcess的返回值自动处理)
     * Param:	void
     * Return:	bool
     */
    bool finish(void);

protected:
    /*
     * Brief:	定时开始函数(需要在子类实现)
     * Param:	void
     * Return:	void
     */
    virtual void onStart(void) = 0;

    /*
     * Brief:	定时触发函数(需要在子类实现)
     * Param:	void
     * Return:	bool,返回true将结束定时动作,返回false将继续定时动作
     */
    virtual bool onProcess(void) = 0;

    /*
     * Brief:	定时结束函数(需要在子类实现)
     * Param:	void
     * Return:	void
     */
    virtual void onFinish(void) = 0;

private slots:
    void onTimeout(void);

private:
    QTimer* mTimer;                         /* 定时器 */
    unsigned long mTotalCount;              /* 定时总次数 */
    unsigned long mTimeoutCount;            /* 当前次数 */
    bool mAutoDestroy;                      /* 是否自动销毁 */
};

#endif /* XTIMER_H */

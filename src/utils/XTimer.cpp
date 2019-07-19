/**********************************************************************
 * Author:	jaron.ho
 * Date:    2019-07-19
 * Brief:	扩展定时器
 **********************************************************************/
#include "XTimer.h"

XTimer::XTimer(QObject* parent) : QTimer (parent) {}

QMetaObject::Connection XTimer::connectTimeout(const QObject* receiver, XTIMER_TIMEOUT_CALLBACK callback, Qt::ConnectionType type) {
    mTimeoutCallback = callback;
    return connect(this, SIGNAL(timeout()), receiver, SLOT(onTimeout()), type);
}

void XTimer::onTimeout(void) {
    if (mTimeoutCallback) {
        mTimeoutCallback(this);
    }
}

XTimerAction::XTimerAction(int msec, unsigned long count, QObject* parent) : QObject(parent) {
    mTimer = new QTimer(this);
    mTimer->setInterval(msec);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    mTotalCount = count;
    mTimeoutCount = 0;
    mAutoDestroy = false;
}

bool XTimerAction::run(bool autoDestroy) {
    if (mTimer && !mTimer->isActive()) {
        mAutoDestroy = autoDestroy;
        mTimer->start();
        onStart();
        return true;
    }
    return false;
}

bool XTimerAction::finish(void) {
    if (mTimer && mTimer->isActive()) {
        mTimer->stop();
        mTimeoutCount = 0;
        onFinish();
        if (mAutoDestroy) {
            delete this;    /* 自动销毁,一般不推荐此用法 */
        }
        return true;
    }
    return false;
}

void XTimerAction::onTimeout(void) {
    ++mTimeoutCount;
    if (onProcess() || (mTotalCount > 0 && mTimeoutCount >= mTotalCount)) {
        finish();
    }
}

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

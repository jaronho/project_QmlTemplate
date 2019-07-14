#ifndef XTIMER_H
#define XTIMER_H

#include <functional>
#include <QTimer>

#define XTIMER_TIMEOUT_CALLBACK std::function<void(XTimer* timer)>

class XTimer : public QTimer {
public:
    /* 构造函数 */
    XTimer(QObject* parent = nullptr);

    /* 连接触发回调 */
    QMetaObject::Connection connectTimeout(const QObject* receiver, XTIMER_TIMEOUT_CALLBACK callback, Qt::ConnectionType type = Qt::AutoConnection);

private:
    void onTimeout(void);

private:
    XTIMER_TIMEOUT_CALLBACK mTimeoutCallback;       /* 定时器触发回调 */
};

#endif /* XTIMER_H */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include "Control.h"

/* 窗体样式类型 */
static const int WINFLAGS_AJUSTSIZE = 0;    /* 窗体可调大小 */
static const int WINFLAGS_FIXEDSIZE = 1;    /* 窗体固定大小 */
static const int WINFLAGS_FRAMELESS = 2;    /* 窗体没有边框 */

/* 宏定义 */
#define WINDOW_FLAGS    WINFLAGS_FIXEDSIZE  /* 窗体样式 */

/* 主函数 */
int main(int argc, char *argv[]) {
    Control::getInstance()->init();
    /* step1:初始Qt程序*/
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("control", Control::getInstance());
    /* step2:加载QML界面 */
    engine.load(QUrl(QStringLiteral("qrc:/qml/UIRoot.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    /* step3:设置Qt窗体 */
    QQuickWindow* window = qobject_cast<QQuickWindow*>(engine.rootObjects().value(0));
#if WINFLAGS_FIXEDSIZE == WINDOW_FLAGS
    window->setFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
#elif WINFLAGS_FRAMELESS == WINDOW_FLAGS
    window->setFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
    window->show();
    Control::getInstance()->setWindow(window);
    /* step4:通知初始成功 */
    Control::getInstance()->notifyInitOk();
    /* step5:进入主循环 */
    return app.exec();
}

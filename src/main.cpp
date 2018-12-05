#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include "Control.h"

/* 主函数 */
int main(int argc, char *argv[]) {
    Control::getInstance()->init();
    /* step1:初始Qt程序*/
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
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
    window->show();
    Control::getInstance()->setWindow(window);
    /* step4:通知初始成功 */
    Control::getInstance()->notifyInitOk();
    /* step5:进入主循环 */
    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include "Control.h"

int main(int argc, char *argv[]) {
    Control::getInstance()->init();
    /* step1:Qt初始化*/
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
    /* step3:设置窗体 */
    QQuickWindow* window = qobject_cast<QQuickWindow*>(engine.rootObjects().value(0));
    Qt::WindowFlags flag = Qt::MSWindowsFixedSizeDialogHint | Qt::WindowCloseButtonHint;
    window->setFlags(flag);
    window->show();
    /* step4:进入主循环 */
    return app.exec();
}

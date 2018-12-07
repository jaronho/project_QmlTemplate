#include <QApplication>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickWidget>
#include "XResizeWindow.h"
#include "Control.h"
#include <QQuickWindow>

/* 主函数 */
int main(int argc, char *argv[]) {
    Control::getInstance()->init();
    /* step1:初始Qt程序*/
#if defined(Q_OS_WIN)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QApplication app(argc, argv);
    /* step2:初始窗口 */
    XResizeWindow window(QSize(640, 480), QSize(320, 240), QSize(800, 600), true);
    window.setFlag(Qt::Window, true);
//    window.setFlag(Qt::FramelessWindowHint, true);
    window.setContextProperty("control", Control::getInstance());
    window.setSource(QUrl(QStringLiteral("qrc:/qml/Root.qml")));
    window.show();
    /* step3:通知初始成功 */
    Control::getInstance()->notifyInitOk();
    /* step4:进入主循环 */
    return app.exec();
}

#include <QApplication>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickWidget>
#include "jhsdk/Global.h"
#include "XResizeWindow.h"
#include "Control.h"

/* 主函数 */
int main(int argc, char* argv[]) {
    /* step1:初始化数据,逻辑模块*/
    initAppDirectory(argv[0]);
    Control::getInstance()->init();
    /* step2:初始Qt程序*/
#if defined(Q_OS_WIN)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QApplication app(argc, argv);
    /* step3:初始Qt窗口 */
    XResizeWindow window(QSize(640, 480), QSize(320, 240), QSize(800, 600), true);
    window.setFlag(Qt::Window, true);
//    window.setFlag(Qt::FramelessWindowHint, true);
    window.setContextProperty("control", Control::getInstance());
    window.setSource(QUrl(QStringLiteral("qrc:/qml/Root.qml")));
    window.show();
    /* step4:通知初始化成功 */
    Control::getInstance()->notifyInitOk();
    /* step5:进入Qt主循环 */
    return app.exec();
}

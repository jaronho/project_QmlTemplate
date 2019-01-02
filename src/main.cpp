#include <QApplication>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickWidget>
#include "jhsdk/Global.h"
#include "XResizeWindow.h"
#include "Proxy.h"

int main(int argc, char* argv[]) {
    initAppDirectory(argv[0]);
    logRecord("######################################################################");
    logRecord("#############################  Starting  #############################");
    logRecord("######################################################################");
    logRecord("Machine Code: " + Proxy::getMachineCode().toStdString());
    /* step1:初始化模块*/
    Proxy::getInstance()->init();
    /* step2:初始化Qt程序*/
    // qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));   /* 集成虚拟键盘 */
#if defined(Q_OS_WIN)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QGuiApplication app(argc, argv);
    /* step3:初始化Qt窗口 */
    XResizeWindow window(QSize(640, 480), QSize(320, 240), QSize(800, 600), false);
    window.setFlag(Qt::Window, true);
    // window.setFlag(Qt::FramelessWindowHint, true);
    window.setContextProperty("app_directory", getAppDirectory().c_str());
    window.setContextProperty("proxy", Proxy::getInstance());
    window.setSource(QUrl(QStringLiteral("qrc:/qml/Root.qml")));
    window.show();
    /* step4:通知初始化成功 */
    Proxy::getInstance()->notifyInitOk();
    /* step5:进入Qt主循环 */
    return app.exec();
}

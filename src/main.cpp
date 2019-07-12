#include <iostream>
#include <QApplication>
#include <QMutex>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickWidget>
#include "jhsdk/Global.h"
#include "utils/XWindow.h"
#include "Proxy.h"

/* 输出日志信息 */
static void outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    QDateTime dt = QDateTime::currentDateTime();
    QString message = QString("[%1] %2").arg(dt.toString("yyyy-MM-dd hh:mm:ss")).arg(msg);
    std::cout << message.toStdString() << std::endl;
    /* 日志文件名 */
    char filename[16] = { 0 };
    sprintf(filename, "%04d%02d%02d.log", dt.date().year(), dt.date().month(), dt.date().day());
    /* 写日志 */
    static QMutex sMutex;
    static QFile sFile;
    sMutex.lock();
    QString fullFilePath = QCoreApplication::applicationDirPath() + "/" + filename; /* 日志全路径 */
    if (sFile.fileName() != fullFilePath) {
        if (sFile.isOpen()) {
            sFile.close();
        }
        sFile.setFileName(fullFilePath);
        sFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Append);
    }
    if (sFile.isOpen()) {
        QTextStream fileStream(&sFile);
        fileStream.setCodec("UTF-8");
        fileStream << message << "\n";
        sFile.flush();
    }
    sMutex.unlock();
}

int main(int argc, char* argv[]) {
    // initAppDirectory(argv[0]);
    // logRecord("######################################################################");
    // logRecord("#############################  Starting  #############################");
    // logRecord("######################################################################");
    // logRecord("Machine Code: " + Proxy::getMachineCode().toStdString());
    // logRecord("IPv4 Address: " + Proxy::getIPv4().toStdString());
    /* step1:初始化Qt程序*/
    // qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));   /* 集成虚拟键盘 */
    qInstallMessageHandler(outputMessage);
#if defined(Q_OS_WIN)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QGuiApplication app(argc, argv);
    /* step2:初始化模块*/
    Proxy::getInstance()->init();
    /* step3:初始化Qt窗口 */
    XWindow window(QSize(640, 480), QSize(320, 240), QSize(800, 600), false);
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

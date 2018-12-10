QT += quickwidgets
CONFIG += c++11

# Unix平台
unix {
    if (contains(CONFIG, ARM)) { # ARM架构
        message("platform - unix(arm)")
    } else { # x86架构
        message("platform - unix(x86)")
        HEADERS += \
            src/jhsdk/libevent/platform-linux/include/event2/buffer.h \
            src/jhsdk/libevent/platform-linux/include/event2/buffer_compat.h \
            src/jhsdk/libevent/platform-linux/include/event2/bufferevent.h \
            src/jhsdk/libevent/platform-linux/include/event2/bufferevent_compat.h \
            src/jhsdk/libevent/platform-linux/include/event2/bufferevent_ssl.h \
            src/jhsdk/libevent/platform-linux/include/event2/bufferevent_struct.h \
            src/jhsdk/libevent/platform-linux/include/event2/dns.h \
            src/jhsdk/libevent/platform-linux/include/event2/dns_compat.h \
            src/jhsdk/libevent/platform-linux/include/event2/dns_struct.h \
            src/jhsdk/libevent/platform-linux/include/event2/event.h \
            src/jhsdk/libevent/platform-linux/include/event2/event_compat.h \
            src/jhsdk/libevent/platform-linux/include/event2/event-config.h \
            src/jhsdk/libevent/platform-linux/include/event2/event_struct.h \
            src/jhsdk/libevent/platform-linux/include/event2/http.h \
            src/jhsdk/libevent/platform-linux/include/event2/http_compat.h \
            src/jhsdk/libevent/platform-linux/include/event2/http_struct.h \
            src/jhsdk/libevent/platform-linux/include/event2/keyvalq_struct.h \
            src/jhsdk/libevent/platform-linux/include/event2/listener.h \
            src/jhsdk/libevent/platform-linux/include/event2/rpc.h \
            src/jhsdk/libevent/platform-linux/include/event2/rpc_compat.h \
            src/jhsdk/libevent/platform-linux/include/event2/rpc_struct.h \
            src/jhsdk/libevent/platform-linux/include/event2/tag.h \
            src/jhsdk/libevent/platform-linux/include/event2/tag_compat.h \
            src/jhsdk/libevent/platform-linux/include/event2/thread.h \
            src/jhsdk/libevent/platform-linux/include/event2/util.h \
            src/jhsdk/libevent/platform-linux/include/event2/visibility.h \
            src/jhsdk/libevent/platform-linux/include/evdns.h \
            src/jhsdk/libevent/platform-linux/include/event.h \
            src/jhsdk/libevent/platform-linux/include/evhttp.h \
            src/jhsdk/libevent/platform-linux/include/evrpc.h \
            src/jhsdk/libevent/platform-linux/include/evutil.h
        LIBS += $$PWD/src/jhsdk/libevent/platform-linux/libevent.a
        LIBS += $$PWD/src/jhsdk/libevent/platform-linux/libevent_core.a
        LIBS += $$PWD/src/jhsdk/libevent/platform-linux/libevent_extra.a
        LIBS += $$PWD/src/jhsdk/libevent/platform-linux/libevent_pthreads.a
    }
}
# Windows平台
win32 {
    message("platform - win32")
    HEADERS += \
        src/jhsdk/libevent/platform-win32/include/event2/buffer.h \
        src/jhsdk/libevent/platform-win32/include/event2/buffer_compat.h \
        src/jhsdk/libevent/platform-win32/include/event2/bufferevent.h \
        src/jhsdk/libevent/platform-win32/include/event2/bufferevent_compat.h \
        src/jhsdk/libevent/platform-win32/include/event2/bufferevent_ssl.h \
        src/jhsdk/libevent/platform-win32/include/event2/bufferevent_struct.h \
        src/jhsdk/libevent/platform-win32/include/event2/dns.h \
        src/jhsdk/libevent/platform-win32/include/event2/dns_compat.h \
        src/jhsdk/libevent/platform-win32/include/event2/dns_struct.h \
        src/jhsdk/libevent/platform-win32/include/event2/event.h \
        src/jhsdk/libevent/platform-win32/include/event2/event_compat.h \
        src/jhsdk/libevent/platform-win32/include/event2/event-config.h \
        src/jhsdk/libevent/platform-win32/include/event2/event_struct.h \
        src/jhsdk/libevent/platform-win32/include/event2/http.h \
        src/jhsdk/libevent/platform-win32/include/event2/http_compat.h \
        src/jhsdk/libevent/platform-win32/include/event2/http_struct.h \
        src/jhsdk/libevent/platform-win32/include/event2/keyvalq_struct.h \
        src/jhsdk/libevent/platform-win32/include/event2/listener.h \
        src/jhsdk/libevent/platform-win32/include/event2/rpc.h \
        src/jhsdk/libevent/platform-win32/include/event2/rpc_compat.h \
        src/jhsdk/libevent/platform-win32/include/event2/rpc_struct.h \
        src/jhsdk/libevent/platform-win32/include/event2/tag.h \
        src/jhsdk/libevent/platform-win32/include/event2/tag_compat.h \
        src/jhsdk/libevent/platform-win32/include/event2/thread.h \
        src/jhsdk/libevent/platform-win32/include/event2/util.h \
        src/jhsdk/libevent/platform-win32/include/event2/visibility.h \
        src/jhsdk/libevent/platform-win32/include/evdns.h \
        src/jhsdk/libevent/platform-win32/include/event.h \
        src/jhsdk/libevent/platform-win32/include/evhttp.h \
        src/jhsdk/libevent/platform-win32/include/evrpc.h \
        src/jhsdk/libevent/platform-win32/include/evutil.h
    LIBS += $$PWD/src/jhsdk/libevent/platform-win32/libevent.lib
    LIBS += $$PWD/src/jhsdk/libevent/platform-win32/libevent_core.lib
    LIBS += $$PWD/src/jhsdk/libevent/platform-win32/libevent_extras.lib
    LIBS += $$PWD/src/jhsdk/libevent/platform-win32/ws2_32.Lib
    LIBS += $$PWD/src/jhsdk/libevent/platform-win32/wsock32.Lib
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    src/jhsdk/common/Common.h \
    src/jhsdk/httpserver/HttpServer.h \
    src/jhsdk/httpserver/MultipartFormData.h \
    src/jhsdk/inifile/IniFile.h \
    src/jhsdk/logfile/logfile.h \
    src/jhsdk/logfile/logfilewrapper.h \
    src/jhsdk/pugixml/pugiconfig.hpp \
    src/jhsdk/pugixml/pugixml.hpp \
    src/jhsdk/shareprefs/SharePrefs.h \
    src/jhsdk/xmlhelper/XmlHelper.h \
    src/XResizeWindow.h \
    src/Control.h

SOURCES += \
    src/jhsdk/common/Common.cpp \
    src/jhsdk/httpserver/HttpServer.cpp \
    src/jhsdk/httpserver/MultipartFormData.cpp \
    src/jhsdk/inifile/IniFile.cpp \
    src/jhsdk/logfile/logfile.c \
    src/jhsdk/logfile/logfilewrapper.c \
    src/jhsdk/pugixml/pugixml.cpp \
    src/jhsdk/shareprefs/SharePrefs.cpp \
    src/jhsdk/xmlhelper/XmlHelper.cpp \
    src/XResizeWindow.cpp \
    src/Control.cpp \
    src/main.cpp

RESOURCES += \
    script.qrc \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

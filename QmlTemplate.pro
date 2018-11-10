QT += quick
CONFIG += c++11

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
    src/jhsdk/logfile/logfile.h \
    src/jhsdk/logfile/logfilewrapper.h \
    src/jhsdk/pugixml/pugiconfig.hpp \
    src/jhsdk/pugixml/pugixml.hpp \
    src/jhsdk/shareprefs/SharePrefs.h \
    src/jhsdk/xmlhelper/XmlHelper.h \
    src/Control.h

SOURCES += \
    src/jhsdk/common/Common.cpp \
    src/jhsdk/logfile/logfile.c \
    src/jhsdk/logfile/logfilewrapper.c \
    src/jhsdk/pugixml/pugixml.cpp \
    src/jhsdk/shareprefs/SharePrefs.cpp \
    src/jhsdk/xmlhelper/XmlHelper.cpp \
    src/main.cpp \
    src/Control.cpp

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

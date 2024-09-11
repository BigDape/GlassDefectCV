QT += gui core

TEMPLATE = lib
DEFINES += ALGORITHM_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algorithm.cpp \
    processdetect.cpp \
    processtile.cpp

HEADERS += \
    algorithm_global.h \
    algorithm.h \
    processdetect.h \
    processtile.h


#添加Halcon22.05库
INCLUDEPATH += $$PWD/HalconLib/include/
INCLUDEPATH += $$PWD/HalconLib/include/halconcpp
INCLUDEPATH += $$PWD/HalconLib/include/hdevengine

LIBS += -L$$PWD/HalconLib/lib/ -lhalconxl
LIBS += -L$$PWD/HalconLib/lib/ -lhalconcppxl
LIBS += -L$$PWD/HalconLib/lib/ -lhdevenginecppxl


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

# 添加公用工具库
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../hstool/release/ -lhstool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../hstool/debug/ -lhstool

INCLUDEPATH += $$PWD/../hstool
DEPENDPATH += $$PWD/../hstool

# 添加jsoncpp模块
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../jsoncpp/release/ -ljsoncpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../jsoncpp/debug/ -ljsoncpp

INCLUDEPATH += $$PWD/../jsoncpp
DEPENDPATH += $$PWD/../jsoncpp

QT +=core gui network xml widgets

TEMPLATE = lib
DEFINES += CAMERA_LIBRARY

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
    Dushen/DushenBasicFunc.cpp \
    mosaickimage.cpp
    camera.cpp\

HEADERS += \
    Dushen/DushenBasicFunc.h \  
    Dushen/DVPCamera.h \
    camera_global.h \
    camera.h \
    mosaickimage.h

#度申相机SDK
message("Windows x86_64 build")
LIBS += -L$$PWD/lib_x86_64/ -lDVPCamera64
INCLUDEPATH += $$PWD/lib_x86_64
DEPENDPATH += $$PWD/lib_x86_64

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


#添加Halcon22.05库
INCLUDEPATH += $$PWD/../algorithm/HalconLib/include/
INCLUDEPATH += $$PWD/../algorithm/HalconLib/include/halconcpp
INCLUDEPATH += $$PWD/../algorithm/HalconLib/include/hdevengine

LIBS += -L$$PWD/../algorithm/HalconLib/lib/ -lhalconxl
LIBS += -L$$PWD/../algorithm/HalconLib/lib/ -lhalconcppxl
LIBS += -L$$PWD/../algorithm/HalconLib/lib/ -lhdevenginecppxl

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../hstool/release/ -lhstool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../hstool/debug/ -lhstool

INCLUDEPATH += $$PWD/../hstool
DEPENDPATH += $$PWD/../hstool

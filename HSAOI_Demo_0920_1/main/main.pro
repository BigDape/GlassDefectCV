#---------------------------------------------------------------------------------------
# Function：    玻璃检测仪
# debugger：    MSVC2017 64
#
# @Author     zsg
# @Time       2022/03/27
#---------------------------------------------------------------------------------------

QT       += core gui network xml sql

TEMPLATE = app
TARGET = haoshi

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_FILE  += logo.rc

CONFIG += c++11
CONFIG += exception
DISTFILES += \
    logo.rc

RESOURCES += \
    SystemSource.qrc
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
           Form/FlawShowWidget.cpp \
           Form/glassstatictablewidget.cpp \
           Form/msvlcdnumclockwidget.cpp \
           Form/singleflawshowwidget.cpp \
           Form/singlesizeshowwidget.cpp \
           Form/LightControl.cpp \
           Form/cameraslayout.cpp \
           Form/DushenCameraWidget.cpp \
           Form/TitleBar.cpp \
           Form/MyGraphicsitem.cpp \
           MainForm.cpp \
           common_func.cpp \
           log_singleton.cpp \
           main.cpp \
           mainwindow.cpp \
           Global.cpp \
           HsListener.cpp

HEADERS += \
        Form/LightControl.h \
        Form/cameraslayout.h \
        Form/DushenCameraWidget.h \
        Form/FlawShowWidget.h \
        Form/SingleSizeShowWidget.h \
        Form/glassstatictablewidget.h \
        Form/msvlcdnumclockwidget.h \
        Form/singleflawshowwidget.h \
        Form/TitleBar.h \
        Form/MyGraphicsitem.h \
        MainForm.h \
        common_func.h \
        log_singleton.h \
        mainwindow.h \
        Global.h \
        HsListener.h \   
        FlawDefine.h

FORMS += \
        Form/SingleSizeShowWidget.ui \
        Form/msvlcdnumclockwidget.ui \
        Form/singleflawshowwidget.ui \
        Form/LightControl.ui \
        Form/DushenCameraWidget.ui \
        Form/cameraslayout.ui\
        MainForm.ui \
        mainwindow.ui

TRANSLATIONS += \
    HSAOI_zh_CN.ts

#度申相机SDK
message("Windows x86_64 build")
## Windows x64 (64bit) specific build here
LIBS += -L$$PWD/lib_x86_64/ -lDVPCamera64
INCLUDEPATH += $$PWD/lib_x86_64
DEPENDPATH += $$PWD/lib_x86_64

#OpenCV 4.5 vc15 图形库
#win32:CONFIG(release, debug|release): LIBS += -LC:/Qt/opencv4.5/build/x64/vc15/lib/ -lopencv_world450
#else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Qt/opencv4.5/build/x64/vc15/lib/ -lopencv_world450d

#INCLUDEPATH += C:/Qt/opencv4.5/build/include
#DEPENDPATH += C:/Qt/opencv4.5/build/include

#添加Halcon22.05库
INCLUDEPATH += $$PWD/HalconLib/include/
INCLUDEPATH += $$PWD/HalconLib/include/halconcpp
INCLUDEPATH += $$PWD/HalconLib/include/hdevengine

LIBS += -L$$PWD/HalconLib/lib/ -lhalconxl
LIBS += -L$$PWD/HalconLib/lib/ -lhalconcppxl
LIBS += -L$$PWD/HalconLib/lib/ -lhdevenginecppxl

#添加qwt插件
win32:CONFIG(release, debug|release): LIBS += -LC:/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/ -lqwtd

INCLUDEPATH += C:/Qt/Qt5.14.2/5.14.2/msvc2017_64/include
DEPENDPATH += C:/Qt/Qt5.14.2/5.14.2/msvc2017_64/include

# 在Release生成用于调试dump的信息，包括【禁用release编译优化】、【生成PDB符号表】，但是这些设置会降低程序性能，和debug差不多
CONFIG(release, debug|release) {
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE += -O0
    QMAKE_CXXFLAGS_RELEASE += /Zi
    QMAKE_LFLAGS_RELEASE += /DEBUG /OPT:REF /OPT:ICF                # 生成 PDB符号文件，功能和下一行一样，但是最好用这一行，显示指定编译选项

    # 打印变量参数值
    message(QMAKE_CXXFLAGS_RELEASE变量值：$$QMAKE_CXXFLAGS_RELEASE)
    message(QMAKE_LFLAGS_RELEASE变量值：$$QMAKE_LFLAGS_RELEASE)
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#添加日志库模块
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../log/release/ -llog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../log/debug/ -llog

INCLUDEPATH += $$PWD/../log
DEPENDPATH += $$PWD/../log

#添加数据库模块
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DataBase/release/ -lDataBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DataBase/debug/ -lDataBase

INCLUDEPATH += $$PWD/../DataBase
DEPENDPATH += $$PWD/../DataBase


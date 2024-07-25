#--------------------------------------------
#   @projectname    HSAOI
#   @Company        Anhui Haoshi
#   @MainBuilder    chengwenjie
#   @CreateDate     2023-06-20
#---------------------------------------------
QT       += core gui network xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_FILE  += logo.rc

CONFIG += c++11

QT  +=sql

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
    Camera/Dushen/DushenBasicFunc.cpp \
    Camera/Dushen/DushenCameraWidget.cpp \
    Camera/Dushen/mosaickimage.cpp \
    Camera/DushenSample/ImageAcquisition.cpp \
    Camera/DushenSample/MyGraphicsitem.cpp \
    Form/CamerasWidget.cpp \
    Form/FlawShowWidget.cpp \
    Form/TitleBar.cpp \
    Form/glassstatictablewidget.cpp \
    Form/msvlcdnumclockwidget.cpp \
    Form/singleflawshowwidget.cpp \
    Form/singlesizeshowwidget.cpp \
    Global.cpp \
    ImageProcess/processdetect.cpp \
    ImageProcess/processtile.cpp \
    Jianbo_db.cpp \
    LightControl/LightControl.cpp \
    LightControl/ParamComm.cpp \
    LightControl/RegParasComm.cpp \
    LightControl/SignalControlData.cpp \
    LightControl/Tcp.cpp \
    LightControl/TcpPackComm.cpp \
    MainForm.cpp \
    NavigationBar/CNavDelegate.cpp \
    NavigationBar/CNavModel.cpp \
    NavigationBar/CNavView.cpp \
    Parameter/CameraParamsWidget.cpp \
    Parameter/JsonParse2Map.cpp \
    Parameter/JsonRecipeWidget.cpp \
    Parameter/JsonResultParse.cpp \
    Parameter/XmlParse.cpp \
    SystemSettingForm.cpp \
    common_func.cpp \
    log_singleton.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    Camera/Dushen/DushenBasicFunc.h \
    Camera/Dushen/DushenCameraWidget.h \
    Camera/Dushen/mosaickimage.h \
    Camera/DushenSample/DVPCamera.h \
    Camera/DushenSample/ImageAcquisition.h \
    Camera/DushenSample/MyGraphicsitem.h \
    FlawDefine.h \
    Form/CamerasWidget.h \
    Form/FlawShowWidget.h \
    Form/SingleSizeShowWidget.h \
    Form/TitleBar.h \
    Form/glassstatictablewidget.h \
    Form/msvlcdnumclockwidget.h \
    Form/singleflawshowwidget.h \
    Global.h \
    ImageProcess/processdetect.h \
    ImageProcess/processtile.h \
    Jianbo_db.h \
    LightControl/ElemMatch.h \
    LightControl/LightControl.h \
    LightControl/ParamComm.h \
    LightControl/RegParasComm.h \
    LightControl/SignalControlData.h \
    LightControl/Tcp.h \
    LightControl/TcpPackComm.h \
    MainForm.h \
    NavigationBar/CNavDelegate.h \
    NavigationBar/CNavModel.h \
    NavigationBar/CNavView.h \
    Parameter/CameraParamsWidget.h \
    Parameter/JsonParse2Map.h \
    Parameter/JsonRecipeWidget.h \
    Parameter/JsonResultParse.h \
    Parameter/XmlParse.h \
    SystemSettingForm.h \
    common_func.h \
    log_singleton.h \
    mainwindow.h \

FORMS += \
    Camera/Dushen/DushenCameraWidget.ui \
    Form/CamerasWidget.ui \
    Form/SingleSizeShowWidget.ui \
    Form/msvlcdnumclockwidget.ui \
    Form/singleflawshowwidget.ui \
    LightControl/LightControl.ui \
    MainForm.ui \
    Parameter/JsonRecipeWidget.ui \
    SystemSettingForm.ui \
    mainwindow.ui

TRANSLATIONS += \
    HSAOI_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#度申相机SDK
win32{
        message("Windows x86_64 build")
        ## Windows x64 (64bit) specific build here
        LIBS += -L$$PWD/lib_x86_64/ -lDVPCamera64
        INCLUDEPATH += $$PWD/lib_x86_64
        DEPENDPATH += $$PWD/lib_x86_64
}

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

DISTFILES += \
    logo.rc

RESOURCES += \
    SystemSource.qrc

#添加qwt插件
win32:CONFIG(release, debug|release): LIBS += -LC:/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/ -lqwtd

INCLUDEPATH += C:/Qt/Qt5.14.2/5.14.2/msvc2017_64/include
DEPENDPATH += C:/Qt/Qt5.14.2/5.14.2/msvc2017_64/include

#添加opencv组件
win32:CONFIG(release, debug|release): LIBS += -LC:/opencv/build/x64/vc15/lib/ -lopencv_world455
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/opencv/build/x64/vc15/lib/ -lopencv_world455d

INCLUDEPATH += C:/opencv/build/include
DEPENDPATH += C:/opencv/build/include

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



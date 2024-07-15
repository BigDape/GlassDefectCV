#--------------------------------------------
#   @projectname    HSAOI
#   @Company        Anhui Haoshi
#   @MainBuilder    chengwenjie
#   @CreateDate     2023-06-20
#---------------------------------------------
QT += core gui network xml sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += MY_MACRO
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Camera/Dushen/DushenBasicFunc.cpp \
    Camera/Dushen/DushenCameraWidget.cpp \
    Camera/Dushen/mosaickimage.cpp \
    Camera/DushenSample/BasicFunction.cpp \
    Camera/DushenSample/ImageAcquisition.cpp \
    Camera/DushenSample/MyGraphicsitem.cpp \
    Form/CamerasWidget.cpp \
    Form/FlawShowWidget.cpp \
    Form/TitleBar.cpp \
    Form/glassstatictablewidget.cpp \
    Form/msvlcdnumclockwidget.cpp \
    Form/realtimedefects.cpp \
    Form/singleflawshowwidget.cpp \
    Form/singlesizeshowwidget.cpp \
    Global.cpp \
    HsListener.cpp \
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
    Parameter/json_reader.cpp \
    Parameter/json_value.cpp \
    Parameter/json_writer.cpp \
    SystemSettingForm.cpp \
    common_func.cpp \
    log_singleton.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Camera/Dushen/DushenBasicFunc.h \
    Camera/Dushen/DushenCameraWidget.h \
    Camera/Dushen/mosaickimage.h \
    Camera/DushenSample/BasicFunction.h \
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
    Form/realtimedefects.h \
    Form/singleflawshowwidget.h \
    Global.h \
    HsListener.h \
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
    Parameter/allocator.h \
    Parameter/assertions.h \
    Parameter/config.h \
    Parameter/forwards.h \
    Parameter/json.h \
    Parameter/json_features.h \
    Parameter/json_tool.h \
    Parameter/reader.h \
    Parameter/value.h \
    Parameter/version.h \
    Parameter/writer.h \
    SystemSettingForm.h \
    common_func.h \
    hsThreadPool.h \
    log_singleton.h \
    mainwindow.h

FORMS += \
    Camera/Dushen/DushenCameraWidget.ui \
    Camera/DushenSample/BasicFunction.ui \
    Form/CamerasWidget.ui \
    Form/SingleSizeShowWidget.ui \
    Form/msvlcdnumclockwidget.ui \
    Form/realtimedefects.ui \
    Form/singleflawshowwidget.ui \
    LightControl/LightControl.ui \
    MainForm.ui \
    Parameter/JsonRecipeWidget.ui \
    SystemSettingForm.ui \
    mainwindow.ui

TRANSLATIONS += HSAOI_zh_CN.ts
RC_FILE  += logo.rc
DISTFILES += logo.rc
RESOURCES += SystemSource.qrc
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
message($$PWD)
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

#添加qt文件
INCLUDEPATH += C:/Qt/Qt5.14.2/5.14.2/msvc2017_64/include
DEPENDPATH += C:/Qt/Qt5.14.2/5.14.2/msvc2017_64/include



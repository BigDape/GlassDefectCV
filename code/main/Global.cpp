﻿#include "Global.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <QSettings>
#include <QFile>

GlobalParamter::GlobalParamter()
    :CurrentRecipe(""),
     SystemName(""),
     Camera0Name(""),
     Camera1Name(""),
     Camera2Name(""),
     Camera3Name(""),
     serverIp(""),
     serverPort(0),
     FrameSignal(0),
     AlmLightSignal(false),
     AlmLightVal(0),
     FieldNumberSet(0),
     camDefineNum(0),
     GlassID_INT(0),
     RollerAngle(0),
     encodeRollerYLength(0),
     m_plot(nullptr),
     isOffline(false),
     offlineFullPath(""),
     isSaveOriginImage(0),
     isSaveEntireImage(0),
     isSaveFlawImage(0),
     isSaveCropImage(0),
     XYLengthEnable(0),
     FlawDefectEnable(0),
     Camera12PixelDeviation(0),
     Camera23PixelDeviation(0),
     Camera24PixelDeviation(0),
     SilkToRollerDist(0),
     ScratchAreaThreshold(0),
     BubbleStoneAreaThreshold(0),
     DirtyAreaThreshold(0),
     YAccuracyB(0),
     YAccuracyK(0),
     Width(0),
     WidthDeviation(0),
     Digonal(0),
     Digonal1Deviation(0),
     Digonal2(0),
     Digonal2Deviation(0),
     Camera1Pixel0Accuracy(0),
     Camera1PixelKValue(0),
     Camera21AccuracyRatio(0),
     Camera2PixelKValue(0),
     Length(0),
     LengthDeviation(0),
     Camera0Frame(0),
     Camera0PhotoRow(0),
     Camera0ExposureTime(0),
     Camera0Gain(0),
     Camera1Frame(0),
     Camera1PhotoRow(0),
     Camera1ExposureTime(0),
     Camera1Gain(0),
     Camera2Frame(0),
     Camera2PhotoRow(0),
     Camera2ExposureTime(0),
     Camera2Gain(0),
     Camera3Frame(0),
     Camera3PhotoRow(0),
     Camera3ExposureTime(0),
     Camera3Gain(0),
     EncodeUnitToDist(0),
     EncodePulseFilterUs(0),
     EncodeRevolution(0),
     RollerPerimeterUm(0),
     ExpectSinglePixelAccuracy(0),
     RollerMaxSpeedToRowCount(0),
     EveryRowToEncodeCount(0),
     PixelAccuracyUm(0),
     PhotoelectricSignalPulseFilter(0),
     CamareTrigerPulseContinueTime10ns(0),
     PhotoelectricToCamareDist(0),
     CamareFrameTrigerDelayRowCount(0),
     FrameSignalContinueTime(0),
     ModuleEnableSignal(0),
     CamarePhotoRowCount(0),
     InnerRowFrequency(0),
     PhotoMode(0),
     PhotoEndDelayRowCount(0),
     LightField1DelayTime(0),
     LightField1GlowTime(0),
     LightField2DelayTime(0),
     LightField2GlowTime(0),
     LightField3DelayTime(0),
     LightField3GlowTime(0),
     LightField4DelayTime(0),
     LightField4GlowTime(0),
     SelectedLightFieldNumber(0),
     HorizontalDarkfieldSelectRegister(0),
     CamareAndLightFieldControl(0),
     SignalSwitch(0),
     RowSignalSelected(0)
{}

GlobalParamter::~GlobalParamter(){}

GlobalParamter& GlobalParamter::getInstance()
{
    static GlobalParamter param;
    return param;
}

QString GlobalParamter::GetParamterFromIniFile(QString fullpath, QString key)
{
    QString result = "default";
    try{
        QSettings settings(fullpath, QSettings::IniFormat);
        // 检查文件是否存在
        if (QFile::exists(settings.fileName())) {
            result = settings.value(key, "default").toString();
            if (result == "default") {
                qDebug() << "Key not found in config file. Using default value.";
            } else {
                qDebug() << "Value from config file: " << result;
            }
        }
    } catch (const std::bad_alloc& e) {
        qDebug()<<"内存分配失败：" << e.what();
    } catch (const std::runtime_error& e) {
        qDebug()<<"运行时错误：" << e.what();
    } catch (const std::exception& e) {
        qDebug()<<"异常错误：" << e.what();
    } catch (...) {
        qDebug()<<"未知错误";
    }
    return result;
}

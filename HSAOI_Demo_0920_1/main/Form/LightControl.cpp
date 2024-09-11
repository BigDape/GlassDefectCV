#include "LightControl.h"
#include "ui_LightControl.h"
#include <QTimer>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Global.h"

#pragma execution_character_set("utf-8")

LightControl::LightControl( QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::LightControl)
{
    ui->setupUi(this);
    // 初始化输入框类型
    LightControl::initLineEditInputType();
    // 加载当前的工单
    // 给每个输入框赋值
    LightControl::InitLightControl();

    //
    // 此处开启一个线程，1S刷新一下数据
    //
    timer1 = std::make_shared<QTimer>();
    connect(timer1.get(),&QTimer::timeout,this,&LightControl::slot_updateCode);
    timer1->start(1000);
}

//析构函数
LightControl::~LightControl()
{
    delete ui;
}

// 初始化输入框输入类型
void LightControl::initLineEditInputType()
{
    //输入框确定类型
    QDoubleValidator* lineDouble = new QDoubleValidator(0, 100000, 3, nullptr);
    QIntValidator* lineInt = new QIntValidator(0, 1000000000, nullptr);
    QRegExpValidator* lineQString = new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$"));
    QRegExpValidator* lineIP = new QRegExpValidator(QRegExp("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"));
    QRegExpValidator* linePort = new QRegExpValidator(QRegExp("((6553[0-5])|[655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{3}|[1-9][0-9]{2}|[1-9][0-9]|[0-9])"));
    //系统参数
    ui->SystemNameLE->setValidator(lineQString);
    ui->CameraNumLE->setValidator(lineInt);
    ui->Camera0NameLE->setValidator(lineQString);
    ui->Camera1NameLE->setValidator(lineQString);
    ui->Camera2NameLE->setValidator(lineQString);
    ui->Camera3NameLE->setValidator(lineQString);
    ui->ServerIPLE->setValidator(lineIP);
    ui->PortLE->setValidator(linePort);
    //自定义参数
    //缺陷检测
    ui->Camera12PixelDeviationLE->setValidator(lineInt);
    ui->Camera23PixelDeviationLE->setValidator(lineInt);
    ui->Camera24PixelDeviationLE->setValidator(lineInt);
    ui->SilkToRollerDistLE->setValidator(lineInt);
    ui->ScratchAreaThresholdLE->setValidator(lineInt);
    ui->BubbleStoneAreaThresholdLE->setValidator(lineInt);
    ui->DirtyAreaThresholdLE->setValidator(lineInt);
    //尺寸测量
    ui->YAccuracyBLE->setValidator(lineDouble);
    ui->YAccuracyKLE->setValidator(lineDouble);
    ui->WidthLE->setValidator(lineDouble);
    ui->WidthDeviationLE->setValidator(lineDouble);
    ui->Digonal1LE->setValidator(lineDouble);
    ui->Digonal1DeviationLE->setValidator(lineDouble);
    ui->Digonal2LE->setValidator(lineDouble);
    ui->Digonal2DeviationLE->setValidator(lineDouble);
    ui->Camera1Pixel0AccuracyLE->setValidator(lineDouble);
    ui->Camera1PixelKValueLE->setValidator(lineDouble);
    ui->Camera21AccuracyRatioLE->setValidator(lineDouble);
    ui->Camera2PixelKValueLE->setValidator(lineDouble);
    ui->LengthLE->setValidator(lineDouble);
    ui->LengthDeviationLE->setValidator(lineDouble);
    //相机参数
    ui->Camera0FrameLE->setValidator(lineInt);
    ui->Camera0PhotoRowLE->setValidator(lineInt);
    ui->Camera0ExposureTimeLE->setValidator(lineInt);
    ui->Camera0GainLE->setValidator(lineInt);
    ui->Camera1FrameLE->setValidator(lineInt);
    ui->Camera1PhotoRowLE->setValidator(lineInt);
    ui->Camera1ExposureTimeLE->setValidator(lineInt);
    ui->Camera1GainLE->setValidator(lineInt);
    ui->Camera2FrameLE->setValidator(lineInt);
    ui->Camera2PhotoRowLE->setValidator(lineInt);
    ui->Camera2ExposureTimeLE->setValidator(lineInt);
    ui->Camera2GainLE->setValidator(lineInt);
    ui->Camera3FrameLE->setValidator(lineInt);
    ui->Camera3PhotoRowLE->setValidator(lineInt);
    ui->Camera3ExposureTimeLE->setValidator(lineInt);
    ui->Camera3GainLE->setValidator(lineInt);
    //编码器参数
    ui->EncodeUnitToDistLE->setValidator(lineInt);
    ui->EncodePulseFilterUsLE->setValidator(lineInt);
    ui->EncodeCountEndFlagLE->setValidator(lineInt);
    ui->EncodeCountLE->setValidator(lineInt);
    ui->EncodeTriggerRowCountLE->setValidator(lineInt);
    ui->Encode4FrequencyMultiplierCountLE->setValidator(lineInt);
    ui->EncodeUnitTimePulseCountLE->setValidator(lineInt);
    ui->EncodeCountTimeHalfSecondLE->setValidator(lineInt);
    ui->EncodeChannelLE->setValidator(lineInt);
    ui->EncodeRevolutionLE->setValidator(lineInt);
    ui->RollerPerimeterUmLE->setValidator(lineInt);
    ui->ExpectSinglePixelAccuracyLE->setValidator(lineInt);
    ui->RollerMaxSpeedToRowCountLE->setValidator(lineInt);
    ui->EveryRowToEncodeCountLE->setValidator(lineInt);
    //控制器参数
    ui->PixelAccuracyUmLE->setValidator(lineInt);
    ui->PhotoelectricSignalPulseFilterLE->setValidator(lineInt);
    ui->CamareTrigerPulseContinueTime10nsLE->setValidator(lineInt);
    ui->PhotoelectricToCamareDistLE->setValidator(lineInt);
    ui->CamareFrameTrigerDelayRowCountLE->setValidator(lineInt);
    ui->FrameSignalContinueTimeLE->setValidator(lineInt);
    ui->ModuleEnableSignalLE->setValidator(lineInt);
    ui->CamarePhotoRowCountLE->setValidator(lineInt);
    ui->InnerRowFrequencyLE->setValidator(lineInt);
    ui->PhotoModeLE->setValidator(lineInt);
    ui->PhotoEndDelayRowCountLE->setValidator(lineInt);
    //光源控制器参数
    ui->LightField1DelayTimeLE->setValidator(lineInt);
    ui->LightField1GlowTimeLE->setValidator(lineInt);
    ui->LightField2DelayTimeLE->setValidator(lineInt);
    ui->LightField2GlowTimeLE->setValidator(lineInt);
    ui->LightField3DelayTimeLE->setValidator(lineInt);
    ui->LightField3GlowTimeLE->setValidator(lineInt);
    ui->LightField4DelayTimeLE->setValidator(lineInt);
    ui->LightField4GlowTimeLE->setValidator(lineInt);
    ui->SelectedLightFieldNumberLE->setValidator(lineInt);
    ui->HorizontalDarkfieldSelectRegisterLE->setValidator(lineInt);
    ui->SignalSwitchLE->setValidator(lineInt);
    ui->RowSignalSelectedLE->setValidator(lineInt);
}

void LightControl::slotTrigger()
{
    //内部产生光电信号(写1再写0)
//    unsigned int endInnerSignal = 0;
//    unsigned int startInnerSignal = 1;
//    m_pSig_comm.SetRegs(ADDR38, ADDR38, &startInnerSignal);
//    m_pSig_comm.SetRegs(ADDR38, ADDR38, &endInnerSignal);

}

void LightControl::slot_updateCode()
{
    ui->EncodeCountLE->setText(QString::number(PARAM.getCodeCount()));
    ui->EncodeCountLE->setText(QString::number(PARAM.getCodeLineCount()));
    ui->Encode4FrequencyMultiplierCountLE->setText(QString::number(PARAM.getCode4Count()));
    ui->EncodeUnitTimePulseCountLE->setText(QString::number(PARAM.getCodePerCount()));
    //计算Y长度
    double radian = PARAM.getRollerAngle();
    double cosValue = cos(radian);
    PARAM.setEncodeRollerYLength(PARAM.getEncodeBRollerCount() * PARAM.getEncodeRollerCofficient() * cosValue);
    ui->EncodePressureWheelCountALE->setText(QString::number(PARAM.getEncodeARollerCount()));
    ui->EncodePressureWheelCountBLE->setText(QString::number(PARAM.getEncodeBRollerCount()));
    ui->Encode4FrequencyMultiplierCountLE->setText(QString::number(PARAM.getEncodeAB4()));
}

bool LightControl::InitLightControl()
{
    QString needLoadJsonFile = PARAM.GetParamterFromIniFile(SYSTEM_PATH,"recipe");//需要加载的工单名称recipe=8nm.json
    QDir dir(RECIPE_FULLPATH);
    QFileInfoList fileList = dir.entryInfoList(QStringList() << "*.json");
    if (fileList.size() == 0) { //没有找到任何json工单
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
        QString recipeFileName = current_date + QString(".json");
        QString newRecipe = LightControl::createNewRecipeFile(recipeFileName);  //产生初始化工单
        LightControl::readRecipeToTable(newRecipe.toStdString());
        ui->RecipeCB->addItem(newRecipe);
        ui->RecipeCB->setCurrentText(newRecipe);
        return true;
    } else {                    //找到了json工单
        ui->RecipeCB->clear();//清除工单里面所有items
        //遍历文件夹
        for(auto fileInfo:fileList) {
            ui->RecipeCB->addItem(fileInfo.fileName());
        }
        int ret = ui->RecipeCB->findText(needLoadJsonFile);
        if (ret == -1) {
            QString message = "Not find " + needLoadJsonFile + " in RecipeCB Items!";
            INFOMATION.criticalMessageBox(this,message);
            return false;
        } else {
            ui->RecipeCB->setCurrentText(needLoadJsonFile);
            LightControl::readRecipeToTable(needLoadJsonFile.toStdString());
            return true;
        }
    }
}

// 创建新的空白工单文件
QString LightControl::createNewRecipeFile(QString recipeFileName)
{
    //Json::Value root;
    Json::FastWriter writer;
    { //系统参数
        m_root["SystemParams"]["SystemName"] = "大拓智能视觉检测";
        m_root["SystemParams"]["CamareNumber"] = "4";
        m_root["SystemParams"]["Camare0Name"] = "DSXL810003076";
        m_root["SystemParams"]["Camare1Name"] = "DSXL810002378";
        m_root["SystemParams"]["Camare2Name"] = "DSXL810002135";
        m_root["SystemParams"]["Camare3Name"] = "DSXL810002382";
        m_root["SystemParams"]["ServerIP"] = "192.168.1.200";
        m_root["SystemParams"]["ServerPort"] = "7002";
    }
    { //自定义参数
       m_root["CustomParams"]["SaveOriginImage"] = "1";
       m_root["CustomParams"]["SaveEntireImage"] = "1";
       m_root["CustomParams"]["SaveFlawImage"] = "1";
       m_root["CustomParams"]["SaveCropImage"] = "1";
       m_root["CustomParams"]["XYLengthEnable"] = "1";
       m_root["CustomParams"]["FlawDefectEnable"] = "1";
    }
    { //缺陷检测
       m_root["DefectDetectionParams"]["Camera12PixelDeviation"] = "0";
       m_root["DefectDetectionParams"]["Camera23PixelDeviation"] = "0";
       m_root["DefectDetectionParams"]["Camera24PixelDeviation"] = "0";
       m_root["DefectDetectionParams"]["SilkToRollerDist"] = "0";
       m_root["DefectDetectionParams"]["ScratchAreaThreshold"] = "0";
       m_root["DefectDetectionParams"]["BubbleStoneAreaThreshold"] = "0";
       m_root["DefectDetectionParams"]["DirtyAreaThreshold"] = "0";
    }
    { //尺寸测量
       m_root["DimensionalMeasurementParams"]["YAccuracyB"] = "0";
       m_root["DimensionalMeasurementParams"]["YAccuracyK"] = "0";
       m_root["DimensionalMeasurementParams"]["Width"] = "0";
       m_root["DimensionalMeasurementParams"]["WidthDeviation"] = "0";
       m_root["DimensionalMeasurementParams"]["Digonal1"] = "0";
       m_root["DimensionalMeasurementParams"]["Digonal1Deviation"] = "0";
       m_root["DimensionalMeasurementParams"]["Diagonal2"] = "0";
       m_root["DimensionalMeasurementParams"]["Digonal2Deviation"] = "0";
       m_root["DimensionalMeasurementParams"]["Camera1Pixel0Accuracy"] = "0";
       m_root["DimensionalMeasurementParams"]["Camera1PixelKValue"] = "0";
       m_root["DimensionalMeasurementParams"]["Camera21AccuracyRatio"] = "0";
       m_root["DimensionalMeasurementParams"]["Camera2PixelKValue"] = "0";
       m_root["DimensionalMeasurementParams"]["Length"] = "0";
       m_root["DimensionalMeasurementParams"]["LengthDeviation"] = "0";
    }
    {//相机参数
        m_root["CamareParams"]["Camera0Frame"] = "0";
        m_root["CamareParams"]["Camera0PhotoRow"] = "0";
        m_root["CamareParams"]["Camera0ExposureTime"] = "0";
        m_root["CamareParams"]["Camera0Gain"] = "0";
        m_root["CamareParams"]["Camera1Frame"] = "0";
        m_root["CamareParams"]["Camera1PhotoRow"] = "0";
        m_root["CamareParams"]["Camera1ExposureTime"] = "0";
        m_root["CamareParams"]["Camera1Gain"] = "0";
        m_root["CamareParams"]["Camera2Frame"] = "0";
        m_root["CamareParams"]["Camera2PhotoRow"] = "0";
        m_root["CamareParams"]["Camera2ExposureTime"] = "0";
        m_root["CamareParams"]["Camera2Gain"] = "0";
        m_root["CamareParams"]["Camera3Frame"] = "0";
        m_root["CamareParams"]["Camera3PhotoRow"] = "0";
        m_root["CamareParams"]["Camera3ExposureTime"] = "0";
        m_root["CamareParams"]["Camera3Gain"] = "0";
    }
    {//编码器参数
        m_root["EncoderParams"]["EncodeUnitToDist"] = "0";
        m_root["EncoderParams"]["EncodePulseFilterUs"] = "0";
        m_root["EncoderParams"]["EncodeCountEndFlag"] = "0";
        m_root["EncoderParams"]["EncodeCount"] = "0";
        m_root["EncoderParams"]["EncodeTriggerRowCount"] = "0";
        m_root["EncoderParams"]["Encode4FrequencyMultiplierCount"] = "0";
        m_root["EncoderParams"]["EncodeUnitTimePulseCount"] = "0";
        m_root["EncoderParams"]["EncodeCountTimeHalfSecond"] = "0";
        m_root["EncoderParams"]["EncodeChannel"] = "0";
        m_root["EncoderParams"]["EncodeRevolution"] = "0";
        m_root["EncoderParams"]["RollerPerimeterUm"] = "0";
        m_root["EncoderParams"]["ExpectSinglePixelAccuracy"] = "0";
        m_root["EncoderParams"]["RollerMaxSpeedToRowCount"] = "0";
        m_root["EncoderParams"]["EveryRowToEncodeCount"] = "0";
        m_root["EncoderParams"]["EncodePressureWheelCountA"] = "0";
        m_root["EncoderParams"]["EncodePressureWheelCountB"] = "0";
        m_root["EncoderParams"]["PressureWheel4FrequencyMutliper"] = "0";
        m_root["EncoderParams"]["PressureEncodecoefficient"] = "0";
    }
    {//控制器参数
        m_root["ControllerParams"]["PixelAccuracyUm"] = "0";
        m_root["ControllerParams"]["PhotoelectricSignalPulseFilter"] = "0";
        m_root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"] = "0";
        m_root["ControllerParams"]["PhotoelectricToCamareDist"] = "0";
        m_root["ControllerParams"]["CamareFrameTrigerDelayRowCount"] = "0";
        m_root["ControllerParams"]["FrameSignalContinueTime"] = "0";
        m_root["ControllerParams"]["ModuleEnableSignal"] = "0";
        m_root["ControllerParams"]["CamarePhotoRowCount"] = "0";
        m_root["ControllerParams"]["InnerRowFrequency"] = "0";
        m_root["ControllerParams"]["PhotoMode"] = "0";
        m_root["ControllerParams"]["PhotoEndDelayRowCount"] = "0";
    }
    {//光源控制器参数
        m_root["LighterParams"]["LightField1DelayTime"] = "0";
        m_root["LighterParams"]["LightField1GlowTime"] = "0";
        m_root["LighterParams"]["LightField2DelayTime"] = "0";
        m_root["LighterParams"]["LightField2GlowTime"] = "0";
        m_root["LighterParams"]["LightField3DelayTime"] = "0";
        m_root["LighterParams"]["LightField3GlowTime"] = "0";
        m_root["LighterParams"]["LightField4DelayTime"] = "0";
        m_root["LighterParams"]["LightField4GlowTime"] = "0";
        m_root["LighterParams"]["SelectedLightFieldNumber"] = "3";
        m_root["LighterParams"]["HorizontalDarkfieldSelectRegister"] = "0";
        m_root["LighterParams"]["CamareAndLightFieldControl"] = "0";
        m_root["LighterParams"]["SignalSwitch"] = "0";
        m_root["LighterParams"]["RowSignalSelected"] = "0";
    }
    std::string json_content = writer.write(m_root);
    std::ofstream ofs;
    ofs.open(recipeFileName.toStdString().data());
    if (ofs.is_open()) {
        ofs<<json_content;
        ofs.close();
    }
    return recipeFileName;
}

// 读取json工单到表单中
void LightControl::readRecipeToTable(std::string filePath)
{
    //获取json数据，初始化界面参数
    std::ifstream ifs;
    ifs.open(filePath); // Windows自己注意路径吧
    if (!ifs.is_open()) {
        QString message = "Open file ["+QString(filePath.data()) +"] is failer!";
        INFOMATION.criticalMessageBox(this,message);
        return;
    }

    Json::Reader reader;
    //Json::Value root;
    // 解析到root，root将包含Json里所有子元素
    if (!reader.parse(ifs, m_root, false)) {
        INFOMATION.criticalMessageBox(this,"Parse json file is error!");
        ifs.close();
        return;
    }
    //系统参数
    ui->SystemNameLE->setText(m_root["SystemParams"]["SystemName"].asCString());
    ui->CameraNumLE->setText(m_root["SystemParams"]["CamareNumber"].asCString());
    ui->Camera0NameLE->setText(m_root["SystemParams"]["Camare0Name"].asCString());
    ui->Camera1NameLE->setText(m_root["SystemParams"]["Camare1Name"].asCString());
    ui->Camera2NameLE->setText(m_root["SystemParams"]["Camare2Name"].asCString());
    ui->Camera3NameLE->setText(m_root["SystemParams"]["Camare3Name"].asCString());
    ui->ServerIPLE->setText(m_root["SystemParams"]["ServerIP"].asCString());
    ui->PortLE->setText(m_root["SystemParams"]["ServerPort"].asCString());
    PARAM.setSystemName( m_root["SystemParams"]["SystemName"].asCString());
    PARAM.setCamDefineNum(m_root["SystemParams"]["CamareNumber"].asInt());
    PARAM.setCamera0Name(m_root["SystemParams"]["Camare0Name"].asCString());
    PARAM.setCamera1Name(m_root["SystemParams"]["Camare1Name"].asCString());
    PARAM.setCamera2Name(m_root["SystemParams"]["Camare2Name"].asCString());
    PARAM.setCamera3Name(m_root["SystemParams"]["Camare3Name"].asCString());
    PARAM.setServerIP(m_root["SystemParams"]["ServerIP"].asCString());
    PARAM.setPort(m_root["SystemParams"]["ServerPort"].asInt());
    //自定义参数
    ui->SaveOriginImageCB->setCurrentIndex(m_root["CustomParams"]["SaveOriginImage"].asInt());
    ui->SaveEntireImageCB->setCurrentIndex(m_root["CustomParams"]["SaveEntireImage"].asInt());
    ui->SaveFlawImageCB->setCurrentIndex(m_root["CustomParams"]["SaveFlawImage"].asInt());
    ui->SaveCropImageCB->setCurrentIndex(m_root["CustomParams"]["SaveCropImage"].asInt());
    ui->XYLengthEnableCB->setCurrentIndex(m_root["CustomParams"]["XYLengthEnable"].asInt());
    ui->FlawDefectEnableCB->setCurrentIndex(m_root["CustomParams"]["FlawDefectEnable"].asInt());
    PARAM.setSaveOriginImage(m_root["CustomParams"]["SaveOriginImage"].asInt());
    PARAM.setSaveEntireImage(m_root["CustomParams"]["SaveEntireImage"].asInt());
    PARAM.setSaveFlawImage(m_root["CustomParams"]["SaveFlawImage"].asInt());
    PARAM.setSaveCropImage(m_root["CustomParams"]["SaveCropImage"].asInt());
    PARAM.setXYLengthEnable(m_root["CustomParams"]["XYLengthEnable"].asInt());
    PARAM.setFlawDefectEnable(m_root["CustomParams"]["FlawDefectEnable"].asInt());
    //缺陷检测
    ui->Camera12PixelDeviationLE->setText(m_root["DefectDetectionParams"]["Camera12PixelDeviation"].asCString());
    ui->Camera23PixelDeviationLE->setText(m_root["DefectDetectionParams"]["Camera23PixelDeviation"].asCString());
    ui->Camera24PixelDeviationLE->setText(m_root["DefectDetectionParams"]["Camera24PixelDeviation"].asCString());
    ui->SilkToRollerDistLE->setText(m_root["DefectDetectionParams"]["SilkToRollerDist"].asCString());
    ui->ScratchAreaThresholdLE->setText(m_root["DefectDetectionParams"]["ScratchAreaThreshold"].asCString());
    ui->BubbleStoneAreaThresholdLE->setText(m_root["DefectDetectionParams"]["BubbleStoneAreaThreshold"].asCString());
    ui->DirtyAreaThresholdLE->setText(m_root["DefectDetectionParams"]["DirtyAreaThreshold"].asCString());
    PARAM.setCamera12PixelDeviation(m_root["DefectDetectionParams"]["Camera12PixelDeviation"].asInt());
    PARAM.setCamera23PixelDeviation(m_root["DefectDetectionParams"]["Camera23PixelDeviation"].asInt());
    PARAM.setCamera24PixelDeviation(m_root["DefectDetectionParams"]["Camera24PixelDeviation"].asInt());
    PARAM.setSilkToRollerDist(m_root["DefectDetectionParams"]["SilkToRollerDist"].asInt());
    PARAM.setScratchAreaThreshold(m_root["DefectDetectionParams"]["ScratchAreaThreshold"].asInt());
    PARAM.setBubbleStoneAreaThreshold(m_root["DefectDetectionParams"]["BubbleStoneAreaThreshold"].asInt());
    PARAM.setDirtyAreaThreshold(m_root["DefectDetectionParams"]["DirtyAreaThreshold"].asInt());
    //尺寸测量
    ui->YAccuracyBLE->setText(m_root["DimensionalMeasurementParams"]["YAccuracyB"].asCString());
    ui->YAccuracyKLE->setText(m_root["DimensionalMeasurementParams"]["YAccuracyK"].asCString());
    ui->WidthLE->setText(m_root["DimensionalMeasurementParams"]["Width"].asCString());
    ui->WidthDeviationLE->setText(m_root["DimensionalMeasurementParams"]["WidthDeviation"].asCString());
    ui->Digonal1LE->setText(m_root["DimensionalMeasurementParams"]["Digonal1"].asCString());
    ui->Digonal1DeviationLE->setText(m_root["DimensionalMeasurementParams"]["Digonal1Deviation"].asCString());
    ui->Digonal2LE->setText(m_root["DimensionalMeasurementParams"]["Diagonal2"].asCString());
    ui->Digonal2DeviationLE->setText(m_root["DimensionalMeasurementParams"]["Digonal2Deviation"].asCString());
    ui->Camera1Pixel0AccuracyLE->setText(m_root["DimensionalMeasurementParams"]["Camera1Pixel0Accuracy"].asCString());
    ui->Camera1PixelKValueLE->setText(m_root["DimensionalMeasurementParams"]["Camera1PixelKValue"].asCString());
    ui->Camera21AccuracyRatioLE->setText(m_root["DimensionalMeasurementParams"]["Camera21AccuracyRatio"].asCString());
    ui->Camera2PixelKValueLE->setText(m_root["DimensionalMeasurementParams"]["Camera2PixelKValue"].asCString());
    ui->LengthLE->setText(m_root["DimensionalMeasurementParams"]["Length"].asCString());
    ui->LengthDeviationLE->setText(m_root["DimensionalMeasurementParams"]["LengthDeviation"].asCString());
    PARAM.setYAccuracyB(m_root["DimensionalMeasurementParams"]["YAccuracyB"].asDouble());
    PARAM.setYAccuracyK(m_root["DimensionalMeasurementParams"]["YAccuracyK"].asDouble());
    PARAM.setWidth(m_root["DimensionalMeasurementParams"]["Width"].asDouble());
    PARAM.setWidthDeviation(m_root["DimensionalMeasurementParams"]["WidthDeviation"].asDouble());
    PARAM.setDigonal(m_root["DimensionalMeasurementParams"]["Digonal1"].asDouble());
    PARAM.setDigonal1Deviation(m_root["DimensionalMeasurementParams"]["Digonal1Deviation"].asDouble());
    PARAM.setDigonal2(m_root["DimensionalMeasurementParams"]["Diagonal2"].asDouble());
    PARAM.setDigonal2Deviation(m_root["DimensionalMeasurementParams"]["Digonal2Deviation"].asDouble());
    PARAM.setCamera1Pixel0Accuracy(m_root["DimensionalMeasurementParams"]["Camera1Pixel0Accuracy"].asDouble());
    PARAM.setCamera1PixelKValue(m_root["DimensionalMeasurementParams"]["Camera1PixelKValue"].asDouble());
    PARAM.setCamera21AccuracyRatio(m_root["DimensionalMeasurementParams"]["Camera21AccuracyRatio"].asDouble());
    PARAM.setCamera2PixelKValue(m_root["DimensionalMeasurementParams"]["Camera2PixelKValue"].asDouble());
    PARAM.setLength(m_root["DimensionalMeasurementParams"]["Length"].asDouble());
    PARAM.setLengthDeviation(m_root["DimensionalMeasurementParams"]["LengthDeviation"].asDouble());
    //相机参数
    ui->Camera0FrameLE->setText(m_root["CamareParams"]["Camera0Frame"].asCString());
    ui->Camera0PhotoRowLE->setText(m_root["CamareParams"]["Camera0PhotoRow"].asCString());
    ui->Camera0ExposureTimeLE->setText(m_root["CamareParams"]["Camera0ExposureTime"].asCString());
    ui->Camera0GainLE->setText(m_root["CamareParams"]["Camera0Gain"].asCString());
    ui->Camera1FrameLE->setText(m_root["CamareParams"]["Camera1Frame"].asCString());
    ui->Camera1PhotoRowLE->setText(m_root["CamareParams"]["Camera1PhotoRow"].asCString());
    ui->Camera1ExposureTimeLE->setText(m_root["CamareParams"]["Camera1ExposureTime"].asCString());
    ui->Camera1GainLE->setText(m_root["CamareParams"]["Camera1Gain"].asCString());
    ui->Camera2FrameLE->setText(m_root["CamareParams"]["Camera2Frame"].asCString());
    ui->Camera2PhotoRowLE->setText(m_root["CamareParams"]["Camera2PhotoRow"].asCString());
    ui->Camera2ExposureTimeLE->setText(m_root["CamareParams"]["Camera2ExposureTime"].asCString());
    ui->Camera2GainLE->setText(m_root["CamareParams"]["Camera2Gain"].asCString());
    ui->Camera3FrameLE->setText(m_root["CamareParams"]["Camera3Frame"].asCString());
    ui->Camera3PhotoRowLE->setText(m_root["CamareParams"]["Camera3PhotoRow"].asCString());
    ui->Camera3ExposureTimeLE->setText(m_root["CamareParams"]["Camera3ExposureTime"].asCString());
    ui->Camera3GainLE->setText(m_root["CamareParams"]["Camera3Gain"].asCString());
    PARAM.setCamera0Frame(m_root["CamareParams"]["Camera0Frame"].asInt());
    PARAM.setCamera0PhotoRow(m_root["CamareParams"]["Camera0PhotoRow"].asInt());
    PARAM.setCamera0ExposureTime(m_root["CamareParams"]["Camera0ExposureTime"].asInt());
    PARAM.setCamera0Gain(m_root["CamareParams"]["Camera0Gain"].asInt());
    PARAM.setCamera1Frame(m_root["CamareParams"]["Camera1Frame"].asInt());
    PARAM.setCamera1PhotoRow(m_root["CamareParams"]["Camera1PhotoRow"].asInt());
    PARAM.setCamera1ExposureTime(m_root["CamareParams"]["Camera1ExposureTime"].asInt());
    PARAM.setCamera1Gain(m_root["CamareParams"]["Camera1Gain"].asInt());
    PARAM.setCamera2Frame(m_root["CamareParams"]["Camera2Frame"].asInt());
    PARAM.setCamera2PhotoRow(m_root["CamareParams"]["Camera2PhotoRow"].asInt());
    PARAM.setCamera2ExposureTime(m_root["CamareParams"]["Camera2ExposureTime"].asInt());
    PARAM.setCamera2Gain(m_root["CamareParams"]["Camera2Gain"].asInt());
    PARAM.setCamera3Frame(m_root["CamareParams"]["Camera3Frame"].asInt());
    PARAM.setCamera3PhotoRow(m_root["CamareParams"]["Camera3PhotoRow"].asInt());
    PARAM.setCamera3ExposureTime(m_root["CamareParams"]["Camera3ExposureTime"].asInt());
    PARAM.setCamera3Gain(m_root["CamareParams"]["Camera3Gain"].asInt());
    //编码器参数
    ui->EncodeUnitToDistLE->setText(m_root["EncoderParams"]["EncodeUnitToDist"].asCString());
    ui->EncodePulseFilterUsLE->setText(m_root["EncoderParams"]["EncodePulseFilterUs"].asCString());
    ui->EncodeCountEndFlagLE->setText(m_root["EncoderParams"]["EncodeCountEndFlag"].asCString());
    ui->EncodeCountLE->setText(m_root["EncoderParams"]["EncodeCount"].asCString());
    ui->EncodeTriggerRowCountLE->setText(m_root["EncoderParams"]["EncodeTriggerRowCount"].asCString());
    ui->Encode4FrequencyMultiplierCountLE->setText(m_root["EncoderParams"]["Encode4FrequencyMultiplierCount"].asCString());
    ui->EncodeUnitTimePulseCountLE->setText(m_root["EncoderParams"]["EncodeUnitTimePulseCount"].asCString());
    ui->EncodeCountTimeHalfSecondLE->setText(m_root["EncoderParams"]["EncodeCountTimeHalfSecond"].asCString());
    ui->EncodeChannelLE->setText(m_root["EncoderParams"]["EncodeChannel"].asCString());
    ui->EncodeRevolutionLE->setText(m_root["EncoderParams"]["EncodeRevolution"].asCString());
    ui->RollerPerimeterUmLE->setText(m_root["EncoderParams"]["RollerPerimeterUm"].asCString());
    ui->ExpectSinglePixelAccuracyLE->setText(m_root["EncoderParams"]["ExpectSinglePixelAccuracy"].asCString());
    ui->RollerMaxSpeedToRowCountLE->setText(m_root["EncoderParams"]["RollerMaxSpeedToRowCount"].asCString());
    ui->EveryRowToEncodeCountLE->setText(m_root["EncoderParams"]["EveryRowToEncodeCount"].asCString());
    ui->EncodePressureWheelCountALE->setText(m_root["EncoderParams"]["EncodePressureWheelCountA"].asCString());
    ui->EncodePressureWheelCountBLE->setText(m_root["EncoderParams"]["EncodePressureWheelCountB"].asCString());
    ui->PressureWheel4FrequencyMutliperLE->setText(m_root["EncoderParams"]["PressureWheel4FrequencyMutliper"].asCString());
    ui->PressureEncodecoefficientLE->setText(m_root["EncoderParams"]["PressureEncodecoefficient"].asCString());
    PARAM.setEncodeUnitToDist(m_root["EncoderParams"]["EncodeUnitToDist"].asInt());               // 编码器单位刻度对应距离
    PARAM.setEncodePulseFilterUs(m_root["EncoderParams"]["EncodePulseFilterUs"].asInt());            // 编码脉冲滤波
    PARAM.setEncodeCountEndFlag(m_root["EncoderParams"]["EncodeCountEndFlag"].asInt());             // 编码器计数结束标志
    PARAM.setEncodeCount(m_root["EncoderParams"]["EncodeCount"].asInt());                    // 编码器计数
    PARAM.setEncodeTriggerRowCount(m_root["EncoderParams"]["EncodeTriggerRowCount"].asInt());          // 编码器触发行计数
    PARAM.setEncode4FrequencyMultiplierCount(m_root["EncoderParams"]["Encode4FrequencyMultiplierCount"].asInt()); //编码器4倍频计数
    PARAM.setEncodeUnitTimePulseCount(m_root["EncoderParams"]["EncodeUnitTimePulseCount"].asInt());        //编码器单位时间脉冲计数
    PARAM.setEncodeCountTimeHalfSecond(m_root["EncoderParams"]["EncodeCountTimeHalfSecond"].asInt());       //编码器计数时间0.5s
    PARAM.setEncodeChannel(m_root["EncoderParams"]["EncodeChannel"].asInt());                   //编码通道
    PARAM.setEncodeRevolution(m_root["EncoderParams"]["EncodeRevolution"].asInt());                //编码器转数
    PARAM.setRollerPerimeterUm(m_root["EncoderParams"]["RollerPerimeterUm"].asInt());               //辊道周长
    PARAM.setExpectSinglePixelAccuracy(m_root["EncoderParams"]["ExpectSinglePixelAccuracy"].asInt());       //期望单个像素精度
    PARAM.setRollerMaxSpeedToRowCount(m_root["EncoderParams"]["RollerMaxSpeedToRowCount"].asInt());        //辊道最大速度对应行频
    PARAM.setEveryRowToEncodeCount(m_root["EncoderParams"]["EveryRowToEncodeCount"].asInt());           //每行对应的编码计数
    PARAM.setEncodePressureWheelCountA(m_root["EncoderParams"]["EncodePressureWheelCountA"].asInt());       //压轮编码器计数A
    PARAM.setEncodePressureWheelCountB(m_root["EncoderParams"]["EncodePressureWheelCountB"].asInt());       //压轮编码器计数B
    PARAM.setPressureWheel4FrequencyMutliper(m_root["EncoderParams"]["PressureWheel4FrequencyMutliper"].asInt()); //压轮编码器四倍计数
    PARAM.setPressureEncodecoefficient(m_root["EncoderParams"]["PressureEncodecoefficient"].asInt());       //压轮编码器系数
    //控制器参数
    ui->PixelAccuracyUmLE->setText(m_root["ControllerParams"]["PixelAccuracyUm"].asCString());
    ui->PhotoelectricSignalPulseFilterLE->setText(m_root["ControllerParams"]["PhotoelectricSignalPulseFilter"].asCString());
    ui->CamareTrigerPulseContinueTime10nsLE->setText(m_root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"].asCString());
    ui->PhotoelectricToCamareDistLE->setText(m_root["ControllerParams"]["PhotoelectricToCamareDist"].asCString());
    ui->CamareFrameTrigerDelayRowCountLE->setText( m_root["ControllerParams"]["CamareFrameTrigerDelayRowCount"].asCString());
    ui->FrameSignalContinueTimeLE->setText(m_root["ControllerParams"]["FrameSignalContinueTime"].asCString());
    ui->ModuleEnableSignalLE->setText(m_root["ControllerParams"]["ModuleEnableSignal"].asCString());
    ui->CamarePhotoRowCountLE->setText(m_root["ControllerParams"]["CamarePhotoRowCount"].asCString());
    ui->InnerRowFrequencyLE->setText(m_root["ControllerParams"]["InnerRowFrequency"].asCString());
    ui->PhotoModeLE->setText(m_root["ControllerParams"]["PhotoMode"].asCString());
    ui->PhotoEndDelayRowCountLE->setText(m_root["ControllerParams"]["PhotoEndDelayRowCount"].asCString());
    PARAM.setPixelAccuracyUm(m_root["ControllerParams"]["PixelAccuracyUm"].asInt());                    //像素精度um
    PARAM.setPhotoelectricSignalPulseFilter(m_root["ControllerParams"]["PhotoelectricSignalPulseFilter"].asInt());     //光电信号脉冲滤波
    PARAM.setCamareTrigerPulseContinueTime10ns(m_root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"].asInt());  //相机触发脉冲持续时间10ns
    PARAM.setPhotoelectricToCamareDist(m_root["ControllerParams"]["PhotoelectricToCamareDist"].asInt());          //光电与相机距离行
    PARAM.setCamareFrameTrigerDelayRowCount(m_root["ControllerParams"]["CamareFrameTrigerDelayRowCount"].asInt());     // 相机帧触发延时行数
    PARAM.setFrameSignalContinueTime(m_root["ControllerParams"]["FrameSignalContinueTime"].asInt());            //帧信号持续时间
    PARAM.setModuleEnableSignal(m_root["ControllerParams"]["ModuleEnableSignal"].asInt());                 //模块使能信号
    PARAM.setCamarePhotoRowCount(m_root["ControllerParams"]["CamarePhotoRowCount"].asInt());                //相机拍照行数
    PARAM.setInnerRowFrequency(m_root["ControllerParams"]["InnerRowFrequency"].asInt());                  //内部行频
    PARAM.setPhotoMode(m_root["ControllerParams"]["PhotoMode"].asInt());                          //拍照模式
    PARAM.setPhotoEndDelayRowCount(m_root["ControllerParams"]["PhotoEndDelayRowCount"].asInt());              //拍照延时行数
    //光源控制器参数
    ui->LightField1DelayTimeLE->setText(m_root["LighterParams"]["LightField1DelayTime"].asCString());
    ui->LightField1GlowTimeLE->setText(m_root["LighterParams"]["LightField1GlowTime"].asCString());
    ui->LightField2DelayTimeLE->setText(m_root["LighterParams"]["LightField2DelayTime"].asCString());
    ui->LightField2GlowTimeLE->setText(m_root["LighterParams"]["LightField2GlowTime"].asCString());
    ui->LightField3DelayTimeLE->setText(m_root["LighterParams"]["LightField3DelayTime"].asCString());
    ui->LightField3GlowTimeLE->setText(m_root["LighterParams"]["LightField3GlowTime"].asCString());
    ui->LightField4DelayTimeLE->setText(m_root["LighterParams"]["LightField4DelayTime"].asCString());
    ui->LightField4GlowTimeLE->setText(m_root["LighterParams"]["LightField4GlowTime"].asCString());
    ui->SelectedLightFieldNumberLE->setText(m_root["LighterParams"]["SelectedLightFieldNumber"].asCString());
    ui->HorizontalDarkfieldSelectRegisterLE->setText(m_root["LighterParams"]["HorizontalDarkfieldSelectRegister"].asCString());
    ui->CamareAndLightFieldControlCB->setCurrentIndex(m_root["LighterParams"]["CamareAndLightFieldControl"].asInt());
    ui->SignalSwitchLE->setText(m_root["LighterParams"]["SignalSwitch"].asCString());
    ui->RowSignalSelectedLE->setText(m_root["LighterParams"]["RowSignalSelected"].asCString());
    PARAM.setLightField1DelayTime(m_root["LighterParams"]["LightField1DelayTime"].asInt());            //光场1延时时间10ns
    PARAM.setLightField1GlowTime(m_root["LighterParams"]["LightField1GlowTime"].asInt());             //光场1发光时间10ns
    PARAM.setLightField2DelayTime(m_root["LighterParams"]["LightField2DelayTime"].asInt());            //光场2延时时间10ns
    PARAM.setLightField2GlowTime(m_root["LighterParams"]["LightField2GlowTime"].asInt());             //光场2发光时间10ns
    PARAM.setLightField3DelayTime(m_root["LighterParams"]["LightField3DelayTime"].asInt());            //光场3延时时间10ns
    PARAM.setLightField3GlowTime(m_root["LighterParams"]["LightField3GlowTime"].asInt());             //光场3发光时间10ns
    PARAM.setLightField4DelayTime(m_root["LighterParams"]["LightField4DelayTime"].asInt());            //光场4延时时间10ns
    PARAM.setLightField4GlowTime(m_root["LighterParams"]["LightField4GlowTime"].asInt());             //光场4发光时间10ns
    PARAM.setSelectedLightFieldNumber(m_root["LighterParams"]["SelectedLightFieldNumber"].asInt());        //选择光场数量
    PARAM.setHorizontalDarkfieldSelectRegister(m_root["LighterParams"]["HorizontalDarkfieldSelectRegister"].asInt());  //横向暗场选择寄存器
    PARAM.setCamareAndLightFieldControl(m_root["LighterParams"]["CamareAndLightFieldControl"].asInt());         //相机与光场控制
    PARAM.setSignalSwitch(m_root["LighterParams"]["SignalSwitch"].asInt());                       //信号切换
    PARAM.setRowSignalSelected(m_root["LighterParams"]["RowSignalSelected"].asInt());                  //行信号源选择
    ifs.close();
}

void LightControl::initConnect()
{
    // 工单
    connect(ui->RecipeCB,SIGNAL(currentIndexChanged(int index)), this,SLOT(void slotUpdateRecipe(int index)));
    // 全局设置
    connect(ui->AllSet,SIGNAL(clicked()),this,SLOT(slotAllSet()));
    connect(ui->AllSave,SIGNAL(clicked()),this,SLOT(slotAllSave()));
    connect(ui->CreateRecipe, SIGNAL(clicked()),this,SLOT(slotCreateRecipe()));
    connect(ui->CopyRecipe,SIGNAL(clicked()), this, SLOT(slotCopyRecipe()));
    connect(ui->Trigger,SIGNAL(clicked()), this, SLOT(slotTrigger()));
    // 系统参数界面设置
    connect(ui->SystemNameSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTSystemName()));
    connect(ui->CameraNumSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTCameraNum()));
    connect(ui->Camera0NameSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTCamera0Name()));
    connect(ui->Camera1NameSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTCamera1Name()));
    connect(ui->Camera2NameSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTCamera2Name()));
    connect(ui->Camera3NameSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTCamera3Name()));
    connect(ui->ServerIPSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTServerIP()));
    connect(ui->PortSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTPort()));
    //自定义参数设置
    connect(ui->SaveOriginImageSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTSaveOriginImage()));
    connect(ui->SaveEntireImageSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTSaveEntireImage()));
    connect(ui->SaveFlawImageSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTSaveFlawImage()));
    connect(ui->SaveCropImageSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTSaveCropImage()));
    connect(ui->XYLengthEnableSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTXYLengthEnable()));
    connect(ui->FlawDefectEnableSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTFlawDefectEnable()));
    //缺陷检测参数设置
    connect(ui->Camera12PixelDeviationSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera12PixelDeviation()));
    connect(ui->Camera23PixelDeviationSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera23PixelDeviation()));
    connect(ui->Camera24PixelDeviationSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera24PixelDeviation()));
    connect(ui->SilkToRollerDistSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTSilkToRollerDist()));
    connect(ui->ScratchAreaThresholdSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTScratchAreaThreshold()));
    connect(ui->BubbleStoneAreaThresholdSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTBubbleStoneAreaThreshold()));
    connect(ui->DirtyAreaThresholdSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTDirtyAreaThreshold()));
    //尺寸参数设置
    connect(ui->YAccuracyBSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTYAccuracyB()));
    connect(ui->YAccuracyKSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTYAccuracyK()));
    connect(ui->WidthSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTWidth()));
    connect(ui->WidthDeviationSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTWidthDeviation()));
    connect(ui->DigonalSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTDigonal()));
    connect(ui->Digonal1DeviationSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTDigonal1Deviation()));
    connect(ui->Digonal2SetBT, SIGNAL(clicked()), this, SLOT(slotSetBTDigonal2()));
    connect(ui->Digonal2DeviationSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTDigonal2Deviation()));
    connect(ui->Camera1Pixel0AccuracySetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera1Pixel0Accuracy()));
    connect(ui->Camera1PixelKValueSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera1PixelKValue()));
    connect(ui->Camera21AccuracyRatioSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera21AccuracyRatio()));
    connect(ui->Camera2PixelKValueSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera2PixelKValue()));
    connect(ui->LengthSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTLength()));
    connect(ui->LengthDeviationSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTLengthDeviation()));
    //相机参数设置
    connect(ui->Camera0FrameSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera0Frame()));
    connect(ui->Camera0PhotoRowSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera0PhotoRow()));
    connect(ui->Camera0ExposureTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera0ExposureTime()));
    connect(ui->Camera0GainSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera0Gain()));
    connect(ui->Camera1FrameSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera1Frame()));
    connect(ui->Camera1PhotoRowSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera1PhotoRow()));
    connect(ui->Camera1ExposureTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera1ExposureTime()));
    connect(ui->Camera1GainSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera1Gain()));
    connect(ui->Camera2FrameSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera2Frame()));
    connect(ui->Camera2PhotoRowSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera2PhotoRow()));
    connect(ui->Camera2ExposureTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera2ExposureTime()));
    connect(ui->Camera2GainSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera2Gain()));
    connect(ui->Camera3FrameSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera3Frame()));
    connect(ui->Camera3PhotoRowSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera3PhotoRow()));
    connect(ui->Camera3ExposureTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera3ExposureTime()));
    connect(ui->Camera3GainSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamera3Gain()));
    //编码器参数设置
    connect(ui->EncodeUnitToDistSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncodeUnitToDist()));
    connect(ui->EncodePulseFilterUsSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncodePulseFilterUs()));
    connect(ui->EncodeCountEndFlagSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncodeCountEndFlag()));
    connect(ui->EncodeCountSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncodeCount()));
    connect(ui->EncodeTriggerRowCountSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncodeTriggerRowCount()));
    connect(ui->Encode4FrequencyMultiplierCountSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncode4FrequencyMultiplierCount()));
    connect(ui->EncodeUnitTimePulseCountSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncodeUnitTimePulseCount()));
    connect(ui->EncodeCountTimeHalfSecondSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncodeCountTimeHalfSecond()));
    connect(ui->EncodeChannelSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncodeChannel()));
    connect(ui->EncodeRevolutionSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncodeRevolution()));
    connect(ui->RollerPerimeterUmSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTRollerPerimeterUm()));
    connect(ui->ExpectSinglePixelAccuracySetBT, SIGNAL(clicked()), this, SLOT(slotSetBTExpectSinglePixelAccuracy()));
    connect(ui->RollerMaxSpeedToRowCountSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTRollerMaxSpeedToRowCount()));
    connect(ui->EveryRowToEncodeCountSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEveryRowToEncodeCount()));
    connect(ui->EncodePressureWheelCountASetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncodePressureWheelCountA()));
    connect(ui->EncodePressureWheelCountBSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTEncodePressureWheelCountB()));
    connect(ui->PressureWheel4FrequencyMutliperSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTPressureWheel4FrequencyMutliper()));
    connect(ui->PressureEncodecoefficientSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTPressureEncodecoefficient()));
    //控制器参数设置
    connect(ui->PixelAccuracyUmSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTPixelAccuracyUm()));
    connect(ui->PhotoelectricSignalPulseFilterSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTPhotoelectricSignalPulseFilter()));
    connect(ui->CamareTrigerPulseContinueTime10nsSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamareTrigerPulseContinueTime10ns()));
    connect(ui->PhotoelectricToCamareDistSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTPhotoelectricToCamareDist()));
    connect(ui->CamareFrameTrigerDelayRowCountSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamareFrameTrigerDelayRowCount()));
    connect(ui->FrameSignalContinueTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTFrameSignalContinueTime()));
    connect(ui->ModuleEnableSignalSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTModuleEnableSignal()));
    connect(ui->CamarePhotoRowCountSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamarePhotoRowCount()));
    connect(ui->InnerRowFrequencySetBT, SIGNAL(clicked()), this, SLOT(slotSetBTInnerRowFrequency()));
    connect(ui->PhotoModeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTPhotoMode()));
    connect(ui->PhotoEndDelayRowCountSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTPhotoEndDelayRowCount()));
    //光源控制器参数设置
    connect(ui->LightField1DelayTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTLightField1DelayTime()));
    connect(ui->LightField1GlowTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTLightField1GlowTime()));
    connect(ui->LightField2DelayTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTLightField2DelayTime()));
    connect(ui->LightField2GlowTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTLightField2GlowTime()));
    connect(ui->LightField3DelayTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTLightField3DelayTime()));
    connect(ui->LightField3GlowTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTLightField3GlowTime()));
    connect(ui->LightField4DelayTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTLightField4DelayTime()));
    connect(ui->LightField4GlowTimeSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTLightField4GlowTime()));
    connect(ui->SelectedLightFieldNumberSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTSelectedLightFieldNumber()));
    connect(ui->HorizontalDarkfieldSelectRegisterSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTHorizontalDarkfieldSelectRegister()));
    connect(ui->CamareAndLightFieldControlSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTCamareAndLightFieldControl()));
    connect(ui->SignalSwitchSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTSignalSwitch()));
    connect(ui->RowSignalSelectedSetBT, SIGNAL(clicked()), this, SLOT(slotSetBTRowSignalSelected()));
}

void LightControl::slotUpdateRecipe(int index)
{
    if (index < ui->RecipeCB->count()) {
        QString fileName = ui->RecipeCB->itemText(index);
        LightControl::readRecipeToTable(fileName.toStdString());
    } else {
        INFOMATION.criticalMessageBox(this, "Update Recipe index is error !!!");
    }
}

void LightControl::slotAllSet()
{
    m_pSig_comm.SetRegs(ADDR0, ADDR0, &sigctrl->temp0);
    m_pSig_comm.SetRegs(ADDR1, ADDR1, &sigctrl->temp1);
    m_pSig_comm.SetRegs(ADDR7, ADDR7, &sigctrl->temp7);
    m_pSig_comm.SetRegs(ADDR8, ADDR8, &sigctrl->temp8);
    m_pSig_comm.SetRegs(ADDR9, ADDR9, &sigctrl->temp9);
    m_pSig_comm.SetRegs(ADDR10, ADDR10, &sigctrl->temp10);
    m_pSig_comm.SetRegs(ADDR11, ADDR11, &sigctrl->temp11);
    m_pSig_comm.SetRegs(ADDR12, ADDR12, &sigctrl->temp12);
    m_pSig_comm.SetRegs(ADDR14, ADDR14, &sigctrl->temp14);
    m_pSig_comm.SetRegs(ADDR15, ADDR15, &sigctrl->temp15);
    m_pSig_comm.SetRegs(ADDR16, ADDR16, &sigctrl->temp16);
    m_pSig_comm.SetRegs(ADDR17, ADDR17, &sigctrl->temp17);
    m_pSig_comm.SetRegs(ADDR18, ADDR18, &sigctrl->temp18);
    m_pSig_comm.SetRegs(ADDR19, ADDR19, &sigctrl->temp19);
    m_pSig_comm.SetRegs(ADDR20, ADDR20, &sigctrl->temp20);
    m_pSig_comm.SetRegs(ADDR21, ADDR21, &sigctrl->temp21);
    m_pSig_comm.SetRegs(ADDR22, ADDR22, &sigctrl->temp22);
    m_pSig_comm.SetRegs(ADDR23, ADDR23, &sigctrl->temp23);
    m_pSig_comm.SetRegs(ADDR24, ADDR24, &sigctrl->temp24);
    m_pSig_comm.SetRegs(ADDR25, ADDR25, &sigctrl->temp25);
    m_pSig_comm.SetRegs(ADDR26, ADDR26, &sigctrl->temp26);
    m_pSig_comm.SetRegs(ADDR27, ADDR27, &sigctrl->temp27);
    m_pSig_comm.SetRegs(ADDR28, ADDR28, &sigctrl->temp28);
    m_pSig_comm.SetRegs(ADDR29, ADDR29, &sigctrl->temp29);
    m_pSig_comm.SetRegs(ADDR30, ADDR30, &sigctrl->temp30);
    m_pSig_comm.SetRegs(ADDR31, ADDR31, &sigctrl->temp31);
    m_pSig_comm.SetRegs(ADDR32, ADDR32, &sigctrl->temp32);
    m_pSig_comm.SetRegs(ADDR33, ADDR33, &sigctrl->temp33);
    m_pSig_comm.SetRegs(ADDR34, ADDR34, &sigctrl->temp34);
    m_pSig_comm.SetRegs(ADDR35, ADDR35, &sigctrl->temp35);
    m_pSig_comm.SetRegs(ADDR36, ADDR36, &sigctrl->temp36);
    m_pSig_comm.SetRegs(ADDR37, ADDR37, &sigctrl->temp37);
    m_pSig_comm.SetRegs(ADDR43, ADDR43, &sigctrl->temp43);
    m_pSig_comm.SetRegs(ADDR44, ADDR44, &sigctrl->temp44);
    m_pSig_comm.SetRegs(ADDR45, ADDR45, &sigctrl->temp45);
    m_pSig_comm.SetRegs(ADDR46, ADDR46, &sigctrl->temp46);
    m_pSig_comm.SetRegs(ADDR47, ADDR47, &sigctrl->temp47);
    m_pSig_comm.SetRegs(ADDR48, ADDR48, &sigctrl->temp48);
    m_pSig_comm.SetRegs(ADDR49, ADDR49, &sigctrl->temp49);
    m_pSig_comm.SetRegs(ADDR50, ADDR50, &sigctrl->temp50);
    m_pSig_comm.SetRegs(ADDR51, ADDR51, &sigctrl->temp51);
    m_pSig_comm.SetRegs(ADDR52, ADDR52, &sigctrl->temp52);
    m_pSig_comm.SetRegs(ADDR53, ADDR53, &sigctrl->temp53);
    m_pSig_comm.SetRegs(ADDR54, ADDR54, &sigctrl->temp54);
    m_pSig_comm.SetRegs(ADDR55, ADDR55, &sigctrl->temp55);
    m_pSig_comm.SetRegs(ADDR56, ADDR56, &sigctrl->temp56);
    m_pSig_comm.SetRegs(ADDR59, ADDR59, &sigctrl->tempAutoPhoto);
    int ret = m_pSig_comm.SetRegs(ADDR60, ADDR60, &sigctrl->tempPhotoEndDelayLine);
    qDebug()<<ret;
}

void LightControl::slotAllSave()
{
    QString filename = ui->RecipeCB->currentText();
    LightControl::writeTableToRecipe(filename);
}

// 写入当前表单数据到工单文件中
void LightControl::writeTableToRecipe(QString filename)
{
    //Json::Value root;
    Json::FastWriter writer;
    { //系统参数
        m_root["SystemParams"]["SystemName"] = ui->SystemNameLE->text().toStdString().data();
        m_root["SystemParams"]["CamareNumber"] = ui->CameraNumLE->text().toStdString().data();
        m_root["SystemParams"]["Camare0Name"] = ui->Camera0NameLE->text().toStdString().data();
        m_root["SystemParams"]["Camare1Name"] = ui->Camera1NameLE->text().toStdString().data();
        m_root["SystemParams"]["Camare2Name"] = ui->Camera2NameLE->text().toStdString().data();
        m_root["SystemParams"]["Camare3Name"] = ui->Camera3NameLE->text().toStdString().data();
        m_root["SystemParams"]["ServerIP"] = ui->ServerIPLE->text().toStdString().data();
        m_root["SystemParams"]["ServerPort"] = ui->PortLE->text().toStdString().data();
    }
    { //自定义参数
       m_root["CustomParams"]["SaveOriginImage"] = QString::number(ui->SaveOriginImageCB->currentIndex()).toStdString().data();
       m_root["CustomParams"]["SaveEntireImage"] = QString::number(ui->SaveEntireImageCB->currentIndex()).toStdString().data();
       m_root["CustomParams"]["SaveFlawImage"] = QString::number(ui->SaveFlawImageCB->currentIndex()).toStdString().data();
       m_root["CustomParams"]["SaveCropImage"] = QString::number(ui->SaveCropImageCB->currentIndex()).toStdString().data();
       m_root["CustomParams"]["XYLengthEnable"] = QString::number(ui->XYLengthEnableCB->currentIndex()).toStdString().data();
       m_root["CustomParams"]["FlawDefectEnable"] = QString::number(ui->FlawDefectEnableCB->currentIndex()).toStdString().data();
    }
    { //缺陷检测
       m_root["DefectDetectionParams"]["Camera12PixelDeviation"] = ui->Camera12PixelDeviationLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["Camera23PixelDeviation"] = ui->Camera23PixelDeviationLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["Camera24PixelDeviation"] = ui->Camera24PixelDeviationLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["SilkToRollerDist"] = ui->SilkToRollerDistLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["ScratchAreaThreshold"] = ui->ScratchAreaThresholdLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["BubbleStoneAreaThreshold"] = ui->BubbleStoneAreaThresholdLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["DirtyAreaThreshold"] = ui->DirtyAreaThresholdLE->text().toStdString().data();
    }
    { //尺寸测量
       m_root["DimensionalMeasurementParams"]["YAccuracyB"] = ui->YAccuracyBLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["YAccuracyK"] = ui->YAccuracyKLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Width"] = ui->WidthLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["WidthDeviation"] = ui->WidthDeviationLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Digonal1"] = ui->Digonal1LE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Digonal1Deviation"] = ui->Digonal1DeviationLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Diagonal2"] = ui->Digonal2LE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Digonal2Deviation"] = ui->Digonal2DeviationLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Camera1Pixel0Accuracy"] = ui->Camera1Pixel0AccuracyLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Camera1PixelKValue"] = ui->Camera1PixelKValueLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Camera21AccuracyRatio"] = ui->Camera21AccuracyRatioLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Camera2PixelKValue"] = ui->Camera2PixelKValueLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Length"] = ui->LengthLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["LengthDeviation"] = ui->LengthDeviationLE->text().toStdString().data();
    }
    {//相机参数
        m_root["CamareParams"]["Camera0Frame"] = ui->Camera0FrameLE->text().toStdString().data();
        m_root["CamareParams"]["Camera0PhotoRow"] = ui->Camera0PhotoRowLE->text().toStdString().data();
        m_root["CamareParams"]["Camera0ExposureTime"] = ui->Camera0ExposureTimeLE->text().toStdString().data();
        m_root["CamareParams"]["Camera0Gain"] = ui->Camera0GainLE->text().toStdString().data();
        m_root["CamareParams"]["Camera1Frame"] = ui->Camera1FrameLE->text().toStdString().data();
        m_root["CamareParams"]["Camera1PhotoRow"] = ui->Camera1PhotoRowLE->text().toStdString().data();
        m_root["CamareParams"]["Camera1ExposureTime"] = ui->Camera1ExposureTimeLE->text().toStdString().data();
        m_root["CamareParams"]["Camera1Gain"] = ui->Camera1GainLE->text().toStdString().data();
        m_root["CamareParams"]["Camera2Frame"] = ui->Camera2FrameLE->text().toStdString().data();
        m_root["CamareParams"]["Camera2PhotoRow"] = ui->Camera2PhotoRowLE->text().toStdString().data();
        m_root["CamareParams"]["Camera2ExposureTime"] = ui->Camera2ExposureTimeLE->text().toStdString().data();
        m_root["CamareParams"]["Camera2Gain"] = ui->Camera2GainLE->text().toStdString().data();
        m_root["CamareParams"]["Camera3Frame"] = ui->Camera3FrameLE->text().toStdString().data();
        m_root["CamareParams"]["Camera3PhotoRow"] = ui->Camera3PhotoRowLE->text().toStdString().data();
        m_root["CamareParams"]["Camera3ExposureTime"] = ui->Camera3ExposureTimeLE->text().toStdString().data();
        m_root["CamareParams"]["Camera3Gain"] = ui->Camera3GainLE->text().toStdString().data();
    }
    {//编码器参数
        m_root["EncoderParams"]["EncodeUnitToDist"] = ui->EncodeUnitToDistLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodePulseFilterUs"] = ui->EncodePulseFilterUsLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeCountEndFlag"] = ui->EncodeCountEndFlagLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeCount"] = ui->EncodeCountLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeTriggerRowCount"] = ui->EncodeTriggerRowCountLE->text().toStdString().data();
        m_root["EncoderParams"]["Encode4FrequencyMultiplierCount"] = ui->Encode4FrequencyMultiplierCountLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeUnitTimePulseCount"] = ui->EncodeUnitTimePulseCountLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeCountTimeHalfSecond"] = ui->EncodeCountTimeHalfSecondLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeChannel"] = ui->EncodeChannelLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeRevolution"] = ui->EncodeRevolutionLE->text().toStdString().data();
        m_root["EncoderParams"]["RollerPerimeterUm"] = ui->RollerPerimeterUmLE->text().toStdString().data();
        m_root["EncoderParams"]["ExpectSinglePixelAccuracy"] = ui->ExpectSinglePixelAccuracyLE->text().toStdString().data();
        m_root["EncoderParams"]["RollerMaxSpeedToRowCount"] = ui->RollerMaxSpeedToRowCountLE->text().toStdString().data();
        m_root["EncoderParams"]["EveryRowToEncodeCount"] = ui->EveryRowToEncodeCountLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodePressureWheelCountA"] = ui->EncodePressureWheelCountALE->text().toStdString().data();
        m_root["EncoderParams"]["EncodePressureWheelCountB"] = ui->EncodePressureWheelCountBLE->text().toStdString().data();
        m_root["EncoderParams"]["PressureWheel4FrequencyMutliper"] = ui->PressureWheel4FrequencyMutliperLE->text().toStdString().data();
        m_root["EncoderParams"]["PressureEncodecoefficient"] = ui->PressureEncodecoefficientLE->text().toStdString().data();
    }
    {//控制器参数
        m_root["ControllerParams"]["PixelAccuracyUm"] = ui->PixelAccuracyUmLE->text().toStdString().data();
        m_root["ControllerParams"]["PhotoelectricSignalPulseFilter"] = ui->PhotoelectricSignalPulseFilterLE->text().toStdString().data();
        m_root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"] = ui->CamareTrigerPulseContinueTime10nsLE->text().toStdString().data();
        m_root["ControllerParams"]["PhotoelectricToCamareDist"] = ui->PhotoelectricToCamareDistLE->text().toStdString().data();
        m_root["ControllerParams"]["CamareFrameTrigerDelayRowCount"] = ui->CamareFrameTrigerDelayRowCountLE->text().toStdString().data();
        m_root["ControllerParams"]["FrameSignalContinueTime"] = ui->FrameSignalContinueTimeLE->text().toStdString().data();
        m_root["ControllerParams"]["ModuleEnableSignal"] = ui->ModuleEnableSignalLE->text().toStdString().data();
        m_root["ControllerParams"]["CamarePhotoRowCount"] = ui->CamarePhotoRowCountLE->text().toStdString().data();
        m_root["ControllerParams"]["InnerRowFrequency"] = ui->InnerRowFrequencyLE->text().toStdString().data();
        m_root["ControllerParams"]["PhotoMode"] = ui->PhotoModeLE->text().toStdString().data();
        m_root["ControllerParams"]["PhotoEndDelayRowCount"] = ui->PhotoEndDelayRowCountLE->text().toStdString().data();
    }
    {//光源控制器参数
        m_root["LighterParams"]["LightField1DelayTime"] = ui->LightField1DelayTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField1GlowTime"] = ui->LightField1GlowTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField2DelayTime"] = ui->LightField2DelayTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField2GlowTime"] = ui->LightField2GlowTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField3DelayTime"] = ui->LightField3DelayTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField3GlowTime"] = ui->LightField3GlowTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField4DelayTime"] = ui->LightField4DelayTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField4GlowTime"] = ui->LightField4GlowTimeLE->text().toStdString().data();
        m_root["LighterParams"]["SelectedLightFieldNumber"] = ui->SelectedLightFieldNumberLE->text().toStdString().data();
        m_root["LighterParams"]["HorizontalDarkfieldSelectRegister"] = ui->HorizontalDarkfieldSelectRegisterLE->text().toStdString().data();
        m_root["LighterParams"]["CamareAndLightFieldControl"] = QString::number(ui->CamareAndLightFieldControlCB->currentIndex()).toStdString().data();
        m_root["LighterParams"]["SignalSwitch"] = ui->SignalSwitchLE->text().toStdString().data();
        m_root["LighterParams"]["RowSignalSelected"] = ui->RowSignalSelectedLE->text().toStdString().data();
    }
    std::string json_content = writer.write(m_root);
    std::ofstream ofs;
    ofs.open(filename.toStdString().data());
    if (ofs.is_open()) {
        ofs<<json_content;
        ofs.close();
    }
}

void LightControl::writeCurrentRooterToJson()
{
    Json::FastWriter writer;
    QString filename = ui->RecipeCB->currentText();
    std::string json_content = writer.write(m_root);
    std::ofstream ofs;
    ofs.open(filename.toStdString().data());
    if (ofs.is_open()) {
        ofs<<json_content;
        ofs.close();
    }
}

//新建工单
void LightControl::slotCreateRecipe()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
    QString defaultRecipeFileName = current_date + QString(".json");
    QString newRecipeFileName = INFOMATION.inputMessageBox(this,"新建工单","请输入新建工单名称",defaultRecipeFileName);
    LightControl::createNewRecipeFile(newRecipeFileName);
}

//拷贝工单
void LightControl::slotCopyRecipe()
{
    QString currentFileName = ui->RecipeCB->currentText();
    QString copyName = "copy_" + currentFileName;
    LightControl::writeTableToRecipe(copyName);
}

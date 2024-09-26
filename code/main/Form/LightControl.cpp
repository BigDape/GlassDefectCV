#include "LightControl.h"
#include "ui_LightControl.h"
#include <QTimer>
#include <cmath>
#include <iostream>
#include <fstream>
#include <QDir>
#include "Global.h"
#include "jsoncpp.h"
#include "HsListener.h"
#include "HSSocketInterface.h"

#pragma execution_character_set("utf-8")

LightControl::LightControl( QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::LightControl)
{
    ui->setupUi(this);
    // 初始化输入框类型
    LightControl::initLineEditInputType();
    // connect按键绑定
    connect(ui->AllSet,SIGNAL(clicked()),this,SLOT(slotAllSet()));              // 下发
    connect(ui->AllGet,SIGNAL(clicked()),this,SLOT(slotAllGet()));              // 获取
    connect(ui->AllSave,SIGNAL(clicked()),this,SLOT(slotAllSave()));            // 保存
    connect(ui->CreateRecipe,SIGNAL(clicked()),this, SLOT(slotCreateRecipe())); // 创建工单
    connect(ui->TestConnectBT,SIGNAL(clicked()), this, SLOT(slotTestConnect()));// 测试连接
    connect(ui->Trigger,SIGNAL(clicked()), this, SLOT(slotTrigger()));          // 触发
    connect(ui->RecipeCB, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeRecipe(int)));// 切换工单

    // 加载当前的工单
    // 读取工单参数，给每个输入框赋值
    LightControl::InitLightControl();
    // 获取通讯处理模块
    SocketObjectPtr = SocketNameSpace::createSocketObject();
    SocketObjectPtr->InitRegs(m_signalctrl,m_signalctrl.ServerIP,m_signalctrl.ServerPort);
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



bool LightControl::InitLightControl()
{
    QString needLoadJsonFile = PARAM.GetParamterFromIniFile(SYSTEM_PATH,"recipe");//需要加载的工单名称recipe=8nm.json
    QDir dir(RECIPE_FULLPATH);
    QFileInfoList fileList = dir.entryInfoList(QStringList() << "*.json");
    if (fileList.size() == 0) { //没有找到任何json工单
        QString current_date = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
        QString recipeFileName = current_date + QString(".json");
        Jsoncpp::GetInstance()->writeEmptyRecipeToJson(recipeFileName);  //创建空白名单
        LightControl::readRecipeToTable(recipeFileName.toStdString());
        ui->RecipeCB->addItem(recipeFileName);
        ui->RecipeCB->setCurrentText(recipeFileName);
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
//            INFOMATION.criticalMessageBox(this,message);
            return false;
        } else {
            ui->RecipeCB->setCurrentText(needLoadJsonFile);
            LightControl::readRecipeToTable(needLoadJsonFile.toStdString());
            return true;
        }
    }
}

// 读取json工单到表单中
void LightControl::readRecipeToTable(std::string filePath)
{
    Jsoncpp::GetInstance()->readRecipeFromJson(QString(filePath.c_str()), m_signalctrl);
    //系统参数
    ui->SystemNameLE->setText(m_signalctrl.systemName);
    ui->CameraNumLE->setText(QString::number(m_signalctrl.CamareNumber));
    ui->Camera0NameLE->setText(m_signalctrl.Camare0Name);
    ui->Camera1NameLE->setText(m_signalctrl.Camare1Name);
    ui->Camera2NameLE->setText(m_signalctrl.Camare2Name);
    ui->Camera3NameLE->setText(m_signalctrl.Camare3Name);
    ui->ServerIPLE->setText(m_signalctrl.ServerIP);
    ui->PortLE->setText(QString::number(m_signalctrl.ServerPort));
    //自定义参数
    ui->SaveOriginImageCB->setCurrentIndex(m_signalctrl.SaveOriginImage);
    ui->SaveEntireImageCB->setCurrentIndex(m_signalctrl.SaveEntireImage);
    ui->SaveFlawImageCB->setCurrentIndex(m_signalctrl.SaveFlawImage);
    ui->SaveCropImageCB->setCurrentIndex(m_signalctrl.SaveCropImage);
    ui->XYLengthEnableCB->setCurrentIndex(m_signalctrl.XYLengthEnable);
    ui->FlawDefectEnableCB->setCurrentIndex(m_signalctrl.FlawDefectEnable);
    //缺陷检测
    ui->Camera12PixelDeviationLE->setText(QString::number(m_signalctrl.Camera12PixelDeviation));
    ui->Camera23PixelDeviationLE->setText(QString::number(m_signalctrl.Camera23PixelDeviation));
    ui->Camera24PixelDeviationLE->setText(QString::number(m_signalctrl.Camera24PixelDeviation));
    ui->SilkToRollerDistLE->setText(QString::number(m_signalctrl.SilkToRollerDist));
    ui->ScratchAreaThresholdLE->setText(QString::number(m_signalctrl.ScratchAreaThreshold));
    ui->BubbleStoneAreaThresholdLE->setText(QString::number(m_signalctrl.BubbleStoneAreaThreshold));
    ui->DirtyAreaThresholdLE->setText(QString::number(m_signalctrl.DirtyAreaThreshold));
    //尺寸测量
    ui->YAccuracyBLE->setText(QString::number(m_signalctrl.YAccuracyB));
    ui->YAccuracyKLE->setText(QString::number(m_signalctrl.YAccuracyK));
    ui->WidthLE->setText(QString::number(m_signalctrl.Width));
    ui->WidthDeviationLE->setText(QString::number(m_signalctrl.WidthDeviation));
    ui->Digonal1LE->setText(QString::number(m_signalctrl.Digonal1));
    ui->Digonal1DeviationLE->setText(QString::number(m_signalctrl.Digonal1Deviation));
    ui->Digonal2LE->setText(QString::number(m_signalctrl.Diagonal2));
    ui->Digonal2DeviationLE->setText(QString::number(m_signalctrl.Digonal2Deviation));
    ui->Camera1Pixel0AccuracyLE->setText(QString::number(m_signalctrl.Camera1Pixel0Accuracy));
    ui->Camera1PixelKValueLE->setText(QString::number(m_signalctrl.Camera1PixelKValue));
    ui->Camera21AccuracyRatioLE->setText(QString::number(m_signalctrl.Camera21AccuracyRatio));
    ui->Camera2PixelKValueLE->setText(QString::number(m_signalctrl.Camera2PixelKValue));
    ui->LengthLE->setText(QString::number(m_signalctrl.Length));
    ui->LengthDeviationLE->setText(QString::number(m_signalctrl.LengthDeviation));
    //相机参数
    ui->Camera0FrameLE->setText(QString::number(m_signalctrl.Camera0Frame));
    ui->Camera0PhotoRowLE->setText(QString::number(m_signalctrl.Camera0PhotoRow));
    ui->Camera0ExposureTimeLE->setText(QString::number(m_signalctrl.Camera0ExposureTime));
    ui->Camera0GainLE->setText(QString::number(m_signalctrl.Camera0Gain));
    ui->Camera1FrameLE->setText(QString::number(m_signalctrl.Camera1Frame));
    ui->Camera1PhotoRowLE->setText(QString::number(m_signalctrl.Camera1PhotoRow));
    ui->Camera1ExposureTimeLE->setText(QString::number(m_signalctrl.Camera1ExposureTime));
    ui->Camera1GainLE->setText(QString::number(m_signalctrl.Camera1Gain));
    ui->Camera2FrameLE->setText(QString::number(m_signalctrl.Camera2Frame));
    ui->Camera2PhotoRowLE->setText(QString::number(m_signalctrl.Camera2PhotoRow));
    ui->Camera2ExposureTimeLE->setText(QString::number(m_signalctrl.Camera2ExposureTime));
    ui->Camera2GainLE->setText(QString::number(m_signalctrl.Camera2Gain));
    ui->Camera3FrameLE->setText(QString::number(m_signalctrl.Camera3Frame));
    ui->Camera3PhotoRowLE->setText(QString::number(m_signalctrl.Camera3PhotoRow));
    ui->Camera3ExposureTimeLE->setText(QString::number(m_signalctrl.Camera3ExposureTime));
    ui->Camera3GainLE->setText(QString::number(m_signalctrl.Camera3Gain));
    //编码器参数
    ui->EncodeUnitToDistLE->setText(QString::number(m_signalctrl.temp0));
    ui->EncodePulseFilterUsLE->setText(QString::number(m_signalctrl.temp1));
    ui->EncodeRevolutionLE->setText(QString::number(m_signalctrl.temp9));
    ui->RollerPerimeterUmLE->setText(QString::number(m_signalctrl.temp10));
    ui->ExpectSinglePixelAccuracyLE->setText(QString::number(m_signalctrl.temp11));
    ui->RollerMaxSpeedToRowCountLE->setText(QString::number(m_signalctrl.temp12));
    ui->EveryRowToEncodeCountLE->setText(QString::number(m_signalctrl.temp13));
    //控制器参数
    ui->PixelAccuracyUmLE->setText(QString::number(m_signalctrl.temp14));
    ui->PhotoelectricSignalPulseFilterLE->setText(QString::number(m_signalctrl.temp15));
    ui->CamareTrigerPulseContinueTime10nsLE->setText(QString::number(m_signalctrl.temp16));
    ui->PhotoelectricToCamareDistLE->setText(QString::number(m_signalctrl.temp17));
    ui->CamareFrameTrigerDelayRowCountLE->setText( QString::number(m_signalctrl.temp18));
    ui->FrameSignalContinueTimeLE->setText(QString::number(m_signalctrl.temp19));
    ui->ModuleEnableSignalLE->setText(QString::number(m_signalctrl.temp20));
    ui->CamarePhotoRowCountLE->setText(QString::number(m_signalctrl.temp21));
    ui->InnerRowFrequencyLE->setText(QString::number(m_signalctrl.temp22));
    ui->PhotoModeLE->setText(QString::number(m_signalctrl.tempAutoPhoto));
    ui->PhotoEndDelayRowCountLE->setText(QString::number(m_signalctrl.tempPhotoEndDelayLine));
    //光源控制器参数
    ui->LightField1DelayTimeLE->setText(QString::number(m_signalctrl.temp23));
    ui->LightField1GlowTimeLE->setText(QString::number(m_signalctrl.temp24));
    ui->LightField2DelayTimeLE->setText(QString::number(m_signalctrl.temp25));
    ui->LightField2GlowTimeLE->setText(QString::number(m_signalctrl.temp26));
    ui->LightField3DelayTimeLE->setText(QString::number(m_signalctrl.temp27));
    ui->LightField3GlowTimeLE->setText(QString::number(m_signalctrl.temp28));
    ui->LightField4DelayTimeLE->setText(QString::number(m_signalctrl.temp29));
    ui->LightField4GlowTimeLE->setText(QString::number(m_signalctrl.temp30));
    ui->SelectedLightFieldNumberLE->setText(QString::number(m_signalctrl.temp55));
    ui->HorizontalDarkfieldSelectRegisterLE->setText(QString::number(m_signalctrl.temp56));
    ui->CamareAndLightFieldControlCB->setCurrentIndex(m_signalctrl.temp35);
    ui->SignalSwitchLE->setText(QString::number(m_signalctrl.temp36));
    ui->RowSignalSelectedLE->setText(QString::number(m_signalctrl.temp37));

    PARAM.SystemName = m_signalctrl.systemName;
    PARAM.camDefineNum = m_signalctrl.CamareNumber;
    PARAM.Camera0Name = m_signalctrl.Camare0Name;
    PARAM.Camera1Name = m_signalctrl.Camare1Name;
    PARAM.Camera2Name = m_signalctrl.Camare2Name;
    PARAM.Camera3Name = m_signalctrl.Camare3Name;
    PARAM.serverIp = m_signalctrl.ServerIP;
    PARAM.serverPort = m_signalctrl.ServerPort;
    PARAM.isSaveOriginImage = m_signalctrl.SaveOriginImage;
    PARAM.isSaveEntireImage = m_signalctrl.SaveEntireImage;
    PARAM.isSaveFlawImage = m_signalctrl.SaveFlawImage;
    PARAM.isSaveCropImage = m_signalctrl.SaveCropImage;
    PARAM.XYLengthEnable = m_signalctrl.XYLengthEnable;
    PARAM.FlawDefectEnable = m_signalctrl.FlawDefectEnable;
    PARAM.Camera12PixelDeviation = m_signalctrl.Camera12PixelDeviation;
    PARAM.Camera23PixelDeviation = m_signalctrl.Camera23PixelDeviation;
    PARAM.Camera24PixelDeviation = m_signalctrl.Camera24PixelDeviation;
    PARAM.SilkToRollerDist = m_signalctrl.SilkToRollerDist;
    PARAM.ScratchAreaThreshold = m_signalctrl.ScratchAreaThreshold;
    PARAM.BubbleStoneAreaThreshold = m_signalctrl.BubbleStoneAreaThreshold;
    PARAM.DirtyAreaThreshold = m_signalctrl.DirtyAreaThreshold;
    PARAM.YAccuracyB = m_signalctrl.YAccuracyB;
    PARAM.YAccuracyK = m_signalctrl.YAccuracyK;
    PARAM.Width = m_signalctrl.Width;
    PARAM.WidthDeviation = m_signalctrl.WidthDeviation;
    PARAM.Digonal = m_signalctrl.Digonal1;
    PARAM.Digonal1Deviation = m_signalctrl.Digonal1Deviation;
    PARAM.Digonal2 = m_signalctrl.Diagonal2;
    PARAM.Digonal2Deviation = m_signalctrl.Digonal2Deviation;
    PARAM.Camera1Pixel0Accuracy = m_signalctrl.Camera1Pixel0Accuracy;
    PARAM.Camera1PixelKValue = m_signalctrl.Camera1PixelKValue;
    PARAM.Camera21AccuracyRatio = m_signalctrl.Camera21AccuracyRatio;
    PARAM.Camera2PixelKValue = m_signalctrl.Camera2PixelKValue;
    PARAM.Length = m_signalctrl.Length;
    PARAM.LengthDeviation = m_signalctrl.LengthDeviation;
    PARAM.Camera0Frame = m_signalctrl.Camera0Frame;
    PARAM.Camera0PhotoRow = m_signalctrl.Camera0PhotoRow;
    PARAM.Camera0ExposureTime = m_signalctrl.Camera0ExposureTime;
    PARAM.Camera0Gain = m_signalctrl.Camera0Gain;
    PARAM.Camera1Frame = m_signalctrl.Camera1Frame;
    PARAM.Camera1PhotoRow = m_signalctrl.Camera1PhotoRow;
    PARAM.Camera1ExposureTime = m_signalctrl.Camera1ExposureTime;
    PARAM.Camera1Gain = m_signalctrl.Camera1Gain;
    PARAM.Camera2Frame = m_signalctrl.Camera2Frame;
    PARAM.Camera2PhotoRow = m_signalctrl.Camera2PhotoRow;
    PARAM.Camera2ExposureTime = m_signalctrl.Camera2ExposureTime;
    PARAM.Camera2Gain = m_signalctrl.Camera2Gain;
    PARAM.Camera3Frame = m_signalctrl.Camera3Frame;
    PARAM.Camera3PhotoRow = m_signalctrl.Camera3PhotoRow;
    PARAM.Camera3ExposureTime = m_signalctrl.Camera3ExposureTime;
    PARAM.Camera3Gain = m_signalctrl.Camera3Gain;
    PARAM.EncodeUnitToDist = m_signalctrl.temp0;               // 编码器单位刻度对应距离
    PARAM.EncodePulseFilterUs = m_signalctrl.temp1;            // 编码脉冲滤
    PARAM.EncodeRevolution = m_signalctrl.temp9;                //编码器转数
    PARAM.RollerPerimeterUm = m_signalctrl.temp10;               //辊道周长
    PARAM.ExpectSinglePixelAccuracy = m_signalctrl.temp11;       //期望单个像素精度
    PARAM.RollerMaxSpeedToRowCount = m_signalctrl.temp12;        //辊道最大速度对应行频
    PARAM.EveryRowToEncodeCount = m_signalctrl.temp13;           //每行对应的编码计数
    PARAM.PixelAccuracyUm = m_signalctrl.temp14;                    //像素精度um
    PARAM.PhotoelectricSignalPulseFilter = m_signalctrl.temp15;     //光电信号脉冲滤波
    PARAM.CamareTrigerPulseContinueTime10ns = m_signalctrl.temp16;  //相机触发脉冲持续时间10ns
    PARAM.PhotoelectricToCamareDist = m_signalctrl.temp17;          //光电与相机距离行
    PARAM.CamareFrameTrigerDelayRowCount = m_signalctrl.temp18;     // 相机帧触发延时行数
    PARAM.FrameSignalContinueTime = m_signalctrl.temp19;            //帧信号持续时间
    PARAM.ModuleEnableSignal = m_signalctrl.temp20;                 //模块使能信号
    PARAM.CamarePhotoRowCount = m_signalctrl.temp21;                //相机拍照行数
    PARAM.InnerRowFrequency = m_signalctrl.temp22;                  //内部行频
    PARAM.PhotoMode = m_signalctrl.tempAutoPhoto;                          //拍照模式
    PARAM.PhotoEndDelayRowCount = m_signalctrl.tempPhotoEndDelayLine;              //拍照延时行数
    PARAM.LightField1DelayTime = m_signalctrl.temp23;            //光场1延时时间10ns
    PARAM.LightField1GlowTime = m_signalctrl.temp24;             //光场1发光时间10ns
    PARAM.LightField2DelayTime = m_signalctrl.temp25;            //光场2延时时间10ns
    PARAM.LightField2GlowTime = m_signalctrl.temp26;             //光场2发光时间10ns
    PARAM.LightField3DelayTime = m_signalctrl.temp27;            //光场3延时时间10ns
    PARAM.LightField3GlowTime= m_signalctrl.temp28;             //光场3发光时间10ns
    PARAM.LightField4DelayTime= m_signalctrl.temp29;            //光场4延时时间10ns
    PARAM.LightField4GlowTime= m_signalctrl.temp30;             //光场4发光时间10ns
    PARAM.SelectedLightFieldNumber = m_signalctrl.temp55;        //选择光场数量
    PARAM.HorizontalDarkfieldSelectRegister = m_signalctrl.temp56;  //横向暗场选择寄存器
    PARAM.CamareAndLightFieldControl = m_signalctrl.temp35;         //相机与光场控制
    PARAM.SignalSwitch = m_signalctrl.temp36;                       //信号切换
    PARAM.RowSignalSelected = m_signalctrl.temp37;                  //行信号源选择
}

// 全部数据下发
void LightControl::slotAllSet()
{
    SocketObjectPtr->SetAllRegs(m_signalctrl);
}

void LightControl::slotAllSave()
{
    QString filename = ui->RecipeCB->currentText();
    QString dirPath = QDir::currentPath() + QString(RECIPE_FULLPATH) + "/" +filename;
    Jsoncpp::GetInstance()->writeRecipeToJson(dirPath,m_signalctrl);
}

//新建工单
void LightControl::slotCreateRecipe()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
    QString defaultRecipeFileName = current_date + QString(".json");
    QString newRecipeFileName = INFOMATION.inputMessageBox(this,"新建工单","请输入新建工单名称",defaultRecipeFileName);
    //
    // 处理逻辑：将当前的json文件重新复制一份且重命名。
    //
    QString sourceFilePath = ui->RecipeCB->currentText();
    QString destinationFilePath = newRecipeFileName;
    QFile sourceFile(sourceFilePath);
    QFile destinationFile(destinationFilePath);

    if (sourceFile.open(QIODevice::ReadOnly)) {
        if (destinationFile.open(QIODevice::WriteOnly)) {
            destinationFile.write(sourceFile.readAll());
            destinationFile.close();
        } else {
            qDebug() << "Failed to open destination file for writing.";
        }
        sourceFile.close();
    } else {
        qDebug() << "Failed to open source file for reading.";
    }
}

void LightControl::slotAllGet()
{
    SocketObjectPtr->GetAllData(m_signalctrl);
}

void LightControl::slotTestConnect()
{
    if( SocketObjectPtr->TestIPConnect()) {
        QString ipinfor = QString("测试") + PARAM.serverIp + QString(":") + QString::number(PARAM.serverPort);
        INFOMATION.informationMessageBox(this,QString("测试结果"),ipinfor + QString("已连接"));
    } else {
        QString ipinfor = QString("测试") + PARAM.serverIp + QString(":") + QString::number(PARAM.serverPort);
        INFOMATION.informationMessageBox(this,QString("测试结果"),ipinfor + QString("未连接"));
    }
}

void LightControl::slotTrigger()
{
    SocketObjectPtr->Trigger();
}

void LightControl::slotChangeRecipe(int index)
{
    qDebug()<<"index ="<<index;
    QString needLoadJsonFile = QDir::currentPath() + QString(RECIPE_FULLPATH) + "/" + ui->RecipeCB->currentText();//需要加载的工单名称recipe=8nm.json
    QDir dir(QDir::currentPath() + QString(RECIPE_FULLPATH));
    QFileInfoList fileList = dir.entryInfoList(QStringList() << "*.json");
    if (fileList.size() == 0) { //没有找到任何json工单
        INFOMATION.informationMessageBox(this,QString("信息"),QDir::currentPath() + QString(RECIPE_FULLPATH) + QString("目录为空或者错误"));
    } else {                    //找到了json工单
        //遍历文件夹
        for(auto fileInfo:fileList) {
            if(fileInfo.fileName() == ui->RecipeCB->currentText()) {
                ui->RecipeCB->setCurrentText(needLoadJsonFile);
                LightControl::readRecipeToTable(needLoadJsonFile.toStdString());
                INFOMATION.informationMessageBox(this,QString("信息"),QString("切换工单成功"));
                return;
            }
        }
        INFOMATION.informationMessageBox(this,QString("信息"),QString("切换工单失败"));
    }
}


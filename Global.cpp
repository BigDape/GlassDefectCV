#include "Global.h"
#include "log_singleton.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#pragma execution_character_set("utf-8")

GlobalParamter::GlobalParamter()
    :CameraCounts(0),
     IsScanned(false),
     xmlParam("SystemParam/SystemParam.xml"),
     FramesPerTri(0),
     ImageHeight(0),
     ImageWidth(0),
     CurrentRecipe(""),
     SystemName(""),
     Camera0Name(""),
     Camera1Name(""),
     Camera2Name(""),
     Camera3Name(""),
     serverIp(""),
     RegParaPort(0),
     FrameSignal(0),
     CodeCount(0),
     CodeLineCount(0),
     Code4Count(0),
     CodePerCount(0),
     CamRows(0),
     CamRowsPerField(0),
     RecChangeSignal(false),
     AlmLightSignal(false),
     AlmLightVal(0),
     FieldNumberSet(0),
     camDefineNum(0),
     GlassID_INT(0),
     encodeRollerCount(0),
     encodeARollerCount(0),
     encodeBRollerCount(0),
     encodeRollerCofficient(0),
     RollerAngle(0),
     encodeRollerYLength(0),
     m_plot(nullptr),
     isOffline(false),
     offlineFullPath(""),
     isJpg(false),
     encodeAB4(0)
{
    camName<<"Camera0"<<"Camera1"<<"Camera2"<<"Camera3";

    xmlParam.getParameter("CurrentRecipe", CurrentRecipe);
    xmlParam.getParameter("SystemName", SystemName);
    xmlParam.getParameter("serverIp", serverIp);
    xmlParam.getParameter("RegParaPort",RegParaPort);

    QString CurrentRecipeNameLog = "获得当前工单: " + CurrentRecipe;
    QString SystemNameLog = "获得当前项目名: " + SystemName;
    log_singleton::Write_Log(CurrentRecipeNameLog, Log_Level::General);
    log_singleton::Write_Log(SystemNameLog, Log_Level::General);

    QString RecipePath = "Recipes/" + CurrentRecipe + ".json";
    JsonParse2Map *JsonRecipe = new JsonParse2Map(RecipePath);
    JsonRecipe->getParameter("相机0.帧次",FramesPerTri);

    HTuple CurrentRecipeHT =  CurrentRecipe.toUtf8().constData();
    ReadDict("Recipes/"+ CurrentRecipeHT +".json", HTuple(), HTuple(), &RecipeDict);
    xmlParam.getParameter("CameraNum",camDefineNum);
    for(int i=0; i < camDefineNum; i++) {
        QString tempCamName;
        xmlParam.getParameter(camName[i],tempCamName); // 获取照相机名称
        camListName.append(tempCamName);
        int tempView;
        xmlParam.getParameter(camName[i]+"Field",tempView);
        FieldSelectedView.append(tempView);
    }
}

GlobalParamter::~GlobalParamter(){}

GlobalParamter& GlobalParamter::getInstance()
{
    static GlobalParamter param;
    return param;
}

bool GlobalParamter::SaveXml()
{
    xmlParam.setParameter("CurrentRecipe", CurrentRecipe);
    int ret = xmlParam.SaveParasToFile();
    QString SaveXmlLog = "系统工单参数已设置完成 ";
    log_singleton::Write_Log(SaveXmlLog, Log_Level::General);
    return (ret < 0 ? false : true);
}

dvpCameraInfo GlobalParamter::getInfo(int index)
{
    assert(index >= 0 && index < (int)info.size());
    return info[index];
}

bool GlobalParamter::setInfo(int index, dvpCameraInfo i)
{
   assert(index >= 0 && index < (int)info.size());
   info[index] = i;
   return true;
}

std::vector<dvpCameraInfo> GlobalParamter::getInfoVec()
{
   return info;
}

bool GlobalParamter::setInfo(std::vector<dvpCameraInfo> infoVec)
{
    info = infoVec;
    return true;
}

dvpUint32 GlobalParamter::getCameraCounts()
{
    return CameraCounts;
}

bool GlobalParamter::setCameraCounts(dvpUint32 counts)
{
    CameraCounts = counts;
    return true;
}

bool GlobalParamter::getIsScanned()
{
    return IsScanned;
}

bool GlobalParamter::setIsScanned(bool isscanned)
{
    IsScanned = isscanned;
    return IsScanned;
}

XmlParse& GlobalParamter::getXmlParam()
{
    return xmlParam;
}

bool GlobalParamter::setXmlParam(XmlParse& xmlparam)
{
    xmlParam = xmlparam;
    return true;
}

double GlobalParamter::getFramesPerTri()
{
    return FramesPerTri;
}

bool GlobalParamter::setFramesPerTri(double framesPerTri)
{
    FramesPerTri = framesPerTri;
    return true;
}

double GlobalParamter::getImageHeight()
{
   return ImageHeight;
}

bool GlobalParamter::setImageHeight(double imageHeight)
{
    ImageHeight = imageHeight;
    return true;
}

double GlobalParamter::getImageWidth()
{
    return ImageWidth;
}

bool GlobalParamter::setImageWidth(double imageWidth)
{
    ImageWidth = imageWidth;
    return true;
}

QString GlobalParamter::getCurrentRecipe()
{
   return CurrentRecipe;
}

bool GlobalParamter::setCurrentRecipe(QString currentRecipe)
{
    CurrentRecipe = currentRecipe;
    return true;
}

QString GlobalParamter::getSystemName()
{
    return SystemName;
}

bool GlobalParamter::setSystemName(QString systemName)
{
    SystemName = systemName;
    return true;
}

QString GlobalParamter::getCamera0Name()
{
    return Camera0Name;
}

bool GlobalParamter::setCamera0Name(QString camera0Name)
{
    Camera0Name = camera0Name;
    return true;
}

QString GlobalParamter::getCamera1Name()
{
    return Camera1Name;
}

bool GlobalParamter::setCamera1Name(QString camera1Name)
{
    Camera1Name = camera1Name;
    return true;
}

QString GlobalParamter::getCamera2Name()
{
    return Camera2Name;
}

bool GlobalParamter::setCamera2Name(QString camera2Name)
{
    Camera2Name = camera2Name;
    return true;
}

QString GlobalParamter::getCamera3Name()
{
    return Camera3Name;
}

bool GlobalParamter::setCamera3Name(QString camer3Name)
{
    Camera3Name = camer3Name;
    return true;
}

QString GlobalParamter::getServerIP()
{
    return serverIp;
}

bool GlobalParamter::setServerIP(QString ip)
{
    serverIp = ip;
    return true;
}

int GlobalParamter::getPort()
{
    return RegParaPort;
}

bool GlobalParamter::setPort(int port)
{
    RegParaPort = port;
    return true;
}

int GlobalParamter::getFrameSignal()
{
    return FrameSignal;
}

bool GlobalParamter::setFrameSignal(int signal)
{
    FrameSignal = signal;
    return FrameSignal;
}

long GlobalParamter::getCodeCount()
{
   return CodeCount;
}

bool GlobalParamter::setCodeCount(long count)
{
    CodeCount = count;
    return true;
}

long GlobalParamter::getCodeLineCount()
{
    return CodeLineCount;
}

bool GlobalParamter::setCodeLineCount(long count)
{
    CodeLineCount = count;
    return true;
}

long GlobalParamter::getCode4Count()
{
    return Code4Count;
}

bool GlobalParamter::setCode4Count(long count)
{
    Code4Count = count;
    return true;
}

long GlobalParamter::getCodePerCount()
{
    return CodePerCount;
}

bool GlobalParamter::setCodePerCount(long count)
{
    CodePerCount = count;
    return true;
}

int GlobalParamter::getCamRows()
{
    return CamRows;
}

bool GlobalParamter::setCamRows(int camRows)
{
    CamRows = camRows;
    return true;
}

int GlobalParamter::getCamRowsPerField()
{
    return CamRowsPerField;
}

bool GlobalParamter::setCamRowsPerField(int camRowsPerField)
{
    CamRowsPerField = camRowsPerField;
    return true;
}

bool GlobalParamter::getRecChangeSignal()
{
   return RecChangeSignal;
}

bool GlobalParamter::setRecChangeSignal(bool signal)
{
    RecChangeSignal = signal;
    return true;
}

bool GlobalParamter::getAlmLightSignal()
{
    return AlmLightSignal;
}

bool GlobalParamter::setAlmLightSignal(bool signal)
{
    AlmLightSignal = signal;
    return AlmLightSignal;
}

int GlobalParamter::getAlmLightVal()
{
    return AlmLightVal;
}

bool GlobalParamter::setAlmLightVal(int val)
{
    AlmLightVal = val;
    return true;
}

int GlobalParamter::getFieldNumberSet()
{
    return FieldNumberSet;
}

bool GlobalParamter::setFieldNumberSet(int fieldNumberSet)
{
    FieldNumberSet = fieldNumberSet;
    return true;
}

HTuple GlobalParamter::getRecipeDict()
{
    return RecipeDict;
}

bool GlobalParamter::setRecipeDict(HTuple recipeDict)
{
    RecipeDict = recipeDict;
    return true;
}

QStringList GlobalParamter::getCamName()
{
    return camName;
}

bool GlobalParamter::setCamName(QStringList list)
{
    camName = list;
    return true;
}

int GlobalParamter::getCamDefineNum()
{
    return camDefineNum;
}

bool GlobalParamter::setCamDefineNum(int num)
{
    camDefineNum = num;
    return true;
}

QList<QString> GlobalParamter::getCamListName()
{
    return camListName;
}

bool GlobalParamter::setCamListName(QList<QString> strs)
{
    camListName = strs;
    return true;
}

QList<int> GlobalParamter::getFieldSelectedView()
{
    return FieldSelectedView;
}

bool GlobalParamter::setFieldSelectedView(QList<int> views)
{
    FieldSelectedView = views;
    return true;
}

quint64 GlobalParamter::getGlassID_INT()
{
    return GlassID_INT;
}

bool GlobalParamter::setGlassID_INT(quint64 id)
{
    GlassID_INT = id;
    return true;
}

long GlobalParamter::getEncodeRollerCount()
{
    return encodeRollerCount;
}

bool GlobalParamter::setEncodeRollerCount(long count)
{
    encodeRollerCount = count;
    return true;
}

long GlobalParamter::getEncodeARollerCount()
{
    return encodeARollerCount;
}

bool GlobalParamter::setEncodeARollerCount(long count)
{
    encodeARollerCount = count;
    return true;
}

long GlobalParamter::getEncodeBRollerCount()
{
    return encodeBRollerCount;
}

bool GlobalParamter::setEncodeBRollerCount(long count)
{
    encodeBRollerCount = count;
    return true;
}

double GlobalParamter::getEncodeRollerCofficient()
{
    return encodeRollerCofficient;
}

bool GlobalParamter::setEncodeRollerCofficient(double cofficient)
{
    encodeRollerCofficient = cofficient;
    return true;
}

double GlobalParamter::getRollerAngle()
{
    return RollerAngle;
}

bool GlobalParamter::setRollerAngle(double angle)
{
    RollerAngle = angle;
    return true;
}

double GlobalParamter::getEncodeRollerYLength()
{
    return encodeRollerYLength;
}

bool GlobalParamter::setEncodeRollerYLength(double length)
{
    encodeRollerYLength = length;
    return true;
}

std::vector<CourTour>& GlobalParamter::getCourtourMapXY()
{
    return courtourMapXY;
}

bool GlobalParamter::setCourtourMapXY(std::vector<CourTour>& tours)
{
    courtourMapXY = tours;
    return true;
}

bool GlobalParamter::setCourtourMapXY(CourTour tour)
{
    courtourMapXY.push_back(tour);
    return true;
}

std::shared_ptr<QwtPlot> GlobalParamter::getPlot()
{
    return m_plot;
}

bool GlobalParamter::setPlot(std::shared_ptr<QwtPlot> ptr)
{
   m_plot = ptr;
   return true;
}

bool GlobalParamter::getIsOffline()
{
    return isOffline;
}

bool GlobalParamter::setIsOffline(bool flag)
{
    isOffline = flag;
    return true;
}

QString GlobalParamter::getOfflineFullPath()
{
    return offlineFullPath;
}

bool GlobalParamter::setOfflineFullPath(QString path)
{
    offlineFullPath = path;
    return true;
}

bool GlobalParamter::getIsJpg()
{
    return isJpg;
}

bool GlobalParamter::setIsJpg(bool isjpg)
{
    isJpg = isjpg;
    return true;
}

long GlobalParamter::getEncodeAB4()
{
    return encodeAB4;
}

bool GlobalParamter::setEncodeAB4(long code4)
{
    encodeAB4 = code4;
    return true;
}

int GlobalParamter::getSaveOriginImage()
{
    return isSaveOriginImage;
}

bool GlobalParamter::setSaveOriginImage(int index)
{
    isSaveOriginImage = index;
    return true;
}

int GlobalParamter::getSaveEntireImage()
{
    return isSaveEntireImage;
}

bool GlobalParamter::setSaveEntireImage(int index)
{
    isSaveEntireImage = index;
    return true;
}

int GlobalParamter::getSaveFlawImage()
{
    return isSaveFlawImage;
}

bool GlobalParamter::setSaveFlawImage(int index)
{
    isSaveFlawImage = index;
    return true;
}

int GlobalParamter::getSaveCropImage()
{
    return isSaveCropImage;
}

bool GlobalParamter::setSaveCropImage(int index)
{
    isSaveCropImage = index;
    return true;
}

int GlobalParamter::getXYLengthEnable()
{
    return XYLengthEnable;
}

bool GlobalParamter::setXYLengthEnable(int index)
{
    XYLengthEnable = index;
    return true;
}

int GlobalParamter::getFlawDefectEnable()
{
    return FlawDefectEnable;
}

bool GlobalParamter::setFlawDefectEnable(int index)
{
    FlawDefectEnable = index;
    return true;
}

int GlobalParamter::getCamera12PixelDeviation()
{
    return Camera12PixelDeviation;
}

bool GlobalParamter::setCamera12PixelDeviation(int number)
{
    Camera12PixelDeviation = number;
    return true;
}

int GlobalParamter::getCamera23PixelDeviation()
{
    return Camera23PixelDeviation;
}

bool GlobalParamter::setCamera23PixelDeviation(int number)
{
    Camera23PixelDeviation = number;
    return true;
}

int GlobalParamter::getCamera24PixelDeviation()
{
    return Camera24PixelDeviation;
}

bool GlobalParamter::setCamera24PixelDeviation(int number)
{
    Camera24PixelDeviation = number;
    return true;
}

int GlobalParamter::getSilkToRollerDist()
{
    return SilkToRollerDist;
}

bool GlobalParamter::setSilkToRollerDist(int number)
{
    SilkToRollerDist = number;
    return true;
}

int GlobalParamter::getScratchAreaThreshold()
{
    return ScratchAreaThreshold;
}

bool GlobalParamter::setScratchAreaThreshold(int number)
{
    ScratchAreaThreshold = number;
    return true;
}

int GlobalParamter::getBubbleStoneAreaThreshold()
{
    return BubbleStoneAreaThreshold;
}

bool GlobalParamter::setBubbleStoneAreaThreshold(int number)
{
    BubbleStoneAreaThreshold = number;
    return true;
}

int GlobalParamter::getDirtyAreaThreshold()
{
    return DirtyAreaThreshold;
}

bool GlobalParamter::setDirtyAreaThreshold(int number)
{
    DirtyAreaThreshold = number;
    return DirtyAreaThreshold;
}

double GlobalParamter::getYAccuracyB()
{
    return YAccuracyB;
}

bool GlobalParamter::setYAccuracyB(double num)
{
    YAccuracyB = num;
    return true;
}

double GlobalParamter::getYAccuracyK()
{
    return YAccuracyK;
}

bool GlobalParamter::setYAccuracyK(double num)
{
    YAccuracyK = num;
    return true;
}

double GlobalParamter::getWidth()
{
    return Width;
}

bool GlobalParamter::setWidth(double num)
{
    Width = num;
    return true;
}

double GlobalParamter::getWidthDeviation()
{
    return WidthDeviation;
}

bool GlobalParamter::setWidthDeviation(double num)
{
    WidthDeviation = num;
    return WidthDeviation;
}

double GlobalParamter::getDigonal()
{
    return Digonal;
}

bool GlobalParamter::setDigonal(double num)
{
    Digonal = num;
    return true;
}

double GlobalParamter::getDigonal1Deviation()
{
    return Digonal1Deviation;
}

bool GlobalParamter::setDigonal1Deviation(double num)
{
   Digonal1Deviation = num;
   return true;
}

double GlobalParamter::getDigonal2()
{
    return Digonal2;
}

bool GlobalParamter::setDigonal2(double num)
{
    Digonal2 = num;
    return true;
}

double GlobalParamter::getDigonal2Deviation()
{
    return Digonal2Deviation;
}

bool GlobalParamter::setDigonal2Deviation(double num)
{
   Digonal2Deviation = num;
   return true;
}

double GlobalParamter::getCamera1Pixel0Accuracy()
{
    return Camera1Pixel0Accuracy;
}

bool GlobalParamter::setCamera1Pixel0Accuracy(double num)
{
    Camera1Pixel0Accuracy = num;
    return true;
}

double GlobalParamter::getCamera1PixelKValue()
{
    return Camera1PixelKValue;
}

bool GlobalParamter::setCamera1PixelKValue(double num)
{
    Camera1PixelKValue = num;
    return true;
}

double GlobalParamter::getCamera21AccuracyRatio()
{
    return Camera21AccuracyRatio;
}

bool GlobalParamter::setCamera21AccuracyRatio(double num)
{
    Camera21AccuracyRatio = num;
    return true;
}

double GlobalParamter::getCamera2PixelKValue()
{
    return Camera2PixelKValue;
}

bool GlobalParamter::setCamera2PixelKValue(double num)
{
    Camera2PixelKValue = num;
    return true;
}

double GlobalParamter::getLength()
{
    return Length;
}

bool GlobalParamter::setLength(double num)
{
    Length = num;
    return Length;
}

double GlobalParamter::getLengthDeviation()
{
    return   LengthDeviation;
}

bool GlobalParamter::setLengthDeviation(double num)
{
    LengthDeviation = num;
    return true;
}

int GlobalParamter::getCamera0Frame()
{
    return Camera0Frame;
}

bool GlobalParamter::setCamera0Frame(int num)
{
    Camera0Frame = num;
    return true;
}

int GlobalParamter::getCamera0PhotoRow()
{
    return  Camera0PhotoRow;
}

bool GlobalParamter::setCamera0PhotoRow(int num)
{
    Camera0PhotoRow = num;
    return true;
}

int GlobalParamter::getCamera0ExposureTime()
{
    return   Camera0ExposureTime;
}

bool GlobalParamter::setCamera0ExposureTime(int num)
{
    Camera0ExposureTime = num;
    return true;
}

int GlobalParamter::getCamera0Gain()
{
    return  Camera0Gain;
}

bool GlobalParamter::setCamera0Gain(int num)
{
    Camera0Gain = num;
    return true;
}

int GlobalParamter::getCamera1Frame()
{
    return Camera1Frame;
}

bool GlobalParamter::setCamera1Frame(int num)
{
    Camera1Frame = num;
    return true;
}

int GlobalParamter::getCamera1PhotoRow()
{
    return Camera1PhotoRow;
}

bool GlobalParamter::setCamera1PhotoRow(int num)
{
    Camera1PhotoRow = num;
    return true;
}

int GlobalParamter::getCamera1ExposureTime()
{
    return  Camera1ExposureTime;
}

bool GlobalParamter::setCamera1ExposureTime(int num)
{
    Camera1ExposureTime = num;
    return true;
}


int GlobalParamter::getCamera1Gain()
{
    return Camera1Gain;
}

bool GlobalParamter::setCamera1Gain(int num)
{
    Camera1Gain = num;
    return true;
}

int GlobalParamter::getCamera2Frame()
{
    return Camera2Frame;
}

bool GlobalParamter::setCamera2Frame(int num)
{
    Camera2Frame = num;
    return true;
}

int GlobalParamter::getCamera2PhotoRow()
{
    return Camera2PhotoRow;
}

bool GlobalParamter::setCamera2PhotoRow(int num)
{
    Camera2PhotoRow = num;
    return true;
}

int GlobalParamter::getCamera2ExposureTime()
{
    return  Camera2ExposureTime;
}

bool GlobalParamter::setCamera2ExposureTime(int num)
{
    Camera2ExposureTime = num;
    return true;
}

int GlobalParamter::getCamera2Gain()
{
    return Camera2Gain;
}

bool GlobalParamter::setCamera2Gain(int num)
{
    Camera2Gain = num;
    return true;
}

int GlobalParamter::getCamera3Frame()
{
    return Camera3Frame;
}

bool GlobalParamter::setCamera3Frame(int num)
{
    Camera3Frame = num;
    return true;
}

int GlobalParamter::getCamera3PhotoRow()
{
    return Camera3PhotoRow;
}

bool GlobalParamter::setCamera3PhotoRow(int num)
{
    Camera3PhotoRow = num;
    return true;
}

int GlobalParamter::getCamera3ExposureTime()
{
    return Camera3ExposureTime;
}

bool GlobalParamter::setCamera3ExposureTime(int num)
{
    Camera3ExposureTime = num;
    return true;
}

int GlobalParamter::getCamera3Gain()
{
    return  Camera3Gain;
}

bool GlobalParamter::setCamera3Gain(int num)
{
    Camera3Gain = num;
    return true;
}

int GlobalParamter::getEncodeUnitToDist()
{
    return EncodeUnitToDist;
}

int GlobalParamter::getEncodePulseFilterUs()
{
    return EncodePulseFilterUs;
}

int GlobalParamter::getEncodeCountEndFlag()
{
    return EncodeCountEndFlag;
}

int GlobalParamter::getEncodeCount()
{
    return EncodeCount;
}

int GlobalParamter::getEncodeTriggerRowCount()
{
    return EncodeTriggerRowCount;
}

int GlobalParamter::getEncode4FrequencyMultiplierCount()
{
    return Encode4FrequencyMultiplierCount;
}

int GlobalParamter::getEncodeUnitTimePulseCount()
{
    return EncodeUnitTimePulseCount;
}

int GlobalParamter::getEncodeCountTimeHalfSecond()
{
    return EncodeCountTimeHalfSecond;
}

int GlobalParamter::getEncodeChannel()
{
    return EncodeChannel;
}

int GlobalParamter::getEncodeRevolution()
{
    return EncodeRevolution;
}

int GlobalParamter::getRollerPerimeterUm()
{
    return RollerPerimeterUm;
}

int GlobalParamter::getExpectSinglePixelAccuracy()
{
    return ExpectSinglePixelAccuracy;
}

int GlobalParamter::getRollerMaxSpeedToRowCount()
{
    return RollerMaxSpeedToRowCount;
}

int GlobalParamter::getEveryRowToEncodeCount()
{
    return EveryRowToEncodeCount;
}

int GlobalParamter::getEncodePressureWheelCountA()
{
    return EncodePressureWheelCountA;
}

int GlobalParamter::getEncodePressureWheelCountB()
{
    return EncodePressureWheelCountB;
}

int GlobalParamter::getPressureWheel4FrequencyMutliper()
{
    return PressureWheel4FrequencyMutliper;
}

int GlobalParamter::getPressureEncodecoefficient()
{
    return PressureEncodecoefficient;
}

bool GlobalParamter::setEncodeUnitToDist(int num)
{
      EncodeUnitToDist = num;
      return true;
}

bool GlobalParamter::setEncodePulseFilterUs(int num)
{
    EncodePulseFilterUs = num;
    return true;
}

bool GlobalParamter::setEncodeCountEndFlag(int num)
{
    EncodeCountEndFlag = num;
    return true;
}

bool GlobalParamter::setEncodeCount(int num)
{
    EncodeCountEndFlag = num;
    return true;
}

bool GlobalParamter::setEncodeTriggerRowCount(int num)
{
    EncodeTriggerRowCount = num;
    return true;
}

bool GlobalParamter::setEncode4FrequencyMultiplierCount(int num)
{
    Encode4FrequencyMultiplierCount = num;
    return true;
}

bool GlobalParamter::setEncodeUnitTimePulseCount(int num)
{
    EncodeUnitTimePulseCount = num;
    return true;
}

bool GlobalParamter::setEncodeCountTimeHalfSecond(int num)
{
    EncodeCountTimeHalfSecond = num;
    return true;
}

bool GlobalParamter::setEncodeChannel(int num)
{
    EncodeChannel = num;
    return true;
}

bool GlobalParamter::setEncodeRevolution(int num)
{
    EncodeRevolution = num;
    return true;
}

bool GlobalParamter::setRollerPerimeterUm(int num)
{
    RollerPerimeterUm = num;
    return true;
}

bool GlobalParamter::setExpectSinglePixelAccuracy(int num)
{
    ExpectSinglePixelAccuracy = num;
    return true;
}

bool GlobalParamter::setRollerMaxSpeedToRowCount(int num)
{
    RollerMaxSpeedToRowCount = num;
    return true;
}

bool GlobalParamter::setEveryRowToEncodeCount(int num)
{
    EveryRowToEncodeCount = num;
    return true;
}

bool GlobalParamter::setEncodePressureWheelCountA(int num)
{
    EncodePressureWheelCountA = num;
    return true;
}

bool GlobalParamter::setEncodePressureWheelCountB(int num)
{
    EncodePressureWheelCountB = num;
    return true;
}

bool GlobalParamter::setPressureWheel4FrequencyMutliper(int num)
{
    PressureWheel4FrequencyMutliper = num;
    return true;
}

bool GlobalParamter::setPressureEncodecoefficient(int num)
{
    PressureEncodecoefficient = num;
    return true;
}

int GlobalParamter::getPixelAccuracyUm()
{
    return PixelAccuracyUm;
}

int GlobalParamter::getPhotoelectricSignalPulseFilter()
{
    return PhotoelectricSignalPulseFilter;
}

int GlobalParamter::getCamareTrigerPulseContinueTime10ns()
{
    return CamareTrigerPulseContinueTime10ns;
}

int GlobalParamter::getPhotoelectricToCamareDist()
{
    return PhotoelectricToCamareDist;
}

int GlobalParamter::getCamareFrameTrigerDelayRowCount()
{
    return CamareFrameTrigerDelayRowCount;
}

int GlobalParamter::getFrameSignalContinueTime()
{
    return FrameSignalContinueTime;
}

int GlobalParamter::getModuleEnableSignal()
{
    return ModuleEnableSignal;
}

int GlobalParamter::getCamarePhotoRowCount()
{
    return CamarePhotoRowCount;
}

int GlobalParamter::getInnerRowFrequency()
{
    return InnerRowFrequency;
}

int GlobalParamter::getPhotoMode()
{
    return PhotoMode;
}

int GlobalParamter::getPhotoEndDelayRowCount()
{
    return PhotoEndDelayRowCount;
}

bool GlobalParamter::setPixelAccuracyUm(int num)
{
    PixelAccuracyUm = num;
    return true;
}

bool GlobalParamter::setPhotoelectricSignalPulseFilter(int num)
{
    PhotoelectricSignalPulseFilter = num;
    return true;
}

bool GlobalParamter::setCamareTrigerPulseContinueTime10ns(int num)
{
    CamareTrigerPulseContinueTime10ns = num;
    return true;
}

bool GlobalParamter::setPhotoelectricToCamareDist(int num)
{
    PhotoelectricToCamareDist = num;
    return true;
}

bool GlobalParamter::setCamareFrameTrigerDelayRowCount(int num)
{
    CamareFrameTrigerDelayRowCount = num;
    return true;
}

bool GlobalParamter::setFrameSignalContinueTime(int num)
{
    FrameSignalContinueTime = num;
    return true;
}

bool GlobalParamter::setModuleEnableSignal(int num)
{
    ModuleEnableSignal = num;
    return true;
}

bool GlobalParamter::setCamarePhotoRowCount(int num)
{
    CamarePhotoRowCount = num;
    return true;
}

bool GlobalParamter::setInnerRowFrequency(int num)
{
    InnerRowFrequency = num;
    return true;
}

bool GlobalParamter::setPhotoMode(int num)
{
    PhotoMode = num;
    return true;
}

bool GlobalParamter::setPhotoEndDelayRowCount(int num)
{
    PhotoEndDelayRowCount = num;
    return true;
}

int GlobalParamter::getLightField1DelayTime()
{
    return LightField1DelayTime;
}

int GlobalParamter::getLightField1GlowTime()
{
    return LightField1GlowTime;
}

int GlobalParamter::getLightField2DelayTime()
{
    return LightField2DelayTime;
}

int GlobalParamter::getLightField2GlowTime()
{
    return LightField2GlowTime;
}

int GlobalParamter::getLightField3DelayTime()
{
    return LightField3DelayTime;
}

int GlobalParamter::getLightField3GlowTime()
{
    return LightField3GlowTime;
}

int GlobalParamter::getLightField4DelayTime()
{
    return LightField4DelayTime;
}

int GlobalParamter::getLightField4GlowTime()
{
    return LightField4GlowTime;
}

int GlobalParamter::getSelectedLightFieldNumber()
{
    return SelectedLightFieldNumber;
}

int GlobalParamter::getHorizontalDarkfieldSelectRegister()
{
    return  HorizontalDarkfieldSelectRegister;
}

int GlobalParamter::getCamareAndLightFieldControl()
{
    return  CamareAndLightFieldControl;
}

int GlobalParamter::getSignalSwitch()
{
    return  SignalSwitch;
}

int GlobalParamter::getRowSignalSelected()
{
    return  RowSignalSelected;
}

bool GlobalParamter::setLightField1DelayTime(int num)
{
    LightField1DelayTime = num;
    return true;
}

bool GlobalParamter::setLightField1GlowTime(int num)
{
    LightField1GlowTime = num;
    return true;
}

bool GlobalParamter::setLightField2DelayTime(int num)
{
    LightField2DelayTime = num;
    return true;
}

bool GlobalParamter::setLightField2GlowTime(int num)
{
    LightField2GlowTime = num;
    return true;
}

bool GlobalParamter::setLightField3DelayTime(int num)
{
    LightField3DelayTime = num;
    return true;
}

bool GlobalParamter::setLightField3GlowTime(int num)
{
    LightField3GlowTime = num;
    return true;
}

bool GlobalParamter::setLightField4DelayTime(int num)
{
    LightField4DelayTime = num;
    return true;
}

bool GlobalParamter::setLightField4GlowTime(int num)
{
    LightField4GlowTime = num;
    return true;
}

bool GlobalParamter::setSelectedLightFieldNumber(int num)
{
    SelectedLightFieldNumber = num;
    return true;
}

bool GlobalParamter::setHorizontalDarkfieldSelectRegister(int num)
{
    HorizontalDarkfieldSelectRegister = num;
    return true;
}

bool GlobalParamter::setCamareAndLightFieldControl(int num)
{
    CamareAndLightFieldControl = num;
    return true;
}

bool GlobalParamter::setSignalSwitch(int num)
{
    SignalSwitch = num;
    return true;
}

bool GlobalParamter::setRowSignalSelected(int num)
{
    RowSignalSelected = num;
    return true;
}


QString GlobalParamter::GetParamterFromIniFile(QString fullpath, QString key)
{
    QString result;
    std::ifstream configFile(fullpath.toStdString());
    std::string line;
    std::map<std::string, std::string> config;
    assert(configFile.is_open());

    while (getline(configFile, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (getline(is_line, key, '=')) {
            std::string value;
            if (getline(is_line, value)) {
                config[key] = value;
            }
        }
    }

    configFile.close();
    // 打印读取的配置
    for (const auto& pair : config) {
        //std::cout << pair.first << " = " << pair.second << std::endl;
        if (pair.first == key.toStdString()) {
          result = pair.second.data();
        }
    }
    return result;
}

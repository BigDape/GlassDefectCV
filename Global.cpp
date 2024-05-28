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

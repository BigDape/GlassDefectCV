#include "Global.h"
#include "log_singleton.h"
#pragma execution_character_set("utf-8")

void Global::InitGlobalParam()
{
    CameraCounts = 0;
    camName<<"Camera0"<<"Camera1"<<"Camera2"<<"Camera3";
    IsScanned = false;
    FrameSignal=false;
    GlassID_INT=0;
    CodeCount=0;
    Code4Count=0;
    CodeLineCount=0;
    CodePerCount=0;
    RecChangeSignal=false;
    AlmLightSignal=false;
    AlmLightVal=0;
    FieldNumberSet=3;
    encodeRollerCount = 0; //编码器压轮计数
    encodeRollerCofficient = 0;//编码器压轮系数
    RollerAngle = 0.0;//玻璃便宜的角度
    encodeRollerYLength = 0.0;
    isOffline = false;
    XmlParam.getParameter("CurrentRecipe", CurrentRecipe);
    XmlParam.getParameter("SystemName", SystemName);
    XmlParam.getParameter("serverIp", serverIp);
    XmlParam.getParameter("RegParaPort",RegParaPort);

    QString CurrentRecipeNameLog = "获得当前工单: " + CurrentRecipe;
    QString SystemNameLog = "获得当前项目名: " + SystemName;
    QString RecipePath = "Recipes/" + CurrentRecipe + ".json";
    JsonParse2Map *JsonRecipe = new JsonParse2Map(RecipePath);
    JsonRecipe->getParameter("相机0.帧次",FramesPerTri);

    qDebug()<<"相机"<<CurrentRecipe;
    qDebug()<<"相机0.帧次"<<FramesPerTri;
    log_singleton::Write_Log(CurrentRecipeNameLog, Log_Level::General);
    log_singleton::Write_Log(SystemNameLog, Log_Level::General);
    HTuple CurrentRecipeHT=  Global::CurrentRecipe.toUtf8().constData();
    ReadDict("Recipes/"+ CurrentRecipeHT +".json", HTuple(), HTuple(), &RecipeDict);
    ReadCameraParam();
    currenttime = "0";
}

void Global::SaveXml()
{
    XmlParam.setParameter("CurrentRecipe", CurrentRecipe);
    XmlParam.SaveParasToFile();
    QString SaveXmlLog = "系统工单参数已设置完成 ";
    log_singleton::Write_Log(SaveXmlLog, Log_Level::General);
}

void Global::ReadCameraParam()
{
    XmlParam.getParameter("CameraNum",camDefineNum);
    for(int i=0;i<camDefineNum;i++){
        QString a1;
        XmlParam.getParameter(camName[i],a1);
        camListName.append(a1);
        int b1;
        XmlParam.getParameter(camName[i]+"Field",b1);
        FieldSelectedView.append(b1);
    }
}

dvpCameraInfo Global::info[16];
dvpUint32 Global::CameraCounts;
bool Global::IsScanned;
XmlParse Global::XmlParam("SystemParam/SystemParam.xml");
QString Global::CurrentRecipe;
double Global::FramesPerTri;
double Global::ImageHeight;
double Global::ImageWidth;
QString Global::SystemName;
QString Global::Camera0Name;
QString Global::Camera1Name;
QString Global::Camera2Name;
QString Global::Camera3Name;
QString Global::serverIp;
int Global::RegParaPort;
int Global::FrameSignal;
int Global::CamRows;
int Global::CamRowsPerField;
long Global::CodeCount;
long Global::CodeLineCount;
long Global::Code4Count;
long Global::CodePerCount;
bool Global::RecChangeSignal;
bool Global::AlmLightSignal;
int Global::AlmLightVal;
int Global::FieldNumberSet;
HTuple Global::RecipeDict;
QStringList Global::camName;
int Global::camDefineNum;
QList<QString> Global::camListName;
QList<int> Global::FieldSelectedView;
quint64 Global::GlassID_INT;
long Global::encodeRollerCount; //编码器压轮计数
long Global::encodeARollerCount; //编码器a压轮计数
long Global::encodeBRollerCount; //编码器B压轮计数
double Global::encodeRollerCofficient;//编码器压轮系数
double Global::RollerAngle; //玻璃偏移的角度
double Global::encodeRollerYLength;//差分编码器计算出来的值
std::vector<CourTour> Global::courtourMapXY;
QwtPlot* Global::m_plot;
bool Global::isOffline; //是否触发了离线模式
QString Global::offlineFullPath;
bool Global::isJpg;
long Global::encodeAB4;
QString Global::currenttime; //当前时间

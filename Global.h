/*******************************************
    @ClassName   : Global
    @Description : 全局变量,静态变量
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-03
********************************************/
#ifndef GLOBAL_H
#define GLOBAL_H

#include "Camera/DushenSample/DVPCamera.h"
#include "Parameter/XmlParse.h"
#include "log_singleton.h"
#include "Parameter/JsonParse2Map.h"
#include "HalconCpp.h"
#include <unordered_map>
#include <utility>
#include <vector>
#include <Qwt/qwt_plot.h>

#define PARAM GlobalParamter::getInstance()

using namespace HalconCpp;

typedef struct GLASSINFO {
    QString GlassID;
    bool isOK;
    bool isSizeOK;
    double GlassLength;
    double GlassWidth;
    double Diagonal1;
    double Diagonal2;
    int FlawCount;
    bool isFlawOK;
    int Flaw1;
    int Flaw2;
    int Flaw3;
    int Flaw4;
    int Flaw5;
    int Flaw6;
    int Flaw7;
} GLASSINFO;

typedef struct FlawPoint {
    double x;
    double y;
    int FlawType;
} FlawPoint;

struct CourTour {
    int index;
    QString x;
    QString y;
};

//
// 线程安全的懒汉单例模式--局部静态变量
//
class GlobalParamter
{
private: //构造和析构函数私有，防止外部声明
    explicit GlobalParamter();
    virtual ~GlobalParamter();
public:
    static GlobalParamter& getInstance();
    bool SaveXml();
    //
    // get参数与set参数
    //
    dvpCameraInfo getInfo(int index);
    bool setInfo(int index, dvpCameraInfo info);
    std::vector<dvpCameraInfo> getInfoVec();
    bool setInfo(std::vector<dvpCameraInfo> infoVec);

    dvpUint32 getCameraCounts();
    bool setCameraCounts(dvpUint32 counts);

    bool getIsScanned();
    bool setIsScanned(bool isscanned);

    XmlParse& getXmlParam();
    bool setXmlParam(XmlParse& xmlparam);

    double getFramesPerTri();
    bool setFramesPerTri(double framesPerTri);

    double getImageHeight();
    bool setImageHeight(double imageHeight);

    double getImageWidth();
    bool setImageWidth(double imageWidth);

    QString getCurrentRecipe();
    bool setCurrentRecipe(QString currentRecipe);

    QString getSystemName();
    bool setSystemName(QString systemName);

    QString getCamera0Name();
    bool setCamera0Name(QString camera0Name);

    QString getCamera1Name();
    bool setCamera1Name(QString camera1Name);

    QString getCamera2Name();
    bool setCamera2Name(QString camera2Name);

    QString getCamera3Name();
    bool setCamera3Name(QString camer3Name);

    QString getServerIP();
    bool setServerIP(QString ip);

    int getPort();
    bool setPort(int port);

    int getFrameSignal();
    bool setFrameSignal(int signal);

    long getCodeCount();
    bool setCodeCount(long count);

    long getCodeLineCount();
    bool setCodeLineCount(long count);

    long getCode4Count();
    bool setCode4Count(long count);

    long getCodePerCount();
    bool setCodePerCount(long count);

    int getCamRows();
    bool setCamRows(int camRows);

    int getCamRowsPerField();
    bool setCamRowsPerField(int camRowsPerField);

    bool getRecChangeSignal();
    bool setRecChangeSignal(bool signal);

    bool getAlmLightSignal();
    bool setAlmLightSignal(bool signal);

    int getAlmLightVal();
    bool setAlmLightVal(int val);

    int getFieldNumberSet();//场数
    bool setFieldNumberSet(int fieldNumberSet);//场数

    HTuple getRecipeDict();
    bool setRecipeDict(HTuple recipeDict);

    QStringList getCamName();
    bool setCamName(QStringList list);

    int getCamDefineNum();
    bool setCamDefineNum(int num);

    QList<QString> getCamListName();
    bool setCamListName(QList<QString> strs);

    QList<int> getFieldSelectedView();
    bool setFieldSelectedView(QList<int> views);

    quint64 getGlassID_INT();
    bool setGlassID_INT(quint64 id);

    long getEncodeRollerCount(); //编码器压轮计数
    bool setEncodeRollerCount(long count);

    long getEncodeARollerCount(); //编码器压轮计数
    bool setEncodeARollerCount(long count);

    long getEncodeBRollerCount(); //编码器压轮计数
    bool setEncodeBRollerCount(long count);

    double getEncodeRollerCofficient();//编码器压轮系数
    bool setEncodeRollerCofficient(double cofficient);

    double getRollerAngle(); //玻璃偏移的角度
    bool setRollerAngle(double angle);

    double getEncodeRollerYLength();//差分计算出来的长度
    bool setEncodeRollerYLength(double length);

    std::vector<CourTour>& getCourtourMapXY();//轮廓点
    bool setCourtourMapXY(std::vector<CourTour>& tours);
    bool setCourtourMapXY(CourTour tours);

    std::shared_ptr<QwtPlot> getPlot();
    bool setPlot(std::shared_ptr<QwtPlot> ptr);

    bool getIsOffline(); //是否触发了离线模式
    bool setIsOffline(bool flag);

    QString getOfflineFullPath();
    bool setOfflineFullPath(QString path);

    bool getIsJpg();
    bool setIsJpg(bool isjpg);

    long getEncodeAB4();
    bool setEncodeAB4(long code4);

    QString GetParamterFromIniFile(QString fullpath, QString key);
private:
    std::vector<dvpCameraInfo> info;  //info[16]
    dvpUint32 CameraCounts;           //相机数量
    bool IsScanned;
    XmlParse xmlParam;
    double FramesPerTri;
    double ImageHeight;
    double ImageWidth;

    QString CurrentRecipe;            // 当前工单名称：8nm
    QString SystemName;               // 当前系统名称：大拓智能视觉检测
    QString Camera0Name;              // 当前照相机0名称：DSXL810003076
    QString Camera1Name;              // 当前照相机1名称：DSXL810002378
    QString Camera2Name;              // 当前照相机2名称：DSXL810002135
    QString Camera3Name;              // 当前照相机3名称：DSXL810002382
    QString serverIp;                 // 控制器IP地址：192.168.1.200
    int RegParaPort;                  // 控制器Port：7002
    int FrameSignal;
    long CodeCount;
    long CodeLineCount;
    long Code4Count;
    long CodePerCount;
    int CamRows;
    int CamRowsPerField;
    bool RecChangeSignal;
    bool AlmLightSignal;            // 报警信号灯
    int AlmLightVal;                // 报警值
    int FieldNumberSet;             //场数
    HTuple RecipeDict;
    QStringList camName;
    int camDefineNum;
    QList<QString> camListName;         //照相机名称list
    QList<int> FieldSelectedView;       //光场选择的视角：1表示选中，0表示未选中
    quint64 GlassID_INT;
    long encodeRollerCount;             //编码器压轮计数
    long encodeARollerCount;            //编码器压轮计数
    long encodeBRollerCount;            //编码器压轮计数
    double encodeRollerCofficient;      //编码器压轮系数
    double RollerAngle;                 //玻璃偏移的角度
    double encodeRollerYLength;         //差分计算出来的长度
    std::vector<CourTour> courtourMapXY;//轮廓点
    std::shared_ptr<QwtPlot> m_plot;
    bool isOffline;                     //是否触发了离线模式
    QString offlineFullPath;
    bool isJpg;
    long encodeAB4;                     //压轮编码器四倍频
};


#endif // GLOBAL_H

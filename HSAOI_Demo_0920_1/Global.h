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


class Global {

public:

    static void InitGlobalParam();
    static void SaveXml();
    static void ReadCameraParam();
    static void GetYLenth();
    static dvpCameraInfo info[16];
    static dvpUint32 CameraCounts;
    static bool IsScanned;
    static XmlParse XmlParam;
    static double FramesPerTri;
    static double ImageHeight;
    static double ImageWidth;
    
    static QString CurrentRecipe;
    static QString SystemName;
    static QString Camera0Name;
    static QString Camera1Name;
    static QString Camera2Name;
    static QString Camera3Name;
    static QString serverIp;
    static int RegParaPort;
    static int FrameSignal;
    static long CodeCount;
    static long CodeLineCount;
    static long Code4Count;
    static long CodePerCount;
    static int CamRows;
    static int CamRowsPerField;
    static bool RecChangeSignal;
    static bool AlmLightSignal;
    static int AlmLightVal;
    static int FieldNumberSet;//场数
    static HTuple RecipeDict;
    static QStringList camName;
    static int camDefineNum;
    static QList<QString> camListName;
    static QList<int> FieldSelectedView;
    static quint64 GlassID_INT;
    static long encodeRollerCount; //编码器压轮计数
    static long encodeARollerCount; //编码器压轮计数
    static long encodeBRollerCount; //编码器压轮计数
    static double encodeRollerCofficient;//编码器压轮系数
    static double RollerAngle; //玻璃偏移的角度
    static double encodeRollerYLength;//差分计算出来的长度

    static std::vector<CourTour> courtourMapXY;//轮廓点
    static  QwtPlot* m_plot;
    static bool isOffline; //是否触发了离线模式
    static QString offlineFullPath;
    static bool isJpg;

    static long encodeAB4; //压轮编码器四倍频
    static QString currenttime; //当前时间
signals:
};

#endif // GLOBAL_H

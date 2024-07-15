/*******************************************
    @ClassName   : Process_Detect
    @Description : Description
    @Creator     : Yangruyi
    @Author      : Yangruyi
    @Date        : 2023-09-19
********************************************/
#ifndef PROCESS_DETECT_H
#define PROCESS_DETECT_H

#include <QString>
#include <QtDebug>
#include "Camera/Dushen/mosaickimage.h"
#include "Global.h"
#include "Parameter/JsonRecipeWidget.h"
#include "SystemSettingForm.h"
#include "log_singleton.h"
#include <QSettings>
#include "Parameter/JsonResultParse.h"
#include "HDevEngineCpp.h"
#include "HalconCpp.h"

using namespace HalconCpp;
using namespace HDevEngineCpp;

typedef struct ResultINFO {
    UINT64 GlassNum;
    uint ngNum;
    uint okNum;
    double passRate;
    uint sorted;
    uint unsorted;
    uint exceptNum;
    bool pre_result;
    bool sort_result;
} ResultINFO;

class Process_Detect : public QObject {
    Q_OBJECT

public:
    Process_Detect();
    ~Process_Detect();

    //    void cleanup(); // 执行清理操作
private:

    void init_detect();
    void update_result(bool a);

public:
    unsigned int sig_light;
    QList<bool> Qlist_Result;
    bool stopFlag_Detect;
    //玻璃位置(1前2中3后)
    int GlassPosition;
    //检测执行步数
    int DetectStep;
    //当前执行帧步
    int ProcessStep;
    //上次执行帧步
    int LastProcessStep;
    //帧次
    int m_FramesPerTri;
    bool ResultNotOutFlag;
    bool ErrFlag;
    bool LastErrFlag;
    //异常计数
    int ErrCount;
    int LastDefectCount;
    QString handleResult;

    JsonResultParse *ResultDataJson;
    HDevEngine* engine;
    HDevProcedure* procedure;
    HDevProcedureCall* procedurecall;
    HDevProcedure* procedure2;
    HDevProcedureCall* procedurecall2;

    QString engine_path;
    QJsonDocument JsonDoc;

    HTuple Code,CodePerScale;
    HTuple CurrentRecipe;

    HTuple ResultDictHoles;

    HRegion ErrRoi;
    HObject ErrImage1;
    HObject ErrImage2;
    HObject ErrImage3;
    HObject OutLineImage;
    HObject HolesImage;

    HTuple ResultDict;
    HTuple ContourDict;
    HTuple XValues;
    HTuple YValues;



    HTuple ErrName;
    HTuple ErrType;
    HTuple Type;
    HTuple DistanceHorizontal;
    HTuple HolesOK;
    HTuple DistanceVertical;
    HTuple HolesWidth;
    HTuple HolesHeight;
    HTuple DefectLevel;
    HTuple GlassLength;
    HTuple GlassWidth;
    HTuple GlassAngle;//编码器压轮偏移的角度
    HTuple ErrX;
    HTuple ErrY;
    HTuple ErrW;
    HTuple ErrL;
    HTuple ErrArea;
    HTuple YCoordIn;
    HTuple YCoordOut;

    QList<FlawPoint>* Points;
//    FlawPoint* Point;
    ResultINFO *result;
    GLASSINFO *ginfo;
    void VisionProcess();
    void DetectSiYin();
    void SummaryResults();
    void DetectData2Json();
    void HolesData2Json();
    void Glassinfo();

signals:
//    void resultReady(JsonResultParse::DetectResult a);
    void sendData(GLASSINFO* info);
    void sig_updateFlaw(GLASSINFO* info);
    void sig_Deliver(QList<FlawPoint>* Points);// emit sig_Deliver(Points);
    void sig_UpdateResultInfo(ResultINFO *result);
    void sig_updateSortRes(ResultINFO *result);
    void sig_updateSignalFlaw(QString id);
//    void sig_SignalLight(unsigned int a);

public slots:
    void slot_updateSortInfo();
//    void slot_ClearDate();
};

#endif // PROCESS_DETECT_H

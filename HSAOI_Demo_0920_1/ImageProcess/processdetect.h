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
#include "Global.h"
#include "log_singleton.h"
#include <QSettings>
#include "HDevEngineCpp.h"
#include "HalconCpp.h"
#include "FlawDefine.h"

using namespace HalconCpp;
using namespace HDevEngineCpp;


class Process_Detect : public QObject {
    Q_OBJECT
public:
    Process_Detect();
    ~Process_Detect();

public:
    void VisionProcess(ImageUnit imageQueue, HoleUnit holeunit);
    void DetectSiYin(HoleUnit holeunit,ProcessHolesAlgorithmResults& procesHoleResult);
    void SummaryResults(GlassDataBaseInfo baseinfo);
    void SummaryFailResult();
    void DetectData2Json(DefeteResult result);
    void HolesData2Json(ProcessHolesAlgorithmResults procesHoleResult);
    void Glassinfo(ProcessVisionAlgorithmResults result, GlassDataBaseInfo& baseinfo);
    void saveErrImage(ProcessVisionAlgorithmResults result, DefeteResult& defect);
    void funcSaveErrImage();
    void writeHoleDataToJsonfile(HoleResult holeresult);
    bool isExistDir(QString dirpath);

signals:
    void sendData(GlassDataBaseInfo info);              // 信息统计表格中插入一行数据
    void sig_updateFlaw(double length,double width);    // 更新最外框轮廓
    void sig_Deliver(QList<FlawPoint>* Points);         //将缺陷点传输给缺陷框架
    void sig_updateSortRes(SummaryResult summaryResult);//更新标题框上的检出和分检
    void sig_updateSignalFlaw(QString id, QString date);//更新缺陷小图信息
    void sig_refreshFlaw(QString glassid);              //实时刷新缺陷小图
    void sig_refreshSize(QString glassid);              //实时刷新尺寸小图
    void sig_UpdateResultInfo(SummaryResult);           //更新缺陷界面的统计信息


public slots:
    void slot_updateSortInfo();

private:
     int GlassPosition;                 //玻璃位置(0整1前2中3后)
     int ProcessStep;                   //当前执行帧步
     int m_FramesPerTri;                //帧次
     bool ResultNotOutFlag;             //记录上一次输出结果
     bool ErrFlag;                      //是否发生错误

     HDevEngine* engine;                //halcon算法引擎
     HDevProcedure* procedure;          //缺陷检出算法
     HDevProcedureCall* procedurecall;
     HDevProcedure* procedure2;
     HDevProcedureCall* procedurecall2;
     QString engine_path;               //算法检出地址
     HTuple YCoordIn;
     HTuple YCoordOut;

     QList<FlawPoint>* Points;          //缺陷点
     SafeQueue<std::tuple<QString, HObject>> threadQueue; //线程安全的缺陷小图队列
     std::atomic<bool> hasStopThread;    //线程停止
     QDateTime currentTimeJson;       //json文件名时间点
     bool onceCall;                 //只调用一次
     SummaryResult summaryResult; //玻璃总的结果
};

#endif // PROCESS_DETECT_H

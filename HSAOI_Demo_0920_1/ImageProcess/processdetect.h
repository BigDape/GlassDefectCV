﻿/*******************************************
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
#include <QThreadPool>
#include <QDebug>
#include <QElapsedTimer>
#include <QMutex>

using namespace HalconCpp;
using namespace HDevEngineCpp;


class Process_Detect : public QObject,public QRunnable
{
    Q_OBJECT
public:
    Process_Detect();
    ~Process_Detect();

public:
    void VisionProcess(ImageUnit imageQueue, HoleUnit holeunit);
    void saveHoleImage(HoleUnit holeunit);
    void SummaryResults(GlassDataBaseInfo baseinfo);
    void SummaryFailResult();
    void Glassinfo(ProcessVisionAlgorithmResults result, GlassDataBaseInfo& baseinfo);
    void saveErrImage(ProcessVisionAlgorithmResults result);
    bool isExistDir(QString dirpath);
    void writeImage(HalconCpp::HObject imag1,
                                         HalconCpp::HObject imag2,
                                         HalconCpp::HObject imag3,
                                         QString ImageNGPath1,
                                         QString ImageNGPath2,
                                         QString ImageNGPath3);

public:
    virtual void run() override;

signals:
    void sendData(GlassDataBaseInfo info);              // 信息统计表格中插入一行数据
    void sig_updateFlaw(double length,double width);    // 更新最外框轮廓
    void sig_sendPoint(QList<FlawPoint> Points);         //将缺陷点传输给缺陷框架
    void sig_updateSortRes(SummaryResult summaryResult);//更新标题框上的检出和分检
    void sig_updateSignalFlaw(QString jsonPath65, int id);//更新缺陷小图信息
    void sig_refreshFlaw(QString jsonFullPath,int glassid);              //实时刷新缺陷小图
    void sig_refreshSize(QString jsonFullPath,int glassid);              //实时刷新尺寸小图
    void sig_UpdateResultInfo(SummaryResult);           //更新缺陷界面的统计信息


public slots:
    void slot_updateSortInfo();

public:
    QList<FlawPoint> Points;          //缺陷点
    std::atomic<bool> hasStopThread;    //线程停止

private:
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
     bool onceCall;                 //只调用一次
     SummaryResult summaryResult; //玻璃总的结果
     HTuple aaa;
    GlassDataBaseInfo baseinfo;//总结数据
};

#endif // PROCESS_DETECT_H

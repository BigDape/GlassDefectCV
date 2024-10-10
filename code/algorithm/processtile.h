﻿#ifndef PROCESSTILE_H
#define PROCESSTILE_H

#include "HDevEngineCpp.h"
#include "HalconCpp.h"
#include <QObject>
#include <QQueue>
#include <QString>
#include <QtDebug>
#include <QThreadPool>
#include "hstool.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "processdetect.h"

class ProcessTile : public QObject
{
    Q_OBJECT
public:
    int MosaickNum;
    std::atomic<bool> hasStopThread;    //线程停止
public:
    ProcessTile();
    void OfflineTileImageProcess(QString fullpath);

    void CV_DefectsDetected(cv::Mat image1, cv::Mat image2, cv::Mat image3);

private:
    void saveMatToImage(QString fullpath,cv::Mat& region);
    void cropRectangleMat(const cv::Mat image, cv::Mat &dst, int row1y, int Column1x, int row2y, int Column2x);
    void prewittEdgeDetection(cv::Mat& src, cv::Mat& dst); //Prewitt边缘检测
    void getBaseLineFromImage(cv::Mat& region, cv::Mat& baseline);//获取基准矩阵
    void edgeDefectDetection(cv::Mat& region,
                             std::vector<cv::Mat>& edgeregions,
                             int topAddition,
                             int bottomAddition,
                             int leftAddition,
                             int rightAddition);//边部缺陷检出

private:
    std::shared_ptr<Process_Detect> cvUnitPtr;
};


#endif // PROCESSTILE_H

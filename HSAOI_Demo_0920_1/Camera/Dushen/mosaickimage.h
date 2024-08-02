/*******************************************
    @ClassName   : MosaickImage
    @Description : Description
    @Creator     : Yangruyi
    @Author      : Yangruyi
    @Date        : 2023-09-19
********************************************/
#ifndef MOSAICKIMAGE_H
#define MOSAICKIMAGE_H

#include <HalconCpp.h>
#include <QDebug>
#include <QElapsedTimer>
#include <QImage>
#include <QObject>
#include <QThread>
#include <QThreadPool>
#include "HalconCpp.h"
#include "FlawDefine.h"

using namespace HalconCpp;

struct MosaickArg{
    QList<HObject> CameraImageList;
    int channel;
    HObject PrepareImage;
};

class MosaickImage:public QObject
{
    Q_OBJECT
public:
    MosaickImage();
    MosaickImage( const MosaickImage& mo);            // Declare copy constructor.
    MosaickImage& operator=(const MosaickImage& mo);
    void DoMosaick(QList<HObject> CameraImageList,
                   int channel,
                   HObject PrepareImage,
                   HObject& FiledImage);
    HObject run();

public:
    SafeQueue<MosaickArg> mosaickQueue;
    HObject MosaickResultImage;
};

//class ThreadDo : public QThread {
//    Q_OBJECT
//public:
//    explicit ThreadDo(QObject* parent = nullptr);
//    void run() override;

//public:
//    int channel;
//    MosaickImage* MosaickProcess;
//    HObject PrepareImage;
//    HObject CameraImage1, CameraImage2, CameraImage3, CameraImage4;
//    HObject MosaickResultImage;
//    QList<HObject> CameraImageList;

//};

#endif // MOSAICKIMAGE_H

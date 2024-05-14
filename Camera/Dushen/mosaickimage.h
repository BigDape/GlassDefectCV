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

#include "HalconCpp.h"

using namespace HalconCpp;

class MosaickImage {
public:
    MosaickImage();
    void DoMosaick(HObject CameraImage1,
                   HObject CameraImage2,
                   HObject CameraImage3,
                   HObject CameraImage4,
                   HObject PrepareImage,
                   HObject& FiledImage);

    void DoMosaick(QList<HObject> CameraImageList,
                   int channel,
                   HObject PrepareImage,
                   HObject& FiledImage);
};

class ThreadDo : public QThread {
    Q_OBJECT
public:
    explicit ThreadDo(QObject* parent = nullptr);
    void run() override;

public:
    int channel;
    MosaickImage* MosaickProcess;
    HObject PrepareImage;
    HObject CameraImage1, CameraImage2, CameraImage3, CameraImage4;
    HObject MosaickResultImage;
    QList<HObject> CameraImageList;

};

#endif // MOSAICKIMAGE_H

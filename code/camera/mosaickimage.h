#ifndef MOSAICKIMAGE_H
#define MOSAICKIMAGE_H

#include <QDebug>
#include <QElapsedTimer>
#include <QImage>
#include <QObject>
#include <QThread>


class MosaickImage {
public:
    MosaickImage();


    void DoMosaick(/*QList<HObject> CameraImageList,int channel,HObject PrepareImage,HObject& FiledImage*/);

    QImage horizontalConcat(const QImage& img1, const QImage& img2);
    QImage verticalConcat(const QImage& img1, const QImage& img2);
};

class ThreadDo : public QThread {
    Q_OBJECT
public:
    explicit ThreadDo(QObject* parent = nullptr);
    void run() override;

public:
    int channel;
    MosaickImage* MosaickProcess;
//    HObject PrepareImage;
//    HObject CameraImage1, CameraImage2, CameraImage3, CameraImage4;
//    HObject MosaickResultImage;
//    QList<HObject> CameraImageList;

};

#endif // MOSAICKIMAGE_H

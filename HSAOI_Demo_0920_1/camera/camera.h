#ifndef CAMERA_H
#define CAMERA_H

#include "camera_global.h"
#include "Dushen/cameraslayout.h"

class CAMERA_EXPORT Camera
{
public:
    Camera();

    void InitCamera(QWidget* parent,std::vector<DushenCameraArgs> args); //初始化相机

    void startCamera(); //相机开始采集

    void stopCamera(); //相机停止采集

    void getFrameImage();//获取每帧图片

    QWidget* getCamerasWidget();
private:
    CamerasLayout* widgets;
};

#endif // CAMERA_H

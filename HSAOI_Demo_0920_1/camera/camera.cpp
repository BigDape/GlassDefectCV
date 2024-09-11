#include "camera.h"
#include "Dushen/DushenCameraWidget.h"
#include "Dushen/DushenBasicFunc.h"

Camera::Camera()
    :widgets(NULL)
{

}

//初始化相机
void Camera::InitCamera(QWidget* parent,std::vector<DushenCameraArgs> args)
{
    widgets =  new CamerasLayout(parent);
    widgets->InitCameras(args);
}

//相机开始采集
void Camera::startCamera()
{
    if(widgets != NULL) {
        widgets->StartCameras();
    }
}

//相机停止采集
void Camera::stopCamera()
{
    if(widgets != NULL) {
        widgets->StopCameras();
    }
}

QWidget* Camera::getCamerasWidget()
{
    if(widgets != NULL) {
        return widgets;
    }
}

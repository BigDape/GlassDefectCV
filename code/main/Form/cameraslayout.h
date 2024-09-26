#ifndef CAMERASLAYOUT_H
#define CAMERASLAYOUT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QList>
#include "hstool.h"

namespace Ui {
class CamerasLayout;
}

class CamerasLayout : public QWidget
{
    Q_OBJECT

public:
    explicit CamerasLayout(QWidget* parent);
    ~CamerasLayout();

    void InitCameras(std::vector<DushenCameraArgs> args); //初始化相机界面
private:
    Ui::CamerasLayout*  ui;
    QHBoxLayout*        hbox_layout;        // 布局容器
    std::vector<std::shared_ptr<ThreadSafeQueue<FrameImage>>> CamresQueue;
};

#endif // CAMERASLAYOUT_H

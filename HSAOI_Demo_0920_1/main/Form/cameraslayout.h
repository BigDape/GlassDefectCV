#ifndef CAMERASLAYOUT_H
#define CAMERASLAYOUT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QList>


namespace Ui {
class CamerasLayout;
}

struct DushenCameraArgs;
template<typename T> class ThreadSafeQueue;
struct FrameImage;

class CamerasLayout : public QWidget
{
    Q_OBJECT

public:
    explicit CamerasLayout(QWidget* parent);
    ~CamerasLayout();

    void InitCameras(std::vector<DushenCameraArgs> args); //初始化相机界面
    void StartCameras();  // 相机开始采集
    void StopCameras();   // 相机停止采集
    void EndCameras();    // 相机结束采集
    void getResult();     // 获取采集结果
private:
    Ui::CamerasLayout *ui;
    QHBoxLayout*        hbox_layout;        // 布局容器
    std::vector<std::shared_ptr<ThreadSafeQueue<FrameImage>>> CamresQueue;
};

#endif // CAMERASLAYOUT_H

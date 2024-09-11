#include "cameraslayout.h"
#include "ui_cameraslayout.h"
#include "DushenCameraWidget.h"
#include "DushenBasicFunc.h"

CamerasLayout::CamerasLayout(QWidget* parent)
    : QWidget(parent),
    ui(new Ui::CamerasLayout)
{
    ui->setupUi(this);
    hbox_layout = new QHBoxLayout(this);
    this->setLayout(hbox_layout);
}

CamerasLayout::~CamerasLayout()
{
    if(hbox_layout != NULL) {
        delete hbox_layout;
    }
    if(ui!=NULL) {
        delete ui;
    }
}

void CamerasLayout::InitCameras(std::vector<DushenCameraArgs> args)
{
    for(int i=0; i < (int)args.size(); i++){
        DushenCameraWidget * camerawid = new DushenCameraWidget(this, args[i]);
        std::shared_ptr<ThreadSafeQueue<FrameImage>> queue = std::make_shared<ThreadSafeQueue<FrameImage>>();
        camerawid->setThreadSafeQueue(queue);
        CamresQueue.push_back(queue);
        hbox_layout->addWidget(camerawid);
    }
}

void CamerasLayout::StartCameras()
{

}

void CamerasLayout::StopCameras()
{

}

void CamerasLayout::EndCameras()
{

}

void CamerasLayout::getResult()
{

}




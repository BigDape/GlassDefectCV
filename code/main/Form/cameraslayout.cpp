#include "cameraslayout.h"
#include "ui_cameraslayout.h"
#include "DushenCameraWidget.h"

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
        hbox_layout->addWidget(camerawid);
    }
}





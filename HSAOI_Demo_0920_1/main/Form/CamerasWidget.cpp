#include "CamerasWidget.h"
#include "Global.h"
#include "ui_CamerasWidget.h"
#pragma execution_character_set("utf-8")

CamerasWidget::CamerasWidget(QWidget* parent, QList<DushenBasicFunc*> ListCamera,int num)
    : QWidget(parent)
    , ui(new Ui::CamerasWidget)
{
    ui->setupUi(this);
    CameraNum=num;
    hbox_layout = new QHBoxLayout(this);
    InitCameras(ListCamera);
    this->setLayout(hbox_layout);
}

CamerasWidget::~CamerasWidget() { delete ui; }

void CamerasWidget::InitCameras(QList<DushenBasicFunc*> ListCamera)
{
    for(int i=0;i<CameraNum;i++){
        DushenCameraWidget * camerawid=new DushenCameraWidget(this,Global::camListName[i],i,ListCamera[i]);
        connect(this,&CamerasWidget::sig_CameraStart,camerawid,&DushenCameraWidget::slot_StartCamera);
        connect(this,&CamerasWidget::sig_CameraStop,camerawid,&DushenCameraWidget::slot_CameraStop);
        hbox_layout->addWidget(camerawid);
    }
}

void CamerasWidget::slot_CameraStart()
{
    emit sig_CameraStart();
}

void CamerasWidget::slot_CameraStop()
{
    emit sig_CameraStop();
}

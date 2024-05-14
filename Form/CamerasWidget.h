/*******************************************
    @ClassName   : CamerasWidget
    @Description : Description
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-09-04
********************************************/
#ifndef CAMERASWIDGET_H
#define CAMERASWIDGET_H

#include "Camera/Dushen/DushenBasicFunc.h"
#include "Camera/Dushen/DushenCameraWidget.h"
#include <QHBoxLayout>
#include <QWidget>
#include<QList>

namespace Ui {
class CamerasWidget;
}

class CamerasWidget : public QWidget {
    Q_OBJECT

public:
    explicit CamerasWidget(QWidget* parent = nullptr,QList<DushenBasicFunc*> ListCamera=QList<DushenBasicFunc*>(),int num=0);
    ~CamerasWidget();

private:
    Ui::CamerasWidget* ui;
    QHBoxLayout* hbox_layout;
    QList<DushenBasicFunc*> listCamera;
    QList<DushenCameraWidget*> listWidget;
    int CameraNum;

    void InitCameras(QList<DushenBasicFunc*> ListCamera);

public slots:
    void slot_CameraStart();
    void slot_CameraStop();
signals:
    void sig_CameraStart();
    void sig_CameraStop();
};

#endif // CAMERASWIDGET_H

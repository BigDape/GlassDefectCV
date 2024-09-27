#include "Calibrate.h"
#include "ui_Calibrate.h"

Calibrate::Calibrate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calibrate)
{
    ui->setupUi(this);
}

Calibrate::~Calibrate()
{
    delete ui;
}

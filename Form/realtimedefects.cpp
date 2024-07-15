#include "realtimedefects.h"
#include "ui_realtimedefects.h"

RealtimeDefects::RealtimeDefects(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RealtimeDefects)
{
    ui->setupUi(this);
}

RealtimeDefects::~RealtimeDefects()
{
    delete ui;
}

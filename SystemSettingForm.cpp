﻿#include "SystemSettingForm.h"
#include "NavigationBar/CNavDelegate.h"
#include "NavigationBar/CNavModel.h"
#include "ui_SystemSettingForm.h"
#pragma execution_character_set("utf-8")

SystemSettingForm::SystemSettingForm(RegParasComm& sig_comm, JsonParse2Map& JsonRecipe, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SystemSettingForm)
    , m_pSig_comm(sig_comm)
    , JSONRECIPE(JsonRecipe)
{
    ui->setupUi(this);

    stack_widget = new QStackedWidget(this);
    List_View = new QListView(this);
    SigCtrlData = new SignalControlData(sig_comm);

    InitForm();

    QHBoxLayout* hbox = new QHBoxLayout();
    setLayout(hbox);
    hbox->addWidget(List_View); //加入导航栏
    hbox->addWidget(stack_widget); //导航栏列表

    SetNavigationBar();
}

SystemSettingForm::~SystemSettingForm()
{
    delete ui;
}

void SystemSettingForm::SetNavigationBar()
{
    CNavModel* pNavModel = new CNavModel(this);
    CNavDelegate* pDelegate = new CNavDelegate(this);
    pNavModel->ReadConfig("SystemParam/navigation.xml");
    pNavModel->ExpandAllNodes();

    List_View->setModel(pNavModel);
    List_View->setItemDelegate(pDelegate);

    connect(List_View, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_ListView_Pressed()));
}

void SystemSettingForm::InitForm()
{
    List_View->setFixedWidth(180);
    this_JsonRecipeWidget = new JsonRecipeWidget(this, &JSONRECIPE,"工单");
    stack_widget->addWidget(this_JsonRecipeWidget);

    cameraRecipeWidget = new JsonRecipeWidget(this, &JSONRECIPE,"相机");
    stack_widget->addWidget(cameraRecipeWidget);

    LightControlWidget = new LightControl(m_pSig_comm, this);
    stack_widget->addWidget(LightControlWidget);

    //1、修改json配置文件
    connect(this_JsonRecipeWidget, SIGNAL(sig_DeliverName(QString)), this, SLOT(slot_JsonRecipeName_Changed(QString)));
    connect(this, SIGNAL(sig_Deliver_NewRecipe(JsonParse2Map*)), this_JsonRecipeWidget, SLOT(slot_RecipeChanged(JsonParse2Map*)));
    connect(this_JsonRecipeWidget, SIGNAL(sig_CameraParamsChangeRecipe()), cameraRecipeWidget, SLOT(ReadValue2Tree()));
    connect(this_JsonRecipeWidget, SIGNAL(sig_LightControlChange()), SigCtrlData, SLOT(slot_DeliverLightData()));
    connect(SigCtrlData, SIGNAL(sig_RecipeChage()), LightControlWidget, SLOT(slot_InitTree()));
}

void SystemSettingForm::slot_ListView_Pressed()
{
    QModelIndex index = List_View->currentIndex();
    int num = index.row();
    QString text = index.data().toString();

    if (num == 3) {
        stack_widget->setCurrentIndex(2);
    } else if (num == 1) {
        stack_widget->setCurrentIndex(0);
    } else if (num == 2) {
        stack_widget->setCurrentIndex(1);
    } else if (num == 5) {
        stack_widget->setCurrentIndex(0);
    } else if (num == 6) {
        stack_widget->setCurrentIndex(0);
    } else if (num == 4) {
        stack_widget->setCurrentIndex(0);
    } else {
    }
}

void SystemSettingForm::slot_JsonRecipe_Changed(JsonParse2Map* NewRecipe)
{
    emit sig_Deliver_NewRecipe(NewRecipe);
}

void SystemSettingForm::slot_JsonRecipeName_Changed(QString NewRecipeName)
{
    emit sig_Deliver_NewRecipeName2mainWindow(NewRecipeName);
}

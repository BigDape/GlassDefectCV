#include "LightControl.h"
#include "ui_LightControl.h"
#include <QMessageBox>
#include <QTimer>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Parameter/json.h"
#include "HsListener.h"
#include "Global.h"

#pragma execution_character_set("utf-8")
#define NO_TCP_SET_BUTTON_(ui_x,ui_name) do {PARAM.set##ui_name(ui_x); \
                                            INFOMATION.informationMessageBox(this,"设置对话框","设置成功"); } while (0)
#define NO_TCP_SET_BUTTON_DEFINITION(ui_x,ui_name) void LightControl::slotSetBT##ui_name(){NO_TCP_SET_BUTTON_(ui_x,ui_name);}


LightControl::LightControl(RegParasComm& sig_comm, QWidget* parent)
    : QWidget(parent)
    ,m_pSig_comm(sig_comm)
    , ui(new Ui::LightControl)
{
    ui->setupUi(this);

    SigCtrlData = new SignalControlData(sig_comm);
    sigctrl = new SignalControl();


    // 加载当前的工单
    // 给每个输入框赋值
    LightControl::InitLightControl();

//    ui->treeWidget->setColumnWidth(0, 230);

//    Layout0 = new QHBoxLayout(this);
//    Layout1 = new QVBoxLayout(this);

//    this->setLayout(Layout0);
//    Layout0->addWidget(ui->treeWidget);

//    Layout0->addLayout(Layout1);

//    Layout1->addWidget(ui->Get);
//    Layout1->addWidget(ui->Set);
//    Layout1->addWidget(ui->Save);
//    Layout1->addWidget(ui->Trigger);
//    Layout1->setAlignment(Qt::AlignTop);

//    ui->Get->setText("获取参数");
//    ui->Set->setText("设置参数");
//    ui->Save->setText("保存参数");
//    ui->Trigger->setText("触发");

//    specificItem0 = ui->treeWidget->topLevelItem(0);        //编码器参数
//    childItem0 = specificItem0->child(0);                   // 编码器单位刻度对应距离(um)
//    childItem1 = specificItem0->child(1);                   // 编码脉冲滤波(us)
//    childItem2 = specificItem0->child(2);                   // 编码器计数结束标志
//    childItem3 = specificItem0->child(3);                   // 编码器计数
//    childItem4 = specificItem0->child(4);                   // 编码器触发行计数
//    childItem5 = specificItem0->child(5);                   // 编码器4倍频计数
//    childItem6 = specificItem0->child(6);                   // 编码器单位时间脉冲计数
//    childItem7 = specificItem0->child(7);                   // 编码器计数时间(0.5s)
//    childItem8 = specificItem0->child(8);                   // 编码通道
//    childItem9 = specificItem0->child(9);                   // 编码器转数
//    childItem10 = specificItem0->child(10);                 // 辊道周长(um)
//    childItem11 = specificItem0->child(11);                 // 期望单个像素精度(um)
//    childItem12 = specificItem0->child(12);                 // 辊道最大速度对应行频
//    childItem13 = specificItem0->child(13);                 // 每行对应的编码计数
//    childItem_rollerACount = specificItem0->child(14);      // 压轮编码器A计数
//    childItem_rollerBCount = specificItem0->child(15);      // 压轮编码器B计数
//    childItemAB4 = specificItem0->child(16);                // 压轮编码器4倍频计数
//    chileItem_rollerCofficient = specificItem0->child(17);  // 压轮编码器系数

//    specificItem1 = ui->treeWidget->topLevelItem(1);        //控制器系统参数
//    childItem14 = specificItem1->child(0);                  //像素精度(um)
//    childItem15 = specificItem1->child(1);                  //光电信号脉冲滤波(us)
//    childItem16 = specificItem1->child(2);                  //相机触发脉冲持续时间(10ns)
//    childItem17 = specificItem1->child(3);                  //光电相机距离(行)
//    childItem18 = specificItem1->child(4);                  //相机帧信号触发延时行数(行)
//    childItem19 = specificItem1->child(5);                  //帧信号持续时间(10ns)
//    childItem20 = specificItem1->child(6);                  //模块使能信号
//    childItem21 = specificItem1->child(7);                  //相机拍照行数(行)
//    childItem22 = specificItem1->child(8);                  //内部行频
//    chileItem_photoMode = specificItem1->child(9);          //拍照模式
//    chileItem_photoEndDelayLine = specificItem1->child(10); //拍照结束延时行数

//    specificItem2 = ui->treeWidget->topLevelItem(2);//光源控制器参数
//    childItem23 = specificItem2->child(0);          // 光场1延时时间(10ns)
//    childItem24 = specificItem2->child(1);          // 光场1发光时间(10ns)
//    childItem25 = specificItem2->child(2);          // 光场2延时时间(10ns)
//    childItem26 = specificItem2->child(3);          // 光场2发光时间(10ns)
//    childItem27 = specificItem2->child(4);          // 光场3延时时间(10ns)
//    childItem28 = specificItem2->child(5);          // 光场3发光时间(10ns)
//    childItem29 = specificItem2->child(6);          // 光场4延时时间(10ns)
//    childItem30 = specificItem2->child(7);          // 光场4发光时间(10ns)
//    childItem31 = specificItem2->child(8);          // 光场5延时时间(10ns)
//    childItem32 = specificItem2->child(9);          // 光场5发光时间(10ns)
//    childItem33 = specificItem2->child(10);         // 光场6延时时间(10ns)
//    childItem34 = specificItem2->child(11);         // 光场6发光时间(10ns)
//    childItem35 = specificItem2->child(26);         // 35相机与光场控制
//    childItem36 = specificItem2->child(27);         // 36信号切换
//    childItem37 = specificItem2->child(28);         // 37行信号源选择
//    childItem43 = specificItem2->child(12);         // 光场7延时时间(10ns)
//    childItem44 = specificItem2->child(13);         // 光场7发光时间(10ns)
//    childItem45 = specificItem2->child(14);         // 光场8延时时间(10ns)
//    childItem46 = specificItem2->child(15);         // 光场8发光时间(10ns)
//    childItem47 = specificItem2->child(16);         // 光场9延时时间(10ns)
//    childItem48 = specificItem2->child(17);         // 光场9发光时间(10ns)
//    childItem49 = specificItem2->child(18);         // 光场10延时时间(10ns)
//    childItem50 = specificItem2->child(19);         // 光场10发光时间(10ns)
//    childItem51 = specificItem2->child(20);         // 光场11延时时间(10ns)
//    childItem52 = specificItem2->child(21);         // 光场11发光时间(10ns)
//    childItem53 = specificItem2->child(22);         // 光场12延时时间(10ns)
//    childItem54 = specificItem2->child(23);         // 光场12发光时间(10ns)
//    childItem55 = specificItem2->child(24);         // 选择光场的数量
//    childItem56 = specificItem2->child(25);         // 横向暗场选择寄存器


//    slot_InitTree();
//    ui->treeWidget->expandAll();
//    timer1=new QTimer();
//    connect(timer1,&QTimer::timeout,this,&LightControl::slot_updateCode);
//    timer1->start(100);

}

void LightControl::onItemDoubleClicked(QTreeWidgetItem* item, int column)
{
    if ( itemMap.find(item) != itemMap.end()) {
        qDebug() <<"Item = "<<itemMap[item];
    } else {
        qDebug()<<"Unknow";
    }

    if (column == 1) { // Check if the clicked column is not the second column
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    } else {
        item->setFlags(item->flags() & ~(Qt::ItemIsEditable));
    }

}

LightControl::~LightControl()
{
    delete ui;
}

void LightControl::slot_InitTree()//初始化工单，在进入软件以及切换工单时会调用
{
    SigCtrlData->InitData();

//    childItem0->setText(1, QString::number(SigCtrlData->sigctrl->temp0));
//    childItem1->setText(1, QString::number(SigCtrlData->sigctrl->temp1));
//    childItem2->setText(1, QString::number(SigCtrlData->sigctrl->temp2));
////    childItem3->setText(1, QString::number(SigCtrlData->sigctrl->temp3));
//    childItem4->setText(1, QString::number(SigCtrlData->sigctrl->temp4));
////    childItem5->setText(1, QString::number(SigCtrlData->sigctrl->temp5));
////    childItem6->setText(1, QString::number(SigCtrlData->sigctrl->temp6));
//    childItem7->setText(1, QString::number(SigCtrlData->sigctrl->temp7));
//    childItem8->setText(1, QString::number(SigCtrlData->sigctrl->temp8));
//    childItem9->setText(1, QString::number(SigCtrlData->sigctrl->temp9));
//    childItem10->setText(1, QString::number(SigCtrlData->sigctrl->temp10));
//    childItem11->setText(1, QString::number(SigCtrlData->sigctrl->temp11));
//    childItem12->setText(1, QString::number(SigCtrlData->sigctrl->temp12));
//    childItem13->setText(1, QString::number(SigCtrlData->sigctrl->temp13));
//    childItem14->setText(1, QString::number(SigCtrlData->sigctrl->temp14));
//    childItem15->setText(1, QString::number(SigCtrlData->sigctrl->temp15));
//    childItem16->setText(1, QString::number(SigCtrlData->sigctrl->temp16));
//    childItem17->setText(1, QString::number(SigCtrlData->sigctrl->temp17));
//    childItem18->setText(1, QString::number(SigCtrlData->sigctrl->temp18));
//    childItem19->setText(1, QString::number(SigCtrlData->sigctrl->temp19));
//    childItem20->setText(1, QString::number(SigCtrlData->sigctrl->temp20));
//    childItem21->setText(1, QString::number(SigCtrlData->sigctrl->temp21));
//    childItem22->setText(1, QString::number(SigCtrlData->sigctrl->temp22));
//    childItem23->setText(1, QString::number(SigCtrlData->sigctrl->temp23));
//    childItem24->setText(1, QString::number(SigCtrlData->sigctrl->temp24));
//    childItem25->setText(1, QString::number(SigCtrlData->sigctrl->temp25));
//    childItem26->setText(1, QString::number(SigCtrlData->sigctrl->temp26));
//    childItem27->setText(1, QString::number(SigCtrlData->sigctrl->temp27));
//    childItem28->setText(1, QString::number(SigCtrlData->sigctrl->temp28));
//    childItem29->setText(1, QString::number(SigCtrlData->sigctrl->temp29));
//    childItem30->setText(1, QString::number(SigCtrlData->sigctrl->temp30));
//    childItem31->setText(1, QString::number(SigCtrlData->sigctrl->temp31));
//    childItem32->setText(1, QString::number(SigCtrlData->sigctrl->temp32));
//    childItem33->setText(1, QString::number(SigCtrlData->sigctrl->temp33));
//    childItem34->setText(1, QString::number(SigCtrlData->sigctrl->temp34));
//    //16进制显示
//    childItem35->setText(1, QString::number(SigCtrlData->sigctrl->temp35,16));
//    childItem36->setText(1, QString::number(SigCtrlData->sigctrl->temp36));
//    childItem37->setText(1, QString::number(SigCtrlData->sigctrl->temp37));

//    childItem43->setText(1, QString::number(SigCtrlData->sigctrl->temp43));
//    childItem44->setText(1, QString::number(SigCtrlData->sigctrl->temp44));
//    childItem45->setText(1, QString::number(SigCtrlData->sigctrl->temp45));
//    childItem46->setText(1, QString::number(SigCtrlData->sigctrl->temp46));
//    childItem47->setText(1, QString::number(SigCtrlData->sigctrl->temp47));
//    childItem48->setText(1, QString::number(SigCtrlData->sigctrl->temp48));
//    childItem49->setText(1, QString::number(SigCtrlData->sigctrl->temp49));
//    childItem50->setText(1, QString::number(SigCtrlData->sigctrl->temp50));
//    childItem51->setText(1, QString::number(SigCtrlData->sigctrl->temp51));
//    childItem52->setText(1, QString::number(SigCtrlData->sigctrl->temp52));
//    childItem53->setText(1, QString::number(SigCtrlData->sigctrl->temp53));
//    childItem54->setText(1, QString::number(SigCtrlData->sigctrl->temp54));
//    childItem55->setText(1, QString::number(SigCtrlData->sigctrl->temp55));
//    childItem56->setText(1, QString::number(SigCtrlData->sigctrl->temp56));

//    PARAM.setFieldNumberSet(SigCtrlData->sigctrl->temp55);//选择光场的数量
//    childItem_rollerACount->setText(1,QString::number(SigCtrlData->sigctrl->tempRollerACount));
//    childItem_rollerBCount->setText(1,QString::number(SigCtrlData->sigctrl->tempRollerBCount));
//    childItemAB4->setText(1, QString::number(SigCtrlData->sigctrl->tempRoller4ABCount));
//    chileItem_rollerCofficient->setText(1,QString::number(SigCtrlData->sigctrl->tempRollerCofficient));

//    chileItem_photoMode->setText(1,QString::number(SigCtrlData->sigctrl->tempAutoPhoto));
//    chileItem_photoEndDelayLine->setText(1,QString::number(SigCtrlData->sigctrl->tempPhotoEndDelayLine));

//    QString strCo=chileItem_rollerCofficient->text(1);
//    PARAM.setEncodeRollerCofficient(strCo.toDouble());
}

void LightControl::slot_getButton_clicked()
{
    SigCtrlData->GetData();

//    childItem0->setText(1, QString::number(SigCtrlData->sigctrl->temp0));
//    childItem1->setText(1, QString::number(SigCtrlData->sigctrl->temp1));
//    childItem2->setText(1, QString::number(SigCtrlData->sigctrl->temp2));
//    childItem4->setText(1, QString::number(SigCtrlData->sigctrl->temp4));
//    childItem7->setText(1, QString::number(SigCtrlData->sigctrl->temp7));
//    childItem8->setText(1, QString::number(SigCtrlData->sigctrl->temp8));
//    childItem9->setText(1, QString::number(SigCtrlData->sigctrl->temp9));
//    childItem10->setText(1, QString::number(SigCtrlData->sigctrl->temp10));
//    childItem11->setText(1, QString::number(SigCtrlData->sigctrl->temp11));
//    childItem12->setText(1, QString::number(SigCtrlData->sigctrl->temp12));
//    childItem13->setText(1, QString::number(SigCtrlData->sigctrl->temp13));
//    childItem14->setText(1, QString::number(SigCtrlData->sigctrl->temp14));
//    childItem15->setText(1, QString::number(SigCtrlData->sigctrl->temp15));
//    childItem16->setText(1, QString::number(SigCtrlData->sigctrl->temp16));
//    childItem17->setText(1, QString::number(SigCtrlData->sigctrl->temp17));
//    childItem18->setText(1, QString::number(SigCtrlData->sigctrl->temp18));
//    childItem19->setText(1, QString::number(SigCtrlData->sigctrl->temp19));
//    childItem20->setText(1, QString::number(SigCtrlData->sigctrl->temp20));
//    childItem21->setText(1, QString::number(SigCtrlData->sigctrl->temp21));
//    childItem22->setText(1, QString::number(SigCtrlData->sigctrl->temp22));
//    childItem23->setText(1, QString::number(SigCtrlData->sigctrl->temp23));
//    childItem24->setText(1, QString::number(SigCtrlData->sigctrl->temp24));
//    childItem25->setText(1, QString::number(SigCtrlData->sigctrl->temp25));
//    childItem26->setText(1, QString::number(SigCtrlData->sigctrl->temp26));
//    childItem27->setText(1, QString::number(SigCtrlData->sigctrl->temp27));
//    childItem28->setText(1, QString::number(SigCtrlData->sigctrl->temp28));
//    childItem29->setText(1, QString::number(SigCtrlData->sigctrl->temp29));
//    childItem30->setText(1, QString::number(SigCtrlData->sigctrl->temp30));
//    childItem31->setText(1, QString::number(SigCtrlData->sigctrl->temp31));
//    childItem32->setText(1, QString::number(SigCtrlData->sigctrl->temp32));
//    childItem33->setText(1, QString::number(SigCtrlData->sigctrl->temp33));
//    childItem34->setText(1, QString::number(SigCtrlData->sigctrl->temp34));
//    childItem35->setText(1, QString::number(SigCtrlData->sigctrl->temp35,16));
//    childItem36->setText(1, QString::number(SigCtrlData->sigctrl->temp36));
//    childItem37->setText(1, QString::number(SigCtrlData->sigctrl->temp37));

//    childItem43->setText(1, QString::number(SigCtrlData->sigctrl->temp43));
//    childItem44->setText(1, QString::number(SigCtrlData->sigctrl->temp44));
//    childItem45->setText(1, QString::number(SigCtrlData->sigctrl->temp45));
//    childItem46->setText(1, QString::number(SigCtrlData->sigctrl->temp46));
//    childItem47->setText(1, QString::number(SigCtrlData->sigctrl->temp47));
//    childItem48->setText(1, QString::number(SigCtrlData->sigctrl->temp48));
//    childItem49->setText(1, QString::number(SigCtrlData->sigctrl->temp49));
//    childItem50->setText(1, QString::number(SigCtrlData->sigctrl->temp50));
//    childItem51->setText(1, QString::number(SigCtrlData->sigctrl->temp51));
//    childItem52->setText(1, QString::number(SigCtrlData->sigctrl->temp52));
//    childItem53->setText(1, QString::number(SigCtrlData->sigctrl->temp53));
//    childItem54->setText(1, QString::number(SigCtrlData->sigctrl->temp54));
//    childItem55->setText(1, QString::number(SigCtrlData->sigctrl->temp55));
//    childItem56->setText(1, QString::number(SigCtrlData->sigctrl->temp56));

//    QString strCo=chileItem_rollerCofficient->text(1);
//    PARAM.setEncodeRollerCofficient(strCo.toDouble());
}

void LightControl::slot_setButton_clicked()
{
//    SigCtrlData->sigctrl->temp0 = childItem0->text(1).toUInt();
//    SigCtrlData->sigctrl->temp1 = childItem1->text(1).toUInt();
//    SigCtrlData->sigctrl->temp7 = childItem7->text(1).toUInt();
//    SigCtrlData->sigctrl->temp8 = childItem8->text(1).toUInt();
//    SigCtrlData->sigctrl->temp9 = childItem9->text(1).toUInt();
//    SigCtrlData->sigctrl->temp10 = childItem10->text(1).toUInt();
//    SigCtrlData->sigctrl->temp11 = childItem11->text(1).toUInt();
//    SigCtrlData->sigctrl->temp12 = childItem12->text(1).toUInt();
//    SigCtrlData->sigctrl->temp14 = childItem14->text(1).toUInt();
//    SigCtrlData->sigctrl->temp15 = childItem15->text(1).toUInt();
//    SigCtrlData->sigctrl->temp16 = childItem16->text(1).toUInt();
//    SigCtrlData->sigctrl->temp17 = childItem17->text(1).toUInt();
//    SigCtrlData->sigctrl->temp18 = childItem18->text(1).toUInt();
//    SigCtrlData->sigctrl->temp19 = childItem19->text(1).toUInt();
//    SigCtrlData->sigctrl->temp20 = childItem20->text(1).toUInt();
//    SigCtrlData->sigctrl->temp21 = childItem21->text(1).toUInt();
//    SigCtrlData->sigctrl->temp22 = childItem22->text(1).toUInt();
//    SigCtrlData->sigctrl->temp23 = childItem23->text(1).toUInt();
//    SigCtrlData->sigctrl->temp24 = childItem24->text(1).toUInt();
//    SigCtrlData->sigctrl->temp25 = childItem25->text(1).toUInt();
//    SigCtrlData->sigctrl->temp26 = childItem26->text(1).toUInt();
//    SigCtrlData->sigctrl->temp27 = childItem27->text(1).toUInt();
//    SigCtrlData->sigctrl->temp28 = childItem28->text(1).toUInt();
//    SigCtrlData->sigctrl->temp29 = childItem29->text(1).toUInt();
//    SigCtrlData->sigctrl->temp30 = childItem30->text(1).toUInt();
//    SigCtrlData->sigctrl->temp31 = childItem31->text(1).toUInt();
//    SigCtrlData->sigctrl->temp32 = childItem32->text(1).toUInt();
//    SigCtrlData->sigctrl->temp33 = childItem33->text(1).toUInt();
//    SigCtrlData->sigctrl->temp34 = childItem34->text(1).toUInt();

//    QString str35=childItem35->text(1);
//    bool ok;
//    int val=str35.toInt(&ok,16);
//    qDebug()<<"str35 begin:"<<str35<<"Val:"<<val;
//    SigCtrlData->sigctrl->temp35 =val;
//    SigCtrlData->sigctrl->temp36 = childItem36->text(1).toUInt();
//    SigCtrlData->sigctrl->temp37 = childItem37->text(1).toUInt();

//    SigCtrlData->sigctrl->temp43 = childItem43->text(1).toUInt();
//    SigCtrlData->sigctrl->temp44 = childItem44->text(1).toUInt();
//    SigCtrlData->sigctrl->temp45 = childItem45->text(1).toUInt();
//    SigCtrlData->sigctrl->temp46 = childItem46->text(1).toUInt();
//    SigCtrlData->sigctrl->temp47 = childItem47->text(1).toUInt();
//    SigCtrlData->sigctrl->temp48 = childItem48->text(1).toUInt();
//    SigCtrlData->sigctrl->temp49 = childItem49->text(1).toUInt();
//    SigCtrlData->sigctrl->temp50 = childItem50->text(1).toUInt();
//    SigCtrlData->sigctrl->temp51 = childItem51->text(1).toUInt();
//    SigCtrlData->sigctrl->temp52 = childItem52->text(1).toUInt();
//    SigCtrlData->sigctrl->temp53 = childItem53->text(1).toUInt();
//    SigCtrlData->sigctrl->temp54 = childItem54->text(1).toUInt();
//    SigCtrlData->sigctrl->temp55 = childItem55->text(1).toUInt();
//    SigCtrlData->sigctrl->temp56 = childItem56->text(1).toUInt();


//    PARAM.setFieldNumberSet(SigCtrlData->sigctrl->temp55);

//    SigCtrlData->sigctrl->tempRollerACount = childItem_rollerACount->text(1).toUInt();
//    SigCtrlData->sigctrl->tempRollerBCount = childItem_rollerBCount->text(1).toUInt();
//    SigCtrlData->sigctrl->tempRoller4ABCount = childItemAB4->text(1).toUInt();
//    SigCtrlData->sigctrl->tempRollerCofficient = chileItem_rollerCofficient->text(1).toDouble();
//    SigCtrlData->sigctrl->tempAutoPhoto = chileItem_photoMode->text(1).toUInt();
//    SigCtrlData->sigctrl->tempPhotoEndDelayLine = chileItem_photoEndDelayLine->text(1).toUInt();
//    QString strCo=chileItem_rollerCofficient->text(1);
//    PARAM.setEncodeRollerCofficient(strCo.toDouble());

//    SigCtrlData->SetData();
}

void LightControl::slot_saveButton_clicked()
{
//    SigCtrlData->sigctrl->temp0 = childItem0->text(1).toUInt();
//    SigCtrlData->sigctrl->temp1 = childItem1->text(1).toUInt();
//    SigCtrlData->sigctrl->temp2 = childItem2->text(1).toUInt();
//    SigCtrlData->sigctrl->temp3 = childItem3->text(1).toUInt();
//    SigCtrlData->sigctrl->temp4 = childItem4->text(1).toUInt();
//    SigCtrlData->sigctrl->temp5 = childItem5->text(1).toUInt();
//    SigCtrlData->sigctrl->temp6 = childItem6->text(1).toUInt();
//    SigCtrlData->sigctrl->temp7 = childItem7->text(1).toUInt();
//    SigCtrlData->sigctrl->temp8 = childItem8->text(1).toUInt();
//    SigCtrlData->sigctrl->temp9 = childItem9->text(1).toUInt();
//    SigCtrlData->sigctrl->temp10 = childItem10->text(1).toUInt();
//    SigCtrlData->sigctrl->temp11 = childItem11->text(1).toUInt();
//    SigCtrlData->sigctrl->temp12 = childItem12->text(1).toUInt();
//    SigCtrlData->sigctrl->temp13 = childItem13->text(1).toUInt();
//    SigCtrlData->sigctrl->temp14 = childItem14->text(1).toUInt();
//    SigCtrlData->sigctrl->temp15 = childItem15->text(1).toUInt();
//    SigCtrlData->sigctrl->temp16 = childItem16->text(1).toUInt();
//    SigCtrlData->sigctrl->temp17 = childItem17->text(1).toUInt();
//    SigCtrlData->sigctrl->temp18 = childItem18->text(1).toUInt();
//    SigCtrlData->sigctrl->temp19 = childItem19->text(1).toUInt();
//    SigCtrlData->sigctrl->temp20 = childItem20->text(1).toUInt();
//    SigCtrlData->sigctrl->temp21 = childItem21->text(1).toUInt();
//    SigCtrlData->sigctrl->temp22 = childItem22->text(1).toUInt();
//    SigCtrlData->sigctrl->temp23 = childItem23->text(1).toUInt();
//    SigCtrlData->sigctrl->temp24 = childItem24->text(1).toUInt();
//    SigCtrlData->sigctrl->temp25 = childItem25->text(1).toUInt();
//    SigCtrlData->sigctrl->temp26 = childItem26->text(1).toUInt();
//    SigCtrlData->sigctrl->temp27 = childItem27->text(1).toUInt();
//    SigCtrlData->sigctrl->temp28 = childItem28->text(1).toUInt();
//    SigCtrlData->sigctrl->temp29 = childItem29->text(1).toUInt();
//    SigCtrlData->sigctrl->temp30 = childItem30->text(1).toUInt();
//    SigCtrlData->sigctrl->temp31 = childItem31->text(1).toUInt();
//    SigCtrlData->sigctrl->temp32 = childItem32->text(1).toUInt();
//    SigCtrlData->sigctrl->temp33 = childItem33->text(1).toUInt();
//    SigCtrlData->sigctrl->temp34 = childItem34->text(1).toUInt();

//    QString str35=childItem35->text(1);
//    bool ok;
//    int val=str35.toInt(&ok,16);
//    qDebug()<<"str35 begin:"<<str35<<"Val:"<<val;
//    SigCtrlData->sigctrl->temp35 =val;
//    SigCtrlData->sigctrl->temp36 = childItem36->text(1).toUInt();
//    SigCtrlData->sigctrl->temp37 = childItem37->text(1).toUInt();

//    SigCtrlData->sigctrl->temp43 = childItem43->text(1).toUInt();
//    SigCtrlData->sigctrl->temp44 = childItem44->text(1).toUInt();
//    SigCtrlData->sigctrl->temp45 = childItem45->text(1).toUInt();
//    SigCtrlData->sigctrl->temp46 = childItem46->text(1).toUInt();
//    SigCtrlData->sigctrl->temp47 = childItem47->text(1).toUInt();
//    SigCtrlData->sigctrl->temp48 = childItem48->text(1).toUInt();
//    SigCtrlData->sigctrl->temp49 = childItem49->text(1).toUInt();
//    SigCtrlData->sigctrl->temp50 = childItem50->text(1).toUInt();
//    SigCtrlData->sigctrl->temp51 = childItem51->text(1).toUInt();
//    SigCtrlData->sigctrl->temp52 = childItem52->text(1).toUInt();
//    SigCtrlData->sigctrl->temp53 = childItem53->text(1).toUInt();
//    SigCtrlData->sigctrl->temp54 = childItem54->text(1).toUInt();
//    SigCtrlData->sigctrl->temp55 = childItem55->text(1).toUInt();
//    SigCtrlData->sigctrl->temp56 = childItem56->text(1).toUInt();

//    SigCtrlData->sigctrl->tempRollerACount = childItem_rollerACount->text(1).toUInt();
//    SigCtrlData->sigctrl->tempRollerBCount = childItem_rollerBCount->text(1).toUInt();
//    SigCtrlData->sigctrl->tempRoller4ABCount = childItemAB4->text(1).toUInt();
//    SigCtrlData->sigctrl->tempRollerCofficient = chileItem_rollerCofficient->text(1).toDouble();
//    SigCtrlData->sigctrl->tempAutoPhoto = chileItem_photoMode->text(1).toUInt();
//    SigCtrlData->sigctrl->tempPhotoEndDelayLine = chileItem_photoEndDelayLine->text(1).toUInt();
//    QString strCo=chileItem_rollerCofficient->text(1);
//    PARAM.setEncodeRollerCofficient(strCo.toDouble());

//    SigCtrlData->SaveData();
}

void LightControl::slotTrigger()
{
    //内部产生光电信号(写1再写0)
    unsigned int endInnerSignal = 0;
    unsigned int startInnerSignal = 1;
    m_pSig_comm.SetRegs(ADDR38, ADDR38, &startInnerSignal);
    m_pSig_comm.SetRegs(ADDR38, ADDR38, &endInnerSignal);
}

void LightControl::slot_updateCode()
{
//    childItem3->setText(1, QString::number(PARAM.getCodeCount()));
//    childItem4->setText(1, QString::number(PARAM.getCodeLineCount()));
//    childItem5->setText(1, QString::number(PARAM.getCode4Count()));
//    childItem6->setText(1, QString::number(PARAM.getCodePerCount()));
//    //计算Y长度
//    double radian = PARAM.getRollerAngle();
//    double cosValue = cos(radian);
//    PARAM.setEncodeRollerYLength(PARAM.getEncodeBRollerCount() * PARAM.getEncodeRollerCofficient() * cosValue);
//    childItem_rollerACount->setText(1,QString::number(PARAM.getEncodeARollerCount()));
//    childItem_rollerBCount->setText(1,QString::number(PARAM.getEncodeBRollerCount()));
//    childItemAB4->setText(1,QString::number(PARAM.getEncodeAB4()));
}

bool LightControl::InitLightControl()
{
    QString needLoadJsonFile = PARAM.GetParamterFromIniFile(SYSTEM_PATH,"recipe");//需要加载的工单名称recipe=8nm.json
    QDir dir(RECIPE_FULLPATH);
    QFileInfoList fileList = dir.entryInfoList(QStringList() << "*.json");
    if (fileList.size() == 0) { //没有找到任何json工单
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
        QString recipeFileName = current_date + QString(".json");
        QString newRecipe = LightControl::createNewRecipeFile(recipeFileName);  //产生初始化工单
        LightControl::readRecipeToTable(newRecipe.toStdString());
        ui->RecipeCB->addItem(newRecipe);
        ui->RecipeCB->setCurrentText(newRecipe);
        return true;
    } else {                    //找到了json工单
        ui->RecipeCB->clear();//清除工单里面所有items
        //遍历文件夹
        for(auto fileInfo:fileList) {
            ui->RecipeCB->addItem(fileInfo.fileName());
        }
        int ret = ui->RecipeCB->findText(needLoadJsonFile);
        if (ret == -1) {
            QString message = "Not find " + needLoadJsonFile + " in RecipeCB Items!";
            INFOMATION.criticalMessageBox(this,message);
            return false;
        } else {
            ui->RecipeCB->setCurrentText(needLoadJsonFile);
            LightControl::readRecipeToTable(needLoadJsonFile.toStdString());
            return true;
        }
    }
}

// 创建新的空白工单文件
QString LightControl::createNewRecipeFile(QString recipeFileName)
{
    //Json::Value root;
    Json::FastWriter writer;
    { //系统参数
        m_root["SystemParams"]["SystemName"] = "大拓智能视觉检测";
        m_root["SystemParams"]["CamareNumber"] = "4";
        m_root["SystemParams"]["Camare0Name"] = "DSXL810003076";
        m_root["SystemParams"]["Camare1Name"] = "DSXL810002378";
        m_root["SystemParams"]["Camare2Name"] = "DSXL810002135";
        m_root["SystemParams"]["Camare3Name"] = "DSXL810002382";
        m_root["SystemParams"]["ServerIP"] = "192.168.1.200";
        m_root["SystemParams"]["ServerPort"] = "7002";
    }
    { //自定义参数
       m_root["CustomParams"]["SaveOriginImage"] = "1";
       m_root["CustomParams"]["SaveEntireImage"] = "1";
       m_root["CustomParams"]["SaveFlawImage"] = "1";
       m_root["CustomParams"]["SaveCropImage"] = "1";
       m_root["CustomParams"]["XYLengthEnable"] = "1";
       m_root["CustomParams"]["FlawDefectEnable"] = "1";
    }
    { //缺陷检测
       m_root["DefectDetectionParams"]["Camera12PixelDeviation"] = "0";
       m_root["DefectDetectionParams"]["Camera23PixelDeviation"] = "0";
       m_root["DefectDetectionParams"]["Camera24PixelDeviation"] = "0";
       m_root["DefectDetectionParams"]["SilkToRollerDist"] = "0";
       m_root["DefectDetectionParams"]["ScratchAreaThreshold"] = "0";
       m_root["DefectDetectionParams"]["BubbleStoneAreaThreshold"] = "0";
       m_root["DefectDetectionParams"]["DirtyAreaThreshold"] = "0";
    }
    { //尺寸测量
       m_root["DimensionalMeasurementParams"]["YAccuracyB"] = "0";
       m_root["DimensionalMeasurementParams"]["YAccuracyK"] = "0";
       m_root["DimensionalMeasurementParams"]["Width"] = "0";
       m_root["DimensionalMeasurementParams"]["WidthDeviation"] = "0";
       m_root["DimensionalMeasurementParams"]["Digonal1"] = "0";
       m_root["DimensionalMeasurementParams"]["Digonal1Deviation"] = "0";
       m_root["DimensionalMeasurementParams"]["Diagonal2"] = "0";
       m_root["DimensionalMeasurementParams"]["Digonal2Deviation"] = "0";
       m_root["DimensionalMeasurementParams"]["Camera1Pixel0Accuracy"] = "0";
       m_root["DimensionalMeasurementParams"]["Camera1PixelKValue"] = "0";
       m_root["DimensionalMeasurementParams"]["Camera21AccuracyRatio"] = "0";
       m_root["DimensionalMeasurementParams"]["Camera2PixelKValue"] = "0";
       m_root["DimensionalMeasurementParams"]["Length"] = "0";
       m_root["DimensionalMeasurementParams"]["LengthDeviation"] = "0";
    }
    {//相机参数
        m_root["CamareParams"]["Camera0Frame"] = "0";
        m_root["CamareParams"]["Camera0PhotoRow"] = "0";
        m_root["CamareParams"]["Camera0ExposureTime"] = "0";
        m_root["CamareParams"]["Camera0Gain"] = "0";
        m_root["CamareParams"]["Camera1Frame"] = "0";
        m_root["CamareParams"]["Camera1PhotoRow"] = "0";
        m_root["CamareParams"]["Camera1ExposureTime"] = "0";
        m_root["CamareParams"]["Camera1Gain"] = "0";
        m_root["CamareParams"]["Camera2Frame"] = "0";
        m_root["CamareParams"]["Camera2PhotoRow"] = "0";
        m_root["CamareParams"]["Camera2ExposureTime"] = "0";
        m_root["CamareParams"]["Camera2Gain"] = "0";
        m_root["CamareParams"]["Camera3Frame"] = "0";
        m_root["CamareParams"]["Camera3PhotoRow"] = "0";
        m_root["CamareParams"]["Camera3ExposureTime"] = "0";
        m_root["CamareParams"]["Camera3Gain"] = "0";
    }
    {//编码器参数
        m_root["EncoderParams"]["EncodeUnitToDist"] = "0";
        m_root["EncoderParams"]["EncodePulseFilterUs"] = "0";
        m_root["EncoderParams"]["EncodeCountEndFlag"] = "0";
        m_root["EncoderParams"]["EncodeCount"] = "0";
        m_root["EncoderParams"]["EncodeTriggerRowCount"] = "0";
        m_root["EncoderParams"]["Encode4FrequencyMultiplierCount"] = "0";
        m_root["EncoderParams"]["EncodeUnitTimePulseCount"] = "0";
        m_root["EncoderParams"]["EncodeCountTimeHalfSecond"] = "0";
        m_root["EncoderParams"]["EncodeChannel"] = "0";
        m_root["EncoderParams"]["EncodeRevolution"] = "0";
        m_root["EncoderParams"]["RollerPerimeterUm"] = "0";
        m_root["EncoderParams"]["ExpectSinglePixelAccuracy"] = "0";
        m_root["EncoderParams"]["RollerMaxSpeedToRowCount"] = "0";
        m_root["EncoderParams"]["EveryRowToEncodeCount"] = "0";
        m_root["EncoderParams"]["EncodePressureWheelCountA"] = "0";
        m_root["EncoderParams"]["EncodePressureWheelCountB"] = "0";
        m_root["EncoderParams"]["PressureWheel4FrequencyMutliper"] = "0";
        m_root["EncoderParams"]["PressureEncodecoefficient"] = "0";
    }
    {//控制器参数
        m_root["ControllerParams"]["PixelAccuracyUm"] = "0";
        m_root["ControllerParams"]["PhotoelectricSignalPulseFilter"] = "0";
        m_root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"] = "0";
        m_root["ControllerParams"]["PhotoelectricToCamareDist"] = "0";
        m_root["ControllerParams"]["CamareFrameTrigerDelayRowCount"] = "0";
        m_root["ControllerParams"]["FrameSignalContinueTime"] = "0";
        m_root["ControllerParams"]["ModuleEnableSignal"] = "0";
        m_root["ControllerParams"]["CamarePhotoRowCount"] = "0";
        m_root["ControllerParams"]["InnerRowFrequency"] = "0";
        m_root["ControllerParams"]["PhotoMode"] = "0";
        m_root["ControllerParams"]["PhotoEndDelayRowCount"] = "0";
    }
    {//光源控制器参数
        m_root["LighterParams"]["LightField1DelayTime"] = "0";
        m_root["LighterParams"]["LightField1GlowTime"] = "0";
        m_root["LighterParams"]["LightField2DelayTime"] = "0";
        m_root["LighterParams"]["LightField2GlowTime"] = "0";
        m_root["LighterParams"]["LightField3DelayTime"] = "0";
        m_root["LighterParams"]["LightField3GlowTime"] = "0";
        m_root["LighterParams"]["LightField4DelayTime"] = "0";
        m_root["LighterParams"]["LightField4GlowTime"] = "0";
        m_root["LighterParams"]["SelectedLightFieldNumber"] = "3";
        m_root["LighterParams"]["HorizontalDarkfieldSelectRegister"] = "0";
        m_root["LighterParams"]["CamareAndLightFieldControl"] = "0";
        m_root["LighterParams"]["SignalSwitch"] = "0";
        m_root["LighterParams"]["RowSignalSelected"] = "0";
    }
    std::string json_content = writer.write(m_root);
    std::ofstream ofs;
    ofs.open(recipeFileName.toStdString().data());
    if (ofs.is_open()) {
        ofs<<json_content;
        ofs.close();
    }
    return recipeFileName;
}

// 读取json工单到表单中
void LightControl::readRecipeToTable(std::string filePath)
{
    //获取json数据，初始化界面参数
    std::ifstream ifs;
    ifs.open(filePath); // Windows自己注意路径吧
    if (!ifs.is_open()) {
        QString message = "Open file ["+QString(filePath.data()) +"] is failer!";
        INFOMATION.criticalMessageBox(this,message);
        return;
    }

    Json::Reader reader;
    //Json::Value root;
    // 解析到root，root将包含Json里所有子元素
    if (!reader.parse(ifs, m_root, false)) {
        INFOMATION.criticalMessageBox(this,"Parse json file is error!");
        ifs.close();
        return;
    }

    {//系统参数
       QString systemName = m_root["SystemParams"]["SystemName"].asCString();
       ui->SystemNameLE->setText(systemName);
       QString camareNumber = m_root["SystemParams"]["CamareNumber"].asCString();
       ui->CameraNumLE->setText(camareNumber);
       QString camare0Name = m_root["SystemParams"]["Camare0Name"].asCString();
       ui->Camera0NameLE->setText(camare0Name);
       QString camare1Name = m_root["SystemParams"]["Camare1Name"].asCString();
       ui->Camera1NameLE->setText(camare1Name);
       QString camare2Name = m_root["SystemParams"]["Camare2Name"].asCString();
       ui->Camera2NameLE->setText(camare2Name);
       QString camare3Name = m_root["SystemParams"]["Camare3Name"].asCString();
       ui->Camera3NameLE->setText(camare3Name);
       QString serverIP = m_root["SystemParams"]["ServerIP"].asCString();
       ui->ServerIPLE->setText(serverIP);
       QString serverPort = m_root["SystemParams"]["ServerPort"].asCString();
       ui->PortLE->setText(serverPort);
    }
    {//自定义参数
        QString saveOriginImage = m_root["CustomParams"]["SaveOriginImage"].asCString();
        ui->SaveOriginImageCB->setCurrentIndex(saveOriginImage.toInt());
        QString saveEntireImage = m_root["CustomParams"]["SaveEntireImage"].asCString();
        ui->SaveEntireImageCB->setCurrentIndex(saveEntireImage.toInt());
        QString saveFlawImage = m_root["CustomParams"]["SaveFlawImage"].asCString();
        ui->SaveFlawImageCB->setCurrentIndex(saveFlawImage.toInt());
        QString saveCropImage = m_root["CustomParams"]["SaveCropImage"].asCString();
        ui->SaveCropImageCB->setCurrentIndex(saveCropImage.toInt());
        QString XYLengthEnable = m_root["CustomParams"]["XYLengthEnable"].asCString();
        ui->XYLengthEnableCB->setCurrentIndex(XYLengthEnable.toInt());
        QString flawDefectEnable = m_root["CustomParams"]["FlawDefectEnable"].asCString();
        ui->FlawDefectEnableCB->setCurrentIndex(flawDefectEnable.toInt());
    }
    {//缺陷检测
        QString camera12PixelDeviation = m_root["DefectDetectionParams"]["Camera12PixelDeviation"].asCString();
        ui->Camera12PixelDeviationLE->setText(camera12PixelDeviation);
        QString camera23PixelDeviation = m_root["DefectDetectionParams"]["Camera23PixelDeviation"].asCString();
        ui->Camera23PixelDeviationLE->setText(camera23PixelDeviation);
        QString camera24PixelDeviation = m_root["DefectDetectionParams"]["Camera24PixelDeviation"].asCString();
        ui->Camera24PixelDeviationLE->setText(camera24PixelDeviation);
        QString silkToRollerDist = m_root["DefectDetectionParams"]["SilkToRollerDist"].asCString();
        ui->SilkToRollerDistLE->setText(silkToRollerDist);
        QString scratchAreaThreshold = m_root["DefectDetectionParams"]["ScratchAreaThreshold"].asCString();
        ui->ScratchAreaThresholdLE->setText(scratchAreaThreshold);
        QString bubbleStoneAreaThreshold = m_root["DefectDetectionParams"]["BubbleStoneAreaThreshold"].asCString();
        ui->BubbleStoneAreaThresholdLE->setText(bubbleStoneAreaThreshold);
        QString dirtyAreaThreshold = m_root["DefectDetectionParams"]["DirtyAreaThreshold"].asCString();
        ui->DirtyAreaThresholdLE->setText(dirtyAreaThreshold);
    }
    {//尺寸测量
        QString YAccuracyB = m_root["DimensionalMeasurementParams"]["YAccuracyB"].asCString();
        ui->YAccuracyBLE->setText(YAccuracyB);
        QString YAccuracyK = m_root["DimensionalMeasurementParams"]["YAccuracyK"].asCString();
        ui->YAccuracyKLE->setText(YAccuracyK);
        QString width = m_root["DimensionalMeasurementParams"]["Width"].asCString();
        ui->WidthLE->setText(width);
        QString widthDeviation = m_root["DimensionalMeasurementParams"]["WidthDeviation"].asCString();
        ui->WidthDeviationLE->setText(widthDeviation);
        QString digonal1 = m_root["DimensionalMeasurementParams"]["Digonal1"].asCString();
        ui->Digonal1LE->setText(digonal1);
        QString digonal1Deviation = m_root["DimensionalMeasurementParams"]["Digonal1Deviation"].asCString();
        ui->Digonal1DeviationLE->setText(digonal1Deviation);
        QString diagonal2 = m_root["DimensionalMeasurementParams"]["Diagonal2"].asCString();
        ui->Digonal2LE->setText(diagonal2);
        QString digonal2Deviation = m_root["DimensionalMeasurementParams"]["Digonal2Deviation"].asCString();
        ui->Digonal2DeviationLE->setText(digonal2Deviation);
        QString camera1Pixel0Accuracy = m_root["DimensionalMeasurementParams"]["Camera1Pixel0Accuracy"].asCString();
        ui->Camera1Pixel0AccuracyLE->setText(camera1Pixel0Accuracy);
        QString camera1PixelKValue = m_root["DimensionalMeasurementParams"]["Camera1PixelKValue"].asCString();
        ui->Camera1PixelKValueLE->setText(camera1PixelKValue);
        QString camera21AccuracyRatio = m_root["DimensionalMeasurementParams"]["Camera21AccuracyRatio"].asCString();
        ui->Camera21AccuracyRatioLE->setText(camera21AccuracyRatio);
        QString camera2PixelKValue = m_root["DimensionalMeasurementParams"]["Camera2PixelKValue"].asCString();
        ui->Camera2PixelKValueLE->setText(camera2PixelKValue);
        QString length = m_root["DimensionalMeasurementParams"]["Length"].asCString();
        ui->LengthLE->setText(length);
        QString lengthDeviation = m_root["DimensionalMeasurementParams"]["LengthDeviation"].asCString();
        ui->LengthDeviationLE->setText(lengthDeviation);
    }
    {//相机参数
        QString camera0Frame = m_root["CamareParams"]["Camera0Frame"].asCString();
        ui->Camera0FrameLE->setText(camera0Frame);
        QString camera0PhotoRow = m_root["CamareParams"]["Camera0PhotoRow"].asCString();
        ui->Camera0PhotoRowLE->setText(camera0PhotoRow);
        QString camera0ExposureTime = m_root["CamareParams"]["Camera0ExposureTime"].asCString();
        ui->Camera0ExposureTimeLE->setText(camera0ExposureTime);
        QString camera0Gain = m_root["CamareParams"]["Camera0Gain"].asCString();
        ui->Camera0GainLE->setText(camera0Gain);
        QString camera1Frame = m_root["CamareParams"]["Camera1Frame"].asCString();
        ui->Camera1FrameLE->setText(camera1Frame);
        QString camera1PhotoRow = m_root["CamareParams"]["Camera1PhotoRow"].asCString();
        ui->Camera1PhotoRowLE->setText(camera1PhotoRow);
        QString camera1ExposureTime = m_root["CamareParams"]["Camera1ExposureTime"].asCString();
        ui->Camera1ExposureTimeLE->setText(camera1ExposureTime);
        QString camera1Gain = m_root["CamareParams"]["Camera1Gain"].asCString();
        ui->Camera1GainLE->setText(camera1Gain);
        QString camera2Frame = m_root["CamareParams"]["Camera2Frame"].asCString();
        ui->Camera2FrameLE->setText(camera2Frame);
        QString camera2PhotoRow = m_root["CamareParams"]["Camera2PhotoRow"].asCString();
        ui->Camera2PhotoRowLE->setText(camera2PhotoRow);
        QString camera2ExposureTime = m_root["CamareParams"]["Camera2ExposureTime"].asCString();
        ui->Camera2ExposureTimeLE->setText(camera2ExposureTime);
        QString camera2Gain = m_root["CamareParams"]["Camera2Gain"].asCString();
        ui->Camera2GainLE->setText(camera2Gain);
        QString camera3Frame = m_root["CamareParams"]["Camera3Frame"].asCString();
        ui->Camera3FrameLE->setText(camera3Frame);
        QString camera3PhotoRow = m_root["CamareParams"]["Camera3PhotoRow"].asCString();
        ui->Camera3PhotoRowLE->setText(camera3PhotoRow);
        QString camera3ExposureTime = m_root["CamareParams"]["Camera3ExposureTime"].asCString();
        ui->Camera3ExposureTimeLE->setText(camera3ExposureTime);
        QString camera3Gain = m_root["CamareParams"]["Camera3Gain"].asCString();
        ui->Camera3GainLE->setText(camera3Gain);
    }
    {//编码器参数
        QString encodeUnitToDist = m_root["EncoderParams"]["EncodeUnitToDist"].asCString();
        ui->EncodeUnitToDistLE->setText(encodeUnitToDist);
        QString encodePulseFilterUs = m_root["EncoderParams"]["EncodePulseFilterUs"].asCString();
        ui->EncodePulseFilterUsLE->setText(encodePulseFilterUs);
        QString encodeCountEndFlag = m_root["EncoderParams"]["EncodeCountEndFlag"].asCString();
        ui->EncodeCountEndFlagLE->setText(encodeCountEndFlag);
        QString encodeCount = m_root["EncoderParams"]["EncodeCount"].asCString();
        ui->EncodeCountLE->setText(encodeCount);
        QString encodeTriggerRowCount = m_root["EncoderParams"]["EncodeTriggerRowCount"].asCString();
        ui->EncodeTriggerRowCountLE->setText(encodeTriggerRowCount);
        QString encode4FrequencyMultiplierCount = m_root["EncoderParams"]["Encode4FrequencyMultiplierCount"].asCString();
        ui->Encode4FrequencyMultiplierCountLE->setText(encode4FrequencyMultiplierCount);
        QString encodeUnitTimePulseCount = m_root["EncoderParams"]["EncodeUnitTimePulseCount"].asCString();
        ui->EncodeUnitTimePulseCountLE->setText(encodeUnitTimePulseCount);
        QString encodeCountTimeHalfSecond = m_root["EncoderParams"]["EncodeCountTimeHalfSecond"].asCString();
        ui->EncodeCountTimeHalfSecondLE->setText(encodeCountTimeHalfSecond);
        QString encodeChannel = m_root["EncoderParams"]["EncodeChannel"].asCString();
        ui->EncodeChannelLE->setText(encodeChannel);
        QString encodeRevolution = m_root["EncoderParams"]["EncodeRevolution"].asCString();
        ui->EncodeRevolutionLE->setText(encodeRevolution);
        QString rollerPerimeterUm = m_root["EncoderParams"]["RollerPerimeterUm"].asCString();
        ui->RollerPerimeterUmLE->setText(rollerPerimeterUm);
        QString expectSinglePixelAccuracy = m_root["EncoderParams"]["ExpectSinglePixelAccuracy"].asCString();
        ui->ExpectSinglePixelAccuracyLE->setText(expectSinglePixelAccuracy);
        QString rollerMaxSpeedToRowCount = m_root["EncoderParams"]["RollerMaxSpeedToRowCount"].asCString();
        ui->RollerMaxSpeedToRowCountLE->setText(rollerMaxSpeedToRowCount);
        QString everyRowToEncodeCount = m_root["EncoderParams"]["EveryRowToEncodeCount"].asCString();
        ui->EveryRowToEncodeCountLE->setText(everyRowToEncodeCount);
        QString encodePressureWheelCountA = m_root["EncoderParams"]["EncodePressureWheelCountA"].asCString();
        ui->EncodePressureWheelCountALE->setText(encodePressureWheelCountA);
        QString encodePressureWheelCountB = m_root["EncoderParams"]["EncodePressureWheelCountB"].asCString();
        ui->EncodePressureWheelCountBLE->setText(encodePressureWheelCountB);
        QString pressureWheel4FrequencyMutliper = m_root["EncoderParams"]["PressureWheel4FrequencyMutliper"].asCString();
        ui->PressureWheel4FrequencyMutliperLE->setText(pressureWheel4FrequencyMutliper);
        QString pressureEncodecoefficient = m_root["EncoderParams"]["PressureEncodecoefficient"].asCString();
        ui->PressureEncodecoefficientLE->setText(pressureEncodecoefficient);
    }
    {//控制器参数
        QString pixelAccuracyUm = m_root["ControllerParams"]["PixelAccuracyUm"].asCString();
        ui->PixelAccuracyUmLE->setText(pixelAccuracyUm);
        QString photoelectricSignalPulseFilter = m_root["ControllerParams"]["PhotoelectricSignalPulseFilter"].asCString();
        ui->PhotoelectricSignalPulseFilterLE->setText(photoelectricSignalPulseFilter);
        QString camareTrigerPulseContinueTime10ns = m_root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"].asCString();
        ui->CamareTrigerPulseContinueTime10nsLE->setText(camareTrigerPulseContinueTime10ns);
        QString photoelectricToCamareDist = m_root["ControllerParams"]["PhotoelectricToCamareDist"].asCString();
        ui->PhotoelectricToCamareDistLE->setText(photoelectricToCamareDist);
        QString camareFrameTrigerDelayRowCount = m_root["ControllerParams"]["CamareFrameTrigerDelayRowCount"].asCString();
        ui->CamareFrameTrigerDelayRowCountLE->setText(camareFrameTrigerDelayRowCount);
        QString frameSignalContinueTime = m_root["ControllerParams"]["FrameSignalContinueTime"].asCString();
        ui->FrameSignalContinueTimeLE->setText(frameSignalContinueTime);
        QString moduleEnableSignal = m_root["ControllerParams"]["ModuleEnableSignal"].asCString();
        ui->ModuleEnableSignalLE->setText(moduleEnableSignal);
        QString camarePhotoRowCount = m_root["ControllerParams"]["CamarePhotoRowCount"].asCString();
        ui->CamarePhotoRowCountLE->setText(camarePhotoRowCount);
        QString innerRowFrequency = m_root["ControllerParams"]["InnerRowFrequency"].asCString();
        ui->InnerRowFrequencyLE->setText(innerRowFrequency);
        QString photoMode = m_root["ControllerParams"]["PhotoMode"].asCString();
        ui->PhotoModeLE->setText(photoMode);
        QString photoEndDelayRowCount = m_root["ControllerParams"]["PhotoEndDelayRowCount"].asCString();
        ui->PhotoEndDelayRowCountLE->setText(photoEndDelayRowCount);
    }
    {//光源控制器参数
        QString lightField1DelayTime = m_root["LighterParams"]["LightField1DelayTime"].asCString();
        ui->LightField1DelayTimeLE->setText(lightField1DelayTime);
        QString lightField1GlowTime = m_root["LighterParams"]["LightField1GlowTime"].asCString();
        ui->LightField1GlowTimeLE->setText(lightField1GlowTime);
        QString lightField2DelayTime = m_root["LighterParams"]["LightField2DelayTime"].asCString();
        ui->LightField2DelayTimeLE->setText(lightField2DelayTime);
        QString lightField2GlowTime = m_root["LighterParams"]["LightField2GlowTime"].asCString();
        ui->LightField2GlowTimeLE->setText(lightField2GlowTime);
        QString lightField3DelayTime = m_root["LighterParams"]["LightField3DelayTime"].asCString();
        ui->LightField3DelayTimeLE->setText(lightField3DelayTime);
        QString lightField3GlowTime = m_root["LighterParams"]["LightField3GlowTime"].asCString();
        ui->LightField3GlowTimeLE->setText(lightField3GlowTime);
        QString lightField4DelayTime = m_root["LighterParams"]["LightField4DelayTime"].asCString();
        ui->LightField4DelayTimeLE->setText(lightField4DelayTime);
        QString lightField4GlowTime = m_root["LighterParams"]["LightField4GlowTime"].asCString();
        ui->LightField4GlowTimeLE->setText(lightField4GlowTime);
        QString selectedLightFieldNumber = m_root["LighterParams"]["SelectedLightFieldNumber"].asCString();
        ui->SelectedLightFieldNumberLE->setText(selectedLightFieldNumber);
        QString horizontalDarkfieldSelectRegister = m_root["LighterParams"]["HorizontalDarkfieldSelectRegister"].asCString();
        ui->HorizontalDarkfieldSelectRegisterLE->setText(horizontalDarkfieldSelectRegister);
        QString camareAndLightFieldControl = m_root["LighterParams"]["CamareAndLightFieldControl"].asCString();
        ui->CamareAndLightFieldControlCB->setCurrentIndex(camareAndLightFieldControl.toInt());
        QString signalSwitch = m_root["LighterParams"]["SignalSwitch"].asCString();
        ui->SignalSwitchLE->setText(signalSwitch);
        QString rowSignalSelected = m_root["LighterParams"]["RowSignalSelected"].asCString();
        ui->RowSignalSelectedLE->setText(rowSignalSelected);
    }
    ifs.close();
}

void LightControl::initConnect()
{
    // 工单
    connect(ui->RecipeCB,SIGNAL(currentIndexChanged(int index)), this,SLOT(void slotUpdateRecipe(int index)));
    // 全局设置
    connect(ui->AllSet,SIGNAL(clicked()),this,SLOT(slotAllSet()));
    connect(ui->AllSave,SIGNAL(clicked()),this,SLOT(slotAllSave()));
    connect(ui->CreateRecipe, SIGNAL(clicked()),this,SLOT(slotCreateRecipe()));
    connect(ui->CopyRecipe,SIGNAL(clicked()), this, SLOT(slotCopyRecipe()));
    connect(ui->Trigger,SIGNAL(clicked()), this, SLOT(slotTrigger()));
    // 系统参数界面设置
    connect(ui->SystemNameSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTSystemName()));
    connect(ui->CameraNumSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTCameraNum()));
    connect(ui->Camera0NameSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTCamera0Name()));
    connect(ui->Camera1NameSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTCamera1Name()));
    connect(ui->Camera2NameSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTCamera2Name()));
    connect(ui->Camera3NameSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTCamera3Name()));
    connect(ui->ServerIPSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTServerIP()));
    connect(ui->PortSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTPort()));
    // 系统参数界面保存
    connect(ui->SystemNameSaveBT,SIGNAL(clicked()), this, SLOT(slotSaveBTSystemName()));
    connect(ui->CameraNumSaveBT,SIGNAL(clicked()), this, SLOT(slotSaveBTCameraNum()));
    connect(ui->Camera0NameSaveBT, SIGNAL(clicked()), this, SLOT(slotSaveBTCamera0Name()));
    connect(ui->Camera1NameSaveBT, SIGNAL(clicked()), this, SLOT(slotSaveBTCamera1Name()));
    connect(ui->Camera2NameSaveBT, SIGNAL(clicked()), this, SLOT(slotSaveBTCamera2Name()));
    connect(ui->Camera3NameSaveBT, SIGNAL(clicked()), this, SLOT(slotSaveBTCamera3Name()));
    connect(ui->ServerIPSaveBT,SIGNAL(clicked()), this, SLOT(slotSaveBTServerIP()));
    connect(ui->PortSaveBT,SIGNAL(clicked()), this, SLOT(slotSaveBTPort()));
    //自定义参数
    connect(ui->SaveOriginImageSetBT,SIGNAL(clicked()), this, SLOT(slotSetBTSaveOriginImage()));

}

void LightControl::slotUpdateRecipe(int index)
{
    if (index < ui->RecipeCB->count()) {
        QString fileName = ui->RecipeCB->itemText(index);
        LightControl::readRecipeToTable(fileName.toStdString());
    } else {
        INFOMATION.criticalMessageBox(this, "Update Recipe index is error !!!");
    }
}

void LightControl::slotAllSet()
{
    m_pSig_comm.SetRegs(ADDR0, ADDR0, &sigctrl->temp0);
    m_pSig_comm.SetRegs(ADDR1, ADDR1, &sigctrl->temp1);
    m_pSig_comm.SetRegs(ADDR7, ADDR7, &sigctrl->temp7);
    m_pSig_comm.SetRegs(ADDR8, ADDR8, &sigctrl->temp8);
    m_pSig_comm.SetRegs(ADDR9, ADDR9, &sigctrl->temp9);
    m_pSig_comm.SetRegs(ADDR10, ADDR10, &sigctrl->temp10);
    m_pSig_comm.SetRegs(ADDR11, ADDR11, &sigctrl->temp11);
    m_pSig_comm.SetRegs(ADDR12, ADDR12, &sigctrl->temp12);
    m_pSig_comm.SetRegs(ADDR14, ADDR14, &sigctrl->temp14);
    m_pSig_comm.SetRegs(ADDR15, ADDR15, &sigctrl->temp15);
    m_pSig_comm.SetRegs(ADDR16, ADDR16, &sigctrl->temp16);
    m_pSig_comm.SetRegs(ADDR17, ADDR17, &sigctrl->temp17);
    m_pSig_comm.SetRegs(ADDR18, ADDR18, &sigctrl->temp18);
    m_pSig_comm.SetRegs(ADDR19, ADDR19, &sigctrl->temp19);
    m_pSig_comm.SetRegs(ADDR20, ADDR20, &sigctrl->temp20);
    m_pSig_comm.SetRegs(ADDR21, ADDR21, &sigctrl->temp21);
    m_pSig_comm.SetRegs(ADDR22, ADDR22, &sigctrl->temp22);
    m_pSig_comm.SetRegs(ADDR23, ADDR23, &sigctrl->temp23);
    m_pSig_comm.SetRegs(ADDR24, ADDR24, &sigctrl->temp24);
    m_pSig_comm.SetRegs(ADDR25, ADDR25, &sigctrl->temp25);
    m_pSig_comm.SetRegs(ADDR26, ADDR26, &sigctrl->temp26);
    m_pSig_comm.SetRegs(ADDR27, ADDR27, &sigctrl->temp27);
    m_pSig_comm.SetRegs(ADDR28, ADDR28, &sigctrl->temp28);
    m_pSig_comm.SetRegs(ADDR29, ADDR29, &sigctrl->temp29);
    m_pSig_comm.SetRegs(ADDR30, ADDR30, &sigctrl->temp30);
    m_pSig_comm.SetRegs(ADDR31, ADDR31, &sigctrl->temp31);
    m_pSig_comm.SetRegs(ADDR32, ADDR32, &sigctrl->temp32);
    m_pSig_comm.SetRegs(ADDR33, ADDR33, &sigctrl->temp33);
    m_pSig_comm.SetRegs(ADDR34, ADDR34, &sigctrl->temp34);
    m_pSig_comm.SetRegs(ADDR35, ADDR35, &sigctrl->temp35);
    m_pSig_comm.SetRegs(ADDR36, ADDR36, &sigctrl->temp36);
    m_pSig_comm.SetRegs(ADDR37, ADDR37, &sigctrl->temp37);
    m_pSig_comm.SetRegs(ADDR43, ADDR43, &sigctrl->temp43);
    m_pSig_comm.SetRegs(ADDR44, ADDR44, &sigctrl->temp44);
    m_pSig_comm.SetRegs(ADDR45, ADDR45, &sigctrl->temp45);
    m_pSig_comm.SetRegs(ADDR46, ADDR46, &sigctrl->temp46);
    m_pSig_comm.SetRegs(ADDR47, ADDR47, &sigctrl->temp47);
    m_pSig_comm.SetRegs(ADDR48, ADDR48, &sigctrl->temp48);
    m_pSig_comm.SetRegs(ADDR49, ADDR49, &sigctrl->temp49);
    m_pSig_comm.SetRegs(ADDR50, ADDR50, &sigctrl->temp50);
    m_pSig_comm.SetRegs(ADDR51, ADDR51, &sigctrl->temp51);
    m_pSig_comm.SetRegs(ADDR52, ADDR52, &sigctrl->temp52);
    m_pSig_comm.SetRegs(ADDR53, ADDR53, &sigctrl->temp53);
    m_pSig_comm.SetRegs(ADDR54, ADDR54, &sigctrl->temp54);
    m_pSig_comm.SetRegs(ADDR55, ADDR55, &sigctrl->temp55);
    m_pSig_comm.SetRegs(ADDR56, ADDR56, &sigctrl->temp56);
    m_pSig_comm.SetRegs(ADDR59, ADDR59, &sigctrl->tempAutoPhoto);
    int ret = m_pSig_comm.SetRegs(ADDR60, ADDR60, &sigctrl->tempPhotoEndDelayLine);
    qDebug()<<ret;
}

void LightControl::slotAllSave()
{
    QString filename = ui->RecipeCB->currentText();
    LightControl::writeTableToRecipe(filename);
}

// 写入当前表单数据到工单文件中
void LightControl::writeTableToRecipe(QString filename)
{
    //Json::Value root;
    Json::FastWriter writer;
    { //系统参数
        m_root["SystemParams"]["SystemName"] = ui->SystemNameLE->text().toStdString().data();
        m_root["SystemParams"]["CamareNumber"] = ui->CameraNumLE->text().toStdString().data();
        m_root["SystemParams"]["Camare0Name"] = ui->Camera0NameLE->text().toStdString().data();
        m_root["SystemParams"]["Camare1Name"] = ui->Camera1NameLE->text().toStdString().data();
        m_root["SystemParams"]["Camare2Name"] = ui->Camera2NameLE->text().toStdString().data();
        m_root["SystemParams"]["Camare3Name"] = ui->Camera3NameLE->text().toStdString().data();
        m_root["SystemParams"]["ServerIP"] = ui->ServerIPLE->text().toStdString().data();
        m_root["SystemParams"]["ServerPort"] = ui->PortLE->text().toStdString().data();
    }
    { //自定义参数
       m_root["CustomParams"]["SaveOriginImage"] = QString::number(ui->SaveOriginImageCB->currentIndex()).toStdString().data();
       m_root["CustomParams"]["SaveEntireImage"] = QString::number(ui->SaveEntireImageCB->currentIndex()).toStdString().data();
       m_root["CustomParams"]["SaveFlawImage"] = QString::number(ui->SaveFlawImageCB->currentIndex()).toStdString().data();
       m_root["CustomParams"]["SaveCropImage"] = QString::number(ui->SaveCropImageCB->currentIndex()).toStdString().data();
       m_root["CustomParams"]["XYLengthEnable"] = QString::number(ui->XYLengthEnableCB->currentIndex()).toStdString().data();
       m_root["CustomParams"]["FlawDefectEnable"] = QString::number(ui->FlawDefectEnableCB->currentIndex()).toStdString().data();
    }
    { //缺陷检测
       m_root["DefectDetectionParams"]["Camera12PixelDeviation"] = ui->Camera12PixelDeviationLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["Camera23PixelDeviation"] = ui->Camera23PixelDeviationLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["Camera24PixelDeviation"] = ui->Camera24PixelDeviationLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["SilkToRollerDist"] = ui->SilkToRollerDistLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["ScratchAreaThreshold"] = ui->ScratchAreaThresholdLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["BubbleStoneAreaThreshold"] = ui->BubbleStoneAreaThresholdLE->text().toStdString().data();
       m_root["DefectDetectionParams"]["DirtyAreaThreshold"] = ui->DirtyAreaThresholdLE->text().toStdString().data();
    }
    { //尺寸测量
       m_root["DimensionalMeasurementParams"]["YAccuracyB"] = ui->YAccuracyBLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["YAccuracyK"] = ui->YAccuracyKLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Width"] = ui->WidthLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["WidthDeviation"] = ui->WidthDeviationLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Digonal1"] = ui->Digonal1LE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Digonal1Deviation"] = ui->Digonal1DeviationLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Diagonal2"] = ui->Digonal2LE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Digonal2Deviation"] = ui->Digonal2DeviationLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Camera1Pixel0Accuracy"] = ui->Camera1Pixel0AccuracyLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Camera1PixelKValue"] = ui->Camera1PixelKValueLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Camera21AccuracyRatio"] = ui->Camera21AccuracyRatioLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Camera2PixelKValue"] = ui->Camera2PixelKValueLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["Length"] = ui->LengthLE->text().toStdString().data();
       m_root["DimensionalMeasurementParams"]["LengthDeviation"] = ui->LengthDeviationLE->text().toStdString().data();
    }
    {//相机参数
        m_root["CamareParams"]["Camera0Frame"] = ui->Camera0FrameLE->text().toStdString().data();
        m_root["CamareParams"]["Camera0PhotoRow"] = ui->Camera0PhotoRowLE->text().toStdString().data();
        m_root["CamareParams"]["Camera0ExposureTime"] = ui->Camera0ExposureTimeLE->text().toStdString().data();
        m_root["CamareParams"]["Camera0Gain"] = ui->Camera0GainLE->text().toStdString().data();
        m_root["CamareParams"]["Camera1Frame"] = ui->Camera1FrameLE->text().toStdString().data();
        m_root["CamareParams"]["Camera1PhotoRow"] = ui->Camera1PhotoRowLE->text().toStdString().data();
        m_root["CamareParams"]["Camera1ExposureTime"] = ui->Camera1ExposureTimeLE->text().toStdString().data();
        m_root["CamareParams"]["Camera1Gain"] = ui->Camera1GainLE->text().toStdString().data();
        m_root["CamareParams"]["Camera2Frame"] = ui->Camera2FrameLE->text().toStdString().data();
        m_root["CamareParams"]["Camera2PhotoRow"] = ui->Camera2PhotoRowLE->text().toStdString().data();
        m_root["CamareParams"]["Camera2ExposureTime"] = ui->Camera2ExposureTimeLE->text().toStdString().data();
        m_root["CamareParams"]["Camera2Gain"] = ui->Camera2GainLE->text().toStdString().data();
        m_root["CamareParams"]["Camera3Frame"] = ui->Camera3FrameLE->text().toStdString().data();
        m_root["CamareParams"]["Camera3PhotoRow"] = ui->Camera3PhotoRowLE->text().toStdString().data();
        m_root["CamareParams"]["Camera3ExposureTime"] = ui->Camera3ExposureTimeLE->text().toStdString().data();
        m_root["CamareParams"]["Camera3Gain"] = ui->Camera3GainLE->text().toStdString().data();
    }
    {//编码器参数
        m_root["EncoderParams"]["EncodeUnitToDist"] = ui->EncodeUnitToDistLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodePulseFilterUs"] = ui->EncodePulseFilterUsLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeCountEndFlag"] = ui->EncodeCountEndFlagLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeCount"] = ui->EncodeCountLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeTriggerRowCount"] = ui->EncodeTriggerRowCountLE->text().toStdString().data();
        m_root["EncoderParams"]["Encode4FrequencyMultiplierCount"] = ui->Encode4FrequencyMultiplierCountLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeUnitTimePulseCount"] = ui->EncodeUnitTimePulseCountLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeCountTimeHalfSecond"] = ui->EncodeCountTimeHalfSecondLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeChannel"] = ui->EncodeChannelLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodeRevolution"] = ui->EncodeRevolutionLE->text().toStdString().data();
        m_root["EncoderParams"]["RollerPerimeterUm"] = ui->RollerPerimeterUmLE->text().toStdString().data();
        m_root["EncoderParams"]["ExpectSinglePixelAccuracy"] = ui->ExpectSinglePixelAccuracyLE->text().toStdString().data();
        m_root["EncoderParams"]["RollerMaxSpeedToRowCount"] = ui->RollerMaxSpeedToRowCountLE->text().toStdString().data();
        m_root["EncoderParams"]["EveryRowToEncodeCount"] = ui->EveryRowToEncodeCountLE->text().toStdString().data();
        m_root["EncoderParams"]["EncodePressureWheelCountA"] = ui->EncodePressureWheelCountALE->text().toStdString().data();
        m_root["EncoderParams"]["EncodePressureWheelCountB"] = ui->EncodePressureWheelCountBLE->text().toStdString().data();
        m_root["EncoderParams"]["PressureWheel4FrequencyMutliper"] = ui->PressureWheel4FrequencyMutliperLE->text().toStdString().data();
        m_root["EncoderParams"]["PressureEncodecoefficient"] = ui->PressureEncodecoefficientLE->text().toStdString().data();
    }
    {//控制器参数
        m_root["ControllerParams"]["PixelAccuracyUm"] = ui->PixelAccuracyUmLE->text().toStdString().data();
        m_root["ControllerParams"]["PhotoelectricSignalPulseFilter"] = ui->PhotoelectricSignalPulseFilterLE->text().toStdString().data();
        m_root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"] = ui->CamareTrigerPulseContinueTime10nsLE->text().toStdString().data();
        m_root["ControllerParams"]["PhotoelectricToCamareDist"] = ui->PhotoelectricToCamareDistLE->text().toStdString().data();
        m_root["ControllerParams"]["CamareFrameTrigerDelayRowCount"] = ui->CamareFrameTrigerDelayRowCountLE->text().toStdString().data();
        m_root["ControllerParams"]["FrameSignalContinueTime"] = ui->FrameSignalContinueTimeLE->text().toStdString().data();
        m_root["ControllerParams"]["ModuleEnableSignal"] = ui->ModuleEnableSignalLE->text().toStdString().data();
        m_root["ControllerParams"]["CamarePhotoRowCount"] = ui->CamarePhotoRowCountLE->text().toStdString().data();
        m_root["ControllerParams"]["InnerRowFrequency"] = ui->InnerRowFrequencyLE->text().toStdString().data();
        m_root["ControllerParams"]["PhotoMode"] = ui->PhotoModeLE->text().toStdString().data();
        m_root["ControllerParams"]["PhotoEndDelayRowCount"] = ui->PhotoEndDelayRowCountLE->text().toStdString().data();
    }
    {//光源控制器参数
        m_root["LighterParams"]["LightField1DelayTime"] = ui->LightField1DelayTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField1GlowTime"] = ui->LightField1GlowTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField2DelayTime"] = ui->LightField2DelayTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField2GlowTime"] = ui->LightField2GlowTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField3DelayTime"] = ui->LightField3DelayTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField3GlowTime"] = ui->LightField3GlowTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField4DelayTime"] = ui->LightField4DelayTimeLE->text().toStdString().data();
        m_root["LighterParams"]["LightField4GlowTime"] = ui->LightField4GlowTimeLE->text().toStdString().data();
        m_root["LighterParams"]["SelectedLightFieldNumber"] = ui->SelectedLightFieldNumberLE->text().toStdString().data();
        m_root["LighterParams"]["HorizontalDarkfieldSelectRegister"] = ui->HorizontalDarkfieldSelectRegisterLE->text().toStdString().data();
        m_root["LighterParams"]["CamareAndLightFieldControl"] = QString::number(ui->CamareAndLightFieldControlCB->currentIndex()).toStdString().data();
        m_root["LighterParams"]["SignalSwitch"] = ui->SignalSwitchLE->text().toStdString().data();
        m_root["LighterParams"]["RowSignalSelected"] = ui->RowSignalSelectedLE->text().toStdString().data();
    }
    std::string json_content = writer.write(m_root);
    std::ofstream ofs;
    ofs.open(filename.toStdString().data());
    if (ofs.is_open()) {
        ofs<<json_content;
        ofs.close();
    }
}

//新建工单
void LightControl::slotCreateRecipe()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
    QString defaultRecipeFileName = current_date + QString(".json");
    QString newRecipeFileName = INFOMATION.inputMessageBox(this,"新建工单","请输入新建工单名称",defaultRecipeFileName);
    LightControl::createNewRecipeFile(newRecipeFileName);
}

//拷贝工单
void LightControl::slotCopyRecipe()
{
    QString currentFileName = ui->RecipeCB->currentText();
    QString copyName = "copy_" + currentFileName;
    LightControl::writeTableToRecipe(copyName);
}

//void LightControl::slotSystemNameSetBT()
//{
//    PARAM.setSystemName(ui->SystemNameLE->text());
//    INFOMATION.informationMessageBox(this,"设置对话框","设置成功");
//}
NO_TCP_SET_BUTTON_DEFINITION(ui->SystemNameLE->text(),SystemName)

void LightControl::slotSetBTCameraNum()
{
    PARAM.setCameraCounts(ui->CameraNumLE->text().toUInt());
    INFOMATION.informationMessageBox(this,"设置对话框","设置成功");
}

NO_TCP_SET_BUTTON_DEFINITION(ui->Camera0NameLE->text(),Camera0Name)
NO_TCP_SET_BUTTON_DEFINITION(ui->Camera1NameLE->text(),Camera1Name)
NO_TCP_SET_BUTTON_DEFINITION(ui->Camera2NameLE->text(),Camera2Name)
NO_TCP_SET_BUTTON_DEFINITION(ui->Camera3NameLE->text(),Camera3Name)
NO_TCP_SET_BUTTON_DEFINITION(ui->ServerIPLE->text(),ServerIP)

void LightControl::slotSetBTPort()
{
    PARAM.setPort(ui->PortLE->text().toUInt());
    INFOMATION.informationMessageBox(this,"设置对话框","设置成功");
}

void LightControl::slotSaveBTSystemName()
{
    //设置全局变量
    PARAM.setSystemName(ui->SystemNameLE->text());
    //写入文件
    Json::FastWriter writer;
    m_root["SystemParams"]["SystemName"] = ui->SystemNameLE->text().toStdString().data();
    QString filename = ui->RecipeCB->currentText();
    std::string json_content = writer.write(m_root);
    std::ofstream ofs;
    ofs.open(filename.toStdString().data());
    if (ofs.is_open()) {
        ofs<<json_content;
        ofs.close();
    }
    INFOMATION.informationMessageBox(this,"保存对话框","保存成功");
}

void LightControl::slotSaveBTCameraNum()
{
    // 设置全局变量
    PARAM.setCameraCounts(ui->CameraNumLE->text().toUInt());
    //
}

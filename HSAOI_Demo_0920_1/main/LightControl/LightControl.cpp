#include "LightControl.h"
#include "ui_LightControl.h"
#include <QMessageBox>
#include <QTimer>
#include <cmath>
#pragma execution_character_set("utf-8")

LightControl::LightControl(RegParasComm& sig_comm, QWidget* parent)
    : QWidget(parent)
    ,m_pSig_comm(sig_comm)
    , ui(new Ui::LightControl)
{
    ui->setupUi(this);

    SigCtrlData = new SignalControlData(sig_comm);
    sigctrl = new SignalControl();

    ui->treeWidget->setColumnWidth(0, 230);

    Layout0 = new QHBoxLayout(this);
    Layout1 = new QVBoxLayout(this);

    this->setLayout(Layout0);
    Layout0->addWidget(ui->treeWidget);

    Layout0->addLayout(Layout1);

    Layout1->addWidget(ui->Get);
    Layout1->addWidget(ui->Set);
    Layout1->addWidget(ui->Save);
    Layout1->addWidget(ui->Trigger);
    Layout1->setAlignment(Qt::AlignTop);

    ui->Get->setText("获取参数");
    ui->Set->setText("设置参数");
    ui->Save->setText("保存参数");
    ui->Trigger->setText("触发");

    specificItem0 = ui->treeWidget->topLevelItem(0);//编码器参数
    childItem0 = specificItem0->child(0);
    childItem1 = specificItem0->child(1);
    childItem2 = specificItem0->child(2);
    childItem3 = specificItem0->child(3);
    childItem4 = specificItem0->child(4);
    childItem5 = specificItem0->child(5);
    childItem6 = specificItem0->child(6);
    childItem7 = specificItem0->child(7);
    childItem8 = specificItem0->child(8);
    childItem9 = specificItem0->child(9);
    childItem10 = specificItem0->child(10);
    childItem11 = specificItem0->child(11);
    childItem12 = specificItem0->child(12);
    childItem13 = specificItem0->child(13);
    childItem_rollerACount = specificItem0->child(14);
    childItem_rollerBCount = specificItem0->child(15);
    childItemAB4 = specificItem0->child(16);
    chileItem_rollerCofficient = specificItem0->child(17);

    specificItem1 = ui->treeWidget->topLevelItem(1);//控制器系统参数
    childItem14 = specificItem1->child(0);
    childItem15 = specificItem1->child(1);
    childItem16 = specificItem1->child(2);
    childItem17 = specificItem1->child(3);
    childItem18 = specificItem1->child(4);
    childItem19 = specificItem1->child(5);
    childItem20 = specificItem1->child(6);
    childItem21 = specificItem1->child(7);
    childItem22 = specificItem1->child(8);
    chileItem_photoMode = specificItem1->child(9);
    chileItem_photoEndDelayLine = specificItem1->child(10);

    specificItem2 = ui->treeWidget->topLevelItem(2);//光源控制器参数
    childItem23 = specificItem2->child(0);
    childItem24 = specificItem2->child(1);
    childItem25 = specificItem2->child(2);
    childItem26 = specificItem2->child(3);
    childItem27 = specificItem2->child(4);
    childItem28 = specificItem2->child(5);
    childItem29 = specificItem2->child(6);
    childItem30 = specificItem2->child(7);
    childItem31 = specificItem2->child(8);
    childItem32 = specificItem2->child(9);
    childItem33 = specificItem2->child(10);
    childItem34 = specificItem2->child(11);

    childItem35 = specificItem2->child(26);
    childItem36 = specificItem2->child(27);
    childItem37 = specificItem2->child(28);

    childItem43 = specificItem2->child(12);
    childItem44 = specificItem2->child(13);
    childItem45 = specificItem2->child(14);
    childItem46 = specificItem2->child(15);
    childItem47 = specificItem2->child(16);
    childItem48 = specificItem2->child(17);
    childItem49 = specificItem2->child(18);
    childItem50 = specificItem2->child(19);
    childItem51 = specificItem2->child(20);
    childItem52 = specificItem2->child(21);
    childItem53 = specificItem2->child(22);
    childItem54 = specificItem2->child(23);
    childItem55 = specificItem2->child(24);
    childItem56 = specificItem2->child(25);

    connect(ui->treeWidget, &QTreeWidget::itemDoubleClicked, this,&LightControl::onItemDoubleClicked);
    connect(ui->Set, SIGNAL(clicked()), this, SLOT(slot_setButton_clicked()));
    connect(ui->Get, SIGNAL(clicked()), this, SLOT(slot_getButton_clicked()));
    connect(ui->Save, SIGNAL(clicked()), this, SLOT(slot_saveButton_clicked()));


    slot_InitTree();
    ui->treeWidget->expandAll();
    timer1=new QTimer();
    connect(timer1,&QTimer::timeout,this,&LightControl::slot_updateCode);
    timer1->start(100);

}

void LightControl::onItemDoubleClicked(QTreeWidgetItem* item, int column)
{
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

    childItem0->setText(1, QString::number(SigCtrlData->sigctrl->temp0));
    childItem1->setText(1, QString::number(SigCtrlData->sigctrl->temp1));
    childItem2->setText(1, QString::number(SigCtrlData->sigctrl->temp2));
//    childItem3->setText(1, QString::number(SigCtrlData->sigctrl->temp3));
    childItem4->setText(1, QString::number(SigCtrlData->sigctrl->temp4));
//    childItem5->setText(1, QString::number(SigCtrlData->sigctrl->temp5));
//    childItem6->setText(1, QString::number(SigCtrlData->sigctrl->temp6));
    childItem7->setText(1, QString::number(SigCtrlData->sigctrl->temp7));
    childItem8->setText(1, QString::number(SigCtrlData->sigctrl->temp8));
    childItem9->setText(1, QString::number(SigCtrlData->sigctrl->temp9));
    childItem10->setText(1, QString::number(SigCtrlData->sigctrl->temp10));
    childItem11->setText(1, QString::number(SigCtrlData->sigctrl->temp11));
    childItem12->setText(1, QString::number(SigCtrlData->sigctrl->temp12));
    childItem13->setText(1, QString::number(SigCtrlData->sigctrl->temp13));
    childItem14->setText(1, QString::number(SigCtrlData->sigctrl->temp14));
    childItem15->setText(1, QString::number(SigCtrlData->sigctrl->temp15));
    childItem16->setText(1, QString::number(SigCtrlData->sigctrl->temp16));
    childItem17->setText(1, QString::number(SigCtrlData->sigctrl->temp17));
    childItem18->setText(1, QString::number(SigCtrlData->sigctrl->temp18));
    childItem19->setText(1, QString::number(SigCtrlData->sigctrl->temp19));
    childItem20->setText(1, QString::number(SigCtrlData->sigctrl->temp20));
    childItem21->setText(1, QString::number(SigCtrlData->sigctrl->temp21));
    childItem22->setText(1, QString::number(SigCtrlData->sigctrl->temp22));
    childItem23->setText(1, QString::number(SigCtrlData->sigctrl->temp23));
    childItem24->setText(1, QString::number(SigCtrlData->sigctrl->temp24));
    childItem25->setText(1, QString::number(SigCtrlData->sigctrl->temp25));
    childItem26->setText(1, QString::number(SigCtrlData->sigctrl->temp26));
    childItem27->setText(1, QString::number(SigCtrlData->sigctrl->temp27));
    childItem28->setText(1, QString::number(SigCtrlData->sigctrl->temp28));
    childItem29->setText(1, QString::number(SigCtrlData->sigctrl->temp29));
    childItem30->setText(1, QString::number(SigCtrlData->sigctrl->temp30));
    childItem31->setText(1, QString::number(SigCtrlData->sigctrl->temp31));
    childItem32->setText(1, QString::number(SigCtrlData->sigctrl->temp32));
    childItem33->setText(1, QString::number(SigCtrlData->sigctrl->temp33));
    childItem34->setText(1, QString::number(SigCtrlData->sigctrl->temp34));
    //16进制显示
    childItem35->setText(1, QString::number(SigCtrlData->sigctrl->temp35,16));
    childItem36->setText(1, QString::number(SigCtrlData->sigctrl->temp36));
    childItem37->setText(1, QString::number(SigCtrlData->sigctrl->temp37));

    childItem43->setText(1, QString::number(SigCtrlData->sigctrl->temp43));
    childItem44->setText(1, QString::number(SigCtrlData->sigctrl->temp44));
    childItem45->setText(1, QString::number(SigCtrlData->sigctrl->temp45));
    childItem46->setText(1, QString::number(SigCtrlData->sigctrl->temp46));
    childItem47->setText(1, QString::number(SigCtrlData->sigctrl->temp47));
    childItem48->setText(1, QString::number(SigCtrlData->sigctrl->temp48));
    childItem49->setText(1, QString::number(SigCtrlData->sigctrl->temp49));
    childItem50->setText(1, QString::number(SigCtrlData->sigctrl->temp50));
    childItem51->setText(1, QString::number(SigCtrlData->sigctrl->temp51));
    childItem52->setText(1, QString::number(SigCtrlData->sigctrl->temp52));
    childItem53->setText(1, QString::number(SigCtrlData->sigctrl->temp53));
    childItem54->setText(1, QString::number(SigCtrlData->sigctrl->temp54));
    childItem55->setText(1, QString::number(SigCtrlData->sigctrl->temp55));
    childItem56->setText(1, QString::number(SigCtrlData->sigctrl->temp56));

    Global::FieldNumberSet=SigCtrlData->sigctrl->temp55;

    childItem_rollerACount->setText(1,QString::number(SigCtrlData->sigctrl->tempRollerACount));
    childItem_rollerBCount->setText(1,QString::number(SigCtrlData->sigctrl->tempRollerBCount));
    childItemAB4->setText(1, QString::number(SigCtrlData->sigctrl->tempRoller4ABCount));
    chileItem_rollerCofficient->setText(1,QString::number(SigCtrlData->sigctrl->tempRollerCofficient));

    chileItem_photoMode->setText(1,QString::number(SigCtrlData->sigctrl->tempAutoPhoto));
    chileItem_photoEndDelayLine->setText(1,QString::number(SigCtrlData->sigctrl->tempPhotoEndDelayLine));

    QString strCo=chileItem_rollerCofficient->text(1);
    Global::encodeRollerCofficient = strCo.toDouble();
}

void LightControl::slot_getButton_clicked()
{
    SigCtrlData->GetData();

    childItem0->setText(1, QString::number(SigCtrlData->sigctrl->temp0));
    childItem1->setText(1, QString::number(SigCtrlData->sigctrl->temp1));
    childItem2->setText(1, QString::number(SigCtrlData->sigctrl->temp2));
//    childItem3->setText(1, QString::number(SigCtrlData->sigctrl->temp3));
    childItem4->setText(1, QString::number(SigCtrlData->sigctrl->temp4));
//    childItem5->setText(1, QString::number(SigCtrlData->sigctrl->temp5));
//    childItem6->setText(1, QString::number(SigCtrlData->sigctrl->temp6));
    childItem7->setText(1, QString::number(SigCtrlData->sigctrl->temp7));
    childItem8->setText(1, QString::number(SigCtrlData->sigctrl->temp8));
    childItem9->setText(1, QString::number(SigCtrlData->sigctrl->temp9));
    childItem10->setText(1, QString::number(SigCtrlData->sigctrl->temp10));
    childItem11->setText(1, QString::number(SigCtrlData->sigctrl->temp11));
    childItem12->setText(1, QString::number(SigCtrlData->sigctrl->temp12));
    childItem13->setText(1, QString::number(SigCtrlData->sigctrl->temp13));
    childItem14->setText(1, QString::number(SigCtrlData->sigctrl->temp14));
    childItem15->setText(1, QString::number(SigCtrlData->sigctrl->temp15));
    childItem16->setText(1, QString::number(SigCtrlData->sigctrl->temp16));
    childItem17->setText(1, QString::number(SigCtrlData->sigctrl->temp17));
    childItem18->setText(1, QString::number(SigCtrlData->sigctrl->temp18));
    childItem19->setText(1, QString::number(SigCtrlData->sigctrl->temp19));
    childItem20->setText(1, QString::number(SigCtrlData->sigctrl->temp20));
    childItem21->setText(1, QString::number(SigCtrlData->sigctrl->temp21));
    childItem22->setText(1, QString::number(SigCtrlData->sigctrl->temp22));
    childItem23->setText(1, QString::number(SigCtrlData->sigctrl->temp23));
    childItem24->setText(1, QString::number(SigCtrlData->sigctrl->temp24));
    childItem25->setText(1, QString::number(SigCtrlData->sigctrl->temp25));
    childItem26->setText(1, QString::number(SigCtrlData->sigctrl->temp26));
    childItem27->setText(1, QString::number(SigCtrlData->sigctrl->temp27));
    childItem28->setText(1, QString::number(SigCtrlData->sigctrl->temp28));
    childItem29->setText(1, QString::number(SigCtrlData->sigctrl->temp29));
    childItem30->setText(1, QString::number(SigCtrlData->sigctrl->temp30));
    childItem31->setText(1, QString::number(SigCtrlData->sigctrl->temp31));
    childItem32->setText(1, QString::number(SigCtrlData->sigctrl->temp32));
    childItem33->setText(1, QString::number(SigCtrlData->sigctrl->temp33));
    childItem34->setText(1, QString::number(SigCtrlData->sigctrl->temp34));
    childItem35->setText(1, QString::number(SigCtrlData->sigctrl->temp35,16));
    childItem36->setText(1, QString::number(SigCtrlData->sigctrl->temp36));
    childItem37->setText(1, QString::number(SigCtrlData->sigctrl->temp37));


    childItem43->setText(1, QString::number(SigCtrlData->sigctrl->temp43));
    childItem44->setText(1, QString::number(SigCtrlData->sigctrl->temp44));
    childItem45->setText(1, QString::number(SigCtrlData->sigctrl->temp45));
    childItem46->setText(1, QString::number(SigCtrlData->sigctrl->temp46));
    childItem47->setText(1, QString::number(SigCtrlData->sigctrl->temp47));
    childItem48->setText(1, QString::number(SigCtrlData->sigctrl->temp48));
    childItem49->setText(1, QString::number(SigCtrlData->sigctrl->temp49));
    childItem50->setText(1, QString::number(SigCtrlData->sigctrl->temp50));
    childItem51->setText(1, QString::number(SigCtrlData->sigctrl->temp51));
    childItem52->setText(1, QString::number(SigCtrlData->sigctrl->temp52));
    childItem53->setText(1, QString::number(SigCtrlData->sigctrl->temp53));
    childItem54->setText(1, QString::number(SigCtrlData->sigctrl->temp54));
    childItem55->setText(1, QString::number(SigCtrlData->sigctrl->temp55));
    childItem56->setText(1, QString::number(SigCtrlData->sigctrl->temp56));

    QString strCo=chileItem_rollerCofficient->text(1);
    Global::encodeRollerCofficient = strCo.toDouble();
}

void LightControl::slot_setButton_clicked()
{
    SigCtrlData->sigctrl->temp0 = childItem0->text(1).toUInt();
    SigCtrlData->sigctrl->temp1 = childItem1->text(1).toUInt();
    //  temp[2] = childItem2->text(1).toInt();
    //  m_pSig_comm.SetRegs(ADDR2, ADDR2, &temp[2]);
    //  temp[3] = childItem3->text(1).toInt();
    //  m_pSig_comm.SetRegs(ADDR3, ADDR3, &temp[3]);
    //  temp[4] = childItem4->text(1).toInt();
    //  m_pSig_comm.SetRegs(ADDR4, ADDR4, &temp[4]);
    //  temp[5] = childItem5->text(1).toInt();
    //  m_pSig_comm.SetRegs(ADDR5, ADDR5, &temp[5]);
    //  temp[6] = childItem6->text(1).toInt();
    //  m_pSig_comm.SetRegs(ADDR6, ADDR6, &temp[6]);
    SigCtrlData->sigctrl->temp7 = childItem7->text(1).toUInt();
    SigCtrlData->sigctrl->temp8 = childItem8->text(1).toUInt();
    SigCtrlData->sigctrl->temp9 = childItem9->text(1).toUInt();
    SigCtrlData->sigctrl->temp10 = childItem10->text(1).toUInt();
    SigCtrlData->sigctrl->temp11 = childItem11->text(1).toUInt();
    SigCtrlData->sigctrl->temp12 = childItem12->text(1).toUInt();
//    SigCtrlData->sigctrl->temp13 = childItem13->text(1).toUInt();
    SigCtrlData->sigctrl->temp14 = childItem14->text(1).toUInt();
    SigCtrlData->sigctrl->temp15 = childItem15->text(1).toUInt();
    SigCtrlData->sigctrl->temp16 = childItem16->text(1).toUInt();
    SigCtrlData->sigctrl->temp17 = childItem17->text(1).toUInt();
    SigCtrlData->sigctrl->temp18 = childItem18->text(1).toUInt();
    SigCtrlData->sigctrl->temp19 = childItem19->text(1).toUInt();
    SigCtrlData->sigctrl->temp20 = childItem20->text(1).toUInt();
    SigCtrlData->sigctrl->temp21 = childItem21->text(1).toUInt();
    SigCtrlData->sigctrl->temp22 = childItem22->text(1).toUInt();
    SigCtrlData->sigctrl->temp23 = childItem23->text(1).toUInt();
    SigCtrlData->sigctrl->temp24 = childItem24->text(1).toUInt();
    SigCtrlData->sigctrl->temp25 = childItem25->text(1).toUInt();
    SigCtrlData->sigctrl->temp26 = childItem26->text(1).toUInt();
    SigCtrlData->sigctrl->temp27 = childItem27->text(1).toUInt();
    SigCtrlData->sigctrl->temp28 = childItem28->text(1).toUInt();
    SigCtrlData->sigctrl->temp29 = childItem29->text(1).toUInt();
    SigCtrlData->sigctrl->temp30 = childItem30->text(1).toUInt();
    SigCtrlData->sigctrl->temp31 = childItem31->text(1).toUInt();
    SigCtrlData->sigctrl->temp32 = childItem32->text(1).toUInt();
    SigCtrlData->sigctrl->temp33 = childItem33->text(1).toUInt();
    SigCtrlData->sigctrl->temp34 = childItem34->text(1).toUInt();

    QString str35=childItem35->text(1);
    bool ok;
    int val=str35.toInt(&ok,16);
    qDebug()<<"str35 begin:"<<str35<<"Val:"<<val;
    //str35=QString(val,10);
    //qDebug()<<"AAA"<<val<<"二进制："<<str35;
    SigCtrlData->sigctrl->temp35 =val;
    //SigCtrlData->sigctrl->temp35 = childItem35->text(1).toUInt();
    SigCtrlData->sigctrl->temp36 = childItem36->text(1).toUInt();
    SigCtrlData->sigctrl->temp37 = childItem37->text(1).toUInt();

    SigCtrlData->sigctrl->temp43 = childItem43->text(1).toUInt();
    SigCtrlData->sigctrl->temp44 = childItem44->text(1).toUInt();
    SigCtrlData->sigctrl->temp45 = childItem45->text(1).toUInt();
    SigCtrlData->sigctrl->temp46 = childItem46->text(1).toUInt();
    SigCtrlData->sigctrl->temp47 = childItem47->text(1).toUInt();
    SigCtrlData->sigctrl->temp48 = childItem48->text(1).toUInt();
    SigCtrlData->sigctrl->temp49 = childItem49->text(1).toUInt();
    SigCtrlData->sigctrl->temp50 = childItem50->text(1).toUInt();
    SigCtrlData->sigctrl->temp51 = childItem51->text(1).toUInt();
    SigCtrlData->sigctrl->temp52 = childItem52->text(1).toUInt();
    SigCtrlData->sigctrl->temp53 = childItem53->text(1).toUInt();
    SigCtrlData->sigctrl->temp54 = childItem54->text(1).toUInt();
    SigCtrlData->sigctrl->temp55 = childItem55->text(1).toUInt();
    SigCtrlData->sigctrl->temp56 = childItem56->text(1).toUInt();


    Global::FieldNumberSet=SigCtrlData->sigctrl->temp55;

    SigCtrlData->sigctrl->tempRollerACount = childItem_rollerACount->text(1).toUInt();
    SigCtrlData->sigctrl->tempRollerBCount = childItem_rollerBCount->text(1).toUInt();
    SigCtrlData->sigctrl->tempRoller4ABCount = childItemAB4->text(1).toUInt();
    SigCtrlData->sigctrl->tempRollerCofficient = chileItem_rollerCofficient->text(1).toDouble();
    SigCtrlData->sigctrl->tempAutoPhoto = chileItem_photoMode->text(1).toUInt();
    SigCtrlData->sigctrl->tempPhotoEndDelayLine = chileItem_photoEndDelayLine->text(1).toUInt();
    QString strCo=chileItem_rollerCofficient->text(1);
    Global::encodeRollerCofficient = strCo.toDouble();

    SigCtrlData->SetData();
}

void LightControl::slot_saveButton_clicked()
{
    SigCtrlData->sigctrl->temp0 = childItem0->text(1).toUInt();
    SigCtrlData->sigctrl->temp1 = childItem1->text(1).toUInt();
    SigCtrlData->sigctrl->temp2 = childItem2->text(1).toUInt();
    SigCtrlData->sigctrl->temp3 = childItem3->text(1).toUInt();
    SigCtrlData->sigctrl->temp4 = childItem4->text(1).toUInt();
    SigCtrlData->sigctrl->temp5 = childItem5->text(1).toUInt();
    SigCtrlData->sigctrl->temp6 = childItem6->text(1).toUInt();
    SigCtrlData->sigctrl->temp7 = childItem7->text(1).toUInt();
    SigCtrlData->sigctrl->temp8 = childItem8->text(1).toUInt();
    SigCtrlData->sigctrl->temp9 = childItem9->text(1).toUInt();
    SigCtrlData->sigctrl->temp10 = childItem10->text(1).toUInt();
    SigCtrlData->sigctrl->temp11 = childItem11->text(1).toUInt();
    SigCtrlData->sigctrl->temp12 = childItem12->text(1).toUInt();
    SigCtrlData->sigctrl->temp13 = childItem13->text(1).toUInt();
    SigCtrlData->sigctrl->temp14 = childItem14->text(1).toUInt();
    SigCtrlData->sigctrl->temp15 = childItem15->text(1).toUInt();
    SigCtrlData->sigctrl->temp16 = childItem16->text(1).toUInt();
    SigCtrlData->sigctrl->temp17 = childItem17->text(1).toUInt();
    SigCtrlData->sigctrl->temp18 = childItem18->text(1).toUInt();
    SigCtrlData->sigctrl->temp19 = childItem19->text(1).toUInt();
    SigCtrlData->sigctrl->temp20 = childItem20->text(1).toUInt();
    SigCtrlData->sigctrl->temp21 = childItem21->text(1).toUInt();
    SigCtrlData->sigctrl->temp22 = childItem22->text(1).toUInt();
    SigCtrlData->sigctrl->temp23 = childItem23->text(1).toUInt();
    SigCtrlData->sigctrl->temp24 = childItem24->text(1).toUInt();
    SigCtrlData->sigctrl->temp25 = childItem25->text(1).toUInt();
    SigCtrlData->sigctrl->temp26 = childItem26->text(1).toUInt();
    SigCtrlData->sigctrl->temp27 = childItem27->text(1).toUInt();
    SigCtrlData->sigctrl->temp28 = childItem28->text(1).toUInt();
    SigCtrlData->sigctrl->temp29 = childItem29->text(1).toUInt();
    SigCtrlData->sigctrl->temp30 = childItem30->text(1).toUInt();
    SigCtrlData->sigctrl->temp31 = childItem31->text(1).toUInt();
    SigCtrlData->sigctrl->temp32 = childItem32->text(1).toUInt();
    SigCtrlData->sigctrl->temp33 = childItem33->text(1).toUInt();
    SigCtrlData->sigctrl->temp34 = childItem34->text(1).toUInt();

    QString str35=childItem35->text(1);
    bool ok;
    int val=str35.toInt(&ok,16);
    qDebug()<<"str35 begin:"<<str35<<"Val:"<<val;
    //str35=QString(val,10);
    //qDebug()<<"AAA"<<val<<"二进制："<<str35;
    SigCtrlData->sigctrl->temp35 =val;
   // SigCtrlData->sigctrl->temp35 = childItem35->text(1).toUInt();
    SigCtrlData->sigctrl->temp36 = childItem36->text(1).toUInt();
    SigCtrlData->sigctrl->temp37 = childItem37->text(1).toUInt();

    SigCtrlData->sigctrl->temp43 = childItem43->text(1).toUInt();
    SigCtrlData->sigctrl->temp44 = childItem44->text(1).toUInt();
    SigCtrlData->sigctrl->temp45 = childItem45->text(1).toUInt();
    SigCtrlData->sigctrl->temp46 = childItem46->text(1).toUInt();
    SigCtrlData->sigctrl->temp47 = childItem47->text(1).toUInt();
    SigCtrlData->sigctrl->temp48 = childItem48->text(1).toUInt();
    SigCtrlData->sigctrl->temp49 = childItem49->text(1).toUInt();
    SigCtrlData->sigctrl->temp50 = childItem50->text(1).toUInt();
    SigCtrlData->sigctrl->temp51 = childItem51->text(1).toUInt();
    SigCtrlData->sigctrl->temp52 = childItem52->text(1).toUInt();
    SigCtrlData->sigctrl->temp53 = childItem53->text(1).toUInt();
    SigCtrlData->sigctrl->temp54 = childItem54->text(1).toUInt();
    SigCtrlData->sigctrl->temp55 = childItem55->text(1).toUInt();
    SigCtrlData->sigctrl->temp56 = childItem56->text(1).toUInt();

    SigCtrlData->sigctrl->tempRollerACount = childItem_rollerACount->text(1).toUInt();
    SigCtrlData->sigctrl->tempRollerBCount = childItem_rollerBCount->text(1).toUInt();
    SigCtrlData->sigctrl->tempRoller4ABCount = childItemAB4->text(1).toUInt();
    SigCtrlData->sigctrl->tempRollerCofficient = chileItem_rollerCofficient->text(1).toDouble();
    SigCtrlData->sigctrl->tempAutoPhoto = chileItem_photoMode->text(1).toUInt();
    SigCtrlData->sigctrl->tempPhotoEndDelayLine = chileItem_photoEndDelayLine->text(1).toUInt();
    QString strCo=chileItem_rollerCofficient->text(1);
    Global::encodeRollerCofficient = strCo.toDouble();

    SigCtrlData->SaveData();
}

void LightControl::on_Trigger_clicked()
{
    SigCtrlData->Trigger();
}

void LightControl::slot_updateCode()
{
    childItem3->setText(1, QString::number(Global::CodeCount));
    childItem4->setText(1, QString::number(Global::CodeLineCount));
    childItem5->setText(1, QString::number(Global::Code4Count));
    childItem6->setText(1, QString::number(Global::CodePerCount));
    //计算Y长度
    double radian = Global::RollerAngle;
    double cosValue = cos(radian);
    //qDebug()<<"cosValue"<<cosValue;
    Global::encodeRollerYLength = Global::encodeRollerCount * Global::encodeRollerCofficient * cosValue;
    //qDebug()<<"encodeRollerYLength"<< Global::encodeRollerYLength;
    childItem_rollerACount->setText(1,QString::number(Global::encodeARollerCount));
    childItem_rollerBCount->setText(1,QString::number(Global::encodeBRollerCount));
    childItemAB4->setText(1,QString::number(Global::encodeAB4));
}

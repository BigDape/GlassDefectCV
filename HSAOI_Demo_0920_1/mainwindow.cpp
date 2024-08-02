#include "mainwindow.h"
#include "QLabel"
#include "math.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <halconcpp/HalconCpp.h>
#include <hdevengine/HDevEngineCpp.h>
#include <QProgressDialog>
#include <QString>
#include <fstream>
#include <QTextStream>
#include <QFileDialog>
#include <iostream>
#include <stdlib.h>
#include <QThreadPool>
#include <thread>


#pragma execution_character_set("utf-8")
using namespace HalconCpp;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , JsonRecipeView(NULL)
    , SystemSettings(NULL)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //
    // 设置窗口属性
    // Qt::FramelessWindowHint(无窗口边框)
    // Qt::WindowSystemMenuHint(为窗口添加一个窗口系统系统菜单，并尽可能地添加一个关闭按钮)
    // Qt::WindowMinMaxButtonsHint(为窗口添加一个“最小化”按钮 和一个“最大化”按钮)
    //
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    // 获取配置文件
    QString RecipePath = "Recipes/" + Global::CurrentRecipe + ".json";
    JsonRecipe = new JsonParse2Map(RecipePath);
    //注册自定义类型，供connect调用
    qRegisterMetaType<GlassDataBaseInfo>("GlassDataBaseInfo");//注册类型，否则不能调用
    qRegisterMetaType<QList<FlawPoint>>("QList<FlawPoint>");//注册类型，否则不能调用
    qRegisterMetaType<SummaryResult>("SummaryResult");//注册类型，否则不能调用
    //初始化相机
    for(int i=0; i<Global::camDefineNum; i++){
        Cameras.append(new DushenBasicFunc(this,i,JsonRecipe));
    }
    //初始化信号平台
    initSignalPlatform();
    //初始化菜单栏
    initMenu();
    // 创建缺陷显示图
    Create_FlawShowWidget();
    // 创建玻璃统计表
    Create_GlassStatisticsTable();
    // 创建单个缺陷界面
    Create_SingleFlawShow();
    // 尺寸信息
    Create_SingleSizeShow();
    // 相机
    Create_CameraShow();
    initLayout();           //初始化布局
    initThread();           //初始化多线程
    initDatabase();         //初始化数据库

    this->showMaximized();
    //
    // 标题栏
    //
    connect(m_pExit, SIGNAL(triggered()), this, SLOT(slot_CloseSystem()));                  //点击退出响应事件
    connect(m_pSettings, SIGNAL(triggered()), this,SLOT(slot_ShowSystemSettingForm()));     //点击设置响应事件
    connect(m_pStart, SIGNAL(triggered()), this, SLOT(slot_ActionStart()));                 //点击开始响应事件
    connect(m_pStop, SIGNAL(triggered()), this, SLOT(slot_ActionStop()));                   //点击停止响应事件
    connect(m_pCameraSettings, SIGNAL(triggered()), this, SLOT(slot_CameraShow()));         //点击相机响应事件
    connect(m_pDB, SIGNAL(triggered()), this, SLOT(slot_DB()));                             //点击数据查询响应事件
    connect(m_pRunningInfo, SIGNAL(triggered()), this, SLOT(slot_RunningInfo()));           //点击日志响应事件
    connect(m_offline, SIGNAL(triggered()), this, SLOT(slot_Offline()));                    //点击离线模式响应事件

    connect(this, SIGNAL(sig_FlawWidgetChange()), m_FlawShowWidget, SLOT(slot_ChangeFlawShow()));
    connect(m_FlawShowWidget,SIGNAL(sig_sendFlawPoint(FlawPoint)),this,SLOT(slot_SendPoint(FlawPoint)));

    connect(this, &MainWindow::sig_StartButton2CameraStart, Camera_widget, &CamerasWidget::slot_CameraStart);
    connect(this, &MainWindow::sig_StopButton2CameraStop, Camera_widget, &CamerasWidget::slot_CameraStop);

    connect(Detectworker, SIGNAL(sendData(GlassDataBaseInfo)), m_GlassStatisticTable, SLOT(slot_insertRowData(GlassDataBaseInfo)));
    connect(Detectworker, SIGNAL(sig_updateFlaw(double,double)), m_FlawShowWidget, SLOT(slot_GetGlassSize(double,double)));
    connect(Detectworker, SIGNAL(sig_sendPoint(QList<FlawPoint> )), m_FlawShowWidget, SLOT(slot_GetFlawPoints(QList<FlawPoint>)));


    connect(Detectworker, SIGNAL(sig_refreshFlaw(QString,int)), m_SingleFlawShow, SLOT(slot_refrshFlaw(QString,int)));
    connect(Detectworker, SIGNAL(sig_refreshSize(QString, int)), m_SingleSizeShow, SLOT(slot_refreshSize(QString, int)));
    //
    // 绑定信号和槽函数
    //
    connect(m_GlassStatisticTable, SIGNAL(sig_reloadDefect(QString,int)), m_SingleFlawShow, SLOT(slot_refrshFlaw(QString,int)));
    connect(m_GlassStatisticTable, SIGNAL(sig_reloadHole(QString,int)), m_SingleSizeShow, SLOT(slot_refreshSize(QString,int)));
    connect(this, &MainWindow::destroyed, this, &MainWindow::stopThread);                       // 关闭时，结束线程

    //
    //  绑定信号和槽函数
    //
    connect(Detectworker, SIGNAL(sig_UpdateResultInfo(SummaryResult)), m_FlawShowWidget, SLOT(slot_GetGlassResult(SummaryResult)));
    connect(Detectworker,SIGNAL(sig_updateSignalFlaw(QString,int)), m_SingleFlawShow,SLOT(slot_RecieveID(QString,int)));
    connect(m_FlawShowWidget, SIGNAL(sig_updatePreGlassRes(bool)), this, SLOT(slot_updatePreGlassRes(bool)));
    connect(Detectworker, SIGNAL(sig_updateSortRes(SummaryResult)), this, SLOT(slot_updateSortGlassRes(SummaryResult)));
    connect(SigCtrlData, &SignalControlData::sig_updateSortGlassSignal,Detectworker, &Process_Detect::slot_updateSortInfo, Qt::DirectConnection);
    connect(m_FlawShowWidget, SIGNAL(sig_ClearDate()), this, SLOT(slot_clearPreSortGlassInfo()));//清除标题栏上分检核检出两个按钮
    connect(m_FlawShowWidget, SIGNAL(sig_ClearDate()), m_GlassStatisticTable, SLOT(slot_clearRowData()));//清除统计表上的数据

    connect(m_SingleFlawShow, SIGNAL(sig_test()), this, SLOT(slot_test()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenu()
{
    m_pExit = new QAction("&退出", this);
    m_pExit->setShortcut(QKeySequence::Quit);
    m_pExit->setToolTip(tr("Exit System."));
    m_pExit->setIcon(QIcon(":/toolbar/icons/exit.png"));
    ui->toolBar->addAction(m_pExit);

    m_pSettings = new QAction("&设置", this);
    m_pSettings->setToolTip(tr("Device Settings."));
    m_pSettings->setIcon(QIcon(":/toolbar/icons/setup.png"));
    ui->toolBar->addAction(m_pSettings);

    m_pStart = new QAction("&开始", this);
    m_pStart->setToolTip(tr("Start."));
    m_pStart->setIcon(QIcon(":/toolbar/icons/start_icon.png"));
    ui->toolBar->addAction(m_pStart);

    m_pStop = new QAction("&停止", this);
    m_pStop->setToolTip(tr("Stop."));
    m_pStop->setIcon(QIcon(":/toolbar/icons/Stop.png"));
    ui->toolBar->addAction(m_pStop);
    m_pStop->setEnabled(false);

    m_pCameraSettings = new QAction("&相机", this);
    m_pCameraSettings->setToolTip(tr("CameraSet."));
    m_pCameraSettings->setIcon(QIcon(":/toolbar/icons/cameraIcon.png"));
    ui->toolBar->addAction(m_pCameraSettings);

    m_pDB = new QAction("&数据查询", this);
    m_pDB->setShortcut(QKeySequence::Quit);
    m_pDB->setToolTip(tr("Database."));
    m_pDB->setIcon(QIcon(":/toolbar/icons/analysis.png"));
    ui->toolBar->addAction(m_pDB);

    m_pRunningInfo = new QAction("&运行日志", this);
    m_pRunningInfo->setToolTip(tr("RunningInfo."));
    m_pRunningInfo->setIcon(QIcon(":/toolbar/icons/check_mark.png"));
    ui->toolBar->addAction(m_pRunningInfo);

    m_offline = new QAction("&离线模式", this);
    m_offline->setToolTip(tr("Offline."));
    m_offline->setIcon(QIcon(":/toolbar/icons/switch.png"));
    ui->toolBar->addAction(m_offline);

    GlassInfoWidget = new QWidget();

    label1 = new QLabel("检出");
    label2 = new QLabel("分拣");
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
    QFont font2;
    font2.setPointSize(12);
    label1->setFont(font2);
    label2->setFont(font2);
    lineEdit1 = new QLineEdit();
    lineEdit2 = new QLineEdit();
    lineEdit1->setMinimumSize(40, 40);
    lineEdit1->setMaximumSize(40, 40);
    lineEdit2->setMinimumSize(40, 40);
    lineEdit2->setMaximumSize(40, 40);

    lineEdit1->setReadOnly(true);
    lineEdit2->setReadOnly(true);
    lineEdit1->setStyleSheet("color: black;border: none; background-color: #FFFFFF; border-radius: 20px;");
    lineEdit2->setStyleSheet("color: black;border: none; background-color: #FFFFFF; border-radius: 20px;");

    QFont font1;
    font1.setPointSize(18);
    lineEdit1->setFont(font1);
    lineEdit1->setAlignment(Qt::AlignCenter);
    lineEdit1->setText("");

    lineEdit2->setFont(font1);
    lineEdit2->setAlignment(Qt::AlignCenter);
    lineEdit2->setText("");

    // 创建水平布局用于左侧和右侧的控件
    QVBoxLayout* leftLayout = new QVBoxLayout();
    QVBoxLayout* rightLayout = new QVBoxLayout();

    // 创建垂直布局用于放置左侧和右侧的水平布局
    QHBoxLayout* mainLayout = new QHBoxLayout();

    // 将 QLineEdit 和 QLabel 添加到左侧和右侧的水平布局中
    leftLayout->addWidget(lineEdit1);
    leftLayout->addWidget(label1);
    rightLayout->addWidget(lineEdit2);
    rightLayout->addWidget(label2);

    // 将左侧和右侧的水平布局添加到垂直布局中
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    // 设置 GlassInfoWidget 的主布局
    GlassInfoWidget->setLayout(mainLayout);

    GlassInfoWidget->setFixedSize(300, 75);

    QWidget* spacerWidget = new QWidget();
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // 使用 addWidget 将 GlassInfoWidget 添加到 QToolBar 的最右侧
    ui->toolBar->addWidget(spacerWidget);
    ui->toolBar->addWidget(GlassInfoWidget);

    ui->toolBar->setIconSize(QSize(40, 40));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->toggleViewAction()->setEnabled(false);
    ui->toolBar->setFloatable(false);
    ui->toolBar->setMovable(false);
}

void MainWindow::initLayout()
{
    addDockWidget(Qt::TopDockWidgetArea, Dock_FlawShowView);
    Dock_FlawShowView->setMaximumHeight(450);
    Dock_FlawShowView->setMinimumHeight(450);
    Dock_FlawShowView->setAllowedAreas(Qt::TopDockWidgetArea);

    addDockWidget(Qt::TopDockWidgetArea, Dock_CameraShow);
    Dock_CameraShow->setMaximumHeight(450);
    Dock_CameraShow->setMinimumHeight(450);
    Dock_CameraShow->setAllowedAreas(Qt::TopDockWidgetArea);

    tabifyDockWidget(Dock_FlawShowView, Dock_CameraShow);
    Dock_FlawShowView->raise();

    addDockWidget(Qt::BottomDockWidgetArea, Dock_GlassStatisticsTableView);
    Dock_GlassStatisticsTableView->setMinimumHeight(450);
    Dock_GlassStatisticsTableView->setMaximumHeight(450);
    Dock_GlassStatisticsTableView->setAllowedAreas(Qt::BottomDockWidgetArea);

    addDockWidget(Qt::BottomDockWidgetArea, Dock_SingleFlawShowView);
    Dock_SingleFlawShowView->setMinimumHeight(450);
    Dock_SingleFlawShowView->setMaximumHeight(450);
    Dock_SingleFlawShowView->setAllowedAreas(Qt::BottomDockWidgetArea);
    tabifyDockWidget(Dock_GlassStatisticsTableView, Dock_SingleFlawShowView);

    addDockWidget(Qt::BottomDockWidgetArea, Dock_SingleSizeShowView);
    Dock_SingleSizeShowView->setMinimumHeight(450);
    Dock_SingleSizeShowView->setMaximumHeight(450);
    Dock_SingleSizeShowView->setAllowedAreas(Qt::BottomDockWidgetArea);
    tabifyDockWidget(Dock_GlassStatisticsTableView, Dock_SingleSizeShowView);
    Dock_SingleSizeShowView->raise();
    Dock_GlassStatisticsTableView->raise();
}

void MainWindow::initSignalPlatform()
{
    sig_comm = new RegParasComm();
    sig_comm->InitSock(Global::serverIp.toStdString().c_str(), Global::RegParaPort);
    qDebug() << "链接：" << Global::serverIp.toStdString().c_str() << Global::RegParaPort;
    sig_comm->ConnectToServer();
}

void MainWindow::initThread()
{
    _pool = QThreadPool::globalInstance();
    int maxThreadcount = 4;//std::thread::hardware_concurrency();
    qDebug() <<"maxThreadcount =" <<maxThreadcount;
    _pool->setMaxThreadCount(maxThreadcount);
    // 调用halcon算法模块
    Detectworker = new Process_Detect();
    Detectworker->setAutoDelete(false);
    _pool->start(Detectworker);
    // 数据预处理模块
    Tileworker = new ProcessTile(Cameras);
    Tileworker->setAutoDelete(false);
    _pool->start(Tileworker);
    // 信号平台模块
    SigCtrlData = new SignalControlData(*sig_comm);
    SigCtrlData->setAutoDelete(false);
    _pool->start(SigCtrlData);
}

void MainWindow::initDatabase()
{
//    Database = new Jianbo_db();
//    Database->start_connect();
    //    for (int i = 0; i < 10; i++) {
    //        Database->start_insert(QDateTime::currentDateTime(), i * 17, i * 7, i * 11, "OK", i * 3, "400*400", 0, 0, 0, 1, 1, 0, 0, 1, 1, 1);
    //    }
}

void MainWindow::Create_FlawShowWidget()
{
    Dock_FlawShowView = new QDockWidget(this);
    Dock_FlawShowView->setObjectName("FlawShow");
    Dock_FlawShowView->setWindowTitle(QString("缺陷示意图"));
    Dock_FlawShowView->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_FlawShowWidget = new FlawShowWidget(Dock_FlawShowView, JsonRecipe);
    Dock_FlawShowView->setWidget(m_FlawShowWidget);
    Dock_FlawShowView->setFeatures(QDockWidget::DockWidgetFloatable);

}

void MainWindow::Create_GlassStatisticsTable()
{
    Dock_GlassStatisticsTableView = new QDockWidget(this);
    Dock_GlassStatisticsTableView->setObjectName("GlassStatisticsTable");
    Dock_GlassStatisticsTableView->setWindowTitle("数据统计");
    Dock_GlassStatisticsTableView->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_GlassStatisticTable = new GlassStatisticTableWidget(Dock_GlassStatisticsTableView);
    Dock_GlassStatisticsTableView->setWidget(m_GlassStatisticTable);
    Dock_GlassStatisticsTableView->setFeatures(QDockWidget::DockWidgetFloatable);
}

void MainWindow::Create_SingleFlawShow()
{
    Dock_SingleFlawShowView = new QDockWidget(this);
    Dock_SingleFlawShowView->setObjectName("SingleFlaw");
    Dock_SingleFlawShowView->setWindowTitle("单个缺陷");
    Dock_SingleFlawShowView->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_SingleFlawShow = new SingleFlawShowWidget(Qt::Horizontal, Qt::Horizontal, Dock_SingleFlawShowView);
    Dock_SingleFlawShowView->setWidget(m_SingleFlawShow);
    Dock_SingleFlawShowView->setFeatures(QDockWidget::DockWidgetFloatable);
}

void MainWindow::Create_SingleSizeShow()
{
    Dock_SingleSizeShowView = new QDockWidget(this);
    Dock_SingleSizeShowView->setObjectName("SizeInfo");
    Dock_SingleSizeShowView->setWindowTitle("尺寸信息");
    Dock_SingleSizeShowView->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_SingleSizeShow = new SingleSizeShowWidget(Qt::Horizontal, Qt::Horizontal, Dock_SingleSizeShowView);
    Dock_SingleSizeShowView->setWidget(m_SingleSizeShow);
    Dock_SingleSizeShowView->setFeatures(QDockWidget::DockWidgetFloatable);
}

void MainWindow::Create_CameraShow()
{
    Dock_CameraShow = new QDockWidget(this);
    Dock_CameraShow->setObjectName("CameraShow");
    Dock_CameraShow->setWindowTitle("相机");
    Dock_CameraShow->setAllowedAreas(Qt::AllDockWidgetAreas);
    Camera_widget = new CamerasWidget(Dock_CameraShow, Cameras, Global::camDefineNum);
    Dock_CameraShow->setWidget(Camera_widget);
    Dock_CameraShow->setFeatures(QDockWidget::DockWidgetFloatable);

}

void MainWindow::slot_CloseSystem()
{
    close();
    qApp->exit(0);
}

void MainWindow::slot_ShowSystemSettingForm()
{
    if (SystemSettings == NULL) {
        SystemSettings = new SystemSettingForm(*sig_comm, *JsonRecipe);
        connect(SystemSettings, SIGNAL(sig_Deliver_NewRecipeName2mainWindow(QString)), this, SLOT(slot_ChangeRecipe(QString)));
        connect(this, SIGNAL(sig_DeliverNewRecipe(JsonParse2Map*)), SystemSettings, SLOT(slot_JsonRecipe_Changed(JsonParse2Map*)));
    }
    SystemSettings->setWindowFlags(Qt::Window);
    SystemSettings->setWindowModality(Qt::ApplicationModal); //点击之后不可对其它窗体操作
    SystemSettings->setWindowFlags(SystemSettings->windowFlags() & ~Qt::WindowMinMaxButtonsHint);//设置窗口无最小化按钮
    SystemSettings->setWindowFlags(SystemSettings->windowFlags() & ~Qt::WindowMaximizeButtonHint);//设置窗口无全屏按钮
    SystemSettings->setWindowIcon(QIcon(":/toolbar/icons/setup.ico"));
    SystemSettings->setWindowTitle("系统设置");
    SystemSettings->show();
}

void MainWindow::slot_ActionStart()
{
    if (SystemStatus == 0) {
        log_singleton::Write_Log("开始检测", Log_Level::General);
        SystemStatus = 1;
        emit sig_StartButton2CameraStart();
        m_pStart->setEnabled(false);
        m_pStop->setEnabled(true);
        m_pExit->setEnabled(false);
        m_pSettings->setEnabled(false);
        QString CurrentRecipeNameLog = "获得当前工单: " + Global::CurrentRecipe;
        QString SystemNameLog = "获得当前项目名: " + Global::SystemName;
        QString RecipePath = "Recipes/" + Global::CurrentRecipe + ".json";
        JsonParse2Map *JsonRecipe = new JsonParse2Map(RecipePath);
        JsonRecipe->getParameter("相机0.帧次",Global::FramesPerTri);
        Global::SystemStatus = 1; //系统运行
    }
}

void MainWindow::slot_ActionStop()
{
    if (SystemStatus == 1) {
        log_singleton::Write_Log("停止检测", Log_Level::General);
        SystemStatus = 0;
        emit sig_StopButton2CameraStop();
        m_pStart->setEnabled(true);
        m_pStop->setEnabled(false);
        m_pExit->setEnabled(true);
        m_pSettings->setEnabled(true);
        Global::SystemStatus = 0; //系统停止
    }
}

void MainWindow::slot_CameraShow()
{
    Dock_CameraShow->raise();
}

void MainWindow::slot_RunningInfo()
{
    if (!log_singleton::widget0->isVisible())
        log_singleton::widget0->setVisible(true);
    else
        log_singleton::widget0->setVisible(false);
}

void MainWindow::slot_DB()
{
    //    Database->start_connect();
//    DB = new QProcess(this);
//    DB->start("JianboDB/Glass_DB_Model.exe");
}

void MainWindow::stopThread()
{
    Detectworker->hasStopThread.store(false);
    Tileworker->hasStopThread.store(false);
    SigCtrlData->hasStopThread.store(false);
}

void MainWindow::slot_ChangeRecipe(QString RecipeName)
{
    QString recipelog = "获得新工单名: " + RecipeName;

    log_singleton::Write_Log(recipelog, Log_Level::General);
    QString NewFilepath = "Recipes/" + RecipeName + ".json";
    JsonRecipe->ChangeParams(NewFilepath);
    log_singleton::Write_Log("新工单已被选择", Log_Level::General);
    Global::CurrentRecipe = RecipeName;
    Global::SaveXml();
    emit sig_DeliverNewRecipe(JsonRecipe);
    emit sig_FlawWidgetChange();

}

void MainWindow::slot_updatePreGlassRes(bool res)
{
    if (res) {
        lineEdit1->setText("OK");
        lineEdit1->setStyleSheet("color: black;border: none; background-color: green; border-radius: 20px;");
    } else {
        lineEdit1->setText("NG");
        lineEdit1->setStyleSheet("color: black;border: none; background-color: red; border-radius: 20px;");
    }
}

void MainWindow::slot_updateSortGlassRes(SummaryResult Res)
{
    if (Res.currentOKorNG) {
        lineEdit2->setText("OK");
        lineEdit2->setStyleSheet("color: black;border: none; background-color: green; border-radius: 20px;");
    } else {
        lineEdit2->setText("NG");
        lineEdit2->setStyleSheet("color: black;border: none; background-color: red; border-radius: 20px;");
    }
}

void MainWindow::slot_clearPreSortGlassInfo()
{
    lineEdit1->setText("");
    lineEdit2->setText("");
    lineEdit1->setStyleSheet( "color: black;border: none; background-color: #FFFFFF; border-radius: 20px;");
    lineEdit2->setStyleSheet("color: black;border: none; background-color: #FFFFFF; border-radius: 20px;");
}

int OriginNum = 0;
int pos_test = 0;
GLASSINFO* newInfo = new GLASSINFO();
QList<FlawPoint>* FlawPointList = new QList<FlawPoint>();
QList<QRectF>* rectangles = new QList<QRectF>();


void MainWindow::slot_SendPoint(const FlawPoint &flawpoint)
{
    if(m_GlassStatisticTable->tableWidget->item(0, 0) != nullptr) {
        m_SingleFlawShow->slot_RecieveID(flawpoint.DefectJsonFullPath, flawpoint.glassid);      //更新缺陷小图
        m_SingleFlawShow->PickerCheckData(flawpoint);                                           //更新缺陷小图
//        m_SingleSizeShow->slot_RecieveID(flawpoint.HoleJsonFullPath,flawpoint.glassid);         //更新尺寸信息
//        m_SingleSizeShow->showSizeDiagramImage(flawpoint.HoleJsonFullPath,flawpoint.glassid);   //更新尺寸轮廓图
        Dock_SingleFlawShowView->raise();
    }
}

void MainWindow::slot_test()
{
    Dock_SingleFlawShowView->raise();
}

void MainWindow::slot_Offline()
{
    try {
      //获取选择的目录路径
      _offlineSelectedDir = QFileDialog::getExistingDirectory(this,"选择一个目录","./",QFileDialog::ShowDirsOnly);
      //若目录路径不为空
      if (!_offlineSelectedDir.isEmpty()) {
          //将路径中的斜杠替换为反斜杠
          _offlineSelectedDir = _offlineSelectedDir.replace(QRegExp("\\"), "/");
          qDebug()<<"_selectedDir =" <<_offlineSelectedDir;
          QDir dir(_offlineSelectedDir);
          QFileInfoList fileList = dir.entryInfoList(QStringList() << "*.jpg");
          bool isJpg = false;
          //遍历容器
          for(auto fileInfo:fileList) {
             //输出文件名包含后缀
             qDebug() << fileInfo.fileName();
             //输出文件的完整路径名
             qDebug() << fileInfo.absoluteFilePath();
             isJpg = true;
          }
          Global::isJpg = isJpg;  //是不是jpg后缀
          Global::offlineFullPath = _offlineSelectedDir;
          Global::isOffline = true; //等待处理线程触发
      }
   } catch(...) {
      qDebug()<<"slot_ButtonExportClicked() error";
   }
}


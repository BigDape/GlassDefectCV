#include "mainwindow.h"
#include "QLabel"
#include "math.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProgressDialog>
#include <QString>
#include <fstream>
#include <QTextStream>
#include <QFileDialog>
#include <iostream>
#include <stdlib.h>
#include <QThreadPool>
#include <thread>
#include <QLineEdit>
#include <Qwt/qwt_picker_machine.h>
#include <Qwt/qwt_legend_label.h>
#include <Qwt/qwt_plot_shapeitem.h>
#include <Qwt/qwt_plot_marker.h>
#include <Qwt/qwt_symbol.h>
#include <Qwt/qwt_legend.h>
#include <Qwt/qwt_plot_curve.h>
#include "jsoncpp.h"

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
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

//    MainWindow::InitRegisterMetaType();
    MainWindow::InitToolBar();
//    MainWindow::InitGlassStaticTableWidget();
//    MainWindow::InitSingleFlawTableWidget();
//    MainWindow::InitSingleSizeTableWidget();
//    MainWindow::InitCameraSettingTableWidget();
//    MainWindow::InitRealTimeFlawTableWidget();
//    MainWindow::InitFlawShowWidget();
     MainWindow::InitSummaryTableWidget();
//    MainWindow::InitLogInformation();

    this->showMaximized();
    QWidget::showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitRegisterMetaType()
{
    //注册自定义类型，供connect调用
//    qRegisterMetaType<GlassDataBaseInfo>("GlassDataBaseInfo");  //注册类型，否则不能调用
//    qRegisterMetaType<QList<FlawPoint>>("QList<FlawPoint>");    //注册类型，否则不能调用
//    qRegisterMetaType<SummaryResult>("SummaryResult");          //注册类型，否则不能调用
}

void MainWindow::InitToolBar()
{
    // 退出按钮
    m_pExit = new QAction("&退出", this);
    m_pExit->setShortcut(QKeySequence::Quit);
    m_pExit->setToolTip(tr("Exit System."));
    m_pExit->setIcon(QIcon(":/toolbar/icons/exit.png"));
    ui->toolBar->addAction(m_pExit);
    // 设置按钮
    m_pSettings = new QAction("&设置", this);
    m_pSettings->setToolTip(tr("Device Settings."));
    m_pSettings->setIcon(QIcon(":/toolbar/icons/setup.png"));
    ui->toolBar->addAction(m_pSettings);
    // 开始按钮
    m_pStart = new QAction("&开始", this);
    m_pStart->setToolTip(tr("Start."));
    m_pStart->setIcon(QIcon(":/toolbar/icons/start_icon.png"));
    ui->toolBar->addAction(m_pStart);
    // 停止按钮
    m_pStop = new QAction("&停止", this);
    m_pStop->setToolTip(tr("Stop."));
    m_pStop->setIcon(QIcon(":/toolbar/icons/Stop.png"));
    ui->toolBar->addAction(m_pStop);
    m_pStop->setEnabled(false);
    // 数据查询按钮
    m_pDB = new QAction("&数据查询", this);
    m_pDB->setShortcut(QKeySequence::Quit);
    m_pDB->setToolTip(tr("Database."));
    m_pDB->setIcon(QIcon(":/toolbar/icons/analysis.png"));
    ui->toolBar->addAction(m_pDB);
    // 离线模式
    m_offline = new QAction("&离线模式", this);
    m_offline->setToolTip(tr("Offline."));
    m_offline->setIcon(QIcon(":/toolbar/icons/switch.png"));
    ui->toolBar->addAction(m_offline);

    ui->toolBar->setIconSize(QSize(40, 40));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->toggleViewAction()->setEnabled(false);
    ui->toolBar->setFloatable(false);
    ui->toolBar->setMovable(false);
    //
    // 标题栏
    //
    connect(m_pExit, SIGNAL(triggered()), this, SLOT(slot_CloseSystem()));                  //点击退出响应事件
    connect(m_pSettings, SIGNAL(triggered()), this,SLOT(slot_ShowSystemSettingForm()));     //点击设置响应事件
    connect(m_pStart, SIGNAL(triggered()), this, SLOT(slot_ActionStart()));                 //点击开始响应事件
    connect(m_pStop, SIGNAL(triggered()), this, SLOT(slot_ActionStop()));                   //点击停止响应事件
    connect(m_pDB, SIGNAL(triggered()), this, SLOT(slot_DataSearch()));                     //点击数据查询响应事件
    connect(m_offline, SIGNAL(triggered()), this, SLOT(slot_Offline()));                    //点击离线模式响应事件
}


void MainWindow::slot_CloseSystem()
{
    // todo:关闭系统之前需要进行资源回收
    close();
    qApp->exit(0);
}

void MainWindow::slot_ShowSystemSettingForm()
{
    if(m_lightControl == nullptr) {
        m_lightControl = std::make_shared<LightControl>(this);//设置窗口
    }
    m_lightControl->setWindowFlags(Qt::Window);
    m_lightControl->setWindowModality(Qt::ApplicationModal); //点击之后不可对其它窗体操作
    m_lightControl->setWindowFlags(m_lightControl->windowFlags() & ~Qt::WindowMinMaxButtonsHint);//设置窗口无最小化按钮
    m_lightControl->setWindowFlags(m_lightControl->windowFlags() & ~Qt::WindowMaximizeButtonHint);//设置窗口无全屏按钮
    m_lightControl->setWindowIcon(QIcon(":/toolbar/icons/setup.ico"));
    m_lightControl->setWindowTitle("系统设置");
    m_lightControl->show();
}

void MainWindow::slot_ActionStart()
{
    //
    // 进行开始流程，打开相机
    // 设置界面上相关按钮的亮和灰
    //
}

void MainWindow::slot_ActionStop()
{
    //
    // 停止采集
    //
}


void MainWindow::slot_DataSearch()
{
    //
    // 进行数据查询
    //
}

void MainWindow::stopThread()
{
//    Detectworker->hasStopThread.store(false);
//    Tileworker->hasStopThread.store(false);
//    SigCtrlData->hasStopThread.store(false);
}

void MainWindow::slot_Offline()
{
    //
    // todo: 从最深层次加载图片
    //
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
          //遍历容器
          for(auto fileInfo:fileList) {
             //输出文件名包含后缀
             qDebug() << fileInfo.fileName();
             //输出文件的完整路径名
             qDebug() << fileInfo.absoluteFilePath();
          }
          PARAM.offlineFullPath = _offlineSelectedDir;
          PARAM.isOffline = true; //等待处理线程触发
      }
   } catch(...) {
      qDebug()<<"slot_ButtonExportClicked() error";
   }
}

void MainWindow::InitGlassStaticTableWidget()
{
    //
    // 设置表头
    //
    QStringList headerLabels = {tr("ID"),tr("OK/NG"),tr("sizeOK/NG"),tr("length"),tr("width"),tr("diagonal1"), tr("diagonal2"), tr("defectNumber"),
                               tr("defectOK/NG"),tr("huashan"),tr("qipao"),tr("jieshi"),tr("benbian"),tr("zanwu"),tr("liewen"),tr("qita")};
    ui->glassstatictablewidget->setColumnCount(headerLabels.size());
    ui->glassstatictablewidget->setHorizontalHeaderLabels(headerLabels);

    ui->glassstatictablewidget->setColumnWidth(0, 100);
    ui->glassstatictablewidget->setColumnWidth(1, 200);
    ui->glassstatictablewidget->setColumnWidth(2, 100);
    ui->glassstatictablewidget->setColumnWidth(3, 100);
    ui->glassstatictablewidget->setColumnWidth(4, 100);
    ui->glassstatictablewidget->setColumnWidth(5, 100);
    ui->glassstatictablewidget->setColumnWidth(6, 100);
    ui->glassstatictablewidget->setColumnWidth(7, 100);
    ui->glassstatictablewidget->setColumnWidth(8, 100);
    ui->glassstatictablewidget->setColumnWidth(9, 100);
    ui->glassstatictablewidget->setColumnWidth(10, 100);
    ui->glassstatictablewidget->setColumnWidth(11, 100);
    ui->glassstatictablewidget->setColumnWidth(12, 100);
    ui->glassstatictablewidget->setColumnWidth(13, 100);
    ui->glassstatictablewidget->setColumnWidth(14, 100);
    ui->glassstatictablewidget->setColumnWidth(15, 100);
    ui->glassstatictablewidget->setColumnWidth(16, 100);

    connect(this,SIGNAL(sign_GlassStaticTableInsertRowData(GlassDataBaseInfo)), this, SLOT(slot_GlassStaticTableInsertRowData(GlassDataBaseInfo)));
}

void MainWindow::slot_GlassStaticTableInsertRowData(GlassDataBaseInfo info)
{
    QTableWidgetItem *itemID = ui->glassstatictablewidget->item(0, 0);
    //
    // 同一块玻璃的多帧图片插入到表格的同一行
    //
    if (itemID == NULL) {
        if(itemID->text().toInt() != info.id)
            ui->glassstatictablewidget->insertRow(0);
    } else {
        ui->glassstatictablewidget->insertRow(0);
    }
    //ID
    QTableWidgetItem* id = new QTableWidgetItem(QString::number(info.id));
    id->setTextAlignment(Qt::AlignCenter);
    id->setFlags(id->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 0, id);
    //时间
    QTableWidgetItem* time = new QTableWidgetItem(info.time);
    time->setTextAlignment(Qt::AlignCenter);
    time->setFlags(time->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 1, time);
    //OK/NG
    QTableWidgetItem* isok = new QTableWidgetItem(info.OKorNG);
    isok->setTextAlignment(Qt::AlignCenter);
    isok->setFlags(isok->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 2, isok);
    //尺寸OK/NG
    QTableWidgetItem* issizeok = new QTableWidgetItem(info.sizeOKorNG);
    issizeok->setTextAlignment(Qt::AlignCenter);
    issizeok->setFlags(issizeok->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 3, issizeok);
    //长度
    QTableWidgetItem* length = new QTableWidgetItem(QString::number(info.width,'f', 2));//??这里为啥要对调
    length->setTextAlignment(Qt::AlignCenter);
    length->setFlags(length->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 4, length);
    //宽度
    QTableWidgetItem* width = new QTableWidgetItem(QString::number(info.length,'f', 2));//??这里为啥要对调
    width->setTextAlignment(Qt::AlignCenter);
    width->setFlags(width->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 5, width);
    //对角线1
    info.duijiaoxian1 = sqrt(pow(info.length,2) + pow(info.width,2));//对角线，todo
    QTableWidgetItem* diagonal1 = new QTableWidgetItem(QString::number(info.duijiaoxian1,'f', 2));
    diagonal1->setTextAlignment(Qt::AlignCenter);
    diagonal1->setFlags(diagonal1->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 6, diagonal1);
    //对角线2
    info.duijiaoxian2 = sqrt(pow(info.length,2) + pow(info.width,2));//对角线，todo
    QTableWidgetItem* diagonal2 = new QTableWidgetItem(QString::number(info.duijiaoxian2,'f', 2));
    diagonal2->setTextAlignment(Qt::AlignCenter);
    diagonal2->setFlags(diagonal2->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 7, diagonal2);
    //缺陷数量
    QTableWidgetItem* flawcount = new QTableWidgetItem(QString::number(info.defectNumber));
    flawcount->setTextAlignment(Qt::AlignCenter);
    flawcount->setFlags(flawcount->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 8, flawcount);
    //缺陷OK/NG
    QTableWidgetItem* isflawok = new QTableWidgetItem(info.defectOKorNG);
    isflawok->setTextAlignment(Qt::AlignCenter);
    isflawok->setFlags(isflawok->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 9, isflawok);
    //划伤
    QTableWidgetItem* flaw1 = new QTableWidgetItem(QString::number(info.huashanNumber));
    flaw1->setTextAlignment(Qt::AlignCenter);
    flaw1->setFlags(flaw1->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 10, flaw1);
    //气泡
    QTableWidgetItem* flaw2 = new QTableWidgetItem(QString::number(info.qipaoNumber));
    flaw2->setTextAlignment(Qt::AlignCenter);
    flaw2->setFlags(flaw2->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 11, flaw2);
    //结石
    QTableWidgetItem* flaw7 = new QTableWidgetItem(QString::number(info.jieshiNumber));
    flaw7->setTextAlignment(Qt::AlignCenter);
    flaw7->setFlags(flaw7->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 12, flaw7);
    //崩边
    QTableWidgetItem* flaw3 = new QTableWidgetItem(QString::number(info.benbianNumber));
    flaw3->setTextAlignment(Qt::AlignCenter);
    flaw3->setFlags(flaw3->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 13, flaw3);
    //脏污
    QTableWidgetItem* flaw4 = new QTableWidgetItem(QString::number(info.zanwuNumber));
    flaw4->setTextAlignment(Qt::AlignCenter);
    flaw4->setFlags(flaw4->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 14, flaw4);
    //裂纹
    QTableWidgetItem* flaw5 = new QTableWidgetItem(QString::number(info.liewenNumber));
    flaw5->setTextAlignment(Qt::AlignCenter);
    flaw5->setFlags(flaw5->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 15, flaw5);
    //其他
    QTableWidgetItem* flaw6 = new QTableWidgetItem(QString::number(info.qitaNumber));
    flaw6->setTextAlignment(Qt::AlignCenter);
    flaw6->setFlags(flaw6->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 16, flaw6);

    // 设置表格内容居中显示
    for (int i = 0; i < ui->glassstatictablewidget->columnCount(); ++i) {
        ui->glassstatictablewidget->horizontalHeaderItem(i)->setTextAlignment(Qt::AlignCenter);
    }
    ui->glassstatictablewidget->verticalHeader()->setVisible(false); // 隐藏行号
}

void MainWindow::InitSingleFlawTableWidget()
{
    QGraphicsScene* scene=new QGraphicsScene();
    loadedPixmapItem = new MyGraphicsItem();
    scene->addItem(loadedPixmapItem);
    ui->graphicsView->setScene(scene);

    QGraphicsScene* scene2=new QGraphicsScene();
    loadedPixmapItem2 = new MyGraphicsItem();
    scene2->addItem(loadedPixmapItem2);
    ui->graphicsView_2->setScene(scene2);

    QGraphicsScene* scene3=new QGraphicsScene();
    loadedPixmapItem3 = new MyGraphicsItem();
    scene3->addItem(loadedPixmapItem3);
    ui->graphicsView_3->setScene(scene3);

    ui->SingleFlawtableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SingleFlawtableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->SingleFlawtableWidget->verticalHeader()->setVisible(false);
    ui->SingleFlawtableWidget->setColumnWidth(0, 90);

    for (int row = 0; row < ui->SingleFlawtableWidget->rowCount(); ++row) {
      for (int col = 0; col < ui->SingleFlawtableWidget->columnCount(); ++col) {
        QTableWidgetItem* item = ui->SingleFlawtableWidget->item(row, col);
        if (item) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
      }
    }
}

void MainWindow::slot_SingleFlawUpdateTableData(GlassDefectInfo info)
{
    if(info.defectdatas.size() > 0 && (int)info.defectdatas.size() == info.defectCount) {
        ui->SingleFlawtableWidget->setRowCount(info.defectdatas.size());
        ui->SingleFlawtableWidget->setColumnCount(9);
        for (int i = 0; i < info.defectCount; i++) {
            //序号
            QString DefectID = QString::number(info.defectdatas[i].defectId);
            QTableWidgetItem* item0 = new QTableWidgetItem(DefectID);
            item0->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 0, item0);
            //时间
            QString Time = info.defectdatas[i].time;
            QTableWidgetItem* item1 = new QTableWidgetItem(Time);
            item1->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 1, item1);
            //类型
            QString DefectType = info.defectdatas[i].defectType;
            QTableWidgetItem* item2 = new QTableWidgetItem(DefectType);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i , 2, item2);
            //等级
            QString DetectLeve = info.defectdatas[i].defectLevel;
            QTableWidgetItem* item3 = new QTableWidgetItem(DetectLeve);
            item3->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 3, item3);
            //坐标X
            QString X = QString::number(info.defectdatas[i].x,'f', 2);
            QTableWidgetItem* item4 = new QTableWidgetItem(X);
            item4->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 4, item4);
            //坐标Y
            QString Y = QString::number(info.defectdatas[i].y,'f', 2);
            QTableWidgetItem* item5 = new QTableWidgetItem(Y);
            item5->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 5, item5);
            //长
            QString Lenth = QString::number(info.defectdatas[i].length,'f', 2);
            QTableWidgetItem* item6 = new QTableWidgetItem(Lenth);
            item6->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 6, item6);
            //宽
            QString Width = QString::number(info.defectdatas[i].width,'f', 2);
            QTableWidgetItem* item7 = new QTableWidgetItem(Width);
            item7->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 7, item7);
            //区域
            QString Area = QString::number(info.defectdatas[i].area,'f', 2);
            QTableWidgetItem* item8 = new QTableWidgetItem(Area);
            item8->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 8, item8);
            //插入坐标到map中，用于追踪缺陷
            PARAM.rowMapXY[info.defectdatas[i].defectId] = std::make_pair(X,Y);
        }
        //
        // 更新缺陷小图
        //
        QImage img1(info.defectdatas[0].imagePath1);
        QImage img2(info.defectdatas[0].imagePath2);
        QImage img3(info.defectdatas[0].imagePath3);

        loadedPixmapItem->loadImage(img1);
        int nwidth = ui->graphicsView->width();
        int nheight = ui->graphicsView->height();
        loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
        ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));

        loadedPixmapItem2->loadImage(img2);
        int nwidth2 = ui->graphicsView_2->width();
        int nheight2 = ui->graphicsView_2->height();
        loadedPixmapItem2->setQGraphicsViewWH(nwidth, nheight);
        ui->graphicsView_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));

        loadedPixmapItem3->loadImage(img3);
        int nwidth3 = ui->graphicsView_3->width();
        int nheight3 = ui->graphicsView_3->height();
        loadedPixmapItem3->setQGraphicsViewWH(nwidth, nheight);
        ui->graphicsView_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
    }
}

void MainWindow::slot_SingleFlawTrack(QTableWidgetItem* item)
{
    if (item) {
      int row = item->row();
      QString x,y;
      if (PARAM.rowMapXY.count(row) != 0) {
          //获取到缺陷的x,y
          y = PARAM.rowMapXY[row].first;
          x = PARAM.rowMapXY[row].second;
         if(PARAM.m_plot != NULL) {
             double xValue = x.toDouble();
             double yValue = y.toDouble();
             PARAM.m_plot->detachItems(QwtPlotItem::Rtti_PlotShape);//清理之前追踪图框
             QwtPlotShapeItem* trackItem = new QwtPlotShapeItem;
             trackItem->setPen(QPen(Qt::red));
             QRectF trackRect(xValue-20, yValue-20, 40, 40);
             trackItem->setRect(trackRect);
             trackItem->attach(PARAM.m_plot);
             PARAM.m_plot->replot();
         }
      }
    }
}

void MainWindow::slot_SingleSizeUpdataTableData(GlassSizeInfo info)
{
    if(info.sizedatas.size() > 0 && (int)info.sizedatas.size() == info.sizeCount) {
        ui->singleSizeTableWidget->setRowCount(info.sizeCount);
        for (int i = 0; i < info.sizeCount; i++) {
            // 序号
            QString HolesID = QString::number(info.sizedatas[i].sizeID);
            QTableWidgetItem* item0 = new QTableWidgetItem(HolesID);
            item0->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 0, item0);
            // 时间
            QString Time = info.sizedatas[i].time;
            QTableWidgetItem* item1 = new QTableWidgetItem(Time);
            item1->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 1, item1);
            // 类型
            QString Type = info.sizedatas[i].sizeType;
            QTableWidgetItem* item2 = new QTableWidgetItem(Type);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 2, item2);
            //孔洞
            QString HolesLeve = info.sizedatas[i].sizeLevel;
            QTableWidgetItem* item3 = new QTableWidgetItem(HolesLeve);
            item3->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 3, item3);
            // 长X
            QString HolesHeight = QString::number(info.sizedatas[i].lengthX,'f', 2);
            QTableWidgetItem* item4 = new QTableWidgetItem(HolesHeight);
            item4->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 4, item4);
            // 宽Y
            QString HolesWidth = QString::number(info.sizedatas[i].widthY,'f', 2);
            QTableWidgetItem* item5 = new QTableWidgetItem(HolesWidth);
            item5->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 5, item5);
            // 边距X
            QString DistanceHorizontal = QString::number(info.sizedatas[i].marginsX,'f', 2);
            QTableWidgetItem* item6 = new QTableWidgetItem(DistanceHorizontal);
            item6->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 6, item6);
            // 边距Y
            QString DistanceVertical = QString::number(info.sizedatas[i].marginsY,'f', 2);
            QTableWidgetItem* item7 = new QTableWidgetItem(DistanceVertical);
            item7->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 7, item7);
        }
        //显示孔洞小图
        if (nullptr != ui->singleSizeTableWidget->item(0, 0)) {
            QString ImageHolesPath = info.sizedatas[0].imagePath;
            qDebug() << "ImageHolesPath = " << ImageHolesPath;
            QImage img2(ImageHolesPath);
            loadedPixmapItem5->loadImage(img2);
            int nwidth = ui->graphicsView_2->width();
            int nheight = ui->graphicsView_2->height();
            loadedPixmapItem5->setQGraphicsViewWH(nwidth, nheight);
            ui->graphicsView_Field->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
        }
        //显示轮廓图
        if(loadedPixmapItem4 != nullptr){
            QString ImageHolesLinePath = info.OutLinePath;
            qDebug() << "ImageHolesLinePath = " << ImageHolesLinePath;
            QImage img1(ImageHolesLinePath);
            loadedPixmapItem4->loadImage(img1);
            int nwidth = ui->graphicsView->width();
            int nheight = ui->graphicsView->height();
            loadedPixmapItem4->setQGraphicsViewWH(nwidth, nheight);
            ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
        }
    }
}

void MainWindow::InitSingleSizeTableWidget()
{
    QGraphicsScene* scene = new QGraphicsScene();
    loadedPixmapItem4 = new MyGraphicsItem();
    ui->graphicsView_outLine->setScene(scene);
    scene->addItem(loadedPixmapItem);

    QGraphicsScene* scene2=new QGraphicsScene();
    loadedPixmapItem5 = new MyGraphicsItem();
    ui->graphicsView_Field->setScene(scene2);
    scene2->addItem(loadedPixmapItem2);

    ui->singleSizeTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->singleSizeTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->singleSizeTableWidget->verticalHeader()->setVisible(false);
    ui->singleSizeTableWidget->setColumnWidth(0, 90);

    for (int row = 0; row < ui->singleSizeTableWidget->rowCount(); ++row) {
      for (int col = 0; col < ui->singleSizeTableWidget->columnCount(); ++col) {
        QTableWidgetItem* item = ui->singleSizeTableWidget->item(row, col);
        if (item) {
          item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
      }
    }
}

void MainWindow::InitCameraSettingTableWidget()
{
    m_cameraslayout = new CamerasLayout(ui->tabWidget_2);
    std::vector<DushenCameraArgs> args;
    //todo:给参数赋值
    m_cameraslayout->InitCameras(args);
}

void MainWindow::InitRealTimeFlawTableWidget()
{
    QGraphicsScene* scene=new QGraphicsScene();
    loadedPixmapItem6 = new MyGraphicsItem();
    scene->addItem(loadedPixmapItem6);
    ui->graphicsView_Field1->setScene(scene);

    QGraphicsScene* scene2=new QGraphicsScene();
    loadedPixmapItem7= new MyGraphicsItem();
    scene2->addItem(loadedPixmapItem7);
    ui->graphicsView_Field2->setScene(scene2);

    QGraphicsScene* scene3=new QGraphicsScene();
    loadedPixmapItem8 = new MyGraphicsItem();
    scene3->addItem(loadedPixmapItem8);
    ui->graphicsView_Field3->setScene(scene3);
}

void MainWindow::slot_RealTimeFlawUpdateTableData(GlassDefect info)
{
    //
    // 更新缺陷小图
    //
    QImage img1(info.imagePath1);
    QImage img2(info.imagePath2);
    QImage img3(info.imagePath3);

    loadedPixmapItem6->loadImage(img1);
    int nwidth = ui->graphicsView_Field1->width();
    int nheight = ui->graphicsView_Field1->height();
    loadedPixmapItem6->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_Field1->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));

    loadedPixmapItem2->loadImage(img2);
    int nwidth2 = ui->graphicsView_Field2->width();
    int nheight2 = ui->graphicsView_Field2->height();
    loadedPixmapItem2->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_Field2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));

    loadedPixmapItem3->loadImage(img3);
    int nwidth3 = ui->graphicsView_Field3->width();
    int nheight3 = ui->graphicsView_Field3->height();
    loadedPixmapItem3->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_Field3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));

    //
    // 更新数据
    //
    ui->defectID1LB->setText(QString::number(info.defectId));
    ui->defectID2LB->setText(QString::number(info.defectId));
    ui->defectID3LB->setText(QString::number(info.defectId));

    ui->defectTime1LB->setText(info.time);
    ui->defectTime2LB->setText(info.time);
    ui->defectTime3LB->setText(info.time);

    ui->defectType1LB->setText(info.defectType);
    ui->defectType2LB->setText(info.defectType);
    ui->defectType3LB->setText(info.defectType);

    ui->defectLevel1LB->setText(info.defectLevel);
    ui->defectLevel2LB->setText(info.defectLevel);
    ui->defectLevel3LB->setText(info.defectLevel);

    ui->defectX1LB->setText(QString::number(info.x));
    ui->defectX2LB->setText(QString::number(info.x));
    ui->defectX3LB->setText(QString::number(info.x));

    ui->defectY1LB->setText(QString::number(info.y));
    ui->defectY2LB->setText(QString::number(info.y));
    ui->defectY3LB->setText(QString::number(info.y));

    ui->defectLength1LB->setText(QString::number(info.length));
    ui->defectLength2LB->setText(QString::number(info.length));
    ui->defectLength3LB->setText(QString::number(info.length));

    ui->defectWidth1LB->setText(QString::number(info.width));
    ui->defectWidth2LB->setText(QString::number(info.width));
    ui->defectWidth3LB->setText(QString::number(info.width));

    ui->defectArea1LB->setText(QString::number(info.area));
    ui->defectArea2LB->setText(QString::number(info.area));
    ui->defectArea3LB->setText(QString::number(info.area));
}

void MainWindow::InitFlawShowWidget()
{
    PARAM.m_plot = ui->qwtPlot;
    plotpicker = new QwtPlotPicker(QwtPlot::xBottom,QwtPlot::yLeft,QwtPlotPicker::CrossRubberBand,QwtPicker::AlwaysOn,ui->qwtPlot->canvas());
    plotpicker->setTrackerMode(QwtPicker::ActiveOnly);
    plotpicker->setStateMachine(new QwtPickerDragPointMachine);
    connect(plotpicker,SIGNAL(appended(const QPointF&)),this,SLOT(slot_PlotPicker(QPointF)));//鼠标点击坐标发生的动作

    QString RecipePath = "Recipes/" + PARAM.CurrentRecipe + ".json";  //配置文件地址
    WorkOrder order;
//    Jsoncpp::GetInstance()->readWorkOrderFromJson(RecipePath, order);
    double Maxlength = order.DMParam.length * 1.1;
    double Maxwidth = order.DMParam.width * 1.1;
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0, Maxwidth);
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0, Maxlength);
}

void MainWindow::slot_DrawGlassAndFlaw()
{
    ui->qwtPlot->detachItems();
//    drawGlass(w, h);
//    drawFlaw(&FlawPointList);
    ui->qwtPlot->replot();
}

void MainWindow::drawGlass(double x_length, double y_length)
{
#if false
    QwtPlotShapeItem* rectangleItem = new QwtPlotShapeItem;
    rectangleItem->setPen(QPen(Qt::black));
    rectangleItem->setBrush(QBrush(Qt::lightGray));
    QRectF rectangleRect(0, 0, x_length, y_length);

    rectangleItem->setRect(rectangleRect);
    rectangleItem->attach(m_plot);
#endif
//    int count = Global::courtourMapXY.size();
//    for (int i =0; i < count; ++i) {
//        QwtPlotMarker* m = new QwtPlotMarker();
//        m->setSymbol(new QwtSymbol(QwtSymbol::Rect, QBrush(Qt::green), QPen(Qt::green), QSize(4, 4)));
//        qDebug()<<"drawGlass ("<<i<<") =>{x:"<<Global::courtourMapXY[i].x<<",y="<<Global::courtourMapXY[i].y<<"}";
//        m->setValue(Global::courtourMapXY[i].x.toDouble(), -Global::courtourMapXY[i].y.toDouble());//y值都为负值
//        m->attach(m_plot);
//    }
}

void MainWindow::drawFlaw(QList<FlawPoint>* m_FlawPointList)
{
    MainWindow::drawLegend();
    int ListLength = m_FlawPointList->count();
    for (int i = 0; i < ListLength; i++) {
        QwtPlotMarker* maker = new QwtPlotMarker();
        switch (m_FlawPointList->at(i).FlawType) {
        case 1:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Cross, QBrush(Qt::blue), QPen(Qt::blue), QSize(10, 10)));
            break;
        case 2:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Rect, QBrush(Qt::red), QPen(Qt::red), QSize(10, 10)));
            break;
        case 3:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Star1, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(10, 10)));
            break;
        case 4:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Triangle, QBrush(Qt::blue), QPen(Qt::blue), QSize(10, 10)));
            break;
        case 5:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Diamond, QBrush(Qt::red), QPen(Qt::red), QSize(10, 10)));
            break;
        case 6:
            maker->setSymbol(new QwtSymbol(QwtSymbol::XCross, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(10, 10)));
            break;
        case 7:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Star2, QBrush(Qt::blue),QPen(Qt::blue), QSize(10, 10)));
            break;
        }
        maker->attach(ui->qwtPlot);
        maker->setValue(QPointF(m_FlawPointList->at(i).x, m_FlawPointList->at(i).y));
    }
}

void MainWindow::reDrawFlaw(QList<FlawPoint>* m_FlawPointList)
{
    ui->qwtPlot->detachItems(QwtPlotItem::Rtti_PlotMarker);//清除画布上的所有
    ui->qwtPlot->replot();
    //画轮廓
    for (int i =0; i < (int)PARAM.courtourMapXY.size(); ++i) {
        QwtPlotMarker* m = new QwtPlotMarker();
        m->setSymbol(new QwtSymbol(QwtSymbol::Rect, QBrush(Qt::green), QPen(Qt::green), QSize(4, 4)));
        m->setValue(PARAM.courtourMapXY[i].x.toDouble(), -PARAM.courtourMapXY[i].y.toDouble());//y值都为负值
        m->attach(ui->qwtPlot);
    }
    int ListLength = m_FlawPointList->count();
    for (int i = 0; i < ListLength; i++) {
        QwtPlotMarker* maker = new QwtPlotMarker();
        int tempType = m_FlawPointList->at(i).FlawType;
        if(replotMap.count(tempType -1) != 0 && replotMap[tempType -1] == true) { //缺陷类别能找到，且被点击为了true
            switch (tempType) {
            case 1:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Cross, QBrush(Qt::blue), QPen(Qt::blue), QSize(10, 10)));
                break;
            case 2:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Rect, QBrush(Qt::red), QPen(Qt::red), QSize(10, 10)));
                break;
            case 3:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Star1, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(10, 10)));
                break;
            case 4:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Triangle, QBrush(Qt::blue), QPen(Qt::blue), QSize(10, 10)));
                break;
            case 5:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Diamond, QBrush(Qt::red), QPen(Qt::red), QSize(10, 10)));
                break;
            case 6:
                maker->setSymbol(new QwtSymbol(QwtSymbol::XCross, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(10, 10)));
                break;
            case 7:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Star2, QBrush(Qt::blue),QPen(Qt::blue), QSize(10, 10)));
                break;
            }
            maker->attach(ui->qwtPlot);
            maker->setValue(QPointF(m_FlawPointList->at(i).x, m_FlawPointList->at(i).y));
        }
    }
    ui->qwtPlot->replot();
}

void MainWindow::drawLegend()
{
    //添加图例
    QwtLegend* legend = new QwtLegend();
    legend->setDefaultItemMode(QwtLegendData::Checkable);
    ui->qwtPlot->insertLegend(legend);
    //划伤标记
    QwtPlotCurve* curve1 = new QwtPlotCurve("划伤");
    QwtSymbol* symbol1 = new QwtSymbol(QwtSymbol::Cross, QBrush(Qt::blue), QPen(Qt::blue), QSize(5, 5));
    curve1->setSymbol(symbol1);
    curve1->setLegendAttribute(QwtPlotCurve::LegendShowSymbol );
    curve1->attach(ui->qwtPlot);
    //气结标记
    QwtPlotCurve* curve2 = new QwtPlotCurve("气泡");
    QwtSymbol* symbol2 = new QwtSymbol(QwtSymbol::Rect, QBrush(Qt::red), QPen(Qt::red), QSize(5, 5));
    curve2->setSymbol(symbol2);
    curve2->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve2->attach(ui->qwtPlot);
    //崩边标记
    QwtPlotCurve* curve3 = new QwtPlotCurve("崩边");
    QwtSymbol* symbol3 = new QwtSymbol(QwtSymbol::Star1, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(5, 5));
    curve3->setSymbol(symbol3);
    curve3->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve3->attach(ui->qwtPlot);
    //脏污标记
    QwtPlotCurve* curve4 = new QwtPlotCurve("脏污");
    QwtSymbol* symbol4 = new QwtSymbol(QwtSymbol::Triangle, QBrush(Qt::blue), QPen(Qt::blue), QSize(5, 5));
    curve4->setSymbol(symbol4);
    curve4->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve4->attach(ui->qwtPlot);
    //裂纹标记
    QwtPlotCurve* curve5 = new QwtPlotCurve("裂纹");
    QwtSymbol* symbol5 = new QwtSymbol(QwtSymbol::Diamond, QBrush(Qt::red), QPen(Qt::red), QSize(5, 5));
    curve5->setSymbol(symbol5);
    curve5->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve5->attach(ui->qwtPlot);
    //其他标记
    QwtPlotCurve* curve6 = new QwtPlotCurve("其他");
    QwtSymbol* symbol6 = new QwtSymbol(QwtSymbol::XCross, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(5, 5));
    curve6->setSymbol(symbol6);
    curve6->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve6->attach(ui->qwtPlot);
    //缺陷7标记
    QwtPlotCurve* curve7 = new QwtPlotCurve("结石");
    QwtSymbol* symbol7 =  new QwtSymbol(QwtSymbol::Star2, QBrush(Qt::blue),QPen(Qt::blue), QSize(5, 5));
    curve7->setSymbol(symbol7);
    curve7->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve7->attach(ui->qwtPlot);

    QwtPlotItemList items = ui->qwtPlot->itemList(QwtPlotItem::Rtti_PlotCurve);
    qDebug()<<"items.size() ="<<items.size();
    for (int i=0; i < items.size(); ++i )
    {
        if (legendVec.size() == 7)//7为缺陷的种类
            legendVec.clear();
        legendVec.push_back(items[i]);//依次保存图例
        const QVariant itemInfo = ui->qwtPlot->itemToInfo( items[i] );
        QwtLegendLabel *legendLabel = (QwtLegendLabel *)legend->legendWidget( itemInfo ) ;
        if ( legendLabel ) {
                legendLabel->setChecked( true );
                replotMap[i] = true;
        }

    }
    //绑定槽函数
    connect(legend,SIGNAL(checked( const QVariant &, bool, int )), this, SLOT( slot_LegendChecked(const QVariant &, bool, int)));
}

void MainWindow::slot_LegendChecked(const QVariant &itemInfo, bool on, int index)
{
    //获取曲线
    QwtPlotItem *plotItem = ui->qwtPlot->infoToItem( itemInfo );
    qDebug()<<"on = "<<on;
    int result = 0;
    for(size_t i=0; i< legendVec.size(); ++i) {
        if (plotItem == legendVec[i]) { //i-1防止数组越界
           result = (int)i;
           replotMap[result] = on;
           break;
        }
    }
    //1~7对应各个缺陷类型
//    reDrawFlaw(&FlawPointList);

}

void MainWindow::InitSummaryTableWidget()
{
    //
    // 时间定时刷新
    //
    _timer = new QTimer();
    connect(_timer, &QTimer::timeout, this, &MainWindow::slot_RefreshSystemTime);
    _timer->start(1000);
    //
    // 读取数据库获取初始化值
    //
    ui->glassTotalCountLE->setText(QString("0"));
    ui->glassTotalCountLE->setAlignment(Qt::AlignCenter);
    ui->glassTotalCountLE->setReadOnly(true);

    ui->currentGlassStatus->setText(QString(""));
    ui->currentGlassStatus->setAlignment(Qt::AlignCenter);

    ui->glassOKCount->setText(QString("0"));
    ui->glassOKCount->setAlignment(Qt::AlignCenter);
    ui->glassOKCount->setReadOnly(true);

    ui->glassNGCount->setText(QString("0"));
    ui->glassNGCount->setAlignment(Qt::AlignCenter);
    ui->glassNGCount->setReadOnly(true);

    ui->qualicaficationRateLE->setText(QString("0"));
    ui->qualicaficationRateLE->setAlignment(Qt::AlignCenter);
    ui->qualicaficationRateLE->setReadOnly(true);

    ui->ExceptionCountLE->setText(QString("0"));
    ui->ExceptionCountLE->setAlignment(Qt::AlignCenter);
    ui->ExceptionCountLE->setReadOnly(true);

    ui->hasSortCountLE->setText(QString("0"));
    ui->hasSortCountLE->setAlignment(Qt::AlignCenter);
    ui->hasSortCountLE->setReadOnly(true);

    ui->NoSortCountLE->setText(QString("0"));
    ui->NoSortCountLE->setAlignment(Qt::AlignCenter);
    ui->NoSortCountLE->setReadOnly(true);
}

void MainWindow::slot_RefreshSystemTime()
{
    QDate currentDate = QDate::currentDate();
    ui->weekLB->setText(currentDate.toString("dddd"));
    ui->weekLB->setAlignment(Qt::AlignCenter);
    ui->weekLB->setStyleSheet("font-size: 30px;color: black;font-weight: bold;"); // 设置字体大小为 20 像素

    QLocale locale(QLocale::Chinese);
    QString chineseDate = locale.toString(currentDate, "yyyy'年'MM'月'dd'日'");
    ui->YearMonthDayLB->setText(chineseDate);
    ui->YearMonthDayLB->setAlignment(Qt::AlignCenter);
    ui->YearMonthDayLB->setStyleSheet("font-size: 30px;color: black;font-weight: bold;"); // 设置字体大小为 20 像素

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QTime currentTime = currentDateTime.time();
    QString chineseTime = currentTime.toString("hh:mm:ss");
    ui->timeLB->setText(chineseTime);
    ui->timeLB->setAlignment(Qt::AlignCenter);
    ui->timeLB->setStyleSheet("font-size: 40px;color: black;font-weight: bold;"); // 设置字体大小为 20 像素
}

void MainWindow::InitLogInformation()
{
    ui->loglistWidget = new QListWidget();
}

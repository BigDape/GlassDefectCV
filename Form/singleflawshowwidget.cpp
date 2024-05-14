#include "singleflawshowwidget.h"
#include <QDebug>
#include <QDir>
#include "ui_singleflawshowwidget.h"
#include <QLineF>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <QProgressDialog>
#include <QString>
#include <fstream>
#include <QTextStream>
#pragma execution_character_set("utf-8")

SingleFlawShowWidget::SingleFlawShowWidget(Qt::Orientation ori,
                                           Qt::Orientation pic_ori,
                                           QWidget* parent)
    : QWidget(parent), ui(new Ui::SingleFlawShowWidget) {
    LastGlassID="0";
  m_orientation = ori;
  m_pic_orientation = pic_ori;
  ui->setupUi(this);
  insertStatus=true;


  scene=new QGraphicsScene();
  loadedPixmapItem = new MyGraphicsItem();
  ui->graphicsView->setScene(scene);
  scene->addItem(loadedPixmapItem);

  scene2=new QGraphicsScene();
  loadedPixmapItem2 = new MyGraphicsItem();
  ui->graphicsView_2->setScene(scene2);
  scene2->addItem(loadedPixmapItem2);

  scene3=new QGraphicsScene();
  loadedPixmapItem3 = new MyGraphicsItem();
  ui->graphicsView_3->setScene(scene3);
  scene3->addItem(loadedPixmapItem3);


  connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(onItemDoubleClicked(QTableWidgetItem*)));
  connect(ui->tableWidget, &QTableWidget::itemDoubleClicked, this, &SingleFlawShowWidget::showFlawImage);
  connect(ui->tableWidget, &QTableWidget::itemClicked, this, &SingleFlawShowWidget::slot_FlawTrack);//缺陷追踪功能
  connect(ui->buttonExport, SIGNAL(clicked()), this, SLOT(slot_ButtonExportClicked()));

  initLayout();

}

void SingleFlawShowWidget::showFlawImage(QTableWidgetItem* item) {
  if (item) {
    int row = item->row();
    QString itemID = ui->tableWidget->item(row, 0)->text();
    JSONRECIPE = new JsonParse2Map(fileName);
    QString ImagePath;
    JSONRECIPE->getParameter(GlassID + "." + QString::number(row + 1) + ".ImageNGPath", ImagePath);
//    QTextCodec *code = QTextCodec::codecForName("GB2312");
//    std::string name = code->fromUnicode(ImagePath).data();
//    ImagePath = ImagePath.replace(QChar(0x202A), "");
//   ImagePath = name.data();
    qDebug() << "imagepath = " << ImagePath;
    QDir dir;
    QString strpath;
    dir.setPath(ImagePath);
    QFileInfoList infolist = dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    qDebug()<<"infolist.size()"<<infolist.size();
    foreach(const QFileInfo &info, infolist)
    {
        strpath += info.absoluteFilePath() + "_";
    }
    qDebug() << strpath;
    qDebug() << strpath << strpath.split("_")[0] << strpath.split("_")[1] << strpath.split("_")[2];
//    QPixmap pixmap1(strpath.split("_")[0]);
//    QPixmap pixmap2(strpath.split("_")[1]);
//    QPixmap pixmap3(strpath.split("_")[2]);
//    ui->label->setPixmap(pixmap1.scaled(310, 310));
//    ui->label->setFixedSize(320, 320);
//    ui->label_2->setPixmap(pixmap2.scaled(310, 310));
//    ui->label_2->setFixedSize(320, 320);
//    ui->label_3->setPixmap(pixmap3.scaled(310, 310));
//    ui->label_3->setFixedSize(320, 320);
    QImage img1(strpath.split("_")[0]);
    QImage img2(strpath.split("_")[1]);
    QImage img3(strpath.split("_")[2]);

    loadedPixmapItem->loadImage(img1);
    int nwidth = ui->graphicsView->width(), nheight = ui->graphicsView->height();
    loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));

//    // 记录当前视图中心点坐标
//    QPointF center = ui->graphicsView->mapToScene(ui->graphicsView->viewport()->rect().center());

//    // 缩放视图
// //   ui->graphicsView->scale(factor, factor); // factor 是缩放因子

//    // 将视图中心点坐标设置为之前记录的坐标
//    QPointF newCenter = ui->graphicsView->mapFromScene(center);
//    QPointF delta = newCenter - ui->graphicsView->viewport()->rect().center();
//    ui->graphicsView->translate(delta.x(), delta.y());

    // 设置 QGraphicsView 的属性，使图片自适应显示
//    ui->graphicsView->setAlignment(Qt::AlignCenter);
//    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
//    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);

    loadedPixmapItem2->loadImage(img2);
    int nwidth2 = ui->graphicsView_2->width(), nheight2 = ui->graphicsView_2->height();
    loadedPixmapItem2->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));

    loadedPixmapItem3->loadImage(img3);
    int nwidth3 = ui->graphicsView_3->width(), nheight3 = ui->graphicsView_3->height();
    loadedPixmapItem3->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
  }
}

void SingleFlawShowWidget::initLayout() {
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

  ui->tableWidget->verticalHeader()->setVisible(false);

  ui->tableWidget->setColumnWidth(0, 90);
}

void SingleFlawShowWidget::onItemDoubleClicked(QTableWidgetItem*) {
  int rowCount = ui->tableWidget->rowCount();
  int columnCount = ui->tableWidget->columnCount();

  for (int row = 0; row < rowCount; ++row) {
    for (int col = 0; col < columnCount; ++col) {
      QTableWidgetItem* item = ui->tableWidget->item(row, col);
      if (item) {
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
      }
    }
  }
}

void SingleFlawShowWidget::slot_RecieveID(QString IDandDate) {
  if (insertStatus) {
    GlassID = IDandDate.split(".")[0];
    if (LastGlassID!=GlassID) {
        LastGlassID=GlassID;
        Date = IDandDate.split(".")[1];
        fileName = "DefectInfJson/" + Date + ".json";
        JSONRECIPE = new JsonParse2Map(fileName);

        int count = JSONRECIPE->CountValuesUnderKey(GlassID);
        ui->tableWidget->setRowCount(count);
        singleFlawData.clear();
        QString header = QString("%1,%2,%3,%4,%5,%6,%7,%8,%9").arg("DefectID").arg("Time").arg("DefectType").arg("DetectLeve").arg("X").arg("Y").arg("Lenth").arg("Width").arg("Area");
        singleFlawData.push_back(header);
        for (int i = 1; i <= count; i++) {
            QString tempData;
            QString DefectID, Time, DefectType, DetectLeve, X, Y, Lenth, Width, Area;
            //序号
            JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".DefectID",DefectID);
            QTableWidgetItem* item0 = new QTableWidgetItem(DefectID);
            item0->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i - 1, 0, item0);
            tempData.clear();
            tempData = DefectID;
            //时间
            JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".Time",Time);
            QTableWidgetItem* item1 = new QTableWidgetItem(Time);
            item1->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i - 1, 1, item1);
            tempData = tempData + "," + Time;
            //类型
            JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".DefectType",DefectType);
            QTableWidgetItem* item2 = new QTableWidgetItem(DefectType);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i - 1, 2, item2);
            tempData = tempData + "," + DefectType;
            //等级
            JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".DetectLeve",DetectLeve);
            QTableWidgetItem* item3 = new QTableWidgetItem(DetectLeve);
            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i - 1, 3, item3);
            tempData = tempData + "," + DetectLeve;
            //坐标X
            JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".X", X);
            QTableWidgetItem* item4 = new QTableWidgetItem(X);
            item4->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i - 1, 4, item4);
            tempData = tempData + "," + X;
            //坐标Y
            JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".Y", Y);
            QTableWidgetItem* item5 = new QTableWidgetItem(Y);
            item5->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i - 1, 5, item5);
            tempData = tempData + "," + Y;
            //长
            JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".Lenth",Lenth);
            QTableWidgetItem* item6 = new QTableWidgetItem(Lenth);
            item6->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i - 1, 6, item6);
            tempData = tempData + "," + Lenth;
            //宽
            JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".Width",Width);
            QTableWidgetItem* item7 = new QTableWidgetItem(Width);
            item7->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i - 1, 7, item7);
            tempData = tempData + "," + Width;
            //区域
            JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".Area",Area);
            QTableWidgetItem* item8 = new QTableWidgetItem(Area);
            item8->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i - 1, 8, item8);
            tempData = tempData + "," + Area;
            //插入坐标到map中
            rowMapXY[i - 1] = std::make_pair(X,Y);
            singleFlawData.push_back(tempData);
        }
    }
  }
}

void SingleFlawShowWidget::slot_PickerCheckData(const FlawPoint &flawpoint)
{
    qDebug()<<" slotcheck success";
    int rowcou=ui->tableWidget->rowCount();
    int col1=4;
    int col2=5;
    for(int row=0;row<rowcou;row++){
        QTableWidgetItem*Item1=ui->tableWidget->item(row,col1);
        QTableWidgetItem*Item2=ui->tableWidget->item(row,col2);
        if(col1&&col2){
            QString data1=Item1->text();
            QString data2=Item2->text();
            QString checkdata1=QString::number(flawpoint.y);
            QString checkdata2=QString::number(flawpoint.x);
//            qDebug()<<data1<<" "<<data2<<" "<<checkdata1<<" "<<checkdata2;
            if(data1==checkdata1&&data2==checkdata2){
                showFlawImage(ui->tableWidget->item(row,0));
                ui->tableWidget->setCurrentItem(ui->tableWidget->item(row,0));
                break;
            }

        }
    }
}

SingleFlawShowWidget::~SingleFlawShowWidget() {
    delete ui;
    delete loadedPixmapItem;
    delete scene;
    delete loadedPixmapItem2;
    delete scene2;
    delete loadedPixmapItem3;
    delete scene3;

}

void SingleFlawShowWidget::on_pushButton_clicked()
{
    if(insertStatus==true){
        ui->pushButton->setText("恢复");
        insertStatus=false;
    }else{
        ui->pushButton->setText("暂停");
        insertStatus=true;
    }
}

void SingleFlawShowWidget::slot_FlawTrack(QTableWidgetItem* item)
{
    qDebug()<<"SingleFlawShowWidget::slot_FlawTrack(int row, int col)";
    if (item) {
      int row = item->row();
      QString x,y;
      if (rowMapXY.count(row) != 0) {
          //获取到缺陷的x,y
          y = rowMapXY[row].first;
          x = rowMapXY[row].second;
         if(Global::m_plot != NULL) {
             double xValue = x.toDouble();
             double yValue = y.toDouble();
             if ( Global::m_plot != NULL) {
                 Global::m_plot->detachItems(QwtPlotItem::Rtti_PlotShape);//清理之前追踪图框
                 QwtPlotShapeItem* trackItem = new QwtPlotShapeItem;
                 trackItem->setPen(QPen(Qt::red));
                 QRectF trackRect(xValue-20, yValue-20, 40, 40);
                 trackItem->setRect(trackRect);
                 trackItem->attach(Global::m_plot);

                 Global::m_plot->replot();
             }
         }
      }
    }
}

void SingleFlawShowWidget::slot_ButtonExportClicked()
{
    try {
      //获取选择的目录路径
          _selectedDir = QFileDialog::getExistingDirectory(this,"选择一个目录","./",QFileDialog::ShowDirsOnly);
          //若目录路径不为空
          if (!_selectedDir.isEmpty()) {
              //将路径中的斜杠替换为反斜杠
              _selectedDir = _selectedDir.replace(QRegExp("\\"), "/");
              qDebug()<<"_selectedDir =" <<_selectedDir;
              //SingleFlawShowWidget::jsonFileToCSVFile();
              QString time = QDateTime::currentDateTime().toString("yy_MM_dd_hhmmss");
              QString tempCSVFile = _selectedDir+ "/" + time + ".csv";
              qDebug()<<"fullpath =" <<tempCSVFile;
              std::string fullpath = tempCSVFile.toStdString();
              qDebug()<<"singleFlawData.size() =" << singleFlawData.size();
              if (singleFlawData.size() != 0 ) {
                  std::ofstream dataFile;
                  dataFile.open(fullpath, std::ios::out | std::ios::trunc);
                  for (size_t i = 0; i < singleFlawData.size(); ++i) { //行数
                        std::string str = singleFlawData[i].toStdString();// 写入数据
                        dataFile << str <<std::endl;// 换行
                  }
                  dataFile.close();                            // 关闭文档
                  singleFlawData.clear();
              }
          }
       } catch(...) {
          qDebug()<<"slot_ButtonExportClicked() error";
      }
}

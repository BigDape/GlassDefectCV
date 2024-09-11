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
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Global.h"

#pragma execution_character_set("utf-8")

SingleFlawShowWidget::SingleFlawShowWidget(Qt::Orientation ori,
                                           Qt::Orientation pic_ori,
                                           QWidget* parent)
    : QWidget(parent),
      ui(new Ui::SingleFlawShowWidget)
{
    LastGlassID=-1;
    m_orientation = ori;
    m_pic_orientation = pic_ori;
    ui->setupUi(this);

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

void SingleFlawShowWidget::showFlawImage(QTableWidgetItem* item)
{
    if (item) {
        int row = item->row();
        QString ImagePath1;
        QString ImagePath2;
        QString ImagePath3;
//        Jsoncpp::GetInstance()->getFlawImageFromJson(jsonFileName,GlassID,row,ImagePath1,ImagePath2,ImagePath3);
        QImage img1(ImagePath1);
        QImage img2(ImagePath2);
        QImage img3(ImagePath3);

        loadedPixmapItem->loadImage(img1);
        int nwidth = ui->graphicsView->width(), nheight = ui->graphicsView->height();
        loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
        ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));

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

void SingleFlawShowWidget::slot_RecieveID(QString jsonFullPath, int glassid)
{
//    Global::glassidTodefectjson[glassid] = jsonFullPath; //存储glassid到jsonFullPath
//    GlassID = glassid;
//    if (LastGlassID != glassid) {
//        LastGlassID = GlassID;
////        std::vector<DefectData> results;
////        Jsoncpp::GetInstance()->getDefectSFromJson(jsonFullPath,glassid,results);
//        int count = results.size();
//        if(count > 0) {
//            ui->tableWidget->setRowCount(count);
//            ui->tableWidget->setColumnCount(9);
//            for (int i = 0; i < count; i++) {
//                //序号
//                QString DefectID = QString::number(results[i].DefectID);
//                QTableWidgetItem* item0 = new QTableWidgetItem(DefectID);
//                item0->setTextAlignment(Qt::AlignCenter);
//                ui->tableWidget->setItem(i, 0, item0);
//                //时间
//                QString Time = results[i].Time;
//                QTableWidgetItem* item1 = new QTableWidgetItem(Time);
//                item1->setTextAlignment(Qt::AlignCenter);
//                ui->tableWidget->setItem(i, 1, item1);
//                //类型
//                QString DefectType = results[i].DefectType;
//                QTableWidgetItem* item2 = new QTableWidgetItem(DefectType);
//                item2->setTextAlignment(Qt::AlignCenter);
//                ui->tableWidget->setItem(i , 2, item2);
//                //等级
//                QString DetectLeve = results[i].DetectLeve;
//                QTableWidgetItem* item3 = new QTableWidgetItem(DetectLeve);
//                item3->setTextAlignment(Qt::AlignCenter);
//                ui->tableWidget->setItem(i, 3, item3);
//                //坐标X
//                QString X = QString::number(results[i].X,'f', 2);
//                QTableWidgetItem* item4 = new QTableWidgetItem(X);
//                item4->setTextAlignment(Qt::AlignCenter);
//                ui->tableWidget->setItem(i, 4, item4);
//                //坐标Y
//                QString Y = QString::number(results[i].Y,'f', 2);
//                QTableWidgetItem* item5 = new QTableWidgetItem(Y);
//                item5->setTextAlignment(Qt::AlignCenter);
//                ui->tableWidget->setItem(i, 5, item5);
//                //长
//                QString Lenth = QString::number(results[i].Lenth,'f', 2);
//                QTableWidgetItem* item6 = new QTableWidgetItem(Lenth);
//                item6->setTextAlignment(Qt::AlignCenter);
//                ui->tableWidget->setItem(i, 6, item6);
//                //宽
//                QString Width = QString::number(results[i].Width,'f', 2);
//                QTableWidgetItem* item7 = new QTableWidgetItem(Width);
//                item7->setTextAlignment(Qt::AlignCenter);
//                ui->tableWidget->setItem(i, 7, item7);
//                //区域
//                QString Area = QString::number(results[i].Area,'f', 2);
//                QTableWidgetItem* item8 = new QTableWidgetItem(Area);
//                item8->setTextAlignment(Qt::AlignCenter);
//                ui->tableWidget->setItem(i, 8, item8);
//                //插入坐标到map中，用于追踪缺陷
//                rowMapXY[i - 1] = std::make_pair(X,Y);
//            }
//        }
//    }
}

void SingleFlawShowWidget::PickerCheckData(/*const FlawPoint &flawpoint*/)
{
//    int rowcou=ui->tableWidget->rowCount();
//    int col1=4;
//    int col2=5;
//    for(int row=0;row<rowcou;row++) {
//        QTableWidgetItem* Item1=ui->tableWidget->item(row,col1);
//        QTableWidgetItem* Item2=ui->tableWidget->item(row,col2);
//        if (Item1 != nullptr && Item2 != nullptr) {
//            QString data1 = Item1->text();
//            QString data2 = Item2->text();
//            QString checkdata1 = QString::number(flawpoint.y,'f',2);
//            QString checkdata2 = QString::number(flawpoint.x, 'f',2);
//            if( data1 == checkdata1 && data2 == checkdata2 ) {
//                showFlawImage(ui->tableWidget->item(row,0));
//                ui->tableWidget->setCurrentItem(ui->tableWidget->item(row,0));
//                break;
//            }
//        }
//    }
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
              QString time = QDateTime::currentDateTime().toString("yy_MM_dd_hhmmss");
              QString tempCSVFile = _selectedDir+ "/" + time + ".csv";
              qDebug()<<"fullpath =" <<tempCSVFile;
              std::string fullpath = tempCSVFile.toStdString();
//              if (singleFlawData.size() != 0 ) {
//                  std::ofstream dataFile;
//                  dataFile.open(fullpath, std::ios::out | std::ios::trunc);
//                  for (size_t i = 0; i < singleFlawData.size(); ++i) { //行数
//                        std::string str = singleFlawData[i].toStdString();// 写入数据
//                        dataFile << str <<std::endl;// 换行
//                  }
//                  dataFile.close();                            // 关闭文档
//                  singleFlawData.clear();
//              }
          }
       } catch(...) {
          qDebug()<<"slot_ButtonExportClicked() error";
      }
}

void SingleFlawShowWidget::slot_refrshFlaw(QString jsonFullPath,int glassid)
{
//    Global::glassidTodefectjson[glassid] = jsonFullPath; //存储glassid到jsonFullPath
//    GlassID = glassid;
//    jsonFileName = jsonFullPath;
//    std::vector<DefectData> results;
//    Jsoncpp::GetInstance()->getDefectSFromJson(jsonFullPath,glassid,results);
//    int count = results.size();
//    if (count > 0) {
//        ui->tableWidget->setRowCount(count);
//        ui->tableWidget->setColumnCount(9);
//        for (int i = 0; i < count; i++) {
//            //序号
//            QString DefectID = QString::number(results[i].DefectID);
//            QTableWidgetItem* item0 = new QTableWidgetItem(DefectID);
//            item0->setTextAlignment(Qt::AlignCenter);
//            ui->tableWidget->setItem(i, 0, item0);
//            //时间
//            QString Time = results[i].Time;
//            QTableWidgetItem* item1 = new QTableWidgetItem(Time);
//            item1->setTextAlignment(Qt::AlignCenter);
//            ui->tableWidget->setItem(i, 1, item1);
//            //类型
//            QString DefectType = results[i].DefectType;
//            QTableWidgetItem* item2 = new QTableWidgetItem(DefectType);
//            item2->setTextAlignment(Qt::AlignCenter);
//            ui->tableWidget->setItem(i , 2, item2);
//            //等级
//            QString DetectLeve = results[i].DetectLeve;
//            QTableWidgetItem* item3 = new QTableWidgetItem(DetectLeve);
//            item3->setTextAlignment(Qt::AlignCenter);
//            ui->tableWidget->setItem(i, 3, item3);
//            //坐标X
//            QString X = QString::number(results[i].X,'f', 2);
//            QTableWidgetItem* item4 = new QTableWidgetItem(X);
//            item4->setTextAlignment(Qt::AlignCenter);
//            ui->tableWidget->setItem(i, 4, item4);
//            //坐标Y
//            QString Y = QString::number(results[i].Y,'f', 2);
//            QTableWidgetItem* item5 = new QTableWidgetItem(Y);
//            item5->setTextAlignment(Qt::AlignCenter);
//            ui->tableWidget->setItem(i, 5, item5);
//            //长
//            QString Lenth = QString::number(results[i].Lenth,'f', 2);
//            QTableWidgetItem* item6 = new QTableWidgetItem(Lenth);
//            item6->setTextAlignment(Qt::AlignCenter);
//            ui->tableWidget->setItem(i, 6, item6);
//            //宽
//            QString Width = QString::number(results[i].Width,'f', 2);
//            QTableWidgetItem* item7 = new QTableWidgetItem(Width);
//            item7->setTextAlignment(Qt::AlignCenter);
//            ui->tableWidget->setItem(i, 7, item7);
//            //区域
//            QString Area = QString::number(results[i].Area,'f', 2);
//            QTableWidgetItem* item8 = new QTableWidgetItem(Area);
//            item8->setTextAlignment(Qt::AlignCenter);
//            ui->tableWidget->setItem(i, 8, item8);
//            //插入坐标到map中，用于追踪缺陷
//            rowMapXY[i - 1] = std::make_pair(X,Y);
//        }
//    } else {
//        qWarning()<<"count = 0";
//    }

//    // 更新三张小图
//    if ( ui->tableWidget->item(0, 0) != nullptr) {
//        try {
//            QString ImagePath1;
//            QString ImagePath2;
//            QString ImagePath3;
//            Jsoncpp::GetInstance()->getFlawImageFromJson(jsonFileName,GlassID,0,ImagePath1,ImagePath2,ImagePath3);
//            qDebug() << "imagepath = " << ImagePath1;
//            QString strpath1 = ImagePath1 + "/1.jpg";
//            QString strpath2 = ImagePath2 + "/2.jpg";
//            QString strpath3 = ImagePath3 + "/3.jpg";
//            QImage img1(strpath1);
//            QImage img2(strpath2);
//            QImage img3(strpath3);

//            loadedPixmapItem->loadImage(img1);
//            int nwidth = ui->graphicsView->width(), nheight = ui->graphicsView->height();
//            loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
//            ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));

//            loadedPixmapItem2->loadImage(img2);
//            int nwidth2 = ui->graphicsView_2->width(), nheight2 = ui->graphicsView_2->height();
//            loadedPixmapItem2->setQGraphicsViewWH(nwidth, nheight);
//            ui->graphicsView_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));

//            loadedPixmapItem3->loadImage(img3);
//            int nwidth3 = ui->graphicsView_3->width(), nheight3 = ui->graphicsView_3->height();
//            loadedPixmapItem3->setQGraphicsViewWH(nwidth, nheight);
//            ui->graphicsView_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
//        } catch (std::exception e) {
//            qDebug()<<e.what();
//        } catch(...) {
//            qDebug()<<"Unknow exception";
//        }
//   }
}

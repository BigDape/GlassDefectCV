#include "SingleSizeShowWidget.h"
#include <QDebug>
#include <QDir>
#include "ui_SingleSizeShowWidget.h"
#include "Parameter/json.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Global.h"
#pragma execution_character_set("utf-8")

#define MATCH_ERROR 0.2

SingleSizeShowWidget::SingleSizeShowWidget(Qt::Orientation ori,
                                           Qt::Orientation pic_ori,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleSizeShowWidget)
{
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

    connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(slot_onItemDoubleClicked(QTableWidgetItem*)));
    connect(ui->tableWidget, &QTableWidget::itemDoubleClicked, this, &SingleSizeShowWidget::slot_showSizeSmallImage);

    initLayout();
    SingleSizeShowWidget::initMode();
}

SingleSizeShowWidget::~SingleSizeShowWidget()
{
    delete ui;
    delete loadedPixmapItem;
    delete scene;
    delete loadedPixmapItem2;
    delete scene2;  
}

void SingleSizeShowWidget::initLayout()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setColumnWidth(0, 90);
}

void SingleSizeShowWidget::slot_onItemDoubleClicked(QTableWidgetItem*) {
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

void SingleSizeShowWidget::slot_RecieveID(QString jsonFullPath,int glassid)
{
    GlassID = glassid;
    jsonFileName = jsonFullPath;
    if(LastGlassID != glassid) {
        LastGlassID=GlassID;
        SingleSizeShowWidget::showSizeDiagramImage(jsonFullPath,glassid);//显示轮廓图
        //
        // 将文件中已有的数据读出来
        //
        Json::Value root;
        QDir folderDir(jsonFullPath);
        qDebug()<<"jsonFullPath  = "<<jsonFullPath;
        if (folderDir.exists()) {
            std::ifstream ifs;
            ifs.open(jsonFullPath.toStdString().c_str()); // Windows自己注意路径吧
            if (ifs.is_open()) {
                 Json::Reader reader;
                 // 解析到root，root将包含Json里所有子元素
                 reader.parse(ifs, root, false);
                 ifs.close();
            } else {
                qDebug()<<"[SingleSizeShowWidget::showSizeDiagramImage] ifs.is_open() =  false";
            }
        } else {
            qDebug()<<"[SingleSizeShowWidget::showSizeDiagramImage] "<<jsonFullPath<<" is not exit.";
        }
        if(!root.empty()) {
            Json::Value holes = root[QString::number(glassid).toStdString().c_str()];
            int count = holes.size() - 4; //减去角度、长度、宽度、轮廓图路径
            ui->tableWidget->setRowCount(count);
            for (int i = 1; i <= count; i++) {
                Json::Value hole = holes[QString::number(i).toStdString().c_str()];
                // 序号
                QString HolesID = QString::number(hole["HolesID"].asInt());
                QTableWidgetItem* item0 = new QTableWidgetItem(HolesID);
                item0->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(i - 1, 0, item0);
                // 时间
                QString Time = hole["Time"].asString().data();
                QTableWidgetItem* item1 = new QTableWidgetItem(Time);
                item1->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(i - 1, 1, item1);
                // 类型
                QString Type = hole["Type"].asString().data();
                QTableWidgetItem* item2 = new QTableWidgetItem(Type);
                item2->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(i - 1, 2, item2);
                // 长X
                QString HolesHeight = QString::number(hole["HolesHeight"].asDouble(),'f', 2);
                QTableWidgetItem* item4 = new QTableWidgetItem(HolesHeight);
                item4->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(i - 1, 4, item4);
                // 宽Y
                QString HolesWidth = QString::number(hole["HolesWidth"].asDouble(),'f', 2);
                QTableWidgetItem* item5 = new QTableWidgetItem(HolesWidth);
                item5->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(i - 1, 5, item5);
                // 边距X
                QString DistanceHorizontal = QString::number(hole["DistanceHorizontal"].asDouble(),'f', 2);
                QTableWidgetItem* item6 = new QTableWidgetItem(DistanceHorizontal);
                item6->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(i - 1, 6, item6);
                // 边距Y
                QString DistanceVertical = QString::number(hole["DistanceVertical"].asDouble(),'f', 2);
                QTableWidgetItem* item7 = new QTableWidgetItem(DistanceVertical);
                item7->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(i - 1, 7, item7);

                //比较孔洞
                QString HolesLeve = hole["HolesLeve"].asString().data();
                if (HolesLeve == "OK") {
                      if(Type == "孔") {
                          if(SingleSizeShowWidget::matchHoleMode(HolesHeight,HolesWidth,DistanceHorizontal,DistanceVertical) == false) {
                              qDebug()<<"NG:=>"<<"HolesHeight="<<HolesHeight<<",HolesWidth="<<HolesWidth<<",DistanceHorizontal="<<DistanceHorizontal<<",DistanceVertical="<<DistanceVertical;
                              HolesLeve = "NG";
                          }
                      } else if(Type == "门夹"){
                          if(SingleSizeShowWidget::matchMenjiaMode(DistanceHorizontal,DistanceVertical) == false) {
                              qDebug()<<"NG:=>"<<"DistanceHorizontal="<<DistanceHorizontal<<",DistanceVertical="<<DistanceVertical;
                              HolesLeve = "NG";
                          }
                      }
                }

                QTableWidgetItem* item3 = new QTableWidgetItem(HolesLeve);
                item3->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(i - 1, 3, item3);
            }
        }
    }
}
//
// 显示缺陷小图
//
void SingleSizeShowWidget::slot_showSizeSmallImage(QTableWidgetItem *item)
{
    if (item) {
      int row = item->row();
      Json::Value root;
      qDebug()<<__FUNCTION__<<"jsonFileName =" <<jsonFileName;
      QFile fileer(jsonFileName);
      if (fileer.exists()) {
          std::ifstream ifs;
          ifs.open(jsonFileName.toStdString().c_str()); // Windows自己注意路径吧
          if (ifs.is_open()) {
               Json::Reader reader;
               // 解析到root，root将包含Json里所有子元素
               reader.parse(ifs, root, false);
               ifs.close();
          } else {
              qDebug()<<__FUNCTION__<<" ifs.is_open() =  false";
          }
      } else {
          qDebug()<<__FUNCTION__<<jsonFileName<<" is not exit.";
      }

      if(!root.empty()) {
            qDebug()<<__FUNCTION__<<"GlassID ="<<GlassID;
            Json::Value holes = root[QString::number(GlassID).toStdString().c_str()];
            Json::Value hole = holes[QString::number(row).toStdString().c_str()];
            QString ImageHolesPath = hole["ImageHolesPath"].asString().data() + QString("/") + QString::number(row) + ".jpg";
            qDebug() << "ImageHolesPath = " << ImageHolesPath;
            QImage img(ImageHolesPath);
            loadedPixmapItem2->loadImage(img);
            int nwidth = ui->graphicsView_2->width(), nheight = ui->graphicsView_2->height();
            loadedPixmapItem2->setQGraphicsViewWH(nwidth, nheight);
            ui->graphicsView_2->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
      }
    }
}

//
// 显示轮廓图
//
void SingleSizeShowWidget::showSizeDiagramImage(QString jsonFullPath,int glassid)
{ 
    Global::glassidToholejson[glassid] = jsonFullPath; //存储glassid到jsonFullPath
    GlassID = glassid;
    jsonFileName = jsonFullPath;
    //
    // 将文件中已有的数据读出来
    //
    Json::Value root;
    QFile folderDir(jsonFullPath);
    qDebug()<<"jsonFullPath  = "<<jsonFullPath;
    if (folderDir.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFullPath.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<"[SingleSizeShowWidget::showSizeDiagramImage] ifs.is_open() =  false";
        }
    } else {
        qDebug()<<"[SingleSizeShowWidget::showSizeDiagramImage] "<<jsonFullPath<<" is not exit.";
    }

    if(!root.empty()) {
        Json::Value holes = root[QString::number(glassid).toStdString().c_str()];
        QString ImageHolesLinePath = holes["ImageHolesLinePath"].asString().data();
        qDebug() << "ImageHolesLinePath = " << ImageHolesLinePath;
        QImage img1(ImageHolesLinePath);//D:/SaveDefectImage/2024-07-30/孔示意图/09-14-39/1.jpg
        loadedPixmapItem->loadImage(img1);
        int nwidth = ui->graphicsView->width(), nheight = ui->graphicsView->height();
        loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
        ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
    } else {
        qDebug()<<"[SingleSizeShowWidget::showSizeDiagramImage] ifs.is_open() =  false";
    }
}

void SingleSizeShowWidget::initMode()
{
    QString holeFileName = QCoreApplication::applicationDirPath() + "/hole.ini";
    qDebug()<<"Path =" <<holeFileName;
    std::shared_ptr<QSettings> setPtr = std::make_shared<QSettings>(holeFileName  , QSettings::IniFormat);
    //设置文件编码，配置文件中使用中文时，这是必须的，否则乱码
    setPtr->setIniCodec(QTextCodec::codecForName("UTF-8"));
    // 判断文件是否存在
    if(QFile::exists(holeFileName)){// 文件存在，读出配置项
        // 这里的setting->value的第二参数，是配置项缺省值，即当读取的配置项不存在时，读取该值
        // User是配置组，name和age是配置项
        int number = setPtr->value("number/id", 0).toInt();
        SingleSizeShowWidget::getHoleData(number,setPtr, holes);
    }else {// 文件不存在，写入配置项，生成配置文件
         qDebug()<<holeFileName<<"文件不存在！";
    }

    QString menjiaFileName = QCoreApplication::applicationDirPath() + "/menjia.ini";
    std::shared_ptr<QSettings> MJsetPtr = std::make_shared<QSettings>(menjiaFileName , QSettings::IniFormat);
    //设置文件编码，配置文件中使用中文时，这是必须的，否则乱码
    MJsetPtr->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(QFile::exists(menjiaFileName)) {
        int number2= MJsetPtr->value("number/id", 0).toInt();
        SingleSizeShowWidget::getMenjiaData(number2,MJsetPtr,menjias);
    } else {
        qDebug()<<menjiaFileName<<"文件不存在！";
    }
}


void SingleSizeShowWidget::getHoleData(int number, std::shared_ptr<QSettings>setPtr, std::vector<holeData>& holes)
{
    for (int i =0; i < number; ++i) {
        holeData data;
        QString keyName = "d"+QString::number(i);
        data.length = setPtr->value("length/"+keyName).toDouble();
        QString keyXName = "x"+QString::number(i);
        data.x = setPtr->value("x/"+keyXName).toDouble();
        QString keyYName = "y"+QString::number(i);
        data.y = setPtr->value("y/"+keyYName).toDouble();
        holes.push_back(data);
    }
}

void SingleSizeShowWidget::getMenjiaData(int number, std::shared_ptr<QSettings>setPtr, std::vector<menjiaData>& menjias)
{
    for(int i=0; i < number; ++i) {
        menjiaData data;
        QString keyXName = "x"+QString::number(i);
        data.x = setPtr->value("x/"+keyXName).toDouble();
        QString keyYName = "y"+QString::number(i);
        data.y = setPtr->value("y/"+keyYName).toDouble();
        menjias.push_back(data);
    }
}

bool SingleSizeShowWidget::matchHoleMode(QString holesHeight, QString holesWidth, QString distanceHorizontal,QString distanceVertical)
{
   bool result = false;
   double height = holesHeight.toDouble();
   double width = holesWidth.toDouble();
   double dd = (height + width) / 2 ;
   double x = distanceHorizontal.toDouble();//x距离横边的最近距离，比如上横边100，下横边900，则算法取值100
   double y = distanceVertical.toDouble();//y距离竖边的最近距离，比如上横边100，下横边900，则算法取值100
   for(int i=0; i< (int)holes.size(); ++i) {
       holeData item = holes[i];
       if (dd <= (item.length + MATCH_ERROR) && dd >= (item.length - MATCH_ERROR)) {
           if(x <= (item.x + MATCH_ERROR) && x >= (item.x - MATCH_ERROR)) {
               if(y <= (item.y + MATCH_ERROR) && y >= (item.y - MATCH_ERROR)) {
                   return true;
               }
           }
        }
   }
   return result;
}

bool SingleSizeShowWidget::matchMenjiaMode(QString distanceHorizontal,QString distanceVertical)
{
    bool result = false;
    double x = distanceHorizontal.toDouble();//x距离横边的最近距离，比如上横边100，下横边900，则算法取值100
    double y = distanceVertical.toDouble();//y距离竖边的最近距离，比如上横边100，下横边900，则算法取值100
    for(int i=0; i< (int)menjias.size(); ++i) {
        menjiaData item = menjias[i];
        if(x <= (item.x + MATCH_ERROR) && x >= (item.x - MATCH_ERROR)) {
             if(y <= (item.y + MATCH_ERROR) && y >= (item.y - MATCH_ERROR)) {
                 return true;
             }
        }
    }
    return result;
}

void SingleSizeShowWidget::slot_refreshSize(QString jsonFilePath, int glassid)
{
    Global::glassidToholejson[glassid] = jsonFilePath; //存储glassid到jsonFullPath
    GlassID = glassid;
    jsonFileName = jsonFilePath;
    //
    // 将文件中已有的数据读出来
    //
    Json::Value root;
    QFile filer(jsonFilePath);
    qDebug()<<"jsonFullPath  = "<<jsonFilePath;
    if (filer.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFilePath.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<__FUNCTION__<<" ifs.is_open() =  false";
        }
    } else {
        qDebug()<<__FUNCTION__<<jsonFilePath<<" is not exit.";
    }
    if(!root.empty()) {
        Json::Value holes = root[QString::number(glassid).toStdString().c_str()];
        int count = holes.size() - 4; //减去角度、长度、宽度、轮廓图路径
        ui->tableWidget->setRowCount(count);
        for (int i = 0; i < count; i++) {
            Json::Value hole = holes[QString::number(i).toStdString().c_str()];
            // 序号
            QString HolesID = QString::number(hole["HolesID"].asInt());
            QTableWidgetItem* item0 = new QTableWidgetItem(HolesID);
            item0->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 0, item0);
            // 时间
            QString Time = hole["Time"].asString().data();
            QTableWidgetItem* item1 = new QTableWidgetItem(Time);
            item1->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 1, item1);
            // 类型
            QString Type = hole["Type"].asString().data();
            QTableWidgetItem* item2 = new QTableWidgetItem(Type);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 2, item2);
            // 长X
            QString HolesHeight = QString::number(hole["HolesHeight"].asDouble(),'f', 2);
            QTableWidgetItem* item4 = new QTableWidgetItem(HolesHeight);
            item4->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 4, item4);
            // 宽Y
            QString HolesWidth = QString::number(hole["HolesWidth"].asDouble(),'f', 2);
            QTableWidgetItem* item5 = new QTableWidgetItem(HolesWidth);
            item5->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 5, item5);
            // 边距X
            QString DistanceHorizontal = QString::number(hole["DistanceHorizontal"].asDouble(),'f', 2);
            QTableWidgetItem* item6 = new QTableWidgetItem(DistanceHorizontal);
            item6->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 6, item6);
            // 边距Y
            QString DistanceVertical = QString::number(hole["DistanceVertical"].asDouble(),'f', 2);
            QTableWidgetItem* item7 = new QTableWidgetItem(DistanceVertical);
            item7->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 7, item7);

            //比较孔洞
            QString HolesLeve = hole["HolesLeve"].asString().data();
            if (HolesLeve == "OK") {
                  if(Type == "孔") {
                      if(SingleSizeShowWidget::matchHoleMode(HolesHeight,HolesWidth,DistanceHorizontal,DistanceVertical) == false) {
                          qDebug()<<"NG:=>"<<"HolesHeight="<<HolesHeight<<",HolesWidth="<<HolesWidth<<",DistanceHorizontal="<<DistanceHorizontal<<",DistanceVertical="<<DistanceVertical;
                          HolesLeve = "NG";
                      }
                  } else if(Type == "门夹"){
                      if(SingleSizeShowWidget::matchMenjiaMode(DistanceHorizontal,DistanceVertical) == false) {
                          qDebug()<<"NG:=>"<<"DistanceHorizontal="<<DistanceHorizontal<<",DistanceVertical="<<DistanceVertical;
                          HolesLeve = "NG";
                      }
                  }
            }

            QTableWidgetItem* item3 = new QTableWidgetItem(HolesLeve);
            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 3, item3);
        }
        //显示孔洞小图
        if (nullptr != ui->tableWidget->item(0, 0)) {
            Json::Value firsthole = holes[QString::number(0).toStdString().c_str()];
            QString ImageHolesPath = firsthole["ImageHolesPath"].asString().data() + QString("/0.jpg");
            qDebug() << "ImageHolesPath = " << ImageHolesPath;
            QImage img2(ImageHolesPath);
            loadedPixmapItem2->loadImage(img2);
            int nwidth = ui->graphicsView_2->width(), nheight = ui->graphicsView_2->height();
            loadedPixmapItem2->setQGraphicsViewWH(nwidth, nheight);
            ui->graphicsView_2->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
        }
        //显示轮廓图
        if(loadedPixmapItem != nullptr){
            QString ImageHolesLinePath = holes["ImageHolesLinePath"].asString().data() ;
            qDebug() << "ImageHolesLinePath = " << ImageHolesLinePath;
            QImage img1(ImageHolesLinePath);
            loadedPixmapItem->loadImage(img1);
            int nwidth = ui->graphicsView->width(), nheight = ui->graphicsView->height();
            loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
            ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
        }
    }
}

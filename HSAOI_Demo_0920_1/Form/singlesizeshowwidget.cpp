#include "SingleSizeShowWidget.h"
#include <QDebug>
#include <QDir>
#include "ui_SingleSizeShowWidget.h"
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

    connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this,
            SLOT(slot_onItemDoubleClicked(QTableWidgetItem*)));
    connect(ui->tableWidget, &QTableWidget::itemDoubleClicked, this,
            &SingleSizeShowWidget::slot_showSizeSmallImage);


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

void SingleSizeShowWidget::slot_RecieveID(QString IDandDate) {

  GlassID = IDandDate.split(".")[0];
  if(LastGlassID!=GlassID) {
      LastGlassID=GlassID;
      Date = IDandDate.split(".")[1];
      fileName = "HolesInfJson/" + Date + ".json";
      JSONRECIPE = new JsonParse2Map(fileName);

      slot_showSizeDiagramImage();

      int count = JSONRECIPE->CountValuesUnderKey(GlassID);
      ui->tableWidget->setRowCount(count);
      for (int i = 1; i <= count; i++) {
          QString HolesID, Time, Type, HolesLeve, HolesHeight, HolesWidth, DistanceHorizontal, DistanceVertical;

          JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".HolesID",HolesID);
          QTableWidgetItem* item0 = new QTableWidgetItem(HolesID);
          item0->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget->setItem(i - 1, 0, item0);

          JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".Time",Time);
          QTableWidgetItem* item1 = new QTableWidgetItem(Time);
          item1->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget->setItem(i - 1, 1, item1);

          JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".Type",Type);
          QTableWidgetItem* item2 = new QTableWidgetItem(Type);
          item2->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget->setItem(i - 1, 2, item2);

//          JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".HolesLeve",HolesLeve);
//          QTableWidgetItem* item3 = new QTableWidgetItem(HolesLeve);
//          item3->setTextAlignment(Qt::AlignCenter);
//          ui->tableWidget->setItem(i - 1, 3, item3);

          JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".HolesHeight", HolesHeight);
          QTableWidgetItem* item4 = new QTableWidgetItem(HolesHeight);
          item4->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget->setItem(i - 1, 4, item4);

          JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".HolesWidth", HolesWidth);
          QTableWidgetItem* item5 = new QTableWidgetItem(HolesWidth);
          item5->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget->setItem(i - 1, 5, item5);

          JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".DistanceHorizontal",DistanceHorizontal);
          QTableWidgetItem* item6 = new QTableWidgetItem(DistanceHorizontal);
          item6->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget->setItem(i - 1, 6, item6);

          JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".DistanceVertical",DistanceVertical);
          QTableWidgetItem* item7 = new QTableWidgetItem(DistanceVertical);
          item7->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget->setItem(i - 1, 7, item7);

          //比较孔洞
          JSONRECIPE->getParameter(GlassID + "." + QString::number(i) + ".HolesLeve",HolesLeve);
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
void SingleSizeShowWidget::slot_showSizeSmallImage(QTableWidgetItem *item)
{
    if (item) {
      int row = item->row();
      QString itemID = ui->tableWidget->item(row, 0)->text();
      JSONRECIPE = new JsonParse2Map(fileName);
      QString ImageHolesPath;
      JSONRECIPE->getParameter(
          GlassID + "." + QString::number(row + 1) + ".ImageHolesPath", ImageHolesPath);
      ImageHolesPath = ImageHolesPath.replace(QChar(0x202A), "");
      qDebug() << "ImageHolesPath = " << ImageHolesPath;
      QDir dir;
      QString strpath;
      dir.setPath(ImageHolesPath);
      QFileInfoList infolist = dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
//      foreach(const QFileInfo &info, infolist)
//      {
//          strpath += info.absoluteFilePath() + "_";
//      }
//      qDebug() << strpath << strpath.split("_")[0] << strpath.split("_")[1] << strpath.split("_")[2];
//      QPixmap pixmap2(strpath.split("_")[row]);
//      ui->label_2->setPixmap(pixmap2.scaled(310, 310));
//      ui->label_2->setFixedSize(320, 320);
      QString path2 = ImageHolesPath + "/" +QString::number(row);
      //QImage img2(strpath.split("_")[row]);
      QImage img2(path2);
      loadedPixmapItem2->loadImage(img2);
      int nwidth = ui->graphicsView_2->width(), nheight = ui->graphicsView_2->height();
      loadedPixmapItem2->setQGraphicsViewWH(nwidth, nheight);
      ui->graphicsView_2->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
    }
}

void SingleSizeShowWidget::slot_showSizeDiagramImage()
{
    QString ImageHolesLinePath;
    JSONRECIPE->getParameter(
        GlassID + ".ImageHolesLinePath", ImageHolesLinePath);
    ImageHolesLinePath = ImageHolesLinePath.replace(QChar(0x202A), "");
    qDebug() << "ImageHolesLinePath = " << ImageHolesLinePath;
//    QPixmap pixmap1(ImageHolesLinePath + "/1.jpg");
//    ui->label->setPixmap(pixmap1.scaled(630, 310));
//    ui->label->setScaledContents(true);
//    ui->label->setFixedSize(640, 320);
    QImage img1(ImageHolesLinePath + "/1.jpg");
    loadedPixmapItem->loadImage(img1);
    int nwidth = ui->graphicsView->width(), nheight = ui->graphicsView->height();
    loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
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


/*******************************************
    @ClassName   : SingleFlawShowWidget
    @Description : Description
    @Creator     : Zhangjun
    @Author      : Zhangjun
    @Date        : 2023-09-01
********************************************/
#ifndef SINGLEFLAWSHOWWIDGET_H
#define SINGLEFLAWSHOWWIDGET_H

#include <Parameter/JsonParse2Map.h>
#include <QDate>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QWidget>
#include "Form/glassstatictablewidget.h"
#include<Form/FlawShowWidget.h>
#include<QPushButton>
#include<Camera/DushenSample/MyGraphicsitem.h>
#include<QGraphicsScene>
#include <unordered_map>
#include <utility>


namespace Ui {
class SingleFlawShowWidget;
}

class SingleFlawShowWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SingleFlawShowWidget(Qt::Orientation ori,
                                Qt::Orientation pic_ori,
                                QWidget* parent = 0);
  ~SingleFlawShowWidget();

 signals:
      void sig_paintFlawPoint(QString x, QString y);
      void sig_test();
 private:
  JsonParse2Map* JSONRECIPE;

  QString jsonFileName;
  int GlassID;
  QString Date;
  int LastGlassID;

 public:
  void initLayout();
  QString _selectedDir;
  void PickerCheckData(const FlawPoint& flawpoint);

 public slots:
  void showFlawImage(QTableWidgetItem* item);

  void onItemDoubleClicked(QTableWidgetItem*);

  void slot_RecieveID(QString jsonFullPath, int glassid);


  void slot_FlawTrack(QTableWidgetItem* item);
   void slot_ButtonExportClicked();

    void slot_refrshFlaw(QString jsonFullPath,int glassid);

private:
  Ui::SingleFlawShowWidget* ui;
  Qt::Orientation m_orientation;
  Qt::Orientation m_pic_orientation;

  MyGraphicsItem* loadedPixmapItem;
  QGraphicsScene* scene;
  MyGraphicsItem* loadedPixmapItem2;
  QGraphicsScene* scene2;
  MyGraphicsItem* loadedPixmapItem3;
  QGraphicsScene* scene3;
  std::unordered_map<int,std::pair<QString,QString>> rowMapXY;
};

#endif  // SINGLEFLAWSHOWWIDGET_H

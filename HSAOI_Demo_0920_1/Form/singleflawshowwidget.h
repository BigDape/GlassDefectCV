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
 private:
  JsonParse2Map* JSONRECIPE;

  QString fileName;
  QString GlassID;
  QString Date;
  QString LastGlassID;

  bool insertStatus;
//  FlawShowWidget *flawshowWidget;


 public:
  void initLayout();
  QString _selectedDir;

 public slots:
  void showFlawImage(QTableWidgetItem* item);

  void onItemDoubleClicked(QTableWidgetItem*);

  void slot_RecieveID(QString);
  void slot_PickerCheckData(const FlawPoint&flawpoint);

  void slot_FlawTrack(QTableWidgetItem* item);
   void slot_ButtonExportClicked();

   void slot_refrshFlaw(QString glassid);

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
  std::vector<QString> singleFlawData;
};

#endif  // SINGLEFLAWSHOWWIDGET_H

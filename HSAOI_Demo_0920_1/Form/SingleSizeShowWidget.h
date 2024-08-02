﻿#ifndef SINGLESIZESHOWWIDGET_H
#define SINGLESIZESHOWWIDGET_H

#include <Parameter/JsonParse2Map.h>
#include <QDate>
#include <QLabel>
#include <QTableWidget>
#include <QWidget>
#include "Form/glassstatictablewidget.h"
#include<Form/FlawShowWidget.h>
#include<Camera/DushenSample/MyGraphicsitem.h>
#include<QGraphicsScene>
#include <QCoreApplication>
#include <QSettings>
#include <QTextCodec>
#include <QFile>
#include <QDebug>

struct holeData
{
    double length;
    double x;
    double y;
};

struct menjiaData
{
    double x;
    double y;
};

namespace Ui {
class SingleSizeShowWidget;
}

class SingleSizeShowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleSizeShowWidget(Qt::Orientation ori,
                                  Qt::Orientation pic_ori,
                                  QWidget *parent = 0);
    ~SingleSizeShowWidget();

    void initLayout();

    void onItemDoubleClicked(QTableWidgetItem *);

    void initMode();

    void getHoleData(int number, std::shared_ptr<QSettings>setPtr, std::vector<holeData>& holes);

    void getMenjiaData(int number, std::shared_ptr<QSettings>setPtr, std::vector<menjiaData>& menjias);

    bool matchHoleMode(QString holesHeight, QString holesWidth, QString distanceHorizontal,QString distanceVertical);

    bool matchMenjiaMode(QString distanceHorizontal,QString distanceVertica);

    void showSizeDiagramImage(QString jsonFullPath,int glassid);
public slots:
    void slot_RecieveID(QString jsonFullPath,int glassid);

    void slot_showSizeSmallImage(QTableWidgetItem* item);



    void slot_onItemDoubleClicked(QTableWidgetItem *);

    void slot_refreshSize(QString jsonFilePath, int glassid);
private:
    Ui::SingleSizeShowWidget *ui;
    Qt::Orientation m_orientation;
    Qt::Orientation m_pic_orientation;

    JsonParse2Map* JSONRECIPE;

    MyGraphicsItem* loadedPixmapItem;
    QGraphicsScene* scene;
    MyGraphicsItem* loadedPixmapItem2;
    QGraphicsScene* scene2;
    QString jsonFileName;  //json文件目录
    int GlassID;   //玻璃id
    QString Date;
    int LastGlassID; //玻璃id
    std::vector<holeData> holes;
    std::vector<menjiaData> menjias;
};

#endif // SINGLESIZESHOWWIDGET_H

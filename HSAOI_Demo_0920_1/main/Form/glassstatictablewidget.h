/*******************************************
    @ClassName   : GlassStatisticTableWidget
    @Description : Description
    @Creator     : Huxujie
    @Author      : Huxujie
    @Date        : 2023-09-01
********************************************/
#ifndef GLASSSTATICTABLEWIDGET_H
#define GLASSSTATICTABLEWIDGET_H

#include "Global.h"
#include <QDateTime>
#include <QFile>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>
#include <QXmlStreamReader>
#include <QtDebug>
#include "FlawDefine.h"

class GlassStatisticTableWidget : public QWidget {
    Q_OBJECT
public:
    explicit GlassStatisticTableWidget(QWidget* parent = 0);

public:
    QLabel* TableTitle;

    QTableWidget* tableWidget;

    JsonParse2Map* RECIPE;
    double length_err;

public:
    void InitTable(QTableWidget* tableWidget);
    void InitTableFromXml(QTableWidget* tableWidget);
public slots:
    void slot_insertRowData(GlassDataBaseInfo info);
    void slot_clearRowData();
signals:
    void sig_reloadDefect(QString jsonFullPath,int glassid);
    void sig_reloadHole(QString jsonFullPath,int glassid);
};

#endif // GLASSSTATICTABLEWIDGET_H

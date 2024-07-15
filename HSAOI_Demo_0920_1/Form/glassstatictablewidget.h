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

class GlassStatisticTableWidget : public QWidget {
    Q_OBJECT
public:
    explicit GlassStatisticTableWidget(QWidget* parent = 0);

public:
    QLabel* TableTitle;

    QTableWidget* tableWidget;

    JsonParse2Map* RECIPE;
    double length_err;

private:
    int row = 0;

public:
    void InitTable(QTableWidget* tableWidget);
    void InitTableFromXml(QTableWidget* tableWidget);
public slots:
    void slot_insertRowData(GLASSINFO* info);
    void slot_clearRowData();
signals:
    void sig_DeliverGlassID(QString ID);
};

#endif // GLASSSTATICTABLEWIDGET_H

#include "glassstatictablewidget.h"
#include <QFile>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QXmlStreamReader>
#include "Global.h"
#pragma execution_character_set("utf-8")

GlassStatisticTableWidget::GlassStatisticTableWidget(QWidget* parent)
    : QWidget(parent)
{
    // 创建表格对象
    tableWidget = new QTableWidget(this);
    tableWidget->setGeometry(0, 30, 610, 500);

    QHBoxLayout* layout0 = new QHBoxLayout(this);
    this->setLayout(layout0);
    layout0->addWidget(tableWidget);

    //初始化表格
    InitTable(tableWidget);

    connect(tableWidget, &QTableWidget::itemDoubleClicked,
        [=](QTableWidgetItem* item) {
            // 获取所在行的第一列内容
            QString glassID = tableWidget->item(item->row(), 0)->text();
            QString jsonPath = Global::glassidTodefectjson[glassID.toInt()];
            qDebug() << __FUNCTION__ << "glassID = " <<glassID.toInt()  <<"jsonPath = "<<jsonPath;
            emit sig_reloadDefect(jsonPath, glassID.toInt());
            QString holejsonPath = Global::glassidToholejson[glassID.toInt()];
            emit sig_reloadHole(holejsonPath,glassID.toInt());
        });

}

// 设置表格表头
void GlassStatisticTableWidget::InitTable(QTableWidget* tableWidget)
{
    // 设置表头
    QStringList headerLabels;
    // QString::fromLocal8Bit不会乱码
    headerLabels << "ID"
                 << "时间"
                 << "OK/NG"
                 << "尺寸OK/NG"
                 << "长度"
                 << "宽度"
                 << "对角线1"
                 << "对角线2"
                 << "缺陷数量"
                 << "缺陷OK/NG"
                 << "划伤"
                 << "气泡"
                 << "结石"
                 << "崩边"
                 << "脏污"
                 << "裂纹"
                 << "其它";
    tableWidget->setColumnCount(headerLabels.size());
    tableWidget->setHorizontalHeaderLabels(headerLabels);

    tableWidget->setColumnWidth(0, 100);
    tableWidget->setColumnWidth(1, 200);
    tableWidget->setColumnWidth(2, 100);
    tableWidget->setColumnWidth(3, 100);
    tableWidget->setColumnWidth(4, 100);
    tableWidget->setColumnWidth(5, 100);
    tableWidget->setColumnWidth(6, 100);
    tableWidget->setColumnWidth(7, 100);
    tableWidget->setColumnWidth(8, 100);
    tableWidget->setColumnWidth(9, 100);
    tableWidget->setColumnWidth(10, 100);
    tableWidget->setColumnWidth(11, 100);
    tableWidget->setColumnWidth(12, 100);
    tableWidget->setColumnWidth(13, 100);
    tableWidget->setColumnWidth(14, 100);
    tableWidget->setColumnWidth(15, 100);
    tableWidget->setColumnWidth(16, 100);
}

void GlassStatisticTableWidget::InitTableFromXml(QTableWidget* tableWidget)
{
    QString xmlFilePath = "file.xml";
    if (QFile::exists(xmlFilePath)) {
        QFile xmlFile(xmlFilePath);
        if (xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QXmlStreamReader xmlReader(&xmlFile);
            QStringList headers;
            int columnCount = 0;

            while (!xmlReader.atEnd()) {
                xmlReader.readNext();
                if (xmlReader.isStartElement() && xmlReader.name() == "Header") {
                    while (!xmlReader.atEnd() && !(xmlReader.isEndElement() && xmlReader.name() == "Header")) {
                        if (xmlReader.isStartElement() && xmlReader.name() == "Column") {
                            headers.append(xmlReader.readElementText());
                            columnCount++;
                        }
                        xmlReader.readNext();
                    }
                }
            }

            if (columnCount > 0) {
                tableWidget->setColumnCount(columnCount);
                tableWidget->setHorizontalHeaderLabels(headers);
            }
        }
    }
}

void GlassStatisticTableWidget::slot_insertRowData(GlassDataBaseInfo info)
{
    QTableWidgetItem *itemID = tableWidget->item(0, 0);
    // 同一块玻璃的多帧图片插入到表格的同一行
    if (itemID) {
       if(itemID->text().toInt() != info.id)
           tableWidget->insertRow(0);
    } else {
       tableWidget->insertRow(0);
    }
    //ID
    QTableWidgetItem* id = new QTableWidgetItem(QString::number(info.id));
    id->setTextAlignment(Qt::AlignCenter);
    id->setFlags(id->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 0, id);
    //时间
    QTableWidgetItem* time = new QTableWidgetItem(info.time);
    time->setTextAlignment(Qt::AlignCenter);
    time->setFlags(time->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 1, time);
    //OK/NG
    QTableWidgetItem* isok = new QTableWidgetItem(info.OKorNG);
    isok->setTextAlignment(Qt::AlignCenter);
    isok->setFlags(isok->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 2, isok);
    //尺寸OK/NG
    QTableWidgetItem* issizeok = new QTableWidgetItem(info.sizeOKorNG);
    issizeok->setTextAlignment(Qt::AlignCenter);
    issizeok->setFlags(issizeok->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 3, issizeok);
    RECIPE = new JsonParse2Map("Recipes/" + Global::CurrentRecipe + ".json");
    //长度
    QTableWidgetItem* length = new QTableWidgetItem(QString::number(info.width,'f', 2));//??这里为啥要对调
    length->setTextAlignment(Qt::AlignCenter);
    length->setFlags(length->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 4, length);
    //宽度
    QTableWidgetItem* width = new QTableWidgetItem(QString::number(info.length,'f', 2));//??这里为啥要对调
    width->setTextAlignment(Qt::AlignCenter);
    width->setFlags(width->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 5, width);
    //对角线1
    info.duijiaoxian1 = sqrt(pow(info.length,2) + pow(info.width,2));//对角线，todo
    QTableWidgetItem* diagonal1 = new QTableWidgetItem(QString::number(info.duijiaoxian1,'f', 2));
    diagonal1->setTextAlignment(Qt::AlignCenter);
    diagonal1->setFlags(diagonal1->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 6, diagonal1);
    //对角线2
    info.duijiaoxian2 = sqrt(pow(info.length,2) + pow(info.width,2));//对角线，todo
    QTableWidgetItem* diagonal2 = new QTableWidgetItem(QString::number(info.duijiaoxian2,'f', 2));
    diagonal2->setTextAlignment(Qt::AlignCenter);
    diagonal2->setFlags(diagonal2->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 7, diagonal2);
    //缺陷数量
    QTableWidgetItem* flawcount = new QTableWidgetItem(QString::number(info.defectNumber));
    flawcount->setTextAlignment(Qt::AlignCenter);
    flawcount->setFlags(flawcount->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 8, flawcount);
    //缺陷OK/NG
    QTableWidgetItem* isflawok = new QTableWidgetItem(info.defectOKorNG);
    isflawok->setTextAlignment(Qt::AlignCenter);
    isflawok->setFlags(isflawok->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 9, isflawok);
    //划伤
    QTableWidgetItem* flaw1 = new QTableWidgetItem(QString::number(info.huashanNumber));
    flaw1->setTextAlignment(Qt::AlignCenter);
    flaw1->setFlags(flaw1->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 10, flaw1);
    //气泡
    QTableWidgetItem* flaw2 = new QTableWidgetItem(QString::number(info.qipaoNumber));
    flaw2->setTextAlignment(Qt::AlignCenter);
    flaw2->setFlags(flaw2->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 11, flaw2);
    //结石
    QTableWidgetItem* flaw7 = new QTableWidgetItem(QString::number(info.jieshiNumber));
    flaw7->setTextAlignment(Qt::AlignCenter);
    flaw7->setFlags(flaw7->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 12, flaw7);
    //崩边
    QTableWidgetItem* flaw3 = new QTableWidgetItem(QString::number(info.benbianNumber));
    flaw3->setTextAlignment(Qt::AlignCenter);
    flaw3->setFlags(flaw3->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 13, flaw3);
    //脏污
    QTableWidgetItem* flaw4 = new QTableWidgetItem(QString::number(info.zanwuNumber));
    flaw4->setTextAlignment(Qt::AlignCenter);
    flaw4->setFlags(flaw4->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 14, flaw4);
    //裂纹
    QTableWidgetItem* flaw5 = new QTableWidgetItem(QString::number(info.liewenNumber));
    flaw5->setTextAlignment(Qt::AlignCenter);
    flaw5->setFlags(flaw5->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 15, flaw5);
    //其他
    QTableWidgetItem* flaw6 = new QTableWidgetItem(QString::number(info.qitaNumber));
    flaw6->setTextAlignment(Qt::AlignCenter);
    flaw6->setFlags(flaw6->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(0, 16, flaw6);

    // 设置表格内容居中显示
    for (int i = 0; i < tableWidget->columnCount(); ++i) {
        tableWidget->horizontalHeaderItem(i)->setTextAlignment(Qt::AlignCenter);
    }
    tableWidget->verticalHeader()->setVisible(false); // 隐藏行号
    qDebug()<<"123";
}

void GlassStatisticTableWidget::slot_clearRowData()
{
    tableWidget->clearContents();
}

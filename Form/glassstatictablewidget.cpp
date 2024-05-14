#include "glassstatictablewidget.h"
#include <QFile>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QXmlStreamReader>
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
            QString firstColumnContent = tableWidget->item(item->row(), 0)->text();
            QString SecondColumnContent = tableWidget->item(item->row(), 1)->text().left(13);
            QString Deliver = firstColumnContent + "." + SecondColumnContent;
            //            Deliver = "000001.2023-09-19";
            if (firstColumnContent != "")
                emit sig_DeliverGlassID(Deliver);
            qDebug() << Deliver;
            qDebug()<<"1111111111111111111111111111";
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

void GlassStatisticTableWidget::slot_insertRowData(GLASSINFO* info)
{
    QString glassid = info->GlassID;
    QTableWidgetItem *itemID = tableWidget->item(0, 0);
    if (itemID) {
       if(itemID->text()!=glassid)
           tableWidget->insertRow(0);
    } else {
       tableWidget->insertRow(0);
    }
    QTableWidgetItem* id = new QTableWidgetItem(glassid);
    //ID
    id->setTextAlignment(Qt::AlignCenter);
    id->setFlags(id->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 0, id);
    //时间
    QString datetime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    QTableWidgetItem* time = new QTableWidgetItem(datetime);
    time->setTextAlignment(Qt::AlignCenter);
    time->setFlags(time->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 1, time);
    //OK/NG
    QString glassisOK = info->isOK ? "OK" : "NG";
    QTableWidgetItem* isok = new QTableWidgetItem(glassisOK);
    if (!info->isOK)
        isok->setForeground(QColor(255, 0, 0));
    isok->setTextAlignment(Qt::AlignCenter);
    isok->setFlags(isok->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 2, isok);
    //尺寸OK/NG
    QString glassisSizeOK = info->isSizeOK ? "OK" : "NG";
    QTableWidgetItem* issizeok = new QTableWidgetItem(glassisSizeOK);
    if (!info->isSizeOK)
        issizeok->setForeground(QColor(255, 0, 0));
    issizeok->setTextAlignment(Qt::AlignCenter);
    issizeok->setFlags(issizeok->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 3, issizeok);

    RECIPE = new JsonParse2Map("Recipes/" + Global::CurrentRecipe + ".json");
    //长度
    double glassLength_temp = 0;
    if (qAbs(info->GlassWidth - Global::encodeRollerYLength) <= 100) {
        glassLength_temp = Global::encodeRollerYLength;
    } else {
        glassLength_temp = info->GlassWidth;
    }
    qDebug()<<"glassLength_temp"<<glassLength_temp;
    QString glasslength = QString::number(glassLength_temp,'f', 2);
    QTableWidgetItem* length = new QTableWidgetItem(glasslength);
    length->setTextAlignment(Qt::AlignCenter);
    length->setFlags(length->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 4, length);
    //宽度
    QString glasswidth = QString::number(info->GlassLength,'f', 2);
    QTableWidgetItem* width = new QTableWidgetItem(glasswidth);
    width->setTextAlignment(Qt::AlignCenter);
    width->setFlags(width->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 5, width);
    //对角线1
    info->Diagonal1 = sqrt(pow(info->GlassLength,2) + pow(glassLength_temp,2));//对角线，todo
    QString glassdiagonal1 = QString::number(info->Diagonal1,'f', 2);
    QTableWidgetItem* diagonal1 = new QTableWidgetItem(glassdiagonal1);
    diagonal1->setTextAlignment(Qt::AlignCenter);
    diagonal1->setFlags(diagonal1->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 6, diagonal1);
    //对角线2
    info->Diagonal2 = sqrt(pow(info->GlassLength,2) + pow(glassLength_temp,2));//对角线，todo
    QString glassdiagonal2 = QString::number(info->Diagonal2,'f', 2);
    QTableWidgetItem* diagonal2 = new QTableWidgetItem(glassdiagonal2);
    diagonal2->setTextAlignment(Qt::AlignCenter);
    diagonal2->setFlags(diagonal2->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 7, diagonal2);
    //缺陷数量
    QString glassFlawCount = QString::number(info->FlawCount);
    QTableWidgetItem* flawcount = new QTableWidgetItem(glassFlawCount);
    flawcount->setTextAlignment(Qt::AlignCenter);
    flawcount->setFlags(flawcount->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 8, flawcount);
    //缺陷OK/NG
    QString glassisFlawOK = info->isFlawOK ? "OK" : "NG";
    QTableWidgetItem* isflawok = new QTableWidgetItem(glassisFlawOK);
    if (!info->isFlawOK)
        isflawok->setForeground(QColor(255, 0, 0));
    isflawok->setTextAlignment(Qt::AlignCenter);
    isflawok->setFlags(isflawok->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 9, isflawok);
    //划伤
    QString glassFlaw1 = QString::number(info->Flaw1);
    QTableWidgetItem* flaw1 = new QTableWidgetItem(glassFlaw1);
    flaw1->setTextAlignment(Qt::AlignCenter);
    flaw1->setFlags(flaw1->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 10, flaw1);
    //气泡
    QString glassFlaw2 = QString::number(info->Flaw2);
    QTableWidgetItem* flaw2 = new QTableWidgetItem(glassFlaw2);
    flaw2->setTextAlignment(Qt::AlignCenter);
    flaw2->setFlags(flaw2->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 11, flaw2);
    //结石
    QString glassFlaw7 = QString::number(info->Flaw7);
    QTableWidgetItem* flaw7 = new QTableWidgetItem(glassFlaw7);
    flaw7->setTextAlignment(Qt::AlignCenter);
    flaw7->setFlags(flaw7->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 12, flaw7);
    //崩边
    QString glassFlaw3 = QString::number(info->Flaw3);
    QTableWidgetItem* flaw3 = new QTableWidgetItem(glassFlaw3);
    flaw3->setTextAlignment(Qt::AlignCenter);
    flaw3->setFlags(flaw3->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 13, flaw3);
    //脏污
    QString glassFlaw4 = QString::number(info->Flaw4);
    QTableWidgetItem* flaw4 = new QTableWidgetItem(glassFlaw4);
    flaw4->setTextAlignment(Qt::AlignCenter);
    flaw4->setFlags(flaw4->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 14, flaw4);
    //裂纹
    QString glassFlaw5 = QString::number(info->Flaw5);
    QTableWidgetItem* flaw5 = new QTableWidgetItem(glassFlaw5);
    flaw5->setTextAlignment(Qt::AlignCenter);
    flaw5->setFlags(flaw5->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 15, flaw5);
    //其他
    QString glassFlaw6 = QString::number(info->Flaw6);
    QTableWidgetItem* flaw6 = new QTableWidgetItem(glassFlaw6);
    flaw6->setTextAlignment(Qt::AlignCenter);
    flaw6->setFlags(flaw6->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 16, flaw6);


    // 设置表格内容居中显示
    for (int i = 0; i < tableWidget->columnCount(); ++i) {
        tableWidget->horizontalHeaderItem(i)->setTextAlignment(Qt::AlignCenter);
    }

    tableWidget->verticalHeader()->setVisible(false); // 隐藏行号
}

void GlassStatisticTableWidget::slot_clearRowData()
{
    tableWidget->clearContents();
}

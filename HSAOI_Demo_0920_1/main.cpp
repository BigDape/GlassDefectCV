#include "MainForm.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <stdlib.h>
//#include "Jianbo_db.h"
using namespace std;

#pragma execution_character_set("utf-8")

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    MainForm AppForm;
    AppForm.show();
    return a.exec();

//    std::shared_ptr<Jianbo_db> ptr = std::make_shared<Jianbo_db>();
//    ptr->openDataBase();
//    GlassDataBaseInfo data;
//    data.id = 11;
//    data.time = QString("2024-7-17-16-37");
//    data.OKorNG = QString("NG");
//    data.sizeOKorNG = QString("NG");
//    data.length = 1200.1;
//    data.width = 500.1;
//    data.duijiaoxian1 = 167.56;
//    data.duijiaoxian2 = 167.53;
//    data.defectNumber = 56;
//    data.defectOKorNG = QString("NG");
//    data.huashanNumber = 12;
//    data.qipaoNumber = 10;
//    data.jieshiNumber = 0;
//    data.benbianNumber =0;
//    data.zanwuNumber = 0;
//    data.liewenNumber = 0;
//    data.qitaNumber =19;
//    ptr->insertOneData(data);
//    GlassSizeInfo data2;
//    data2.id=1;
//    data2.sizeno = 1;
//    data2.time = "2024-8-19";
//    data2.sizeType = "孔";
//    data2.sizeLevel = "NG";
//    data2.lengthX = 123.56;
//    data2.widthY = 234.5;
//    data2.marginsX = 1234.56;
//    data2.marginsY = 2345.67;
//    data2.glassid = 1;
//    data2.imagePath = "D:/saveDefect/1.jpg";
//    ptr->insertOneData(data2);
//    GlassDefect data3;
//    data3.id = 1;
//    data3.defectId = 1;
//    data3.time = "2024-7-90";
//    data3.defectType = "划伤";
//    data3.defectLevel="NG";
//    data3.x = 120.23;
//    data3.y = 128.89;
//    data3.length = 123.334;
//    data3.width = 234.56;
//    data3.area = 120;
//    data3.glassid = 1;
//    data3.imagePath = "D:/saveDefect/2.jpg";
//    ptr->insertOneData(data3);
//    GlassDataBaseInfo data4;
//    data4.id = 11;
//    data4.time = QString("2024-7-17-16-37");
//    data4.OKorNG = QString("OK");
//    data4.sizeOKorNG = QString("OK");
//    data4.length = 1200.1;
//    data4.width = 500.1;
//    data4.duijiaoxian1 = 167.56;
//    data4.duijiaoxian2 = 167.53;
//    data4.defectNumber = 56;
//    data4.defectOKorNG = QString("OK");
//    data4.huashanNumber = 12;
//    data4.qipaoNumber = 10;
//    data4.jieshiNumber = 0;
//    data4.benbianNumber =0;
//    data4.zanwuNumber = 0;
//    data4.liewenNumber = 0;
//    data4.qitaNumber =19;
//    ptr->updateData(data4);
//    GlassSizeInfo data5;
//    data5.id=1;
//    data5.sizeno = 1;
//    data5.time = "2024-8-19";
//    data5.sizeType = "孔";
//    data5.sizeLevel = "OK";
//    data5.lengthX = 123.56;
//    data5.widthY = 234.5;
//    data5.marginsX = 1234.56;
//    data5.marginsY = 2345.67;
//    data5.glassid = 1;
//    data5.imagePath = "D:/saveDefect/1.jpg";
//    ptr->updateData(data5);
//    GlassDefect data6;
//    data6.id = 1;
//    data6.defectId = 1;
//    data6.time = "2024-7-90";
//    data6.defectType = "划伤";
//    data6.defectLevel="OK";
//    data6.x = 120.23;
//    data6.y = 128.89;
//    data6.length = 123.334;
//    data6.width = 234.56;
//    data6.area = 120;
//    data6.glassid = 1;
//    data6.imagePath = "D:/saveDefect/2.jpg";
//    ptr->updateData(data6);
////    ptr->deleteGlassTableData(data4.id);
////    ptr->deleteGlassSizeinfoData(data5.id);
////    ptr->deleteGlassDefectData(data6.id);
//    std::vector<GlassDataBaseInfo> datas;
//    QString querySql=QString("SELECT * FROM glass_table WHERE id = %1").arg(data4.id);
//    ptr->queryTableData(datas,querySql);
//    std::vector<GlassSizeInfo> datass;
//    QString querySql2=QString("SELECT * FROM glass_sizeinfo WHERE id = %1").arg(data5.id);
//    ptr->queryTableData(datass,querySql2);
//    std::vector<GlassDefect> datasss;
//    QString querySql3=QString("SELECT * FROM glass_defect WHERE id = %1").arg(data6.id);
//    ptr->queryTableData(datasss,querySql3);
//    ptr->closeDataBase();
}

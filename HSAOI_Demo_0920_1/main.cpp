#include "MainForm.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <stdlib.h>
//#include "Jianbo_db.h"

#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
using namespace std;
using namespace cv;
#pragma execution_character_set("utf-8")


#include<Windows.h>
#include<DbgHelp.h>
#pragma comment(lib,"DbgHelp.lib")
// 创建Dump文件
void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
{
    HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    // Dump信息
    MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
    dumpInfo.ExceptionPointers = pException;
    dumpInfo.ThreadId = GetCurrentThreadId();
    dumpInfo.ClientPointers = TRUE;
    // 写入Dump文件内容
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
    CloseHandle(hDumpFile);
}
// 处理Unhandled Exception的回调函数
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
    int processID = GetCurrentProcessId();
    QString dmpPath = "D:/" + QString::number(processID)+".dmp";
    qDebug()<<dmpPath;
    CreateDumpFile(dmpPath.toStdWString().data(),pException);
    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char* argv[])
{
    //注册异常处理函数,使用VS打开D盘的dmp文件，查看崩溃在哪一行
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    QApplication a(argc, argv);
    MainForm AppForm;
    AppForm.show();
    return a.exec();

//    Jianbo_db::GetInstance()->openDataBase();
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
//    Jianbo_db::GetInstance()->insertOneData(data);
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
//    Jianbo_db::GetInstance()->insertOneData(data2);
//    Jianbo_db::GetInstance()->insertOneData(data2);
//    Jianbo_db::GetInstance()->insertOneData(data2);
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
//    Jianbo_db::GetInstance()->insertOneData(data3);
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
//    Jianbo_db::GetInstance()->updateData(data4);
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
//    Jianbo_db::GetInstance()->updateData(data5);
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
//    Jianbo_db::GetInstance()->updateData(data6);
////    ptr->deleteGlassTableData(data4.id);
////    ptr->deleteGlassSizeinfoData(data5.id);
////    ptr->deleteGlassDefectData(data6.id);
//    std::vector<GlassDataBaseInfo> datas;
//    QString querySql=QString("SELECT * FROM glass_table WHERE id = %1").arg(data4.id);
//    Jianbo_db::GetInstance()->queryTableData(datas,querySql);
//    std::vector<GlassSizeInfo> datass;
//    QString querySql2=QString("SELECT * FROM glass_sizeinfo WHERE id = %1").arg(data5.id);
//    Jianbo_db::GetInstance()->queryTableData(datass,querySql2);
//    std::vector<GlassDefect> datasss;
//    QString querySql3=QString("SELECT * FROM glass_defect WHERE id = %1").arg(data6.id);
//    Jianbo_db::GetInstance()->queryTableData(datasss,querySql3);
//    Jianbo_db::GetInstance()->closeDataBase();
}

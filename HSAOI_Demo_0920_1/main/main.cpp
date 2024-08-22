#include "MainForm.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <log.h>
#include <database.h>

using namespace std;

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
    Log ab;
    DataBase::GetInstance();
    //注册异常处理函数,使用VS打开D盘的dmp文件，查看崩溃在哪一行
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    QApplication a(argc, argv);
    MainForm AppForm;
    AppForm.show();
   return a.exec();
}

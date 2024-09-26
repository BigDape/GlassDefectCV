#include <QApplication>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <QDebug>
#include <QDir>
#include <QTranslator>
#include <QObject>
#include "Form/Login.h"
#include "MainForm.h"
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
    // 加载国际化翻译
    QString path = QDir::currentPath() + "/../HSAOI_Demo_0920_1/HSAOI_zh_CN.qm";
    qDebug()<<"path = "<<path;
    QTranslator translator;
    if (translator.load(path)) {
        qDebug()<<"加载翻译文件";
        a.installTranslator(&translator);
    }
    // 登录成功后加载主界面
    Login w;
    MainForm AppForm;
    QObject::connect(&w,SIGNAL(LoginSuccessSignal()),&AppForm, SLOT(showWindows()));
    w.show();
    return a.exec();
}

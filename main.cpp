#include "MainForm.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

#pragma execution_character_set("utf-8")

int main(int argc, char* argv[])
{
#ifndef MY_MACRO
    QApplication a(argc, argv);
    MainForm AppForm;
    AppForm.show();
    return a.exec();
#else
    qDebug()<<"unit test";
#endif
}

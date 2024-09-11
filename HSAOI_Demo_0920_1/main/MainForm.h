#ifndef MAINFORM_H
#define MAINFORM_H

#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include <QAction>
#include "mainwindow.h"
#include "Form/TitleBar.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget* parent = nullptr);
    ~MainForm();

private:
    Ui::MainForm* ui;
    QVBoxLayout* vbox;
    MainWindow* main_window;
    TitleBar* title_bar;

    QAction* m_pExit;           //退出按钮
    QAction* m_pSettings;       //设置按钮
    QAction* m_pStart;          //开始按钮
    QAction* m_pStop;           //停止按钮
    QAction* m_pCameraSettings; //相机按钮
    QAction* m_pRunningInfo;    //日志按钮
    QAction* m_pDB;             //数据分析按钮
    QAction* m_offline;         //离线模式

    QLabel *m_CurrentRecipeLabel;
private slots:
    void slot_tt();
};

#endif // MAINFORM_H

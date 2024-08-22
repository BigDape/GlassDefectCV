/*******************************************
    @ClassName   : MainForm
    @Description : 程序主窗口，其中会包含原mainwindow
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-15
********************************************/
#ifndef MAINFORM_H
#define MAINFORM_H

#include "Form/TitleBar.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include<QTimer>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget {
    Q_OBJECT

public:
    explicit MainForm(QWidget* parent = nullptr);
    ~MainForm();

    QLabel *m_CurrentRecipeLabel;
    QTimer*timer;


private:
    Ui::MainForm* ui;
    QVBoxLayout* vbox;
    MainWindow* main_window;
    TitleBar* title_bar;
private slots:
    void slot_tt();
};

#endif // MAINFORM_H

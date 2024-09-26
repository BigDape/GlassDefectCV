#include "MainForm.h"
#include "Global.h"
#include "ui_MainForm.h"
#include <QLabel>
#include <QDesktopWidget>

#pragma execution_character_set("utf-8")

#define TITLEBAR_HEIGHT 40

MainForm::MainForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);


}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::showWindows()
{
    // 商标
    QLabel *m_pIconLabel = new QLabel(this);
    m_pIconLabel->setFixedSize(300, 56);
    m_pIconLabel->setPixmap(QPixmap(":/toolbar/icons/hs.png"));
    m_pIconLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    // 标题
    QLabel* m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setFixedSize(300,56);
    m_pTitleLabel->setText("皓视在线缺陷检测");
    m_pTitleLabel->setStyleSheet("font: 75 24pt \"微软雅黑\"; color: rgb(0, 0, 200);");
    m_pTitleLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    m_pTitleLabel->move(800,0);
    // 获取主界面的大小
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();
    qDebug()<<screenWidth<<","<<screenHeight;
    // 主界面
    main_window = new MainWindow(this);
    main_window->move(0,56);
    QWidget::showFullScreen();
}

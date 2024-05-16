#include "MainForm.h"
#include "Global.h"
#include "ui_MainForm.h"
#pragma execution_character_set("utf-8")
MainForm::MainForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);

    vbox = new QVBoxLayout();
    setLayout(vbox);
    log_singleton::CreateWidget0();
    Global::InitGlobalParam();
    title_bar = new TitleBar(this);
    main_window = new MainWindow(this);

    QLabel *m_pIconLabel = new QLabel(this);
    m_pIconLabel->setFixedSize(300, 56);
    m_pIconLabel->setPixmap(QPixmap(":/toolbar/icons/datuo.png"));
    m_CurrentRecipeLabel = new QLabel(this);
    m_CurrentRecipeLabel->setGeometry(1650,0,300,56);
    m_CurrentRecipeLabel->setFixedSize(300, 56);
    QFont ft;
    ft.setPointSize(12);
    m_CurrentRecipeLabel->setFont(ft);

    timer=new QTimer();
    timer->setInterval(1000);
    connect(timer,&QTimer::timeout,this,&MainForm::slot_tt);
    timer->start();

    vbox->addWidget(title_bar);
    vbox->addWidget(main_window);

    //QWidget::showFullScreen();
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::slot_tt()
{
    QString recipeName=Global::CurrentRecipe;
    m_CurrentRecipeLabel->setText("当前配方："+recipeName);
}

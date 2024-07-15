#include "TitleBar.h"
#include "Global.h"
#include <QHBoxLayout>
#pragma execution_character_set("utf-8")

#define TITLEBAR_HEIGHT 40

TitleBar::TitleBar(QWidget* parent)
    : QWidget(parent)
{
    setFixedHeight(TITLEBAR_HEIGHT);
    int button_size = TITLEBAR_HEIGHT - 5;
    int icon_size = button_size - 10;

    m_pTitleLabel = std::make_shared<QLabel>(this);
    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pTitleLabel->setText(PARAM.getSystemName());
    m_pTitleLabel->setStyleSheet("font: 75 24pt \"微软雅黑\"; color: rgb(0, 0, 200);");

    m_pIconLabel = std::make_shared<QLabel>(this);
    m_pIconLabel->setFixedSize(300, 56);
    m_pIconLabel->setPixmap(QPixmap(":/toolbar/icons/datuo.png"));
    m_CurrentRecipeLabel = std::make_shared<QLabel>(this);
    m_CurrentRecipeLabel->setGeometry(1650,0,300,56);
    m_CurrentRecipeLabel->setFixedSize(300, 56);
    QFont ft;
    ft.setPointSize(12);
    m_CurrentRecipeLabel->setFont(ft);
    m_CurrentRecipeLabel->setText("当前配方："+PARAM.getCurrentRecipe());//PARAM.getCurrentRecipe()


    QHBoxLayout* layout1 = new QHBoxLayout(this);
    layout1->addWidget(m_pIconLabel.get());
    layout1->addWidget(m_pTitleLabel.get());
    layout1->addWidget(m_CurrentRecipeLabel.get());
    layout1->setAlignment(m_pIconLabel.get(), Qt::AlignLeft);
    layout1->setAlignment(m_pTitleLabel.get(), Qt::AlignCenter);
    layout1->setAlignment(m_CurrentRecipeLabel.get(), Qt::AlignRight);
    layout1->setMargin(0); //将布局放到左上角0*0的位置处
}

// 更新工单名称
void TitleBar::slotUpdateRecipe(QString name)
{
    if (m_CurrentRecipeLabel != nullptr) {
        m_CurrentRecipeLabel->setText("当前配方："+PARAM.getCurrentRecipe());
    }
}

// 更新系统名称
void TitleBar::slotUpdateSystem(QString name)
{
    if ( m_pTitleLabel != nullptr) {
         m_pTitleLabel->setText(PARAM.getSystemName());
    }
}


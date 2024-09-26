/********************************************************************************
** Form generated from reading UI file 'JsonRecipeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JSONRECIPEWIDGET_H
#define UI_JSONRECIPEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JsonRecipeWidget
{
public:
    QWidget *gridLayoutWidget_4;
    QGridLayout *Layout_bottom;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *Layout_head;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *Layout_btns;
    QWidget *gridLayoutWidget_2;
    QGridLayout *Layout_table;

    void setupUi(QWidget *JsonRecipeWidget)
    {
        if (JsonRecipeWidget->objectName().isEmpty())
            JsonRecipeWidget->setObjectName(QString::fromUtf8("JsonRecipeWidget"));
        JsonRecipeWidget->resize(520, 640);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(JsonRecipeWidget->sizePolicy().hasHeightForWidth());
        JsonRecipeWidget->setSizePolicy(sizePolicy);
        JsonRecipeWidget->setMinimumSize(QSize(520, 640));
        JsonRecipeWidget->setMaximumSize(QSize(520, 640));
        gridLayoutWidget_4 = new QWidget(JsonRecipeWidget);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(0, 600, 521, 41));
        Layout_bottom = new QGridLayout(gridLayoutWidget_4);
        Layout_bottom->setObjectName(QString::fromUtf8("Layout_bottom"));
        Layout_bottom->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget = new QWidget(JsonRecipeWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 521, 31));
        Layout_head = new QHBoxLayout(horizontalLayoutWidget);
        Layout_head->setObjectName(QString::fromUtf8("Layout_head"));
        Layout_head->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget = new QWidget(JsonRecipeWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(410, 30, 111, 571));
        Layout_btns = new QVBoxLayout(verticalLayoutWidget);
        Layout_btns->setObjectName(QString::fromUtf8("Layout_btns"));
        Layout_btns->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_2 = new QWidget(JsonRecipeWidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 30, 411, 571));
        Layout_table = new QGridLayout(gridLayoutWidget_2);
        Layout_table->setObjectName(QString::fromUtf8("Layout_table"));
        Layout_table->setContentsMargins(0, 0, 0, 0);

        retranslateUi(JsonRecipeWidget);

        QMetaObject::connectSlotsByName(JsonRecipeWidget);
    } // setupUi

    void retranslateUi(QWidget *JsonRecipeWidget)
    {
        JsonRecipeWidget->setWindowTitle(QCoreApplication::translate("JsonRecipeWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JsonRecipeWidget: public Ui_JsonRecipeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JSONRECIPEWIDGET_H

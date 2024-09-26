/********************************************************************************
** Form generated from reading UI file 'msvlcdnumclockwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSVLCDNUMCLOCKWIDGET_H
#define UI_MSVLCDNUMCLOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MsvLCDNumClockWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget_show;
    QLabel *label_day;
    QLabel *label_date;
    QLabel *label_time;

    void setupUi(QWidget *MsvLCDNumClockWidget)
    {
        if (MsvLCDNumClockWidget->objectName().isEmpty())
            MsvLCDNumClockWidget->setObjectName(QString::fromUtf8("MsvLCDNumClockWidget"));
        MsvLCDNumClockWidget->resize(472, 253);
        MsvLCDNumClockWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        horizontalLayout = new QHBoxLayout(MsvLCDNumClockWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget_show = new QWidget(MsvLCDNumClockWidget);
        widget_show->setObjectName(QString::fromUtf8("widget_show"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_show->sizePolicy().hasHeightForWidth());
        widget_show->setSizePolicy(sizePolicy);
        widget_show->setMinimumSize(QSize(300, 160));
        label_day = new QLabel(widget_show);
        label_day->setObjectName(QString::fromUtf8("label_day"));
        label_day->setGeometry(QRect(20, 10, 101, 31));
        label_day->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));
        label_date = new QLabel(widget_show);
        label_date->setObjectName(QString::fromUtf8("label_date"));
        label_date->setGeometry(QRect(150, 10, 141, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        label_date->setFont(font);
        label_date->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));
        label_time = new QLabel(widget_show);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(30, 60, 241, 91));
        label_time->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        horizontalLayout->addWidget(widget_show);


        retranslateUi(MsvLCDNumClockWidget);

        QMetaObject::connectSlotsByName(MsvLCDNumClockWidget);
    } // setupUi

    void retranslateUi(QWidget *MsvLCDNumClockWidget)
    {
        MsvLCDNumClockWidget->setWindowTitle(QCoreApplication::translate("MsvLCDNumClockWidget", "Form", nullptr));
        label_day->setText(QCoreApplication::translate("MsvLCDNumClockWidget", "TextLabel", nullptr));
        label_date->setText(QCoreApplication::translate("MsvLCDNumClockWidget", "TextLabel", nullptr));
        label_time->setText(QCoreApplication::translate("MsvLCDNumClockWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MsvLCDNumClockWidget: public Ui_MsvLCDNumClockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSVLCDNUMCLOCKWIDGET_H

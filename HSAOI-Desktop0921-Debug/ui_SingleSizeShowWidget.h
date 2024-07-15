/********************************************************************************
** Form generated from reading UI file 'SingleSizeShowWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLESIZESHOWWIDGET_H
#define UI_SINGLESIZESHOWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleSizeShowWidget
{
public:
    QLabel *label_6;
    QLabel *label_7;
    QTableWidget *tableWidget;
    QLabel *label;
    QLabel *label_2;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;

    void setupUi(QWidget *SingleSizeShowWidget)
    {
        if (SingleSizeShowWidget->objectName().isEmpty())
            SingleSizeShowWidget->setObjectName(QString::fromUtf8("SingleSizeShowWidget"));
        SingleSizeShowWidget->resize(1804, 453);
        label_6 = new QLabel(SingleSizeShowWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(670, 40, 54, 12));
        label_7 = new QLabel(SingleSizeShowWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 40, 54, 12));
        tableWidget = new QTableWidget(SingleSizeShowWidget);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEnabled(true);
        tableWidget->setGeometry(QRect(990, 60, 811, 341));
        label = new QLabel(SingleSizeShowWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 60, 54, 12));
        label_2 = new QLabel(SingleSizeShowWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(670, 60, 54, 12));
        graphicsView = new QGraphicsView(SingleSizeShowWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(30, 80, 601, 281));
        graphicsView_2 = new QGraphicsView(SingleSizeShowWidget);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(670, 80, 291, 281));

        retranslateUi(SingleSizeShowWidget);

        QMetaObject::connectSlotsByName(SingleSizeShowWidget);
    } // setupUi

    void retranslateUi(QWidget *SingleSizeShowWidget)
    {
        SingleSizeShowWidget->setWindowTitle(QCoreApplication::translate("SingleSizeShowWidget", "Form", nullptr));
        label_6->setText(QCoreApplication::translate("SingleSizeShowWidget", "\345\205\211\345\234\272", nullptr));
        label_7->setText(QCoreApplication::translate("SingleSizeShowWidget", "\344\272\247\345\223\201\350\275\256\345\273\223", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SingleSizeShowWidget", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SingleSizeShowWidget", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SingleSizeShowWidget", "\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SingleSizeShowWidget", "\347\255\211\347\272\247", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SingleSizeShowWidget", "\351\225\277X (mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SingleSizeShowWidget", "\345\256\275Y (mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SingleSizeShowWidget", "\350\276\271\350\267\235X (mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SingleSizeShowWidget", "\350\276\271\350\267\235Y (mm)", nullptr));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SingleSizeShowWidget: public Ui_SingleSizeShowWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLESIZESHOWWIDGET_H

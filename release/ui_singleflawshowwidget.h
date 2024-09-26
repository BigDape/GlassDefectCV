/********************************************************************************
** Form generated from reading UI file 'singleflawshowwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEFLAWSHOWWIDGET_H
#define UI_SINGLEFLAWSHOWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleFlawShowWidget
{
public:
    QTableWidget *tableWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;
    QGraphicsView *graphicsView_3;
    QPushButton *buttonExport;

    void setupUi(QWidget *SingleFlawShowWidget)
    {
        if (SingleFlawShowWidget->objectName().isEmpty())
            SingleFlawShowWidget->setObjectName(QString::fromUtf8("SingleFlawShowWidget"));
        SingleFlawShowWidget->resize(1901, 483);
        tableWidget = new QTableWidget(SingleFlawShowWidget);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
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
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEnabled(true);
        tableWidget->setGeometry(QRect(990, 60, 901, 341));
        label = new QLabel(SingleFlawShowWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 60, 54, 12));
        label_2 = new QLabel(SingleFlawShowWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(350, 60, 54, 12));
        label_3 = new QLabel(SingleFlawShowWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(670, 60, 54, 12));
        label_4 = new QLabel(SingleFlawShowWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(670, 40, 54, 12));
        label_5 = new QLabel(SingleFlawShowWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(350, 40, 54, 12));
        label_6 = new QLabel(SingleFlawShowWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 40, 54, 12));
        pushButton = new QPushButton(SingleFlawShowWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1760, 10, 81, 20));
        graphicsView = new QGraphicsView(SingleFlawShowWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(30, 80, 291, 271));
        graphicsView_2 = new QGraphicsView(SingleFlawShowWidget);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(350, 80, 291, 271));
        graphicsView_3 = new QGraphicsView(SingleFlawShowWidget);
        graphicsView_3->setObjectName(QString::fromUtf8("graphicsView_3"));
        graphicsView_3->setGeometry(QRect(670, 80, 291, 271));
        buttonExport = new QPushButton(SingleFlawShowWidget);
        buttonExport->setObjectName(QString::fromUtf8("buttonExport"));
        buttonExport->setGeometry(QRect(1620, 10, 75, 23));

        retranslateUi(SingleFlawShowWidget);

        QMetaObject::connectSlotsByName(SingleFlawShowWidget);
    } // setupUi

    void retranslateUi(QWidget *SingleFlawShowWidget)
    {
        SingleFlawShowWidget->setWindowTitle(QCoreApplication::translate("SingleFlawShowWidget", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SingleFlawShowWidget", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SingleFlawShowWidget", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SingleFlawShowWidget", "\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SingleFlawShowWidget", "\347\255\211\347\272\247", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SingleFlawShowWidget", "\345\235\220\346\240\207X", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SingleFlawShowWidget", "\345\235\220\346\240\207Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SingleFlawShowWidget", "\351\225\277", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SingleFlawShowWidget", "\345\256\275", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("SingleFlawShowWidget", "\351\235\242\347\247\257", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QCoreApplication::translate("SingleFlawShowWidget", "\345\205\211\345\234\2723", nullptr));
        label_5->setText(QCoreApplication::translate("SingleFlawShowWidget", "\345\205\211\345\234\2722", nullptr));
        label_6->setText(QCoreApplication::translate("SingleFlawShowWidget", "\345\205\211\345\234\2721", nullptr));
        pushButton->setText(QCoreApplication::translate("SingleFlawShowWidget", "\346\232\202\345\201\234", nullptr));
        buttonExport->setText(QCoreApplication::translate("SingleFlawShowWidget", "\345\257\274\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SingleFlawShowWidget: public Ui_SingleFlawShowWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEFLAWSHOWWIDGET_H

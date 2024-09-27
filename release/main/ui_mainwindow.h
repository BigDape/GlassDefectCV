/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QTableWidget *glassstatictablewidget;
    QWidget *tab_4;
    QLabel *label_15;
    QLabel *label_14;
    QGraphicsView *graphicsView_2;
    QGraphicsView *graphicsView_3;
    QLabel *label_13;
    QGraphicsView *graphicsView;
    QTableWidget *SingleFlawtableWidget;
    QWidget *tab_5;
    QTableWidget *singleSizeTableWidget;
    QGraphicsView *graphicsView_outLine;
    QGraphicsView *graphicsView_Field;
    QWidget *tab_6;
    QWidget *tab_9;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView_Field3;
    QFormLayout *formLayout_3;
    QLabel *label_62;
    QLabel *defectID3LB;
    QLabel *label_64;
    QLabel *defectTime3LB;
    QLabel *label_66;
    QLabel *defectType3LB;
    QLabel *label_68;
    QLabel *defectLevel3LB;
    QLabel *label_70;
    QLabel *defectX3LB;
    QLabel *label_72;
    QLabel *defectY3LB;
    QLabel *label_74;
    QLabel *defectLength3LB;
    QLabel *label_76;
    QLabel *defectWidth3LB;
    QLabel *label_78;
    QLabel *defectArea3LB;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *graphicsView_Field2;
    QFormLayout *formLayout_2;
    QLabel *label_44;
    QLabel *defectID2LB;
    QLabel *label_46;
    QLabel *defectTime2LB;
    QLabel *label_48;
    QLabel *defectType2LB;
    QLabel *label_50;
    QLabel *defectLevel2LB;
    QLabel *label_52;
    QLabel *defectX2LB;
    QLabel *label_54;
    QLabel *defectY2LB;
    QLabel *label_56;
    QLabel *defectLength2LB;
    QLabel *label_58;
    QLabel *defectWidth2LB;
    QLabel *label_60;
    QLabel *defectArea2LB;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QGraphicsView *graphicsView_Field1;
    QFormLayout *formLayout;
    QLabel *label_26;
    QLabel *defectID1LB;
    QLabel *label_28;
    QLabel *defectTime1LB;
    QLabel *label_30;
    QLabel *defectType1LB;
    QLabel *label_31;
    QLabel *defectLevel1LB;
    QLabel *label_34;
    QLabel *defectX1LB;
    QLabel *label_36;
    QLabel *defectY1LB;
    QLabel *label_38;
    QLabel *defectLength1LB;
    QLabel *label_39;
    QLabel *defectWidth1LB;
    QLabel *label_40;
    QLabel *defectArea1LB;
    QTabWidget *tabWidget_3;
    QWidget *tab_summary;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_2;
    QLabel *label_16;
    QLineEdit *glassTotalCountLE;
    QLabel *label_5;
    QLabel *label_17;
    QLineEdit *glassOKCount;
    QLabel *label_18;
    QLineEdit *glassNGCount;
    QLabel *label_19;
    QLineEdit *qualicaficationRateLE;
    QLabel *label_20;
    QLineEdit *ExceptionCountLE;
    QLabel *label_21;
    QLineEdit *hasSortCountLE;
    QLabel *label_22;
    QLineEdit *NoSortCountLE;
    QLabel *currentGlassStatus;
    QWidget *layoutWidget_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *weekLB;
    QLabel *YearMonthDayLB;
    QLabel *timeLB;
    QWidget *tab_information;
    QListWidget *loglistWidget;
    QwtPlot *qwtPlot;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1920, 1028);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(2000, 16777215));
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setAutoFillBackground(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget_2 = new QTabWidget(centralwidget);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(0, 471, 1921, 681));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        glassstatictablewidget = new QTableWidget(tab_3);
        glassstatictablewidget->setObjectName(QString::fromUtf8("glassstatictablewidget"));
        glassstatictablewidget->setGeometry(QRect(2, 0, 1911, 441));
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        label_15 = new QLabel(tab_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(790, 60, 54, 12));
        label_14 = new QLabel(tab_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(480, 60, 54, 12));
        graphicsView_2 = new QGraphicsView(tab_4);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(350, 100, 281, 251));
        graphicsView_3 = new QGraphicsView(tab_4);
        graphicsView_3->setObjectName(QString::fromUtf8("graphicsView_3"));
        graphicsView_3->setGeometry(QRect(670, 100, 281, 251));
        label_13 = new QLabel(tab_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(140, 60, 54, 12));
        graphicsView = new QGraphicsView(tab_4);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(30, 100, 281, 251));
        SingleFlawtableWidget = new QTableWidget(tab_4);
        if (SingleFlawtableWidget->columnCount() < 9)
            SingleFlawtableWidget->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        SingleFlawtableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        SingleFlawtableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        SingleFlawtableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        SingleFlawtableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        SingleFlawtableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        SingleFlawtableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        SingleFlawtableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        SingleFlawtableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        SingleFlawtableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        SingleFlawtableWidget->setObjectName(QString::fromUtf8("SingleFlawtableWidget"));
        SingleFlawtableWidget->setGeometry(QRect(990, 40, 901, 391));
        tabWidget_2->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        singleSizeTableWidget = new QTableWidget(tab_5);
        if (singleSizeTableWidget->columnCount() < 7)
            singleSizeTableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        singleSizeTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        singleSizeTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        singleSizeTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        singleSizeTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        singleSizeTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        singleSizeTableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        singleSizeTableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem15);
        singleSizeTableWidget->setObjectName(QString::fromUtf8("singleSizeTableWidget"));
        singleSizeTableWidget->setGeometry(QRect(1190, 50, 701, 381));
        graphicsView_outLine = new QGraphicsView(tab_5);
        graphicsView_outLine->setObjectName(QString::fromUtf8("graphicsView_outLine"));
        graphicsView_outLine->setGeometry(QRect(80, 80, 611, 301));
        graphicsView_Field = new QGraphicsView(tab_5);
        graphicsView_Field->setObjectName(QString::fromUtf8("graphicsView_Field"));
        graphicsView_Field->setGeometry(QRect(790, 80, 361, 301));
        tabWidget_2->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        tabWidget_2->addTab(tab_6, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName(QString::fromUtf8("tab_9"));
        layoutWidget = new QWidget(tab_9);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(1400, 100, 374, 194));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView_Field3 = new QGraphicsView(layoutWidget);
        graphicsView_Field3->setObjectName(QString::fromUtf8("graphicsView_Field3"));

        horizontalLayout->addWidget(graphicsView_Field3);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_62 = new QLabel(layoutWidget);
        label_62->setObjectName(QString::fromUtf8("label_62"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_62);

        defectID3LB = new QLabel(layoutWidget);
        defectID3LB->setObjectName(QString::fromUtf8("defectID3LB"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, defectID3LB);

        label_64 = new QLabel(layoutWidget);
        label_64->setObjectName(QString::fromUtf8("label_64"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_64);

        defectTime3LB = new QLabel(layoutWidget);
        defectTime3LB->setObjectName(QString::fromUtf8("defectTime3LB"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, defectTime3LB);

        label_66 = new QLabel(layoutWidget);
        label_66->setObjectName(QString::fromUtf8("label_66"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_66);

        defectType3LB = new QLabel(layoutWidget);
        defectType3LB->setObjectName(QString::fromUtf8("defectType3LB"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, defectType3LB);

        label_68 = new QLabel(layoutWidget);
        label_68->setObjectName(QString::fromUtf8("label_68"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_68);

        defectLevel3LB = new QLabel(layoutWidget);
        defectLevel3LB->setObjectName(QString::fromUtf8("defectLevel3LB"));

        formLayout_3->setWidget(3, QFormLayout::FieldRole, defectLevel3LB);

        label_70 = new QLabel(layoutWidget);
        label_70->setObjectName(QString::fromUtf8("label_70"));

        formLayout_3->setWidget(4, QFormLayout::LabelRole, label_70);

        defectX3LB = new QLabel(layoutWidget);
        defectX3LB->setObjectName(QString::fromUtf8("defectX3LB"));

        formLayout_3->setWidget(4, QFormLayout::FieldRole, defectX3LB);

        label_72 = new QLabel(layoutWidget);
        label_72->setObjectName(QString::fromUtf8("label_72"));

        formLayout_3->setWidget(5, QFormLayout::LabelRole, label_72);

        defectY3LB = new QLabel(layoutWidget);
        defectY3LB->setObjectName(QString::fromUtf8("defectY3LB"));

        formLayout_3->setWidget(5, QFormLayout::FieldRole, defectY3LB);

        label_74 = new QLabel(layoutWidget);
        label_74->setObjectName(QString::fromUtf8("label_74"));

        formLayout_3->setWidget(6, QFormLayout::LabelRole, label_74);

        defectLength3LB = new QLabel(layoutWidget);
        defectLength3LB->setObjectName(QString::fromUtf8("defectLength3LB"));

        formLayout_3->setWidget(6, QFormLayout::FieldRole, defectLength3LB);

        label_76 = new QLabel(layoutWidget);
        label_76->setObjectName(QString::fromUtf8("label_76"));

        formLayout_3->setWidget(7, QFormLayout::LabelRole, label_76);

        defectWidth3LB = new QLabel(layoutWidget);
        defectWidth3LB->setObjectName(QString::fromUtf8("defectWidth3LB"));

        formLayout_3->setWidget(7, QFormLayout::FieldRole, defectWidth3LB);

        label_78 = new QLabel(layoutWidget);
        label_78->setObjectName(QString::fromUtf8("label_78"));

        formLayout_3->setWidget(8, QFormLayout::LabelRole, label_78);

        defectArea3LB = new QLabel(layoutWidget);
        defectArea3LB->setObjectName(QString::fromUtf8("defectArea3LB"));

        formLayout_3->setWidget(8, QFormLayout::FieldRole, defectArea3LB);


        horizontalLayout->addLayout(formLayout_3);

        layoutWidget1 = new QWidget(tab_9);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(750, 100, 374, 194));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        graphicsView_Field2 = new QGraphicsView(layoutWidget1);
        graphicsView_Field2->setObjectName(QString::fromUtf8("graphicsView_Field2"));

        horizontalLayout_2->addWidget(graphicsView_Field2);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_44 = new QLabel(layoutWidget1);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_44);

        defectID2LB = new QLabel(layoutWidget1);
        defectID2LB->setObjectName(QString::fromUtf8("defectID2LB"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, defectID2LB);

        label_46 = new QLabel(layoutWidget1);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_46);

        defectTime2LB = new QLabel(layoutWidget1);
        defectTime2LB->setObjectName(QString::fromUtf8("defectTime2LB"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, defectTime2LB);

        label_48 = new QLabel(layoutWidget1);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_48);

        defectType2LB = new QLabel(layoutWidget1);
        defectType2LB->setObjectName(QString::fromUtf8("defectType2LB"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, defectType2LB);

        label_50 = new QLabel(layoutWidget1);
        label_50->setObjectName(QString::fromUtf8("label_50"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_50);

        defectLevel2LB = new QLabel(layoutWidget1);
        defectLevel2LB->setObjectName(QString::fromUtf8("defectLevel2LB"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, defectLevel2LB);

        label_52 = new QLabel(layoutWidget1);
        label_52->setObjectName(QString::fromUtf8("label_52"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_52);

        defectX2LB = new QLabel(layoutWidget1);
        defectX2LB->setObjectName(QString::fromUtf8("defectX2LB"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, defectX2LB);

        label_54 = new QLabel(layoutWidget1);
        label_54->setObjectName(QString::fromUtf8("label_54"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_54);

        defectY2LB = new QLabel(layoutWidget1);
        defectY2LB->setObjectName(QString::fromUtf8("defectY2LB"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, defectY2LB);

        label_56 = new QLabel(layoutWidget1);
        label_56->setObjectName(QString::fromUtf8("label_56"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_56);

        defectLength2LB = new QLabel(layoutWidget1);
        defectLength2LB->setObjectName(QString::fromUtf8("defectLength2LB"));

        formLayout_2->setWidget(6, QFormLayout::FieldRole, defectLength2LB);

        label_58 = new QLabel(layoutWidget1);
        label_58->setObjectName(QString::fromUtf8("label_58"));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, label_58);

        defectWidth2LB = new QLabel(layoutWidget1);
        defectWidth2LB->setObjectName(QString::fromUtf8("defectWidth2LB"));

        formLayout_2->setWidget(7, QFormLayout::FieldRole, defectWidth2LB);

        label_60 = new QLabel(layoutWidget1);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        formLayout_2->setWidget(8, QFormLayout::LabelRole, label_60);

        defectArea2LB = new QLabel(layoutWidget1);
        defectArea2LB->setObjectName(QString::fromUtf8("defectArea2LB"));

        formLayout_2->setWidget(8, QFormLayout::FieldRole, defectArea2LB);


        horizontalLayout_2->addLayout(formLayout_2);

        layoutWidget2 = new QWidget(tab_9);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(70, 100, 374, 194));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        graphicsView_Field1 = new QGraphicsView(layoutWidget2);
        graphicsView_Field1->setObjectName(QString::fromUtf8("graphicsView_Field1"));

        horizontalLayout_4->addWidget(graphicsView_Field1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_26 = new QLabel(layoutWidget2);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_26);

        defectID1LB = new QLabel(layoutWidget2);
        defectID1LB->setObjectName(QString::fromUtf8("defectID1LB"));

        formLayout->setWidget(0, QFormLayout::FieldRole, defectID1LB);

        label_28 = new QLabel(layoutWidget2);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_28);

        defectTime1LB = new QLabel(layoutWidget2);
        defectTime1LB->setObjectName(QString::fromUtf8("defectTime1LB"));

        formLayout->setWidget(1, QFormLayout::FieldRole, defectTime1LB);

        label_30 = new QLabel(layoutWidget2);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_30);

        defectType1LB = new QLabel(layoutWidget2);
        defectType1LB->setObjectName(QString::fromUtf8("defectType1LB"));

        formLayout->setWidget(2, QFormLayout::FieldRole, defectType1LB);

        label_31 = new QLabel(layoutWidget2);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_31);

        defectLevel1LB = new QLabel(layoutWidget2);
        defectLevel1LB->setObjectName(QString::fromUtf8("defectLevel1LB"));

        formLayout->setWidget(3, QFormLayout::FieldRole, defectLevel1LB);

        label_34 = new QLabel(layoutWidget2);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_34);

        defectX1LB = new QLabel(layoutWidget2);
        defectX1LB->setObjectName(QString::fromUtf8("defectX1LB"));

        formLayout->setWidget(4, QFormLayout::FieldRole, defectX1LB);

        label_36 = new QLabel(layoutWidget2);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_36);

        defectY1LB = new QLabel(layoutWidget2);
        defectY1LB->setObjectName(QString::fromUtf8("defectY1LB"));

        formLayout->setWidget(5, QFormLayout::FieldRole, defectY1LB);

        label_38 = new QLabel(layoutWidget2);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_38);

        defectLength1LB = new QLabel(layoutWidget2);
        defectLength1LB->setObjectName(QString::fromUtf8("defectLength1LB"));

        formLayout->setWidget(6, QFormLayout::FieldRole, defectLength1LB);

        label_39 = new QLabel(layoutWidget2);
        label_39->setObjectName(QString::fromUtf8("label_39"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_39);

        defectWidth1LB = new QLabel(layoutWidget2);
        defectWidth1LB->setObjectName(QString::fromUtf8("defectWidth1LB"));

        formLayout->setWidget(7, QFormLayout::FieldRole, defectWidth1LB);

        label_40 = new QLabel(layoutWidget2);
        label_40->setObjectName(QString::fromUtf8("label_40"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_40);

        defectArea1LB = new QLabel(layoutWidget2);
        defectArea1LB->setObjectName(QString::fromUtf8("defectArea1LB"));

        formLayout->setWidget(8, QFormLayout::FieldRole, defectArea1LB);


        horizontalLayout_4->addLayout(formLayout);

        tabWidget_2->addTab(tab_9, QString());
        tabWidget_3 = new QTabWidget(centralwidget);
        tabWidget_3->setObjectName(QString::fromUtf8("tabWidget_3"));
        tabWidget_3->setGeometry(QRect(1525, 0, 381, 451));
        tab_summary = new QWidget();
        tab_summary->setObjectName(QString::fromUtf8("tab_summary"));
        layoutWidget_3 = new QWidget(tab_summary);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(6, 191, 361, 171));
        gridLayout_2 = new QGridLayout(layoutWidget_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_16 = new QLabel(layoutWidget_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 0, 0, 1, 1);

        glassTotalCountLE = new QLineEdit(layoutWidget_3);
        glassTotalCountLE->setObjectName(QString::fromUtf8("glassTotalCountLE"));

        gridLayout_2->addWidget(glassTotalCountLE, 0, 1, 1, 1);

        label_5 = new QLabel(layoutWidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 2, 1, 1);

        label_17 = new QLabel(layoutWidget_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 1, 0, 1, 1);

        glassOKCount = new QLineEdit(layoutWidget_3);
        glassOKCount->setObjectName(QString::fromUtf8("glassOKCount"));

        gridLayout_2->addWidget(glassOKCount, 1, 1, 1, 1);

        label_18 = new QLabel(layoutWidget_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_2->addWidget(label_18, 1, 2, 1, 1);

        glassNGCount = new QLineEdit(layoutWidget_3);
        glassNGCount->setObjectName(QString::fromUtf8("glassNGCount"));

        gridLayout_2->addWidget(glassNGCount, 1, 3, 1, 1);

        label_19 = new QLabel(layoutWidget_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_2->addWidget(label_19, 2, 0, 1, 1);

        qualicaficationRateLE = new QLineEdit(layoutWidget_3);
        qualicaficationRateLE->setObjectName(QString::fromUtf8("qualicaficationRateLE"));

        gridLayout_2->addWidget(qualicaficationRateLE, 2, 1, 1, 1);

        label_20 = new QLabel(layoutWidget_3);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_2->addWidget(label_20, 2, 2, 1, 1);

        ExceptionCountLE = new QLineEdit(layoutWidget_3);
        ExceptionCountLE->setObjectName(QString::fromUtf8("ExceptionCountLE"));

        gridLayout_2->addWidget(ExceptionCountLE, 2, 3, 1, 1);

        label_21 = new QLabel(layoutWidget_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_2->addWidget(label_21, 3, 0, 1, 1);

        hasSortCountLE = new QLineEdit(layoutWidget_3);
        hasSortCountLE->setObjectName(QString::fromUtf8("hasSortCountLE"));

        gridLayout_2->addWidget(hasSortCountLE, 3, 1, 1, 1);

        label_22 = new QLabel(layoutWidget_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_2->addWidget(label_22, 3, 2, 1, 1);

        NoSortCountLE = new QLineEdit(layoutWidget_3);
        NoSortCountLE->setObjectName(QString::fromUtf8("NoSortCountLE"));

        gridLayout_2->addWidget(NoSortCountLE, 3, 3, 1, 1);

        currentGlassStatus = new QLabel(layoutWidget_3);
        currentGlassStatus->setObjectName(QString::fromUtf8("currentGlassStatus"));

        gridLayout_2->addWidget(currentGlassStatus, 0, 3, 1, 1);

        layoutWidget_4 = new QWidget(tab_summary);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(6, 24, 361, 111));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        weekLB = new QLabel(layoutWidget_4);
        weekLB->setObjectName(QString::fromUtf8("weekLB"));

        horizontalLayout_3->addWidget(weekLB);

        YearMonthDayLB = new QLabel(layoutWidget_4);
        YearMonthDayLB->setObjectName(QString::fromUtf8("YearMonthDayLB"));

        horizontalLayout_3->addWidget(YearMonthDayLB);


        verticalLayout_2->addLayout(horizontalLayout_3);

        timeLB = new QLabel(layoutWidget_4);
        timeLB->setObjectName(QString::fromUtf8("timeLB"));

        verticalLayout_2->addWidget(timeLB);

        tabWidget_3->addTab(tab_summary, QString());
        tab_information = new QWidget();
        tab_information->setObjectName(QString::fromUtf8("tab_information"));
        loglistWidget = new QListWidget(tab_information);
        loglistWidget->setObjectName(QString::fromUtf8("loglistWidget"));
        loglistWidget->setGeometry(QRect(-5, -9, 381, 441));
        tabWidget_3->addTab(tab_information, QString());
        qwtPlot = new QwtPlot(centralwidget);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));
        qwtPlot->setGeometry(QRect(0, 0, 1511, 451));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        tabWidget_2->setCurrentIndex(4);
        tabWidget_3->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\347\273\237\350\256\241", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\345\205\211\345\234\2723", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\345\205\211\345\234\2722", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\345\205\211\345\234\2721", nullptr));
        QTableWidgetItem *___qtablewidgetitem = SingleFlawtableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = SingleFlawtableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = SingleFlawtableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = SingleFlawtableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\347\255\211\347\272\247", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = SingleFlawtableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\345\235\220\346\240\207X", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = SingleFlawtableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\345\235\220\346\240\207Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = SingleFlawtableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\351\225\277", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = SingleFlawtableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "\345\256\275", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = SingleFlawtableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "\351\235\242\347\247\257", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\344\277\241\346\201\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = singleSizeTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = singleSizeTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = singleSizeTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "\347\255\211\347\272\247", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = singleSizeTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "\351\225\277X(mm\357\274\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = singleSizeTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "\345\256\275Y(mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = singleSizeTableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "\350\276\271\350\267\235X(mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = singleSizeTableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "\350\276\271\350\267\235Y(mm)", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QCoreApplication::translate("MainWindow", "\345\260\272\345\257\270\344\277\241\346\201\257", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QCoreApplication::translate("MainWindow", "\347\233\270\346\234\272\344\277\241\346\201\257", nullptr));
        label_62->setText(QCoreApplication::translate("MainWindow", "  \345\272\217\345\217\267\357\274\232", nullptr));
        defectID3LB->setText(QString());
        label_64->setText(QCoreApplication::translate("MainWindow", "  \346\227\266\351\227\264\357\274\232", nullptr));
        defectTime3LB->setText(QString());
        label_66->setText(QCoreApplication::translate("MainWindow", "  \347\261\273\345\236\213\357\274\232", nullptr));
        defectType3LB->setText(QString());
        label_68->setText(QCoreApplication::translate("MainWindow", "  \347\255\211\347\272\247\357\274\232", nullptr));
        defectLevel3LB->setText(QString());
        label_70->setText(QCoreApplication::translate("MainWindow", " \345\235\220\346\240\207X\357\274\232", nullptr));
        defectX3LB->setText(QString());
        label_72->setText(QCoreApplication::translate("MainWindow", " \345\235\220\346\240\207Y\357\274\232", nullptr));
        defectY3LB->setText(QString());
        label_74->setText(QCoreApplication::translate("MainWindow", "    \351\225\277\357\274\232", nullptr));
        defectLength3LB->setText(QString());
        label_76->setText(QCoreApplication::translate("MainWindow", "    \345\256\275\357\274\232", nullptr));
        defectWidth3LB->setText(QString());
        label_78->setText(QCoreApplication::translate("MainWindow", "  \351\235\242\347\247\257\357\274\232", nullptr));
        defectArea3LB->setText(QString());
        label_44->setText(QCoreApplication::translate("MainWindow", "  \345\272\217\345\217\267\357\274\232", nullptr));
        defectID2LB->setText(QString());
        label_46->setText(QCoreApplication::translate("MainWindow", "  \346\227\266\351\227\264\357\274\232", nullptr));
        defectTime2LB->setText(QString());
        label_48->setText(QCoreApplication::translate("MainWindow", "  \347\261\273\345\236\213\357\274\232", nullptr));
        defectType2LB->setText(QString());
        label_50->setText(QCoreApplication::translate("MainWindow", "  \347\255\211\347\272\247\357\274\232", nullptr));
        defectLevel2LB->setText(QString());
        label_52->setText(QCoreApplication::translate("MainWindow", " \345\235\220\346\240\207X\357\274\232", nullptr));
        defectX2LB->setText(QString());
        label_54->setText(QCoreApplication::translate("MainWindow", " \345\235\220\346\240\207Y\357\274\232", nullptr));
        defectY2LB->setText(QString());
        label_56->setText(QCoreApplication::translate("MainWindow", "    \351\225\277\357\274\232", nullptr));
        defectLength2LB->setText(QString());
        label_58->setText(QCoreApplication::translate("MainWindow", "    \345\256\275\357\274\232", nullptr));
        defectWidth2LB->setText(QString());
        label_60->setText(QCoreApplication::translate("MainWindow", "  \351\235\242\347\247\257\357\274\232", nullptr));
        defectArea2LB->setText(QString());
        label_26->setText(QCoreApplication::translate("MainWindow", "  \345\272\217\345\217\267\357\274\232", nullptr));
        defectID1LB->setText(QString());
        label_28->setText(QCoreApplication::translate("MainWindow", "  \346\227\266\351\227\264\357\274\232", nullptr));
        defectTime1LB->setText(QString());
        label_30->setText(QCoreApplication::translate("MainWindow", "  \347\261\273\345\236\213\357\274\232", nullptr));
        defectType1LB->setText(QString());
        label_31->setText(QCoreApplication::translate("MainWindow", "  \347\255\211\347\272\247\357\274\232", nullptr));
        defectLevel1LB->setText(QString());
        label_34->setText(QCoreApplication::translate("MainWindow", " \345\235\220\346\240\207X\357\274\232", nullptr));
        defectX1LB->setText(QString());
        label_36->setText(QCoreApplication::translate("MainWindow", " \345\235\220\346\240\207Y\357\274\232", nullptr));
        defectY1LB->setText(QString());
        label_38->setText(QCoreApplication::translate("MainWindow", "    \351\225\277\357\274\232", nullptr));
        defectLength1LB->setText(QString());
        label_39->setText(QCoreApplication::translate("MainWindow", "    \345\256\275\357\274\232", nullptr));
        defectWidth1LB->setText(QString());
        label_40->setText(QCoreApplication::translate("MainWindow", "  \351\235\242\347\247\257\357\274\232", nullptr));
        defectArea1LB->setText(QString());
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_9), QCoreApplication::translate("MainWindow", "\345\256\236\346\227\266\347\274\272\351\231\267", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\347\216\273\347\222\203\346\200\273\346\225\260\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\347\216\273\347\222\203\347\212\266\346\200\201\357\274\232", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "OK:", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "NG:", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\345\220\210\346\240\274\347\216\207\357\274\232", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "\345\274\202\345\270\270\346\225\260\357\274\232", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\345\267\262\345\210\206\346\213\243\357\274\232", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\345\276\205\345\210\206\346\213\243\357\274\232", nullptr));
        currentGlassStatus->setText(QString());
        weekLB->setText(QString());
        YearMonthDayLB->setText(QString());
        timeLB->setText(QString());
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_summary), QCoreApplication::translate("MainWindow", "\346\246\202\350\277\260", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_information), QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

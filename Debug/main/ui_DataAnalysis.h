/********************************************************************************
** Form generated from reading UI file 'DataAnalysis.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAANALYSIS_H
#define UI_DATAANALYSIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataAnalysis
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;
    QGraphicsView *graphicsView_3;
    QTableWidget *tableWidget_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *glassidLB;
    QWidget *tab_3;
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *GlassIDLB;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *glassIDLE;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *glassTypeLB;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *glassTypeCB;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *YearLB;
    QLabel *monthLB;
    QLabel *DayLB;
    QLabel *HourLB;
    QLabel *minuteLB;
    QLabel *timeLB;
    QComboBox *YearSCB;
    QComboBox *MonthSCB;
    QComboBox *DaySCB;
    QComboBox *HourSCB;
    QComboBox *MinuteSCB;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *YearLB_2;
    QLabel *monthLB_2;
    QLabel *DayLB_2;
    QLabel *HourLB_2;
    QLabel *minuteLB_2;
    QLabel *timeLB_2;
    QComboBox *YearECB;
    QComboBox *MonthECB;
    QComboBox *DayECB;
    QComboBox *HourECB;
    QComboBox *MinuteECB;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *searchBT;
    QPushButton *clearBT;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *DataAnalysis)
    {
        if (DataAnalysis->objectName().isEmpty())
            DataAnalysis->setObjectName(QString::fromUtf8("DataAnalysis"));
        DataAnalysis->resize(1588, 614);
        tabWidget = new QTabWidget(DataAnalysis);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(3, 220, 1581, 391));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tableWidget = new QTableWidget(tab);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 1571, 361));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMinimumSize(QSize(0, 0));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        graphicsView = new QGraphicsView(tab_2);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 110, 241, 181));
        graphicsView_2 = new QGraphicsView(tab_2);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(240, 110, 251, 181));
        graphicsView_3 = new QGraphicsView(tab_2);
        graphicsView_3->setObjectName(QString::fromUtf8("graphicsView_3"));
        graphicsView_3->setGeometry(QRect(490, 110, 241, 181));
        tableWidget_2 = new QTableWidget(tab_2);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(740, 10, 831, 351));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(90, 80, 54, 12));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(330, 80, 54, 12));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(590, 80, 54, 12));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 30, 54, 12));
        glassidLB = new QLabel(tab_2);
        glassidLB->setObjectName(QString::fromUtf8("glassidLB"));
        glassidLB->setGeometry(QRect(70, 30, 54, 12));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());
        label = new QLabel(DataAnalysis);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(11, 1, 48, 16));
        layoutWidget = new QWidget(DataAnalysis);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(8, 24, 544, 183));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        GlassIDLB = new QLabel(layoutWidget);
        GlassIDLB->setObjectName(QString::fromUtf8("GlassIDLB"));
        GlassIDLB->setMinimumSize(QSize(50, 0));

        horizontalLayout->addWidget(GlassIDLB);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        glassIDLE = new QLineEdit(layoutWidget);
        glassIDLE->setObjectName(QString::fromUtf8("glassIDLE"));
        glassIDLE->setMinimumSize(QSize(150, 0));
        glassIDLE->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(glassIDLE);


        horizontalLayout_5->addLayout(horizontalLayout);

        horizontalSpacer_5 = new QSpacerItem(320, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        glassTypeLB = new QLabel(layoutWidget);
        glassTypeLB->setObjectName(QString::fromUtf8("glassTypeLB"));
        glassTypeLB->setMinimumSize(QSize(50, 0));

        horizontalLayout_2->addWidget(glassTypeLB);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        glassTypeCB = new QComboBox(layoutWidget);
        glassTypeCB->setObjectName(QString::fromUtf8("glassTypeCB"));
        glassTypeCB->setMinimumSize(QSize(150, 0));

        horizontalLayout_2->addWidget(glassTypeCB);

        horizontalSpacer_2 = new QSpacerItem(320, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        YearLB = new QLabel(layoutWidget);
        YearLB->setObjectName(QString::fromUtf8("YearLB"));

        gridLayout_2->addWidget(YearLB, 0, 1, 1, 1);

        monthLB = new QLabel(layoutWidget);
        monthLB->setObjectName(QString::fromUtf8("monthLB"));

        gridLayout_2->addWidget(monthLB, 0, 2, 1, 1);

        DayLB = new QLabel(layoutWidget);
        DayLB->setObjectName(QString::fromUtf8("DayLB"));

        gridLayout_2->addWidget(DayLB, 0, 3, 1, 1);

        HourLB = new QLabel(layoutWidget);
        HourLB->setObjectName(QString::fromUtf8("HourLB"));

        gridLayout_2->addWidget(HourLB, 0, 4, 1, 1);

        minuteLB = new QLabel(layoutWidget);
        minuteLB->setObjectName(QString::fromUtf8("minuteLB"));

        gridLayout_2->addWidget(minuteLB, 0, 5, 1, 1);

        timeLB = new QLabel(layoutWidget);
        timeLB->setObjectName(QString::fromUtf8("timeLB"));

        gridLayout_2->addWidget(timeLB, 1, 0, 1, 1);

        YearSCB = new QComboBox(layoutWidget);
        YearSCB->addItem(QString());
        YearSCB->addItem(QString());
        YearSCB->addItem(QString());
        YearSCB->addItem(QString());
        YearSCB->addItem(QString());
        YearSCB->addItem(QString());
        YearSCB->addItem(QString());
        YearSCB->addItem(QString());
        YearSCB->addItem(QString());
        YearSCB->addItem(QString());
        YearSCB->addItem(QString());
        YearSCB->setObjectName(QString::fromUtf8("YearSCB"));

        gridLayout_2->addWidget(YearSCB, 1, 1, 1, 1);

        MonthSCB = new QComboBox(layoutWidget);
        MonthSCB->addItem(QString());
        MonthSCB->addItem(QString());
        MonthSCB->addItem(QString());
        MonthSCB->addItem(QString());
        MonthSCB->addItem(QString());
        MonthSCB->addItem(QString());
        MonthSCB->addItem(QString());
        MonthSCB->addItem(QString());
        MonthSCB->addItem(QString());
        MonthSCB->addItem(QString());
        MonthSCB->addItem(QString());
        MonthSCB->addItem(QString());
        MonthSCB->setObjectName(QString::fromUtf8("MonthSCB"));

        gridLayout_2->addWidget(MonthSCB, 1, 2, 1, 1);

        DaySCB = new QComboBox(layoutWidget);
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->addItem(QString());
        DaySCB->setObjectName(QString::fromUtf8("DaySCB"));

        gridLayout_2->addWidget(DaySCB, 1, 3, 1, 1);

        HourSCB = new QComboBox(layoutWidget);
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->addItem(QString());
        HourSCB->setObjectName(QString::fromUtf8("HourSCB"));

        gridLayout_2->addWidget(HourSCB, 1, 4, 1, 1);

        MinuteSCB = new QComboBox(layoutWidget);
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->addItem(QString());
        MinuteSCB->setObjectName(QString::fromUtf8("MinuteSCB"));

        gridLayout_2->addWidget(MinuteSCB, 1, 5, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        YearLB_2 = new QLabel(layoutWidget);
        YearLB_2->setObjectName(QString::fromUtf8("YearLB_2"));

        gridLayout->addWidget(YearLB_2, 0, 1, 1, 1);

        monthLB_2 = new QLabel(layoutWidget);
        monthLB_2->setObjectName(QString::fromUtf8("monthLB_2"));

        gridLayout->addWidget(monthLB_2, 0, 2, 1, 1);

        DayLB_2 = new QLabel(layoutWidget);
        DayLB_2->setObjectName(QString::fromUtf8("DayLB_2"));

        gridLayout->addWidget(DayLB_2, 0, 3, 1, 1);

        HourLB_2 = new QLabel(layoutWidget);
        HourLB_2->setObjectName(QString::fromUtf8("HourLB_2"));

        gridLayout->addWidget(HourLB_2, 0, 4, 1, 1);

        minuteLB_2 = new QLabel(layoutWidget);
        minuteLB_2->setObjectName(QString::fromUtf8("minuteLB_2"));

        gridLayout->addWidget(minuteLB_2, 0, 5, 1, 1);

        timeLB_2 = new QLabel(layoutWidget);
        timeLB_2->setObjectName(QString::fromUtf8("timeLB_2"));

        gridLayout->addWidget(timeLB_2, 1, 0, 1, 1);

        YearECB = new QComboBox(layoutWidget);
        YearECB->addItem(QString());
        YearECB->addItem(QString());
        YearECB->addItem(QString());
        YearECB->addItem(QString());
        YearECB->addItem(QString());
        YearECB->addItem(QString());
        YearECB->addItem(QString());
        YearECB->addItem(QString());
        YearECB->addItem(QString());
        YearECB->addItem(QString());
        YearECB->addItem(QString());
        YearECB->setObjectName(QString::fromUtf8("YearECB"));

        gridLayout->addWidget(YearECB, 1, 1, 1, 1);

        MonthECB = new QComboBox(layoutWidget);
        MonthECB->addItem(QString());
        MonthECB->addItem(QString());
        MonthECB->addItem(QString());
        MonthECB->addItem(QString());
        MonthECB->addItem(QString());
        MonthECB->addItem(QString());
        MonthECB->addItem(QString());
        MonthECB->addItem(QString());
        MonthECB->addItem(QString());
        MonthECB->addItem(QString());
        MonthECB->addItem(QString());
        MonthECB->addItem(QString());
        MonthECB->setObjectName(QString::fromUtf8("MonthECB"));

        gridLayout->addWidget(MonthECB, 1, 2, 1, 1);

        DayECB = new QComboBox(layoutWidget);
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->addItem(QString());
        DayECB->setObjectName(QString::fromUtf8("DayECB"));

        gridLayout->addWidget(DayECB, 1, 3, 1, 1);

        HourECB = new QComboBox(layoutWidget);
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->addItem(QString());
        HourECB->setObjectName(QString::fromUtf8("HourECB"));

        gridLayout->addWidget(HourECB, 1, 4, 1, 1);

        MinuteECB = new QComboBox(layoutWidget);
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->addItem(QString());
        MinuteECB->setObjectName(QString::fromUtf8("MinuteECB"));

        gridLayout->addWidget(MinuteECB, 1, 5, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        searchBT = new QPushButton(layoutWidget);
        searchBT->setObjectName(QString::fromUtf8("searchBT"));

        horizontalLayout_3->addWidget(searchBT);

        clearBT = new QPushButton(layoutWidget);
        clearBT->setObjectName(QString::fromUtf8("clearBT"));

        horizontalLayout_3->addWidget(clearBT);

        horizontalSpacer = new QSpacerItem(320, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(DataAnalysis);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DataAnalysis);
    } // setupUi

    void retranslateUi(QWidget *DataAnalysis)
    {
        DataAnalysis->setWindowTitle(QCoreApplication::translate("DataAnalysis", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("DataAnalysis", "\346\261\207\346\200\273", nullptr));
        label_4->setText(QCoreApplication::translate("DataAnalysis", "\345\205\211\345\234\2721", nullptr));
        label_5->setText(QCoreApplication::translate("DataAnalysis", "\345\205\211\345\234\2722", nullptr));
        label_6->setText(QCoreApplication::translate("DataAnalysis", "\345\205\211\345\234\2723", nullptr));
        label_7->setText(QCoreApplication::translate("DataAnalysis", "\347\216\273\347\222\203ID\357\274\232", nullptr));
        glassidLB->setText(QCoreApplication::translate("DataAnalysis", "000001", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("DataAnalysis", "\347\274\272\351\231\267", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("DataAnalysis", "\346\237\261\347\212\266\345\233\276", nullptr));
        label->setText(QCoreApplication::translate("DataAnalysis", "\347\255\233\351\200\211\346\235\241\344\273\266", nullptr));
        GlassIDLB->setText(QCoreApplication::translate("DataAnalysis", "\347\216\273\347\222\203\345\272\217\345\217\267", nullptr));
        glassTypeLB->setText(QCoreApplication::translate("DataAnalysis", "\347\216\273\347\222\203\347\261\273\345\236\213", nullptr));
        label_2->setText(QString());
        YearLB->setText(QCoreApplication::translate("DataAnalysis", "    \345\271\264", nullptr));
        monthLB->setText(QCoreApplication::translate("DataAnalysis", "    \346\234\210", nullptr));
        DayLB->setText(QCoreApplication::translate("DataAnalysis", "     \346\227\245", nullptr));
        HourLB->setText(QCoreApplication::translate("DataAnalysis", "    \346\227\266", nullptr));
        minuteLB->setText(QCoreApplication::translate("DataAnalysis", "     \345\210\206", nullptr));
        timeLB->setText(QCoreApplication::translate("DataAnalysis", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        YearSCB->setItemText(0, QCoreApplication::translate("DataAnalysis", "2024", nullptr));
        YearSCB->setItemText(1, QCoreApplication::translate("DataAnalysis", "2025", nullptr));
        YearSCB->setItemText(2, QCoreApplication::translate("DataAnalysis", "2026", nullptr));
        YearSCB->setItemText(3, QCoreApplication::translate("DataAnalysis", "2027", nullptr));
        YearSCB->setItemText(4, QCoreApplication::translate("DataAnalysis", "2028", nullptr));
        YearSCB->setItemText(5, QCoreApplication::translate("DataAnalysis", "2029", nullptr));
        YearSCB->setItemText(6, QCoreApplication::translate("DataAnalysis", "2030", nullptr));
        YearSCB->setItemText(7, QCoreApplication::translate("DataAnalysis", "2031", nullptr));
        YearSCB->setItemText(8, QCoreApplication::translate("DataAnalysis", "2032", nullptr));
        YearSCB->setItemText(9, QCoreApplication::translate("DataAnalysis", "2033", nullptr));
        YearSCB->setItemText(10, QCoreApplication::translate("DataAnalysis", "2034", nullptr));

        MonthSCB->setItemText(0, QCoreApplication::translate("DataAnalysis", "01", nullptr));
        MonthSCB->setItemText(1, QCoreApplication::translate("DataAnalysis", "02", nullptr));
        MonthSCB->setItemText(2, QCoreApplication::translate("DataAnalysis", "03", nullptr));
        MonthSCB->setItemText(3, QCoreApplication::translate("DataAnalysis", "04", nullptr));
        MonthSCB->setItemText(4, QCoreApplication::translate("DataAnalysis", "05", nullptr));
        MonthSCB->setItemText(5, QCoreApplication::translate("DataAnalysis", "06", nullptr));
        MonthSCB->setItemText(6, QCoreApplication::translate("DataAnalysis", "07", nullptr));
        MonthSCB->setItemText(7, QCoreApplication::translate("DataAnalysis", "08", nullptr));
        MonthSCB->setItemText(8, QCoreApplication::translate("DataAnalysis", "09", nullptr));
        MonthSCB->setItemText(9, QCoreApplication::translate("DataAnalysis", "10", nullptr));
        MonthSCB->setItemText(10, QCoreApplication::translate("DataAnalysis", "11", nullptr));
        MonthSCB->setItemText(11, QCoreApplication::translate("DataAnalysis", "12", nullptr));

        DaySCB->setItemText(0, QCoreApplication::translate("DataAnalysis", "01", nullptr));
        DaySCB->setItemText(1, QCoreApplication::translate("DataAnalysis", "02", nullptr));
        DaySCB->setItemText(2, QCoreApplication::translate("DataAnalysis", "03", nullptr));
        DaySCB->setItemText(3, QCoreApplication::translate("DataAnalysis", "04", nullptr));
        DaySCB->setItemText(4, QCoreApplication::translate("DataAnalysis", "05", nullptr));
        DaySCB->setItemText(5, QCoreApplication::translate("DataAnalysis", "06", nullptr));
        DaySCB->setItemText(6, QCoreApplication::translate("DataAnalysis", "07", nullptr));
        DaySCB->setItemText(7, QCoreApplication::translate("DataAnalysis", "08", nullptr));
        DaySCB->setItemText(8, QCoreApplication::translate("DataAnalysis", "09", nullptr));
        DaySCB->setItemText(9, QCoreApplication::translate("DataAnalysis", "10", nullptr));
        DaySCB->setItemText(10, QCoreApplication::translate("DataAnalysis", "11", nullptr));
        DaySCB->setItemText(11, QCoreApplication::translate("DataAnalysis", "12", nullptr));
        DaySCB->setItemText(12, QCoreApplication::translate("DataAnalysis", "13", nullptr));
        DaySCB->setItemText(13, QCoreApplication::translate("DataAnalysis", "14", nullptr));
        DaySCB->setItemText(14, QCoreApplication::translate("DataAnalysis", "15", nullptr));
        DaySCB->setItemText(15, QCoreApplication::translate("DataAnalysis", "16", nullptr));
        DaySCB->setItemText(16, QCoreApplication::translate("DataAnalysis", "17", nullptr));
        DaySCB->setItemText(17, QCoreApplication::translate("DataAnalysis", "18", nullptr));
        DaySCB->setItemText(18, QCoreApplication::translate("DataAnalysis", "19", nullptr));
        DaySCB->setItemText(19, QCoreApplication::translate("DataAnalysis", "20", nullptr));
        DaySCB->setItemText(20, QCoreApplication::translate("DataAnalysis", "21", nullptr));
        DaySCB->setItemText(21, QCoreApplication::translate("DataAnalysis", "22", nullptr));
        DaySCB->setItemText(22, QCoreApplication::translate("DataAnalysis", "23", nullptr));
        DaySCB->setItemText(23, QCoreApplication::translate("DataAnalysis", "24", nullptr));
        DaySCB->setItemText(24, QCoreApplication::translate("DataAnalysis", "25", nullptr));
        DaySCB->setItemText(25, QCoreApplication::translate("DataAnalysis", "26", nullptr));
        DaySCB->setItemText(26, QCoreApplication::translate("DataAnalysis", "27", nullptr));
        DaySCB->setItemText(27, QCoreApplication::translate("DataAnalysis", "28", nullptr));
        DaySCB->setItemText(28, QCoreApplication::translate("DataAnalysis", "29", nullptr));
        DaySCB->setItemText(29, QCoreApplication::translate("DataAnalysis", "30", nullptr));
        DaySCB->setItemText(30, QCoreApplication::translate("DataAnalysis", "31", nullptr));

        HourSCB->setItemText(0, QCoreApplication::translate("DataAnalysis", "00", nullptr));
        HourSCB->setItemText(1, QCoreApplication::translate("DataAnalysis", "01", nullptr));
        HourSCB->setItemText(2, QCoreApplication::translate("DataAnalysis", "02", nullptr));
        HourSCB->setItemText(3, QCoreApplication::translate("DataAnalysis", "03", nullptr));
        HourSCB->setItemText(4, QCoreApplication::translate("DataAnalysis", "04", nullptr));
        HourSCB->setItemText(5, QCoreApplication::translate("DataAnalysis", "05", nullptr));
        HourSCB->setItemText(6, QCoreApplication::translate("DataAnalysis", "06", nullptr));
        HourSCB->setItemText(7, QCoreApplication::translate("DataAnalysis", "07", nullptr));
        HourSCB->setItemText(8, QCoreApplication::translate("DataAnalysis", "08", nullptr));
        HourSCB->setItemText(9, QCoreApplication::translate("DataAnalysis", "09", nullptr));
        HourSCB->setItemText(10, QCoreApplication::translate("DataAnalysis", "10", nullptr));
        HourSCB->setItemText(11, QCoreApplication::translate("DataAnalysis", "11", nullptr));
        HourSCB->setItemText(12, QCoreApplication::translate("DataAnalysis", "12", nullptr));
        HourSCB->setItemText(13, QCoreApplication::translate("DataAnalysis", "13", nullptr));
        HourSCB->setItemText(14, QCoreApplication::translate("DataAnalysis", "14", nullptr));
        HourSCB->setItemText(15, QCoreApplication::translate("DataAnalysis", "15", nullptr));
        HourSCB->setItemText(16, QCoreApplication::translate("DataAnalysis", "16", nullptr));
        HourSCB->setItemText(17, QCoreApplication::translate("DataAnalysis", "17", nullptr));
        HourSCB->setItemText(18, QCoreApplication::translate("DataAnalysis", "18", nullptr));
        HourSCB->setItemText(19, QCoreApplication::translate("DataAnalysis", "19", nullptr));
        HourSCB->setItemText(20, QCoreApplication::translate("DataAnalysis", "20", nullptr));
        HourSCB->setItemText(21, QCoreApplication::translate("DataAnalysis", "21", nullptr));
        HourSCB->setItemText(22, QCoreApplication::translate("DataAnalysis", "22", nullptr));
        HourSCB->setItemText(23, QCoreApplication::translate("DataAnalysis", "23", nullptr));

        MinuteSCB->setItemText(0, QCoreApplication::translate("DataAnalysis", "00", nullptr));
        MinuteSCB->setItemText(1, QCoreApplication::translate("DataAnalysis", "01", nullptr));
        MinuteSCB->setItemText(2, QCoreApplication::translate("DataAnalysis", "02", nullptr));
        MinuteSCB->setItemText(3, QCoreApplication::translate("DataAnalysis", "03", nullptr));
        MinuteSCB->setItemText(4, QCoreApplication::translate("DataAnalysis", "04", nullptr));
        MinuteSCB->setItemText(5, QCoreApplication::translate("DataAnalysis", "05", nullptr));
        MinuteSCB->setItemText(6, QCoreApplication::translate("DataAnalysis", "06", nullptr));
        MinuteSCB->setItemText(7, QCoreApplication::translate("DataAnalysis", "07", nullptr));
        MinuteSCB->setItemText(8, QCoreApplication::translate("DataAnalysis", "08", nullptr));
        MinuteSCB->setItemText(9, QCoreApplication::translate("DataAnalysis", "09", nullptr));
        MinuteSCB->setItemText(10, QCoreApplication::translate("DataAnalysis", "10", nullptr));
        MinuteSCB->setItemText(11, QCoreApplication::translate("DataAnalysis", "11", nullptr));
        MinuteSCB->setItemText(12, QCoreApplication::translate("DataAnalysis", "12", nullptr));
        MinuteSCB->setItemText(13, QCoreApplication::translate("DataAnalysis", "13", nullptr));
        MinuteSCB->setItemText(14, QCoreApplication::translate("DataAnalysis", "14", nullptr));
        MinuteSCB->setItemText(15, QCoreApplication::translate("DataAnalysis", "15", nullptr));
        MinuteSCB->setItemText(16, QCoreApplication::translate("DataAnalysis", "16", nullptr));
        MinuteSCB->setItemText(17, QCoreApplication::translate("DataAnalysis", "17", nullptr));
        MinuteSCB->setItemText(18, QCoreApplication::translate("DataAnalysis", "18", nullptr));
        MinuteSCB->setItemText(19, QCoreApplication::translate("DataAnalysis", "19", nullptr));
        MinuteSCB->setItemText(20, QCoreApplication::translate("DataAnalysis", "20", nullptr));
        MinuteSCB->setItemText(21, QCoreApplication::translate("DataAnalysis", "21", nullptr));
        MinuteSCB->setItemText(22, QCoreApplication::translate("DataAnalysis", "22", nullptr));
        MinuteSCB->setItemText(23, QCoreApplication::translate("DataAnalysis", "23", nullptr));
        MinuteSCB->setItemText(24, QCoreApplication::translate("DataAnalysis", "24", nullptr));
        MinuteSCB->setItemText(25, QCoreApplication::translate("DataAnalysis", "25", nullptr));
        MinuteSCB->setItemText(26, QCoreApplication::translate("DataAnalysis", "26", nullptr));
        MinuteSCB->setItemText(27, QCoreApplication::translate("DataAnalysis", "27", nullptr));
        MinuteSCB->setItemText(28, QCoreApplication::translate("DataAnalysis", "28", nullptr));
        MinuteSCB->setItemText(29, QCoreApplication::translate("DataAnalysis", "29", nullptr));
        MinuteSCB->setItemText(30, QCoreApplication::translate("DataAnalysis", "30", nullptr));
        MinuteSCB->setItemText(31, QCoreApplication::translate("DataAnalysis", "31", nullptr));
        MinuteSCB->setItemText(32, QCoreApplication::translate("DataAnalysis", "32", nullptr));
        MinuteSCB->setItemText(33, QCoreApplication::translate("DataAnalysis", "33", nullptr));
        MinuteSCB->setItemText(34, QCoreApplication::translate("DataAnalysis", "34", nullptr));
        MinuteSCB->setItemText(35, QCoreApplication::translate("DataAnalysis", "35", nullptr));
        MinuteSCB->setItemText(36, QCoreApplication::translate("DataAnalysis", "36", nullptr));
        MinuteSCB->setItemText(37, QCoreApplication::translate("DataAnalysis", "37", nullptr));
        MinuteSCB->setItemText(38, QCoreApplication::translate("DataAnalysis", "38", nullptr));
        MinuteSCB->setItemText(39, QCoreApplication::translate("DataAnalysis", "39", nullptr));
        MinuteSCB->setItemText(40, QCoreApplication::translate("DataAnalysis", "40", nullptr));
        MinuteSCB->setItemText(41, QCoreApplication::translate("DataAnalysis", "41", nullptr));
        MinuteSCB->setItemText(42, QCoreApplication::translate("DataAnalysis", "42", nullptr));
        MinuteSCB->setItemText(43, QCoreApplication::translate("DataAnalysis", "43", nullptr));
        MinuteSCB->setItemText(44, QCoreApplication::translate("DataAnalysis", "44", nullptr));
        MinuteSCB->setItemText(45, QCoreApplication::translate("DataAnalysis", "45", nullptr));
        MinuteSCB->setItemText(46, QCoreApplication::translate("DataAnalysis", "46", nullptr));
        MinuteSCB->setItemText(47, QCoreApplication::translate("DataAnalysis", "47", nullptr));
        MinuteSCB->setItemText(48, QCoreApplication::translate("DataAnalysis", "48", nullptr));
        MinuteSCB->setItemText(49, QCoreApplication::translate("DataAnalysis", "49", nullptr));
        MinuteSCB->setItemText(50, QCoreApplication::translate("DataAnalysis", "50", nullptr));
        MinuteSCB->setItemText(51, QCoreApplication::translate("DataAnalysis", "51", nullptr));
        MinuteSCB->setItemText(52, QCoreApplication::translate("DataAnalysis", "52", nullptr));
        MinuteSCB->setItemText(53, QCoreApplication::translate("DataAnalysis", "53", nullptr));
        MinuteSCB->setItemText(54, QCoreApplication::translate("DataAnalysis", "54", nullptr));
        MinuteSCB->setItemText(55, QCoreApplication::translate("DataAnalysis", "55", nullptr));
        MinuteSCB->setItemText(56, QCoreApplication::translate("DataAnalysis", "56", nullptr));
        MinuteSCB->setItemText(57, QCoreApplication::translate("DataAnalysis", "57", nullptr));
        MinuteSCB->setItemText(58, QCoreApplication::translate("DataAnalysis", "58", nullptr));
        MinuteSCB->setItemText(59, QCoreApplication::translate("DataAnalysis", "59", nullptr));

        label_3->setText(QString());
        YearLB_2->setText(QCoreApplication::translate("DataAnalysis", "    \345\271\264", nullptr));
        monthLB_2->setText(QCoreApplication::translate("DataAnalysis", "    \346\234\210", nullptr));
        DayLB_2->setText(QCoreApplication::translate("DataAnalysis", "    \346\227\245", nullptr));
        HourLB_2->setText(QCoreApplication::translate("DataAnalysis", "    \346\227\266", nullptr));
        minuteLB_2->setText(QCoreApplication::translate("DataAnalysis", "    \345\210\206", nullptr));
        timeLB_2->setText(QCoreApplication::translate("DataAnalysis", "\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        YearECB->setItemText(0, QCoreApplication::translate("DataAnalysis", "2024", nullptr));
        YearECB->setItemText(1, QCoreApplication::translate("DataAnalysis", "2025", nullptr));
        YearECB->setItemText(2, QCoreApplication::translate("DataAnalysis", "2026", nullptr));
        YearECB->setItemText(3, QCoreApplication::translate("DataAnalysis", "2027", nullptr));
        YearECB->setItemText(4, QCoreApplication::translate("DataAnalysis", "2028", nullptr));
        YearECB->setItemText(5, QCoreApplication::translate("DataAnalysis", "2029", nullptr));
        YearECB->setItemText(6, QCoreApplication::translate("DataAnalysis", "2030", nullptr));
        YearECB->setItemText(7, QCoreApplication::translate("DataAnalysis", "2031", nullptr));
        YearECB->setItemText(8, QCoreApplication::translate("DataAnalysis", "2032", nullptr));
        YearECB->setItemText(9, QCoreApplication::translate("DataAnalysis", "2033", nullptr));
        YearECB->setItemText(10, QCoreApplication::translate("DataAnalysis", "2034", nullptr));

        MonthECB->setItemText(0, QCoreApplication::translate("DataAnalysis", "01", nullptr));
        MonthECB->setItemText(1, QCoreApplication::translate("DataAnalysis", "02", nullptr));
        MonthECB->setItemText(2, QCoreApplication::translate("DataAnalysis", "03", nullptr));
        MonthECB->setItemText(3, QCoreApplication::translate("DataAnalysis", "04", nullptr));
        MonthECB->setItemText(4, QCoreApplication::translate("DataAnalysis", "05", nullptr));
        MonthECB->setItemText(5, QCoreApplication::translate("DataAnalysis", "06", nullptr));
        MonthECB->setItemText(6, QCoreApplication::translate("DataAnalysis", "07", nullptr));
        MonthECB->setItemText(7, QCoreApplication::translate("DataAnalysis", "08", nullptr));
        MonthECB->setItemText(8, QCoreApplication::translate("DataAnalysis", "09", nullptr));
        MonthECB->setItemText(9, QCoreApplication::translate("DataAnalysis", "10", nullptr));
        MonthECB->setItemText(10, QCoreApplication::translate("DataAnalysis", "11", nullptr));
        MonthECB->setItemText(11, QCoreApplication::translate("DataAnalysis", "12", nullptr));

        DayECB->setItemText(0, QCoreApplication::translate("DataAnalysis", "01", nullptr));
        DayECB->setItemText(1, QCoreApplication::translate("DataAnalysis", "02", nullptr));
        DayECB->setItemText(2, QCoreApplication::translate("DataAnalysis", "03", nullptr));
        DayECB->setItemText(3, QCoreApplication::translate("DataAnalysis", "04", nullptr));
        DayECB->setItemText(4, QCoreApplication::translate("DataAnalysis", "05", nullptr));
        DayECB->setItemText(5, QCoreApplication::translate("DataAnalysis", "06", nullptr));
        DayECB->setItemText(6, QCoreApplication::translate("DataAnalysis", "07", nullptr));
        DayECB->setItemText(7, QCoreApplication::translate("DataAnalysis", "08", nullptr));
        DayECB->setItemText(8, QCoreApplication::translate("DataAnalysis", "09", nullptr));
        DayECB->setItemText(9, QCoreApplication::translate("DataAnalysis", "10", nullptr));
        DayECB->setItemText(10, QCoreApplication::translate("DataAnalysis", "11", nullptr));
        DayECB->setItemText(11, QCoreApplication::translate("DataAnalysis", "12", nullptr));
        DayECB->setItemText(12, QCoreApplication::translate("DataAnalysis", "13", nullptr));
        DayECB->setItemText(13, QCoreApplication::translate("DataAnalysis", "14", nullptr));
        DayECB->setItemText(14, QCoreApplication::translate("DataAnalysis", "15", nullptr));
        DayECB->setItemText(15, QCoreApplication::translate("DataAnalysis", "16", nullptr));
        DayECB->setItemText(16, QCoreApplication::translate("DataAnalysis", "17", nullptr));
        DayECB->setItemText(17, QCoreApplication::translate("DataAnalysis", "18", nullptr));
        DayECB->setItemText(18, QCoreApplication::translate("DataAnalysis", "19", nullptr));
        DayECB->setItemText(19, QCoreApplication::translate("DataAnalysis", "20", nullptr));
        DayECB->setItemText(20, QCoreApplication::translate("DataAnalysis", "21", nullptr));
        DayECB->setItemText(21, QCoreApplication::translate("DataAnalysis", "22", nullptr));
        DayECB->setItemText(22, QCoreApplication::translate("DataAnalysis", "23", nullptr));
        DayECB->setItemText(23, QCoreApplication::translate("DataAnalysis", "24", nullptr));
        DayECB->setItemText(24, QCoreApplication::translate("DataAnalysis", "25", nullptr));
        DayECB->setItemText(25, QCoreApplication::translate("DataAnalysis", "26", nullptr));
        DayECB->setItemText(26, QCoreApplication::translate("DataAnalysis", "27", nullptr));
        DayECB->setItemText(27, QCoreApplication::translate("DataAnalysis", "28", nullptr));
        DayECB->setItemText(28, QCoreApplication::translate("DataAnalysis", "29", nullptr));
        DayECB->setItemText(29, QCoreApplication::translate("DataAnalysis", "30", nullptr));
        DayECB->setItemText(30, QCoreApplication::translate("DataAnalysis", "31", nullptr));

        HourECB->setItemText(0, QCoreApplication::translate("DataAnalysis", "00", nullptr));
        HourECB->setItemText(1, QCoreApplication::translate("DataAnalysis", "01", nullptr));
        HourECB->setItemText(2, QCoreApplication::translate("DataAnalysis", "02", nullptr));
        HourECB->setItemText(3, QCoreApplication::translate("DataAnalysis", "03", nullptr));
        HourECB->setItemText(4, QCoreApplication::translate("DataAnalysis", "04", nullptr));
        HourECB->setItemText(5, QCoreApplication::translate("DataAnalysis", "05", nullptr));
        HourECB->setItemText(6, QCoreApplication::translate("DataAnalysis", "06", nullptr));
        HourECB->setItemText(7, QCoreApplication::translate("DataAnalysis", "07", nullptr));
        HourECB->setItemText(8, QCoreApplication::translate("DataAnalysis", "08", nullptr));
        HourECB->setItemText(9, QCoreApplication::translate("DataAnalysis", "09", nullptr));
        HourECB->setItemText(10, QCoreApplication::translate("DataAnalysis", "10", nullptr));
        HourECB->setItemText(11, QCoreApplication::translate("DataAnalysis", "11", nullptr));
        HourECB->setItemText(12, QCoreApplication::translate("DataAnalysis", "12", nullptr));
        HourECB->setItemText(13, QCoreApplication::translate("DataAnalysis", "13", nullptr));
        HourECB->setItemText(14, QCoreApplication::translate("DataAnalysis", "14", nullptr));
        HourECB->setItemText(15, QCoreApplication::translate("DataAnalysis", "15", nullptr));
        HourECB->setItemText(16, QCoreApplication::translate("DataAnalysis", "16", nullptr));
        HourECB->setItemText(17, QCoreApplication::translate("DataAnalysis", "17", nullptr));
        HourECB->setItemText(18, QCoreApplication::translate("DataAnalysis", "18", nullptr));
        HourECB->setItemText(19, QCoreApplication::translate("DataAnalysis", "19", nullptr));
        HourECB->setItemText(20, QCoreApplication::translate("DataAnalysis", "20", nullptr));
        HourECB->setItemText(21, QCoreApplication::translate("DataAnalysis", "21", nullptr));
        HourECB->setItemText(22, QCoreApplication::translate("DataAnalysis", "22", nullptr));
        HourECB->setItemText(23, QCoreApplication::translate("DataAnalysis", "23", nullptr));

        MinuteECB->setItemText(0, QCoreApplication::translate("DataAnalysis", "00", nullptr));
        MinuteECB->setItemText(1, QCoreApplication::translate("DataAnalysis", "01", nullptr));
        MinuteECB->setItemText(2, QCoreApplication::translate("DataAnalysis", "02", nullptr));
        MinuteECB->setItemText(3, QCoreApplication::translate("DataAnalysis", "03", nullptr));
        MinuteECB->setItemText(4, QCoreApplication::translate("DataAnalysis", "04", nullptr));
        MinuteECB->setItemText(5, QCoreApplication::translate("DataAnalysis", "05", nullptr));
        MinuteECB->setItemText(6, QCoreApplication::translate("DataAnalysis", "06", nullptr));
        MinuteECB->setItemText(7, QCoreApplication::translate("DataAnalysis", "07", nullptr));
        MinuteECB->setItemText(8, QCoreApplication::translate("DataAnalysis", "08", nullptr));
        MinuteECB->setItemText(9, QCoreApplication::translate("DataAnalysis", "09", nullptr));
        MinuteECB->setItemText(10, QCoreApplication::translate("DataAnalysis", "10", nullptr));
        MinuteECB->setItemText(11, QCoreApplication::translate("DataAnalysis", "11", nullptr));
        MinuteECB->setItemText(12, QCoreApplication::translate("DataAnalysis", "12", nullptr));
        MinuteECB->setItemText(13, QCoreApplication::translate("DataAnalysis", "13", nullptr));
        MinuteECB->setItemText(14, QCoreApplication::translate("DataAnalysis", "14", nullptr));
        MinuteECB->setItemText(15, QCoreApplication::translate("DataAnalysis", "15", nullptr));
        MinuteECB->setItemText(16, QCoreApplication::translate("DataAnalysis", "16", nullptr));
        MinuteECB->setItemText(17, QCoreApplication::translate("DataAnalysis", "17", nullptr));
        MinuteECB->setItemText(18, QCoreApplication::translate("DataAnalysis", "18", nullptr));
        MinuteECB->setItemText(19, QCoreApplication::translate("DataAnalysis", "19", nullptr));
        MinuteECB->setItemText(20, QCoreApplication::translate("DataAnalysis", "20", nullptr));
        MinuteECB->setItemText(21, QCoreApplication::translate("DataAnalysis", "21", nullptr));
        MinuteECB->setItemText(22, QCoreApplication::translate("DataAnalysis", "22", nullptr));
        MinuteECB->setItemText(23, QCoreApplication::translate("DataAnalysis", "23", nullptr));
        MinuteECB->setItemText(24, QCoreApplication::translate("DataAnalysis", "24", nullptr));
        MinuteECB->setItemText(25, QCoreApplication::translate("DataAnalysis", "25", nullptr));
        MinuteECB->setItemText(26, QCoreApplication::translate("DataAnalysis", "26", nullptr));
        MinuteECB->setItemText(27, QCoreApplication::translate("DataAnalysis", "27", nullptr));
        MinuteECB->setItemText(28, QCoreApplication::translate("DataAnalysis", "28", nullptr));
        MinuteECB->setItemText(29, QCoreApplication::translate("DataAnalysis", "29", nullptr));
        MinuteECB->setItemText(30, QCoreApplication::translate("DataAnalysis", "30", nullptr));
        MinuteECB->setItemText(31, QCoreApplication::translate("DataAnalysis", "31", nullptr));
        MinuteECB->setItemText(32, QCoreApplication::translate("DataAnalysis", "32", nullptr));
        MinuteECB->setItemText(33, QCoreApplication::translate("DataAnalysis", "33", nullptr));
        MinuteECB->setItemText(34, QCoreApplication::translate("DataAnalysis", "34", nullptr));
        MinuteECB->setItemText(35, QCoreApplication::translate("DataAnalysis", "35", nullptr));
        MinuteECB->setItemText(36, QCoreApplication::translate("DataAnalysis", "36", nullptr));
        MinuteECB->setItemText(37, QCoreApplication::translate("DataAnalysis", "37", nullptr));
        MinuteECB->setItemText(38, QCoreApplication::translate("DataAnalysis", "38", nullptr));
        MinuteECB->setItemText(39, QCoreApplication::translate("DataAnalysis", "39", nullptr));
        MinuteECB->setItemText(40, QCoreApplication::translate("DataAnalysis", "40", nullptr));
        MinuteECB->setItemText(41, QCoreApplication::translate("DataAnalysis", "41", nullptr));
        MinuteECB->setItemText(42, QCoreApplication::translate("DataAnalysis", "42", nullptr));
        MinuteECB->setItemText(43, QCoreApplication::translate("DataAnalysis", "43", nullptr));
        MinuteECB->setItemText(44, QCoreApplication::translate("DataAnalysis", "44", nullptr));
        MinuteECB->setItemText(45, QCoreApplication::translate("DataAnalysis", "45", nullptr));
        MinuteECB->setItemText(46, QCoreApplication::translate("DataAnalysis", "46", nullptr));
        MinuteECB->setItemText(47, QCoreApplication::translate("DataAnalysis", "47", nullptr));
        MinuteECB->setItemText(48, QCoreApplication::translate("DataAnalysis", "48", nullptr));
        MinuteECB->setItemText(49, QCoreApplication::translate("DataAnalysis", "49", nullptr));
        MinuteECB->setItemText(50, QCoreApplication::translate("DataAnalysis", "50", nullptr));
        MinuteECB->setItemText(51, QCoreApplication::translate("DataAnalysis", "51", nullptr));
        MinuteECB->setItemText(52, QCoreApplication::translate("DataAnalysis", "52", nullptr));
        MinuteECB->setItemText(53, QCoreApplication::translate("DataAnalysis", "53", nullptr));
        MinuteECB->setItemText(54, QCoreApplication::translate("DataAnalysis", "54", nullptr));
        MinuteECB->setItemText(55, QCoreApplication::translate("DataAnalysis", "55", nullptr));
        MinuteECB->setItemText(56, QCoreApplication::translate("DataAnalysis", "56", nullptr));
        MinuteECB->setItemText(57, QCoreApplication::translate("DataAnalysis", "57", nullptr));
        MinuteECB->setItemText(58, QCoreApplication::translate("DataAnalysis", "58", nullptr));
        MinuteECB->setItemText(59, QCoreApplication::translate("DataAnalysis", "59", nullptr));

        searchBT->setText(QCoreApplication::translate("DataAnalysis", "\346\220\234\347\264\242", nullptr));
        clearBT->setText(QCoreApplication::translate("DataAnalysis", "\346\270\205\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataAnalysis: public Ui_DataAnalysis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAANALYSIS_H

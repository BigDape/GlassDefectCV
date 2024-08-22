/********************************************************************************
** Form generated from reading UI file 'BasicFunction.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASICFUNCTION_H
#define UI_BASICFUNCTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QBasicFunction
{
public:
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *label_fps;
    QGroupBox *General;
    QGridLayout *gridLayout;
    QPushButton *toolButton_Scan;
    QPushButton *pushButton_Start;
    QComboBox *comboBox_Devices;
    QPushButton *pushButton_Open;
    QPushButton *pushButton_iniSave;
    QPushButton *pushButton_Load;
    QPushButton *pushButton_Property;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_Save;
    QGroupBox *groupBox_trigger;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_trigger;
    QGroupBox *groupBox_AWB;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_OnceWB;
    QGroupBox *groupBox_AEOper;
    QGridLayout *gridLayout_6;
    QSpinBox *spinBox_AETarget;
    QLabel *label_AE_TargetLightness;
    QLabel *label_AE_Mode;
    QComboBox *comboBox_AEMode;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_7;
    QDoubleSpinBox *doubleSpinBox_ExpoTime;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_8;
    QDoubleSpinBox *doubleSpinBox_Gain;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_10;
    QComboBox *comboBox_ROI;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox_ColorSolution;
    QSpacerItem *verticalSpacer;
    QGraphicsView *graphicsView_PreView;

    void setupUi(QWidget *QBasicFunction)
    {
        if (QBasicFunction->objectName().isEmpty())
            QBasicFunction->setObjectName(QString::fromUtf8("QBasicFunction"));
        QBasicFunction->resize(1111, 681);
        horizontalLayout = new QHBoxLayout(QBasicFunction);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        scrollArea = new QScrollArea(QBasicFunction);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(500, 0));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 484, 804));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_fps = new QLabel(scrollAreaWidgetContents);
        label_fps->setObjectName(QString::fromUtf8("label_fps"));

        verticalLayout->addWidget(label_fps);

        General = new QGroupBox(scrollAreaWidgetContents);
        General->setObjectName(QString::fromUtf8("General"));
        gridLayout = new QGridLayout(General);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        toolButton_Scan = new QPushButton(General);
        toolButton_Scan->setObjectName(QString::fromUtf8("toolButton_Scan"));

        gridLayout->addWidget(toolButton_Scan, 0, 1, 1, 2);

        pushButton_Start = new QPushButton(General);
        pushButton_Start->setObjectName(QString::fromUtf8("pushButton_Start"));

        gridLayout->addWidget(pushButton_Start, 2, 2, 1, 1);

        comboBox_Devices = new QComboBox(General);
        comboBox_Devices->setObjectName(QString::fromUtf8("comboBox_Devices"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_Devices->sizePolicy().hasHeightForWidth());
        comboBox_Devices->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBox_Devices, 1, 1, 1, 2);

        pushButton_Open = new QPushButton(General);
        pushButton_Open->setObjectName(QString::fromUtf8("pushButton_Open"));

        gridLayout->addWidget(pushButton_Open, 2, 1, 1, 1);

        pushButton_iniSave = new QPushButton(General);
        pushButton_iniSave->setObjectName(QString::fromUtf8("pushButton_iniSave"));

        gridLayout->addWidget(pushButton_iniSave, 3, 1, 1, 1);

        pushButton_Load = new QPushButton(General);
        pushButton_Load->setObjectName(QString::fromUtf8("pushButton_Load"));

        gridLayout->addWidget(pushButton_Load, 3, 2, 1, 1);

        pushButton_Property = new QPushButton(General);
        pushButton_Property->setObjectName(QString::fromUtf8("pushButton_Property"));

        gridLayout->addWidget(pushButton_Property, 4, 1, 1, 2);


        verticalLayout->addWidget(General);

        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pushButton_Save = new QPushButton(groupBox);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));

        gridLayout_3->addWidget(pushButton_Save, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_trigger = new QGroupBox(scrollAreaWidgetContents);
        groupBox_trigger->setObjectName(QString::fromUtf8("groupBox_trigger"));
        groupBox_trigger->setCheckable(true);
        groupBox_trigger->setChecked(false);
        gridLayout_4 = new QGridLayout(groupBox_trigger);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButton_trigger = new QPushButton(groupBox_trigger);
        pushButton_trigger->setObjectName(QString::fromUtf8("pushButton_trigger"));

        gridLayout_4->addWidget(pushButton_trigger, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_trigger);

        groupBox_AWB = new QGroupBox(scrollAreaWidgetContents);
        groupBox_AWB->setObjectName(QString::fromUtf8("groupBox_AWB"));
        groupBox_AWB->setCheckable(true);
        groupBox_AWB->setChecked(false);
        gridLayout_5 = new QGridLayout(groupBox_AWB);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButton_OnceWB = new QPushButton(groupBox_AWB);
        pushButton_OnceWB->setObjectName(QString::fromUtf8("pushButton_OnceWB"));

        gridLayout_5->addWidget(pushButton_OnceWB, 3, 0, 1, 1);


        verticalLayout->addWidget(groupBox_AWB);

        groupBox_AEOper = new QGroupBox(scrollAreaWidgetContents);
        groupBox_AEOper->setObjectName(QString::fromUtf8("groupBox_AEOper"));
        groupBox_AEOper->setCheckable(true);
        gridLayout_6 = new QGridLayout(groupBox_AEOper);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        spinBox_AETarget = new QSpinBox(groupBox_AEOper);
        spinBox_AETarget->setObjectName(QString::fromUtf8("spinBox_AETarget"));

        gridLayout_6->addWidget(spinBox_AETarget, 3, 0, 1, 2);

        label_AE_TargetLightness = new QLabel(groupBox_AEOper);
        label_AE_TargetLightness->setObjectName(QString::fromUtf8("label_AE_TargetLightness"));

        gridLayout_6->addWidget(label_AE_TargetLightness, 2, 0, 1, 1);

        label_AE_Mode = new QLabel(groupBox_AEOper);
        label_AE_Mode->setObjectName(QString::fromUtf8("label_AE_Mode"));

        gridLayout_6->addWidget(label_AE_Mode, 1, 0, 1, 1);

        comboBox_AEMode = new QComboBox(groupBox_AEOper);
        comboBox_AEMode->setObjectName(QString::fromUtf8("comboBox_AEMode"));

        gridLayout_6->addWidget(comboBox_AEMode, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox_AEOper);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_7 = new QGridLayout(groupBox_3);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        doubleSpinBox_ExpoTime = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox_ExpoTime->setObjectName(QString::fromUtf8("doubleSpinBox_ExpoTime"));
        doubleSpinBox_ExpoTime->setDecimals(2);
        doubleSpinBox_ExpoTime->setSingleStep(1000.000000000000000);

        gridLayout_7->addWidget(doubleSpinBox_ExpoTime, 0, 0, 1, 2);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_8 = new QGridLayout(groupBox_4);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        doubleSpinBox_Gain = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_Gain->setObjectName(QString::fromUtf8("doubleSpinBox_Gain"));

        gridLayout_8->addWidget(doubleSpinBox_Gain, 0, 0, 1, 2);


        verticalLayout->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_10 = new QGridLayout(groupBox_5);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        comboBox_ROI = new QComboBox(groupBox_5);
        comboBox_ROI->setObjectName(QString::fromUtf8("comboBox_ROI"));
        comboBox_ROI->setMinimumSize(QSize(0, 0));
        comboBox_ROI->setFocusPolicy(Qt::WheelFocus);

        gridLayout_10->addWidget(comboBox_ROI, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_5);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        comboBox_ColorSolution = new QComboBox(groupBox_2);
        comboBox_ColorSolution->setObjectName(QString::fromUtf8("comboBox_ColorSolution"));

        gridLayout_2->addWidget(comboBox_ColorSolution, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        graphicsView_PreView = new QGraphicsView(QBasicFunction);
        graphicsView_PreView->setObjectName(QString::fromUtf8("graphicsView_PreView"));

        horizontalLayout->addWidget(graphicsView_PreView);


        retranslateUi(QBasicFunction);

        QMetaObject::connectSlotsByName(QBasicFunction);
    } // setupUi

    void retranslateUi(QWidget *QBasicFunction)
    {
        QBasicFunction->setWindowTitle(QCoreApplication::translate("QBasicFunction", "QBasicFunction", nullptr));
        label_fps->setText(QCoreApplication::translate("QBasicFunction", "fps", nullptr));
        General->setTitle(QCoreApplication::translate("QBasicFunction", "General", nullptr));
        toolButton_Scan->setText(QCoreApplication::translate("QBasicFunction", "Scan", nullptr));
        pushButton_Start->setText(QCoreApplication::translate("QBasicFunction", "Start", nullptr));
        pushButton_Open->setText(QCoreApplication::translate("QBasicFunction", "Open", nullptr));
        pushButton_iniSave->setText(QCoreApplication::translate("QBasicFunction", "Save ini", nullptr));
        pushButton_Load->setText(QCoreApplication::translate("QBasicFunction", "Load ini", nullptr));
        pushButton_Property->setText(QCoreApplication::translate("QBasicFunction", "Property", nullptr));
        groupBox->setTitle(QCoreApplication::translate("QBasicFunction", "Save Image", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("QBasicFunction", "Save", nullptr));
        groupBox_trigger->setTitle(QCoreApplication::translate("QBasicFunction", "Trigger", nullptr));
        pushButton_trigger->setText(QCoreApplication::translate("QBasicFunction", "Trigger Fire", nullptr));
        groupBox_AWB->setTitle(QCoreApplication::translate("QBasicFunction", "Auto White Balance", nullptr));
        pushButton_OnceWB->setText(QCoreApplication::translate("QBasicFunction", "Once White Balance", nullptr));
        groupBox_AEOper->setTitle(QCoreApplication::translate("QBasicFunction", "Auto Exposure Enable", nullptr));
        label_AE_TargetLightness->setText(QCoreApplication::translate("QBasicFunction", "AE Target Value", nullptr));
        label_AE_Mode->setText(QCoreApplication::translate("QBasicFunction", "AE Mode   ", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("QBasicFunction", "Exposure Time(us)", nullptr));
        doubleSpinBox_ExpoTime->setSuffix(QString());
        groupBox_4->setTitle(QCoreApplication::translate("QBasicFunction", "Gain(x)", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("QBasicFunction", "Quick ROI", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("QBasicFunction", "ColorSolution", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QBasicFunction: public Ui_QBasicFunction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASICFUNCTION_H

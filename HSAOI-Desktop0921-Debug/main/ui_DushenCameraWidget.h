/********************************************************************************
** Form generated from reading UI file 'DushenCameraWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DUSHENCAMERAWIDGET_H
#define UI_DUSHENCAMERAWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DushenCameraWidget
{
public:
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab_Display;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbl_CameraName;
    QLabel *lbl_FrameInfo;
    QPushButton *pushButton_trigger;
    QGraphicsView *graphicsView_Image;
    QWidget *tab_Settings;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_Scan;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox_Devices;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *cbx_SoftTrigger;
    QPushButton *pushButton_Open;
    QPushButton *pushButton_Start;
    QPushButton *pushButton_Property;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Saveini;
    QPushButton *pushButton_Loadini;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lbl_multifield;
    QComboBox *comboBox_MultiFieldSelect;
    QPushButton *pushButton_MultiFieldSelect;

    void setupUi(QWidget *DushenCameraWidget)
    {
        if (DushenCameraWidget->objectName().isEmpty())
            DushenCameraWidget->setObjectName(QString::fromUtf8("DushenCameraWidget"));
        DushenCameraWidget->resize(400, 340);
        verticalLayoutWidget_2 = new QWidget(DushenCameraWidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 402, 342));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(verticalLayoutWidget_2);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(400, 340));
        tabWidget->setMaximumSize(QSize(400, 340));
        tab_Display = new QWidget();
        tab_Display->setObjectName(QString::fromUtf8("tab_Display"));
        verticalLayoutWidget = new QWidget(tab_Display);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-1, 3, 401, 311));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(20, -1, 20, -1);
        lbl_CameraName = new QLabel(verticalLayoutWidget);
        lbl_CameraName->setObjectName(QString::fromUtf8("lbl_CameraName"));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(10);
        lbl_CameraName->setFont(font);
        lbl_CameraName->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lbl_CameraName);

        lbl_FrameInfo = new QLabel(verticalLayoutWidget);
        lbl_FrameInfo->setObjectName(QString::fromUtf8("lbl_FrameInfo"));
        lbl_FrameInfo->setEnabled(true);
        lbl_FrameInfo->setFont(font);
        lbl_FrameInfo->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lbl_FrameInfo);

        pushButton_trigger = new QPushButton(verticalLayoutWidget);
        pushButton_trigger->setObjectName(QString::fromUtf8("pushButton_trigger"));
        pushButton_trigger->setIconSize(QSize(16, 16));

        horizontalLayout_3->addWidget(pushButton_trigger);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 3);
        horizontalLayout_3->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_3);

        graphicsView_Image = new QGraphicsView(verticalLayoutWidget);
        graphicsView_Image->setObjectName(QString::fromUtf8("graphicsView_Image"));

        verticalLayout->addWidget(graphicsView_Image);

        tabWidget->addTab(tab_Display, QString());
        tab_Settings = new QWidget();
        tab_Settings->setObjectName(QString::fromUtf8("tab_Settings"));
        gridLayoutWidget = new QWidget(tab_Settings);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 82, 31));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_Scan = new QPushButton(gridLayoutWidget);
        pushButton_Scan->setObjectName(QString::fromUtf8("pushButton_Scan"));
        pushButton_Scan->setIconSize(QSize(16, 16));

        gridLayout->addWidget(pushButton_Scan, 0, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(tab_Settings);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(100, 10, 281, 31));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        comboBox_Devices = new QComboBox(gridLayoutWidget_2);
        comboBox_Devices->setObjectName(QString::fromUtf8("comboBox_Devices"));

        gridLayout_2->addWidget(comboBox_Devices, 0, 0, 1, 1);

        horizontalLayoutWidget = new QWidget(tab_Settings);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 40, 371, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cbx_SoftTrigger = new QCheckBox(horizontalLayoutWidget);
        cbx_SoftTrigger->setObjectName(QString::fromUtf8("cbx_SoftTrigger"));
        cbx_SoftTrigger->setChecked(false);

        horizontalLayout->addWidget(cbx_SoftTrigger);

        pushButton_Open = new QPushButton(horizontalLayoutWidget);
        pushButton_Open->setObjectName(QString::fromUtf8("pushButton_Open"));
        pushButton_Open->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(pushButton_Open);

        pushButton_Start = new QPushButton(horizontalLayoutWidget);
        pushButton_Start->setObjectName(QString::fromUtf8("pushButton_Start"));
        pushButton_Start->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(pushButton_Start);

        pushButton_Property = new QPushButton(horizontalLayoutWidget);
        pushButton_Property->setObjectName(QString::fromUtf8("pushButton_Property"));
        pushButton_Property->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(pushButton_Property);

        horizontalLayoutWidget_2 = new QWidget(tab_Settings);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 70, 371, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_Save = new QPushButton(horizontalLayoutWidget_2);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));
        pushButton_Save->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(pushButton_Save);

        pushButton_Saveini = new QPushButton(horizontalLayoutWidget_2);
        pushButton_Saveini->setObjectName(QString::fromUtf8("pushButton_Saveini"));
        pushButton_Saveini->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(pushButton_Saveini);

        pushButton_Loadini = new QPushButton(horizontalLayoutWidget_2);
        pushButton_Loadini->setObjectName(QString::fromUtf8("pushButton_Loadini"));
        pushButton_Loadini->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(pushButton_Loadini);

        horizontalLayoutWidget_3 = new QWidget(tab_Settings);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 100, 371, 31));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        lbl_multifield = new QLabel(horizontalLayoutWidget_3);
        lbl_multifield->setObjectName(QString::fromUtf8("lbl_multifield"));
        lbl_multifield->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(lbl_multifield);

        comboBox_MultiFieldSelect = new QComboBox(horizontalLayoutWidget_3);
        comboBox_MultiFieldSelect->setObjectName(QString::fromUtf8("comboBox_MultiFieldSelect"));

        horizontalLayout_4->addWidget(comboBox_MultiFieldSelect);

        pushButton_MultiFieldSelect = new QPushButton(horizontalLayoutWidget_3);
        pushButton_MultiFieldSelect->setObjectName(QString::fromUtf8("pushButton_MultiFieldSelect"));

        horizontalLayout_4->addWidget(pushButton_MultiFieldSelect);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 4);
        horizontalLayout_4->setStretch(2, 2);
        tabWidget->addTab(tab_Settings, QString());

        verticalLayout_3->addWidget(tabWidget);


        retranslateUi(DushenCameraWidget);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(DushenCameraWidget);
    } // setupUi

    void retranslateUi(QWidget *DushenCameraWidget)
    {
        DushenCameraWidget->setWindowTitle(QCoreApplication::translate("DushenCameraWidget", "Form", nullptr));
        lbl_CameraName->setText(QCoreApplication::translate("DushenCameraWidget", "Camera 0", nullptr));
        lbl_FrameInfo->setText(QCoreApplication::translate("DushenCameraWidget", "FPS :", nullptr));
        pushButton_trigger->setText(QCoreApplication::translate("DushenCameraWidget", "TriggerFrame", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Display), QCoreApplication::translate("DushenCameraWidget", "Display", nullptr));
        pushButton_Scan->setText(QCoreApplication::translate("DushenCameraWidget", "Scan", nullptr));
        cbx_SoftTrigger->setText(QCoreApplication::translate("DushenCameraWidget", "Trigger", nullptr));
        pushButton_Open->setText(QCoreApplication::translate("DushenCameraWidget", "Open", nullptr));
        pushButton_Start->setText(QCoreApplication::translate("DushenCameraWidget", "Start", nullptr));
        pushButton_Property->setText(QCoreApplication::translate("DushenCameraWidget", "Property", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("DushenCameraWidget", "SaveAll", nullptr));
        pushButton_Saveini->setText(QCoreApplication::translate("DushenCameraWidget", "Save_ini", nullptr));
        pushButton_Loadini->setText(QCoreApplication::translate("DushenCameraWidget", "Load_ini", nullptr));
        lbl_multifield->setText(QCoreApplication::translate("DushenCameraWidget", "FieldNum", nullptr));
        pushButton_MultiFieldSelect->setText(QCoreApplication::translate("DushenCameraWidget", "Select", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Settings), QCoreApplication::translate("DushenCameraWidget", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DushenCameraWidget: public Ui_DushenCameraWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DUSHENCAMERAWIDGET_H

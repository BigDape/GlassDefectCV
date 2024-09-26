/********************************************************************************
** Form generated from reading UI file 'cameraslayout.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERASLAYOUT_H
#define UI_CAMERASLAYOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CamerasLayout
{
public:

    void setupUi(QWidget *CamerasLayout)
    {
        if (CamerasLayout->objectName().isEmpty())
            CamerasLayout->setObjectName(QString::fromUtf8("CamerasLayout"));
        CamerasLayout->resize(400, 300);

        retranslateUi(CamerasLayout);

        QMetaObject::connectSlotsByName(CamerasLayout);
    } // setupUi

    void retranslateUi(QWidget *CamerasLayout)
    {
        CamerasLayout->setWindowTitle(QCoreApplication::translate("CamerasLayout", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CamerasLayout: public Ui_CamerasLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERASLAYOUT_H

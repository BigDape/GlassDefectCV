/********************************************************************************
** Form generated from reading UI file 'CamerasWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERASWIDGET_H
#define UI_CAMERASWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CamerasWidget
{
public:

    void setupUi(QWidget *CamerasWidget)
    {
        if (CamerasWidget->objectName().isEmpty())
            CamerasWidget->setObjectName(QString::fromUtf8("CamerasWidget"));
        CamerasWidget->resize(400, 300);

        retranslateUi(CamerasWidget);

        QMetaObject::connectSlotsByName(CamerasWidget);
    } // setupUi

    void retranslateUi(QWidget *CamerasWidget)
    {
        CamerasWidget->setWindowTitle(QCoreApplication::translate("CamerasWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CamerasWidget: public Ui_CamerasWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERASWIDGET_H

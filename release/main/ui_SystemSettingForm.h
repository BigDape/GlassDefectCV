/********************************************************************************
** Form generated from reading UI file 'SystemSettingForm.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMSETTINGFORM_H
#define UI_SYSTEMSETTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemSettingForm
{
public:

    void setupUi(QWidget *SystemSettingForm)
    {
        if (SystemSettingForm->objectName().isEmpty())
            SystemSettingForm->setObjectName(QString::fromUtf8("SystemSettingForm"));
        SystemSettingForm->resize(400, 300);

        retranslateUi(SystemSettingForm);

        QMetaObject::connectSlotsByName(SystemSettingForm);
    } // setupUi

    void retranslateUi(QWidget *SystemSettingForm)
    {
        SystemSettingForm->setWindowTitle(QCoreApplication::translate("SystemSettingForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SystemSettingForm: public Ui_SystemSettingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSETTINGFORM_H

/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLineEdit *userLE;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *passwdLE;
    QPushButton *loginBT;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(400, 300);
        userLE = new QLineEdit(Login);
        userLE->setObjectName(QString::fromUtf8("userLE"));
        userLE->setGeometry(QRect(164, 85, 113, 20));
        label = new QLabel(Login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 89, 54, 12));
        label_2 = new QLabel(Login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(110, 129, 54, 12));
        passwdLE = new QLineEdit(Login);
        passwdLE->setObjectName(QString::fromUtf8("passwdLE"));
        passwdLE->setGeometry(QRect(165, 126, 111, 20));
        loginBT = new QPushButton(Login);
        loginBT->setObjectName(QString::fromUtf8("loginBT"));
        loginBT->setGeometry(QRect(170, 179, 75, 23));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Form", nullptr));
        label->setText(QCoreApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "\345\257\206\347\240\201", nullptr));
        loginBT->setText(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H

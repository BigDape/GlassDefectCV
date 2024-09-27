/********************************************************************************
** Form generated from reading UI file 'Calibrate.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATE_H
#define UI_CALIBRATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calibrate
{
public:
    QLabel *label;
    QLineEdit *camera1VPixLE;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *camera2VPixLE;
    QLabel *label_4;
    QLineEdit *camera3VPixLE;
    QLabel *label_5;
    QLineEdit *camera4VPixLE;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *camera12HPixLE;
    QLabel *label_8;
    QLineEdit *camera23HPixLE;
    QLabel *label_9;
    QLineEdit *camera34HPixLE;
    QFrame *line;

    void setupUi(QWidget *Calibrate)
    {
        if (Calibrate->objectName().isEmpty())
            Calibrate->setObjectName(QString::fromUtf8("Calibrate"));
        Calibrate->resize(400, 300);
        label = new QLabel(Calibrate);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(17, 15, 91, 16));
        camera1VPixLE = new QLineEdit(Calibrate);
        camera1VPixLE->setObjectName(QString::fromUtf8("camera1VPixLE"));
        camera1VPixLE->setGeometry(QRect(62, 50, 90, 20));
        label_2 = new QLabel(Calibrate);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(16, 53, 54, 12));
        label_3 = new QLabel(Calibrate);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(200, 53, 54, 12));
        camera2VPixLE = new QLineEdit(Calibrate);
        camera2VPixLE->setObjectName(QString::fromUtf8("camera2VPixLE"));
        camera2VPixLE->setGeometry(QRect(247, 50, 90, 20));
        label_4 = new QLabel(Calibrate);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(16, 100, 54, 12));
        camera3VPixLE = new QLineEdit(Calibrate);
        camera3VPixLE->setObjectName(QString::fromUtf8("camera3VPixLE"));
        camera3VPixLE->setGeometry(QRect(62, 98, 90, 20));
        label_5 = new QLabel(Calibrate);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(200, 100, 54, 12));
        camera4VPixLE = new QLineEdit(Calibrate);
        camera4VPixLE->setObjectName(QString::fromUtf8("camera4VPixLE"));
        camera4VPixLE->setGeometry(QRect(247, 98, 90, 20));
        label_6 = new QLabel(Calibrate);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(17, 150, 81, 16));
        label_7 = new QLabel(Calibrate);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 190, 81, 16));
        camera12HPixLE = new QLineEdit(Calibrate);
        camera12HPixLE->setObjectName(QString::fromUtf8("camera12HPixLE"));
        camera12HPixLE->setGeometry(QRect(100, 190, 81, 20));
        label_8 = new QLabel(Calibrate);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(200, 190, 81, 16));
        camera23HPixLE = new QLineEdit(Calibrate);
        camera23HPixLE->setObjectName(QString::fromUtf8("camera23HPixLE"));
        camera23HPixLE->setGeometry(QRect(283, 188, 81, 20));
        label_9 = new QLabel(Calibrate);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(8, 240, 91, 16));
        camera34HPixLE = new QLineEdit(Calibrate);
        camera34HPixLE->setObjectName(QString::fromUtf8("camera34HPixLE"));
        camera34HPixLE->setGeometry(QRect(100, 240, 81, 20));
        line = new QFrame(Calibrate);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 140, 401, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(Calibrate);

        QMetaObject::connectSlotsByName(Calibrate);
    } // setupUi

    void retranslateUi(QWidget *Calibrate)
    {
        Calibrate->setWindowTitle(QCoreApplication::translate("Calibrate", "Form", nullptr));
        label->setText(QCoreApplication::translate("Calibrate", "\345\236\202\347\233\264\346\226\271\345\220\221\346\240\207\345\256\232", nullptr));
        label_2->setText(QCoreApplication::translate("Calibrate", "\347\233\270\346\234\2721\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Calibrate", "\347\233\270\346\234\2722\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("Calibrate", "\347\233\270\346\234\2723\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("Calibrate", "\347\233\270\346\234\2724\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("Calibrate", "\346\260\264\345\271\263\346\226\271\345\220\221\346\240\207\345\256\232", nullptr));
        label_7->setText(QCoreApplication::translate("Calibrate", "\347\233\270\346\234\27212\345\203\217\347\264\240\345\267\256\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("Calibrate", "\347\233\270\346\234\27223\345\203\217\347\264\240\345\267\256\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("Calibrate", "\347\233\270\346\234\27234\345\203\217\347\264\240\345\267\256\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Calibrate: public Ui_Calibrate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATE_H

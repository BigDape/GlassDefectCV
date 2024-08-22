/********************************************************************************
** Form generated from reading UI file 'DefectShow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEFECTSHOW_H
#define UI_DEFECTSHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DefectShow
{
public:
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *DefectShow)
    {
        if (DefectShow->objectName().isEmpty())
            DefectShow->setObjectName(QString::fromUtf8("DefectShow"));
        DefectShow->resize(267, 268);
        checkBox = new QCheckBox(DefectShow);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(50, 30, 71, 16));
        checkBox_2 = new QCheckBox(DefectShow);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(50, 90, 71, 16));
        checkBox_3 = new QCheckBox(DefectShow);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(50, 140, 71, 16));
        checkBox_4 = new QCheckBox(DefectShow);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(50, 200, 71, 16));
        label = new QLabel(DefectShow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 30, 54, 12));
        label->setStyleSheet(QString::fromUtf8("image: url(:/toolbar/icons/zhengfangxing.png);"));
        label_2 = new QLabel(DefectShow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(180, 90, 54, 12));
        label_2->setStyleSheet(QString::fromUtf8("image: url(:/toolbar/icons/lvsechahao.png);"));
        label_3 = new QLabel(DefectShow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(180, 140, 54, 12));
        label_3->setStyleSheet(QString::fromUtf8("image: url(:/toolbar/icons/langsesanjiaoxing.png);"));
        label_4 = new QLabel(DefectShow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(180, 200, 54, 12));
        label_4->setStyleSheet(QString::fromUtf8("image: url(:/toolbar/icons/langsejiahao.jpeg);"));

        retranslateUi(DefectShow);

        QMetaObject::connectSlotsByName(DefectShow);
    } // setupUi

    void retranslateUi(QWidget *DefectShow)
    {
        DefectShow->setWindowTitle(QCoreApplication::translate("DefectShow", "Form", nullptr));
        checkBox->setText(QCoreApplication::translate("DefectShow", "\346\260\224\346\263\241", nullptr));
        checkBox_2->setText(QCoreApplication::translate("DefectShow", "\345\210\222\347\227\225", nullptr));
        checkBox_3->setText(QCoreApplication::translate("DefectShow", "\345\205\266\344\273\226", nullptr));
        checkBox_4->setText(QCoreApplication::translate("DefectShow", "\350\204\217\346\261\241", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DefectShow: public Ui_DefectShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEFECTSHOW_H

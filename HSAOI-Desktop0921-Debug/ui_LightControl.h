/********************************************************************************
** Form generated from reading UI file 'LightControl.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHTCONTROL_H
#define UI_LIGHTCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LightControl
{
public:
    QPushButton *Set;
    QPushButton *Get;
    QTreeWidget *treeWidget;
    QPushButton *Save;
    QPushButton *Trigger;

    void setupUi(QWidget *LightControl)
    {
        if (LightControl->objectName().isEmpty())
            LightControl->setObjectName(QString::fromUtf8("LightControl"));
        LightControl->resize(520, 640);
        Set = new QPushButton(LightControl);
        Set->setObjectName(QString::fromUtf8("Set"));
        Set->setGeometry(QRect(420, 170, 91, 41));
        Get = new QPushButton(LightControl);
        Get->setObjectName(QString::fromUtf8("Get"));
        Get->setGeometry(QRect(420, 100, 91, 41));
        treeWidget = new QTreeWidget(LightControl);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(10, 10, 390, 620));
        treeWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        Save = new QPushButton(LightControl);
        Save->setObjectName(QString::fromUtf8("Save"));
        Save->setGeometry(QRect(420, 240, 91, 41));
        Trigger = new QPushButton(LightControl);
        Trigger->setObjectName(QString::fromUtf8("Trigger"));
        Trigger->setGeometry(QRect(420, 330, 91, 91));

        retranslateUi(LightControl);

        QMetaObject::connectSlotsByName(LightControl);
    } // setupUi

    void retranslateUi(QWidget *LightControl)
    {
        LightControl->setWindowTitle(QCoreApplication::translate("LightControl", "\350\256\276\347\275\256", nullptr));
        Set->setText(QCoreApplication::translate("LightControl", "Set", nullptr));
        Get->setText(QCoreApplication::translate("LightControl", "Get", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("LightControl", "\345\200\274", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("LightControl", "\345\220\215\347\247\260", nullptr));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("LightControl", "\347\274\226\347\240\201\345\231\250\345\217\202\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("LightControl", "\347\274\226\347\240\201\345\231\250\345\215\225\344\275\215\345\210\273\345\272\246\345\257\271\345\272\224\350\267\235\347\246\273(um)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("LightControl", "\347\274\226\347\240\201\350\204\211\345\206\262\346\273\244\346\263\242(us)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("LightControl", "\347\274\226\347\240\201\345\231\250\350\256\241\346\225\260\347\273\223\346\235\237\346\240\207\345\277\227", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(3);
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("LightControl", "\347\274\226\347\240\201\345\231\250\350\256\241\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem1->child(4);
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("LightControl", "\347\274\226\347\240\201\345\231\250\350\247\246\345\217\221\350\241\214\350\256\241\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem1->child(5);
        ___qtreewidgetitem7->setText(0, QCoreApplication::translate("LightControl", "\347\274\226\347\240\201\345\231\2504\345\200\215\351\242\221\350\256\241\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem1->child(6);
        ___qtreewidgetitem8->setText(0, QCoreApplication::translate("LightControl", "\347\274\226\347\240\201\345\231\250\345\215\225\344\275\215\346\227\266\351\227\264\350\204\211\345\206\262\350\256\241\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem1->child(7);
        ___qtreewidgetitem9->setText(0, QCoreApplication::translate("LightControl", "\347\274\226\347\240\201\345\231\250\350\256\241\346\225\260\346\227\266\351\227\264(0.5s)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem1->child(8);
        ___qtreewidgetitem10->setText(0, QCoreApplication::translate("LightControl", "\347\274\226\347\240\201\351\200\232\351\201\223", nullptr));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem1->child(9);
        ___qtreewidgetitem11->setText(0, QCoreApplication::translate("LightControl", "\347\274\226\347\240\201\345\231\250\350\275\254\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem1->child(10);
        ___qtreewidgetitem12->setText(0, QCoreApplication::translate("LightControl", "\350\276\212\351\201\223\345\221\250\351\225\277(um)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem1->child(11);
        ___qtreewidgetitem13->setText(0, QCoreApplication::translate("LightControl", "\346\234\237\346\234\233\345\215\225\344\270\252\345\203\217\347\264\240\347\262\276\345\272\246(um)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem1->child(12);
        ___qtreewidgetitem14->setText(0, QCoreApplication::translate("LightControl", "\350\276\212\351\201\223\346\234\200\345\244\247\351\200\237\345\272\246\345\257\271\345\272\224\350\241\214\351\242\221", nullptr));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem1->child(13);
        ___qtreewidgetitem15->setText(0, QCoreApplication::translate("LightControl", "\346\257\217\350\241\214\345\257\271\345\272\224\347\232\204\347\274\226\347\240\201\350\256\241\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem1->child(14);
        ___qtreewidgetitem16->setText(0, QCoreApplication::translate("LightControl", "\345\216\213\350\275\256\347\274\226\347\240\201\345\231\250A\350\256\241\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem1->child(15);
        ___qtreewidgetitem17->setText(0, QCoreApplication::translate("LightControl", "\345\216\213\350\275\256\347\274\226\347\240\201\345\231\250B\350\256\241\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem1->child(16);
        ___qtreewidgetitem18->setText(0, QCoreApplication::translate("LightControl", "\345\216\213\350\275\256\347\274\226\347\240\201\345\231\2504\345\200\215\351\242\221\350\256\241\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem1->child(17);
        ___qtreewidgetitem19->setText(0, QCoreApplication::translate("LightControl", "\345\216\213\350\275\256\347\274\226\347\240\201\345\231\250\347\263\273\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem20 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem20->setText(0, QCoreApplication::translate("LightControl", "\346\216\247\345\210\266\345\231\250\347\263\273\347\273\237\345\217\202\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem21 = ___qtreewidgetitem20->child(0);
        ___qtreewidgetitem21->setText(0, QCoreApplication::translate("LightControl", "\345\203\217\347\264\240\347\262\276\345\272\246(um)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem22 = ___qtreewidgetitem20->child(1);
        ___qtreewidgetitem22->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\347\224\265\344\277\241\345\217\267\350\204\211\345\206\262\346\273\244\346\263\242(us)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem23 = ___qtreewidgetitem20->child(2);
        ___qtreewidgetitem23->setText(0, QCoreApplication::translate("LightControl", "\347\233\270\346\234\272\350\247\246\345\217\221\350\204\211\345\206\262\346\214\201\347\273\255\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem24 = ___qtreewidgetitem20->child(3);
        ___qtreewidgetitem24->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\347\224\265\347\233\270\346\234\272\350\267\235\347\246\273(\350\241\214)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem25 = ___qtreewidgetitem20->child(4);
        ___qtreewidgetitem25->setText(0, QCoreApplication::translate("LightControl", "\347\233\270\346\234\272\345\270\247\344\277\241\345\217\267\350\247\246\345\217\221\345\273\266\346\227\266\350\241\214\346\225\260(\350\241\214)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem26 = ___qtreewidgetitem20->child(5);
        ___qtreewidgetitem26->setText(0, QCoreApplication::translate("LightControl", "\345\270\247\344\277\241\345\217\267\346\214\201\347\273\255\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem27 = ___qtreewidgetitem20->child(6);
        ___qtreewidgetitem27->setText(0, QCoreApplication::translate("LightControl", "\346\250\241\345\235\227\344\275\277\350\203\275\344\277\241\345\217\267", nullptr));
        QTreeWidgetItem *___qtreewidgetitem28 = ___qtreewidgetitem20->child(7);
        ___qtreewidgetitem28->setText(0, QCoreApplication::translate("LightControl", "\347\233\270\346\234\272\346\213\215\347\205\247\350\241\214\346\225\260(\350\241\214)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem29 = ___qtreewidgetitem20->child(8);
        ___qtreewidgetitem29->setText(0, QCoreApplication::translate("LightControl", "\345\206\205\351\203\250\350\241\214\351\242\221", nullptr));
        QTreeWidgetItem *___qtreewidgetitem30 = ___qtreewidgetitem20->child(9);
        ___qtreewidgetitem30->setText(0, QCoreApplication::translate("LightControl", "\346\213\215\347\205\247\346\250\241\345\274\217", nullptr));
        QTreeWidgetItem *___qtreewidgetitem31 = ___qtreewidgetitem20->child(10);
        ___qtreewidgetitem31->setText(0, QCoreApplication::translate("LightControl", "\346\213\215\347\205\247\347\273\223\346\235\237\345\273\266\346\227\266\350\241\214\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem32 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem32->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\346\272\220\346\216\247\345\210\266\345\231\250\345\217\202\346\225\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem33 = ___qtreewidgetitem32->child(0);
        ___qtreewidgetitem33->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2721\345\273\266\346\227\266\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem34 = ___qtreewidgetitem32->child(1);
        ___qtreewidgetitem34->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2721\345\217\221\345\205\211\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem35 = ___qtreewidgetitem32->child(2);
        ___qtreewidgetitem35->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2722\345\273\266\346\227\266\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem36 = ___qtreewidgetitem32->child(3);
        ___qtreewidgetitem36->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2722\345\217\221\345\205\211\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem37 = ___qtreewidgetitem32->child(4);
        ___qtreewidgetitem37->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2723\345\273\266\346\227\266\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem38 = ___qtreewidgetitem32->child(5);
        ___qtreewidgetitem38->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2723\345\217\221\345\205\211\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem39 = ___qtreewidgetitem32->child(6);
        ___qtreewidgetitem39->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2724\345\273\266\346\227\266\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem40 = ___qtreewidgetitem32->child(7);
        ___qtreewidgetitem40->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2724\345\217\221\345\205\211\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem41 = ___qtreewidgetitem32->child(8);
        ___qtreewidgetitem41->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2725\345\273\266\346\227\266\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem42 = ___qtreewidgetitem32->child(9);
        ___qtreewidgetitem42->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2725\345\217\221\345\205\211\346\227\266\351\227\264(10ns)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem43 = ___qtreewidgetitem32->child(10);
        ___qtreewidgetitem43->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2726\345\273\266\346\227\266\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem44 = ___qtreewidgetitem32->child(11);
        ___qtreewidgetitem44->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2726\345\217\221\345\205\211\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem45 = ___qtreewidgetitem32->child(12);
        ___qtreewidgetitem45->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2727\345\273\266\346\227\266\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem46 = ___qtreewidgetitem32->child(13);
        ___qtreewidgetitem46->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2727\345\217\221\345\205\211\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem47 = ___qtreewidgetitem32->child(14);
        ___qtreewidgetitem47->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2728\345\273\266\346\227\266\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem48 = ___qtreewidgetitem32->child(15);
        ___qtreewidgetitem48->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2728\345\217\221\345\205\211\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem49 = ___qtreewidgetitem32->child(16);
        ___qtreewidgetitem49->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2729\345\273\266\346\227\266\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem50 = ___qtreewidgetitem32->child(17);
        ___qtreewidgetitem50->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\2729\345\217\221\345\205\211\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem51 = ___qtreewidgetitem32->child(18);
        ___qtreewidgetitem51->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\27210\345\273\266\346\227\266\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem52 = ___qtreewidgetitem32->child(19);
        ___qtreewidgetitem52->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\27210\345\217\221\345\205\211\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem53 = ___qtreewidgetitem32->child(20);
        ___qtreewidgetitem53->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\27211\345\273\266\346\227\266\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem54 = ___qtreewidgetitem32->child(21);
        ___qtreewidgetitem54->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\27211\345\217\221\345\205\211\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem55 = ___qtreewidgetitem32->child(22);
        ___qtreewidgetitem55->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\27212\345\273\266\346\227\266\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem56 = ___qtreewidgetitem32->child(23);
        ___qtreewidgetitem56->setText(0, QCoreApplication::translate("LightControl", "\345\205\211\345\234\27212\345\217\221\345\205\211\346\227\266\351\227\264\357\274\21010ns\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem57 = ___qtreewidgetitem32->child(24);
        ___qtreewidgetitem57->setText(0, QCoreApplication::translate("LightControl", "\351\200\211\346\213\251\345\205\211\345\234\272\347\232\204\346\225\260\351\207\217", nullptr));
        QTreeWidgetItem *___qtreewidgetitem58 = ___qtreewidgetitem32->child(25);
        ___qtreewidgetitem58->setText(0, QCoreApplication::translate("LightControl", "\346\250\252\345\220\221\346\232\227\345\234\272\351\200\211\346\213\251\345\257\204\345\255\230\345\231\250", nullptr));
        QTreeWidgetItem *___qtreewidgetitem59 = ___qtreewidgetitem32->child(26);
        ___qtreewidgetitem59->setText(0, QCoreApplication::translate("LightControl", "\347\233\270\346\234\272\344\270\216\345\205\211\345\234\272\346\216\247\345\210\266", nullptr));
        QTreeWidgetItem *___qtreewidgetitem60 = ___qtreewidgetitem32->child(27);
        ___qtreewidgetitem60->setText(0, QCoreApplication::translate("LightControl", "\344\277\241\345\217\267\345\210\207\346\215\242", nullptr));
        QTreeWidgetItem *___qtreewidgetitem61 = ___qtreewidgetitem32->child(28);
        ___qtreewidgetitem61->setText(0, QCoreApplication::translate("LightControl", "\350\241\214\344\277\241\345\217\267\346\272\220\351\200\211\346\213\251", nullptr));
        treeWidget->setSortingEnabled(__sortingEnabled);

        Save->setText(QCoreApplication::translate("LightControl", "Save", nullptr));
        Trigger->setText(QCoreApplication::translate("LightControl", "Trigger", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LightControl: public Ui_LightControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHTCONTROL_H

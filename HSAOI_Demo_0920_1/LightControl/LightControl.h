#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#include "Global.h"
#include "LightControl/SignalControlData.h"
#include "Parameter/JsonRecipeWidget.h"
#include "RegParasComm.h"

#include <QHBoxLayout>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class LightControl;
}
QT_END_NAMESPACE

class LightControl : public QWidget {
    Q_OBJECT

public:
    explicit LightControl(RegParasComm& sig_comm, QWidget* parent = nullptr);
    ~LightControl();

private slots:
    void slot_getButton_clicked();

    void slot_setButton_clicked();

    void slot_saveButton_clicked();

    void onItemDoubleClicked(QTreeWidgetItem* item, int column);

    void slot_InitTree();

    void on_Trigger_clicked();

    void slot_updateCode();

signals:

private:
    RegParasComm& m_pSig_comm;
    JsonParse2Map* JSONRECIPE;
    QTimer* timer;
    SignalControlData* SigCtrlData;
    SignalControl* sigctrl;

    QTreeWidgetItem* specificItem0;
    QTreeWidgetItem* specificItem1;
    QTreeWidgetItem* specificItem2;
    QTreeWidgetItem* childItem0;
    QTreeWidgetItem* childItem1;
    QTreeWidgetItem* childItem2;
    QTreeWidgetItem* childItem3;
    QTreeWidgetItem* childItem4;
    QTreeWidgetItem* childItem5;
    QTreeWidgetItem* childItem6;
    QTreeWidgetItem* childItem7;
    QTreeWidgetItem* childItem8;
    QTreeWidgetItem* childItem9;
    QTreeWidgetItem* childItem10;
    QTreeWidgetItem* childItem11;
    QTreeWidgetItem* childItem12;
    QTreeWidgetItem* childItem13;
    QTreeWidgetItem* childItem14;
    QTreeWidgetItem* childItem15;
    QTreeWidgetItem* childItem16;
    QTreeWidgetItem* childItem17;
    QTreeWidgetItem* childItem18;
    QTreeWidgetItem* childItem19;
    QTreeWidgetItem* childItem20;
    QTreeWidgetItem* childItem21;
    QTreeWidgetItem* childItem22;
    QTreeWidgetItem* childItem23;
    QTreeWidgetItem* childItem24;
    QTreeWidgetItem* childItem25;
    QTreeWidgetItem* childItem26;
    QTreeWidgetItem* childItem27;
    QTreeWidgetItem* childItem28;
    QTreeWidgetItem* childItem29;
    QTreeWidgetItem* childItem30;
    QTreeWidgetItem* childItem31;
    QTreeWidgetItem* childItem32;
    QTreeWidgetItem* childItem33;
    QTreeWidgetItem* childItem34;
    QTreeWidgetItem* childItem35;
    QTreeWidgetItem* childItem36;
    QTreeWidgetItem* childItem37;


    QTreeWidgetItem* childItem43;
    QTreeWidgetItem* childItem44;
    QTreeWidgetItem* childItem45;
    QTreeWidgetItem* childItem46;
    QTreeWidgetItem* childItem47;
    QTreeWidgetItem* childItem48;
    QTreeWidgetItem* childItem49;
    QTreeWidgetItem* childItem50;
    QTreeWidgetItem* childItem51;
    QTreeWidgetItem* childItem52;
    QTreeWidgetItem* childItem53;
    QTreeWidgetItem* childItem54;
    QTreeWidgetItem* childItem55;
    QTreeWidgetItem* childItem56;
    QTreeWidgetItem* childItem_rollerACount;
    QTreeWidgetItem* childItem_rollerBCount;
    QTreeWidgetItem* childItemAB4;
    QTreeWidgetItem* chileItem_rollerCofficient;

    QTreeWidgetItem* chileItem_photoMode;
    QTreeWidgetItem* chileItem_photoEndDelayLine;
private:
    QHBoxLayout* Layout0;
    QVBoxLayout* Layout1;

    QTimer *timer1;
    QString str[47];

private:
    Ui::LightControl* ui;
};

#endif // LIGHTCONTROL_H

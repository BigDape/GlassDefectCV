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
#include "Parameter/json.h"

#define RECIPE_FULLPATH "Recipes"
#define SYSTEM_PATH "Recipes/system.ini"

#define NO_TCP_SET_BUTTON_DECLARE(param_name) void slotSetBT##param_name();
#define NO_TCP_SAVE_BUTTON_DECLARE(param_name) void slotSaveBT##param_name();

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

    // 初始化函数
    bool InitLightControl();
    // 创建新的空白工单文件
    QString createNewRecipeFile(QString recipeFileName);
    // 读取json工单到表单中
    void readRecipeToTable(std::string filePath);
    // 初始化connect函数
    void initConnect();
    // 写入当前表单数据到工单文件中
    void writeTableToRecipe(QString filename);

private slots:
    void slot_getButton_clicked();

    void slot_setButton_clicked();

    void slot_saveButton_clicked();

    void onItemDoubleClicked(QTreeWidgetItem* item, int column);

    void slot_InitTree();

    void slot_updateCode();
    //更新工单
    void slotUpdateRecipe(int index);
    //全部设置
    void slotAllSet();
    //全部保存
    void slotAllSave();
    //新建工单
    void slotCreateRecipe();
    //拷贝工单
    void slotCopyRecipe();
    //触发
    void slotTrigger();
    //设置(系统名称、相机个数、相机0名称、相机1名称、相机2名称、相机3名称、服务器IP、端口号)
    NO_TCP_SET_BUTTON_DECLARE(SystemName)
    NO_TCP_SET_BUTTON_DECLARE(CameraNum)
    NO_TCP_SET_BUTTON_DECLARE(Camera0Name)
    NO_TCP_SET_BUTTON_DECLARE(Camera1Name)
    NO_TCP_SET_BUTTON_DECLARE(Camera2Name)
    NO_TCP_SET_BUTTON_DECLARE(Camera3Name)
    NO_TCP_SET_BUTTON_DECLARE(ServerIP)
    NO_TCP_SET_BUTTON_DECLARE(Port)
    //保存(系统名称、相机个数、相机0名称、相机1名称、相机2名称、相机3名称、服务器IP、端口号)
    NO_TCP_SAVE_BUTTON_DECLARE(SystemName)
    NO_TCP_SAVE_BUTTON_DECLARE(CameraNum)
    NO_TCP_SAVE_BUTTON_DECLARE(Camera0Name)
    NO_TCP_SAVE_BUTTON_DECLARE(Camera1Name)
    NO_TCP_SAVE_BUTTON_DECLARE(Camera2Name)
    NO_TCP_SAVE_BUTTON_DECLARE(Camera3Name)
    NO_TCP_SAVE_BUTTON_DECLARE(ServerIP)
    NO_TCP_SAVE_BUTTON_DECLARE(Port)
    //设置

signals:

private:
    RegParasComm& m_pSig_comm;
    JsonParse2Map* JSONRECIPE;
    QTimer* timer;
    SignalControlData* SigCtrlData;
    SignalControl* sigctrl;

    RegParasComm sig_comm;
    Json::Value m_root; //当前内存中的json对象

//    QTreeWidgetItem* specificItem0;
//    QTreeWidgetItem* specificItem1;
//    QTreeWidgetItem* specificItem2;
//    QTreeWidgetItem* childItem0;
//    QTreeWidgetItem* childItem1;
//    QTreeWidgetItem* childItem2;
//    QTreeWidgetItem* childItem3;
//    QTreeWidgetItem* childItem4;
//    QTreeWidgetItem* childItem5;
//    QTreeWidgetItem* childItem6;
//    QTreeWidgetItem* childItem7;
//    QTreeWidgetItem* childItem8;
//    QTreeWidgetItem* childItem9;
//    QTreeWidgetItem* childItem10;
//    QTreeWidgetItem* childItem11;
//    QTreeWidgetItem* childItem12;
//    QTreeWidgetItem* childItem13;
//    QTreeWidgetItem* childItem14;
//    QTreeWidgetItem* childItem15;
//    QTreeWidgetItem* childItem16;
//    QTreeWidgetItem* childItem17;
//    QTreeWidgetItem* childItem18;
//    QTreeWidgetItem* childItem19;
//    QTreeWidgetItem* childItem20;
//    QTreeWidgetItem* childItem21;
//    QTreeWidgetItem* childItem22;
//    QTreeWidgetItem* childItem23;
//    QTreeWidgetItem* childItem24;
//    QTreeWidgetItem* childItem25;
//    QTreeWidgetItem* childItem26;
//    QTreeWidgetItem* childItem27;
//    QTreeWidgetItem* childItem28;
//    QTreeWidgetItem* childItem29;
//    QTreeWidgetItem* childItem30;
//    QTreeWidgetItem* childItem31;
//    QTreeWidgetItem* childItem32;
//    QTreeWidgetItem* childItem33;
//    QTreeWidgetItem* childItem34;
//    QTreeWidgetItem* childItem35;
//    QTreeWidgetItem* childItem36;
//    QTreeWidgetItem* childItem37;
//    QTreeWidgetItem* childItem43;
//    QTreeWidgetItem* childItem44;
//    QTreeWidgetItem* childItem45;
//    QTreeWidgetItem* childItem46;
//    QTreeWidgetItem* childItem47;
//    QTreeWidgetItem* childItem48;
//    QTreeWidgetItem* childItem49;
//    QTreeWidgetItem* childItem50;
//    QTreeWidgetItem* childItem51;
//    QTreeWidgetItem* childItem52;
//    QTreeWidgetItem* childItem53;
//    QTreeWidgetItem* childItem54;
//    QTreeWidgetItem* childItem55;
//    QTreeWidgetItem* childItem56;
//    QTreeWidgetItem* childItem_rollerACount;
//    QTreeWidgetItem* childItem_rollerBCount;
//    QTreeWidgetItem* childItemAB4;
//    QTreeWidgetItem* chileItem_rollerCofficient;

//    QTreeWidgetItem* chileItem_photoMode;
//    QTreeWidgetItem* chileItem_photoEndDelayLine;

    std::unordered_map<QTreeWidgetItem*,QString> itemMap;
private:
    QHBoxLayout* Layout0;
    QVBoxLayout* Layout1;

    QTimer *timer1;
    QString str[47];

private:
    Ui::LightControl* ui;
};

#endif // LIGHTCONTROL_H

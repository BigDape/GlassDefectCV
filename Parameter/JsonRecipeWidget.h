/*******************************************
    @ClassName   : JsonRecipeWidget
    @Description : Json工单参数管理界面类
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-25
********************************************/
#ifndef JSONRECIPEWIDGET_H
#define JSONRECIPEWIDGET_H

#include "Parameter/JsonParse2Map.h"
#include <QComboBox>
#include <QDateTime>
#include <QDialog>
#include <QDir>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QTextStream>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include <QVBoxLayout>
#include <QWidget>
#include <QInputDialog>
#include <QSettings>
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextCodec>
#include <QMessageBox>
#include "HalconCpp.h"
using namespace HalconCpp;

namespace Ui {
class JsonRecipeWidget;
}

class JsonRecipeWidget : public QWidget {
    Q_OBJECT

public:
    explicit JsonRecipeWidget(QWidget* parent = nullptr,
                              JsonParse2Map* Recipe = nullptr,
                              QString name="");
    ~JsonRecipeWidget();

    JsonParse2Map* CurrentRecipe;

private:
    Ui::JsonRecipeWidget* ui;

    void InitTreeWidget();
    void InitRecipesInFiles();
    void InitWidgetLayout();
    void InitTickData(QString name);

    //窗口控件
    QPushButton* btn_Save;               // 保存
    QPushButton* btn_Read;               // 读取
    QPushButton* btn_SelectRecipe;       // 选择
    QPushButton* btn_NewRecipe;          // 新建工单
    QPushButton* btn_DeleteRecipe;       // 删除
    QPushButton* btn_NewParam;           // 新建参数
    QPushButton* btn_DeleteSingleParam;  // 删除元素
    QPushButton* btn_CreateSon;          // 创建子项名称
    QPushButton* btn_DeleteTicket;       // 删除工单

    QComboBox* cbx_RecipeSelect;
    QLabel* lbl_OperationResult;
    QTreeWidget* TreeWidget;

    QTreeWidgetItem* rootItem4GlassMeasure;
    QTreeWidgetItem* rootItem4FlawDetect;
    QTreeWidgetItem* rootItem2Custom;

    QList<Key2Value> Params4GlassMeasure;
    QList<Key2Value> Params4FlawDetect;
    QList<Key2Value> Params2CustomDetect;

    QList<QList<Key2Value>> Params4ListAll;
    QStringList ParamsListName;
    QStringList TicketName;

    void ReadParamsFromRecipe();

    QString SelectedName;
    QString SelectedValue;
    QString SelectedParent;

    QString tickFileName;
    QString tickName;

    bool SelectedisRootItem = false;
public slots:
    void SelectRecipe();
    void CreateNewRecipe();
    void DeleteRecipe();
    void slot_RecipeChanged(JsonParse2Map* m_RecipeChanged);

    void ReadValue2Tree();
    void SaveValue2tree();
    void GetNewParam();
    void DeleteSingleParam();


    void CreateNewSon();
    void SaveTicketData() ;
    void DeleteTick();
signals:
    void sig_DeliverName(QString RecipeChanged);
    void sig_CameraParamsChangeRecipe();
    void sig_LightControlChange();
    void sig_RecipeChange();


private slots:
    void slot_ItemDoubleClicked(QTreeWidgetItem* item, int column);
    void slot_ItemSelected(QTreeWidgetItem* item, int column);


};

#endif // JSONRECIPEWIDGET_H

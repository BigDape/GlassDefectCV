#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Camera/Dushen/DushenBasicFunc.h"
#include "Form/CamerasWidget.h"
#include "Form/FlawShowWidget.h"
#include "Form/glassstatictablewidget.h"
#include "Form/singleflawshowwidget.h"
#include "Global.h"
#include "Jianbo_db.h"
#include "ImageProcess/processdetect.h"
#include "ImageProcess/processtile.h"
#include "Parameter/JsonParse2Map.h"
#include "Parameter/JsonRecipeWidget.h"
#include "SystemSettingForm.h"
#include <QDockWidget>
#include <QMainWindow>
#include <QSettings>
#include <QThread>
#include <Form/SingleSizeShowWidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    //工单
    JsonParse2Map* JsonRecipe;

    //数据库
    Jianbo_db* Database;

    //相机
    DushenBasicFunc* Camera0;
    DushenBasicFunc* Camera1;
    DushenBasicFunc* Camera2;
    DushenBasicFunc* Camera3;

    QList<DushenBasicFunc*> Cameras;

    JsonRecipeWidget* JsonRecipeView;
    SystemSettingForm* SystemSettings;

    int SystemStatus = 0; // 0停止，1采集

    RegParasComm* sig_comm;

    QString _offlineSelectedDir; //离线模式下选择的路径

private:
    Ui::MainWindow* ui;
    Process_Detect* Detectworker;
    ProcessTile* Tileworker;
    SignalControlData* SigCtrlData;

    QAction* m_pExit;
    QAction* m_pSettings;
    QAction* m_pStart;
    QAction* m_pStop;
    QAction* m_pCameraSettings;
    QAction* m_pRunningInfo;
    QAction* m_pDB;
    QAction* m_offline; //离线模式

    QLabel* label1;
    QLabel* label2;
    QLineEdit* lineEdit1;
    QLineEdit* lineEdit2;

    QWidget* GlassInfoWidget;

    QProcess* DB;

    void initMenu();
    void initLayout();
    void initSignalPlatform();
    void initThread();
    void initDatabase();

    FlawShowWidget* m_FlawShowWidget;
    GlassStatisticTableWidget* m_GlassStatisticTable;
    SingleFlawShowWidget* m_SingleFlawShow;
    SingleSizeShowWidget* m_SingleSizeShow;
    CamerasWidget* Camera_widget;

    QDockWidget* Dock_FlawShowView;
    QDockWidget* Dock_GlassStatisticsTableView;
    QDockWidget* Dock_SingleFlawShowView;
    QDockWidget* Dock_SingleSizeShowView;
    QDockWidget* Dock_CameraShow;

    void Create_FlawShowWidget();
    void Create_GlassStatisticsTable();
    void Create_SingleFlawShow();
    void Create_SingleSizeShow();
    void Create_CameraShow();

private slots:
    void slot_CloseSystem();
    void slot_ShowSystemSettingForm();
    void slot_ActionStart();
    void slot_ActionStop();
    void slot_CameraShow();
    void slot_RunningInfo();
    void stopThread();
    void slot_DB();
    void slot_Offline();

public slots:
    void slot_ChangeRecipe(QString RecipeName);
    void slot_updatePreGlassRes(bool);
    void slot_updateSortGlassRes(SummaryResult Res);
    void slot_clearPreSortGlassInfo();
    void slot_SendPoint(const FlawPoint&flawpoint);
    void slot_test();
signals:
    void sig_DeliverNewRecipe(JsonParse2Map* NewRecipe);
    void sig_FlawWidgetChange();
    void sig_DeliverFlawPoints2Widget(QList<FlawPoint>* points);
    void sig_DeliverGlasses2Widget(QList<QRectF>* Glasses);

    void sig_StartButton2CameraStart();
    void sig_StopButton2CameraStop();

private:
    QThreadPool* _pool;
};
#endif // MAINWINDOW_H

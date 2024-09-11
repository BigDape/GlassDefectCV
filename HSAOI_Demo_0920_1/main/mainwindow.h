#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QMainWindow>
#include <QSettings>
#include <QThread>
#include "Form/SingleSizeShowWidget.h"
#include "Form/FlawShowWidget.h"
#include "Form/glassstatictablewidget.h"
#include "Form/singleflawshowwidget.h"
#include "Global.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void initMenu();
    void initLayout();
    void initThread();
    void initDatabase();
    void Create_FlawShowWidget();
    void Create_GlassStatisticsTable();
    void Create_SingleFlawShow();
    void Create_SingleSizeShow();
    void Create_CameraShow();

public slots:
    void slot_CloseSystem();
    void slot_ShowSystemSettingForm();
    void slot_ActionStart();
    void slot_ActionStop();
    void slot_CameraShow();
    void slot_RunningInfo();
    void stopThread();
    void slot_DB();
    void slot_Offline();
    void slot_ChangeRecipe(QString RecipeName);
    void slot_updatePreGlassRes(bool);
    void slot_updateSortGlassRes(/*SummaryResult Res*/);
    void slot_clearPreSortGlassInfo();
    void slot_SendPoint(/*const FlawPoint&flawpoint*/);
    void slot_test();

signals:
    void sig_FlawWidgetChange();
    void sig_DeliverFlawPoints2Widget(/*QList<FlawPoint>* points*/);
    void sig_DeliverGlasses2Widget(QList<QRectF>* Glasses);
    void sig_StartButton2CameraStart();
    void sig_StopButton2CameraStop();
    void sig_tt(); //更新主界面的工单内容

private:
    Ui::MainWindow* ui;
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
    FlawShowWidget* m_FlawShowWidget;
    GlassStatisticTableWidget* m_GlassStatisticTable;
    SingleFlawShowWidget* m_SingleFlawShow;
    SingleSizeShowWidget* m_SingleSizeShow;
    QDockWidget* Dock_FlawShowView;
    QDockWidget* Dock_GlassStatisticsTableView;
    QDockWidget* Dock_SingleFlawShowView;
    QDockWidget* Dock_SingleSizeShowView;
    QDockWidget* Dock_CameraShow;
    int SystemStatus = 0; // 0停止，1采集
    QString _offlineSelectedDir; //离线模式下选择的路径
    QTimer* _timer;
};
#endif // MAINWINDOW_H

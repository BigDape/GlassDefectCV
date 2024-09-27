#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QMainWindow>
#include <QSettings>
#include <QThread>
#include <QTableWidgetItem>
#include <Qwt/qwt_plot_picker.h>
#include "Global.h"
#include "Form/cameraslayout.h"
#include "Form/LightControl.h"
#include "Form/MyGraphicsitem.h"
#include "Form/Calibrate.h"

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
    /**
     * @brief InitRegisterMetaType 注册信号与槽函数使用到的自定义结构体
     */
    void InitRegisterMetaType();
    /**
     * @brief InitToolBar 初始化工具栏
     */
    void InitToolBar();
    /**
     * @brief InitGlassStaticTableWidget 初始化数据统计界面
     */
    void InitGlassStaticTableWidget();
    /**
     * @brief InitSingleFlawTableWidget 初始化缺陷界面
     */
    void InitSingleFlawTableWidget();
    /**
     * @brief InitSingleSizeTableWidget 初始化尺寸界面
     */
    void InitSingleSizeTableWidget();
    /**
     * @brief InitCameraSettingTableWidget 初始化相机设置界面
     */
    void InitCameraSettingTableWidget();
    /**
     * @brief InitRealTimeFlawTableWidget 初始化相机实时缺陷界面
     */
    void InitRealTimeFlawTableWidget();
    /**
     * @brief InitFlawShowWidget 初始化缺陷显示界面
     */
    void InitFlawShowWidget();
    /**
     * @brief InitSummaryTableWidget 初始化总结界面
     */
    void InitSummaryTableWidget();
    /**
     * @brief InitLogInformation 初始化日志界面
     */
    void InitLogInformation();

private:
    /**
     * @brief drawGlass 绘制玻璃轮廓
     * @param x_length 宽
     * @param y_length 长
     */
    void drawGlass(double x_length, double y_length);
    /**
     * @brief drawFlaw 绘制缺陷
     * @param m_FlawPointList 缺陷点集合
     */
    void drawFlaw(QList<FlawPoint>* m_FlawPointList);
    /**
     * @brief reDrawFlaw 重新绘制缺陷点
     * @param m_FlawPointList
     */
    void reDrawFlaw(QList<FlawPoint>* m_FlawPointList);
    /**
     * @brief drawLegend 绘制图例
     */
    void drawLegend();

public slots:
    void slot_CloseSystem();
    void slot_ShowSystemSettingForm();
    void slot_ActionStart();
    void slot_ActionStop();
    void stopThread();
    void slot_DataSearch();
    void slot_Offline();
    void slot_Calibrate();
    /**
     * @brief slot_GlassStaticTableInsertRowData 在玻璃统计表中插入一行数据
     * @param info 要插入的数据
     */
    void slot_GlassStaticTableInsertRowData(GlassDataBaseInfo info);
    /**
     * @brief slot_SingleFlawUpdateTableData 在缺陷界面中更新表格和图片
     * @param info
     */
    void slot_SingleFlawUpdateTableData(GlassDefectInfo info);
    void slot_SingleFlawTrack(QTableWidgetItem* item);
    void slot_SingleSizeUpdataTableData(GlassSizeInfo info);
    /**
     * @brief slot_RealTimeFlawUpdateTableData 在实时缺陷界面上更新数据
     * @param info
     */
    void slot_RealTimeFlawUpdateTableData(GlassDefect info);
    /**
     * @brief slot_DrawGlassAndFlaw 绘画玻璃轮廓和缺陷点
     */
    void slot_DrawGlassAndFlaw();
    void slot_LegendChecked(const QVariant &itemInfo, bool on, int index);
    void slot_RefreshSystemTime();
signals:
    /**
     * @brief sign_GlassStaticTableInsertRowData 在玻璃统计表中插入一行数据
     * @param info
     */
    void sign_GlassStaticTableInsertRowData(GlassDataBaseInfo info);
private:
    Ui::MainWindow* ui;
    QAction* m_pExit;               // 退出
    QAction* m_pSettings;           // 设置
    QAction* m_pStart;              // 开始
    QAction* m_pStop;               // 停止
    QAction* m_pDB;                 // 数据查询
    QAction* m_offline;             // 离线模式
    QAction* m_calibrate;           // 标定

    MyGraphicsItem* loadedPixmapItem; // 缺陷小图光场1
    MyGraphicsItem* loadedPixmapItem2;// 缺陷小图光场2
    MyGraphicsItem* loadedPixmapItem3;// 缺陷小图光场3

    MyGraphicsItem* loadedPixmapItem4; //尺寸轮廓图展示
    MyGraphicsItem* loadedPixmapItem5; //尺寸小图

    MyGraphicsItem* loadedPixmapItem6; //实时缺陷光场1
    MyGraphicsItem* loadedPixmapItem7; //实时缺陷光场2
    MyGraphicsItem* loadedPixmapItem8; //实时缺陷光场3

    QwtPlotPicker* plotpicker;                      // 鼠标点击缺陷图对象
    std::vector<QwtPlotItem*> legendVec;            // 图例对应缺陷对象
    std::unordered_map<int,bool> replotMap;         // 标记图例有哪些被点击
    CamerasLayout* m_cameraslayout;                 // 相机布局界面
    std::shared_ptr<LightControl> m_lightControl;   // 设置界面
    QString _offlineSelectedDir;                    // 离线模式下选择的路径
    QTimer* _timer;                                 // 时钟用于更新系统时间
    std::shared_ptr<Calibrate> calibratePtr;        // 标定界面
};
#endif // MAINWINDOW_H

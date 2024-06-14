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
#define TCP_SET_BUTTON_DECLARE(param_name) void slotSetBT##param_name();

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
    // 创建新的空白工单文件
    QString createNewRecipeFile(QString recipeFileName);
    // 读取json工单到表单中
    void readRecipeToTable(std::string filePath);

    // 写入当前表单数据到工单文件中
    void writeTableToRecipe(QString filename);

private:
    // 初始化connect函数
    void initConnect();
    // 初始化函数
    bool InitLightControl();
    // 将当前的m_root写入到json文件中
    void writeCurrentRooterToJson();
    // 初始化输入框输入类型
    void initLineEditInputType();

private slots:
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
    //自定义参数设置
    NO_TCP_SET_BUTTON_DECLARE(SaveOriginImage)
    NO_TCP_SET_BUTTON_DECLARE(SaveEntireImage)
    NO_TCP_SET_BUTTON_DECLARE(SaveFlawImage)
    NO_TCP_SET_BUTTON_DECLARE(SaveCropImage)
    NO_TCP_SET_BUTTON_DECLARE(XYLengthEnable)
    NO_TCP_SET_BUTTON_DECLARE(FlawDefectEnable)
    //缺陷参数设置
    NO_TCP_SET_BUTTON_DECLARE(Camera12PixelDeviation)
    NO_TCP_SET_BUTTON_DECLARE(Camera23PixelDeviation)
    NO_TCP_SET_BUTTON_DECLARE(Camera24PixelDeviation)
    NO_TCP_SET_BUTTON_DECLARE(SilkToRollerDist)
    NO_TCP_SET_BUTTON_DECLARE(ScratchAreaThreshold)
    NO_TCP_SET_BUTTON_DECLARE(BubbleStoneAreaThreshold)
    NO_TCP_SET_BUTTON_DECLARE(DirtyAreaThreshold)
    //尺寸测量设置
    NO_TCP_SET_BUTTON_DECLARE(YAccuracyB)
    NO_TCP_SET_BUTTON_DECLARE(YAccuracyK)
    NO_TCP_SET_BUTTON_DECLARE(Width)
    NO_TCP_SET_BUTTON_DECLARE(WidthDeviation)
    NO_TCP_SET_BUTTON_DECLARE(Digonal)
    NO_TCP_SET_BUTTON_DECLARE(Digonal1Deviation)
    NO_TCP_SET_BUTTON_DECLARE(Digonal2)
    NO_TCP_SET_BUTTON_DECLARE(Digonal2Deviation)
    NO_TCP_SET_BUTTON_DECLARE(Camera1Pixel0Accuracy)
    NO_TCP_SET_BUTTON_DECLARE(Camera1PixelKValue)
    NO_TCP_SET_BUTTON_DECLARE(Camera21AccuracyRatio)
    NO_TCP_SET_BUTTON_DECLARE(Camera2PixelKValue)
    NO_TCP_SET_BUTTON_DECLARE(Length)
    NO_TCP_SET_BUTTON_DECLARE(LengthDeviation)
    //相机参数设置
    NO_TCP_SET_BUTTON_DECLARE(Camera0Frame)
    NO_TCP_SET_BUTTON_DECLARE(Camera0PhotoRow)
    NO_TCP_SET_BUTTON_DECLARE(Camera0ExposureTime)
    NO_TCP_SET_BUTTON_DECLARE(Camera0Gain)
    NO_TCP_SET_BUTTON_DECLARE(Camera1Frame)
    NO_TCP_SET_BUTTON_DECLARE(Camera1PhotoRow)
    NO_TCP_SET_BUTTON_DECLARE(Camera1ExposureTime)
    NO_TCP_SET_BUTTON_DECLARE(Camera1Gain)
    NO_TCP_SET_BUTTON_DECLARE(Camera2Frame)
    NO_TCP_SET_BUTTON_DECLARE(Camera2PhotoRow)
    NO_TCP_SET_BUTTON_DECLARE(Camera2ExposureTime)
    NO_TCP_SET_BUTTON_DECLARE(Camera2Gain)
    NO_TCP_SET_BUTTON_DECLARE(Camera3Frame)
    NO_TCP_SET_BUTTON_DECLARE(Camera3PhotoRow)
    NO_TCP_SET_BUTTON_DECLARE(Camera3ExposureTime)
    NO_TCP_SET_BUTTON_DECLARE(Camera3Gain)
    //编码器参数设置
    NO_TCP_SET_BUTTON_DECLARE(EncodeUnitToDist)
    NO_TCP_SET_BUTTON_DECLARE(EncodePulseFilterUs)
    NO_TCP_SET_BUTTON_DECLARE(EncodeCountEndFlag)
    NO_TCP_SET_BUTTON_DECLARE(EncodeCount)
    NO_TCP_SET_BUTTON_DECLARE(EncodeTriggerRowCount)
    NO_TCP_SET_BUTTON_DECLARE(Encode4FrequencyMultiplierCount)
    NO_TCP_SET_BUTTON_DECLARE(EncodeUnitTimePulseCount)
    NO_TCP_SET_BUTTON_DECLARE(EncodeCountTimeHalfSecond)
    NO_TCP_SET_BUTTON_DECLARE(EncodeChannel)
    NO_TCP_SET_BUTTON_DECLARE(EncodeRevolution)
    NO_TCP_SET_BUTTON_DECLARE(RollerPerimeterUm)
    NO_TCP_SET_BUTTON_DECLARE(ExpectSinglePixelAccuracy)
    NO_TCP_SET_BUTTON_DECLARE(RollerMaxSpeedToRowCount)
    NO_TCP_SET_BUTTON_DECLARE(EveryRowToEncodeCount)
    NO_TCP_SET_BUTTON_DECLARE(EncodePressureWheelCountA)
    NO_TCP_SET_BUTTON_DECLARE(EncodePressureWheelCountB)
    NO_TCP_SET_BUTTON_DECLARE(PressureWheel4FrequencyMutliper)
    NO_TCP_SET_BUTTON_DECLARE(PressureEncodecoefficient)
    //控制器参数设置
    NO_TCP_SET_BUTTON_DECLARE(PixelAccuracyUm)
    NO_TCP_SET_BUTTON_DECLARE(PhotoelectricSignalPulseFilter)
    NO_TCP_SET_BUTTON_DECLARE(CamareTrigerPulseContinueTime10ns)
    NO_TCP_SET_BUTTON_DECLARE(PhotoelectricToCamareDist)
    NO_TCP_SET_BUTTON_DECLARE(CamareFrameTrigerDelayRowCount)
    NO_TCP_SET_BUTTON_DECLARE(FrameSignalContinueTime)
    NO_TCP_SET_BUTTON_DECLARE(ModuleEnableSignal)
    NO_TCP_SET_BUTTON_DECLARE(CamarePhotoRowCount)
    NO_TCP_SET_BUTTON_DECLARE(InnerRowFrequency)
    NO_TCP_SET_BUTTON_DECLARE(PhotoMode)
    NO_TCP_SET_BUTTON_DECLARE(PhotoEndDelayRowCount)
    //光源控制器参数设置
    NO_TCP_SET_BUTTON_DECLARE(LightField1DelayTime)
    NO_TCP_SET_BUTTON_DECLARE(LightField1GlowTime)
    NO_TCP_SET_BUTTON_DECLARE(LightField2DelayTime)
    NO_TCP_SET_BUTTON_DECLARE(LightField2GlowTime)
    NO_TCP_SET_BUTTON_DECLARE(LightField3DelayTime)
    NO_TCP_SET_BUTTON_DECLARE(LightField3GlowTime)
    NO_TCP_SET_BUTTON_DECLARE(LightField4DelayTime)
    NO_TCP_SET_BUTTON_DECLARE(LightField4GlowTime)
    NO_TCP_SET_BUTTON_DECLARE(SelectedLightFieldNumber)
    NO_TCP_SET_BUTTON_DECLARE(HorizontalDarkfieldSelectRegister)
    NO_TCP_SET_BUTTON_DECLARE(CamareAndLightFieldControl)
    NO_TCP_SET_BUTTON_DECLARE(SignalSwitch)
    NO_TCP_SET_BUTTON_DECLARE(RowSignalSelected)
private:
    RegParasComm& m_pSig_comm;
    JsonParse2Map* JSONRECIPE;
    QTimer* timer;
    SignalControlData* SigCtrlData;
    SignalControl* sigctrl;

    Json::Value m_root; //当前内存中的json对象
    std::shared_ptr<QTimer> timer1;
private:
    Ui::LightControl* ui;
};

#endif // LIGHTCONTROL_H

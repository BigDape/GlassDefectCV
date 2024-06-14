/*******************************************
    @ClassName   : Global
    @Description : 全局变量,静态变量
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-03
********************************************/
#ifndef GLOBAL_H
#define GLOBAL_H

#include "Camera/DushenSample/DVPCamera.h"
#include "Parameter/XmlParse.h"
#include "log_singleton.h"
#include "Parameter/JsonParse2Map.h"
#include "HalconCpp.h"
#include <unordered_map>
#include <utility>
#include <vector>
#include <Qwt/qwt_plot.h>

#define PARAM GlobalParamter::getInstance()

using namespace HalconCpp;

typedef struct GLASSINFO {
    QString GlassID;
    bool isOK;
    bool isSizeOK;
    double GlassLength;
    double GlassWidth;
    double Diagonal1;
    double Diagonal2;
    int FlawCount;
    bool isFlawOK;
    int Flaw1;
    int Flaw2;
    int Flaw3;
    int Flaw4;
    int Flaw5;
    int Flaw6;
    int Flaw7;
} GLASSINFO;

typedef struct FlawPoint {
    double x;
    double y;
    int FlawType;
} FlawPoint;

struct CourTour {
    int index;
    QString x;
    QString y;
};

//
// 线程安全的懒汉单例模式--局部静态变量
//
class GlobalParamter
{
private: //构造和析构函数私有，防止外部声明
    explicit GlobalParamter();
    virtual ~GlobalParamter();
public:
    static GlobalParamter& getInstance();
    bool SaveXml();
    //
    // get参数与set参数
    //
    dvpCameraInfo getInfo(int index);
    bool setInfo(int index, dvpCameraInfo info);
    std::vector<dvpCameraInfo> getInfoVec();
    bool setInfo(std::vector<dvpCameraInfo> infoVec);

    dvpUint32 getCameraCounts();
    bool setCameraCounts(dvpUint32 counts);

    bool getIsScanned();
    bool setIsScanned(bool isscanned);

    XmlParse& getXmlParam();
    bool setXmlParam(XmlParse& xmlparam);

    double getFramesPerTri();
    bool setFramesPerTri(double framesPerTri);

    double getImageHeight();
    bool setImageHeight(double imageHeight);

    double getImageWidth();
    bool setImageWidth(double imageWidth);

    QString getCurrentRecipe();
    bool setCurrentRecipe(QString currentRecipe);

    QString getSystemName();
    bool setSystemName(QString systemName);

    QString getCamera0Name();
    bool setCamera0Name(QString camera0Name);

    QString getCamera1Name();
    bool setCamera1Name(QString camera1Name);

    QString getCamera2Name();
    bool setCamera2Name(QString camera2Name);

    QString getCamera3Name();
    bool setCamera3Name(QString camer3Name);

    QString getServerIP();
    bool setServerIP(QString ip);

    int getPort();
    bool setPort(int port);

    int getFrameSignal();
    bool setFrameSignal(int signal);

    long getCodeCount();
    bool setCodeCount(long count);

    long getCodeLineCount();
    bool setCodeLineCount(long count);

    long getCode4Count();
    bool setCode4Count(long count);

    long getCodePerCount();
    bool setCodePerCount(long count);

    int getCamRows();
    bool setCamRows(int camRows);

    int getCamRowsPerField();
    bool setCamRowsPerField(int camRowsPerField);

    bool getRecChangeSignal();
    bool setRecChangeSignal(bool signal);

    bool getAlmLightSignal();
    bool setAlmLightSignal(bool signal);

    int getAlmLightVal();
    bool setAlmLightVal(int val);

    int getFieldNumberSet();//场数
    bool setFieldNumberSet(int fieldNumberSet);//场数

    HTuple getRecipeDict();
    bool setRecipeDict(HTuple recipeDict);

    QStringList getCamName();
    bool setCamName(QStringList list);

    int getCamDefineNum();
    bool setCamDefineNum(int num);

    QList<QString> getCamListName();
    bool setCamListName(QList<QString> strs);

    QList<int> getFieldSelectedView();
    bool setFieldSelectedView(QList<int> views);

    quint64 getGlassID_INT();
    bool setGlassID_INT(quint64 id);

    long getEncodeRollerCount(); //编码器压轮计数
    bool setEncodeRollerCount(long count);

    long getEncodeARollerCount(); //编码器压轮计数
    bool setEncodeARollerCount(long count);

    long getEncodeBRollerCount(); //编码器压轮计数
    bool setEncodeBRollerCount(long count);

    double getEncodeRollerCofficient();//编码器压轮系数
    bool setEncodeRollerCofficient(double cofficient);

    double getRollerAngle(); //玻璃偏移的角度
    bool setRollerAngle(double angle);

    double getEncodeRollerYLength();//差分计算出来的长度
    bool setEncodeRollerYLength(double length);

    std::vector<CourTour>& getCourtourMapXY();//轮廓点
    bool setCourtourMapXY(std::vector<CourTour>& tours);
    bool setCourtourMapXY(CourTour tours);

    std::shared_ptr<QwtPlot> getPlot();
    bool setPlot(std::shared_ptr<QwtPlot> ptr);

    bool getIsOffline(); //是否触发了离线模式
    bool setIsOffline(bool flag);

    QString getOfflineFullPath();
    bool setOfflineFullPath(QString path);

    bool getIsJpg();
    bool setIsJpg(bool isjpg);

    long getEncodeAB4();
    bool setEncodeAB4(long code4);

    int getSaveOriginImage();
    bool setSaveOriginImage(int index);

    int getSaveEntireImage();
    bool setSaveEntireImage(int index);

    int getSaveFlawImage();
    bool setSaveFlawImage(int index);

    int getSaveCropImage();
    bool setSaveCropImage(int index);

    int getXYLengthEnable();
    bool setXYLengthEnable(int index);

    int getFlawDefectEnable();
    bool setFlawDefectEnable(int index);

    int getCamera12PixelDeviation();
    bool setCamera12PixelDeviation(int number);

    int getCamera23PixelDeviation();
    bool setCamera23PixelDeviation(int number);

    int getCamera24PixelDeviation();
    bool setCamera24PixelDeviation(int number);

    int getSilkToRollerDist();
    bool setSilkToRollerDist(int number);

    int getScratchAreaThreshold();
    bool setScratchAreaThreshold(int number);

    int getBubbleStoneAreaThreshold();
    bool setBubbleStoneAreaThreshold(int number);

    int getDirtyAreaThreshold();
    bool setDirtyAreaThreshold(int number);

    double getYAccuracyB();
    bool setYAccuracyB(double num);

    double getYAccuracyK();
    bool setYAccuracyK(double num);

    double getWidth();
    bool setWidth(double num);

    double getWidthDeviation();
    bool setWidthDeviation(double num);

    double getDigonal();
    bool setDigonal(double num);

    double getDigonal1Deviation();
    bool setDigonal1Deviation(double num);

    double getDigonal2();
    bool setDigonal2(double num);

    double getDigonal2Deviation();
    bool setDigonal2Deviation(double num);

    double getCamera1Pixel0Accuracy();
    bool setCamera1Pixel0Accuracy(double num);

    double getCamera1PixelKValue();
    bool setCamera1PixelKValue(double num);

    double getCamera21AccuracyRatio();
    bool setCamera21AccuracyRatio(double num);

    double getCamera2PixelKValue();
    bool setCamera2PixelKValue(double num);

    double getLength();
    bool setLength(double num);

    double getLengthDeviation();
    bool setLengthDeviation(double num);

    int getCamera0Frame();
    bool setCamera0Frame(int num);

    int getCamera0PhotoRow();           // 相机0拍照行数
    bool setCamera0PhotoRow(int num);

    int getCamera0ExposureTime();            // 相机0曝光时间
    bool setCamera0ExposureTime(int num);

    int getCamera0Gain();                    // 相机0增益
    bool setCamera0Gain(int num);

    int getCamera1Frame();                   // 相机1帧次
    bool setCamera1Frame(int num);

    int getCamera1PhotoRow();                // 相机1拍照行数
    bool setCamera1PhotoRow(int num);

    int getCamera1ExposureTime();            // 相机1曝光时间
    bool setCamera1ExposureTime(int num);

    int getCamera1Gain();                    // 相机1增益
    bool setCamera1Gain(int num);

    int getCamera2Frame();                   // 相机2帧次
    bool setCamera2Frame(int num);

    int getCamera2PhotoRow();                // 相机2拍照行数
    bool setCamera2PhotoRow(int num);

    int getCamera2ExposureTime();            // 相机2曝光时间
    bool setCamera2ExposureTime(int num);

    int getCamera2Gain();                    // 相机2增益
    bool setCamera2Gain(int num);

    int getCamera3Frame();                   // 相机3帧次
    bool setCamera3Frame(int num);

    int getCamera3PhotoRow();                // 相机3拍照行数
    bool setCamera3PhotoRow(int num);

    int getCamera3ExposureTime();            // 相机3曝光时间
    bool setCamera3ExposureTime(int num);

    int getCamera3Gain();                    // 相机3增益
    bool setCamera3Gain(int num);

    int getEncodeUnitToDist();               // 编码器单位刻度对应距离
    int getEncodePulseFilterUs();            // 编码脉冲滤波
    int getEncodeCountEndFlag();             // 编码器计数结束标志
    int getEncodeCount();                    // 编码器计数
    int getEncodeTriggerRowCount();          // 编码器触发行计数
    int getEncode4FrequencyMultiplierCount(); //编码器4倍频计数
    int getEncodeUnitTimePulseCount();        //编码器单位时间脉冲计数
    int getEncodeCountTimeHalfSecond();       //编码器计数时间0.5s
    int getEncodeChannel();                   //编码通道
    int getEncodeRevolution();                //编码器转数
    int getRollerPerimeterUm();               //辊道周长
    int getExpectSinglePixelAccuracy();       //期望单个像素精度
    int getRollerMaxSpeedToRowCount();        //辊道最大速度对应行频
    int getEveryRowToEncodeCount();           //每行对应的编码计数
    int getEncodePressureWheelCountA();       //压轮编码器计数A
    int getEncodePressureWheelCountB();       //压轮编码器计数B
    int getPressureWheel4FrequencyMutliper(); //压轮编码器四倍计数
    int getPressureEncodecoefficient();       //压轮编码器系数

    bool setEncodeUnitToDist(int num);               // 编码器单位刻度对应距离
    bool setEncodePulseFilterUs(int num);            // 编码脉冲滤波
    bool setEncodeCountEndFlag(int num);             // 编码器计数结束标志
    bool setEncodeCount(int num);                    // 编码器计数
    bool setEncodeTriggerRowCount(int num);          // 编码器触发行计数
    bool setEncode4FrequencyMultiplierCount(int num); //编码器4倍频计数
    bool setEncodeUnitTimePulseCount(int num);        //编码器单位时间脉冲计数
    bool setEncodeCountTimeHalfSecond(int num);       //编码器计数时间0.5s
    bool setEncodeChannel(int num);                   //编码通道
    bool setEncodeRevolution(int num);                //编码器转数
    bool setRollerPerimeterUm(int num);               //辊道周长
    bool setExpectSinglePixelAccuracy(int num);       //期望单个像素精度
    bool setRollerMaxSpeedToRowCount(int num);        //辊道最大速度对应行频
    bool setEveryRowToEncodeCount(int num);           //每行对应的编码计数
    bool setEncodePressureWheelCountA(int num);       //压轮编码器计数A
    bool setEncodePressureWheelCountB(int num);       //压轮编码器计数B
    bool setPressureWheel4FrequencyMutliper(int num); //压轮编码器四倍计数
    bool setPressureEncodecoefficient(int num);       //压轮编码器系数

    int getPixelAccuracyUm();                    //像素精度um
    int getPhotoelectricSignalPulseFilter();     //光电信号脉冲滤波
    int getCamareTrigerPulseContinueTime10ns();  //相机触发脉冲持续时间10ns
    int getPhotoelectricToCamareDist();          //光电与相机距离行
    int getCamareFrameTrigerDelayRowCount();     // 相机帧触发延时行数
    int getFrameSignalContinueTime();            //帧信号持续时间
    int getModuleEnableSignal();                 //模块使能信号
    int getCamarePhotoRowCount();                //相机拍照行数
    int getInnerRowFrequency();                  //内部行频
    int getPhotoMode();                          //拍照模式
    int getPhotoEndDelayRowCount();              //拍照延时行数

    bool setPixelAccuracyUm(int num);                    //像素精度um
    bool setPhotoelectricSignalPulseFilter(int num);     //光电信号脉冲滤波
    bool setCamareTrigerPulseContinueTime10ns(int num);  //相机触发脉冲持续时间10ns
    bool setPhotoelectricToCamareDist(int num);          //光电与相机距离行
    bool setCamareFrameTrigerDelayRowCount(int num);     // 相机帧触发延时行数
    bool setFrameSignalContinueTime(int num);            //帧信号持续时间
    bool setModuleEnableSignal(int num);                 //模块使能信号
    bool setCamarePhotoRowCount(int num);                //相机拍照行数
    bool setInnerRowFrequency(int num);                  //内部行频
    bool setPhotoMode(int num);                          //拍照模式
    bool setPhotoEndDelayRowCount(int num);              //拍照延时行数

    int getLightField1DelayTime();            //光场1延时时间10ns
    int getLightField1GlowTime();             //光场1发光时间10ns
    int getLightField2DelayTime();            //光场2延时时间10ns
    int getLightField2GlowTime();             //光场2发光时间10ns
    int getLightField3DelayTime();            //光场3延时时间10ns
    int getLightField3GlowTime();             //光场3发光时间10ns
    int getLightField4DelayTime();            //光场4延时时间10ns
    int getLightField4GlowTime();             //光场4发光时间10ns
    int getSelectedLightFieldNumber();        //选择光场数量
    int getHorizontalDarkfieldSelectRegister();  //横向暗场选择寄存器
    int getCamareAndLightFieldControl();         //相机与光场控制
    int getSignalSwitch();                       //信号切换
    int getRowSignalSelected();                  //行信号源选择

    bool setLightField1DelayTime(int num);            //光场1延时时间10ns
    bool setLightField1GlowTime(int num);             //光场1发光时间10ns
    bool setLightField2DelayTime(int num);            //光场2延时时间10ns
    bool setLightField2GlowTime(int num);             //光场2发光时间10ns
    bool setLightField3DelayTime(int num);            //光场3延时时间10ns
    bool setLightField3GlowTime(int num);             //光场3发光时间10ns
    bool setLightField4DelayTime(int num);            //光场4延时时间10ns
    bool setLightField4GlowTime(int num);             //光场4发光时间10ns
    bool setSelectedLightFieldNumber(int num);        //选择光场数量
    bool setHorizontalDarkfieldSelectRegister(int num);  //横向暗场选择寄存器
    bool setCamareAndLightFieldControl(int num);         //相机与光场控制
    bool setSignalSwitch(int num);                       //信号切换
    bool setRowSignalSelected(int num);                  //行信号源选择

    QString GetParamterFromIniFile(QString fullpath, QString key);
private:
    std::vector<dvpCameraInfo> info;  //info[16]
    dvpUint32 CameraCounts;           //相机数量
    bool IsScanned;
    XmlParse xmlParam;
    double FramesPerTri;
    double ImageHeight;
    double ImageWidth;

    QString CurrentRecipe;            // 当前工单名称：8nm
    QString SystemName;               // 当前系统名称：大拓智能视觉检测
    QString Camera0Name;              // 当前照相机0名称：DSXL810003076
    QString Camera1Name;              // 当前照相机1名称：DSXL810002378
    QString Camera2Name;              // 当前照相机2名称：DSXL810002135
    QString Camera3Name;              // 当前照相机3名称：DSXL810002382
    QString serverIp;                 // 控制器IP地址：192.168.1.200
    int RegParaPort;                  // 控制器Port：7002
    int FrameSignal;
    long CodeCount;
    long CodeLineCount;
    long Code4Count;
    long CodePerCount;
    int CamRows;
    int CamRowsPerField;
    bool RecChangeSignal;
    bool AlmLightSignal;            // 报警信号灯
    int AlmLightVal;                // 报警值
    int FieldNumberSet;             //场数
    HTuple RecipeDict;
    QStringList camName;
    int camDefineNum;                   // 照相机个数
    QList<QString> camListName;         // 照相机名称list
    QList<int> FieldSelectedView;       // 光场选择的视角：1表示选中，0表示未选中
    quint64 GlassID_INT;
    long encodeRollerCount;             //编码器压轮计数
    long encodeARollerCount;            //编码器压轮A计数
    long encodeBRollerCount;            //编码器压轮B计数
    double encodeRollerCofficient;      //编码器压轮系数
    double RollerAngle;                 //玻璃偏移的角度
    double encodeRollerYLength;         //差分计算出来的长度
    std::vector<CourTour> courtourMapXY;//轮廓点
    std::shared_ptr<QwtPlot> m_plot;
    bool isOffline;                     //是否触发了离线模式
    QString offlineFullPath;
    bool isJpg;
    long encodeAB4;                     // 压轮编码器四倍频
    int isSaveOriginImage;              // 保存原图
    int isSaveEntireImage;              // 保存整图
    int isSaveFlawImage;                // 保存缺捡图
    int isSaveCropImage;                //  保存裁剪图像
    int XYLengthEnable;                 // 尺寸测量启用
    int FlawDefectEnable;               // 缺陷检测启用
    int Camera12PixelDeviation;         // 12相机像素偏差
    int Camera23PixelDeviation;         // 23相机像素偏差
    int Camera24PixelDeviation;         // 24相机像素偏差
    int SilkToRollerDist;               // 丝印到辊道距离
    int ScratchAreaThreshold;           // 划痕面积阈值
    int BubbleStoneAreaThreshold;       // 气节面积阈值
    int DirtyAreaThreshold;             // 脏污面积阈值
    double YAccuracyB;                  // Y方向上精度B
    double YAccuracyK;                  // Y方向上精度K
    double Width;                       // 宽度
    double WidthDeviation;              // 宽度误差
    double Digonal;                     // 对角线1
    double Digonal1Deviation;           // 对角线1误差
    double Digonal2;                     // 对角线2
    double Digonal2Deviation;           // 对角线2误差
    int Camera1Pixel0Accuracy;          // 相机1像素0精度
    double Camera1PixelKValue;             // 相机1像素k值
    double Camera21AccuracyRatio;           //相机21精度比值
    double Camera2PixelKValue;          //相机2像素k值
    double Length;                      // 长度
    double LengthDeviation;             // 长度误差
    int Camera0Frame;                   // 相机0帧次
    int Camera0PhotoRow;                // 相机0拍照行数
    int Camera0ExposureTime;            // 相机0曝光时间
    int Camera0Gain;                    // 相机0增益
    int Camera1Frame;                   // 相机1帧次
    int Camera1PhotoRow;                // 相机1拍照行数
    int Camera1ExposureTime;            // 相机1曝光时间
    int Camera1Gain;                    // 相机1增益
    int Camera2Frame;                   // 相机2帧次
    int Camera2PhotoRow;                // 相机2拍照行数
    int Camera2ExposureTime;            // 相机2曝光时间
    int Camera2Gain;                    // 相机2增益
    int Camera3Frame;                   // 相机3帧次
    int Camera3PhotoRow;                // 相机3拍照行数
    int Camera3ExposureTime;            // 相机3曝光时间
    int Camera3Gain;                    // 相机3增益
    ////////
    int EncodeUnitToDist;               // 编码器单位刻度对应距离
    int EncodePulseFilterUs;            // 编码脉冲滤波
    int EncodeCountEndFlag;             // 编码器计数结束标志
    int EncodeCount;                    // 编码器计数
    int EncodeTriggerRowCount;          // 编码器触发行计数
    int Encode4FrequencyMultiplierCount; //编码器4倍频计数
    int EncodeUnitTimePulseCount;        //编码器单位时间脉冲计数
    int EncodeCountTimeHalfSecond;       //编码器计数时间0.5s
    int EncodeChannel;                   //编码通道
    int EncodeRevolution;                //编码器转数
    int RollerPerimeterUm;               //辊道周长
    int ExpectSinglePixelAccuracy;       //期望单个像素精度
    int RollerMaxSpeedToRowCount;        //辊道最大速度对应行频
    int EveryRowToEncodeCount;           //每行对应的编码计数
    int EncodePressureWheelCountA;       //压轮编码器计数A
    int EncodePressureWheelCountB;       //压轮编码器计数B
    int PressureWheel4FrequencyMutliper; //压轮编码器四倍计数
    int PressureEncodecoefficient;       //压轮编码器系数
    //////////
    int PixelAccuracyUm;                    //像素精度um
    int PhotoelectricSignalPulseFilter;     //光电信号脉冲滤波
    int CamareTrigerPulseContinueTime10ns;  //相机触发脉冲持续时间10ns
    int PhotoelectricToCamareDist;          //光电与相机距离行
    int CamareFrameTrigerDelayRowCount;     // 相机帧触发延时行数
    int FrameSignalContinueTime;            //帧信号持续时间
    int ModuleEnableSignal;                 //模块使能信号
    int CamarePhotoRowCount;                //相机拍照行数
    int InnerRowFrequency;                  //内部行频
    int PhotoMode;                          //拍照模式
    int PhotoEndDelayRowCount;              //拍照延时行数

    int LightField1DelayTime;            //光场1延时时间10ns
    int LightField1GlowTime;             //光场1发光时间10ns
    int LightField2DelayTime;            //光场2延时时间10ns
    int LightField2GlowTime;             //光场2发光时间10ns
    int LightField3DelayTime;            //光场3延时时间10ns
    int LightField3GlowTime;             //光场3发光时间10ns
    int LightField4DelayTime;            //光场4延时时间10ns
    int LightField4GlowTime;             //光场4发光时间10ns
    int SelectedLightFieldNumber;        //选择光场数量
    int HorizontalDarkfieldSelectRegister;  //横向暗场选择寄存器
    int CamareAndLightFieldControl;         //相机与光场控制
    int SignalSwitch;                       //信号切换
    int RowSignalSelected;                  //行信号源选择
};


#endif // GLOBAL_H

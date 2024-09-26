#ifndef HSTOOL_H
#define HSTOOL_H

#include <QMutex>
#include <QObject>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <queue>
#include <QImage>
#include "hstool_global.h"

class HSTOOL_EXPORT Hstool
{
public:
    Hstool();
};

#define ADDR0 0x0070    // 编码器单位刻度对应距离(um)
#define ADDR1 0x0010    // 编码脉冲滤波(us)
#define ADDR2 0x0860    // 编码器计数结束标志
#define ADDR3 0x0864    // 编码器计数
#define ADDR4 0x0868    // 编码器触发行计数
#define ADDR5 0x086C    // 编码器4倍频计数
#define ADDR6 0x0870    // 编码器单位时间脉冲计数
#define ADDR7 0x01D4    // 编码器计数时间(0.5s)
#define ADDR8 0x001C    // 编码通道
#define ADDR9 0x00F0    // 编码器转数
#define ADDR10 0x00F4   // 辊道周长(um)
#define ADDR11 0x00F8   // 期望单个像素精度(um)
#define ADDR12 0x00FC   // 辊道最大速度对应行频
#define ADDR13 0x01D8   // 每行对应的编码计数
#define ADDR14 0x0074   // 像素精度(um)
#define ADDR15 0x007C   // 光电信号脉冲滤波(us)
#define ADDR16 0x0090   // 相机触发脉冲持续时间(10ns)
#define ADDR17 0x0094   // 光电相机距离(行)
#define ADDR18 0x00C8   // 相机帧信号触发延时行数(行)
#define ADDR19 0x00CC   // 帧信号持续时间(10ns)
#define ADDR20 0x00D0   // 模块使能信号
#define ADDR21 0x00D8   // 相机拍照行数(行)
#define ADDR22 0x00DC   // 内部行频
#define ADDR23 0x0098   // 光场1延时时间(10ns)
#define ADDR24 0x009C   // 光场1发光时间(10ns)
#define ADDR25 0x00A0   // 光场2延时时间(10ns)
#define ADDR26 0x00A4   // 光场2发光时间(10ns)
#define ADDR27 0x00A8   // 光场3延时时间(10ns)
#define ADDR28 0x00AC   // 光场3发光时间(10ns)
#define ADDR29 0x00B0   // 光场4延时时间(10ns)
#define ADDR30 0x00B4   // 光场4发光时间(10ns)
#define ADDR31 0x00B8   // 光场5延时时间(10ns)
#define ADDR32 0x00BC   // 光场5发光时间(10ns)
#define ADDR33 0x00C0   // 光场6延时时间(10ns)
#define ADDR34 0x00C4   // 光场6发光时间(10ns)
#define ADDR35 0x0040   // 相机与光场控制
#define ADDR36 0x00D4   // 信号切换
#define ADDR37 0x01D0   // 行信号源选择
#define ADDR38 0x00E0   // 内部产生光电信号
#define ADDR39 0x00E4
#define ADDR40 0x00E8   // 帧信号为1时执行，为0时结束
#define ADDR41 0x00EC
#define ADDR42 0x0078   // 上位机反馈信号
#define ADDR43 0x0100   // 光场7延时时间(10ns)
#define ADDR44 0x0104   // 光场7发光时间(10ns)
#define ADDR45 0x0108   // 光场8延时时间(10ns)
#define ADDR46 0x010C   // 光场8发光时间(10ns)
#define ADDR47 0x0110   // 光场9延时时间(10ns)
#define ADDR48 0x0114   // 光场9发光时间(10ns)
#define ADDR49 0x0118   // 光场10延时时间(10ns)
#define ADDR50 0x011C   // 光场10发光时间(10ns)
#define ADDR51 0x0120   // 光场11延时时间(10ns)
#define ADDR52 0x0124   // 光场11发光时间(10ns)
#define ADDR53 0x0128   // 光场12延时时间(10ns)
#define ADDR54 0x012C   // 光场12发光时间(10ns)
#define ADDR55 0x0130   // 选择光场的数量
#define ADDR56 0x0134   // 横向暗场选择寄存器
#define ADDR57 0x0874  //编码器脉冲计数1
#define ADDR58 0x0878  //编码器脉冲计数2
#define ADDR59 0x01DC  //固定或自动拍照模式
#define ADDR60 0x01E0  //相机结束延时行数
#define ADDR61 0x087C  //压轮编码值可读标志
#define ADDR62 0x0844  //压轮编码器四倍频计数


// 每帧数据结构体
struct FrameImage {
    QImage buffer;
    int framecount;
};

//单个缺陷信息
struct GlassDefect{
    size_t id;              // 主键id,在所有缺陷中的顺序
    int defectId;           // 缺陷id，在一块玻璃中缺陷的顺序
    QString time;           // 缺陷检测时间
    QString defectType;     // 缺陷类型
    QString defectLevel;    // 缺陷等级，OK NG
    double x;               // 缺陷在玻璃上的X坐标
    double y;               // 缺陷在玻璃上的Y坐标
    double length;          // 缺陷的长度
    double width;           // 缺陷的宽度
    double area;            // 缺陷面积大小
    size_t glassid;         // 外键id,玻璃的id
    QString imagePath1;      // 光场1缺陷图片的路径
    QString imagePath2;      // 光场2缺陷图片的路径
    QString imagePath3;      // 光场3缺陷图片的路径
};

// 孔洞、门夹、丝印信息
struct GlassSize{
    size_t id;              // 主键id,玻璃尺寸信息的顺序id
    int sizeID;             // 孔、门夹、丝印排列顺序
    QString time;           // 时间
    QString sizeType;       // 类型
    QString sizeLevel;      // 等级
    double lengthX;         // 长X(mm)
    double widthY;          // 宽Y(mm)
    double marginsX;        // 边距X(mm)
    double marginsY;        // 边距Y(mm)
    size_t glassid;         // 外键id,玻璃的id
    QString imagePath;      // 缺陷图片的路径
};

//数据统计信息
struct GlassDataBaseInfo{
    int id;              // 玻璃的id，唯一的主键
    QString time;           // 时间
    QString OKorNG;         // 整体情况OK或者NG
    QString sizeOKorNG;     // 尺寸OK或者NG
    double length;          // 玻璃的长度
    double width;           // 玻璃的宽度
    double duijiaoxian1;    // 玻璃的对角线1
    double duijiaoxian2;    // 玻璃的对角线2
    int defectNumber;       // 玻璃的缺陷数量
    QString defectOKorNG;   // 缺陷OK或者NG
    int huashanNumber;      // 划伤数量
    int qipaoNumber;        // 气泡数量
    int jieshiNumber;       // 结石数量
    int benbianNumber;      // 崩边数量
    int zanwuNumber;        // 脏污数量
    int liewenNumber;       // 裂纹数量
    int qitaNumber;         // 其它数量
    GlassDataBaseInfo(){
        id =0;
        time = "0";
        OKorNG = "OK";
        sizeOKorNG = "OK";
        length =0;
        width =0;
        duijiaoxian1 = 0;
        duijiaoxian2 =0;
        defectNumber = 0;
        defectOKorNG = "OK";
        huashanNumber = 0;
        qipaoNumber = 0;
        jieshiNumber = 0;
        benbianNumber = 0;
        zanwuNumber = 0;
        liewenNumber = 0;
        qitaNumber = 0;
    }
    ~GlassDataBaseInfo(){}
};
// 缺陷统计表格统计结果
struct GlassDefectInfo{
    std::vector<GlassDefect> defectdatas; //多行数据
    int defectCount;//缺陷数目
};
// 尺寸统计表格统计结果
struct GlassSizeInfo{
    std::vector<GlassSize> sizedatas; // 多行尺寸数据
    int sizeCount; //尺寸数据数目
    QString OutLinePath;    // 轮廓图片的路径
};

//数据总的统计结果
struct SummaryResult {
    int GlassNum;       //玻璃总数
    int ngNum;          //NG数目
    int okNum;          //OK数目
    double suceessRate; //合格率
    int sorted;         //已分拣
    int unsorted;       //待分检
    int exceptNum;      //异常数
    bool currentOKorNG; //当前玻璃OK或者NG
    bool currentSort;   //当前玻璃是否分拣
    SummaryResult():GlassNum(0),
        ngNum(0),
        okNum(0),
        suceessRate(0.0),
        sorted(0),
        unsorted(0),
        exceptNum(0),
        currentOKorNG(false),
        currentSort(false){}
};


struct SignalControl {
   /**
   * @brief temp0编码器单位刻度对应距离(um)
   */
  unsigned int temp0;
  /**
   * @brief temp1编码脉冲滤波(us)
   */
  unsigned int temp1;
  /**
   * @brief temp2编码器计数结束标志
   */
  unsigned int temp2;
  /**
   * @brief temp3编码器计数
   */
  unsigned int temp3;
  /**
   * @brief temp4编码器触发行计数
   */
  unsigned int temp4;
  /**
   * @brief temp5编码器4倍频计数
   */
  unsigned int temp5;
  /**
   * @brief temp6编码器单位时间脉冲计数
   */
  unsigned int temp6;
  /**
   * @brief temp7编码器计数时间(0.5s)
   */
  unsigned int temp7;
  /**
   * @brief temp8编码通道
   */
  unsigned int temp8;
  /**
   * @brief temp9编码器转数
   */
  unsigned int temp9;
  /**
   * @brief temp10辊道周长(um)
   */
  unsigned int temp10;
  /**
   * @brief temp11期望单个像素精度(um)
   */
  unsigned int temp11;
  /**
   * @brief temp12辊道最大速度对应行频
   */
  unsigned int temp12;
  /**
   * @brief temp13每行对应的编码计数
   */
  unsigned int temp13;
  /**
   * @brief temp14像素精度(um)
   */
  unsigned int temp14;
  /**
   * @brief temp15光电信号脉冲滤波(us)
   */
  unsigned int temp15;
  /**
   * @brief temp16相机触发脉冲持续时间(10ns)
   */
  unsigned int temp16;
  /**
   * @brief temp17光电相机距离(行)
   */
  unsigned int temp17;
  /**
   * @brief temp18相机帧信号触发延时行数(行)
   */
  unsigned int temp18;
  /**
   * @brief temp19帧信号持续时间(10ns)
   */
  unsigned int temp19;
  /**
   * @brief temp20模块使能信号
   */
  unsigned int temp20;
  /**
   * @brief temp21相机拍照行数(行)
   */
  unsigned int temp21;
  /**
   * @brief temp22内部行频
   */
  unsigned int temp22;
  /**
   * @brief temp23光场1延时时间(10ns)
   */
  unsigned int temp23;
  /**
   * @brief temp24光场1发光时间(10ns)
   */
  unsigned int temp24;
  /**
   * @brief temp25光场2延时时间(10ns)
   */
  unsigned int temp25;
  /**
   * @brief temp26光场2发光时间(10ns)
   */
  unsigned int temp26;
  /**
   * @brief temp27光场3延时时间(10ns)
   */
  unsigned int temp27;
  /**
   * @brief temp28光场3发光时间(10ns)
   */
  unsigned int temp28;
  /**
   * @brief temp29光场4延时时间(10ns)
   */
  unsigned int temp29;
  /**
   * @brief temp30光场4发光时间(10ns)
   */
  unsigned int temp30;
  /**
   * @brief temp31光场5延时时间(10ns)
   */
  unsigned int temp31;
  /**
   * @brief temp32光场5发光时间(10ns)
   */
  unsigned int temp32;
  /**
   * @brief temp33光场6延时时间(10ns)
   */
  unsigned int temp33;
  /**
   * @brief temp34 光场6发光时间(10ns)
   */
  unsigned int temp34;
  /**
   * @brief temp35 35相机与光场控制
   */
  unsigned int temp35;
  /**
   * @brief temp36信号切换
   */
  unsigned int temp36;
  /**
   * @brief temp37行信号源选择
   */
  unsigned int temp37;
  unsigned int temp38;

  /**
   * @brief temp43光场7延时时间(10ns)
   */
  unsigned int temp43;
  /**
   * @brief temp44 光场7发光时间(10ns)
   */
  unsigned int temp44;
  /**
   * @brief temp45 光场8延时时间(10ns)
   */
  unsigned int temp45;
  /**
   * @brief temp46 光场8发光时间(10ns)
   */
  unsigned int temp46;
  /**
   * @brief temp47 光场9延时时间(10ns)
   */
  unsigned int temp47;
  /**
   * @brief temp48 光场9发光时间(10ns)
   */
  unsigned int temp48;
  /**
   * @brief temp49 光场10延时时间(10ns)
   */
  unsigned int temp49;
  /**
   * @brief temp50 光场10发光时间(10ns)
   */
  unsigned int temp50;
  /**
   * @brief temp51 光场11延时时间(10ns)
   */
  unsigned int temp51;
  /**
   * @brief temp52 光场11发光时间(10ns)
   */
  unsigned int temp52;
  /**
   * @brief temp53 光场12延时时间(10ns)
   */
  unsigned int temp53;
  /**
   * @brief temp54 光场12发光时间(10ns)
   */
  unsigned int temp54;
  /**
   * @brief temp55 选择光场的数量
   */
  unsigned int temp55;
  /**
   * @brief temp56 横向暗场选择寄存器
   */
  unsigned int temp56;
  /**
   * @brief tempRollerACount 压轮编码器A计数
   */
  unsigned int tempRollerACount;
  /**
   * @brief tempRollerBCount 压轮编码器B计数
   */
  unsigned int tempRollerBCount;
  /**
   * @brief tempRollerCofficient 压轮编码器系数
   */
  double tempRollerCofficient;
  /**
   * @brief tempAutoPhoto 拍照模式
   */
  unsigned int tempAutoPhoto;
  /**
   * @brief tempPhotoEndDelayLine 拍照结束延时行数
   */
  unsigned int tempPhotoEndDelayLine;
  /**
   * @brief tempRoller4ABCount 压轮编码器4倍频计数
   */
  unsigned int tempRoller4ABCount;
  /**
   * @brief systemName 系统名称
   */
  QString systemName;
  /**
   * @brief CamareNumber 相机数量
   */
  int CamareNumber;
  /**
   * @brief Camare0Name 相机0名称
   */
  QString Camare0Name;
  /**
   * @brief Camare1Name 相机1名称
   */
  QString Camare1Name;
  /**
   * @brief Camare2Name 相机2名称
   */
  QString Camare2Name;
  /**
   * @brief Camare3Name 相机3名称
   */
  QString Camare3Name;
  /**
   * @brief ServerIP 服务器IP
   */
  QString ServerIP;
  /**
   * @brief ServerPort 服务端口
   */
  int ServerPort;
  /**
   * @brief SaveOriginImage 保存原图
   */
  int SaveOriginImage;
  /**
   * @brief SaveEntireImage 保存整图
   */
  int SaveEntireImage;
  /**
   * @brief SaveFlawImage 保存缺检图
   */
  int SaveFlawImage;
  /**
   * @brief SaveCropImage 保存裁剪图
   */
  int SaveCropImage;
  /**
   * @brief XYLengthEnable 尺寸测量
   */
  int XYLengthEnable;
  /**
   * @brief FlawDefectEnable 缺陷检测
   */
  int FlawDefectEnable;
  /**
   * @brief Camera12PixelDeviation 12相机像素偏差
   */
  int Camera12PixelDeviation;
  /**
   * @brief Camera23PixelDeviation 23相机像素偏差
   */
  int Camera23PixelDeviation;
  /**
   * @brief Camera24PixelDeviation 24相机像素偏差
   */
  int Camera24PixelDeviation;
  /**
   * @brief SilkToRollerDist 丝印离辊道距离
   */
  int SilkToRollerDist;
  /**
   * @brief ScratchAreaThreshold 划痕面积阈值
   */
  int ScratchAreaThreshold;
  /**
   * @brief BubbleStoneAreaThreshold 气节面积阈值
   */
  int BubbleStoneAreaThreshold;
  /**
   * @brief DirtyAreaThreshold 脏污面积阈值
   */
  int DirtyAreaThreshold;
  /**
   * @brief YAccuracyB Y方向精度B
   */
  int YAccuracyB;
  /**
   * @brief YAccuracyK Y方向精度K
   */
  int YAccuracyK;
  /**
   * @brief Width 宽度
   */
  int Width;
  /**
   * @brief WidthDeviation 宽度误差
   */
  int WidthDeviation;
  /**
   * @brief Digonal1 对角线1
   */
  int Digonal1;
  /**
   * @brief Digonal1Deviation 对角线1误差
   */
  int Digonal1Deviation;
  /**
   * @brief Diagonal2 对角线2
   */
  int Diagonal2;
  /**
   * @brief Digonal2Deviation 对角线2误差
   */
  int Digonal2Deviation;
  /**
   * @brief Camera1Pixel0Accuracy 相机1像素0精度
   */
  int Camera1Pixel0Accuracy;
  /**
   * @brief Camera1PixelKValue 相机1像素K值
   */
  int Camera1PixelKValue;
  /**
   * @brief Camera21AccuracyRatio 相机21精度比值
   */
  int Camera21AccuracyRatio;
  /**
   * @brief Camera2PixelKValue 相机2像素K值
   */
  int Camera2PixelKValue;
  /**
   * @brief Length 长度
   */
  int Length;
  /**
   * @brief LengthDeviation 长度误差
   */
  int LengthDeviation;
  /**
   * @brief Camera0Frame 相机0帧次
   */
  int Camera0Frame;
  /**
   * @brief Camera0PhotoRow 相机0拍照行数
   */
  int Camera0PhotoRow;
  /**
   * @brief Camera0ExposureTime 相机0曝光时间
   */
  int Camera0ExposureTime;
  /**
   * @brief Camera0Gain 相机0增益
   */
  int Camera0Gain;
  /**
   * @brief Camera1Frame 相机1帧次
   */
  int Camera1Frame;
  /**
   * @brief Camera1PhotoRow 相机1拍照行数
   */
  int Camera1PhotoRow;
  /**
   * @brief Camera1ExposureTime 相机1曝光时间
   */
  int Camera1ExposureTime;
  /**
   * @brief Camera1Gain 相机1增益
   */
  int Camera1Gain;
  /**
   * @brief Camera2Frame 相机2帧次
   */
  int Camera2Frame;
  /**
   * @brief Camera2PhotoRow 相机2拍照行数
   */
  int Camera2PhotoRow;
  /**
   * @brief Camera2ExposureTime 相机2曝光时间
   */
  int Camera2ExposureTime;
  /**
   * @brief Camera2Gain 相机2增益
   */
  int Camera2Gain;
  /**
   * @brief Camera3Frame 相机3帧次
   */
  int Camera3Frame;
  /**
   * @brief Camera3PhotoRow 相机3拍照行数
   */
  int Camera3PhotoRow;
  /**
   * @brief Camera3ExposureTime 相机3曝光时间
   */
  int Camera3ExposureTime;
  /**
   * @brief Camera3Gain 相机3增益
   */
  int Camera3Gain;
};

struct DushenCameraArgs{
    double expo;        // 相机曝光时间
    double gain;        // 相机增益
    double height;      // 相机行数
    double framecount;  // 相机多少帧
    int fieldnumberset; // 场的数量
    int camNumber;      // 相机个数
    QString camName;    // 相机名称
};


template <typename T>
class HSTOOL_EXPORT ThreadSafeQueue {
public:
    ThreadSafeQueue() {}

     inline void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        condition_.notify_one();
    }

    inline bool pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this](){ return!queue_.empty(); });
        if (queue_.empty()) {
            return false;
        }
        item = queue_.front();
        queue_.pop();
        return true;
    }

    inline bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
};

#endif // HSTOOL_H

#ifndef SIGNALCONTROLDATA_H
#define SIGNALCONTROLDATA_H

#include "RegParasComm.h"
#include "hstool.h"

#define ADDR0 0x0070
#define ADDR1 0x0010
#define ADDR2 0x0860
#define ADDR3 0x0864
#define ADDR4 0x0868
#define ADDR5 0x086C
#define ADDR6 0x0870
#define ADDR7 0x01D4
#define ADDR8 0x001C
#define ADDR9 0x00F0
#define ADDR10 0x00F4
#define ADDR11 0x00F8
#define ADDR12 0x00FC
#define ADDR13 0x01D8
#define ADDR14 0x0074
#define ADDR15 0x007C
#define ADDR16 0x0090
#define ADDR17 0x0094
#define ADDR18 0x00C8
#define ADDR19 0x00CC //帧信号持续时间
#define ADDR20 0x00D0
#define ADDR21 0x00D8
#define ADDR22 0x00DC
#define ADDR23 0x0098
#define ADDR24 0x009C
#define ADDR25 0x00A0
#define ADDR26 0x00A4
#define ADDR27 0x00A8
#define ADDR28 0x00AC
#define ADDR29 0x00B0
#define ADDR30 0x00B4
#define ADDR31 0x00B8
#define ADDR32 0x00BC
#define ADDR33 0x00C0
#define ADDR34 0x00C4
#define ADDR35 0x0040
#define ADDR36 0x00D4
#define ADDR37 0x01D0
#define ADDR38 0x00E0//内部产生光电信号
#define ADDR39 0x00E4
#define ADDR40 0x00E8 //帧信号为1时执行，为0时结束
#define ADDR41 0x00EC
#define ADDR42 0x0078//上位机反馈信号
#define ADDR43 0x0100
#define ADDR44 0x0104
#define ADDR45 0x0108
#define ADDR46 0x010C
#define ADDR47 0x0110
#define ADDR48 0x0114
#define ADDR49 0x0118
#define ADDR50 0x011C
#define ADDR51 0x0120
#define ADDR52 0x0124
#define ADDR53 0x0128
#define ADDR54 0x012C
#define ADDR55 0x0130
#define ADDR56 0x0134
#define ADDR57 0x0874  //编码器脉冲计数1
#define ADDR58 0x0878  //编码器脉冲计数2
#define ADDR59 0x01DC  //固定或自动拍照模式
#define ADDR60 0x01E0  //相机结束延时行数
#define ADDR61 0x087C  //压轮编码值可读标志
#define ADDR62 0x0844  //压轮编码器四倍频计数


class SignalControlData : public QObject
{
    Q_OBJECT
public:
    SignalControlData(RegParasComm& sig_comm);
    ~SignalControlData();

private:
    RegParasComm& m_pSig_comm;
    QString str[63];
    unsigned int mid1;
    unsigned int mid2;
    unsigned int mid3;
    unsigned int aaa = 0;
    unsigned int bbb = 0;
    unsigned int ccc = 0;
    unsigned int ddd = 0;
    unsigned int eee = 0;
    unsigned int fff = 0;
    unsigned int ggg = 0;
    unsigned int temp1 = 0;
    unsigned int temp2 = 1;

public:
    void InitData();
    void GetData();
    void SetData();
    void SaveData();
    void Trigger();


    SignalControl* sigctrl;
    QTimer* timer;
    QThread *AlmLightOutThread;
    bool StopFlag_sig;

public slots:
    void slot_DeliverLightData();
    void TimeOut1();
signals:
    void sig_updateSortGlassSignal();
    void sig_RecipeChage();

public:
    int FrameSignal;                    //帧信号
    long CodeCount;                     //编码值
    long CodeLineCount;
    long Code4Count;
    long CodePerCount;
    bool AlmLightSignal;                // 报警信号灯
    long encodeARollerCount;            //编码器压轮A计数
    long encodeBRollerCount;            //编码器压轮B计数
    long encodeRollerCount;             //编码器压轮计数
    long encodeAB4;                     // 压轮编码器四倍频
};

#endif  // SIGNALCONTROLDATA_H

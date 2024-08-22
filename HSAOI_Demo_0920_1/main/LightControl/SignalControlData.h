#ifndef SIGNALCONTROLDATA_H
#define SIGNALCONTROLDATA_H

#include <Global.h>
#include <Parameter/JsonParse2Map.h>
#include "RegParasComm.h"

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
#define ADDR19 0x00CC
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
#define ADDR40 0x00E8
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

typedef struct SignalControl {
  unsigned int temp0;
  unsigned int temp1;
  unsigned int temp2;
  unsigned int temp3;
  unsigned int temp4;
  unsigned int temp5;
  unsigned int temp6;
  unsigned int temp7;
  unsigned int temp8;
  unsigned int temp9;
  unsigned int temp10;
  unsigned int temp11;
  unsigned int temp12;
  unsigned int temp13;
  unsigned int temp14;
  unsigned int temp15;
  unsigned int temp16;
  unsigned int temp17;
  unsigned int temp18;
  unsigned int temp19;
  //long  temp19;
  unsigned int temp20;
  unsigned int temp21;
  unsigned int temp22;
  unsigned int temp23;
  unsigned int temp24;
  unsigned int temp25;
  unsigned int temp26;
  unsigned int temp27;
  unsigned int temp28;
  unsigned int temp29;
  unsigned int temp30;
  unsigned int temp31;
  unsigned int temp32;
  unsigned int temp33;
  unsigned int temp34;
  unsigned int temp35;
  unsigned int temp36;
  unsigned int temp37;
  unsigned int temp38;


  unsigned int temp43;
  unsigned int temp44;
  unsigned int temp45;
  unsigned int temp46;
  unsigned int temp47;
  unsigned int temp48;
  unsigned int temp49;
  unsigned int temp50;
  unsigned int temp51;
  unsigned int temp52;
  unsigned int temp53;
  unsigned int temp54;
  unsigned int temp55;
  unsigned int temp56;
  unsigned int tempRollerACount;
  unsigned int tempRollerBCount;
  double tempRollerCofficient;
  unsigned int tempAutoPhoto;
  unsigned int tempPhotoEndDelayLine;
  unsigned int tempRoller4ABCount;

} SignalControl;


class SignalControlData : public QObject,public QRunnable
{
    Q_OBJECT
public:
    SignalControlData(RegParasComm& sig_comm);
    ~SignalControlData();
    void InitData();
    void GetData();
    void SetData();
    void SaveData();
    void Trigger();

private:
    virtual void run() override;

public:
    std::atomic<bool> hasStopThread;    //线程停止

 RegParasComm& m_pSig_comm;
 JsonParse2Map* JSONRECIPE;
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
//  void sig_SendAlmSignal();

};

#endif  // SIGNALCONTROLDATA_H

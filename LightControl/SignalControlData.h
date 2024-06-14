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


//    specificItem0 = ui->treeWidget->topLevelItem(0);        //编码器参数
//    childItem0 = specificItem0->child(0);                   // 编码器单位刻度对应距离(um)
//    childItem1 = specificItem0->child(1);                   // 编码脉冲滤波(us)
//    childItem2 = specificItem0->child(2);                   // 编码器计数结束标志
//    childItem3 = specificItem0->child(3);                   // 编码器计数
//    childItem4 = specificItem0->child(4);                   // 编码器触发行计数
//    childItem5 = specificItem0->child(5);                   // 编码器4倍频计数
//    childItem6 = specificItem0->child(6);                   // 编码器单位时间脉冲计数
//    childItem7 = specificItem0->child(7);                   // 编码器计数时间(0.5s)
//    childItem8 = specificItem0->child(8);                   // 编码通道
//    childItem9 = specificItem0->child(9);                   // 编码器转数
//    childItem10 = specificItem0->child(10);                 // 辊道周长(um)
//    childItem11 = specificItem0->child(11);                 // 期望单个像素精度(um)
//    childItem12 = specificItem0->child(12);                 // 辊道最大速度对应行频
//    childItem13 = specificItem0->child(13);                 // 每行对应的编码计数
//    childItem_rollerACount = specificItem0->child(14);      // 压轮编码器A计数
//    childItem_rollerBCount = specificItem0->child(15);      // 压轮编码器B计数
//    childItemAB4 = specificItem0->child(16);                // 压轮编码器4倍频计数
//    chileItem_rollerCofficient = specificItem0->child(17);  // 压轮编码器系数

//    specificItem1 = ui->treeWidget->topLevelItem(1);        //控制器系统参数
//    childItem14 = specificItem1->child(0);                  //像素精度(um)
//    childItem15 = specificItem1->child(1);                  //光电信号脉冲滤波(us)
//    childItem16 = specificItem1->child(2);                  //相机触发脉冲持续时间(10ns)
//    childItem17 = specificItem1->child(3);                  //光电相机距离(行)
//    childItem18 = specificItem1->child(4);                  //相机帧信号触发延时行数(行)
//    childItem19 = specificItem1->child(5);                  //帧信号持续时间(10ns)
//    childItem20 = specificItem1->child(6);                  //模块使能信号
//    childItem21 = specificItem1->child(7);                  //相机拍照行数(行)
//    childItem22 = specificItem1->child(8);                  //内部行频
//    chileItem_photoMode = specificItem1->child(9);          //拍照模式
//    chileItem_photoEndDelayLine = specificItem1->child(10); //拍照结束延时行数

//    specificItem2 = ui->treeWidget->topLevelItem(2);//光源控制器参数
//    childItem23 = specificItem2->child(0);          // 光场1延时时间(10ns)
//    childItem24 = specificItem2->child(1);          // 光场1发光时间(10ns)
//    childItem25 = specificItem2->child(2);          // 光场2延时时间(10ns)
//    childItem26 = specificItem2->child(3);          // 光场2发光时间(10ns)
//    childItem27 = specificItem2->child(4);          // 光场3延时时间(10ns)
//    childItem28 = specificItem2->child(5);          // 光场3发光时间(10ns)
//    childItem29 = specificItem2->child(6);          // 光场4延时时间(10ns)
//    childItem30 = specificItem2->child(7);          // 光场4发光时间(10ns)
//    childItem31 = specificItem2->child(8);          // 光场5延时时间(10ns)
//    childItem32 = specificItem2->child(9);          // 光场5发光时间(10ns)
//    childItem33 = specificItem2->child(10);         // 光场6延时时间(10ns)
//    childItem34 = specificItem2->child(11);         // 光场6发光时间(10ns)
//    childItem35 = specificItem2->child(26);         // 35相机与光场控制
//    childItem36 = specificItem2->child(27);         // 36信号切换
//    childItem37 = specificItem2->child(28);         // 37行信号源选择
//    childItem43 = specificItem2->child(12);         // 光场7延时时间(10ns)
//    childItem44 = specificItem2->child(13);         // 光场7发光时间(10ns)
//    childItem45 = specificItem2->child(14);         // 光场8延时时间(10ns)
//    childItem46 = specificItem2->child(15);         // 光场8发光时间(10ns)
//    childItem47 = specificItem2->child(16);         // 光场9延时时间(10ns)
//    childItem48 = specificItem2->child(17);         // 光场9发光时间(10ns)
//    childItem49 = specificItem2->child(18);         // 光场10延时时间(10ns)
//    childItem50 = specificItem2->child(19);         // 光场10发光时间(10ns)
//    childItem51 = specificItem2->child(20);         // 光场11延时时间(10ns)
//    childItem52 = specificItem2->child(21);         // 光场11发光时间(10ns)
//    childItem53 = specificItem2->child(22);         // 光场12延时时间(10ns)
//    childItem54 = specificItem2->child(23);         // 光场12发光时间(10ns)
//    childItem55 = specificItem2->child(24);         // 选择光场的数量
//    childItem56 = specificItem2->child(25);         // 横向暗场选择寄存器


typedef struct SignalControl {
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

} SignalControl;


class SignalControlData : public QObject {
  Q_OBJECT
 public:
  SignalControlData(RegParasComm& sig_comm);
  ~SignalControlData();

private:
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
//  void sig_SendAlmSignal();

};

#endif  // SIGNALCONTROLDATA_H

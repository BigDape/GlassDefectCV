#include "SignalControlData.h"
#pragma execution_character_set("utf-8")

SignalControlData::SignalControlData(RegParasComm& sig_comm)
    : m_pSig_comm(sig_comm) {
  sigctrl = new SignalControl();
  mid1 = 0;
  mid2 = 0;
  mid3 = 0;
  StopFlag_sig = false;

  Global::FrameSignal = 0;
  Global::CodeCount = 0;
}

SignalControlData::~SignalControlData() {}

void SignalControlData::InitData() {
  JSONRECIPE = new JsonParse2Map("Recipes/" + Global::CurrentRecipe + ".json");
  str[0] = "编码器参数.编码器单位刻度对应距离";
  str[1] = "编码器参数.编码脉冲滤波";
  str[2] = "编码器参数.编码器计数结束标志";
  str[3] = "编码器参数.编码器计数";
  str[4] = "编码器参数.编码器触发行计数";
  str[5] = "编码器参数.编码器4倍频计数";
  str[6] = "编码器参数.编码器单位时间脉冲计数";
  str[7] = "编码器参数.编码器计数时间";
  str[8] = "编码器参数.编码通道";
  str[9] = "编码器参数.编码器转数";
  str[10] = "编码器参数.辊道周长";
  str[11] = "编码器参数.期望单个像素精度";
  str[12] = "编码器参数.辊道最大速度对应行频";
  str[13] = "编码器参数.每行对应的编码计数";
  str[14] = "控制器系统参数.像素精度";
  str[15] = "控制器系统参数.光电信号脉冲滤波";
  str[16] = "控制器系统参数.相机触发脉冲持续时间";
  str[17] = "控制器系统参数.光电相机距离";
  str[18] = "控制器系统参数.相机帧信号触发延时行数";
  str[19] = "控制器系统参数.帧信号持续时间";
  str[20] = "控制器系统参数.模块使能信号";
  str[21] = "控制器系统参数.相机拍照行数";
  str[22] = "控制器系统参数.内部行频";
  str[23] = "光源控制器参数.光场1延时时间";
  str[24] = "光源控制器参数.光场1发光时间";
  str[25] = "光源控制器参数.光场2延时时间";
  str[26] = "光源控制器参数.光场2发光时间";
  str[27] = "光源控制器参数.光场3延时时间";
  str[28] = "光源控制器参数.光场3发光时间";
  str[29] = "光源控制器参数.光场4延时时间";
  str[30] = "光源控制器参数.光场4发光时间";
  str[31] = "光源控制器参数.光场5延时时间";
  str[32] = "光源控制器参数.光场5发光时间";
  str[33] = "光源控制器参数.光场6延时时间";
  str[34] = "光源控制器参数.光场6发光时间";
  str[35] = "光源控制器参数.相机与光场控制";
  str[36] = "光源控制器参数.信号切换";
  str[37] = "光源控制器参数.行信号源选择";

  str[43]="光源控制器参数.光场7延时时间";
  str[44]="光源控制器参数.光场7发光时间";
  str[45]="光源控制器参数.光场8延时时间";
  str[46]="光源控制器参数.光场8发光时间";
  str[47]="光源控制器参数.光场9延时时间";
  str[48]="光源控制器参数.光场9发光时间";
  str[49]="光源控制器参数.光场10延时时间";
  str[50]="光源控制器参数.光场10发光时间";
  str[51]="光源控制器参数.光场11延时时间";
  str[52]="光源控制器参数.光场11发光时间";
  str[53]="光源控制器参数.光场12延时时间";
  str[54]="光源控制器参数.光场12发光时间";
  str[55]="光源控制器参数.选择光场的数量";
  str[56]="光源控制器参数.横向暗场选择寄存器";
  str[57]="编码器参数.压轮编码器A计数";
  str[58]="编码器参数.压轮编码器B计数";
  str[59]="编码器参数.压轮编码器系数";
  str[60]="控制器系统参数.拍照模式";
  str[61]="控制器系统参数.拍照结束延时行数";
  str[62]="编码器参数.压轮编码器四倍频计数";

  JSONRECIPE->getParameter(str[0], sigctrl->temp0);
  JSONRECIPE->getParameter(str[1], sigctrl->temp1);
  JSONRECIPE->getParameter(str[2], sigctrl->temp2);
  JSONRECIPE->getParameter(str[3], sigctrl->temp3);
  JSONRECIPE->getParameter(str[4], sigctrl->temp4);
  JSONRECIPE->getParameter(str[5], sigctrl->temp5);
  JSONRECIPE->getParameter(str[6], sigctrl->temp6);
  JSONRECIPE->getParameter(str[7], sigctrl->temp7);
  JSONRECIPE->getParameter(str[8], sigctrl->temp8);
  JSONRECIPE->getParameter(str[9], sigctrl->temp9);
  JSONRECIPE->getParameter(str[10], sigctrl->temp10);
  JSONRECIPE->getParameter(str[11], sigctrl->temp11);
  JSONRECIPE->getParameter(str[12], sigctrl->temp12);
  JSONRECIPE->getParameter(str[13], sigctrl->temp13);

  JSONRECIPE->getParameter(str[14], sigctrl->temp14);
  JSONRECIPE->getParameter(str[15], sigctrl->temp15);
  JSONRECIPE->getParameter(str[16], sigctrl->temp16);
  JSONRECIPE->getParameter(str[17], sigctrl->temp17);
  JSONRECIPE->getParameter(str[18], sigctrl->temp18);
  JSONRECIPE->getParameter(str[19], sigctrl->temp19);
  JSONRECIPE->getParameter(str[20], sigctrl->temp20);
  JSONRECIPE->getParameter(str[21], sigctrl->temp21);
  JSONRECIPE->getParameter(str[22], sigctrl->temp22);

  JSONRECIPE->getParameter(str[23], sigctrl->temp23);
  JSONRECIPE->getParameter(str[24], sigctrl->temp24);
  JSONRECIPE->getParameter(str[25], sigctrl->temp25);
  JSONRECIPE->getParameter(str[26], sigctrl->temp26);
  JSONRECIPE->getParameter(str[27], sigctrl->temp27);
  JSONRECIPE->getParameter(str[28], sigctrl->temp28);
  JSONRECIPE->getParameter(str[29], sigctrl->temp29);
  JSONRECIPE->getParameter(str[30], sigctrl->temp30);
  JSONRECIPE->getParameter(str[31], sigctrl->temp31);
  JSONRECIPE->getParameter(str[32], sigctrl->temp32);
  JSONRECIPE->getParameter(str[33], sigctrl->temp33);
  JSONRECIPE->getParameter(str[34], sigctrl->temp34);
  JSONRECIPE->getParameter(str[35], sigctrl->temp35);
  JSONRECIPE->getParameter(str[36], sigctrl->temp36);
  JSONRECIPE->getParameter(str[37], sigctrl->temp37);

  JSONRECIPE->getParameter(str[43], sigctrl->temp43);
  JSONRECIPE->getParameter(str[44], sigctrl->temp44);
  JSONRECIPE->getParameter(str[45], sigctrl->temp45);
  JSONRECIPE->getParameter(str[46], sigctrl->temp46);
  JSONRECIPE->getParameter(str[47], sigctrl->temp47);
  JSONRECIPE->getParameter(str[48], sigctrl->temp48);
  JSONRECIPE->getParameter(str[49], sigctrl->temp49);
  JSONRECIPE->getParameter(str[50], sigctrl->temp50);
  JSONRECIPE->getParameter(str[51], sigctrl->temp51);
  JSONRECIPE->getParameter(str[52], sigctrl->temp52);
  JSONRECIPE->getParameter(str[53], sigctrl->temp53);
  JSONRECIPE->getParameter(str[54], sigctrl->temp54);
  JSONRECIPE->getParameter(str[55], sigctrl->temp55);
  JSONRECIPE->getParameter(str[56], sigctrl->temp56);

  JSONRECIPE->getParameter(str[57], sigctrl->tempRollerACount);
  JSONRECIPE->getParameter(str[58], sigctrl->tempRollerBCount);
  JSONRECIPE->getParameter(str[59], sigctrl->tempRollerCofficient);
  JSONRECIPE->getParameter(str[60], sigctrl->tempAutoPhoto);
  JSONRECIPE->getParameter(str[61], sigctrl->tempPhotoEndDelayLine);
  JSONRECIPE->getParameter(str[62], sigctrl->tempRoller4ABCount);

  m_pSig_comm.SetRegs(ADDR0, ADDR0, &sigctrl->temp0);
  m_pSig_comm.SetRegs(ADDR1, ADDR1, &sigctrl->temp1);
  m_pSig_comm.SetRegs(ADDR7, ADDR7, &sigctrl->temp7);
  m_pSig_comm.SetRegs(ADDR8, ADDR8, &sigctrl->temp8);
  m_pSig_comm.SetRegs(ADDR9, ADDR9, &sigctrl->temp9);
  m_pSig_comm.SetRegs(ADDR10, ADDR10, &sigctrl->temp10);
  m_pSig_comm.SetRegs(ADDR11, ADDR11, &sigctrl->temp11);
  m_pSig_comm.SetRegs(ADDR12, ADDR12, &sigctrl->temp12);

  m_pSig_comm.SetRegs(ADDR14, ADDR14, &sigctrl->temp14);
  m_pSig_comm.SetRegs(ADDR15, ADDR15, &sigctrl->temp15);
  m_pSig_comm.SetRegs(ADDR16, ADDR16, &sigctrl->temp16);
  m_pSig_comm.SetRegs(ADDR17, ADDR17, &sigctrl->temp17);
  m_pSig_comm.SetRegs(ADDR18, ADDR18, &sigctrl->temp18);

  m_pSig_comm.SetRegs(ADDR19, ADDR19, &sigctrl->temp19);
  m_pSig_comm.SetRegs(ADDR20, ADDR20, &sigctrl->temp20);
  m_pSig_comm.SetRegs(ADDR21, ADDR21, &sigctrl->temp21);
  m_pSig_comm.SetRegs(ADDR22, ADDR22, &sigctrl->temp22);

  m_pSig_comm.SetRegs(ADDR23, ADDR23, &sigctrl->temp23);
  m_pSig_comm.SetRegs(ADDR24, ADDR24, &sigctrl->temp24);
  m_pSig_comm.SetRegs(ADDR25, ADDR25, &sigctrl->temp25);
  m_pSig_comm.SetRegs(ADDR26, ADDR26, &sigctrl->temp26);
  m_pSig_comm.SetRegs(ADDR27, ADDR27, &sigctrl->temp27);
  m_pSig_comm.SetRegs(ADDR28, ADDR28, &sigctrl->temp28);
  m_pSig_comm.SetRegs(ADDR29, ADDR29, &sigctrl->temp29);
  m_pSig_comm.SetRegs(ADDR30, ADDR30, &sigctrl->temp30);
  m_pSig_comm.SetRegs(ADDR31, ADDR31, &sigctrl->temp31);
  m_pSig_comm.SetRegs(ADDR32, ADDR32, &sigctrl->temp32);
  m_pSig_comm.SetRegs(ADDR33, ADDR33, &sigctrl->temp33);
  m_pSig_comm.SetRegs(ADDR34, ADDR34, &sigctrl->temp34);
  m_pSig_comm.SetRegs(ADDR35, ADDR35, &sigctrl->temp35);
  m_pSig_comm.SetRegs(ADDR36, ADDR36, &sigctrl->temp36);
  m_pSig_comm.SetRegs(ADDR37, ADDR37, &sigctrl->temp37);


  m_pSig_comm.SetRegs(ADDR43, ADDR43, &sigctrl->temp43);
  m_pSig_comm.SetRegs(ADDR44, ADDR44, &sigctrl->temp44);
  m_pSig_comm.SetRegs(ADDR45, ADDR45, &sigctrl->temp45);
  m_pSig_comm.SetRegs(ADDR46, ADDR46, &sigctrl->temp46);
  m_pSig_comm.SetRegs(ADDR47, ADDR47, &sigctrl->temp47);
  m_pSig_comm.SetRegs(ADDR48, ADDR48, &sigctrl->temp48);
  m_pSig_comm.SetRegs(ADDR49, ADDR49, &sigctrl->temp49);
  m_pSig_comm.SetRegs(ADDR50, ADDR50, &sigctrl->temp50);
  m_pSig_comm.SetRegs(ADDR51, ADDR51, &sigctrl->temp51);
  m_pSig_comm.SetRegs(ADDR52, ADDR52, &sigctrl->temp52);
  m_pSig_comm.SetRegs(ADDR53, ADDR53, &sigctrl->temp53);
  m_pSig_comm.SetRegs(ADDR54, ADDR54, &sigctrl->temp54);
  m_pSig_comm.SetRegs(ADDR55, ADDR55, &sigctrl->temp55);
  m_pSig_comm.SetRegs(ADDR56, ADDR56, &sigctrl->temp56);

  m_pSig_comm.SetRegs(ADDR59, ADDR59, &sigctrl->tempAutoPhoto);
  m_pSig_comm.SetRegs(ADDR60, ADDR60, &sigctrl->tempPhotoEndDelayLine);
}

void SignalControlData::GetData() {
  m_pSig_comm.GetRegs(ADDR0, ADDR0, &sigctrl->temp0);
  m_pSig_comm.GetRegs(ADDR1, ADDR1, &sigctrl->temp1);
  m_pSig_comm.GetRegs(ADDR2, ADDR2, &sigctrl->temp2);
  m_pSig_comm.GetRegs(ADDR3, ADDR3, &sigctrl->temp3);
  m_pSig_comm.GetRegs(ADDR4, ADDR4, &sigctrl->temp4);
  m_pSig_comm.GetRegs(ADDR5, ADDR5, &sigctrl->temp5);
  m_pSig_comm.GetRegs(ADDR6, ADDR6, &sigctrl->temp6);
  m_pSig_comm.GetRegs(ADDR7, ADDR7, &sigctrl->temp7);
  m_pSig_comm.GetRegs(ADDR8, ADDR8, &sigctrl->temp8);
  m_pSig_comm.GetRegs(ADDR9, ADDR9, &sigctrl->temp9);
  m_pSig_comm.GetRegs(ADDR10, ADDR10, &sigctrl->temp10);
  m_pSig_comm.GetRegs(ADDR11, ADDR11, &sigctrl->temp11);
  m_pSig_comm.GetRegs(ADDR12, ADDR12, &sigctrl->temp12);
  m_pSig_comm.GetRegs(ADDR13, ADDR13, &sigctrl->temp13);

  m_pSig_comm.GetRegs(ADDR14, ADDR14, &sigctrl->temp14);
  m_pSig_comm.GetRegs(ADDR15, ADDR15, &sigctrl->temp15);
  m_pSig_comm.GetRegs(ADDR16, ADDR16, &sigctrl->temp16);
  m_pSig_comm.GetRegs(ADDR17, ADDR17, &sigctrl->temp17);
  m_pSig_comm.GetRegs(ADDR19, ADDR19, &sigctrl->temp19);
  m_pSig_comm.GetRegs(ADDR20, ADDR20, &sigctrl->temp20);
  m_pSig_comm.GetRegs(ADDR21, ADDR21, &sigctrl->temp21);
  m_pSig_comm.GetRegs(ADDR22, ADDR22, &sigctrl->temp22);

  m_pSig_comm.GetRegs(ADDR23, ADDR23, &sigctrl->temp23);
  m_pSig_comm.GetRegs(ADDR24, ADDR24, &sigctrl->temp24);
  m_pSig_comm.GetRegs(ADDR25, ADDR25, &sigctrl->temp25);
  m_pSig_comm.GetRegs(ADDR26, ADDR26, &sigctrl->temp26);
  m_pSig_comm.GetRegs(ADDR27, ADDR27, &sigctrl->temp27);
  m_pSig_comm.GetRegs(ADDR28, ADDR28, &sigctrl->temp28);
  m_pSig_comm.GetRegs(ADDR29, ADDR29, &sigctrl->temp29);
  m_pSig_comm.GetRegs(ADDR30, ADDR30, &sigctrl->temp30);
  m_pSig_comm.GetRegs(ADDR31, ADDR31, &sigctrl->temp31);
  m_pSig_comm.GetRegs(ADDR32, ADDR32, &sigctrl->temp32);
  m_pSig_comm.GetRegs(ADDR33, ADDR33, &sigctrl->temp33);
  m_pSig_comm.GetRegs(ADDR34, ADDR34, &sigctrl->temp34);
  m_pSig_comm.GetRegs(ADDR35, ADDR35, &sigctrl->temp35);
  m_pSig_comm.GetRegs(ADDR36, ADDR36, &sigctrl->temp36);
  m_pSig_comm.GetRegs(ADDR37, ADDR37, &sigctrl->temp37);


  m_pSig_comm.GetRegs(ADDR43, ADDR43, &sigctrl->temp43);
  m_pSig_comm.GetRegs(ADDR44, ADDR44, &sigctrl->temp44);
  m_pSig_comm.GetRegs(ADDR45, ADDR45, &sigctrl->temp45);
  m_pSig_comm.GetRegs(ADDR46, ADDR46, &sigctrl->temp46);
  m_pSig_comm.GetRegs(ADDR47, ADDR47, &sigctrl->temp47);
  m_pSig_comm.GetRegs(ADDR48, ADDR48, &sigctrl->temp48);
  m_pSig_comm.GetRegs(ADDR49, ADDR49, &sigctrl->temp49);
  m_pSig_comm.GetRegs(ADDR50, ADDR50, &sigctrl->temp50);
  m_pSig_comm.GetRegs(ADDR51, ADDR51, &sigctrl->temp51);
  m_pSig_comm.GetRegs(ADDR52, ADDR52, &sigctrl->temp52);
  m_pSig_comm.GetRegs(ADDR53, ADDR53, &sigctrl->temp53);
  m_pSig_comm.GetRegs(ADDR54, ADDR54, &sigctrl->temp54);
  m_pSig_comm.GetRegs(ADDR55, ADDR55, &sigctrl->temp55);
  m_pSig_comm.GetRegs(ADDR56, ADDR56, &sigctrl->temp56);

  m_pSig_comm.GetRegs(ADDR59, ADDR59, &sigctrl->tempAutoPhoto);
  m_pSig_comm.GetRegs(ADDR60, ADDR60, &sigctrl->tempPhotoEndDelayLine);
}

void SignalControlData::SetData() {
  m_pSig_comm.SetRegs(ADDR0, ADDR0, &sigctrl->temp0);
  m_pSig_comm.SetRegs(ADDR1, ADDR1, &sigctrl->temp1);
  m_pSig_comm.SetRegs(ADDR7, ADDR7, &sigctrl->temp7);
  m_pSig_comm.SetRegs(ADDR8, ADDR8, &sigctrl->temp8);
  m_pSig_comm.SetRegs(ADDR9, ADDR9, &sigctrl->temp9);
  m_pSig_comm.SetRegs(ADDR10, ADDR10, &sigctrl->temp10);
  m_pSig_comm.SetRegs(ADDR11, ADDR11, &sigctrl->temp11);
  m_pSig_comm.SetRegs(ADDR12, ADDR12, &sigctrl->temp12);

  m_pSig_comm.SetRegs(ADDR14, ADDR14, &sigctrl->temp14);
  m_pSig_comm.SetRegs(ADDR15, ADDR15, &sigctrl->temp15);
  m_pSig_comm.SetRegs(ADDR16, ADDR16, &sigctrl->temp16);
  m_pSig_comm.SetRegs(ADDR17, ADDR17, &sigctrl->temp17);
  m_pSig_comm.SetRegs(ADDR18, ADDR18, &sigctrl->temp18);
  m_pSig_comm.SetRegs(ADDR19, ADDR19, &sigctrl->temp19);
  m_pSig_comm.SetRegs(ADDR20, ADDR20, &sigctrl->temp20);
  m_pSig_comm.SetRegs(ADDR21, ADDR21, &sigctrl->temp21);
  m_pSig_comm.SetRegs(ADDR22, ADDR22, &sigctrl->temp22);

  m_pSig_comm.SetRegs(ADDR23, ADDR23, &sigctrl->temp23);
  m_pSig_comm.SetRegs(ADDR24, ADDR24, &sigctrl->temp24);
  m_pSig_comm.SetRegs(ADDR25, ADDR25, &sigctrl->temp25);
  m_pSig_comm.SetRegs(ADDR26, ADDR26, &sigctrl->temp26);
  m_pSig_comm.SetRegs(ADDR27, ADDR27, &sigctrl->temp27);
  m_pSig_comm.SetRegs(ADDR28, ADDR28, &sigctrl->temp28);
  m_pSig_comm.SetRegs(ADDR29, ADDR29, &sigctrl->temp29);
  m_pSig_comm.SetRegs(ADDR30, ADDR30, &sigctrl->temp30);
  m_pSig_comm.SetRegs(ADDR31, ADDR31, &sigctrl->temp31);
  m_pSig_comm.SetRegs(ADDR32, ADDR32, &sigctrl->temp32);
  m_pSig_comm.SetRegs(ADDR33, ADDR33, &sigctrl->temp33);
  m_pSig_comm.SetRegs(ADDR34, ADDR34, &sigctrl->temp34);
  m_pSig_comm.SetRegs(ADDR35, ADDR35, &sigctrl->temp35);
  m_pSig_comm.SetRegs(ADDR36, ADDR36, &sigctrl->temp36);
  m_pSig_comm.SetRegs(ADDR37, ADDR37, &sigctrl->temp37);


  m_pSig_comm.SetRegs(ADDR43, ADDR43, &sigctrl->temp43);
  m_pSig_comm.SetRegs(ADDR44, ADDR44, &sigctrl->temp44);
  m_pSig_comm.SetRegs(ADDR45, ADDR45, &sigctrl->temp45);
  m_pSig_comm.SetRegs(ADDR46, ADDR46, &sigctrl->temp46);
  m_pSig_comm.SetRegs(ADDR47, ADDR47, &sigctrl->temp47);
  m_pSig_comm.SetRegs(ADDR48, ADDR48, &sigctrl->temp48);
  m_pSig_comm.SetRegs(ADDR49, ADDR49, &sigctrl->temp49);
  m_pSig_comm.SetRegs(ADDR50, ADDR50, &sigctrl->temp50);
  m_pSig_comm.SetRegs(ADDR51, ADDR51, &sigctrl->temp51);
  m_pSig_comm.SetRegs(ADDR52, ADDR52, &sigctrl->temp52);
  m_pSig_comm.SetRegs(ADDR53, ADDR53, &sigctrl->temp53);
  m_pSig_comm.SetRegs(ADDR54, ADDR54, &sigctrl->temp54);
  m_pSig_comm.SetRegs(ADDR55, ADDR55, &sigctrl->temp55);
  m_pSig_comm.SetRegs(ADDR56, ADDR56, &sigctrl->temp56);

  m_pSig_comm.SetRegs(ADDR59, ADDR59, &sigctrl->tempAutoPhoto);
 int ret = m_pSig_comm.SetRegs(ADDR60, ADDR60, &sigctrl->tempPhotoEndDelayLine);
 qDebug()<<ret;
}

void SignalControlData::SaveData() {
  JSONRECIPE->setParameter(str[0], sigctrl->temp0);
  JSONRECIPE->setParameter(str[1], sigctrl->temp1);
  JSONRECIPE->setParameter(str[2], sigctrl->temp2);
  JSONRECIPE->setParameter(str[3], sigctrl->temp3);
  JSONRECIPE->setParameter(str[4], sigctrl->temp4);
  JSONRECIPE->setParameter(str[5], sigctrl->temp5);
  JSONRECIPE->setParameter(str[6], sigctrl->temp6);
  JSONRECIPE->setParameter(str[7], sigctrl->temp7);
  JSONRECIPE->setParameter(str[8], sigctrl->temp8);
  JSONRECIPE->setParameter(str[9], sigctrl->temp9);
  JSONRECIPE->setParameter(str[10], sigctrl->temp10);
  JSONRECIPE->setParameter(str[11], sigctrl->temp11);
  JSONRECIPE->setParameter(str[12], sigctrl->temp12);
  JSONRECIPE->setParameter(str[13], sigctrl->temp13);

  JSONRECIPE->setParameter(str[14], sigctrl->temp14);
  JSONRECIPE->setParameter(str[15], sigctrl->temp15);
  JSONRECIPE->setParameter(str[16], sigctrl->temp16);
  JSONRECIPE->setParameter(str[17], sigctrl->temp17);
  JSONRECIPE->setParameter(str[18], sigctrl->temp18);
  JSONRECIPE->setParameter(str[19], sigctrl->temp19);
  JSONRECIPE->setParameter(str[20], sigctrl->temp20);
  JSONRECIPE->setParameter(str[21], sigctrl->temp21);
  JSONRECIPE->setParameter(str[22], sigctrl->temp22);

  JSONRECIPE->setParameter(str[23], sigctrl->temp23);
  JSONRECIPE->setParameter(str[24], sigctrl->temp24);
  JSONRECIPE->setParameter(str[25], sigctrl->temp25);
  JSONRECIPE->setParameter(str[26], sigctrl->temp26);
  JSONRECIPE->setParameter(str[27], sigctrl->temp27);
  JSONRECIPE->setParameter(str[28], sigctrl->temp28);
  JSONRECIPE->setParameter(str[29], sigctrl->temp29);
  JSONRECIPE->setParameter(str[30], sigctrl->temp30);
  JSONRECIPE->setParameter(str[31], sigctrl->temp31);
  JSONRECIPE->setParameter(str[32], sigctrl->temp32);
  JSONRECIPE->setParameter(str[33], sigctrl->temp33);
  JSONRECIPE->setParameter(str[34], sigctrl->temp34);
  JSONRECIPE->setParameter(str[35], sigctrl->temp35);
  JSONRECIPE->setParameter(str[36], sigctrl->temp36);
  JSONRECIPE->setParameter(str[37], sigctrl->temp37);



  JSONRECIPE->setParameter(str[43], sigctrl->temp43);
  JSONRECIPE->setParameter(str[44], sigctrl->temp44);
  JSONRECIPE->setParameter(str[45], sigctrl->temp45);
  JSONRECIPE->setParameter(str[46], sigctrl->temp46);
  JSONRECIPE->setParameter(str[47], sigctrl->temp47);
  JSONRECIPE->setParameter(str[48], sigctrl->temp48);
  JSONRECIPE->setParameter(str[49], sigctrl->temp49);
  JSONRECIPE->setParameter(str[50], sigctrl->temp50);
  JSONRECIPE->setParameter(str[51], sigctrl->temp51);
  JSONRECIPE->setParameter(str[52], sigctrl->temp52);
  JSONRECIPE->setParameter(str[53], sigctrl->temp53);
  JSONRECIPE->setParameter(str[54], sigctrl->temp54);
  JSONRECIPE->setParameter(str[55], sigctrl->temp55);
  JSONRECIPE->setParameter(str[56], sigctrl->temp56);
  JSONRECIPE->setParameter(str[57], sigctrl->tempRollerACount);
  JSONRECIPE->setParameter(str[58], sigctrl->tempRollerBCount);
  JSONRECIPE->setParameter(str[59], sigctrl->tempRollerCofficient);
  JSONRECIPE->setParameter(str[60], sigctrl->tempAutoPhoto);
  JSONRECIPE->setParameter(str[61], sigctrl->tempPhotoEndDelayLine);
  JSONRECIPE->setParameter(str[62], sigctrl->tempRoller4ABCount);
  JSONRECIPE->SaveParamsToFile();
}

void SignalControlData::Trigger() {
  unsigned int temp1 = 0;
  unsigned int temp2 = 1;
  m_pSig_comm.SetRegs(ADDR38, ADDR38, &temp2);
  m_pSig_comm.SetRegs(ADDR38, ADDR38, &temp1);
}


void SignalControlData::TimeOut1() {
    //初始化编码器结束标志信号
    m_pSig_comm.SetRegs(ADDR42, ADDR42, &temp2);
    m_pSig_comm.SetRegs(ADDR42, ADDR42, &temp1);
    unsigned int flag = 0; //上升沿
    while (true) {
          //帧信号
          m_pSig_comm.GetRegs(ADDR40, ADDR40, &aaa);//1表示控制器在控制帧信号，随后为0
          if (aaa > mid1) {
              Global::FrameSignal = 1;
              mid1 = aaa;
          } else {
              mid1 = aaa;
          }
          //分拣信号
          m_pSig_comm.GetRegs(ADDR39, ADDR39, &bbb);
          if (bbb > mid2) {
            emit sig_updateSortGlassSignal();
            mid2 = bbb;
          } else {
            mid2 = bbb;
          }
          //ADDR8编码通道选择
          //ADDR2编码器信号结束标志
          m_pSig_comm.GetRegs(ADDR2, ADDR2, &ccc);

          //ADDR4编码器备用

          if (ccc > mid3) {
            //ADDR3编码器信号1当前值
            m_pSig_comm.GetRegs(ADDR3, ADDR3, &eee);
            Global::CodeCount = eee;
            m_pSig_comm.GetRegs(ADDR4, ADDR4, &fff);
            Global::CodeLineCount = fff;
            m_pSig_comm.GetRegs(ADDR5, ADDR5, &fff);
            Global::Code4Count = fff;
            qDebug()<<"Global::CodeCount"<<Global::CodeCount;
            qDebug()<<"Global::Code4Count"<<Global::Code4Count;
            m_pSig_comm.SetRegs(ADDR42, ADDR42, &temp2);
            m_pSig_comm.SetRegs(ADDR42, ADDR42, &temp1);
            mid3 = ccc;
          } else {
              mid3 = ccc;
          }
          //单位时间内编码器脉冲计数
          m_pSig_comm.GetRegs(ADDR6, ADDR6, &ggg);
          Global::CodePerCount = ggg;

          //报警灯
          if (Global::AlmLightSignal) {
              Global::AlmLightSignal=false;
              uint lightnum=Global::AlmLightVal;
              m_pSig_comm.SetRegs(ADDR41, ADDR41, &lightnum);
          }

          if(StopFlag_sig)
              break;

          //差分编码器压轮编码值
          unsigned int codecount1 = 0; //脉冲编码值
          unsigned int codecount2 = 0; //脉冲编码值
          unsigned int endSignal = 0; //结束信号，玻璃结束的时候为0
          unsigned int codecountAB4 = 0; //压轮编码器4倍频
          m_pSig_comm.GetRegs(ADDR61, ADDR61, &endSignal);//玻璃检测结束
          if ( flag == 0 &&  endSignal == 1) {//1
              m_pSig_comm.GetRegs(ADDR57, ADDR57, &codecount1);
              m_pSig_comm.GetRegs(ADDR58, ADDR58, &codecount2);
              m_pSig_comm.GetRegs(ADDR62, ADDR62, &codecountAB4);
              Global::encodeARollerCount = codecount1;
              Global::encodeBRollerCount = codecount2;
              Global::encodeRollerCount = (codecount1 + codecount2)/2;
              Global::encodeAB4 = codecountAB4;
          }
          flag = endSignal;
  }
}

void SignalControlData::slot_DeliverLightData()
{
    emit sig_RecipeChage();
}


#include "SignalControlData.h"
#pragma execution_character_set("utf-8")

SignalControlData::SignalControlData(RegParasComm& sig_comm):
    m_pSig_comm(sig_comm)
{
    sigctrl = new SignalControl();
    mid1 = 0;
    mid2 = 0;
    mid3 = 0;
    StopFlag_sig = false;
    FrameSignal = 0;
    CodeCount = 0;
}

SignalControlData::~SignalControlData() {}

void SignalControlData::InitData()
{
    //todo: 读取工单json文件
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

void SignalControlData::GetData()
{
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

void SignalControlData::SetData()
{
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

void SignalControlData::SaveData()
{
    //todo:读取数据，从ui或者结构体里面读取，写入json文件中
}

void SignalControlData::Trigger()
{
    unsigned int temp1 = 0;
    unsigned int temp2 = 1;
    m_pSig_comm.SetRegs(ADDR38, ADDR38, &temp2);
    m_pSig_comm.SetRegs(ADDR38, ADDR38, &temp1);
}

//todo:什么时候启动线程
void SignalControlData::TimeOut1()
{
    //初始化编码器结束标志信号，测试Y反向长度
    m_pSig_comm.SetRegs(ADDR42, ADDR42, &temp2);
    m_pSig_comm.SetRegs(ADDR42, ADDR42, &temp1);
    unsigned int flag = 0; //上升沿
    while (true) {
          //帧信号
          m_pSig_comm.GetRegs(ADDR40, ADDR40, &aaa);//1表示控制器在控制帧信号，随后为0
          if (aaa > mid1) {
              FrameSignal = 1;
              mid1 = aaa;
          } else {
              mid1 = aaa;
          }
          //分拣信号（暂未用到）
          m_pSig_comm.GetRegs(ADDR39, ADDR39, &bbb);
          if (bbb > mid2) {
            emit sig_updateSortGlassSignal();
            mid2 = bbb;
          } else {
            mid2 = bbb;
          }
          //ADDR8编码通道选择
          //ADDR2编码器信号结束标志,光电
          m_pSig_comm.GetRegs(ADDR2, ADDR2, &ccc);

          //ADDR4编码器备用

          if (ccc > mid3) {
            //ADDR3编码器信号1当前值
            m_pSig_comm.GetRegs(ADDR3, ADDR3, &eee);
            CodeCount = eee;
            m_pSig_comm.GetRegs(ADDR4, ADDR4, &fff);
            CodeLineCount = fff;
            m_pSig_comm.GetRegs(ADDR5, ADDR5, &fff);
            Code4Count = fff;
            m_pSig_comm.SetRegs(ADDR42, ADDR42, &temp2);
            m_pSig_comm.SetRegs(ADDR42, ADDR42, &temp1);
            mid3 = ccc;
          } else {
              mid3 = ccc;
          }
          //单位时间内编码器脉冲计数（暂未用到），单位时间内是否速度是否均匀
          m_pSig_comm.GetRegs(ADDR6, ADDR6, &ggg);
          CodePerCount = ggg;

          //报警灯
          if (AlmLightSignal ==  true) {
              AlmLightSignal = false;
              uint lightnum = AlmLightSignal;
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
              encodeARollerCount = codecount1;
              encodeBRollerCount = codecount2;
              encodeRollerCount = (codecount1 + codecount2)/2;//去AB的平均值
              encodeAB4 = codecountAB4;
          }
          flag = endSignal;
  }
}

void SignalControlData::slot_DeliverLightData()
{
    emit sig_RecipeChage();
}


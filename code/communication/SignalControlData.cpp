#include "SignalControlData.h"
#pragma execution_character_set("utf-8")

void SignalControlData::InitRegs(QString ip, int port)
{
    // 连接到服务器
    m_pSig_comm.ConnectToServer(ip,port);
}

void SignalControlData::Trigger()
{
    unsigned int temp1 = 0;
    unsigned int temp2 = 1;
    m_pSig_comm.SetRegs(ADDR38, ADDR38, &temp2);
    m_pSig_comm.SetRegs(ADDR38, ADDR38, &temp1);
}

void SignalControlData::SetAllRegs(SignalControl data)
{
    m_pSig_comm.SetRegs(ADDR0, ADDR0, &data.temp0);
    m_pSig_comm.SetRegs(ADDR1, ADDR1, &data.temp1);
    m_pSig_comm.SetRegs(ADDR7, ADDR7, &data.temp7);
    m_pSig_comm.SetRegs(ADDR8, ADDR8, &data.temp8);
    m_pSig_comm.SetRegs(ADDR9, ADDR9, &data.temp9);
    m_pSig_comm.SetRegs(ADDR10, ADDR10, &data.temp10);
    m_pSig_comm.SetRegs(ADDR11, ADDR11, &data.temp11);
    m_pSig_comm.SetRegs(ADDR12, ADDR12, &data.temp12);

    m_pSig_comm.SetRegs(ADDR14, ADDR14, &data.temp14);
    m_pSig_comm.SetRegs(ADDR15, ADDR15, &data.temp15);
    m_pSig_comm.SetRegs(ADDR16, ADDR16, &data.temp16);
    m_pSig_comm.SetRegs(ADDR17, ADDR17, &data.temp17);
    m_pSig_comm.SetRegs(ADDR18, ADDR18, &data.temp18);
    m_pSig_comm.SetRegs(ADDR19, ADDR19, &data.temp19);
    m_pSig_comm.SetRegs(ADDR20, ADDR20, &data.temp20);
    m_pSig_comm.SetRegs(ADDR21, ADDR21, &data.temp21);
    m_pSig_comm.SetRegs(ADDR22, ADDR22, &data.temp22);

    m_pSig_comm.SetRegs(ADDR23, ADDR23, &data.temp23);
    m_pSig_comm.SetRegs(ADDR24, ADDR24, &data.temp24);
    m_pSig_comm.SetRegs(ADDR25, ADDR25, &data.temp25);
    m_pSig_comm.SetRegs(ADDR26, ADDR26, &data.temp26);
    m_pSig_comm.SetRegs(ADDR27, ADDR27, &data.temp27);
    m_pSig_comm.SetRegs(ADDR28, ADDR28, &data.temp28);
    m_pSig_comm.SetRegs(ADDR29, ADDR29, &data.temp29);
    m_pSig_comm.SetRegs(ADDR30, ADDR30, &data.temp30);
    m_pSig_comm.SetRegs(ADDR31, ADDR31, &data.temp31);
    m_pSig_comm.SetRegs(ADDR32, ADDR32, &data.temp32);
    m_pSig_comm.SetRegs(ADDR33, ADDR33, &data.temp33);
    m_pSig_comm.SetRegs(ADDR34, ADDR34, &data.temp34);
    m_pSig_comm.SetRegs(ADDR35, ADDR35, &data.temp35);
    m_pSig_comm.SetRegs(ADDR36, ADDR36, &data.temp36);
    m_pSig_comm.SetRegs(ADDR37, ADDR37, &data.temp37);

    m_pSig_comm.SetRegs(ADDR43, ADDR43, &data.temp43);
    m_pSig_comm.SetRegs(ADDR44, ADDR44, &data.temp44);
    m_pSig_comm.SetRegs(ADDR45, ADDR45, &data.temp45);
    m_pSig_comm.SetRegs(ADDR46, ADDR46, &data.temp46);
    m_pSig_comm.SetRegs(ADDR47, ADDR47, &data.temp47);
    m_pSig_comm.SetRegs(ADDR48, ADDR48, &data.temp48);
    m_pSig_comm.SetRegs(ADDR49, ADDR49, &data.temp49);
    m_pSig_comm.SetRegs(ADDR50, ADDR50, &data.temp50);
    m_pSig_comm.SetRegs(ADDR51, ADDR51, &data.temp51);
    m_pSig_comm.SetRegs(ADDR52, ADDR52, &data.temp52);
    m_pSig_comm.SetRegs(ADDR53, ADDR53, &data.temp53);
    m_pSig_comm.SetRegs(ADDR54, ADDR54, &data.temp54);
    m_pSig_comm.SetRegs(ADDR55, ADDR55, &data.temp55);
    m_pSig_comm.SetRegs(ADDR56, ADDR56, &data.temp56);

    m_pSig_comm.SetRegs(ADDR59, ADDR59, &data.tempAutoPhoto);
    m_pSig_comm.SetRegs(ADDR60, ADDR60, &data.tempPhotoEndDelayLine);
}

void SignalControlData::SetReg(unsigned short addr_s,
                               unsigned short addr_e,
                               unsigned int data)
{
    m_pSig_comm.SetRegs(addr_s,addr_e,&data);
}

void SignalControlData::GetRealTimeData(unsigned int& FrameSignal, unsigned int& AlmLightSignal)
{
    //帧信号
    m_pSig_comm.GetRegs(ADDR40, ADDR40, &FrameSignal);//1表示控制器在控制帧信号，随后为0

    //报警灯
    if (AlmLightSignal ==  true) {
          AlmLightSignal = false;
          uint lightnum = AlmLightSignal;
          m_pSig_comm.SetRegs(ADDR41, ADDR41, &lightnum);
    }
}

void SignalControlData::GetAllData(SignalControl& data)
{
    m_pSig_comm.GetRegs(ADDR0, ADDR0, &data.temp0);
    m_pSig_comm.GetRegs(ADDR1, ADDR1, &data.temp1);
    m_pSig_comm.GetRegs(ADDR2, ADDR2, &data.temp2);
    m_pSig_comm.GetRegs(ADDR3, ADDR3, &data.temp3);
    m_pSig_comm.GetRegs(ADDR4, ADDR4, &data.temp4);
    m_pSig_comm.GetRegs(ADDR5, ADDR5, &data.temp5);
    m_pSig_comm.GetRegs(ADDR6, ADDR6, &data.temp6);
    m_pSig_comm.GetRegs(ADDR7, ADDR7, &data.temp7);
    m_pSig_comm.GetRegs(ADDR8, ADDR8, &data.temp8);
    m_pSig_comm.GetRegs(ADDR9, ADDR9, &data.temp9);
    m_pSig_comm.GetRegs(ADDR10, ADDR10, &data.temp10);
    m_pSig_comm.GetRegs(ADDR11, ADDR11, &data.temp11);
    m_pSig_comm.GetRegs(ADDR12, ADDR12, &data.temp12);
    m_pSig_comm.GetRegs(ADDR13, ADDR13, &data.temp13);

    m_pSig_comm.GetRegs(ADDR14, ADDR14, &data.temp14);
    m_pSig_comm.GetRegs(ADDR15, ADDR15, &data.temp15);
    m_pSig_comm.GetRegs(ADDR16, ADDR16, &data.temp16);
    m_pSig_comm.GetRegs(ADDR17, ADDR17, &data.temp17);
    m_pSig_comm.GetRegs(ADDR19, ADDR19, &data.temp19);
    m_pSig_comm.GetRegs(ADDR20, ADDR20, &data.temp20);
    m_pSig_comm.GetRegs(ADDR21, ADDR21, &data.temp21);
    m_pSig_comm.GetRegs(ADDR22, ADDR22, &data.temp22);

    m_pSig_comm.GetRegs(ADDR23, ADDR23, &data.temp23);
    m_pSig_comm.GetRegs(ADDR24, ADDR24, &data.temp24);
    m_pSig_comm.GetRegs(ADDR25, ADDR25, &data.temp25);
    m_pSig_comm.GetRegs(ADDR26, ADDR26, &data.temp26);
    m_pSig_comm.GetRegs(ADDR27, ADDR27, &data.temp27);
    m_pSig_comm.GetRegs(ADDR28, ADDR28, &data.temp28);
    m_pSig_comm.GetRegs(ADDR29, ADDR29, &data.temp29);
    m_pSig_comm.GetRegs(ADDR30, ADDR30, &data.temp30);
    m_pSig_comm.GetRegs(ADDR31, ADDR31, &data.temp31);
    m_pSig_comm.GetRegs(ADDR32, ADDR32, &data.temp32);
    m_pSig_comm.GetRegs(ADDR33, ADDR33, &data.temp33);
    m_pSig_comm.GetRegs(ADDR34, ADDR34, &data.temp34);
    m_pSig_comm.GetRegs(ADDR35, ADDR35, &data.temp35);
    m_pSig_comm.GetRegs(ADDR36, ADDR36, &data.temp36);
    m_pSig_comm.GetRegs(ADDR37, ADDR37, &data.temp37);

    m_pSig_comm.GetRegs(ADDR43, ADDR43, &data.temp43);
    m_pSig_comm.GetRegs(ADDR44, ADDR44, &data.temp44);
    m_pSig_comm.GetRegs(ADDR45, ADDR45, &data.temp45);
    m_pSig_comm.GetRegs(ADDR46, ADDR46, &data.temp46);
    m_pSig_comm.GetRegs(ADDR47, ADDR47, &data.temp47);
    m_pSig_comm.GetRegs(ADDR48, ADDR48, &data.temp48);
    m_pSig_comm.GetRegs(ADDR49, ADDR49, &data.temp49);
    m_pSig_comm.GetRegs(ADDR50, ADDR50, &data.temp50);
    m_pSig_comm.GetRegs(ADDR51, ADDR51, &data.temp51);
    m_pSig_comm.GetRegs(ADDR52, ADDR52, &data.temp52);
    m_pSig_comm.GetRegs(ADDR53, ADDR53, &data.temp53);
    m_pSig_comm.GetRegs(ADDR54, ADDR54, &data.temp54);
    m_pSig_comm.GetRegs(ADDR55, ADDR55, &data.temp55);
    m_pSig_comm.GetRegs(ADDR56, ADDR56, &data.temp56);

    m_pSig_comm.GetRegs(ADDR59, ADDR59, &data.tempAutoPhoto);
    m_pSig_comm.GetRegs(ADDR60, ADDR60, &data.tempPhotoEndDelayLine);
}

bool SignalControlData::TestIPConnect()
{
    return m_pSig_comm.IsOpen();
}



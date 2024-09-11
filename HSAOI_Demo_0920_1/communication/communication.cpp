#include "communication.h"
#include <QFile>

Communication::Communication()
    : regcomPtr(nullptr)
    , SigCtrlData(nullptr)
{
    regcomPtr = std::make_shared<RegParasComm>();
    SigCtrlData = std::make_shared<SignalControlData>(*regcomPtr);
    sigctrl = std::make_shared<SignalControl>();
}

void Communication::InitConnect(QString IP,int port)
{
//    qDebug() << "链接：" << IP << ":" << port;
    regcomPtr->ConnectToServer(IP,port);
}

void Communication::SetFunction()
{
    //todo:只将数据变化的值写入寄存器
    regcomPtr->SetRegs(ADDR0, ADDR0, &sigctrl->temp0);
    regcomPtr->SetRegs(ADDR1, ADDR1, &sigctrl->temp1);
    regcomPtr->SetRegs(ADDR7, ADDR7, &sigctrl->temp7);
    regcomPtr->SetRegs(ADDR8, ADDR8, &sigctrl->temp8);
    regcomPtr->SetRegs(ADDR9, ADDR9, &sigctrl->temp9);
    regcomPtr->SetRegs(ADDR10, ADDR10, &sigctrl->temp10);
    regcomPtr->SetRegs(ADDR11, ADDR11, &sigctrl->temp11);
    regcomPtr->SetRegs(ADDR12, ADDR12, &sigctrl->temp12);
    regcomPtr->SetRegs(ADDR14, ADDR14, &sigctrl->temp14);
    regcomPtr->SetRegs(ADDR15, ADDR15, &sigctrl->temp15);
    regcomPtr->SetRegs(ADDR16, ADDR16, &sigctrl->temp16);
    regcomPtr->SetRegs(ADDR17, ADDR17, &sigctrl->temp17);
    regcomPtr->SetRegs(ADDR18, ADDR18, &sigctrl->temp18);
    regcomPtr->SetRegs(ADDR19, ADDR19, &sigctrl->temp19);
    regcomPtr->SetRegs(ADDR20, ADDR20, &sigctrl->temp20);
    regcomPtr->SetRegs(ADDR21, ADDR21, &sigctrl->temp21);
    regcomPtr->SetRegs(ADDR22, ADDR22, &sigctrl->temp22);
    regcomPtr->SetRegs(ADDR23, ADDR23, &sigctrl->temp23);
    regcomPtr->SetRegs(ADDR24, ADDR24, &sigctrl->temp24);
    regcomPtr->SetRegs(ADDR25, ADDR25, &sigctrl->temp25);
    regcomPtr->SetRegs(ADDR26, ADDR26, &sigctrl->temp26);
    regcomPtr->SetRegs(ADDR27, ADDR27, &sigctrl->temp27);
    regcomPtr->SetRegs(ADDR28, ADDR28, &sigctrl->temp28);
    regcomPtr->SetRegs(ADDR29, ADDR29, &sigctrl->temp29);
    regcomPtr->SetRegs(ADDR30, ADDR30, &sigctrl->temp30);
    regcomPtr->SetRegs(ADDR31, ADDR31, &sigctrl->temp31);
    regcomPtr->SetRegs(ADDR32, ADDR32, &sigctrl->temp32);
    regcomPtr->SetRegs(ADDR33, ADDR33, &sigctrl->temp33);
    regcomPtr->SetRegs(ADDR34, ADDR34, &sigctrl->temp34);
    regcomPtr->SetRegs(ADDR35, ADDR35, &sigctrl->temp35);
    regcomPtr->SetRegs(ADDR36, ADDR36, &sigctrl->temp36);
    regcomPtr->SetRegs(ADDR37, ADDR37, &sigctrl->temp37);
    regcomPtr->SetRegs(ADDR43, ADDR43, &sigctrl->temp43);
    regcomPtr->SetRegs(ADDR44, ADDR44, &sigctrl->temp44);
    regcomPtr->SetRegs(ADDR45, ADDR45, &sigctrl->temp45);
    regcomPtr->SetRegs(ADDR46, ADDR46, &sigctrl->temp46);
    regcomPtr->SetRegs(ADDR47, ADDR47, &sigctrl->temp47);
    regcomPtr->SetRegs(ADDR48, ADDR48, &sigctrl->temp48);
    regcomPtr->SetRegs(ADDR49, ADDR49, &sigctrl->temp49);
    regcomPtr->SetRegs(ADDR50, ADDR50, &sigctrl->temp50);
    regcomPtr->SetRegs(ADDR51, ADDR51, &sigctrl->temp51);
    regcomPtr->SetRegs(ADDR52, ADDR52, &sigctrl->temp52);
    regcomPtr->SetRegs(ADDR53, ADDR53, &sigctrl->temp53);
    regcomPtr->SetRegs(ADDR54, ADDR54, &sigctrl->temp54);
    regcomPtr->SetRegs(ADDR55, ADDR55, &sigctrl->temp55);
    regcomPtr->SetRegs(ADDR56, ADDR56, &sigctrl->temp56);
    regcomPtr->SetRegs(ADDR59, ADDR59, &sigctrl->tempAutoPhoto);
    int ret = regcomPtr->SetRegs(ADDR60, ADDR60, &sigctrl->tempPhotoEndDelayLine);
    qDebug()<<ret;
}

void Communication::SaveFunction(const QString recipeFullpath, const SignalControl& data)
{
//    Jsoncpp::GetInstance()->writeComDataToJson(recipeFullpath,data);

}

void Communication::NewRecipeFunction(const QString recipeFullpath, QString newRecipeFullpath)
{
    //todo:将当前的json工单复制一份，切换到当前的工单
    if(newRecipeFullpath != recipeFullpath) {
        // 源 JSON 文件路径
        QString sourceFilePath = recipeFullpath;
        // 目标 JSON 文件路径
        QString destinationFilePath = newRecipeFullpath;
        QFile sourceFile(sourceFilePath);
        QFile destinationFile(destinationFilePath);

        if (sourceFile.open(QIODevice::ReadOnly)) {
            if (destinationFile.open(QIODevice::WriteOnly)) {
                destinationFile.write(sourceFile.readAll());
                destinationFile.close();
            } else {
                qDebug() << "Failed to open destination file for writing.";
            }
            sourceFile.close();
        } else {
            qDebug() << "Failed to open source file for reading.";
        }
    }

}

bool Communication::TestConnect()
{
    return regcomPtr->IsOpen();
}

void Communication::DebugTriger()
{
    //内部产生光电信号(写1再写0)
    unsigned int endInnerSignal = 0;
    unsigned int startInnerSignal = 1;
    regcomPtr->SetRegs(ADDR38, ADDR38, &startInnerSignal);
    regcomPtr->SetRegs(ADDR38, ADDR38, &endInnerSignal);
}

void Communication::ChangeRecipe(QString recipeFullPath)
{
    //todo:读取recipeFullPath的json文件内容，初始化json文件
}



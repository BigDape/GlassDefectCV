#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "communication_global.h"
#include "RegParasComm.h"
#include "SignalControlData.h"

class COMMUNICATION_EXPORT Communication
{
public:
    Communication();
    void InitConnect(QString IP,int port);

    void SetFunction();//设置按钮
    void SaveFunction(const QString recipeFullpath, const SignalControl& data);//保存按钮
    void NewRecipeFunction(const QString recipeFullpath, QString newRecipeFullpath);//新建工单
    bool TestConnect(); //测试连接
    void DebugTriger(); //触发
    void ChangeRecipe(QString recipeFullPath); //切换工单

private:
    std::shared_ptr<RegParasComm> regcomPtr;
    std::shared_ptr<SignalControlData> SigCtrlData;
    std::shared_ptr<SignalControl> sigctrl;
};

#endif // COMMUNICATION_H

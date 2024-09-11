#include "Global.h"
#include "log_singleton.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#pragma execution_character_set("utf-8")

GlobalParamter::GlobalParamter()
    :IsScanned(false),
     FramesPerTri(0),
     ImageHeight(0),
     ImageWidth(0),
     CurrentRecipe(""),
     SystemName(""),
     Camera0Name(""),
     Camera1Name(""),
     Camera2Name(""),
     Camera3Name(""),
     serverIp(""),
     RegParaPort(0),
     FrameSignal(0),
     CodeCount(0),
     CodeLineCount(0),
     Code4Count(0),
     CodePerCount(0),
     CamRows(0),
     CamRowsPerField(0),
     RecChangeSignal(false),
     AlmLightSignal(false),
     AlmLightVal(0),
     FieldNumberSet(0),
     camDefineNum(0),
     GlassID_INT(0),
     encodeRollerCount(0),
     encodeARollerCount(0),
     encodeBRollerCount(0),
     encodeRollerCofficient(0),
     RollerAngle(0),
     encodeRollerYLength(0),
     m_plot(nullptr),
     isOffline(false),
     offlineFullPath(""),
     isJpg(false),
     encodeAB4(0)
{
    camName<<"Camera0"<<"Camera1"<<"Camera2"<<"Camera3";
    QString CurrentRecipeNameLog = "获得当前工单: " + CurrentRecipe;
    QString SystemNameLog = "获得当前项目名: " + SystemName;
    log_singleton::Write_Log(CurrentRecipeNameLog, Log_Level::General);
    log_singleton::Write_Log(SystemNameLog, Log_Level::General);
}

GlobalParamter::~GlobalParamter(){}

GlobalParamter& GlobalParamter::getInstance()
{
    static GlobalParamter param;
    return param;
}

QString GlobalParamter::GetParamterFromIniFile(QString fullpath, QString key)
{
    QString result;
    std::ifstream configFile(fullpath.toStdString());
    std::string line;
    std::map<std::string, std::string> config;
    assert(configFile.is_open());

    while (getline(configFile, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (getline(is_line, key, '=')) {
            std::string value;
            if (getline(is_line, value)) {
                config[key] = value;
            }
        }
    }

    configFile.close();
    // 打印读取的配置
    for (const auto& pair : config) {
        //std::cout << pair.first << " = " << pair.second << std::endl;
        if (pair.first == key.toStdString()) {
          result = pair.second.data();
        }
    }
    return result;
}

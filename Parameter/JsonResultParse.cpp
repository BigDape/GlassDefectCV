#include "JsonResultParse.h"
#include <QDateTime>
#include <QDir>
#include<Global.h>

#pragma execution_character_set("utf-8")

JsonResultParse::JsonResultParse()
{
  ini_JsonResult();
}
JsonResultParse::~JsonResultParse()
{

}
void JsonResultParse::ini_JsonResult()
{
    //缺陷信息读取
    jsonObj = QJsonObject();
    // 判断文件是否存在
    // 获取当前时间
    QDateTime currentDateTime = QDateTime::currentDateTime();
    // 根据当前时间构建文件名
    QString fileName = currentDateTime.toString("yyyy-MM-dd HH") + ".json";
    // 获取当前项目文件夹路径
    QString projectFolder = QDir::currentPath();
    // 拼接文件夹路径和文件名
    QString filePath = projectFolder + "/DefectInfJson/" + fileName;
    QFile file(filePath);
    if (file.exists()) {
        // Read the existing JSON file
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        QString fileContent = in.readAll();
        file.close();
        // Parse the JSON content
        jsonDoc = QJsonDocument::fromJson(fileContent.toUtf8());
        jsonObj = jsonDoc.object();
    } else {
        // Create a new file
        if (file.open(QIODevice::ReadWrite)) {
            // Create a JSON object and insert a key-value pair
            qDebug() << "New file with the key-value pair is created.";
        } else {
            qDebug() << "Failed to create the file";
        }
    }

    //丝印孔信息读取
    jsonObjSK = QJsonObject();
    // 文件夹路径和文件名
    QString filePathSK = projectFolder + "/HolesInfJson/" + fileName;
    QFile fileSK(filePathSK);
    if (fileSK.exists()) {
        //     qDebug() << "File" << fileName << "exists in project folder.";
        // Read the existing JSON file
        fileSK.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&fileSK);
        QString fileContentSK = in.readAll();
        fileSK.close();
        // Parse the JSON content
        jsonDocSK = QJsonDocument::fromJson(fileContentSK.toUtf8());
        jsonObjSK = jsonDocSK.object();
    } else {
        // Create a new file
        if (fileSK.open(QIODevice::ReadWrite)) {
            // Create a JSON object and insert a key-value pair
            qDebug() << "New file with the key-value pair is created.";
        } else {
            qDebug() << "Failed to create the file";
        }
    }

}

QString JsonResultParse::InterParasToQJson(DetectResult ResultData,
                                           int DefectStartCount,
                                           int DefectCount,
                                           int ProcessStep,
                                           int HolesCount,
                                           bool isDefect)
{
    quint64 GlassID_INT = PARAM.getGlassID_INT();
    // 获取当前时间
    QDateTime currentDateTime = QDateTime::currentDateTime();
    // 根据当前时间构建文件名
    QString fileName = currentDateTime.toString("yyyy-MM-dd HH") + ".json";
    // 获取当前项目文件夹路径
    QString projectFolder = QDir::currentPath();
    if(isDefect)
    {
        // 文件夹路径和文件名
        QString filePath = projectFolder + "/DefectInfJson/" + fileName;
        QFile file(filePath);
        if (file.exists()) {
            //     qDebug() << "File" << fileName << "exists in project folder.";
        } else {
            jsonObj = QJsonObject();
            // Create a new file
            if (file.open(QIODevice::ReadWrite)) {
                // Create a JSON object and insert a key-value pair
                qDebug() << "New file with the key-value pair is created.";
            } else {
                qDebug() << "Failed to create the file";
            }
        }
        // const QJsonValue lastValue = it.value();
        // Insert a new key-value pair

        if (jsonObj.isEmpty()) {
            // 键值为空
            GlassID_INT = 0;
        } else {
            // 键值不为空
            auto it = jsonObj.constEnd();
            --it; // 移动到最后一个键值对
            QString key = it.key().trimmed();
            GlassID_INT = key.toUInt();
        }
        if (ProcessStep==1 || ProcessStep==0)
        {
            GlassID_INT++;
            nestedData = QJsonObject();


            qDebug() << "nestedData" <<nestedData.count();

        }
        PARAM.setGlassID_INT(GlassID_INT);
    //    int jsonlengthFirst=jsonObj.length();
    //    QStringList jsonlist1=jsonObj.keys();
    //    QString currentjsonkey=jsonlist1[jsonlengthFirst-1];
    //    QJsonObject nestedData=jsonObj[currentjsonkey].toObject();
        for (int i = 0; i < DefectCount; i++) {
            QJsonObject thirdData = QJsonObject();
            thirdData["Time"] = ResultData.Time;
            int j=DefectStartCount+i;
            thirdData["DefectID"] = ResultData.DefectID.at(j);
            thirdData["DefectType"] = ResultData.DefectType.at(j);
            thirdData["DetectLeve"] = ResultData.DefectLeve.at(j);
            thirdData["X"] = ResultData.X.at(j);
            thirdData["Y"] = ResultData.Y.at(j);
            thirdData["Lenth"] = ResultData.Lenth.at(j);
            thirdData["Width"] = ResultData.Width.at(j);
            thirdData["Area"] = ResultData.Area.at(j);
            thirdData["ImageNGPath"] = ResultData.ImageNGPath.at(j);

            // 在 JSON 对象中插入二级键值对数据
            nestedData[ResultData.DefectID.at(j)] = thirdData;            
        }
        if(ProcessStep==0 || ProcessStep==3)
        {
            nestedData["GlassWidth"]    = ResultData.GlassWidth;
            nestedData["GlassLength"]   = ResultData.GlassLength;
            nestedData["GlassAngle"]    = ResultData.GlassAngle;
        }


        ResultData.GlassID = QString::number(GlassID_INT).rightJustified(6, '0');
        jsonObj[ResultData.GlassID] = nestedData;
    //    jsonObj.insert(ResultData.GlassID, nestedData);

        qDebug() << "GlassID" << ResultData.GlassID;
        jsonDoc = QJsonDocument(jsonObj);
        QString jsonString = jsonDoc.toJson();

        // Write the updated JSON back to the file
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << jsonString;
       // qDebug() << "jsonString:"<<jsonString;
        file.close();
    }


    if(!isDefect)
    {
    // 文件夹路径和文件名
    QString filePath = projectFolder + "/HolesInfJson/" + fileName;
    QFile file(filePath);
    if (file.exists()) {
        //     qDebug() << "File" << fileName << "exists in project folder.";
    } else {
        jsonObjSK.empty();
        // Create a new file
        if (file.open(QIODevice::ReadWrite)) {
            // Create a JSON object and insert a key-value pair
            qDebug() << "New file with the key-value pair is created.";
        } else {
            qDebug() << "Failed to create the file";
        }
    }

        QJsonObject nestedDataSK = QJsonObject();
        nestedDataSK["GlassLength"] = ResultData.GlassLength;
        nestedDataSK["GlassWidth"] = ResultData.GlassWidth;
        nestedDataSK["GlassAngle"] = ResultData.GlassAngle;
        nestedDataSK["ImageHolesLinePath"] = ResultData.ImageHolesLinePath;

        for (int i = 0; i < HolesCount; i++) {
            QJsonObject thirdDataSK = QJsonObject();
            thirdDataSK["Time"] = ResultData.Time;
            thirdDataSK["HolesID"] = ResultData.HolesID.at(i);
            thirdDataSK["Type"] = ResultData.Type.at(i);
            thirdDataSK["HolesLeve"] = ResultData.HolesLeve.at(i);
            thirdDataSK["DistanceHorizontal"] = ResultData.DistanceHorizontal.at(i);
            thirdDataSK["DistanceVertical"] = ResultData.DistanceVertical.at(i);
            thirdDataSK["HolesWidth"] = ResultData.HolesWidth.at(i);
            thirdDataSK["HolesHeight"] = ResultData.HolesHeight.at(i);
            thirdDataSK["ImageHolesPath"] = ResultData.ImageHolesPath.at(i);

            // 在 JSON 对象中插入二级键值对数据
            nestedDataSK[ResultData.HolesID.at(i)] = thirdDataSK;
        }
        ResultData.GlassID = QString::number(GlassID_INT).rightJustified(6, '0');
        //  jsonObj[ResultData.GlassID] = nestedData;
        jsonObjSK.insert(ResultData.GlassID, nestedDataSK);
        qDebug() << "GlassID" << ResultData.GlassID;
        jsonDocSK = QJsonDocument(jsonObjSK);
        QString jsonStringSK = jsonDocSK.toJson();

        // Write the updated JSON back to the file
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << jsonStringSK;
        file.close();
    }
//    QString info="玻璃ID" + ResultData.GlassID + "缺陷信息写入json完成！";
//    log_singleton::Write_Log(info, Log_Level::General);
    return ResultData.GlassID;
}

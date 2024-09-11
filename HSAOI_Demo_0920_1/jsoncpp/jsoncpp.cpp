#include "jsoncpp.h"
#include <QFile>
#include <fstream>
#include <stdlib.h>
#include <QString>
#include <fstream>
#include <QTextStream>
#include <iostream>
#include <fstream>
#include <QDebug>

Jsoncpp::Jsoncpp()
{
}

Jsoncpp* Jsoncpp::GetInstance()
{
    static Jsoncpp instance;
    return (&instance);
}

void Jsoncpp::getFlawImageFromJson(QString jsonFileName,
                                   int GlassID,
                                   int defectid,
                                   QString& ImagePath1,
                                   QString& ImagePath2,
                                   QString& ImagePath3)
{
    Json::Value root;
    QFile file(jsonFileName);
    if (file.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFileName.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
            Json::Reader reader;
            // 解析到root，root将包含Json里所有子元素
            reader.parse(ifs, root, false);
            ifs.close();
        } else {
            qCritical()<<__FUNCTION__<<" ifs.is_open() =  false";
        }
    } else {
        qCritical()<<__FUNCTION__<<jsonFileName<<" is not exit.";
    }
    if(!root.empty()) {
        Json::Value glass = root[QString::number(GlassID).toStdString().c_str()];
        Json::Value defect = glass[QString::number(defectid).toStdString().c_str()];
        ImagePath1 = defect["ImageNGPath"].asString().data() + QString("/1.jpg");
        ImagePath2 = defect["ImageNGPath"].asString().data() + QString("/2.jpg");
        ImagePath3 = defect["ImageNGPath"].asString().data() + QString("/3.jpg");
    } else {
        qWarning()<<"root is empty!";
    }
}

void Jsoncpp::getDefectSFromJson(QString jsonFullPath,
                                 int glassid,
                                 std::vector<DefectData>& Defects)
{
    //
    // 将文件中已有的数据读出来
    //
    Json::Value root;
    QFile file(jsonFullPath);
    qDebug()<<"jsonFullPath="<<jsonFullPath;
    if (file.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFullPath.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
            Json::Reader reader;
            // 解析到root，root将包含Json里所有子元素
            reader.parse(ifs, root, false);
            ifs.close();
        } else {
            qDebug()<<"ifs.is_open() =  false";
        }
    } else {
        qDebug()<<jsonFullPath<<" is not exit.";
    }
    if(!root.empty()) {
        Json::Value glass = root[QString::number(glassid).toStdString().c_str()];
        int count = glass.size() - 3;
        for (int i = 0; i < count; i++) {
            Json::Value defect = glass[QString::number(i).toStdString().c_str()];
            DefectData temp;
            temp.DefectID = defect["DefectID"].asInt();//序号
            temp.Time = defect["Time"].asString().data();//时间
            temp.DefectType = defect["DefectType"].asString().data();//类型
            temp.DetectLeve = defect["DetectLeve"].asString().data();//等级
            temp.X = defect["X"].asDouble();//坐标X
            temp.Y = defect["Y"].asDouble();//坐标Y
            temp.Lenth = defect["Lenth"].asDouble();//长
            temp.Width = defect["Width"].asDouble();//宽
            temp.Area = defect["Area"].asDouble();//区域
            Defects.push_back(temp);
        }
    } else {
        qWarning()<<"root is empty!";
    }
}

void Jsoncpp::readHoleFromJson(QString jsonFullPath, int glassid, QString& ImageHolesLinePath)
{
    //
    // 将文件中已有的数据读出来
    //
    Json::Value root;
    QFile folderDir(jsonFullPath);
    qDebug()<<"jsonFullPath  = "<<jsonFullPath;
    if (folderDir.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFullPath.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<" ifs.is_open() =  false";
        }
    } else {
        qDebug()<<jsonFullPath<<" is not exit.";
    }

    if(!root.empty()) {
        Json::Value holes = root[QString::number(glassid).toStdString().c_str()];
        ImageHolesLinePath = holes["ImageHolesLinePath"].asString().data();
    } else {
        qDebug()<<"ifs.is_open() =  false";
    }
}

void Jsoncpp::readSizeSmallImage(QString jsonFileName, int GlassID, int row, QString& ImageHolesPath)
{
    Json::Value root;
    QFile fileer(jsonFileName);
    if (fileer.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFileName.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<__FUNCTION__<<" ifs.is_open() =  false";
        }
    } else {
        qDebug()<<__FUNCTION__<<jsonFileName<<" is not exit.";
    }

    if(!root.empty()) {
          qDebug()<<__FUNCTION__<<"GlassID ="<<GlassID;
          Json::Value holes = root[QString::number(GlassID).toStdString().c_str()];
          Json::Value hole = holes[QString::number(row).toStdString().c_str()];
          ImageHolesPath = hole["ImageHolesPath"].asString().data() + QString("/") + QString::number(row) + ".jpg";
    }
}

void Jsoncpp::readSizeFromJson(QString jsonFilePath,int glassid,std::vector<SizeData>& result)
{
    //
    // 将文件中已有的数据读出来
    //
    Json::Value root;
    QFile filer(jsonFilePath);
    if (filer.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFilePath.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<" ifs.is_open() =  false";
        }
    } else {
        qDebug()<<jsonFilePath<<" is not exit.";
    }
    if(!root.empty()) {
        Json::Value holes = root[QString::number(glassid).toStdString().c_str()];
        int count = holes.size() - 4; //减去角度、长度、宽度、轮廓图路径
        for (int i = 0; i < count; i++) {
            Json::Value hole = holes[QString::number(i).toStdString().c_str()];
            SizeData temp;
            temp.HolesID = hole["HolesID"].asInt();                             // 序号
            temp.Time = hole["Time"].asString().data();                         // 时间
            temp.Type = hole["Type"].asString().data();                         // 类型
            temp.HolesHeight = hole["HolesHeight"].asDouble();                  // 长X
            temp.HolesWidth = hole["HolesWidth"].asDouble();                    // 宽Y
            temp.DistanceHorizontal = hole["DistanceHorizontal"].asDouble();    // 边距X
            temp.DistanceVertical = hole["DistanceVertical"].asDouble();        // 边距Y
            temp.HolesLeve = hole["HolesLeve"].asString().data();               // 等级
            result.push_back(temp);
        }
    }
}

void Jsoncpp::writeSizeToJson(HoleResult inputdata)
{
    //
    // 每块玻璃单独一个文件
    //
    try{
        Json::Value root;
        Json::Value glassholedata;
        for(int i=0; i<(int)inputdata.holes.size(); ++i) {
            HoleData temp = inputdata.holes[i];
            Json::Value holeData;
            holeData["DistanceHorizontal"] = temp.DistanceHorizontal;
            holeData["DistanceVertical"] = temp.DistanceVertical;
            holeData["HolesHeight"] = temp.HolesHeight;
            holeData["HolesID"] = i;
            holeData["HolesLeve"] = temp.HolesLeve.toStdString().c_str();
            holeData["HolesWidth"] = temp.HolesWidth;
            holeData["ImageHolesPath"] = temp.ImageHolesPath.toStdString().c_str();
            holeData["Time"] = temp.Time.toStdString().c_str();
            holeData["Type"] = temp.Type.toStdString().c_str();
            glassholedata[QString::number(i).toStdString().c_str()] = holeData;
        }
        glassholedata["GlassLength"] = inputdata.GlassLength;
        glassholedata["GlassAngle"] = inputdata.GlassAngle;
        glassholedata["GlassWidth"] = inputdata.GlassWidth;
        glassholedata["ImageHolesLinePath"] = inputdata.ImageHolesLinePath.toStdString().c_str();
        root[QString::number(inputdata.GlassID).toStdString().c_str()] = glassholedata;

        Json::StreamWriterBuilder jswBuilder;
        jswBuilder["emitUTF8"] = true;//中文转换
        std::unique_ptr<Json::StreamWriter> jsWriter(jswBuilder.newStreamWriter());
        std::ofstream ofs;
        ofs.open(inputdata.jsonFullPath.toStdString().data());
        if (ofs.is_open()) {
            jsWriter->write(root, &ofs);
            ofs.close();
        }
    } catch(std::exception e) {
        qDebug()<<"Process_Detect::writeHoleDataToJsonfile Error"<<e.what();
    } catch(...) {
        qDebug()<<"Process_Detect::writeHoleDataToJsonfile Error";
    }
}

void Jsoncpp::writeDefectToJson(DefeteResult defect,int GlassID)
{
    //
    // 一块玻璃一个json文件
    //
    try{
        //
        // 将文件中已有的数据读出来
        //
        Json::Value root;
        QFile file(defect.jsonFullPath);
        int precount = 0;
        qDebug()<<"jsonFullPath="<<defect.jsonFullPath;
        if (file.exists()) {
            std::ifstream ifs;
            ifs.open(defect.jsonFullPath.toStdString().data()); // Windows自己注意路径吧
            if (ifs.is_open()) {
                Json::Reader reader;
                // 解析到root，root将包含Json里所有子元素
                reader.parse(ifs, root, false);
                ifs.close();
                precount = root[QString::number(GlassID).toStdString().c_str()].size() - 3;//减去宽度、长度、角度
                qDebug()<<"precount = " <<precount;
            } else {
                qDebug()<<__FUNCTION__<<" ifs.is_open() =  false";
            }
        }
        // 添加新数据
        Json::Value glassdata;
        if (precount != 0) {
            glassdata = root[QString::number(GlassID).toStdString().c_str()];
        }
        for(int i=0; i<(int)defect.defetes.size(); ++i) {
            DefeteData temp = defect.defetes[i];
            Json::Value defectdata;
            defectdata["Area"] = temp.Area;
            defectdata["DefectID"] = precount+i;//加上上一帧的数据个数
            defectdata["DefectType"] = temp.DefectType.toStdString().c_str();
            defectdata["DetectLeve"] = temp.DetectLeve.toStdString().c_str();
            defectdata["ImageNGPath"] = temp.ImageNGPath.toStdString().c_str();
            defectdata["Lenth"] = temp.Lenth;
            defectdata["Time"] = temp.Time.toStdString().c_str();
            defectdata["Width"] = temp.Width;
            defectdata["X"] = temp.X;
            defectdata["Y"] = temp.Y;
            glassdata[QString::number(precount+i).toStdString().c_str()] = defectdata;
        }
        glassdata["GlassLength"] = defect.GlassLength;
        glassdata["GlassAngle"] = defect.GlassAngle;
        glassdata["GlassWidth"] = defect.GlassWidth;
        root[QString::number(GlassID).toStdString().c_str()] = glassdata;

        Json::StreamWriterBuilder jswBuilder;
        jswBuilder["emitUTF8"] = true;//中文转换
        std::unique_ptr<Json::StreamWriter> jsWriter(jswBuilder.newStreamWriter());
        std::ofstream ofs;
        ofs.open(defect.jsonFullPath.toStdString().data());
        if (ofs.is_open()) {
            jsWriter->write(root, &ofs);
            ofs.close();
        }
    } catch(std::exception e) {
        qDebug()<<"[Process_Detect::DetectData2Json] Error"<<e.what();
    } catch(...) {
        qDebug()<<"[Process_Detect::DetectData2Json] Error";
    }
}

void Jsoncpp::readWorkOrderFromJson(QString jsonFilePath, WorkOrder& order)
{
    //
    // 将文件中已有的数据读出来
    //
    Json::Value root;
    QFile filer(jsonFilePath);
    if (filer.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFilePath.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<" ifs.is_open() =  false";
        }
    } else {
        qDebug()<<jsonFilePath<<" is not exit.";
    }
    if(!root.empty()) {
        Json::Value lightParam = root["光源控制器参数"];
        order.LCParam.signalChange = lightParam["信号切换"].asInt();
        order.LCParam.lightField_1_LuminescenceTime = lightParam["光场1发光时间"].asInt();
        order.LCParam.lightField_1_DelayTime = lightParam["光场1延时时间"].asInt();
        order.LCParam.lightField_2_LuminescenceTime = lightParam["光场2发光时间"].asInt();
        order.LCParam.lightField_2_DelayTime = lightParam["光场2延时时间"].asInt();
        order.LCParam.lightField_3_LuminescenceTime = lightParam["光场3发光时间"].asInt();
        order.LCParam.lightField_3_DelayTime = lightParam["光场3延时时间"].asInt();
        order.LCParam.lightField_4_LuminescenceTime = lightParam["光场4发光时间"].asInt();
        order.LCParam.lightField_4_DelayTime = lightParam["光场4延时时间"].asInt();
        order.LCParam.lightField_5_LuminescenceTime = lightParam["光场5发光时间"].asInt();
        order.LCParam.lightField_5_DelayTime = lightParam["光场5延时时间"].asInt();
        order.LCParam.lightField_6_LuminescenceTime = lightParam["光场6发光时间"].asInt();
        order.LCParam.lightField_6_DelayTime = lightParam["光场6延时时间"].asInt();
        order.LCParam.lightField_7_LuminescenceTime = lightParam["光场7发光时间"].asInt();
        order.LCParam.lightField_7_DelayTime = lightParam["光场7延时时间"].asInt();
        order.LCParam.lightField_8_LuminescenceTime = lightParam["光场8发光时间"].asInt();
        order.LCParam.lightField_8_DelayTime = lightParam["光场8延时时间"].asInt();
        order.LCParam.lightField_9_LuminescenceTime = lightParam["光场9发光时间"].asInt();
        order.LCParam.lightField_9_DelayTime = lightParam["光场9延时时间"].asInt();
        order.LCParam.lightField_10_LuminescenceTime = lightParam["光场10发光时间"].asInt();
        order.LCParam.lightField_10_DelayTime = lightParam["光场10延时时间"].asInt();
        order.LCParam.lightField_11_LuminescenceTime = lightParam["光场11发光时间"].asInt();
        order.LCParam.lightField_11_DelayTime = lightParam["光场11延时时间"].asInt();
        order.LCParam.lightField_12_LuminescenceTime = lightParam["光场12发光时间"].asInt();
        order.LCParam.lightField_12_DelayTime = lightParam["光场12延时时间"].asInt();
        order.LCParam.horizontalDarkFieldSelectionReg = lightParam["横向暗场选择寄存器"].asInt();
        order.LCParam.CameraLightCtrl =  lightParam["相机与光场控制"].asInt();
        order.LCParam.LightSignalSlection = lightParam["行信号源选择"].asInt();
        order.LCParam.LightField = lightParam["选择光场的数量"].asInt();
        Json::Value sizeMesure = root["尺寸测量"];
        order.DMParam.YB = sizeMesure["Y方向精度B"].asDouble();
        order.DMParam.YK = sizeMesure["Y方向精度K"].asDouble();
        order.DMParam.width = sizeMesure["宽度"].asDouble();
        order.DMParam.widthDeviation = sizeMesure["宽度误差"].asDouble();
        order.DMParam.diagonal1 = sizeMesure["对角线1"].asDouble();
        order.DMParam.diagonal1Deviation = sizeMesure["对角线1误差"].asDouble();
        order.DMParam.diagonal2 = sizeMesure["对角线2"].asDouble();
        order.DMParam.diagonal2Deviation = sizeMesure["对角线2误差"].asDouble();
        order.DMParam.enableMeasure = sizeMesure["尺寸测量启用"].asDouble();
        order.DMParam.camera1PixAccury = sizeMesure["相机1像素0精度"].asDouble();
        order.DMParam.camera1K = sizeMesure["相机1像素k值"].asDouble();
        order.DMParam.camera2CompareCamera1 = sizeMesure["相机2与相机1精度比值"].asDouble();
        order.DMParam.camera2K = sizeMesure["相机2像素k值"].asDouble();
        order.DMParam.length = sizeMesure["长度"].asDouble();
        order.DMParam.lengthDeviation = sizeMesure["长度误差"].asDouble();
        Json::Value crtlParm = root["控制器系统参数"];
        order.CSParam.PixAccury = crtlParm["像素精度"].asInt();
        order.CSParam.PhotoelectricSignalPulseFiltering = crtlParm["光电信号脉冲滤波"].asInt();
        order.CSParam.PhotoelectricSignalCameraDistance = crtlParm["光电相机距离"].asInt();
        order.CSParam.InnerLineFrequency = crtlParm["内部行频"].asInt();
        order.CSParam.FrameSignalDuration = crtlParm["帧信号持续时间"].asInt();
        order.CSParam.PhotMode = crtlParm["拍照模式"].asInt();
        order.CSParam.PhotoEndDelayLine = crtlParm["拍照结束延时行数"].asInt();
        order.CSParam.EnableModuleOn = crtlParm["模块使能信号"].asInt();
        order.CSParam.CameraFrameSignalStartDelayLine = crtlParm["相机帧信号触发延时行数"].asInt();
        order.CSParam.CameraPhotoLine = crtlParm["相机拍照行数"].asInt();
        order.CSParam.CameraStartPlusDuration = crtlParm["相机触发脉冲持续时间"].asInt();
        CameraParameters cam1,cam2,cam3,cam4;
        Json::Value cam1Param = root["相机0"];
        cam1.CameraGain = cam1Param["相机增益"].asInt();
        cam1.FrameCount = cam1Param["帧次"].asInt();
        cam1.PhotoLineCount = cam1Param["拍照行数"].asInt();
        cam1.ExposureTime = cam1Param["曝光时间"].asInt();
        order.CVecParam.push_back(cam1);
        Json::Value cam2Param = root["相机1"];
        cam2.CameraGain = cam2Param["相机增益"].asInt();
        cam2.FrameCount = cam2Param["帧次"].asInt();
        cam2.PhotoLineCount = cam2Param["拍照行数"].asInt();
        cam2.ExposureTime = cam2Param["曝光时间"].asInt();
        order.CVecParam.push_back(cam2);
        Json::Value cam3Param = root["相机2"];
        cam3.CameraGain = cam3Param["相机增益"].asInt();
        cam3.FrameCount = cam3Param["帧次"].asInt();
        cam3.PhotoLineCount = cam3Param["拍照行数"].asInt();
        cam3.ExposureTime = cam3Param["曝光时间"].asInt();
        order.CVecParam.push_back(cam3);
        Json::Value cam4Param = root["相机3"];
        cam4.CameraGain = cam4Param["相机增益"].asInt();
        cam4.FrameCount = cam4Param["帧次"].asInt();
        cam4.PhotoLineCount = cam4Param["拍照行数"].asInt();
        cam4.ExposureTime = cam4Param["曝光时间"].asInt();
        order.CVecParam.push_back(cam4);
        Json::Value CodeParams = root["编码器参数"];
        order.CoderParam.PressureWheelK = CodeParams["压轮编码器系数"].asDouble();
        order.CoderParam.PressureWheelACount = CodeParams["压轮编码器A计数"].asInt();
        order.CoderParam.PressureWheelBCount = CodeParams["压轮编码器B计数"].asInt();
        order.CoderParam.PressureWheel4FrequencyCount = CodeParams["压轮编码器四倍频计数"].asInt();
        order.CoderParam.ExceptOnePixAccury = CodeParams["期望单个像素精度"].asInt();
        order.CoderParam.Coder4FrequencyCount = CodeParams["编码器4倍频计数"].asInt();
        order.CoderParam.CoderUnitTimePlusCount = CodeParams["编码器单位时间脉冲计数"].asInt();
        order.CoderParam.CoderUnitScaleToDistance = CodeParams["编码器单位刻度对应距离"].asInt();
        order.CoderParam.CoderTriggerLineCount = CodeParams["编码器触发行计数"].asInt();
        order.CoderParam.CoderCount = CodeParams["编码器计数"].asInt();
        order.CoderParam.CoderCountTime = CodeParams["编码器计数时间"].asInt();
        order.CoderParam.CoderCountEndFlag = CodeParams["编码器计数结束标志"].asInt();
        order.CoderParam.CoderCircleCount = CodeParams["编码器转数"].asInt();
        order.CoderParam.CoderPulseFiltering = CodeParams["编码脉冲滤波"].asInt();
        order.CoderParam.CoderChannel = CodeParams["编码通道"].asInt();
        order.CoderParam.RollerCircumference = CodeParams["辊道周长"].asInt();
        order.CoderParam.RollerMaxToLine = CodeParams["辊道最大速度对应行频"].asInt();
        Json::Value DefectParams = root["缺陷检测"];
        order.DDCParam.Camera12PixOffset = DefectParams["12相机像素偏差"].asInt();
        order.DDCParam.Camera23PixOffset = DefectParams["23相机像素偏差"].asInt();
        order.DDCParam.Camera24PixOffset = DefectParams["24相机像素偏差"].asInt();
        order.DDCParam.SiyinToRollerDistance = DefectParams["丝印离辊道距离"].asDouble();
        order.DDCParam.GlassThickness = DefectParams["玻璃厚度"].asInt();
        order.DDCParam.EnableDefect = DefectParams["缺陷检测启用"].asInt();
        Json::Value DefectAreaParams = root["缺陷面积阈值"];
        order.DATParam.HuashanAreaThreahold = DefectAreaParams["划痕面积阈值"].asInt();
        order.DATParam.QijieAreaThreahold = DefectAreaParams["气结面积阈值"].asInt();
        order.DATParam.ZanwuAreaThreahold = DefectAreaParams["脏污面积阈值"].asInt();
        Json::Value custom = root["自定义参数"];
        order.CTParam.SaveOrigin = custom["保存原图"].asInt();
        order.CTParam.SaveImage = custom["保存整图"].asInt();
        order.CTParam.SaveCorpImage = custom["保存裁剪图像"].asInt();
        order.CTParam.SaveDefectIamge = custom["保存缺检图"].asInt();
        order.CTParam.EnableDimensionalMeasurement = custom["尺寸测量启用"].asInt();
        order.CTParam.EnableDefect = custom["缺陷检测启用"].asInt();
    }
}

//communication模块保存json
void Jsoncpp::writeComDataToJson(QString recipeFullpath, const SignalControl& data)
{
    //
    // 直接将数据覆盖到文件中
    //
    try{
        Json::Value root;
        //系统参数
        root["SystemParams"]["SystemName"] = data.systemName.toStdString().c_str();
        root["SystemParams"]["CamareNumber"] = data.CamareNumber;
        root["SystemParams"]["Camare0Name"] = data.Camare0Name.toStdString().c_str();
        root["SystemParams"]["Camare1Name"] = data.Camare1Name.toStdString().c_str();
        root["SystemParams"]["Camare2Name"] = data.Camare2Name.toStdString().c_str();
        root["SystemParams"]["Camare3Name"] = data.Camare3Name.toStdString().c_str();
        root["SystemParams"]["ServerIP"] = data.ServerIP.toStdString().c_str();
        root["SystemParams"]["ServerPort"] = data.ServerPort;
        //自定义参数
        root["CustomParams"]["SaveOriginImage"] = data.SaveOriginImage;
        root["CustomParams"]["SaveEntireImage"] = data.SaveEntireImage;
        root["CustomParams"]["SaveFlawImage"] = data.SaveFlawImage;
        root["CustomParams"]["SaveCropImage"] = data.SaveCropImage;
        root["CustomParams"]["XYLengthEnable"] = data.XYLengthEnable;
        root["CustomParams"]["FlawDefectEnable"] = data.FlawDefectEnable;
        //缺陷检测
        root["DefectDetectionParams"]["Camera12PixelDeviation"] = data.Camera12PixelDeviation;
        root["DefectDetectionParams"]["Camera23PixelDeviation"] = data.Camera23PixelDeviation;
        root["DefectDetectionParams"]["Camera24PixelDeviation"] = data.Camera24PixelDeviation;
        root["DefectDetectionParams"]["SilkToRollerDist"] = data.SilkToRollerDist;
        root["DefectDetectionParams"]["ScratchAreaThreshold"] = data.ScratchAreaThreshold;
        root["DefectDetectionParams"]["BubbleStoneAreaThreshold"] = data.BubbleStoneAreaThreshold;
        root["DefectDetectionParams"]["DirtyAreaThreshold"] = data.DirtyAreaThreshold;
        //尺寸测量
        root["DimensionalMeasurementParams"]["YAccuracyB"] = data.YAccuracyB;
        root["DimensionalMeasurementParams"]["YAccuracyK"] = data.YAccuracyK;
        root["DimensionalMeasurementParams"]["Width"] = data.Width;
        root["DimensionalMeasurementParams"]["WidthDeviation"] = data.WidthDeviation;
        root["DimensionalMeasurementParams"]["Digonal1"] = data.Digonal1;
        root["DimensionalMeasurementParams"]["Digonal1Deviation"] = data.Digonal1Deviation;
        root["DimensionalMeasurementParams"]["Diagonal2"] = data.Diagonal2;
        root["DimensionalMeasurementParams"]["Digonal2Deviation"] = data.Digonal2Deviation;
        root["DimensionalMeasurementParams"]["Camera1Pixel0Accuracy"] = data.Camera1Pixel0Accuracy;
        root["DimensionalMeasurementParams"]["Camera1PixelKValue"] = data.Camera1PixelKValue;
        root["DimensionalMeasurementParams"]["Camera21AccuracyRatio"] = data.Camera21AccuracyRatio;
        root["DimensionalMeasurementParams"]["Camera2PixelKValue"] = data.Camera2PixelKValue;
        root["DimensionalMeasurementParams"]["Length"] = data.Length;
        root["DimensionalMeasurementParams"]["LengthDeviation"] = data.LengthDeviation;
        //相机参数
        root["CamareParams"]["Camera0Frame"] = data.Camera0Frame;
        root["CamareParams"]["Camera0PhotoRow"] = data.Camera0PhotoRow;
        root["CamareParams"]["Camera0ExposureTime"] = data.Camera0ExposureTime;
        root["CamareParams"]["Camera0Gain"] = data.Camera0Gain;
        root["CamareParams"]["Camera1Frame"] = data.Camera1Frame;
        root["CamareParams"]["Camera1PhotoRow"] = data.Camera1PhotoRow;
        root["CamareParams"]["Camera1ExposureTime"] = data.Camera1ExposureTime;
        root["CamareParams"]["Camera1Gain"] = data.Camera1Gain;
        root["CamareParams"]["Camera2Frame"] = data.Camera2Frame;
        root["CamareParams"]["Camera2PhotoRow"] = data.Camera2PhotoRow;
        root["CamareParams"]["Camera2ExposureTime"] = data.Camera2ExposureTime;
        root["CamareParams"]["Camera2Gain"] = data.Camera2Gain;
        root["CamareParams"]["Camera3Frame"] = data.Camera3Frame;
        root["CamareParams"]["Camera3PhotoRow"] = data.Camera3PhotoRow;
        root["CamareParams"]["Camera3ExposureTime"] = data.Camera3ExposureTime;
        root["CamareParams"]["Camera3Gain"] = data.Camera3Gain;
        //编码器参数
        root["EncoderParams"]["EncodeUnitToDist"] = data.temp0;
        root["EncoderParams"]["EncodePulseFilterUs"] = data.temp1;
        root["EncoderParams"]["EncodeCountEndFlag"] = data.temp2;
        root["EncoderParams"]["EncodeCount"] = data.temp3;
        root["EncoderParams"]["EncodeTriggerRowCount"] = data.temp4;
        root["EncoderParams"]["Encode4FrequencyMultiplierCount"] = data.temp5;
        root["EncoderParams"]["EncodeUnitTimePulseCount"] = data.temp6;
        root["EncoderParams"]["EncodeCountTimeHalfSecond"] = data.temp7;
        root["EncoderParams"]["EncodeChannel"] = data.temp8;
        root["EncoderParams"]["EncodeRevolution"] = data.temp9;
        root["EncoderParams"]["RollerPerimeterUm"] = data.temp10;
        root["EncoderParams"]["ExpectSinglePixelAccuracy"] = data.temp11;
        root["EncoderParams"]["RollerMaxSpeedToRowCount"] = data.temp12;
        root["EncoderParams"]["EveryRowToEncodeCount"] = data.temp13;
        root["EncoderParams"]["PressureEncodecoefficient"] = data.tempRollerCofficient;
        //控制器参数
        root["ControllerParams"]["PixelAccuracyUm"] = data.temp14;
        root["ControllerParams"]["PhotoelectricSignalPulseFilter"] = data.temp15;
        root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"] = data.temp16;
        root["ControllerParams"]["PhotoelectricToCamareDist"] = data.temp17;
        root["ControllerParams"]["CamareFrameTrigerDelayRowCount"] = data.temp18;
        root["ControllerParams"]["FrameSignalContinueTime"] = data.temp19;
        root["ControllerParams"]["ModuleEnableSignal"] = data.temp20;
        root["ControllerParams"]["CamarePhotoRowCount"] = data.temp21;
        root["ControllerParams"]["InnerRowFrequency"] = data.temp22;
        root["ControllerParams"]["PhotoMode"] = data.tempAutoPhoto;
        root["ControllerParams"]["PhotoEndDelayRowCount"] = data.temp18;
        //光源控制器参数
        root["LighterParams"]["LightField1DelayTime"] = data.temp23;
        root["LighterParams"]["LightField1GlowTime"] = data.temp24;
        root["LighterParams"]["LightField2DelayTime"] = data.temp25;
        root["LighterParams"]["LightField2GlowTime"] = data.temp26;
        root["LighterParams"]["LightField3DelayTime"] = data.temp27;
        root["LighterParams"]["LightField3GlowTime"] = data.temp28;
        root["LighterParams"]["LightField4DelayTime"] = data.temp29;
        root["LighterParams"]["LightField4GlowTime"] = data.temp30;
        root["LighterParams"]["SelectedLightFieldNumber"] = data.temp55;
        root["LighterParams"]["HorizontalDarkfieldSelectRegister"] = data.temp56;
        root["LighterParams"]["CamareAndLightFieldControl"] = data.temp35;
        root["LighterParams"]["SignalSwitch"] = data.temp36;
        root["LighterParams"]["RowSignalSelected"] = data.temp37;


        Json::StreamWriterBuilder jswBuilder;
        jswBuilder["emitUTF8"] = true;//中文转换
        std::unique_ptr<Json::StreamWriter> jsWriter(jswBuilder.newStreamWriter());
        std::ofstream ofs;
        ofs.open(recipeFullpath.toStdString().data());
        if (ofs.is_open()) {
            jsWriter->write(root, &ofs);
            ofs.close();
        }
    } catch(std::exception e) {
        qDebug()<<"[Process_Detect::DetectData2Json] Error"<<e.what();
    } catch(...) {
        qDebug()<<"[Process_Detect::DetectData2Json] Error";
    }
}




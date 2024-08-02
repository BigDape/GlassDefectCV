#include "processdetect.h"
#include <algorithm>
#include "Parameter/json.h"
#include <iostream>
#include <fstream>
#include <QQueue>
#include <QDir>
#include <QThread>
#include "processtile.h"

#pragma execution_character_set("utf-8")
Process_Detect::Process_Detect()
{
    ResultNotOutFlag = false;
    ErrFlag = false;
    GlassPosition=0;
    Points = QList<FlawPoint>();
    ProcessStep = 0; //相机帧数
    m_FramesPerTri=0;

    YCoordIn= 0;
    YCoordOut = HTuple();
    //
    // 声明halcon脚本引擎
    //
    engine = new HDevEngine();
    engine->SetEngineAttribute("docu_language", "zh_CN");
    engine_path = "D:/HalconFunction/";
    engine->AddProcedurePath(engine_path.toLatin1().data());
    procedure = new HDevProcedure("ProcessVision");
    procedurecall = new HDevProcedureCall(*procedure);
    procedure2 = new HDevProcedure("ProcessHoles");
    procedurecall2 = new HDevProcedureCall(*procedure2);
    hasStopThread.store(false);
}

Process_Detect::~Process_Detect()
{
    delete engine;
    engine = nullptr;
    delete procedure;
    procedure = nullptr;
    delete procedurecall;
    procedurecall = nullptr;
    delete procedure2;
    procedure2 = nullptr;
    delete procedurecall2;
    procedurecall2 = nullptr;
}

void Process_Detect::run()
{
PDLOOP:
    //条件变量
    if (!ProcessTile::preImageQueue.empty()) {
        PDArgs args;
        if(ProcessTile::preImageQueue.dequeue(args)) {
            Process_Detect::VisionProcess(args.imageunit, args.holeunit);
        }
    }
    if (!hasStopThread.load())
        goto PDLOOP;
}

//算法执行
void Process_Detect::VisionProcess(ImageUnit imageunit, HoleUnit holeunit)
{
    if (Global::isOffline == false && Global::SystemStatus == 0) return;
    int glassID;
    //recipe切换
    if(Global::RecChangeSignal) {
        Global::RecChangeSignal=false;
    }
//        GetDictTuple(Global::RecipeDict,"编码器参数",&Code);
//        GetDictTuple(Code,"编码器单位刻度对应距离",&CodePerScale);

    ProcessStep = imageunit.ProcessStep;
    GlassPosition = imageunit.GlassPositionInf; //玻璃部分，1头2中3尾0完整玻璃
    m_FramesPerTri = Global::FramesPerTri;
    HTuple UserDefinedDict;
    GetDictTuple(Global::RecipeDict,"自定义参数",&UserDefinedDict);
    if(ProcessStep==1 || GlassPosition==1 || GlassPosition==0) {
        ErrFlag = false;
        //判断上一片玻璃结果是否输出
        if(ResultNotOutFlag) {
            Process_Detect::SummaryFailResult();// 输出结果
            ResultNotOutFlag = false;
        }
        Global::AlmLightSignal=true;
        Global::AlmLightVal=0;
    }
    qDebug() << "ProcessStep :" << ProcessStep;
    HTuple EnableDefect;
    GetDictTuple(UserDefinedDict,"缺陷检测启用",&EnableDefect);
    ProcessVisionAlgorithmResults processvisionresult;//算法执行结果
    DefeteResult outResult;//解析出来的结果
    if( EnableDefect==1 ) {
        //图像正常执行算法or输出异常提醒
        if(imageunit.ImageList.CountObj()>0 && imageunit.ErrorFlag==false) {
            bool EnableDefect=true;
            if(EnableDefect) {
                try {
                    HObject SelectObj1,SelectObj2,SelectObj3;
                    SelectObj(imageunit.ImageList,&SelectObj1,1);
                    SelectObj(imageunit.ImageList,&SelectObj2,2);
                    SelectObj(imageunit.ImageList,&SelectObj3,3);

                    procedurecall->SetInputIconicParamObject("Image1", SelectObj1);
                    procedurecall->SetInputIconicParamObject("Image2", SelectObj2);
                    procedurecall->SetInputIconicParamObject("Image3", SelectObj3);
                    procedurecall->SetInputIconicParamObject("GlassRegion", imageunit.ImageRegion);
                    procedurecall->SetInputIconicParamObject("FrameRegion", imageunit.FrameRegion);
                    if(GlassPosition==1 || GlassPosition==0) {
                        HTuple a=0;
                        YCoordIn= a ;
                    } else {
                        YCoordIn= YCoordOut;
                    }
                    procedurecall->SetInputCtrlParamTuple("VisionProcessStep", ProcessStep);
                    procedurecall->SetInputCtrlParamTuple("GlassPositionInf", GlassPosition);
                    procedurecall->SetInputCtrlParamTuple("YCoordIn", YCoordIn);
                    procedurecall->SetInputCtrlParamTuple("DetectDict", Global::RecipeDict);
                    procedurecall->Execute();
                    //获取算法结果
                    processvisionresult.GlassID = Global::GlassID_INT;
                    processvisionresult.ErrImage1 = procedurecall->GetOutputIconicParamObject("ErrImage1");
                    processvisionresult.ErrImage2 = procedurecall->GetOutputIconicParamObject("ErrImage2");
                    processvisionresult.ErrImage3 = procedurecall->GetOutputIconicParamObject("ErrImage3");
                    processvisionresult.ResultDict = procedurecall->GetOutputCtrlParamTuple("ResultDict");
                    processvisionresult.ErrName = processvisionresult.ResultDict.TupleGetDictTuple("ErrName");
                    processvisionresult.ErrType = processvisionresult.ResultDict.TupleGetDictTuple("ErrType");
                    processvisionresult.DefectLevel = processvisionresult.ResultDict.TupleGetDictTuple("DefectLevel");
                    processvisionresult.ErrX = processvisionresult.ResultDict.TupleGetDictTuple("ErrX");
                    processvisionresult.ErrY = processvisionresult.ResultDict.TupleGetDictTuple("ErrY");
                    processvisionresult.ErrW = processvisionresult.ResultDict.TupleGetDictTuple("ErrW");
                    processvisionresult.ErrL = processvisionresult.ResultDict.TupleGetDictTuple("ErrH");
                    processvisionresult.ErrArea = processvisionresult.ResultDict.TupleGetDictTuple("ErrArea");
                    processvisionresult.YCoordOut = procedurecall->GetOutputCtrlParamTuple("YCoordOut");
                    processvisionresult.GlassLength = procedurecall->GetOutputCtrlParamTuple("GlassLength");
                    processvisionresult.GlassWidth = procedurecall->GetOutputCtrlParamTuple("GlassWidth");
                    processvisionresult.GlassAngle = procedurecall->GetOutputCtrlParamTuple("GlassAngle");
                    processvisionresult.XValues = procedurecall->GetOutputCtrlParamTuple("Col_x");
                    processvisionresult.YValues = procedurecall->GetOutputCtrlParamTuple("Row_y");
                    if ( processvisionresult.XValues.Length() == processvisionresult.YValues.Length() ) {
                        Global::courtourMapXY.clear();
                        for (int ii = 0; ii < processvisionresult.XValues.Length(); ii = ii +12) {
                            QString xx = processvisionresult.XValues.TupleSelect(ii).ToString().Text();
                            QString yy = processvisionresult.YValues.TupleSelect(ii).ToString().Text();
                            CourTour tour;
                            tour.index = ii;
                            tour.x = xx;
                            tour.y = yy;
                            Global::courtourMapXY.push_back(tour);
                        }
                    }

                    Process_Detect::saveErrImage(processvisionresult, outResult);
                    processvisionresult.time = currentTimeJson.toString("yyyy-MM-dd hh:mm:ss");
                    glassID = outResult.GlassID; //更新GlassID，给后面程序使用
                    Process_Detect::DetectData2Json(outResult,outResult.jsonFullPath);
                    qDebug()<<"GlassPosition: "<<GlassPosition;qDebug()<<"Points.size(): "<<Points.size();

                    emit sig_sendPoint(Points);   //发送显示缺陷点位置信号
                    //emit sig_updateSignalFlaw(outResult.jsonFullPath, outResult.GlassID);//更新缺陷小图信息
                    qDebug()<<"ProcessStep"<<ProcessStep;
                    qDebug()<<"m_FramesPerTri"<<Global::FramesPerTri;
                    QString info="ProcessStep" + QString::number(ProcessStep)  + "算法执行完成！";
                    log_singleton::Write_Log(info, Log_Level::General);
                } catch (HalconCpp::HException& Except) {
                    ErrFlag = true;
                    qDebug() << "HalconHalconErr:" << Except.ErrorMessage().Text();
                    QString info= "算法执行异常！";
                    log_singleton::Write_Log(info, Log_Level::General);
                }//try
            }//if(EnableDefect)
        } else { //if(imageunit.ImageList.CountObj()>0 && imageunit.ErrorFlag==false)
            ErrFlag=true;
            qDebug() << "图像为空或已出现异常！";
            QString info= "图像为空或已出现异常！";
            log_singleton::Write_Log(info, Log_Level::General);
        }//if(imageunit.ImageList.CountObj()>0 &&imageunit.ErrorFlag==false)
    }//if(EnableDefect==1)
    //
    // 尺寸測量
    //
    ProcessHolesAlgorithmResults procesHoleResult;
    HoleResult holeresult;
    if (GlassPosition==0 || GlassPosition==3 ) {
        HTuple EnableMeasure;
        GetDictTuple(UserDefinedDict,"尺寸测量启用",&EnableMeasure);
        qDebug() << "EnableMeasure :" << EnableMeasure.ToString().Text();
        if(EnableMeasure==1) {
            procesHoleResult.GlassID = glassID;
            procesHoleResult.HolesImage.GenEmptyObj();
            procesHoleResult.OutLineImage.GenEmptyObj();
            Process_Detect::DetectSiYin(holeunit, procesHoleResult);
            Process_Detect::HolesData2Json(procesHoleResult,holeresult);
            emit sig_updateFlaw(procesHoleResult.GlassWidth.D(),procesHoleResult.GlassLength.D());//画出最外围轮廓
        }
    }
    ResultNotOutFlag = true;
    GlassDataBaseInfo baseinfo;
    Process_Detect::Glassinfo(processvisionresult,baseinfo);

    emit sendData(baseinfo); //信息统计表格中插入一行数据
    QString glassidAndTime = QString::number(baseinfo.id) + "." + currentTimeJson.toString("yyyy-MM-dd HH");
    //更新缺陷小图
    emit sig_refreshFlaw(outResult.jsonFullPath,outResult.GlassID); //刷新缺陷
    emit sig_refreshSize(holeresult.jsonFullPath,holeresult.GlassID); //刷新尺寸
    if (GlassPosition==0 || GlassPosition==3 ) {
        Process_Detect::SummaryResults(baseinfo);
        ResultNotOutFlag = false;
    }

}

void Process_Detect::DetectSiYin(HoleUnit holeunit, ProcessHolesAlgorithmResults& procesHoleResult)
{
    HTuple NumTile;
    CountObj(holeunit.ImageTile1R,&NumTile);
    if(NumTile>0) {
        try {
            procedurecall2->SetInputCtrlParamTuple("Cam1pixs", holeunit.Cam1pixs);
            procedurecall2->SetInputCtrlParamTuple("Cam1Width", holeunit.Cam1Width);
            procedurecall2->SetInputCtrlParamTuple("Tile2Column1", holeunit.Tile2Column1);
            procedurecall2->SetInputCtrlParamTuple("DetectDict", Global::RecipeDict);
            procedurecall2->SetInputIconicParamObject("Image1", holeunit.ImageTile1R);
            procedurecall2->SetInputIconicParamObject("Image2", holeunit.ImageTile2R);
            procedurecall2->SetInputIconicParamObject("Image3", holeunit.ImageTile3R);
            procedurecall2->SetInputIconicParamObject("Image4", holeunit.ImageTile4R);
            procedurecall2->Execute();
        } catch (HalconCpp::HException& Except) {
            ErrFlag = true;
            qDebug() << "HalconHalconErr:" << Except.ErrorMessage().Text();
            QString info= "算法执行异常！";
            log_singleton::Write_Log(info, Log_Level::General);
        }

        try{
            ConcatObj(procesHoleResult.OutLineImage, procedurecall2->GetOutputIconicParamObject("OutLineImage"), &procesHoleResult.OutLineImage);
            ConcatObj(procesHoleResult.HolesImage, procedurecall2->GetOutputIconicParamObject("HolesImage"), &procesHoleResult.HolesImage);
            HTuple CountHoles=0;
            CountObj(procesHoleResult.HolesImage,&CountHoles);
            procesHoleResult.ResultDictHoles = procedurecall2->GetOutputCtrlParamTuple("ResultDictHoles");
            if( CountHoles > 0 ) {
                procesHoleResult.Type = procesHoleResult.ResultDictHoles.TupleGetDictTuple("Type");
                procesHoleResult.HolesOK = procesHoleResult.ResultDictHoles.TupleGetDictTuple("HolesOK");
                procesHoleResult.DistanceHorizontal = procesHoleResult.ResultDictHoles.TupleGetDictTuple("DistanceHorizontal");
                procesHoleResult.DistanceVertical = procesHoleResult.ResultDictHoles.TupleGetDictTuple("DistanceVertical");
                procesHoleResult.HolesWidth = procesHoleResult.ResultDictHoles.TupleGetDictTuple("HolesWidth");
                procesHoleResult.HolesHeight = procesHoleResult.ResultDictHoles.TupleGetDictTuple("HolesHeight");
            }
            procesHoleResult.GlassWidth = procesHoleResult.ResultDictHoles.TupleGetDictTuple("GlassWidth");
            procesHoleResult.GlassLength = procesHoleResult.ResultDictHoles.TupleGetDictTuple("GlassHeight");
        } catch(HalconCpp::HException& Except) {
            procesHoleResult.GlassWidth = 0;
            procesHoleResult.GlassLength = 0;
            qDebug() << "HalconHalconErr:" << Except.ErrorMessage().Text();
        }
        qDebug() << "Current used GlassWidth ="<<procesHoleResult.GlassWidth.ToString().Text();
        qDebug() << "Current used GlassLenth ="<<procesHoleResult.GlassLength.ToString().Text();
   } else {
        //无测量结果
        qDebug() << "Error : NumTile = "<<NumTile.I();
   }
}
void Process_Detect::slot_updateSortInfo()
{
    if(summaryResult.GlassNum > 0 ) {
       summaryResult.unsorted = summaryResult.unsorted - 1;
       summaryResult.sorted = summaryResult.sorted + 1;
       emit sig_updateSortRes(summaryResult); //更新标题框上的检出和分拣
    }
}

void Process_Detect::SummaryResults(GlassDataBaseInfo baseinfo)
{
    summaryResult.GlassNum = summaryResult.GlassNum + 1;

    if(baseinfo.OKorNG == "OK") {
        //报警灯信号输出
        Global::AlmLightSignal = true;
        Global::AlmLightVal = 4;
        summaryResult.okNum = summaryResult.okNum + 1;
        summaryResult.unsorted = summaryResult.unsorted + 1;
        summaryResult.currentOKorNG = true; //当前玻璃OK或者NG
        summaryResult.currentSort = false;   //当前玻璃是否分拣
        summaryResult.suceessRate = (double)summaryResult.okNum / (double)summaryResult.GlassNum;
    } else {
        //报警灯信号输出
        Global::AlmLightSignal=true;
        Global::AlmLightVal=15;
        summaryResult.ngNum = summaryResult.ngNum + 1;
        summaryResult.unsorted = summaryResult.unsorted + 1;
        summaryResult.exceptNum = summaryResult.exceptNum + 1;
        summaryResult.currentOKorNG = false; //当前玻璃OK或者NG
        summaryResult.currentSort = false;   //当前玻璃是否分拣
        summaryResult.suceessRate = (double)summaryResult.okNum / (double)summaryResult.GlassNum;
    }

    //检测结果刷新
    emit sig_UpdateResultInfo(summaryResult);
    Global::GlassID_INT = Global::GlassID_INT + 1; //玻璃id加1

    // 发送数据
    Points.clear();
    QString info="玻璃ID" + QString::number(baseinfo.id)  + "算法执行完成！";
    log_singleton::Write_Log(info, Log_Level::General);
}

void Process_Detect::DetectData2Json(DefeteResult result,QString jsonFullPath)
{
    qDebug()<<"[Process_Detect::DetectData2Json] DefeteResult{"
            <<"GlassID="<<result.GlassID
            <<",std::vector<DefeteData> defetes.size()="<<result.defetes.size()
            <<",GlassWidth="<<result.GlassWidth
            <<",GlassLength="<<result.GlassLength
            <<",GlassAngle="<<result.GlassAngle
            <<",jsonFullPath="<<result.jsonFullPath
            <<",currentTime="<<result.currentTime.toString()<<"}";

    //
    // 一块玻璃一个json文件
    //
    try{
        Json::Value root;
        Json::Value glassdata;
        for(int i=0; i<(int)result.defetes.size(); ++i) {
            DefeteData temp = result.defetes[i];
            Json::Value defectdata;
            defectdata["Area"] = temp.Area;
            defectdata["DefectID"] = i;
            defectdata["DefectType"] = temp.DefectType.toStdString().c_str();
            defectdata["DetectLeve"] = temp.DetectLeve.toStdString().c_str();
            defectdata["ImageNGPath"] = temp.ImageNGPath.toStdString().c_str();
            defectdata["Lenth"] = temp.Lenth;
            defectdata["Time"] = temp.Time.toStdString().c_str();
            defectdata["Width"] = temp.Width;
            defectdata["X"] = temp.X;
            defectdata["Y"] = temp.Y;
            glassdata[QString::number(i).toStdString().c_str()] = defectdata;
        }
        glassdata["GlassLength"] = result.GlassLength;
        glassdata["GlassAngle"] = result.GlassAngle;
        glassdata["GlassWidth"] = result.GlassWidth;
        root[QString::number(result.GlassID).toStdString().c_str()] = glassdata;

        Json::StreamWriterBuilder jswBuilder;
        jswBuilder["emitUTF8"] = true;//中文转换
        std::unique_ptr<Json::StreamWriter> jsWriter(jswBuilder.newStreamWriter());
        std::ofstream ofs;
        ofs.open(jsonFullPath.toStdString().data());
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

void Process_Detect::HolesData2Json(ProcessHolesAlgorithmResults procesHoleResult,HoleResult& holeresult)
{
    //
    // 判断外层文件是否存在
    //
    QString folderDefectImage = QString("D:/SaveDefectImage");
    if( !Process_Detect::isExistDir(folderDefectImage)) {
        QString errorMessage = "Faile to create " + folderDefectImage;
        throw std::exception(errorMessage.toStdString().c_str());
    }
    QString folderName = QString("D:/SaveDefectImage/") + currentTimeJson.toString("yyyy-MM-dd");
    if( !Process_Detect::isExistDir(folderName)) {
        QString errorMessage = "Faile to create " + folderName;
        throw std::exception(errorMessage.toStdString().c_str());
    }

    //
    // 解析算法结果数据
    //
    holeresult.GlassID = procesHoleResult.GlassID;
    HTuple CountSK;
    CountObj(procesHoleResult.HolesImage, &CountSK);
    qDebug()<<"count2:"<<CountSK.ToString().Text();
    for (int i = 0; i < CountSK; i++) {
        HoleData hole;
        hole.HolesID = i+1;
        hole.Time = currentTimeJson.toString("hh-mm-ss");
        QString strType = procesHoleResult.Type.TupleSelect(i).ToString().Text();
        strType = strType.remove("\"");
        hole.Type = strType;
        QString strHolesOK = procesHoleResult.HolesOK.TupleSelect(i).ToString().Text();
        strHolesOK = strHolesOK.remove("\"");
        hole.HolesLeve = strHolesOK;
        qDebug()<<strType<<strHolesOK;
        QString strDistanceHorizontal, strDistanceVertical, strHolesWidth, strHolesHeight;
        if (procesHoleResult.DistanceHorizontal.Length()==CountSK
                && procesHoleResult.DistanceVertical.Length()==CountSK
                && procesHoleResult.HolesWidth.Length()==CountSK
                && procesHoleResult.HolesHeight.Length()==CountSK ) {
            QString strDistanceHorizontal = procesHoleResult.DistanceHorizontal.TupleSelect(i).ToString().Text();
            hole.DistanceHorizontal = strDistanceHorizontal.toDouble();

            QString strDistanceVertical = procesHoleResult.DistanceVertical.TupleSelect(i).ToString().Text();
            hole.DistanceVertical = strDistanceVertical.toDouble();

            QString strHolesWidth = procesHoleResult.HolesWidth.TupleSelect(i).ToString().Text();
            hole.HolesWidth = strHolesWidth.toDouble();

            QString strHolesHeight = procesHoleResult.HolesHeight.TupleSelect(i).ToString().Text();
            hole.HolesHeight = strHolesHeight.toDouble();
        } else {
            hole.DistanceHorizontal = 0;
            hole.DistanceVertical = 0;
            hole.HolesWidth = 0;
            hole.HolesHeight = 0;
        }

        QString strImageHolesPath = folderName + "/" + "孔" + "/" + currentTimeJson.toString("yyyy-MM-dd");
        hole.ImageHolesPath = strImageHolesPath;
        holeresult.holes.push_back(hole);
        //存小图
        QString directory1 = folderName + "/" + strType;
        if( !Process_Detect::isExistDir(directory1)) {
            QString errorMessage = "Faile to create " + directory1;
            throw std::exception(errorMessage.toStdString().c_str());
        }
        if( !Process_Detect::isExistDir(strImageHolesPath)) {
            QString errorMessage = "Faile to create " + strImageHolesPath;
            throw std::exception(errorMessage.toStdString().c_str());
        }
        QString ImageHolesPath2 = strImageHolesPath + "/" + QString::number(i) + ".jpg";
        WriteImage(procesHoleResult.HolesImage.SelectObj(i + 1), "jpg", 0, ImageHolesPath2.toUtf8().constData());
    }//for (int i = 0; i < CountSK; i++)
    holeresult.GlassWidth = procesHoleResult.GlassWidth.D();
    holeresult.GlassLength = procesHoleResult.GlassLength.D();
    holeresult.GlassAngle = 0;
    //
    // 写入轮廓图
    //
    QString strImageHolesLinePath = folderName + "/" + "孔示意图" + "/" + currentTimeJson.toString("hh-mm-ss");
    if( !Process_Detect::isExistDir(strImageHolesLinePath)) {
        QString errorMessage = "Faile to create " + strImageHolesLinePath;
        throw std::exception(errorMessage.toStdString().c_str());
    }
    QString ImageHolesPath1 = strImageHolesLinePath + "/" + "1.jpg";
    WriteImage(procesHoleResult.OutLineImage, "jpg", 0, ImageHolesPath1.toUtf8().constData());
    holeresult.ImageHolesLinePath = ImageHolesPath1;

    //
    // 写入json文件的地址
    //
    QString jsonFilePath = QDir::currentPath() + "/HolesInfJson/" + QString::number(currentTimeJson.toTime_t()) + ".json";
    holeresult.jsonFullPath = jsonFilePath;
    Process_Detect::writeHoleDataToJsonfile(holeresult);
}

void Process_Detect::Glassinfo(ProcessVisionAlgorithmResults result, GlassDataBaseInfo& baseinfo)
{
    baseinfo.id = result.GlassID;
    baseinfo.time = currentTimeJson.toString("yyyy-MM-dd hh:mm:ss");
    baseinfo.sizeOKorNG = "NG";
    HTuple Count;
    CountObj(result.ErrImage1, &Count);
    qDebug()<<"count:"<<Count.ToString().Text();
    if (Count > 0) {
        HTuple  hv_Indices_NG,hv_count_NG;
        HTuple  hv_Indices,hv_count;

        TupleFind(result.DefectLevel, "NG", &hv_Indices_NG);
        if (0 != (int(hv_Indices_NG!=-1))) {
           baseinfo.defectOKorNG = "NG";
        } else {
           baseinfo.defectOKorNG = "OK";
        }

        if (baseinfo.defectOKorNG == "OK" && baseinfo.sizeOKorNG == "OK") {
            baseinfo.OKorNG = "OK";
        } else {
            baseinfo.OKorNG = "NG";
        }

        baseinfo.length = result.GlassLength.D();
        baseinfo.width = result.GlassWidth.D();
        baseinfo.duijiaoxian1 = 0;
        baseinfo.duijiaoxian2 = 0;
        baseinfo.huashanNumber = 0;
        baseinfo.qipaoNumber = 0;
        baseinfo.benbianNumber = 0;
        baseinfo.zanwuNumber = 0;
        baseinfo.liewenNumber = 0;
        baseinfo.qitaNumber = 0;
        baseinfo.jieshiNumber = 0;
        baseinfo.defectNumber = 0;

        baseinfo.defectNumber = result.ErrName.Length();
        for(int i=0; i<result.ErrName.Length(); ++i) {
            if ( result.ErrName[i] == "划伤") {
                ++baseinfo.huashanNumber;
            } else if(result.ErrName[i] == "气泡") {
                ++baseinfo.qipaoNumber;
            } else if(result.ErrName[i] == "崩边") {
                ++baseinfo.benbianNumber;
            } else if(result.ErrName[i] == "脏污") {
                ++baseinfo.zanwuNumber;
            } else if(result.ErrName[i] == "裂纹") {
                ++baseinfo.liewenNumber;
            } else if(result.ErrName[i] == "结石") {
                ++baseinfo.jieshiNumber;
            } else if(result.ErrName[i] == "其它") {
                ++baseinfo.qitaNumber;
            }
        }
    } else {
        baseinfo.defectOKorNG = "OK";
        baseinfo.OKorNG = "OK";
        baseinfo.huashanNumber = 0;
        baseinfo.qipaoNumber = 0;
        baseinfo.benbianNumber = 0;
        baseinfo.zanwuNumber = 0;
        baseinfo.liewenNumber = 0;
        baseinfo.qitaNumber = 0;
        baseinfo.jieshiNumber = 0;
        baseinfo.duijiaoxian1 = 0;
        baseinfo.duijiaoxian2 = 0;
        baseinfo.width = 2500;
        baseinfo.length = 1200;
        baseinfo.defectNumber = 0;
    }
}

void Process_Detect::saveErrImage(ProcessVisionAlgorithmResults result, DefeteResult& defect)
{
    //玻璃ID，用于递增的
    defect.GlassID = Global::GlassID_INT;
    //
    // 根据当前时间构建文件名
    //
    QDateTime currentDateTime = QDateTime::currentDateTime();
    currentTimeJson = currentDateTime; //实时更新使用到
    defect.currentTime = currentDateTime;
    QString fileName = QString::number(currentDateTime.toTime_t()) + ".json";
    QString projectFolder = QDir::currentPath();// 获取当前项目文件夹路径
    QString jsonFilePath = projectFolder + "/DefectInfJson/" + fileName;
    defect.jsonFullPath = jsonFilePath;

    //保存缺陷小图
    HTuple Count;
    CountObj(result.ErrImage1, &Count);
    QString folderDefectImage = QString("D:/SaveDefectImage");
    if (!Process_Detect::isExistDir(folderDefectImage)) {
        QString errorMessage = "Faile to create " + folderDefectImage;
        throw std::exception(errorMessage.toStdString().c_str());
    }

    QString folderName = folderDefectImage+ "/" + currentDateTime.toString("yyyy-MM-dd");
    for (int i = 0; i < Count; i++) {
        DefeteData data;
        data.DefectID = i;
        if (!Process_Detect::isExistDir(folderName)) {
            QString errorMessage = "Faile to create " + folderName;
            throw std::exception(errorMessage.toStdString().c_str());
        }

        // Build the file name based on the current time
         QString CurrentTime = currentDateTime.toString("hh-mm-ss");
         data.Time = CurrentTime;

         QString strErrName = result.ErrName.TupleSelect(i).ToString().Text();
         data.DefectType = strErrName.remove("\"");//去除双层双引号

         QString strDefectLevel = result.DefectLevel.TupleSelect(i).ToString().Text();
         data.DetectLeve = strDefectLevel.remove("\"");;

         QString strErrX = result.ErrX.TupleSelect(i).ToString().Text();
         data.X = strErrX.toDouble();

         QString strErrY = result.ErrY.TupleSelect(i).ToString().Text();
         data.Y = strErrY.toDouble();

         QString strErrL = result.ErrL.TupleSelect(i).ToString().Text();
         data.Lenth = strErrL.toDouble();

         QString strErrW = result.ErrW.TupleSelect(i).ToString().Text();
         data.Width = strErrW.toDouble();

         QString strErrArea = result.ErrArea.TupleSelect(i).ToString().Text();
         data.Area = strErrArea.toDouble();

         QString strImageNGPath = folderName + "/" + strErrName + "/" + CurrentTime + "-" + QString::number(i + 1);
         data.ImageNGPath = strImageNGPath;

         defect.defetes.push_back(data);
         //
         // 缺陷坐标用于界面显示
         //
         FlawPoint Point;
         Point.x=strErrY.toDouble();
         Point.y=strErrX.toDouble();
         Point.FlawType= result.ErrType.TupleSelect(i).TupleInt();
         Point.HoleJsonFullPath = QDir::currentPath() + "/HolesInfJson/" + fileName;;
         Point.DefectJsonFullPath = jsonFilePath;
         Point.glassid = defect.GlassID;
         Points.append(Point);

         QString strErrNameDir = folderName + "/" + strErrName;
         if (!Process_Detect::isExistDir(strErrNameDir)) {
             QString errorMessage = "Faile to create " + strErrNameDir;
             throw std::exception(errorMessage.toStdString().c_str());
         }
         if (!Process_Detect::isExistDir(strImageNGPath)) {
             QString errorMessage = "Faile to create " + strImageNGPath;
             throw std::exception(errorMessage.toStdString().c_str());
         }

         QString ImageNGPath1 = strImageNGPath + "/" + "1.jpg";
         QString ImageNGPath2 = strImageNGPath + "/" + "2.jpg";
         QString ImageNGPath3 = strImageNGPath + "/" + "3.jpg";

         WriteImage(result.ErrImage1.SelectObj(i + 1), "jpg", 0, ImageNGPath1.toUtf8().constData());
         WriteImage(result.ErrImage2.SelectObj(i + 1), "jpg", 0, ImageNGPath2.toUtf8().constData());
         WriteImage(result.ErrImage3.SelectObj(i + 1), "jpg", 0, ImageNGPath3.toUtf8().constData());

#if false
         HObject jpgImage1 = result.ErrImage1.SelectObj(i + 1);
         HObject jpgImage2 = result.ErrImage2.SelectObj(i + 1);
         HObject jpgImage3 = result.ErrImage3.SelectObj(i + 1);
         std::tuple<QString, HObject> oneJpg = std::make_tuple(ImageNGPath1,jpgImage1);
         std::tuple<QString, HObject> twoJpg = std::make_tuple(ImageNGPath2,jpgImage2);
         std::tuple<QString, HObject> threeJpg = std::make_tuple(ImageNGPath3,jpgImage3);
         threadQueue.inqueue(oneJpg);
         threadQueue.inqueue(twoJpg);
         threadQueue.inqueue(threeJpg);
#endif
    }

    QString strGlassWidth = result.GlassWidth.ToString().Text();
    defect.GlassWidth = strGlassWidth.toDouble();

    QString strGlassLength = result.GlassLength.ToString().Text();
    defect.GlassLength = strGlassLength.toDouble();

    QString strGlassAngle = result.GlassAngle.ToString().Text();
    Global::RollerAngle = strGlassAngle.toDouble();
    defect.GlassAngle = strGlassAngle.toDouble();
}

void Process_Detect::funcSaveErrImage()
{
LOOP:
    if(!threadQueue.empty()) {  //队列不空则获取tuple保存图片
        std::tuple<QString, HObject> item;
        threadQueue.dequeue(item);
        auto imagePath = std::get<0>(item);
        auto image = std::get<1>(item);
        WriteImage(image, "jpg", 0, imagePath.toUtf8().constData());
    } else { //队列为空，则停顿100微秒
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (!hasStopThread.load())
        goto LOOP;
}

// 判断文件夹是否存在
bool Process_Detect::isExistDir(QString dirpath)
{
    QDir folderDir(dirpath);
    if (!folderDir.exists()) {
        if (!folderDir.mkpath(dirpath)) {
            qDebug() << "Failed to create directory"<<dirpath;
            return false;
        }
    }
    return true;
}

void Process_Detect::writeHoleDataToJsonfile(HoleResult holeresult)
{
    //
    // 每块玻璃单独一个文件
    //
    try{
        Json::Value root;
        Json::Value glassholedata;
        for(int i=0; i<(int)holeresult.holes.size(); ++i) {
            HoleData temp = holeresult.holes[i];
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
        glassholedata["GlassLength"] = holeresult.GlassLength;
        glassholedata["GlassAngle"] = holeresult.GlassAngle;
        glassholedata["GlassWidth"] = holeresult.GlassWidth;
        glassholedata["ImageHolesLinePath"] = holeresult.ImageHolesLinePath.toStdString().c_str();
        root[QString::number(holeresult.GlassID).toStdString().c_str()] = glassholedata;

        Json::StreamWriterBuilder jswBuilder;
        jswBuilder["emitUTF8"] = true;//中文转换
        std::unique_ptr<Json::StreamWriter> jsWriter(jswBuilder.newStreamWriter());
        std::ofstream ofs;
        ofs.open(holeresult.jsonFullPath.toStdString().data());
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

void Process_Detect::SummaryFailResult()
{
    //异常数据输出
    summaryResult.GlassNum = summaryResult.GlassNum + 1;
    summaryResult.ngNum = summaryResult.ngNum + 1;
    summaryResult.unsorted = summaryResult.unsorted + 1;
    summaryResult.exceptNum = summaryResult.exceptNum + 1;
    summaryResult.currentOKorNG = false; //当前玻璃OK或者NG
    summaryResult.currentSort = false;   //当前玻璃是否分拣
    summaryResult.suceessRate = (double)summaryResult.okNum / (double)summaryResult.GlassNum;

    //检测结果刷新
    emit sig_UpdateResultInfo(summaryResult);
    Global::GlassID_INT = Global::GlassID_INT + 1; //玻璃id加1
}

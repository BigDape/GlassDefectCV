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
    Points = QList<FlawPoint>();
    baseinfo = GlassDataBaseInfo();
    YCoordIn= 0;
    YCoordOut = HTuple();
    //
    // 声明halcon脚本引擎
    //
    engine = new HDevEngine();
    engine->SetEngineAttribute("docu_language", "zh_CN");
    engine_path = "D:/GlassDefectCV/HalconFunction";
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
            qDebug()<<"VisionProcess start:"<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
            Process_Detect::VisionProcess(args.imageunit, args.holeunit);
            qDebug()<<"VisionProcess end:"<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
        }
    }
    if (!hasStopThread.load())
        goto PDLOOP;
}

//算法执行
void Process_Detect::VisionProcess(ImageUnit imageunit, HoleUnit holeunit)
{
    if (Global::isOffline == false && Global::SystemStatus == 0) return;
    //recipe切换
    if(Global::RecChangeSignal) {
        Global::RecChangeSignal = false;
    }

    HTuple UserDefinedDict;
    GetDictTuple(Global::RecipeDict,"自定义参数",&UserDefinedDict);
    if(imageunit.ProcessStep==1 || imageunit.GlassPositionInf==1 || imageunit.GlassPositionInf==0) {//玻璃部分，1头2中3尾0完整玻璃
        ErrFlag = false;
        //判断上一片玻璃结果是否输出
        if(ResultNotOutFlag) {
            Process_Detect::SummaryFailResult();// 输出结果
            ResultNotOutFlag = false;
        }
        Global::AlmLightSignal = true;
        Global::AlmLightVal = 0;
    }
    qDebug() << "ProcessStep :" << imageunit.ProcessStep;

    //
    // 对一帧图像开始缺陷检测
    //
    ProcessVisionAlgorithmResults processvisionresult;//算法执行结果
    std::shared_ptr<std::thread> thExe = nullptr;
    std::shared_ptr<std::thread> thExe2 = nullptr;
    HTuple EnableDefect;
    GetDictTuple(UserDefinedDict,"缺陷检测启用",&EnableDefect);
    if( EnableDefect==1 ) {
        //图像正常执行算法or输出异常提醒
        if(imageunit.ImageList.CountObj() > 0 && imageunit.ErrorFlag == false) {
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
                if(imageunit.GlassPositionInf==1 || imageunit.GlassPositionInf==0) {
                    Global::jsonTime = QDateTime::currentDateTime();//第一帧/完整玻璃的时候刷新时间
                    HTuple a=0;
                    YCoordIn= a ;
                } else {
                    YCoordIn= YCoordOut;
                }
                procedurecall->SetInputCtrlParamTuple("VisionProcessStep", imageunit.ProcessStep);
                procedurecall->SetInputCtrlParamTuple("GlassPositionInf", imageunit.GlassPositionInf);
                procedurecall->SetInputCtrlParamTuple("YCoordIn", YCoordIn);
                procedurecall->SetInputCtrlParamTuple("DetectDict", Global::RecipeDict);
                procedurecall->Execute();//耗时多
                qDebug()<<"VisionProcess Execute:"<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
                //获取算法结果
                processvisionresult.GlassID = Global::GlassID_INT;
                processvisionresult.time = Global::jsonTime.toString("yyyy-MM-dd hh:mm:ss");
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
                YCoordOut = processvisionresult.YCoordOut;//用于第二帧参数，否则Y坐标获取不到
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
                //陷入处理线程
                thExe = std::make_shared<std::thread>(&Process_Detect::saveErrImage, this,processvisionresult);                              //耗时多
                Process_Detect::Glassinfo(processvisionresult,baseinfo);
                emit sendData(baseinfo); //信息统计表格中插入一行数据，每帧都刷新
                qDebug()<<"ProcessStep"<<imageunit.ProcessStep;
                qDebug()<<"m_FramesPerTri"<<Global::FramesPerTri;
                QString info="ProcessStep" + QString::number(imageunit.ProcessStep)  + "算法执行完成！";
                log_singleton::Write_Log(info, Log_Level::General);
            } catch (HalconCpp::HException& Except) {
                ErrFlag = true;
                qDebug() << "Hole HalconHalconErr:" << Except.ErrorMessage().Text();
                qDebug() << "123 Halcon error:" <<Except.ProcName().Text();
                QString info= "算法执行异常！";
                log_singleton::Write_Log(info, Log_Level::General);
            }//try
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
    HoleResult holeresult;
    qDebug()<<"imageunit.GlassPositionInf = "<<imageunit.GlassPositionInf;
    if (imageunit.GlassPositionInf==0 || imageunit.GlassPositionInf==3 ) {
        HTuple EnableMeasure;
        GetDictTuple(UserDefinedDict,"尺寸测量启用",&EnableMeasure);
        qDebug() << "EnableMeasure :" << EnableMeasure.ToString().Text();
        if(EnableMeasure == 1) {
            thExe2 = std::make_shared<std::thread>(&Process_Detect::saveHoleImage, this,holeunit);
            qDebug()<<"VisionProcess saveHoleImage:"<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
        }
    }
    //
    // 处理缺陷算子结果的同时计算孔洞的数据
    //
    if(thExe!=nullptr) {//等待缺陷检测处理线程结束，获取结果
        if(thExe->joinable())
            thExe->join();
    }
    Global::GlobalLock.lock();
    emit sig_sendPoint(Points);                                                                 //发送显示缺陷点位置信号
    Global::GlobalLock.unlock();
    if(thExe2 != nullptr) {//等待尺寸检测处理线程结束，获取结果
        if(thExe2->joinable())
            thExe2->join();
    }
    ResultNotOutFlag = true;
    if (imageunit.GlassPositionInf==0 || imageunit.GlassPositionInf==3 ) {
        Process_Detect::SummaryResults(baseinfo);
        ResultNotOutFlag = false;
    }
}

void Process_Detect::saveHoleImage(HoleUnit holeunit)
{
    HTuple NumTile;
    CountObj(holeunit.ImageTile1R,&NumTile);
    ProcessHolesAlgorithmResults procesHoleResult;
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
        procesHoleResult.GlassID = Global::GlassID_INT;
        procesHoleResult.HolesImage.GenEmptyObj();
        procesHoleResult.OutLineImage.GenEmptyObj();
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
    //
    // 解析算法结果数据并写入json文件中
    //
    HoleResult holeresult;//解析后的结果
    holeresult.GlassID = procesHoleResult.GlassID;
    HTuple CountSK;
    CountObj(procesHoleResult.HolesImage, &CountSK);
    qDebug()<<"procesHoleResult.HolesImage count2:"<<CountSK.ToString().Text();
    QString folderName = QString("D:/SaveDefectImage/") + Global::jsonTime.toString("yyyy-MM-dd");
    for (int i = 0; i < CountSK; i++) {
        HoleData hole;
        hole.HolesID = i+1;
        hole.Time = Global::jsonTime.toString("hh-mm-ss");
        QString strType = procesHoleResult.Type.TupleSelect(i).ToString().Text();
        strType = strType.remove("\"");
        hole.Type = strType;
        QString strHolesOK = procesHoleResult.HolesOK.TupleSelect(i).ToString().Text();
        strHolesOK = strHolesOK.remove("\"");
        hole.HolesLeve = strHolesOK;
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

        QString strImageHolesPath = folderName + "/" + "孔" + "/" + Global::jsonTime.toString("yyyy-MM-dd");
        hole.ImageHolesPath = strImageHolesPath;
        holeresult.holes.push_back(hole);
        //存小图
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

    // 写入轮廓图
    QString strImageHolesLinePath = folderName + "/" + "孔示意图" + "/" + Global::jsonTime.toString("hh-mm-ss");
    if( !Process_Detect::isExistDir(strImageHolesLinePath)) {
        QString errorMessage = "Faile to create " + strImageHolesLinePath;
        throw std::exception(errorMessage.toStdString().c_str());
    }
    QString ImageHolesPath1 = strImageHolesLinePath + "/" + "1.jpg";
    WriteImage(procesHoleResult.OutLineImage, "jpg", 0, ImageHolesPath1.toUtf8().constData());
    holeresult.ImageHolesLinePath = ImageHolesPath1;

    //写入json文件的地址
    QString path = QDir::currentPath() + "/HolesInfJson/" + QString::number(Global::jsonTime.toTime_t()) + ".json";
    holeresult.jsonFullPath = path;
    qDebug()<<"holeresult.jsonFullPath ="<<holeresult.jsonFullPath;
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

    emit sig_updateFlaw(procesHoleResult.GlassWidth.D(),procesHoleResult.GlassLength.D());  //画出最外围轮廓
    emit sig_refreshSize(holeresult.jsonFullPath,holeresult.GlassID);                       //刷新尺寸
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
    baseinfo = GlassDataBaseInfo();

    QString info="玻璃ID" + QString::number(baseinfo.id)  + "算法执行完成！";
    log_singleton::Write_Log(info, Log_Level::General);
}


void Process_Detect::Glassinfo(ProcessVisionAlgorithmResults result, GlassDataBaseInfo& baseinfo)
{
    baseinfo.id = result.GlassID;
    baseinfo.time = Global::jsonTime.toString("yyyy-MM-dd hh:mm:ss");
    baseinfo.sizeOKorNG = "OK";//后面待修改
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

        baseinfo.defectNumber = baseinfo.defectNumber + result.ErrName.Length();
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
    }
}

void Process_Detect::saveErrImage(ProcessVisionAlgorithmResults result)
{
    //
    // 多线程函数，注意线程安全！！！！
    //
    DefeteResult defect;//解析出来的结果
    //玻璃ID，用于递增的
    defect.GlassID = Global::GlassID_INT;
    //
    // 根据当前时间构建文件名
    //
    defect.currentTime = Global::jsonTime;
    QString fileName = QString::number(Global::jsonTime.toTime_t()) + ".json";
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

    QString folderName = folderDefectImage+ "/" + Global::jsonTime.toString("yyyy-MM-dd");
    for (int i = 0; i < Count; i++) {
         DefeteData data;
         data.DefectID = i;
         data.Time = Global::jsonTime.toString("hh-mm-ss");
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
         QString strImageNGPath = folderName + "/" + strErrName + "/" + data.Time + "-" + QString::number(i + 1);
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
         Global::GlobalLock.lock();
         Points.append(Point);
         Global::GlobalLock.unlock();
         QString strErrNameDir = folderName + "/" + strErrName;
         if (!Process_Detect::isExistDir(strImageNGPath)) {
             QString errorMessage = "Faile to create " + strImageNGPath;
             throw std::exception(errorMessage.toStdString().c_str());
         }

         HalconCpp::HObject imag1 = result.ErrImage1.SelectObj(i + 1);
         HalconCpp::HObject imag2 = result.ErrImage2.SelectObj(i + 1);
         HalconCpp::HObject imag3 = result.ErrImage3.SelectObj(i + 1);
         QString ImageNGPath1 = strImageNGPath + "/" + "1.jpg";
         QString ImageNGPath2 = strImageNGPath + "/" + "2.jpg";
         QString ImageNGPath3 = strImageNGPath + "/" + "3.jpg";
         //
         // 多线程写入图片，加快速度
         //
         std::thread th1(&Process_Detect::writeImage,this,imag1,imag2,imag3,ImageNGPath1,ImageNGPath2,ImageNGPath3);
         th1.detach();
    }
    QString strGlassWidth = result.GlassWidth.ToString().Text();
    defect.GlassWidth = strGlassWidth.toDouble();

    QString strGlassLength = result.GlassLength.ToString().Text();
    defect.GlassLength = strGlassLength.toDouble();

    QString strGlassAngle = result.GlassAngle.ToString().Text();
    Global::RollerAngle = strGlassAngle.toDouble();
    defect.GlassAngle = strGlassAngle.toDouble();

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
        qDebug()<<__FUNCTION__<<"jsonFullPath="<<defect.jsonFullPath;
        if (file.exists()) {
            std::ifstream ifs;
            ifs.open(defect.jsonFullPath.toStdString().data()); // Windows自己注意路径吧
            if (ifs.is_open()) {
                Json::Reader reader;
                // 解析到root，root将包含Json里所有子元素
                reader.parse(ifs, root, false);
                ifs.close();
                precount = root[QString::number(result.GlassID).toStdString().c_str()].size() - 3;//减去宽度、长度、角度
                qDebug()<<"precount = " <<precount;
            } else {
                qDebug()<<__FUNCTION__<<" ifs.is_open() =  false";
            }
        }
        // 添加新数据
        Json::Value glassdata;
        if (precount != 0) {
            glassdata = root[QString::number(result.GlassID).toStdString().c_str()];
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
        root[QString::number(result.GlassID).toStdString().c_str()] = glassdata;

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
    emit sig_updateFlaw(result.GlassWidth.D(),result.GlassLength.D());                          //画出最外围轮廓,每次都刷新
    emit sig_refreshFlaw(defect.jsonFullPath,defect.GlassID);                                   //更新缺陷小图
    qDebug()<<"result.GlassWidth.D() ="<<result.GlassWidth.D() <<"result.GlassLength.D() ="<<result.GlassLength.D();

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

void Process_Detect::SummaryFailResult()
{
    qDebug()<<__FUNCTION__<<" has down";
    //异常数据输出
    summaryResult.GlassNum = summaryResult.GlassNum + 1;
    summaryResult.ngNum = summaryResult.ngNum + 1;
    summaryResult.unsorted = summaryResult.unsorted + 1;
    summaryResult.exceptNum = summaryResult.exceptNum + 1;
    summaryResult.currentOKorNG = false; //当前玻璃OK或者NG
    summaryResult.currentSort = false;   //当前玻璃是否分拣
    summaryResult.suceessRate = (double)summaryResult.okNum / (double)summaryResult.GlassNum;
    Points.clear();
    baseinfo = GlassDataBaseInfo();
    //检测结果刷新
    emit sig_UpdateResultInfo(summaryResult);
    Global::GlassID_INT = Global::GlassID_INT + 1; //玻璃id加1
}

void Process_Detect::writeImage(HalconCpp::HObject imag1,
                                HalconCpp::HObject imag2,
                                HalconCpp::HObject imag3,
                                QString ImageNGPath1,
                                QString ImageNGPath2,
                                QString ImageNGPath3)
{
    WriteImage(imag1, "jpg", 0, ImageNGPath1.toUtf8().constData());
    WriteImage(imag2, "jpg", 0, ImageNGPath2.toUtf8().constData());
    WriteImage(imag3, "jpg", 0, ImageNGPath3.toUtf8().constData());
}

void Process_Detect::sortHole()
{
#if false
    int typeLength = Type.TupleLength().I();
    int HolesOKLength =  HolesOK.TupleLength().I();
    int DistanceHorizontalLength =  DistanceHorizontal.TupleLength().I();
    int DistanceVerticalLength =  DistanceVertical.TupleLength().I();
    int HolesWidthLength =  HolesWidth.TupleLength().I();
    int HolesHeightLength =  HolesHeight.TupleLength().I();
    int column2QKLength = Column2QK.TupleLength().I();
    int row2QKLength = Row2QK.TupleLength().I();
    qDebug()<<"typeLength ="<<typeLength;
    qDebug()<<"HolesOKLength ="<<HolesOKLength;
    qDebug()<<"DistanceHorizontalLength ="<<DistanceHorizontalLength;
    qDebug()<<"DistanceVerticalLength ="<<DistanceVerticalLength;
    qDebug()<<"HolesWidthLength = "<<HolesWidthLength;
    qDebug()<<"HolesHeightLength ="<<HolesHeightLength;
    qDebug()<<"column2QKLength ="<<column2QKLength;
    qDebug()<<"row2QKLength ="<<row2QKLength;
 if(column2QKLength == row2QKLength
         && column2QKLength == typeLength
         && column2QKLength == HolesOKLength
         && column2QKLength == DistanceHorizontalLength
         && column2QKLength == DistanceVerticalLength
         && column2QKLength == HolesWidthLength
         && column2QKLength == HolesHeightLength){//数组具有一致性
    int holeCount = 0; //统计孔的个数
    for(int i = 0; i<Type.TupleLength(); ++i) {
        QString type = Type.TupleSelect(i).ToString().Text();
        qDebug()<<"type ="<<type <<"=>i="<<i;
        if(type.contains("孔"))
            ++holeCount;
    }
    if(holeCount != 0) {
        HTuple holeColumn2QK = HTuple();
        TupleSelectRange(Column2QK,0,holeCount-1,&holeColumn2QK);//孔的数组单独提取出来
        qDebug()<<"holeColumn2QK.TupleLength() =" <<holeColumn2QK.TupleLength().I();
        HTuple holeColumn2QKIndex = HTuple();
        TupleSortIndex(holeColumn2QK,&holeColumn2QKIndex);//升序排好的下标

        HTuple NewType = HTuple();
        HTuple NewHolesOK =  HTuple();
        HTuple NewDistanceHorizontal =  HTuple();
        HTuple NewDistanceVertical =  HTuple();
        HTuple NewHolesWidth =  HTuple();
        HTuple NewHolesHeight =  HTuple();
        HTuple NewColumn2QK =  HTuple();
        HTuple NewRow2QK =  HTuple();
        //
        // 按照x坐标的升序排列好孔的其他属性
        //
        TupleSelect(Type,holeColumn2QKIndex,&NewType);
        TupleSelect(HolesOK,holeColumn2QKIndex,&NewHolesOK);
        TupleSelect(DistanceHorizontal,holeColumn2QKIndex,&NewDistanceHorizontal);
        TupleSelect(DistanceVertical,holeColumn2QKIndex,&NewDistanceVertical);
        TupleSelect(HolesWidth,holeColumn2QKIndex,&NewHolesWidth);
        TupleSelect(HolesHeight,holeColumn2QKIndex,&HolesHeight);
        TupleSelect(Column2QK,holeColumn2QKIndex,&NewColumn2QK);
        TupleSelect(Row2QK,holeColumn2QKIndex,&NewRow2QK);

        HTuple RemainType = HTuple();
        HTuple RemainHolesOK =  HTuple();
        HTuple RemainDistanceHorizontal =  HTuple();
        HTuple RemainDistanceVertical =  HTuple();
        HTuple RemainHolesWidth =  HTuple();
        HTuple RemainHolesHeight =  HTuple();
        HTuple RemainColumn2QK =  HTuple();
        HTuple RemainRow2QK =  HTuple();
        //
        // 获取除了孔之外的其他坐标，暂不排序
        //
        TupleSelectRange(Type,holeCount,Type.TupleLength().I()-1,&RemainType);
        TupleSelectRange(HolesOK,holeCount,HolesOK.TupleLength().I()-1,&RemainHolesOK);
        TupleSelectRange(DistanceHorizontal,holeCount,DistanceHorizontal.TupleLength().I()-1,&RemainDistanceHorizontal);
        TupleSelectRange(DistanceVertical,holeCount,DistanceVertical.TupleLength().I()-1,&RemainDistanceVertical);
        TupleSelectRange(HolesWidth,holeCount,HolesWidth.TupleLength().I()-1,&RemainHolesWidth);
        TupleSelectRange(HolesHeight,holeCount,HolesHeight.TupleLength().I()-1,&RemainHolesHeight);
        TupleSelectRange(Column2QK,holeCount,Column2QK.TupleLength().I()-1,&RemainColumn2QK);
        TupleSelectRange(Row2QK,holeCount,Row2QK.TupleLength().I()-1,&RemainRow2QK);
        //
        // 将排好序的孔+剩下的合并，赋值给原来的数组
        //
        TupleConcat(NewType,RemainType,&Type);
        TupleConcat(NewHolesOK,RemainHolesOK,&HolesOK);
        TupleConcat(NewDistanceHorizontal,RemainDistanceHorizontal,&DistanceHorizontal);
        TupleConcat(NewDistanceVertical,RemainDistanceVertical,&DistanceVertical);
        TupleConcat(NewHolesWidth,RemainHolesWidth,&HolesWidth);
        TupleConcat(NewHolesHeight,RemainHolesHeight,&HolesHeight);
        TupleConcat(NewColumn2QK,RemainColumn2QK,&Column2QK);
        TupleConcat(NewRow2QK,RemainRow2QK,&Row2QK);
    }//if(holeCount != 0)
  }
#endif
}


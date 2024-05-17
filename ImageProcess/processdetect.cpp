﻿#include "processdetect.h"
//#include "devicecamera.h"
#include "processtile.h"
#include "Global.h"
#include <algorithm>
#pragma execution_character_set("utf-8")
Process_Detect::Process_Detect()
{
    init_detect();
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

//初始化
void Process_Detect::init_detect()
{
//    Point=new FlawPoint();
    ResultNotOutFlag=false;
    ErrCount=0;
    LastErrFlag=false;
    ErrFlag=false;
    GlassPosition=0;
    Points=new QList<FlawPoint>();
    result = new ResultINFO;
    result->ngNum=0;
    result->okNum=0;
    result->sorted=0;
    result->GlassNum=0;
    result->passRate=0;
    result->unsorted=0;
    result->exceptNum=0;
    LastDefectCount=0;
    result->pre_result="NG";
    result->sort_result="OK";
    sig_light=0;
    Qlist_Result.clear();
    stopFlag_Detect=false;
    DetectStep = 0;
    ProcessStep = 0;
    m_FramesPerTri=0;
    LastProcessStep = 0;
    GenEmptyObj(&ErrImage1);
    GenEmptyObj(&ErrImage2);
    GenEmptyObj(&ErrImage3);
    GenEmptyObj(&OutLineImage);
    GenEmptyObj(&HolesImage);
    procedure = nullptr;
    procedurecall = nullptr;
    procedure2 = nullptr;
    procedurecall2 = nullptr;
    ResultDict = HTuple();
    ResultDictHoles = HTuple();
    ErrName = HTuple();
    DefectLevel = HTuple();
    ErrX = HTuple();
    ErrY = HTuple();
    ErrW = HTuple();
    ErrL = HTuple();    
    ErrArea = HTuple();
    GlassLength = HTuple();
    GlassWidth = HTuple();
    GlassAngle = HTuple();
    YCoordIn= 0;
    YCoordOut = HTuple();
    engine = new HDevEngine();
    engine->SetEngineAttribute("docu_language", "zh_CN");
    engine_path = "D:/HalconFunction/";
    engine->AddProcedurePath(engine_path.toLatin1().data());
    procedure = new HDevProcedure("ProcessVision");
    procedurecall = new HDevProcedureCall(*procedure);
    procedure2 = new HDevProcedure("ProcessHoles");
    procedurecall2 = new HDevProcedureCall(*procedure2);
}

void Process_Detect::update_result(bool a)
{
    if(a) {
       result->GlassNum++;
       result->okNum++;
       result->unsorted++;
       result->passRate=result->okNum/result->GlassNum;
       result->pre_result = true;
    } else {
        result->GlassNum++;
        result->ngNum++;
        result->unsorted++;
        result->passRate=result->okNum/result->GlassNum;
        result->pre_result = false;
    }
}
//算法执行
void Process_Detect::VisionProcess()
{
    ResultDataJson = new JsonResultParse();
    ginfo = new GLASSINFO;
    while (true) {
            switch (DetectStep) {
            case 0:
                if (ProcessTile::ImageQueue.size() != 0) {
                    //recipe切换
                    if(Global::RecChangeSignal)
                    {
                       LastProcessStep = 0;
                       Global::RecChangeSignal=false;
                    }

                    qDebug() << "start1 :" << QDateTime::currentDateTime().toString("HH:mm:ss.zzz");

                    GetDictTuple(Global::RecipeDict,"编码器参数",&Code);

                    GetDictTuple(Code,"编码器单位刻度对应距离",&CodePerScale);
//                  ReadDict("D:/HalconFunction/DuMo3.2.hdict", HTuple(), HTuple(), &RecipeDict);


                    qDebug()<<"编码器单位刻度对应距离:"<<CodePerScale.ToString().Text();
                    DetectStep = 10;
                }
                break;
            case 10:
                ProcessStep = ProcessTile::ImageQueue.head().ProcessStep;
                GlassPosition=ProcessTile::ImageQueue.head().GlassPositionInf;
                m_FramesPerTri=Global::FramesPerTri;
                HTuple UserDefinedDict;
                GetDictTuple(Global::RecipeDict,"自定义参数",&UserDefinedDict);
                if(ProcessStep==1 || GlassPosition==1 || GlassPosition==0)
                {                    
                    ErrFlag=false;
                    //判断上一片玻璃结果是否输出
                    if(ResultNotOutFlag)
                    {
                       // 输出结果
                        SummaryResults();
                        ResultNotOutFlag=false;
                    }
                    Global::AlmLightSignal=true;
                    Global::AlmLightVal=0;
                }
                qDebug() << "ProcessStep :" << ProcessStep;
                qDebug() << "LastProcessStep :" << LastProcessStep;
                HTuple EnableDefect;
                GetDictTuple(UserDefinedDict,"缺陷检测启用",&EnableDefect);
                if(EnableDefect==1) {
                    //图像正常执行算法or输出异常提醒
                    if(ProcessTile::ImageQueue.head().ImageList.CountObj()>0 && ProcessTile::ImageQueue.head().ErrorFlag==false)
                    {
                        bool EnableDefect=true;
                        if(EnableDefect)
                        {

                               try {
                                    HObject SelectObj1,SelectObj2,SelectObj3;
                                    SelectObj(ProcessTile::ImageQueue.head().ImageList,&SelectObj1,1);
                                    SelectObj(ProcessTile::ImageQueue.head().ImageList,&SelectObj2,2);
                                    SelectObj(ProcessTile::ImageQueue.head().ImageList,&SelectObj3,3);

                                    procedurecall->SetInputIconicParamObject("Image1", SelectObj1);
                                    procedurecall->SetInputIconicParamObject("Image2", SelectObj2);
                                    procedurecall->SetInputIconicParamObject("Image3", SelectObj3);
                                    procedurecall->SetInputIconicParamObject("GlassRegion", ProcessTile::ImageQueue.head().ImageRegion);
                                    procedurecall->SetInputIconicParamObject("FrameRegion", ProcessTile::ImageQueue.head().FrameRegion);
                                    if(GlassPosition==1 || GlassPosition==0)
                                    {
                                        HTuple a=0;
                                        YCoordIn= a ;
                                    }
                                    else
                                    {
                                        YCoordIn= YCoordOut;
                                    }
                                    procedurecall->SetInputCtrlParamTuple("VisionProcessStep", ProcessStep);
                                    procedurecall->SetInputCtrlParamTuple("GlassPositionInf", GlassPosition);
                                    procedurecall->SetInputCtrlParamTuple("YCoordIn", YCoordIn);
                                    procedurecall->SetInputCtrlParamTuple("DetectDict", Global::RecipeDict);
                                    procedurecall->Execute();
                                    SelectObj1.Clear();
                                    SelectObj2.Clear();
                                    SelectObj3.Clear();

                                    ErrImage1=procedurecall->GetOutputIconicParamObject("ErrImage1");
                                    ErrImage2=procedurecall->GetOutputIconicParamObject("ErrImage2");
                                    ErrImage3=procedurecall->GetOutputIconicParamObject("ErrImage3");

                                    //获取缺陷参数
                                    ResultDict = procedurecall->GetOutputCtrlParamTuple("ResultDict");
    //                                GlassLength = ResultDict.TupleGetDictTuple("GlassLength");
    //                                GlassWidth = ResultDict.TupleGetDictTuple("GlassWidth");
    //                                GlassLength = 2000;
    //                                GlassWidth = 1000;
                                    ErrName = ResultDict.TupleGetDictTuple("ErrName");
                                    ErrType = ResultDict.TupleGetDictTuple("ErrType");
                                    DefectLevel = ResultDict.TupleGetDictTuple("DefectLevel");
                                    ErrX = ResultDict.TupleGetDictTuple("ErrX");
                                    ErrY = ResultDict.TupleGetDictTuple("ErrY");
                                    ErrW = ResultDict.TupleGetDictTuple("ErrW");
                                    ErrL = ResultDict.TupleGetDictTuple("ErrH");
                                    ErrArea = ResultDict.TupleGetDictTuple("ErrArea");
                                    YCoordOut=procedurecall->GetOutputCtrlParamTuple("YCoordOut");
                                    GlassLength=procedurecall->GetOutputCtrlParamTuple("GlassLength");
                                    GlassWidth=procedurecall->GetOutputCtrlParamTuple("GlassWidth");
                                    GlassAngle=procedurecall->GetOutputCtrlParamTuple("GlassAngle");
                                    //获取轮廓点object
                                    XValues = procedurecall->GetOutputCtrlParamTuple("Col_x");
                                    YValues = procedurecall->GetOutputCtrlParamTuple("Row_y");
                                    qDebug()<<"XValues:"<<XValues.Length();
                                    if ( XValues.Length() == YValues.Length() ) {
                                        Global::courtourMapXY.clear();
                                        for (int ii = 0; ii < XValues.Length(); ii = ii +12) {
                                            QString xx = XValues.TupleSelect(ii).ToString().Text();
                                            QString yy = YValues.TupleSelect(ii).ToString().Text();
                                            CourTour tour;
                                            tour.index = ii;
                                            tour.x = xx;
                                            tour.y = yy;
                                            Global::courtourMapXY.push_back(tour);
                                         }
                                    }

                                    HTuple Count;
                                    CountObj(ErrImage1, &Count);
                                    if(Count>0)
                                    {
                                        QString folderDefectImage = QString("E:/SaveDefectImage");
                                        QDir directory(folderDefectImage);
                                        // 判断存储小图文件夹是否存在
                                        QDir folderDir(folderDefectImage);
                                        if (folderDir.exists()) {
                                            qDebug() << "Folder" << folderDefectImage << "exists.";
                                        } else {
                                            if (directory.mkpath(folderDefectImage)) {
                                                qDebug() << "Directory"
                                                         << "created.";
                                            } else {
                                                qDebug() << "Failed to create directory";
                                            }
                                        }
                                        qDebug() << "P2 :" << QDateTime::currentDateTime().toString("HH:mm:ss.zzz");


                                        // Get the current time
                                        QDateTime currentDateTime = QDateTime::currentDateTime();
                                        QString folderName = QString("D:/SaveDefectImage/") + currentDateTime.toString("yyyy-MM-dd");
                                        //获取已检出缺陷个数
                                        LastDefectCount=ResultDataJson->ResultData.DefectID.length();
                                        qDebug() << "LastDefectCount:"<<LastDefectCount;
                                        for (int i = 0; i < Count; i++) {
                                            QDir directory(folderName);
                                            // 判断文件夹是否存在
                                            QDir folderDir(folderName);
                                            if (folderDir.exists()) {
                                                qDebug() << "Folder" << folderName << "exists.";
                                            } else {
                                                if (directory.mkpath(folderName)) {
                                                    qDebug() << "Directory"
                                                             << "created.";
                                                } else {
                                                    qDebug() << "Failed to create directory";
                                                }
                                            }

                                            //      ResultDataJson->ResultData.GlassID
                                            // Build the file name based on the current time
                                            QString CurrentTime = currentDateTime.toString("hh-mm-ss");
                                            ResultDataJson->ResultData.Time = CurrentTime;
                                            QString strErrName = ErrName.TupleSelect(i).ToString().Text();
                                            strErrName = strErrName.remove("\"");
                                            QString strDefectLevel = DefectLevel.TupleSelect(i).ToString().Text();
                                            strDefectLevel = strDefectLevel.remove("\"");
                                            QString strErrX = ErrX.TupleSelect(i).ToString().Text();
                                            strErrX = strErrX.remove("\"");
                                            QString strErrY = ErrY.TupleSelect(i).ToString().Text();
                                            strErrY = strErrY.remove("\"");
                                            QString strErrL = ErrL.TupleSelect(i).ToString().Text();
                                            strErrL = strErrL.remove("\"");
                                            QString strErrW = ErrW.TupleSelect(i).ToString().Text();
                                            strErrW = strErrW.remove("\"");
                                            QString strErrArea = ErrArea.TupleSelect(i).ToString().Text();
                                            strErrArea = strErrArea.remove("\"");
    //

                                            ResultDataJson->ResultData.DefectID.append(QString::number(LastDefectCount+i + 1));

                                            ResultDataJson->ResultData.DefectType.append(strErrName);

                                            ResultDataJson->ResultData.DefectLeve.append(strDefectLevel);
                                            ResultDataJson->ResultData.Y.append(strErrY);
                                            ResultDataJson->ResultData.X.append(strErrX);
                                            ResultDataJson->ResultData.Lenth.append(strErrL);
                                            ResultDataJson->ResultData.Width.append(strErrW);
                                            ResultDataJson->ResultData.Area.append(strErrArea);
                                            QString strImageNGPath = folderName + "/" + strErrName + "/" + CurrentTime + "-" + QString::number(LastDefectCount+i + 1);
                                            ResultDataJson->ResultData.ImageNGPath.append(strImageNGPath);
                                            FlawPoint Point;
                                            Point.x=strErrY.toDouble();
                                            Point.y=strErrX.toDouble();
                                            Point.FlawType=ErrType.TupleSelect(i).TupleInt();
                                            Points->append(Point);
                                            // 发送数据
                                            //   emit resultReady(ResultDataJson->ResultData);
                                            //存小图
                                            QDir directory1(folderName + "/" + strErrName);
                                            if (directory1.exists()) {
                                                qDebug() << "Directory"
                                                         << "already exists.";
                                            } else {
                                                // Create the directory
                                                if (directory1.mkpath(folderName + "/" + strErrName)) {
                                                    qDebug() << "Directory"
                                                             << "created.";
                                                } else {
                                                    qDebug() << "Failed to create directory";
                                                }
                                            }
                                            QDir directory2(strImageNGPath);
                                            if (directory2.exists()) {
                                                qDebug() << "Directory"
                                                         << "already exists.";
                                            } else {
                                                // Create the directory
                                                if (directory2.mkpath(strImageNGPath)) {
                                                    qDebug() << "Directory"
                                                             << "created.";
                                                } else {
                                                    qDebug() << "Failed to create directory";
                                                }
                                            }
                                            QString ImageNGPath1 = strImageNGPath + "/" + strErrName + "1.jpg";
                                            QString ImageNGPath2 = strImageNGPath + "/" + strErrName + "2.jpg";
                                            QString ImageNGPath3 = strImageNGPath + "/" + strErrName + "3.jpg";

                                            WriteImage(ErrImage1.SelectObj(i + 1), "jpg", 0, ImageNGPath1.toUtf8().constData());
                                            WriteImage(ErrImage2.SelectObj(i + 1), "jpg", 0, ImageNGPath2.toUtf8().constData());
                                            WriteImage(ErrImage3.SelectObj(i + 1), "jpg", 0, ImageNGPath3.toUtf8().constData());
                                        }
                                 }
                                     QString strGlassWidth = GlassWidth.ToString().Text();
                                     strGlassWidth = strGlassWidth.remove("\"");
                                     QString strGlassLength = GlassLength.ToString().Text();
                                     strGlassLength = strGlassLength.remove("\"");
                                     QString strGlassAngle = GlassAngle.ToString().Text();
                                     qDebug()<<"strGlassAngle ="<<strGlassAngle;

                                     ResultDataJson->ResultData.GlassWidth.clear();
                                     ResultDataJson->ResultData.GlassLength.clear();
                                     ResultDataJson->ResultData.GlassWidth.append(strGlassWidth);
                                     ResultDataJson->ResultData.GlassLength.append(strGlassLength);
                                     ResultDataJson->ResultData.GlassAngle.append(strGlassAngle);

                                     ginfo->GlassWidth=strGlassLength.toDouble();
                                     ginfo->GlassLength=strGlassWidth.toDouble();
                                     Global::RollerAngle = strGlassAngle.toDouble();

                                     ginfo->GlassID=ResultDataJson->InterParasToQJson(ResultDataJson->ResultData, LastDefectCount, Count, GlassPosition, 0 , true);
                                     qDebug()<<"GlassPosition: "<<GlassPosition;
                                     qDebug()<<"LastDefectCount: "<<LastDefectCount;
                                     qDebug()<<"Count: "<< Count.ToString().Text();
                                    //发送显示缺陷点位置信号
                                    emit sig_Deliver(Points);
                                    emit sig_updateSignalFlaw(ginfo->GlassID);
                                    qDebug()<<"ProcessStep"<<ProcessStep;
                                    qDebug()<<"m_FramesPerTri"<<Global::FramesPerTri;
                                    emit sig_updateFlaw(ginfo);
                                    QString info="ProcessStep" + QString::number(ProcessStep)  + "算法执行完成！";
                                    log_singleton::Write_Log(info, Log_Level::General);
                                } catch (HalconCpp::HException& Except) {
                                        ErrFlag=true;
                                        qDebug() << "HalconHalconErr:" << Except.ErrorMessage().Text();
                                        QString info= "算法执行异常！";
                                        log_singleton::Write_Log(info, Log_Level::General);
                                        // 处理异常操作
                                }

                            }
                    }
                    else
                    {
                        ErrFlag=true;
                        qDebug() << "图像为空或已出现异常！";
                        QString info= "图像为空或已出现异常！";
                        log_singleton::Write_Log(info, Log_Level::General);
                    }
                   }

                  //尺寸測量+缺陷信息
                  if (GlassPosition==0 || GlassPosition==3 )
                  {
                      HTuple EnableMeasure;
                      GetDictTuple(UserDefinedDict,"尺寸测量启用",&EnableMeasure);
                      qDebug() << "EnableMeasure :" << EnableMeasure.ToString().Text();
                      if(EnableMeasure==1)
                      {
                          DetectSiYin();
                          HolesData2Json();
                      }

                  }
                  ResultNotOutFlag=true;
                  Glassinfo();
                  emit sendData(ginfo);

                  if (GlassPosition==0 || GlassPosition==3 )
                  {
                      SummaryResults();
                      ResultNotOutFlag=false;
                  }
                  ProcessTile::ImageQueue.dequeue();                
                  DetectStep = 0;
                  break;

            }

            if(stopFlag_Detect==true)
                break;
    }
}
void Process_Detect::DetectSiYin()
{
    HTuple NumTile;
    CountObj(ProcessTile::ImageTile1R,&NumTile);
    if(NumTile>0) {
        try {
            procedurecall2->SetInputCtrlParamTuple("Cam1pixs", ProcessTile::Cam1pixs);
            procedurecall2->SetInputCtrlParamTuple("Cam1Width", ProcessTile::Cam1Width);
            procedurecall2->SetInputCtrlParamTuple("Tile2Column1", ProcessTile::Tile2Column1);
            procedurecall2->SetInputCtrlParamTuple("DetectDict", Global::RecipeDict);
            procedurecall2->SetInputIconicParamObject("Image1", ProcessTile::ImageTile1R);
            procedurecall2->SetInputIconicParamObject("Image2", ProcessTile::ImageTile2R);
            procedurecall2->SetInputIconicParamObject("Image3", ProcessTile::ImageTile3R);
            procedurecall2->SetInputIconicParamObject("Image4", ProcessTile::ImageTile4R);

            procedurecall2->Execute();
            ProcessTile::ImageTile1R.Clear();
            ProcessTile::ImageTile2R.Clear();
            ProcessTile::ImageTile3R.Clear();
            ProcessTile::ImageTile4R.Clear();
            GenEmptyObj(&ProcessTile::ImageTile1R);
            GenEmptyObj(&ProcessTile::ImageTile2R);
            GenEmptyObj(&ProcessTile::ImageTile3R);
            GenEmptyObj(&ProcessTile::ImageTile4R);

            ConcatObj(OutLineImage, procedurecall2->GetOutputIconicParamObject("OutLineImage"), &OutLineImage);
            ConcatObj(HolesImage, procedurecall2->GetOutputIconicParamObject("HolesImage"), &HolesImage);
        } catch(HalconCpp::HException& Except) {
            ErrFlag=true;
            qDebug() << "HalconHalconErr:" << Except.ErrorMessage().Text();
            QString info= "算法执行异常！";
            log_singleton::Write_Log(info, Log_Level::General);// 处理异常操作
        }
        HTuple CountHoles=0;
        CountObj(HolesImage,&CountHoles);
        try{
            ResultDictHoles = procedurecall2->GetOutputCtrlParamTuple("ResultDictHoles");
            if (CountHoles>0) {
                Type = ResultDictHoles.TupleGetDictTuple("Type");
                HolesOK = ResultDictHoles.TupleGetDictTuple("HolesOK");
                DistanceHorizontal = ResultDictHoles.TupleGetDictTuple("DistanceHorizontal");
                DistanceVertical = ResultDictHoles.TupleGetDictTuple("DistanceVertical");
                HolesWidth = ResultDictHoles.TupleGetDictTuple("HolesWidth");
                HolesHeight = ResultDictHoles.TupleGetDictTuple("HolesHeight");
            }
            GlassWidth = ResultDictHoles.TupleGetDictTuple("GlassWidth");
            GlassLength = ResultDictHoles.TupleGetDictTuple("GlassHeight");
        } catch(HalconCpp::HException& Except) {
            GlassWidth = 0;
            GlassLength = 0;
            qDebug() << "HalconHalconErr:" << Except.ErrorMessage().Text();
        }
        qDebug() << "GlassWidthttttttttttttttt"<<GlassWidth.ToString().Text();
        qDebug() << "GlassWidthttttttttttttttttt"<<GlassLength.ToString().Text();
    } else {
        //无测量结果
    }
}
void Process_Detect::slot_updateSortInfo()
{
    if(Qlist_Result.count()>0)
    {
       result->sort_result= Qlist_Result.takeFirst();
       result->sorted++;
       result->unsorted--;
       emit sig_updateSortRes(result);
       emit sig_UpdateResultInfo(result);
    } else {

    }
}

//void Process_Detect::slot_ClearDate()
//{
//    result->ngNum=0;
//    result->okNum=0;
//    result->sorted=0;
//    result->GlassNum=0;
//    result->passRate=0;
//    result->unsorted=0;
//    result->exceptNum=0;
//    result->pre_result="OK";
//    result->sort_result="OK";
//}
void Process_Detect::SummaryResults()
{             


        //报警灯信号输出
        if(ginfo->isOK)
        {
            Qlist_Result.append(true);
            Global::AlmLightSignal=true;
            Global::AlmLightVal=4;
        }
        else
        {
            Qlist_Result.append(false);
            Global::AlmLightSignal=true;
            Global::AlmLightVal=15;
        }

        //检测结果刷新
        update_result(ginfo->isOK);

        qDebug() << result->GlassNum;
        emit sig_UpdateResultInfo(result);
//        emit sig_SignalLight(1);
        //变量清理
        ErrImage1.Clear();
        ErrImage2.Clear();
        ErrImage3.Clear();
        OutLineImage.Clear();
        HolesImage.Clear();
        GenEmptyObj(&ErrImage1);
        GenEmptyObj(&ErrImage2);
        GenEmptyObj(&ErrImage3);
        GenEmptyObj(&OutLineImage);
        GenEmptyObj(&HolesImage);
        ResultDict = HTuple();
        ResultDictHoles = HTuple();
        GlassWidth = HTuple();
        GlassLength = HTuple();
        ErrName = HTuple();
        ErrType = HTuple();
        Type = HTuple();
        HolesOK = HTuple();
        DistanceHorizontal = HTuple();
        DistanceVertical = HTuple();
        HolesWidth = HTuple();
        HolesHeight = HTuple();
        DefectLevel = HTuple();
        ErrX = HTuple();
        ErrY = HTuple();
        ErrW = HTuple();
        ErrL = HTuple();
        ErrArea = HTuple();
        ResultDataJson->ResultData.DefectID.clear();
        ResultDataJson->ResultData.DefectType.clear();
        ResultDataJson->ResultData.DefectLeve.clear();

        ResultDataJson->ResultData.Lenth.clear();
        ResultDataJson->ResultData.Width.clear();
        ResultDataJson->ResultData.Area.clear();
        ResultDataJson->ResultData.X.clear();
        ResultDataJson->ResultData.Y.clear();
        ResultDataJson->ResultData.ImageNGPath.clear();
        ResultDataJson->ResultData.GlassLength.clear();
        ResultDataJson->ResultData.GlassWidth.clear();

        ResultDataJson->ResultData.Type.clear();
        ResultDataJson->ResultData.HolesLeve.clear();
        ResultDataJson->ResultData.HolesWidth.clear();
        ResultDataJson->ResultData.HolesHeight.clear();
        ResultDataJson->ResultData.DistanceVertical.clear();
        ResultDataJson->ResultData.DistanceHorizontal.clear();
        ResultDataJson->ResultData.ImageHolesLinePath.clear();
        ResultDataJson->ResultData.ImageHolesPath.clear();
          // 发送数据
        Points->clear();
        QString info="玻璃ID" + ginfo->GlassID  + "算法执行完成！";

        log_singleton::Write_Log(info, Log_Level::General);
}

void Process_Detect::DetectData2Json()
{
}

void Process_Detect::HolesData2Json()
{
    HTuple CountSK;
    CountObj(HolesImage, &CountSK);
    qDebug()<<"count2:"<<CountSK.ToString().Text();
    //siyin信息汇总
    if (CountSK > 0) {
        QString folderDefectImage = QString("E:/SaveDefectImage");
        QDir directory(folderDefectImage);
        // 判断存储小图文件夹是否存在
        QDir folderDir(folderDefectImage);
        if (folderDir.exists()) {
            qDebug() << "Folder" << folderDefectImage << "exists.";
        } else {
            if (directory.mkpath(folderDefectImage)) {
                qDebug() << "Directory created.";
            } else {
                qDebug() << "Failed to create directory";
            }
        }
        qDebug() << "P2 :" << QDateTime::currentDateTime().toString("HH:mm:ss.zzz");

        // Get the current time
        QDateTime currentDateTime = QDateTime::currentDateTime();

        QString folderName = QString("E:/SaveDefectImage/") + currentDateTime.toString("yyyy-MM-dd");
        for (int i = 0; i < CountSK; i++) {
            QDir directory(folderName);
            // 判断文件夹是否存在
            QDir folderDir(folderName);
            if (folderDir.exists()) {
               qDebug() << "Folder" << folderName << "exists.";
            } else {
                    if (directory.mkpath(folderName)) {
                        qDebug() << "Directory"
                                 << "created.";
                    } else {
                        qDebug() << "Failed to create directory";
                    }
                }
                QString CurrentTime = currentDateTime.toString("hh-mm-ss");
                ResultDataJson->ResultData.Time = CurrentTime;
                QString strType = Type.TupleSelect(i).ToString().Text();

                strType = strType.remove("\"");
                QString strHolesOK = HolesOK.TupleSelect(i).ToString().Text();
                strHolesOK = strHolesOK.remove("\"");
                qDebug()<<strType<<strHolesOK;
                QString strDistanceHorizontal, strDistanceVertical, strHolesWidth, strHolesHeight;
                qDebug()<<"Count2"<<CountSK.ToString().Text()<<"DistanceHorizontal.Length()"<<DistanceHorizontal.Length()<<DistanceVertical.Length()<<HolesWidth.Length()<<HolesHeight.Length();
                if(DistanceHorizontal.Length()==CountSK && DistanceVertical.Length()==CountSK && HolesWidth.Length()==CountSK  && HolesHeight.Length()==CountSK )
                {
                strDistanceHorizontal = DistanceHorizontal.TupleSelect(i).ToString().Text();
                strDistanceHorizontal = strDistanceHorizontal.remove("\"");
                strDistanceVertical = DistanceVertical.TupleSelect(i).ToString().Text();
                strDistanceVertical = strDistanceVertical.remove("\"");
                strHolesWidth = HolesWidth.TupleSelect(i).ToString().Text();
                strHolesWidth = strHolesWidth.remove("\"");
                strHolesHeight = HolesHeight.TupleSelect(i).ToString().Text();
                strHolesHeight = strHolesHeight.remove("\"");
                }
                else
                {
                    strDistanceHorizontal="0";
                    strDistanceVertical="0";
                    strHolesWidth="0";
                    strHolesHeight="0";

                }
                ResultDataJson->ResultData.HolesID.append(QString::number(i + 1));
                ResultDataJson->ResultData.Type.append(strType);
                ResultDataJson->ResultData.HolesLeve.append(strHolesOK);
                ResultDataJson->ResultData.DistanceVertical.append(strDistanceVertical);
                ResultDataJson->ResultData.DistanceHorizontal.append(strDistanceHorizontal);
                ResultDataJson->ResultData.HolesWidth.append(strHolesWidth);
                ResultDataJson->ResultData.HolesHeight.append(strHolesHeight);

                QString strImageHolesPath = folderName + "/" + "孔" + "/" + CurrentTime;
                ResultDataJson->ResultData.ImageHolesPath.append(strImageHolesPath);



                // 发送数据
        //                                emit resultReady(ResultDataJson->ResultData);
                //存小图
                QDir directory1(folderName + "/" + strType);
                if (directory1.exists()) {
                    qDebug() << "Directory"
                             << "already exists.";
                } else {
                    // Create the directory
                    if (directory1.mkpath(folderName + "/" + strType)) {
                        qDebug() << "Directory"
                                 << "created.";
                    } else {
                        qDebug() << "Failed to create directory";
                    }
                }
                QDir directory2(strImageHolesPath);
                if (directory2.exists()) {
                    qDebug() << "Directory"
                             << "already exists.";
                } else {
                    // Create the directory
                    if (directory2.mkpath(strImageHolesPath)) {
                        qDebug() << "Directory"
                                 << "created.";
                    } else {
                        qDebug() << "Failed to create directory";
                    }
                }

                QString ImageHolesPath2 = strImageHolesPath + "/" + QString::number(i) + ".jpg";

                WriteImage(HolesImage.SelectObj(i + 1), "jpg", 0, ImageHolesPath2.toUtf8().constData());

            }

            QString CurrentTime = currentDateTime.toString("hh-mm-ss");

            QString strImageHolesLinePath = folderName + "/" + "孔示意图" + "/" + CurrentTime;
            ResultDataJson->ResultData.ImageHolesLinePath.append(strImageHolesLinePath);

            QDir directory3(strImageHolesLinePath);
            if (directory3.exists()) {
                qDebug() << "Directory"
                         << "already exists.";
            } else {
                // Create the directory
                if (directory3.mkpath(strImageHolesLinePath)) {
                    qDebug() << "Directory"
                             << "created.";
                } else {
                    qDebug() << "Failed to create directory";
                }
            }
            QString ImageHolesPath1 = strImageHolesLinePath + "/" + "1.jpg";
            WriteImage(OutLineImage, "jpg", 0, ImageHolesPath1.toUtf8().constData());
        }

         ginfo->GlassID=ResultDataJson->InterParasToQJson(ResultDataJson->ResultData, 0, 0, 0, CountSK , false);
         qDebug()<<"GlassID: "<<ginfo->GlassID;

}
void Process_Detect::Glassinfo()
{
    ginfo->isSizeOK = false;
    HTuple Count;
    CountObj(ErrImage1, &Count);
    qDebug()<<"count:"<<Count.ToString().Text();
    if (Count > 0) {
        HTuple  hv_Indices_NG,hv_count_NG;
        HTuple  hv_Indices,hv_count;

        TupleFind(DefectLevel, "NG", &hv_Indices_NG);
        if (0 != (int(hv_Indices_NG!=-1))) {
          ginfo->isFlawOK=false;
        } else {
          ginfo->isFlawOK=true;
        }

        if(ginfo->isFlawOK==true && ginfo->isSizeOK==true) {
            ginfo->isOK=true;
        } else {
            ginfo->isOK=false;
        }

        if (ResultDataJson->ResultData.DefectType.contains("划伤")) {
            ginfo->Flaw1 = ResultDataJson->ResultData.DefectType.count("划伤");
        } else {
            ginfo->Flaw1 = 0;
        }

        if (ResultDataJson->ResultData.DefectType.contains("气泡")) {
            ginfo->Flaw2 = ResultDataJson->ResultData.DefectType.count("气泡");
        } else {
            ginfo->Flaw2 = 0;
        }
        if (ResultDataJson->ResultData.DefectType.contains("崩边")) {
            ginfo->Flaw3 = ResultDataJson->ResultData.DefectType.count("崩边");
        } else {
            ginfo->Flaw3 = 0;
        }

        if (ResultDataJson->ResultData.DefectType.contains("脏污")) {
            ginfo->Flaw4 =  ResultDataJson->ResultData.DefectType.count("脏污");
        } else {
            ginfo->Flaw4 = 0;
        }

        if (ResultDataJson->ResultData.DefectType.contains("裂纹")) {
            ginfo->Flaw5 =  ResultDataJson->ResultData.DefectType.count("裂纹");
        } else {
            ginfo->Flaw5 = 0;
        }

        if (ResultDataJson->ResultData.DefectType.contains("其它")) {
            ginfo->Flaw6 =  ResultDataJson->ResultData.DefectType.count("其它");
        } else {
            ginfo->Flaw6 = 0;
        }

        if (ResultDataJson->ResultData.DefectType.contains("结石")) {
            ginfo->Flaw7 =  ResultDataJson->ResultData.DefectType.count("结石");
        } else {
            ginfo->Flaw7 = 0;
        }

        ginfo->Diagonal1=0;
        ginfo->Diagonal2=0;
        ginfo->FlawCount=ginfo->Flaw1 + ginfo->Flaw2 +ginfo->Flaw3 + ginfo->Flaw4 + ginfo->Flaw5 + ginfo->Flaw6 + ginfo->Flaw7;
    } else {
        ginfo->isFlawOK=true;
        ginfo->Diagonal1=0;
        ginfo->Diagonal2=0;
        ginfo->FlawCount=0;
        ginfo->GlassWidth=1200;
        ginfo->GlassLength=2500;
        ginfo->Flaw1=0;
        ginfo->Flaw2=0;
        ginfo->Flaw3=0;
        ginfo->Flaw4=0;
        ginfo->Flaw5=0;
        ginfo->Flaw6=0;
        ginfo->Flaw7=0;
    }

    if(ginfo->isFlawOK && ginfo->isSizeOK && ErrFlag==0) {
        ginfo->isOK =true;
    } else {
        ginfo->isOK =false;
        if(ErrFlag==1) {
            result->exceptNum++;
        }
    }
}

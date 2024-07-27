#include "processdetect.h"
#include <algorithm>
#include "Parameter/json.h"
#include <iostream>
#include <fstream>
#include <QQueue>
#include <QDir>
#pragma execution_character_set("utf-8")
Process_Detect::Process_Detect()
{
    ResultNotOutFlag = false;
    ErrFlag = false;
    GlassPosition=0;
    Points = new QList<FlawPoint>();
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

//算法执行
void Process_Detect::VisionProcess(ImageUnit imageunit, HoleUnit holeunit)
{
    QString glassID;
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
                    DefeteResult outResult;
                    Process_Detect::saveErrImage(processvisionresult, outResult);
                    glassID = outResult.GlassID; //更新GlassID，给后面程序使用
                    Process_Detect::DetectData2Json(outResult);
                    qDebug()<<"GlassPosition: "<<GlassPosition;


                    emit sig_Deliver(Points);   //发送显示缺陷点位置信号
                    emit sig_updateSignalFlaw(QString::number(outResult.GlassID),outResult.currentTime.toString("yyyy-MM-dd HH"));//更新缺陷小图信息
                    qDebug()<<"ProcessStep"<<ProcessStep;
                    qDebug()<<"m_FramesPerTri"<<Global::FramesPerTri;
                    emit sig_updateFlaw(outResult.GlassLength.toDouble(),outResult.GlassWidth.toDouble());//画出最外围轮廓
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
    if (GlassPosition==0 || GlassPosition==3 ) {
        HTuple EnableMeasure;
        GetDictTuple(UserDefinedDict,"尺寸测量启用",&EnableMeasure);
        qDebug() << "EnableMeasure :" << EnableMeasure.ToString().Text();
        if(EnableMeasure==1) {
            ProcessHolesAlgorithmResults procesHoleResult;
            procesHoleResult.GlassID = glassID;
            Process_Detect::DetectSiYin(holeunit, procesHoleResult);
            Process_Detect::HolesData2Json(procesHoleResult);
        }
    }
    ResultNotOutFlag = true;
    GlassDataBaseInfo baseinfo;
    Process_Detect::Glassinfo(processvisionresult,baseinfo);
    emit sendData(baseinfo); //信息统计表格中插入一行数据
    QString glassidAndTime = QString::number(baseinfo.id) + "." + currentTimeJson.toString("yyyy-MM-dd HH");
    qDebug()<<"glassidAndTime = "<<glassidAndTime;
    //更新缺陷小图
    emit sig_refreshFlaw(glassidAndTime); //刷新缺陷
    emit sig_refreshSize(glassidAndTime); //刷新尺寸
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
        qDebug() << "GlassWidthttttttttttttttt"<<procesHoleResult.GlassWidth.ToString().Text();
        qDebug() << "GlassWidthttttttttttttttttt"<<procesHoleResult.GlassLength.ToString().Text();
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
    Points->clear();
    QString info="玻璃ID" + QString::number(baseinfo.id)  + "算法执行完成！";
    log_singleton::Write_Log(info, Log_Level::General);
}

void Process_Detect::DetectData2Json(DefeteResult result)
{
    //
    // 先将文件中已有的数据读出来
    //
    Json::Value root;
    QDir folderDir(result.jsonFullPath);
    qDebug()<<"result.jsonFullPath  = "<<result.jsonFullPath;
    if (folderDir.exists()) {
        std::ifstream ifs;
        ifs.open(result.jsonFullPath.toStdString()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<"[Process_Detect::DetectData2Json] ifs.is_open() =  false";
        }
    } else {
        qDebug()<<"[Process_Detect::DetectData2Json] "<<result.jsonFullPath<<" is not exit.";
    }
    //
    // 将数据追加在文件末尾上
    //
    Json::FastWriter writer;
    Json::Value glassdata;
    for(int i=0; i<(int)result.defetes.size(); ++i) {
        DefeteData temp = result.defetes[i];
        Json::Value defectdata;
        defectdata["Area"] = temp.Area.toStdString();
        defectdata["DefectID"] = temp.DefectID.toStdString();
        defectdata["DefectType"] = temp.DefectType.toStdString();
        defectdata["DetectLeve"] = temp.DetectLeve.toStdString();
        defectdata["ImageNGPath"] = temp.ImageNGPath.toStdString();
        defectdata["Lenth"] = temp.Lenth.toStdString();
        defectdata["Time"] = temp.Time.toStdString();
        defectdata["Width"] = temp.Width.toStdString();
        defectdata["X"] = temp.X.toStdString();
        defectdata["Y"] = temp.Y.toStdString();
        glassdata[temp.DefectID.toStdString().c_str()] = defectdata;
    }
    glassdata["GlassAngle"] = result.GlassAngle.toStdString();
    glassdata["GlassLength"] = result.GlassLength.toStdString();
    glassdata["GlassWidth"] = result.GlassWidth.toStdString();
    root[QString::number(result.GlassID).toStdString().c_str()] = glassdata;

    std::string json_content = writer.write(root);
    std::ofstream ofs;
    ofs.open(result.jsonFullPath.toStdString().data());
    if (ofs.is_open()) {
        ofs<<json_content;
        ofs.close();
    }
}

void Process_Detect::HolesData2Json(ProcessHolesAlgorithmResults procesHoleResult)
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
    HoleResult holeresult;
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
            hole.DistanceHorizontal = strDistanceHorizontal.remove("\"");

            QString strDistanceVertical = procesHoleResult.DistanceVertical.TupleSelect(i).ToString().Text();
            hole.DistanceVertical = strDistanceVertical.remove("\"");

            QString strHolesWidth = procesHoleResult.HolesWidth.TupleSelect(i).ToString().Text();
            hole.HolesWidth = strHolesWidth.remove("\"");

            QString strHolesHeight = procesHoleResult.HolesHeight.TupleSelect(i).ToString().Text();
            hole.HolesHeight = strHolesHeight.remove("\"");
        } else {
            hole.DistanceHorizontal = "0";
            hole.DistanceVertical = "0";
            hole.HolesWidth = "0";
            hole.HolesHeight = "0";
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
    QString jsonFilePath = QDir::currentPath() + "/HolesInfJson/" + currentTimeJson.toString("yyyy-MM-dd HH") + ".json";
    holeresult.jsonFullPath = jsonFilePath;
    Process_Detect::writeHoleDataToJsonfile(holeresult);
}

void Process_Detect::Glassinfo(ProcessVisionAlgorithmResults result, GlassDataBaseInfo& baseinfo)
{
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

        HTuple huashan;
        TupleFind(result.ErrType, "划伤", &huashan);
        baseinfo.huashanNumber = huashan.TupleLength().I();

        HTuple qipao;
        TupleFind(result.ErrType, "气泡", &qipao);
        baseinfo.qipaoNumber = qipao.TupleLength().I();

        HTuple benbian;
        TupleFind(result.ErrType, "崩边", &benbian);
        baseinfo.benbianNumber = benbian.TupleLength().I();

        HTuple zanwu;
        TupleFind(result.ErrType, "脏污", &zanwu);
        baseinfo.zanwuNumber = zanwu.TupleLength().I();

        HTuple liewen;
        TupleFind(result.ErrType, "裂纹", &liewen);
        baseinfo.liewenNumber = liewen.TupleLength().I();

        HTuple qita;
        TupleFind(result.ErrType, "其它", &qita);
        baseinfo.qitaNumber = qita.TupleLength().I();

        HTuple jieshi;
        TupleFind(result.ErrType, "结石", &jieshi);
        baseinfo.qitaNumber = jieshi.TupleLength().I();

        baseinfo.duijiaoxian1 = 0;
        baseinfo.duijiaoxian2 = 0;

        baseinfo.defectNumber = baseinfo.huashanNumber+baseinfo.qipaoNumber+baseinfo.benbianNumber+baseinfo.zanwuNumber+baseinfo.liewenNumber+baseinfo.qitaNumber+baseinfo.jieshiNumber;
    } else {
        baseinfo.defectOKorNG = "OK";
        baseinfo.OKorNG = "OK";
        baseinfo.huashanNumber = 0;
        baseinfo.qipaoNumber = 0;
        baseinfo.benbianNumber = 0;
        baseinfo.zanwuNumber = 0;
        baseinfo.liewenNumber = 0;
        baseinfo.qitaNumber = 0;
        baseinfo.qitaNumber = 0;
        baseinfo.duijiaoxian1 = 0;
        baseinfo.duijiaoxian2 = 0;
        baseinfo.width = 2500;
        baseinfo.length = 1200;
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
    QString fileName = currentDateTime.toString("yyyy-MM-dd HH") + ".json";
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
         strErrName = strErrName.remove("\"");
         data.DefectType = strErrName;

         QString strDefectLevel = result.DefectLevel.TupleSelect(i).ToString().Text();
         strDefectLevel = strDefectLevel.remove("\"");
         data.DetectLeve = strDefectLevel;

         QString strErrX = result.ErrX.TupleSelect(i).ToString().Text();
         strErrX = strErrX.remove("\"");
         data.X = strErrX;

         QString strErrY = result.ErrY.TupleSelect(i).ToString().Text();
         strErrY = strErrY.remove("\"");
         data.Y = strErrY;

         QString strErrL = result.ErrL.TupleSelect(i).ToString().Text();
         strErrL = strErrL.remove("\"");
         data.Lenth = strErrL;

         QString strErrW = result.ErrW.TupleSelect(i).ToString().Text();
         strErrW = strErrW.remove("\"");
         data.Width = strErrW;

         QString strErrArea = result.ErrArea.TupleSelect(i).ToString().Text();
         strErrArea = strErrArea.remove("\"");
         data.Area = strErrArea;

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
         Points->append(Point);

         QString strErrNameDir = folderName + "/" + strErrName;
         if (!Process_Detect::isExistDir(strErrNameDir)) {
             QString errorMessage = "Faile to create " + strErrNameDir;
             throw std::exception(errorMessage.toStdString().c_str());
         }
         if (!Process_Detect::isExistDir(strImageNGPath)) {
             QString errorMessage = "Faile to create " + strImageNGPath;
             throw std::exception(errorMessage.toStdString().c_str());
         }

         QString ImageNGPath1 = strImageNGPath + "/" + strErrName + "1.jpg";
         QString ImageNGPath2 = strImageNGPath + "/" + strErrName + "2.jpg";
         QString ImageNGPath3 = strImageNGPath + "/" + strErrName + "3.jpg";

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
    strGlassWidth = strGlassWidth.remove("\"");
    defect.GlassWidth = strGlassWidth;

    QString strGlassLength = result.GlassLength.ToString().Text();
    strGlassLength = strGlassLength.remove("\"");
    defect.GlassLength = strGlassLength;

    QString strGlassAngle = result.GlassAngle.ToString().Text();
    Global::RollerAngle = strGlassAngle.toDouble();
    defect.GlassAngle = strGlassAngle;
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
    if (folderDir.exists()) {
        qDebug() << "Folder: " << dirpath << "exists.";
    } else {
        if (folderDir.mkpath(dirpath)) {
            qDebug() << "Directory created.";
        } else {
            qDebug() << "Failed to create directory";
            return false;
        }
    }
    return true;
}

void Process_Detect::writeHoleDataToJsonfile(HoleResult holeresult)
{
    //
    // 先将文件中已有的数据读出来
    //
    Json::Value root;
    QDir folderDir(holeresult.jsonFullPath);
    qDebug()<<"result.jsonFullPath  = "<<holeresult.jsonFullPath;
    if (folderDir.exists()) {
        std::ifstream ifs;
        ifs.open(holeresult.jsonFullPath.toStdString()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<"[Process_Detect::DetectData2Json] ifs.is_open() =  false";
        }
    } else {
        qDebug()<<"[Process_Detect::DetectData2Json] "<<holeresult.jsonFullPath<<" is not exit.";
    }
    //
    // 将数据追加在文件末尾上
    //
    Json::FastWriter writer;
    Json::Value glassholedata;
    for(int i=0; i<(int)holeresult.holes.size(); ++i) {
        HoleData temp = holeresult.holes[i];
        Json::Value holeData;
        holeData["DistanceHorizontal"] = temp.DistanceHorizontal.toStdString();
        holeData["DistanceVertical"] = temp.DistanceVertical.toStdString();
        holeData["HolesHeight"] = temp.HolesHeight.toStdString();
        holeData["HolesID"] = temp.HolesID.toStdString();
        holeData["HolesLeve"] = temp.HolesLeve.toStdString();
        holeData["HolesWidth"] = temp.HolesWidth.toStdString();
        holeData["ImageHolesPath"] = temp.ImageHolesPath.toStdString();
        holeData["Time"] = temp.Time.toStdString();
        holeData["Type"] = temp.Type.toStdString();
        glassholedata[temp.HolesID.toStdString().c_str()] = holeData;
    }
    glassholedata["GlassAngle"] = holeresult.GlassAngle.toStdString();
    glassholedata["GlassLength"] = holeresult.GlassLength.toStdString();
    glassholedata["GlassWidth"] = holeresult.GlassWidth.toStdString();
    glassholedata["ImageHolesLinePath"] = holeresult.ImageHolesLinePath.toStdString();
    root[holeresult.GlassID.toStdString().c_str()] = glassholedata;

    std::string json_content = writer.write(root);
    std::ofstream ofs;
    ofs.open(holeresult.jsonFullPath.toStdString().data());
    if (ofs.is_open()) {
        ofs<<json_content;
        ofs.close();
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

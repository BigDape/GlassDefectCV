﻿#include "processtile.h"
#include "Global.h"
#include <QMessageBox>
#include <QDir>
#pragma execution_character_set("utf-8")


HObject ProcessTile::ImageTile1R;
HObject ProcessTile::ImageTile2R;
HObject ProcessTile::ImageTile3R;
HObject ProcessTile::ImageTile4R;
int ProcessTile::Cam1pixs;
int ProcessTile::Cam1Width;
int ProcessTile::Tile2Column1;
bool ProcessTile::ErrFlag;
bool ProcessTile::LastErrFlag;
SafeQueue<PDArgs> ProcessTile::preImageQueue;

ProcessTile::ProcessTile(QList<DushenBasicFunc*> Cameras)
{
    m_Cameras = Cameras;
    init_ProcessTile();
}

void ProcessTile::init_ProcessTile()
{
    stopFlag_Tile=false;
    TileStep = 0;
    FrameCount=0;
    GlassPosition=0;
    lastGlassPosition=0;
    ErrFlag=false;
    FirstFrame = true;
    FieldNumber=Global::FieldNumberSet+1;
    TileColumn1=HTuple();
    TileColumn2=HTuple();
    GenEmptyObj(&TileRectangle);

    MosaickHobject = new HObject[4];
    GlassRegion.GenEmptyObj();
    RegionsFrameCrop.GenEmptyObj();
    RegionFrame.GenEmptyObj();
    ImageTile1.GenEmptyObj();
    ImageTile2.GenEmptyObj();
    ImageTile3.GenEmptyObj();
    ImageTile4.GenEmptyObj();
    ImageTile1R.GenEmptyObj();
    ImageTile2R.GenEmptyObj();
    ImageTile3R.GenEmptyObj();
    ImageTile4R.GenEmptyObj();
    hasStopThread.store(false);
}

void ProcessTile::run()
{
TPLOOP:
    ProcessTile::TileImageProcess();
    if(!hasStopThread.load())
        goto TPLOOP;
}

//图像预处理
void ProcessTile::TileImageProcess()
{
    if (Global::isOffline == false && Global::SystemStatus == 0) return;
    //
    // 离线模式
    //
    if (Global::isOffline) {
        ProcessTile::OfflineTileImageProcess(Global::offlineFullPath);
        Global::isOffline = false;
        Global::offlineFullPath.clear();
        return;
    }
    //
    // 在线模式
    //
    bool allCamerasStarted = true;
    for (auto camera : m_Cameras) {
        if (!camera || !camera->IsStarted) {
            allCamerasStarted = false;
            return; //相机未全部开始，流程提前结束
        }
    }
    bool allCameraIsNotEmpty = true;
    if (allCamerasStarted) {
        for(auto i:m_Cameras) {
            std::unique_lock<std::mutex> sbguard(_mutex);
            if(hasStopThread.load()) return;
            if(i->m_AcquireImage->ImageQueue.empty()){//这里会崩溃
                allCameraIsNotEmpty = false;
                return; //相机队列为空，流程提前结束
            }
        }
    }

    if(allCamerasStarted && allCameraIsNotEmpty) {
        std::unique_lock<std::mutex> sbguard(_mutex);
        if(hasStopThread.load()) return;
        QImageAcquisition::ImageUnit headImage;
        m_Cameras[0]->m_AcquireImage->ImageQueue.dequeue(headImage);
        FrameCount = headImage.FrameCount;
        if(FrameCount == 1) {
            Global::ImageHeight = 0;
            Global::ImageWidth = 0;
            //Err标志位
            ErrFlag = false;
        }
        //帧信号复位
        Global::FrameSignal = 0;
        GetDictTuple(Global::RecipeDict,"自定义参数",&UserDefinedDict);
        HSThreadPool pool(FieldNumber);
        qDebug() << "FieldNumber :" <<FieldNumber;
        std::vector<std::future<HObject>> resultvec;
        for (int i = 0; i < FieldNumber; i++) {//光场数量
            MosaickImage mosaickthread;
            MosaickArg Args;
            for(int j=0;j<Global::camDefineNum;j++) {//相机个数
                qDebug() << "camDefineNum :" <<Global::camDefineNum;
                Args.CameraImageList.append(headImage.ImageList[i]) ;
                Args.channel =  (i==FieldNumber-1) ? 1 : 0;//最后一个场为0
            }
            mosaickthread.mosaickQueue.inqueue(Args);
            resultvec.push_back(pool.submit(std::bind(&MosaickImage::run,&mosaickthread)));
        }
        //等待所有线程执行完成
         mosaickResult.clear();
        for(int j=0;j<FieldNumber;j++) {
             mosaickResult.push_back( resultvec[j].get());
        }

    } //if(allCamerasStarted && allCameraIsNotEmpty)

    qDebug() << "end :" << QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
    HTuple isSaveOriImage;
    GetDictTuple(UserDefinedDict,"保存原图",&isSaveOriImage);
    if(isSaveOriImage==1) {
        //
        // 保存每一帧小图
        //
        try {
            // 获取当前时间
            QString formattedTime = "0";
            if (FrameCount == 1) {
                QDateTime currentDateTime1 = QDateTime::currentDateTime();
                formattedTime = currentDateTime1.toString("yyyy-MM-dd_HH-mm-ss");
                Global::currenttime = formattedTime;
            } else {
                formattedTime = Global::currenttime;
            }
            QString path = "D:/DTSmalleFile/";
            QString dirFileName = formattedTime;
            QDir dir(QDir::currentPath());
            dir.cd(path);
            if(!dir.exists(dirFileName)) {
                dir.mkdir(dirFileName);
            }
            std::string str0 =(path + dirFileName).toStdString();
            std::string str1 = (path + dirFileName+QString("/qqqqqqqqq")+QString::number(FrameCount)+QString("1")).toStdString();
            std::string str2 = (path + dirFileName+QString("/qqqqqqqqq")+QString::number(FrameCount)+QString("2")).toStdString();
            std::string str3 = (path + dirFileName+QString("/qqqqqqqqq")+QString::number(FrameCount)+QString("3")).toStdString();
            HTuple str11(str1.c_str());
            HTuple str22(str2.c_str());
            HTuple str33(str3.c_str());
            if(mosaickResult.size() >= 3){
                WriteImage(mosaickResult[0],"jpg",0,str11);
                WriteImage(mosaickResult[1],"jpg",0,str22);
                WriteImage(mosaickResult[2],"jpg",0,str33);
            }

        } catch(...) {
            for(int i=0; i<mosaickResult.size();++i ){
                HTuple a = FrameCount;
                HTuple str1 = "D:/qqqqqqqq"+ a;
                HTuple str2 = str1 + i;
                 WriteImage(mosaickResult[i],"jpg",0,str2);
            }
        }
    }
    qDebug() << "mosaick success";
    ProcessTile::PreProceeTile();
}

void ProcessTile::PreProceeTile()
{
    ImageUnit imageunit;    //缺陷参数
    HoleUnit holeunit;      //尺寸参数
    try {
        SetSystem("clip_region","false");
        HTuple ImageHeight;
        HTuple ImageWidth;
        HObject RegionFLPanel,RegionOpeningFL,RegionClosingFL,RegionConnectionFL,SelectedRegionsFL;
        HObject RegionUnion2Panel,RegionOpeningPanel,RegionConnectionPanel,RegionPanel;
        if((int)mosaickResult.size() < FieldNumber){
            qDebug()<<"mosaickResult.size()="<<mosaickResult.size()<<"< FieldNumber";
            return;
        }
        GetImageSize(mosaickResult[0], &ImageWidth, &ImageHeight);
        if(FirstFrame==true) {
            HObject ImageP500;
            HObject ImageConcat;
            GenEmptyObj(&ImageConcat);
            CropPart(mosaickResult[0],&ImageP500,0,0,ImageWidth,500);
            for (int j=1; j <= ImageHeight/500+2; j++) {
                ConcatObj(ImageConcat,ImageP500,&ImageConcat);
            }
            TileImages(ImageConcat,&BackGroundImage,1,"vertical") ;
            FirstFrame = false ;
            QString info="拼图步骤"+ QString::number(FrameCount) + "亮场背景处理完成！";
            log_singleton::Write_Log(info, Log_Level::General);
        }
        CropPart(BackGroundImage,&BackGroundImage, 0, 0, ImageWidth, ImageHeight);
        HTuple str2 = "D:/q111";
        WriteImage(BackGroundImage,"jpg",0,str2);
        HTuple Row1,Column1,Phi1,Length1,Length2;
        HObject SubImage1,SubRegion1,RegionUnion1,RegionFillUp1,RegionOpening1,ConnectedRegions1,SelectedRegions1;
        HObject RegionLines, RegionLines1, RegionLines2;
        SubImage(BackGroundImage, mosaickResult[0], &SubImage1, 1, 0);
        HTuple str3 = "D:/q222";
        WriteImage(SubImage1,"jpg",0,str3);

        //反射亮場

        Threshold(mosaickResult[1], &RegionFLPanel, 20, 255);//Threshold(mosaickthread[1].MosaickResultImage, &RegionFLPanel, 20, 255);
        HTuple RegionsWidth;
        //反射亮場找面内區域
        ClosingCircle(RegionFLPanel,&RegionClosingFL,3.5);
        Connection(RegionClosingFL,&RegionConnectionFL);
        SelectShapeStd(RegionConnectionFL, &SelectedRegionsFL, "max_area", 70);
        RegionFeatures(SelectedRegionsFL,"width",&RegionsWidth);
        //透射亮场
        Threshold(SubImage1, &SubRegion1, 150, 255);//Threshold(SubImage1, &SubRegion1, 30, 255);
        OpeningRectangle1(SubRegion1,&RegionOpening1,100,1);
        Connection(RegionOpening1, &ConnectedRegions1);
        SelectShape(ConnectedRegions1,&SelectedRegions1,"width","and",0.5*RegionsWidth,2*RegionsWidth);

        ConcatObj(SelectedRegions1,SelectedRegionsFL,&RegionUnion2Panel);
        Union1(RegionUnion2Panel,&RegionUnion2Panel);

        ClosingCircle(RegionUnion2Panel,&RegionOpeningPanel,1.5);
        Connection(RegionOpeningPanel,&RegionConnectionPanel);
        SelectShapeStd(RegionConnectionPanel, &RegionPanel, "max_area", 70);
        SelectShape(RegionPanel,&RegionPanel,"area","and",100,999999999);

        HTuple RegionPanelArea;
        RegionFeatures(RegionPanel,"area",&RegionPanelArea);
        qDebug()<<"RegionPanelArea"<<RegionPanelArea.ToString().Text();
        HTuple Number,PanelArea,RowPanel,ColumnPanel,PhiPanel,LengthPanel1,LengthPanel2;
        CountObj(RegionPanel, &Number);
        if (Number.TupleInt() > 0) {
            RegionFeatures(RegionPanel,"area",&PanelArea);
            SmallestRectangle2(RegionPanel, &RowPanel, &ColumnPanel, &PhiPanel, &LengthPanel1, &LengthPanel2);
            HTuple a=0.8*(4*LengthPanel1*LengthPanel2);
            HTuple Row1, Column1,Row2,Column2;
            SmallestRectangle1(RegionPanel,&Row1, &Column1, &Row2,&Column2);
//**************************************玻璃位置判断和截取区域提取start**********************************************************
            HTuple RegionRow2,QKNum;
            RegionFeatures(GlassRegion,"row2",&RegionRow2);

            HObject RegionContours,RegionPanelMoved;
            RegionContours = RegionPanel;

            if((Column2-Column1>3000) && Row2-Row1>500) {
                if(Row1>0 && Row2<ImageHeight-1) {
                    //完整玻璃
                    GlassPosition=0;
                    GlassRegion.GenEmptyObj();
                    GlassRegion=RegionContours;
                } else {
                    if(Row1>0) {
                        //玻璃头部
                        Global::CamRowsPerField=ImageHeight;
                        GlassPosition=1;
                        GlassRegion.GenEmptyObj();
                        GlassRegion=RegionContours;
                    } else {
                        if(Row2<ImageHeight-1) {
                            //玻璃尾部
                            GlassPosition=3;
                        } else {
                            //玻璃中部
                            GlassPosition=2;
                        }
                    }
                }
            //
            // 完整玻璃或玻璃头部或第一帧
            //
            if(GlassPosition == 0 || GlassPosition==1 || FrameCount == 1) {
                if(Column1>1000){
                    TileColumn1=Column1-1000;
                } else {
                    TileColumn1=0;
                }

                if(ImageWidth-Column2>1000) {
                    TileColumn2=Column2+1000;
                } else {
                    TileColumn2=ImageWidth-1;
                }
                qDebug()<<"Column2//////////////////////////////////////////"<<Column2.ToString().Text();
                qDebug() <<"TileColumn1"<<TileColumn1.ToString().Text();
                qDebug()<<"TileColumn2"<<TileColumn2.ToString().Text();
                qDebug() << "ImageHeighttttt :" << ImageHeight.ToString().Text();
            }
        } else {
            GlassPosition=3;
            QString info="拼图步骤"+ QString::number(FrameCount) + "玻璃有效区域占比小！定为玻璃尾部";
            log_singleton::Write_Log(info, Log_Level::General);
        }

        //玻璃region
        if(GlassPosition==2 || GlassPosition==3) {
            if(RegionRow2>0) {
                MoveRegion(RegionContours,&RegionPanelMoved,RegionRow2,0);
                Union2(GlassRegion,RegionPanelMoved,&GlassRegion);
                RegionContours.Clear();
                RegionPanelMoved.Clear();
            }
        }

        if(GlassPosition==3) {
            //一次扫描结束
            Global::FrameSignal=1;
        }

        if(FrameCount == 1 && Row1==0) {
            QString info="拼图步骤"+ QString::number(FrameCount) + "玻璃头部未扫描";
            log_singleton::Write_Log(info, Log_Level::General);
        }
        //单帧玻璃区域矫正
        MoveRegion(RegionPanel,&RegionFrame,0,-TileColumn1);
        //截取有效区域
        GenRectangle1(&TileRectangle, 0, TileColumn1,ImageHeight - 1 , TileColumn2);
        HTuple width1;
        RegionFeatures(TileRectangle,"width",&width1);
        qDebug() << "width1 :" << width1.ToString().Text();
        HObject ImageReduced[4];
        HObject ImagePart[4];

        for(int i=0;i<FieldNumber;i++) {
            if((int)mosaickResult.size()>= FieldNumber){
                ReduceDomain(mosaickResult[i], TileRectangle, &ImageReduced[i]);
                CropDomain(ImageReduced[i], &ImagePart[i]);
            }
        }
        //拼整图
        if(GlassPosition!=0) {
            HTuple ImageHeight1;
            HTuple ImageWidth1;
            GetImageSize(ImagePart[0], &ImageWidth1, &ImageHeight1);
            //拼接前
            if(GlassPosition==1) {
                ImageTile1.GenEmptyObj();
                ImageTile2.GenEmptyObj();
                ImageTile3.GenEmptyObj();
                ImageTile4.GenEmptyObj();

                qDebug()<<"ImageWidth1"<<ImageWidth1.ToString().Text()<<"ImageHeight1"<<ImageHeight1.ToString().Text();
                HObject ho_ImagePart[4],ho_ObjectsConcat[4],ho_TiledImage[4];
                for(int i=0;i<FieldNumber;i++) {
                    CropPart(ImagePart[i], &ho_ImagePart[i], 0, 0, ImageWidth1, 200);
                    GenEmptyObj(&ho_ObjectsConcat[i]);
                    ConcatObj(ho_ImagePart[i], ImagePart[i], &ho_ObjectsConcat[i]);
                    TileImagesOffset(ho_ObjectsConcat[i], &ho_TiledImage[i], (HTuple(0).Append(200)), (HTuple(0).Append(0)),
                         (HTuple(-1).Append(-1)), (HTuple(-1).Append(-1)), (HTuple(-1).Append(-1)),
                         (HTuple(-1).Append(-1)), ImageWidth1, ImageHeight+200);
                }

                ConcatObj(ImageTile1, ho_TiledImage[0], &ImageTile1);
                ConcatObj(ImageTile2, ho_TiledImage[1], &ImageTile2);
                ConcatObj(ImageTile3, ho_TiledImage[2], &ImageTile3);
                ConcatObj(ImageTile4, ho_TiledImage[3], &ImageTile4);

                HTuple ImageHeight2;
                HTuple ImageWidth2;
                GetImageSize(ho_TiledImage[0], &ImageWidth2, &ImageHeight2);
                qDebug()<<"ImageWidth2"<<ImageWidth2.ToString().Text()<<"ImageHeight2"<<ImageHeight2.ToString().Text();

                for(int i=0;i<FieldNumber;i++){
                    GenEmptyObj(&ho_ImagePart[i]);
                    GenEmptyObj(&ho_ObjectsConcat[i]);
                    GenEmptyObj(&ho_TiledImage[i]);
                }
            } else {
                CropPart(ImagePart[0],&ImagePart[0],0,0,ImageWidth1,ImageHeight1);
                CropPart(ImagePart[1],&ImagePart[1],0,0,ImageWidth1,ImageHeight1);
                CropPart(ImagePart[2],&ImagePart[2],0,0,ImageWidth1,ImageHeight1);
                CropPart(ImagePart[3],&ImagePart[3],0,0,ImageWidth1,ImageHeight1);
                ConcatObj(ImageTile1, ImagePart[0], &ImageTile1);
                ConcatObj(ImageTile2, ImagePart[1], &ImageTile2);
                ConcatObj(ImageTile3, ImagePart[2], &ImageTile3);
                ConcatObj(ImageTile4, ImagePart[3], &ImageTile4);
            }
            //拼接
            if (GlassPosition==3) {
                HTuple NumTile;
                CountObj(ImageTile1,&NumTile);
                if(NumTile>0) {
                    Cam1pixs = ImageWidth/2 - TileColumn1;
                    Cam1Width = ImageWidth/2;
                    Tile2Column1 = TileColumn1;

                    if(Cam1pixs<0) {
                        Cam1pixs=0;
                    }
                    TileImages(ImageTile1, &ImageTile1R, 1, "vertical");
                    TileImages(ImageTile2, &ImageTile2R, 1, "vertical");
                    TileImages(ImageTile3, &ImageTile3R, 1, "vertical");
                    TileImages(ImageTile4, &ImageTile4R, 1, "vertical");

                    QString info="拼图步骤"+ QString::number(FrameCount) + "开始写入数据！";
                    log_singleton::Write_Log(info, Log_Level::General);
                    HTuple isSaveWholeImage;
                    GetDictTuple(UserDefinedDict,"保存整图",&isSaveWholeImage);
                    if(isSaveWholeImage==1) {
                        try {
                             // 获取当前时间
                             QDateTime currentDateTime1 = QDateTime::currentDateTime();
                             QString formattedTime = currentDateTime1.toString("yyyy-MM-dd_HH-mm-ss");
                             QString path = "D:/DTFile/";
                             QString dirFileName = formattedTime;
                             QDir dir(QDir::currentPath());
                             dir.cd(path);
                             if(!dir.exists(dirFileName)) {
                                 dir.mkdir(dirFileName);
                             }
                             std::string str0 =(path + dirFileName).toStdString();
                             std::string str1 = (path + formattedTime+QString("/tile1")).toStdString();
                             std::string str2 = (path + formattedTime+QString("/tile2")).toStdString();
                             std::string str3 = (path + formattedTime+QString("/tile3")).toStdString();
                             std::string str4 = (path + formattedTime+QString("/tile4")).toStdString();
                             HTuple str11(str1.c_str());
                             HTuple str22(str2.c_str());
                             HTuple str33(str3.c_str());
                             HTuple str44(str4.c_str());
                             WriteImage(ImageTile1R,"jpg",0,str11);
                             WriteImage(ImageTile2R,"jpg",0,str22);
                             WriteImage(ImageTile3R,"jpg",0,str33);
                             WriteImage(ImageTile4R,"jpg",0,str44);
                        } catch(...) {
                             WriteImage(ImageTile1R,"jpg",0,"D:/tile1");
                             WriteImage(ImageTile2R,"jpg",0,"D:/tile2");
                             WriteImage(ImageTile3R,"jpg",0,"D:/tile3");
                             WriteImage(ImageTile4R,"jpg",0,"D:/tile4");
                         }
                     }
                     GenEmptyObj(&ImageTile1);
                     GenEmptyObj(&ImageTile2);
                     GenEmptyObj(&ImageTile3);
                     GenEmptyObj(&ImageTile4);
                 }
            }
        } else {
            ImageTile1R = ImagePart[0];
            ImageTile2R = ImagePart[1];
            ImageTile3R = ImagePart[2];
            ImageTile4R = ImagePart[3];
        }
        //判断玻璃尾端
        qDebug() << "lastGlassPosition :" << lastGlassPosition;
        qDebug() << "GlassPosition :" << GlassPosition;
        if(GlassPosition==3 && (lastGlassPosition==2 || lastGlassPosition==1)) {
            HObject ObjectsConcat[3];
            //玻璃尾部，拼接上张图像尾部1000行
            HTuple ImageHeight1;
            HTuple ImageWidth1;
            GetImageSize(ImagePart[0], &ImageWidth1, &ImageHeight1);
            for(int i=0;i<FieldNumber-1;i++) {
                ConcatObj(ImageCrop[i], ImagePart[i], &ObjectsConcat[i]);
                TileImagesOffset(ObjectsConcat[i], &ImagePart[i], (HTuple(0).Append(1000)), (HTuple(0).Append(0)),
                      (HTuple(-1).Append(-1)), (HTuple(-1).Append(-1)), (HTuple(-1).Append(-1)),
                      (HTuple(-1).Append(-1)), ImageWidth1, ImageHeight1+1000);
            }
            HObject RegionsFrameMoved;
            MoveRegion(RegionFrame,&RegionsFrameMoved,1000,0);
            Union2(RegionsFrameMoved,RegionsFrameCrop,&RegionFrame);
            RegionsFrameMoved.Clear();
            RegionsFrameCrop.Clear();
            ObjectsConcat->Clear();
        } else {
            if(GlassPosition==1 || GlassPosition==2) {
                if(ImageHeight>1000) {
                    //截取图像尾部1000行
                    HObject CropRectangle,ImageCropRecReduced[3];
                    GenRectangle1(&CropRectangle, ImageHeight -1 -1000, TileColumn1,ImageHeight - 1 , TileColumn2);
                    for(int i=0;i<FieldNumber-1;i++) {
                        if((int)mosaickResult.size() >= FieldNumber-1){
                            ReduceDomain(mosaickResult[i], CropRectangle, &ImageCropRecReduced[i]);
                            CropDomain(ImageCropRecReduced[i], &ImageCrop[i]);
                            ImageCropRecReduced[i].Clear();
                        }
                    }
                    CropRectangle.Clear();
                    //截取Region尾部1000行
                    HTuple Row1Frame,Column1Frame,Row2Frame,Column2Frame,FrameRowVal;
                    HObject RegionLinesFrame,RegionDifferenceFrame,ConnectedRegionsFrame,SelectedRegionsFrame;

                    SmallestRectangle1(RegionFrame,&Row1Frame, &Column1Frame, &Row2Frame,&Column2Frame);
                    GenRegionLine(&RegionLinesFrame, Row2Frame-1000, Column1Frame-100, Row2Frame-1000, Column2Frame+100);
                    Difference(RegionFrame,RegionLinesFrame,&RegionDifferenceFrame);
                    Connection(RegionDifferenceFrame,&ConnectedRegionsFrame);
                    SelectShape(ConnectedRegionsFrame,&SelectedRegionsFrame, "row","and",Row2Frame-1000,Row2Frame);
                    RegionFeatures(SelectedRegionsFrame,"row1",&FrameRowVal);
                    MoveRegion(SelectedRegionsFrame,&RegionsFrameCrop,-FrameRowVal,0);
                    RegionLinesFrame.Clear();
                    RegionDifferenceFrame.Clear();
                    ConnectedRegionsFrame.Clear();
                    SelectedRegionsFrame.Clear();
                } else {
                    QString info="拼图步骤"+ QString::number(FrameCount) + "图像高度小于1000！";
                    log_singleton::Write_Log(info, Log_Level::General);
                }
            }
        }
        lastGlassPosition = GlassPosition;
        //**************************************玻璃位置判断和截取区域提取end**********************************************************
        HTuple isSaveCropImage;
        GetDictTuple(UserDefinedDict,"保存裁剪图像",&isSaveCropImage);
        if(isSaveCropImage==1) {
            HTuple b= FrameCount;
            WriteImage(ImagePart[0], "jpg", 0, "D:/QQQ1"+b);
            WriteImage(ImagePart[1], "jpg", 0, "D:/QQQ2"+b);
            WriteImage(ImagePart[2], "jpg", 0, "D:/QQQ3"+b);
        }

        GenEmptyObj(&imageunit.ImageList);
        ConcatObj(imageunit.ImageList, ImagePart[0], &imageunit.ImageList);
        ConcatObj(imageunit.ImageList, ImagePart[1], &imageunit.ImageList);
        ConcatObj(imageunit.ImageList, ImagePart[2], &imageunit.ImageList);
 //     ConcatObj(imageunit.ImageList, ImagePart[3], &imageunit.ImageList);

        HTuple ImageListNum;
        CountObj(imageunit.ImageList, &ImageListNum);
        qDebug() << "ImageListNum :" << ImageListNum.ToString().Text();
        imageunit.GlassPositionInf = GlassPosition;
        imageunit.ProcessStep = FrameCount;
        imageunit.ErrorFlag = ErrFlag;
        imageunit.ImageRegion = GlassRegion;
        imageunit.FrameRegion = RegionFrame;

        holeunit.Cam1pixs = Cam1pixs;
        holeunit.Cam1Width = Cam1Width;
        holeunit.ImageTile1R = ImageTile1R;
        holeunit.ImageTile2R = ImageTile2R;
        holeunit.ImageTile3R = ImageTile3R;
        holeunit.ImageTile4R = ImageTile4R;
        holeunit.Tile2Column1 = Tile2Column1;

        if(hasStopThread.load()) return;
        _args.holeunit=holeunit;
        _args.imageunit = imageunit;
        preImageQueue.inqueue(_args);

        for(int i=0;i<FieldNumber;i++) {
            ImageReduced[i].Clear();
            ImagePart[i].Clear();
        }
        QString info="拼图步骤"+ QString::number(FrameCount) + "完成！";
        log_singleton::Write_Log(info, Log_Level::General);
     } else {
        QString info="拼图步骤"+ QString::number(FrameCount) + "无玻璃！";
        log_singleton::Write_Log(info, Log_Level::General);
     }
     mosaickResult.clear();
     SubImage1.Clear();
     SubRegion1.Clear();
     RegionUnion1.Clear();
     RegionFillUp1.Clear();
     RegionOpening1.Clear();
     ConnectedRegions1.Clear();
     SelectedRegions1.Clear();
     RegionLines.Clear();
     RegionLines1.Clear();
     RegionLines2.Clear();
     RegionFLPanel.Clear();
     RegionOpeningFL.Clear();
     RegionClosingFL.Clear();
     RegionConnectionFL.Clear();
     SelectedRegionsFL.Clear();
     RegionUnion2Panel.Clear();
     RegionOpeningPanel.Clear();
     RegionConnectionPanel.Clear();
     RegionPanel.Clear();
     TileRectangle.Clear();
    } catch (HalconCpp::HException& Except) {
     qDebug() << "HalconHalconErr:" << Except.ErrorMessage().Text();
     qDebug() << "拼图步骤:" << QString::number(FrameCount) + "异常！";
     imageunit.ProcessStep = FrameCount;
     imageunit.GlassPositionInf=101;
     ErrFlag = true;
     imageunit.ErrorFlag=ErrFlag;
     GenEmptyObj(&imageunit.ImageList);
     GenEmptyObj(&imageunit.ImageRegion);
     GenEmptyObj(&imageunit.FrameRegion);
     imageunit = {};
     ImageTile1.Clear();
     ImageTile2.Clear();
     ImageTile3.Clear();
     ImageTile4.Clear();
     mosaickResult.clear();
     QString info="拼图步骤"+ QString::number(FrameCount) + "异常";
     log_singleton::Write_Log(info, Log_Level::General);
    }
}

// 离线模式调用的函数
void ProcessTile::OfflineTileImageProcess(QString fullpath)
{
    QString tile1Fullpath,tile2Fullpath,tile3Fullpath,tile4Fullpath;
    if (Global::isJpg) {
        tile1Fullpath = fullpath + QString("/tile1.jpg");
        tile2Fullpath = fullpath + QString("/tile2.jpg");
        tile3Fullpath = fullpath + QString("/tile3.jpg");
        tile4Fullpath = fullpath + QString("/tile4.jpg");
    } else {
        tile1Fullpath = fullpath + QString("/tile1.bmp");
        tile2Fullpath = fullpath + QString("/tile2.bmp");
        tile3Fullpath = fullpath + QString("/tile3.bmp");
        tile4Fullpath = fullpath + QString("/tile4.bmp");
    }

    bool res1 = QFile::exists(tile1Fullpath);
    bool res2 = QFile::exists(tile2Fullpath);
    bool res3 = QFile::exists(tile3Fullpath);
    bool res4 = QFile::exists(tile4Fullpath);
    for(int i=0; i<4;++i) {
        HObject mosaickthread;
        mosaickResult.push_back(mosaickthread);
    }
    if( res1 && res2 && res3 && res4) {
        ReadImage(&mosaickResult[0],tile1Fullpath.toStdString().data());
        ReadImage(&mosaickResult[1],tile2Fullpath.toStdString().data());
        ReadImage(&mosaickResult[2],tile3Fullpath.toStdString().data());
        ReadImage(&mosaickResult[3],tile4Fullpath.toStdString().data());
        GetDictTuple(Global::RecipeDict,"自定义参数",&UserDefinedDict);
        ProcessTile::PreProceeTile();
    } else {
        qDebug() << tile1Fullpath << tile2Fullpath << tile3Fullpath << tile4Fullpath << " is not exists()";
    }
}


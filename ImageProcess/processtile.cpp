#include "processtile.h"
#include "Global.h"
#include <QMessageBox>
#pragma execution_character_set("utf-8")

QQueue<ProcessTile::ImageUnit> ProcessTile::ImageQueue;
HObject ProcessTile::ImageTile1R;
HObject ProcessTile::ImageTile2R;
HObject ProcessTile::ImageTile3R;
HObject ProcessTile::ImageTile4R;
int ProcessTile::Cam1pixs;
int ProcessTile::Cam1Width;
int ProcessTile::Tile2Column1;
bool ProcessTile::ErrFlag;
bool ProcessTile::LastErrFlag;
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
    mosaickthread = new ThreadDo[FieldNumber];
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
}
//图像预处理
void ProcessTile::TileImageProcess()
{
    bool allCamerasStarted = true;
    bool allCameraIsNotEmpty;
    while (true) {
        //
        // 离线模式
        //
        if (Global::isOffline) {
            ProcessTile::OfflineTileImageProcess(Global::offlineFullPath);
            Global::isOffline = false;
            Global::offlineFullPath.clear();
            TileStep = 0;
        }
        //
        // 在线模式
        //
        switch (TileStep) {
            case 0:
                allCamerasStarted = true;
                for (auto camera : m_Cameras) {
                    if (!camera || !camera->IsStarted) {
                        allCamerasStarted = false;
                        break;
                    }
                }
                allCameraIsNotEmpty = true;
                if (allCamerasStarted) {
                    for(auto i:m_Cameras) {
                        if(i->m_AcquireImage->ImageQueue.empty()){
                            allCameraIsNotEmpty = false;
                            break;
                        }
                    }
                }
                if(allCamerasStarted && allCameraIsNotEmpty) {
                    qDebug() << "start1 :" << QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
                    qDebug() << "step :" << TileStep;
                    FrameCount = m_Cameras[0]->m_AcquireImage->ImageQueue.head().FrameCount;
                    if(FrameCount == 1) {
                        Global::ImageHeight = 0;
                        Global::ImageWidth = 0;
                        //Err标志位
                        ErrFlag=false;
                    }
                    //帧信号复位
                    Global::FrameSignal = 0;
                    GetDictTuple(Global::RecipeDict,"自定义参数",&UserDefinedDict);
                    TileStep = 10;
                 }
                break;
            case 10:
                for (int i = 0; i < FieldNumber; i++) {
                    qDebug() << "FieldNumber :" <<FieldNumber;
                    if(i<FieldNumber-1) {
                        for(int j=0;j<Global::camDefineNum;j++) {
                            qDebug() << "camDefineNum :" <<Global::camDefineNum;
                            qDebug() << "camDefineNum i :" <<i<< "ImageList.length() :"<<m_Cameras[j]->m_AcquireImage->ImageQueue.head().ImageList.length();
                            mosaickthread[i].CameraImageList.append(m_Cameras[j]->m_AcquireImage->ImageQueue.head().ImageList[i]) ;
                        }
                        mosaickthread[i].channel=0;
                    } else {
                        for(int j=0;j<Global::camDefineNum;j++) {
                            qDebug() << "camDefineNum :" <<Global::camDefineNum;
                            qDebug() << "camDefineNum i :" <<i<< "ImageList.length() :"<<m_Cameras[j]->m_AcquireImage->ImageQueue.head().ImageList.length();
                            mosaickthread[i].CameraImageList.append(m_Cameras[j]->m_AcquireImage->ImageQueue.head().ImageList[0]) ;
                        }
                        mosaickthread[i].channel=1;
                    }
                    mosaickthread[i].start();//开启线程
                }

                //等待所有线程执行完成
                for(int j=0;j<FieldNumber;j++) {
                    mosaickthread[j].wait();
                    mosaickthread[j].CameraImageList.clear();
                }

                qDebug() << "end :" << QDateTime::currentDateTime().toString("HH:mm:ss.zzz");

                HTuple isSaveOriImage;
                GetDictTuple(UserDefinedDict,"保存原图",&isSaveOriImage);
                if(isSaveOriImage==1) {
                    HTuple a=FrameCount;
                    HTuple str1 = "D:/qqqqqqqq"+a;
                    WriteImage(mosaickthread[0].MosaickResultImage,"jpg",0,str1+"1");
                    WriteImage(mosaickthread[1].MosaickResultImage,"jpg",0,str1+"2");
                    WriteImage(mosaickthread[2].MosaickResultImage,"jpg",0,str1+"3");
                }
                qDebug() << "mosaick success";

                for(int j=0;j<Global::camDefineNum;j++) {
                    m_Cameras[j]->m_AcquireImage->ImageQueue.dequeue();
                }
                PreProceeTile();
                TileStep = 0;
                break;
            }
            if(stopFlag_Tile==true)
                break;
        // 拼图操作异常
    }
    // 运行线程逻辑
}

void ProcessTile::PreProceeTile()
{
try {
     SetSystem("clip_region","false");
     HTuple ImageHeight;
     HTuple ImageWidth;
     HObject RegionFLPanel,RegionOpeningFL,RegionClosingFL,RegionConnectionFL,SelectedRegionsFL;
     HObject RegionUnion2Panel,RegionOpeningPanel,RegionConnectionPanel,RegionPanel;
     GetImageSize(mosaickthread[0].MosaickResultImage, &ImageWidth, &ImageHeight);
     if(FirstFrame==true)
     {
         HObject ImageP500;
         HObject ImageConcat;
         GenEmptyObj(&ImageConcat);
         CropPart(mosaickthread[0].MosaickResultImage,&ImageP500,0,0,ImageWidth,500);
         for (int j=1; j <= ImageHeight/500+2; j++)
         {
             ConcatObj(ImageConcat,ImageP500,&ImageConcat);
         }
          TileImages(ImageConcat,&BackGroundImage,1,"vertical") ;
        FirstFrame = false ;
        QString info="拼图步骤"+ QString::number(FrameCount) + "亮场背景处理完成！";
        log_singleton::Write_Log(info, Log_Level::General);
     }
     CropPart(BackGroundImage,&BackGroundImage, 0, 0, ImageWidth, ImageHeight);
//                HTuple str2 = "D:/q111"     ;
//                WriteImage(BackGroundImage,"jpg",0,str2);
     HTuple Row1,Column1,Phi1,Length1,Length2;
     HObject SubImage1,SubRegion1,RegionUnion1,RegionFillUp1,RegionOpening1,ConnectedRegions1,SelectedRegions1;
     HObject RegionLines, RegionLines1, RegionLines2;
     SubImage(BackGroundImage, mosaickthread[0].MosaickResultImage, &SubImage1, 1, 0);
     Threshold(SubImage1, &SubRegion1, 30, 255);
     GenRegionLine(&RegionLines1, ImageHeight - 1, 0, ImageHeight - 1, ImageWidth - 1);
     GenRegionLine(&RegionLines2, 0, 0, 0, ImageWidth - 1);
     Union2(RegionLines1, RegionLines2, &RegionLines);
     Union2(RegionLines,SubRegion1,&RegionUnion1);
     FillUp(RegionUnion1, &RegionFillUp1);
     OpeningCircle(RegionFillUp1,&RegionOpening1,1.5);
     Connection(RegionOpening1, &ConnectedRegions1);
     SelectShapeStd(ConnectedRegions1, &SelectedRegions1, "max_area", 70);

     //反射亮場
     Threshold(mosaickthread[1].MosaickResultImage, &RegionFLPanel, 20, 255);
     //孔region提取
     HObject RegionClosingKQ,RegionConnectionKQ,SelectedRegionsQK,RegionFillUpQK,DifferenceQK,RegionConnection1KQ,RegionQK;
     ClosingCircle(RegionFLPanel,&RegionClosingKQ,3.5);
     Connection(RegionClosingKQ,&RegionConnectionKQ);
     SelectShapeStd(RegionConnectionKQ, &SelectedRegionsQK, "max_area", 70);
     FillUp(SelectedRegionsQK, &RegionFillUpQK);
     Difference(RegionFillUpQK,SelectedRegionsQK,&DifferenceQK);
     Connection(DifferenceQK,&RegionConnection1KQ);
     SelectShape(RegionConnection1KQ,&RegionQK,"area","and",5000,999999999);

     RegionClosingKQ.Clear();
             RegionConnectionKQ.Clear();
             SelectedRegionsQK.Clear();
             RegionFillUpQK.Clear();
             DifferenceQK.Clear();
             RegionConnection1KQ.Clear();


     //反射亮場找面内區域
     OpeningCircle(RegionFLPanel,&RegionOpeningFL,1.5);
     ClosingCircle(RegionOpeningFL,&RegionClosingFL,30);
     Connection(RegionClosingFL,&RegionConnectionFL);
     SelectShapeStd(RegionConnectionFL, &SelectedRegionsFL, "max_area", 70);

     Union2(SelectedRegions1,SelectedRegionsFL,&RegionUnion2Panel);
     OpeningCircle(RegionUnion2Panel,&RegionOpeningPanel,1.5);
     Connection(RegionOpeningPanel,&RegionConnectionPanel);
     SelectShapeStd(RegionConnectionPanel, &RegionPanel, "max_area", 70);
     SelectShape(RegionPanel,&RegionPanel,"area","and",1,999999999);



     HTuple RegionPanelArea;
     RegionFeatures(RegionPanel,"area",&RegionPanelArea);
     qDebug()<<"RegionPanelArea"<<RegionPanelArea.ToString().Text();
     HTuple Number,PanelArea,RowPanel,ColumnPanel,PhiPanel,LengthPanel1,LengthPanel2;
     CountObj(RegionPanel, &Number);
      if (Number.TupleInt() > 0)
      {
        RegionFeatures(RegionPanel,"area",&PanelArea);
        SmallestRectangle2(RegionPanel, &RowPanel, &ColumnPanel, &PhiPanel, &LengthPanel1, &LengthPanel2);
        HTuple a=0.8*(4*LengthPanel1*LengthPanel2);
        HTuple Row1, Column1,Row2,Column2;
        SmallestRectangle1(RegionPanel,&Row1, &Column1, &Row2,&Column2);
//**************************************玻璃位置判断和截取区域提取start**********************************************************
        HTuple RegionRow2,QKNum;
        RegionFeatures(GlassRegion,"row2",&RegionRow2);
       //孔数量判断
        CountObj(RegionQK,&QKNum);
        HObject RegionPanelQK,RegionConnectionPanelQK,RegionContours,RegionPanelMoved;
        if(QKNum>0)
        {
            Difference(RegionPanel,RegionQK,&RegionPanelQK);
            Connection(RegionPanelQK,&RegionConnectionPanelQK);
            SelectShapeStd(RegionConnectionPanelQK, &RegionContours, "max_area", 70);
            RegionPanelQK.Clear();
            RegionConnectionPanelQK.Clear();
        }
        else
        {
            RegionContours=RegionPanel;
        }

           if((Column2-Column1>3000) && Row2-Row1>500)
           {
              if(Row1>0 && Row2<ImageHeight-1)
               {
                   //完整玻璃
                   GlassPosition=0;
                   GlassRegion.GenEmptyObj();
                   GlassRegion=RegionContours;
               }
               else
               {
                   if(Row1>0)
                   {
                       //玻璃头部
                       Global::CamRowsPerField=ImageHeight;
                       GlassPosition=1;
                       GlassRegion.GenEmptyObj();
                       GlassRegion=RegionContours;
                   }
                   else
                   {
                       if(Row2<ImageHeight-1)
                       {
                           //玻璃尾部
                           GlassPosition=3;
                       }
                       else
                       {
                           //玻璃中部
                           GlassPosition=2;
                       }

                   }
               }

               if(GlassPosition == 0 || GlassPosition==1 || FrameCount == 1)
               {
                  if(Column1>1000)
                  { TileColumn1=Column1-1000;}
                  else
                  {TileColumn1=0;}
                  if(ImageWidth-Column2>1000)
                  {
                  TileColumn2=Column2+1000;
                  }
                  else
                  {
                  TileColumn2=ImageWidth-1;
                  }
                  qDebug()<<"Column2//////////////////////////////////////////"<<Column2.ToString().Text();
                  qDebug() <<"TileColumn1"<<TileColumn1.ToString().Text();
                  qDebug()<<"TileColumn2"<<TileColumn2.ToString().Text();
                  qDebug() << "ImageHeighttttt :" << ImageHeight.ToString().Text();

               }
           }
           else
           {
              GlassPosition=3;
              QString info="拼图步骤"+ QString::number(FrameCount) + "玻璃有效区域占比小！定为玻璃尾部";
              log_singleton::Write_Log(info, Log_Level::General);
           }
           //玻璃region

           if(GlassPosition==2 || GlassPosition==3)
           {
               if(RegionRow2>0)
               {
                   MoveRegion(RegionContours,&RegionPanelMoved,RegionRow2,0);
                   Union2(GlassRegion,RegionPanelMoved,&GlassRegion);
                   RegionContours.Clear();
                   RegionPanelMoved.Clear();
               }
           }


           if(GlassPosition==3)
           {
               //一次扫描结束
               Global::FrameSignal=1;
           }

           if(FrameCount == 1 && Row1==0)
           {
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

             for(int i=0;i<FieldNumber;i++)
             {
              ReduceDomain(mosaickthread[i].MosaickResultImage, TileRectangle, &ImageReduced[i]);
              CropDomain(ImageReduced[i], &ImagePart[i]);
             }
           //拼整图
          if(GlassPosition!=0)
           {
           //拼接前
             if(GlassPosition==1)
             {
                 ImageTile1.GenEmptyObj();
                 ImageTile2.GenEmptyObj();
                 ImageTile3.GenEmptyObj();
                 ImageTile4.GenEmptyObj();
                     HTuple ImageHeight1;
                     HTuple ImageWidth1;
                     GetImageSize(ImagePart[0], &ImageWidth1, &ImageHeight1);
                     qDebug()<<"ImageWidth1"<<ImageWidth1.ToString().Text()<<"ImageHeight1"<<ImageHeight1.ToString().Text();
                     HObject ho_ImagePart[4],ho_ObjectsConcat[4],ho_TiledImage[4];
                  for(int i=0;i<FieldNumber;i++)
                  {
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

  //                                                      WriteImage(ho_TiledImage[0],"jpg",0,"D:/tile11");
  //                                                      WriteImage(ho_TiledImage[1],"jpg",0,"D:/tile12");
  //                                                      WriteImage(ho_TiledImage[2],"jpg",0,"D:/tile13");
  //                                                      WriteImage(ho_TiledImage[3],"jpg",0,"D:/tile14");

                     HTuple ImageHeight2;
                     HTuple ImageWidth2;
                     GetImageSize(ho_TiledImage[0], &ImageWidth2, &ImageHeight2);

                     qDebug()<<"ImageWidth2"<<ImageWidth2.ToString().Text()<<"ImageHeight2"<<ImageHeight2.ToString().Text();

                     for(int i=0;i<FieldNumber;i++)
                     {
                         GenEmptyObj(&ho_ImagePart[i]);
                         GenEmptyObj(&ho_ObjectsConcat[i]);
                         GenEmptyObj(&ho_TiledImage[i]);
                     }
             }
             else
             {
                     ConcatObj(ImageTile1, ImagePart[0], &ImageTile1);
                     ConcatObj(ImageTile2, ImagePart[1], &ImageTile2);
                     ConcatObj(ImageTile3, ImagePart[2], &ImageTile3);
                     ConcatObj(ImageTile4, ImagePart[3], &ImageTile4);
             }
           //拼接
             if (GlassPosition==3)
             {
                 HTuple NumTile;
                 CountObj(ImageTile1,&NumTile);
                 if(NumTile>0)
                 {
                     Cam1pixs=ImageWidth/2 - TileColumn1;
                     Cam1Width=ImageWidth/2;
                     Tile2Column1=TileColumn1;

                     if(Cam1pixs<0)
                     {
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
                     if(isSaveWholeImage==1)
                     {
                         WriteImage(ImageTile1R,"jpg",0,"D:/tile1");
                         WriteImage(ImageTile2R,"jpg",0,"D:/tile2");
                         WriteImage(ImageTile3R,"jpg",0,"D:/tile3");
                         WriteImage(ImageTile4R,"jpg",0,"D:/tile4");
                     }
                     GenEmptyObj(&ImageTile1);
                     GenEmptyObj(&ImageTile2);
                     GenEmptyObj(&ImageTile3);
                     GenEmptyObj(&ImageTile4);
                 }
               }
            }
            else
          {
              ImageTile1R = ImagePart[0];
              ImageTile2R = ImagePart[1];
              ImageTile3R = ImagePart[2];
              ImageTile4R = ImagePart[3];
          }
       //判断玻璃尾端
          qDebug() << "lastGlassPosition :" << lastGlassPosition;
          qDebug() << "GlassPosition :" << GlassPosition;
           if(GlassPosition==3 && (lastGlassPosition==2 || lastGlassPosition==1))
           {
                HObject ObjectsConcat[3];
               //玻璃尾部，拼接上张图像尾部1000行
               for(int i=0;i<FieldNumber-1;i++)
               {
                   HTuple ImageHeight1;
                   HTuple ImageWidth1;
                  GetImageSize(ImagePart[0], &ImageWidth1, &ImageHeight1);
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
           }
           else
           {
               if(GlassPosition==1 || GlassPosition==2)
               {
                   if(ImageHeight>1000)
                   {
                       //截取图像尾部1000行
                       HObject CropRectangle,ImageCropRecReduced[3];
                       GenRectangle1(&CropRectangle, ImageHeight -1 -1000, TileColumn1,ImageHeight - 1 , TileColumn2);
                       for(int i=0;i<FieldNumber-1;i++)
                       {
                        ReduceDomain(mosaickthread[i].MosaickResultImage, CropRectangle, &ImageCropRecReduced[i]);
                        CropDomain(ImageCropRecReduced[i], &ImageCrop[i]);
                        ImageCropRecReduced[i].Clear();
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
                   }
                   else
                   {
                       QString info="拼图步骤"+ QString::number(FrameCount) + "图像高度小于1000！";
                       log_singleton::Write_Log(info, Log_Level::General);
                   }
               }
           }
           lastGlassPosition=GlassPosition;
           //**************************************玻璃位置判断和截取区域提取end**********************************************************


//**************************************************************************存图****************************************************************************

           HTuple isSaveCropImage;
           GetDictTuple(UserDefinedDict,"保存裁剪图像",&isSaveCropImage);
           if(isSaveCropImage==1)
           {
               HTuple b= FrameCount;
               WriteImage(ImagePart[0], "jpg", 0, "D:/QQQ1"+b);
               WriteImage(ImagePart[1], "jpg", 0, "D:/QQQ2"+b);
               WriteImage(ImagePart[2], "jpg", 0, "D:/QQQ3"+b);
           }

//**************************************************************************存图****************************************************************************
                                GenEmptyObj(&imageunit.ImageList);
                                ConcatObj(imageunit.ImageList, ImagePart[0], &imageunit.ImageList);
                                ConcatObj(imageunit.ImageList, ImagePart[1], &imageunit.ImageList);
                                ConcatObj(imageunit.ImageList, ImagePart[2], &imageunit.ImageList);
 //                               ConcatObj(imageunit.ImageList, ImagePart[3], &imageunit.ImageList);


                                HTuple ImageListNum;
                                CountObj(imageunit.ImageList, &ImageListNum);
                                qDebug() << "ImageListNum :" << ImageListNum.ToString().Text();
                                imageunit.GlassPositionInf=GlassPosition;
                                imageunit.ProcessStep = FrameCount;
                                imageunit.ErrorFlag=ErrFlag;
                                imageunit.ImageRegion=GlassRegion;
                                imageunit.FrameRegion=RegionFrame;
                                ImageQueue.enqueue(imageunit);

                                for(int i=0;i<FieldNumber;i++)
                                {
                                    ImageReduced[i].Clear();
                                    ImagePart[i].Clear();
                                }
                                imageunit = {};
                                QString info="拼图步骤"+ QString::number(FrameCount) + "完成！";
                                log_singleton::Write_Log(info, Log_Level::General);
      }
      else
      {
          QString info="拼图步骤"+ QString::number(FrameCount) + "无玻璃！";
          log_singleton::Write_Log(info, Log_Level::General);
      }
      for(int i=0;i<FieldNumber;i++)
      {
        mosaickthread[i].MosaickResultImage.Clear();
      }
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
         ErrFlag=true;
         imageunit.ErrorFlag=ErrFlag;
         GenEmptyObj(&imageunit.ImageList);
         GenEmptyObj(&imageunit.ImageRegion);
         GenEmptyObj(&imageunit.FrameRegion);
         ImageQueue.enqueue(imageunit);
         imageunit = {};
         ImageTile1.Clear();
         ImageTile2.Clear();
         ImageTile3.Clear();
         ImageTile4.Clear();
         for(int i=0;i<FieldNumber;i++)
         {
           mosaickthread[i].MosaickResultImage.Clear();
         }
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
    if( res1 && res2 && res3 && res4) {
        ReadImage(&mosaickthread[0].MosaickResultImage,tile1Fullpath.toStdString().data());
        ReadImage(&mosaickthread[1].MosaickResultImage,tile2Fullpath.toStdString().data());
        ReadImage(&mosaickthread[2].MosaickResultImage,tile3Fullpath.toStdString().data());
        ReadImage(&mosaickthread[3].MosaickResultImage,tile4Fullpath.toStdString().data());
        GetDictTuple(Global::RecipeDict,"自定义参数",&UserDefinedDict);
        ProcessTile::PreProceeTile();
    } else {
        qDebug() << tile1Fullpath << tile2Fullpath << tile3Fullpath << tile4Fullpath << " is not exists()";
    }
}


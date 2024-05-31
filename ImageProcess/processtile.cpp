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
    GlassPosition = GlassPart::Complete;
    lastGlassPosition = GlassPart::Complete;
    ErrFlag=false;
    FirstFrame = true;
    FieldNumber = PARAM.getFieldNumberSet() + 1;   //光场数量
    TileColumn1=HTuple();
    TileColumn2=HTuple();
    GenEmptyObj(&TileRectangle);
    mosaickthread = new ThreadDo[FieldNumber];
    qDebug()<<"FieldNumber"<<FieldNumber;
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
    bool allCamerasStarted = true;  //声明一个布尔变量 allCamerasStarted，用于跟踪所有相机是否已经启动
    bool allCameraIsNotEmpty;       //声明一个布尔变量 allCameraIsNotEmpty，用于检查所有相机的图像队列是否不为空。
    while (true) {
        //
        // 离线模式
        //
        if (PARAM.getIsOffline()) {
            qDebug()<<"PARAM.getIsOffline() = " <<PARAM.getIsOffline();
            //开始离线拼接图片
            ProcessTile::OfflineTileImageProcess(PARAM.getOfflineFullPath());
            PARAM.setIsOffline(false);
            //PARAM.setOfflineFullPath("");
            TileStep = 0;

        }
        //
        // 在线模式
        //
        switch (TileStep) {
            case 0:
                allCamerasStarted = true;
                //检查m_Cameras容器中的所有相机是否都已经启动
                for (auto camera : m_Cameras) {     //auto关键字让编译器自动推断camera的类型
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
                    FrameCount = m_Cameras[0]->m_AcquireImage->ImageQueue.head().FrameCount;//相机拍照的帧数
                    if(FrameCount == 1) {
                        PARAM.setImageHeight(0);
                        PARAM.setImageWidth(0);
                        //Err标志位
                        ErrFlag=false;
                    }
                    //帧信号复位
                    PARAM.setFrameSignal(0);

                    //GetDictTuple: Halcon算子，从字典中检索与键关联的元组
                    //控制输入参数1：字典句柄；控制输入参数2：键字符串；控制输出参数：从字典中检索的元组值。
                    GetDictTuple(PARAM.getRecipeDict(),"自定义参数",&UserDefinedDict);
                    TileStep = 10;
                 }
                break;
            case 10:
                for (int i = 0; i < FieldNumber; i++) {
                    qDebug() << "FieldNumber :" <<FieldNumber;
                    if( i < FieldNumber-1 ) {
                        for(int j=0;j<PARAM.getCamDefineNum();j++) {
                            qDebug() << "camDefineNum :" <<PARAM.getCamDefineNum();
                            qDebug() << "camDefineNum i :" <<i<< "ImageList.length() :"<<m_Cameras[j]->m_AcquireImage->ImageQueue.head().ImageList.length();

                            //将当前相机的图像列表中的第i个图像添加到mosaickthread数组中索引为i的线程的CameraImageList中
                            //mosaickthread[i].CameraImageList中的图片个数为相机个数
                            mosaickthread[i].CameraImageList.append(m_Cameras[j]->m_AcquireImage->ImageQueue.head().ImageList[i]) ;
                        }
                        mosaickthread[i].channel=0;
                    } else {
                        for(int j=0;j<PARAM.getCamDefineNum();j++) {
                            qDebug() << "camDefineNum :" <<PARAM.getCamDefineNum();
                            qDebug() << "camDefineNum i :" <<i<< "ImageList.length() :"<<m_Cameras[j]->m_AcquireImage->ImageQueue.head().ImageList.length();
                            mosaickthread[i].CameraImageList.append(m_Cameras[j]->m_AcquireImage->ImageQueue.head().ImageList[0]) ;
                        }
                        mosaickthread[i].channel=1;
                    }

                    //开启线程，主要实现功能是将每个相机在同一帧获得的图片进行横向拼接
                    mosaickthread[i].start();
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

                //清空相机图片列表
                for(int j=0;j<PARAM.getCamDefineNum();j++) {
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
     //SetSystem：这是一个 Halcon 函数，用于设置系统参数。
     //"clip_region"：这是一个系统参数的名称，用于控制图像操作时是否剪裁图像区域。
     //"false"：这是一个字符串，表示不进行图像区域的剪裁
     SetSystem("clip_region","false");

     //HTuple：这是 Halcon 库中的一个数据类型，用于存储单个值或一系列值。
     HTuple ImageHeight;
     HTuple ImageWidth;

     //HObject 是一个特殊的数据类型，它代表了 Halcon 中的一个图像对象。
     HObject RegionFLPanel,RegionOpeningFL,RegionClosingFL,RegionConnectionFL,SelectedRegionsFL;
     HObject RegionUnion2Panel,RegionOpeningPanel,RegionConnectionPanel,RegionPanel;

     //Halcon算子，用于获取图像的大小
     //图像输入参数1：图像；控制输出参数1：图像的宽度；控制输出参数2：图像的高度。
     GetImageSize(mosaickthread[0].MosaickResultImage, &ImageWidth, &ImageHeight);


     //生成亮场背景图 
     if (FirstFrame==true) {
         HObject ImageP500;
         HObject ImageConcat;
         GenEmptyObj(&ImageConcat);     //初始化 ImageConcat 为一个空的 HObject

         //在 mosaickthread[0].MosaickResultImage 中从起始点（0，0）裁剪出一个宽度为 ImageWidth 像素，高度为 500 像素的小图像，并将其存储在 ImageP500 中。
         CropPart(mosaickthread[0].MosaickResultImage,&ImageP500,0,0,ImageWidth,500);

         //目的是使BackGroundImage的高度为500的整数倍，且保证 ImageConcat的高度 - ImageHight < 500。
         for (int j=1; j <= ImageHeight/500+2; j++) {
             //将ImageConcat与ImageP500两个区域组合成区域集，并将结果存储回 ImageConcat
             ConcatObj(ImageConcat,ImageP500,&ImageConcat);
         }
         //将 ImageConcat 中的图像平铺到 BackGroundImage 上，以垂直方向排成1列
         TileImages(ImageConcat,&BackGroundImage,1,"vertical") ;

        FirstFrame = false ;
        QString info="拼图步骤"+ QString::number(FrameCount) + "亮场背景处理完成！";
        log_singleton::Write_Log(info, Log_Level::General);     //将日志信息写入日志系统。
     }
     //在 BackGroundImage 中从起始点（0，0）裁剪出一个宽度为 ImageWidth 像素，高度为 ImageHeight 像素的图像，并将其存储回 BackGroundImage 中。
     CropPart(BackGroundImage,&BackGroundImage, 0, 0, ImageWidth, ImageHeight);

     HTuple Row1,Column1,Phi1,Length1,Length2;
     HObject SubImage1,SubRegion1,RegionUnion1,RegionFillUp1,RegionOpening1,ConnectedRegions1,SelectedRegions1;
     HObject RegionLines, RegionLines1, RegionLines2;

     //图像相减，SubImage1 =( BackGroundImage - MosaickResultImage ) * 1 + 0
     SubImage(BackGroundImage, mosaickthread[0].MosaickResultImage, &SubImage1, 1, 0);
     //全局阈值分割
     Threshold(SubImage1, &SubRegion1, 30, 255);

     //生成一条连接 (Row1, Col1) 和 (Row2, Col2) 两点的直线，并将其赋值给 RegionLines1 变量。
     GenRegionLine(&RegionLines1, ImageHeight - 1, 0, ImageHeight - 1, ImageWidth - 1);
     GenRegionLine(&RegionLines2, 0, 0, 0, ImageWidth - 1);

     //将两个区域合并成一个整体
     Union2(RegionLines1, RegionLines2, &RegionLines);
     Union2(RegionLines,SubRegion1,&RegionUnion1);

     //填充区域中的孔、裂缝
     FillUp(RegionUnion1, &RegionFillUp1);
     //开运算
     OpeningCircle(RegionFillUp1,&RegionOpening1,1.5);
     //将不相连的区域都分割成单独的区域
     Connection(RegionOpening1, &ConnectedRegions1);
     //选择给定形状的区域，'max_area' 选择最大的区域，相似度70
     SelectShapeStd(ConnectedRegions1, &SelectedRegions1, "max_area", 70);

     //对反射亮場做全局阈值分割
     Threshold(mosaickthread[1].MosaickResultImage, &RegionFLPanel, 20, 255);

     HObject RegionClosingKQ,RegionConnectionKQ,SelectedRegionsQK,RegionFillUpQK,DifferenceQK,RegionConnection1KQ,RegionQK;
     //闭运算
     ClosingCircle(RegionFLPanel,&RegionClosingKQ,3.5);
     Connection(RegionClosingKQ,&RegionConnectionKQ);
     SelectShapeStd(RegionConnectionKQ, &SelectedRegionsQK, "max_area", 70);
     FillUp(SelectedRegionsQK, &RegionFillUpQK);

     //计算两个区域的差集，第1区域剩下部分形成新的区域
     Difference(RegionFillUpQK,SelectedRegionsQK,&DifferenceQK);
     Connection(DifferenceQK,&RegionConnection1KQ);

     //孔region提取
     //从一组区域中选择特定属性的区域。基于区域的面积"area"，必须同时"and"满足最小值5000和最大值999999999的条件
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
     //计算玻璃面积
     RegionFeatures(RegionPanel,"area",&RegionPanelArea);
     qDebug()<<"RegionPanelArea"<<RegionPanelArea.ToString().Text();
     HTuple Number,PanelArea,RowPanel,ColumnPanel,PhiPanel,LengthPanel1,LengthPanel2;
     //计算输入区域中连通域的个数
     CountObj(RegionPanel, &Number);
     if (Number.TupleInt() > 0) {
        RegionFeatures(RegionPanel,"area",&PanelArea);

        //求最小包围矩形
//        SmallestRectangle2(RegionPanel, &RowPanel, &ColumnPanel, &PhiPanel, &LengthPanel1, &LengthPanel2);
//        HTuple a=0.8*(4*LengthPanel1*LengthPanel2);

        HTuple Row1, Column1,Row2,Column2;
        //求输入区域的平行于坐标系的最小外包矩形
        SmallestRectangle1(RegionPanel,&Row1, &Column1, &Row2,&Column2);
//**************************************玻璃位置判断和截取区域提取start**********************************************************
        HTuple RegionRow2,QKNum;

        //获得输入区域右下角行坐标
        RegionFeatures(GlassRegion,"row2",&RegionRow2);
       //孔数量判断
        CountObj(RegionQK,&QKNum);
        HObject RegionPanelQK,RegionConnectionPanelQK,RegionContours,RegionPanelMoved;
        if (QKNum>0) {
            //计算RegionPanel与RegionQK区域的差集，RegionPanel区域剩下部分形成新的区域
            Difference(RegionPanel,RegionQK,&RegionPanelQK);
            Connection(RegionPanelQK,&RegionConnectionPanelQK);
            SelectShapeStd(RegionConnectionPanelQK, &RegionContours, "max_area", 70);
            RegionPanelQK.Clear();
            RegionConnectionPanelQK.Clear();
        } else {
            RegionContours = RegionPanel;
        }

        if ((Column2 - Column1 > 3000) && Row2 - Row1 > 500) {
          if (Row1>0 && Row2<ImageHeight-1) {
               //完整玻璃
               GlassPosition = GlassPart::Complete;
               GlassRegion.GenEmptyObj();   //调用了Halcon对象的GenEmptyObj方法，生成一个空的区域对象
               GlassRegion = RegionContours;
           } else {
               if (Row1>0) {
                   //玻璃头部
                   PARAM.setCamRowsPerField(ImageHeight);
                   GlassPosition = GlassPart::HeadPart;
                   GlassRegion.GenEmptyObj();
                   GlassRegion = RegionContours;
               } else {//尾部或中部
                   if(Row2<ImageHeight-1) {
                       //玻璃尾部
                       GlassPosition = GlassPart::TailPart;
                   } else {
                       //玻璃中部
                       GlassPosition = GlassPart::MidPart;
                   }
               }
           }

           if (GlassPosition == GlassPart::Complete || GlassPosition==GlassPart::HeadPart || FrameCount == 1) {
              if(Column1 > 1000) {
                  TileColumn1 = Column1-1000;
              } else {
                  TileColumn1 = 0;
              }
              if( ImageWidth - Column2 > 1000 ) {
                TileColumn2 = Column2 + 1000;
              } else {
                TileColumn2 = ImageWidth - 1;
              }
              qDebug()<<"Column2//////////////////////////////////////////"<<Column2.ToString().Text();
              qDebug() <<"TileColumn1"<<TileColumn1.ToString().Text();
              qDebug()<<"TileColumn2"<<TileColumn2.ToString().Text();
              qDebug() << "ImageHeighttttt :" << ImageHeight.ToString().Text();

           }
        } else {
          GlassPosition = GlassPart::TailPart;
          QString info="拼图步骤"+ QString::number(FrameCount) + "玻璃有效区域占比小！定为玻璃尾部";
          log_singleton::Write_Log(info, Log_Level::General);
        }
        //玻璃region

        if (GlassPosition==GlassPart::MidPart || GlassPosition==GlassPart::TailPart) {
           if(RegionRow2>0) {
               MoveRegion(RegionContours,&RegionPanelMoved,RegionRow2,0);   //平移
               Union2(GlassRegion,RegionPanelMoved,&GlassRegion);
               RegionContours.Clear();
               RegionPanelMoved.Clear();
           }
        }

        if(GlassPosition == GlassPart::TailPart) {
           //一次扫描结束
           PARAM.setFrameSignal(1);
        }

        if(FrameCount == 1 && Row1==0) {
           QString info="拼图步骤"+ QString::number(FrameCount) + "玻璃头部未扫描";
           log_singleton::Write_Log(info, Log_Level::General);
        }
        //单帧玻璃区域矫正
        MoveRegion(RegionPanel,&RegionFrame,0,-TileColumn1);
        //生成一个平行于坐标轴的矩形，截取有效区域
        GenRectangle1(&TileRectangle, 0, TileColumn1,ImageHeight - 1 , TileColumn2);
        HTuple width1;
        RegionFeatures(TileRectangle,"width",&width1);
        qDebug() << "width1 :" << width1.ToString().Text();
        HObject ImageReduced[4];
        HObject ImagePart[4];

         for(int i=0;i<FieldNumber;i++) {
             //mosaickthread[i].MosaickResultImage是输入的图像；TileRectangle是输入的区域；ImageReduced[i]是输出的图像，是mosaickthread[i].MosaickResultImage中Region的那部分图像。
             ReduceDomain(mosaickthread[i].MosaickResultImage, TileRectangle, &ImageReduced[i]);
             //ImageReduced[i]是输入的原始图像；ImagePart[i]是输出的最小外界正矩形的图像，也就是说，如果一副大图上，就一块区域有值，其他区域均没有值。通过调用该函数，能够将有值的区域以最小外界正矩形的方式返回，而剪掉那些没有值的区域。
             CropDomain(ImageReduced[i], &ImagePart[i]);
         }
        //拼整图
        if (GlassPosition!=GlassPart::Complete) {
            //拼接前
            if (GlassPosition==GlassPart::HeadPart) {
                ImageTile1.GenEmptyObj();
                ImageTile2.GenEmptyObj();
                ImageTile3.GenEmptyObj();
                ImageTile4.GenEmptyObj();
                HTuple ImageHeight1;
                HTuple ImageWidth1;
                GetImageSize(ImagePart[0], &ImageWidth1, &ImageHeight1);
                qDebug()<<"ImageWidth1"<<ImageWidth1.ToString().Text()<<"ImageHeight1"<<ImageHeight1.ToString().Text();
                HObject ho_ImagePart[4],ho_ObjectsConcat[4],ho_TiledImage[4];
                for(int i=0; i<FieldNumber; i++) {
                    CropPart(ImagePart[i], &ho_ImagePart[i], 0, 0, ImageWidth1, 200);
                    GenEmptyObj(&ho_ObjectsConcat[i]);
                    ConcatObj(ho_ImagePart[i], ImagePart[i], &ho_ObjectsConcat[i]);

                    //将多张图像拼接成一张大图像
                    //TileImagesOffset(Images, &TiledImage,OffsetRow, OffsetCol, Row1, Col1, Row2, Col2, Width, Height)
                    //Images (input_object)：输入图像
                    //TiledImage (output_object)：拼接后图像
                    //OffsetRow (input_control)：拼接后图像中输入图像左上角的行坐标
                    //OffsetCol (input_control)：拼接后图像中输入图像左上角的列坐标
                    //Row1 (input_control)：裁切图像左上角行坐标
                    //Col1 (input_control)：裁切图像左上角列坐标
                    //Row2 (input_control)：裁切图像右下角行坐标
                    //Col2 (input_control)：裁切图像右下角列坐标
                    //Width (input_control)：拼接后图像宽
                    //Height (input_control)：拼接后图像高
                    TileImagesOffset(ho_ObjectsConcat[i],
                                  &ho_TiledImage[i],
                                  (HTuple(0).Append(200)),
                                  (HTuple(0).Append(0)),
                                  (HTuple(-1).Append(-1)),
                                  (HTuple(-1).Append(-1)),
                                  (HTuple(-1).Append(-1)),
                                  (HTuple(-1).Append(-1)),
                                  ImageWidth1,
                                  ImageHeight+200);
                }


                 ConcatObj(ImageTile1, ho_TiledImage[0], &ImageTile1);
                 ConcatObj(ImageTile2, ho_TiledImage[1], &ImageTile2);
                 ConcatObj(ImageTile3, ho_TiledImage[2], &ImageTile3);
                 ConcatObj(ImageTile4, ho_TiledImage[3], &ImageTile4);

                 HTuple ImageHeight2;
                 HTuple ImageWidth2;
                 GetImageSize(ho_TiledImage[0], &ImageWidth2, &ImageHeight2);

                 qDebug()<<"ImageWidth2"<<ImageWidth2.ToString().Text()<<"ImageHeight2"<<ImageHeight2.ToString().Text();

                 //清除临时变量
                 for (int i=0;i<FieldNumber;i++) {
                     GenEmptyObj(&ho_ImagePart[i]);
                     GenEmptyObj(&ho_ObjectsConcat[i]);
                     GenEmptyObj(&ho_TiledImage[i]);
                 }
         } else {//玻璃中部、尾部
             ConcatObj(ImageTile1, ImagePart[0], &ImageTile1);
             ConcatObj(ImageTile2, ImagePart[1], &ImageTile2);
             ConcatObj(ImageTile3, ImagePart[2], &ImageTile3);
             ConcatObj(ImageTile4, ImagePart[3], &ImageTile4);
         }
        //拼接
         if (GlassPosition==GlassPart::TailPart) {
             HTuple NumTile;
             CountObj(ImageTile1,&NumTile);
             if(NumTile>0) {
                 TileImages(ImageTile1, &ImageTile1R, 1, "vertical");
                 TileImages(ImageTile2, &ImageTile2R, 1, "vertical");
                 TileImages(ImageTile3, &ImageTile3R, 1, "vertical");
                 TileImages(ImageTile4, &ImageTile4R, 1, "vertical");

                 QString info="拼图步骤"+ QString::number(FrameCount) + "开始写入数据！";
                 log_singleton::Write_Log(info, Log_Level::General);
                 HTuple isSaveWholeImage;
                 GetDictTuple(UserDefinedDict,"保存整图",&isSaveWholeImage);
                 if (isSaveWholeImage == 1) {
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
        } else {
          ImageTile1R = ImagePart[0];
          ImageTile2R = ImagePart[1];
          ImageTile3R = ImagePart[2];
          ImageTile4R = ImagePart[3];
        }

        //判断玻璃尾端
        qDebug() << "lastGlassPosition :" << lastGlassPosition;
        qDebug() << "GlassPosition :" << GlassPosition;
        if ( GlassPosition==GlassPart::TailPart && (lastGlassPosition == GlassPart::MidPart || lastGlassPosition == GlassPart::HeadPart)) {
            HObject ObjectsConcat[3];
            //玻璃尾部，拼接上张图像尾部1000行
            for (int i=0; i<FieldNumber-1; i++) {
                HTuple ImageHeight1;
                HTuple ImageWidth1;
                GetImageSize(ImagePart[0], &ImageWidth1, &ImageHeight1);
                ConcatObj(ImageCrop[i], ImagePart[i], &ObjectsConcat[i]);
                TileImagesOffset(ObjectsConcat[i],
                                 &ImagePart[i],
                                 (HTuple(0).Append(1000)),
                                 (HTuple(0).Append(0)),
                                 (HTuple(-1).Append(-1)),
                                 (HTuple(-1).Append(-1)),
                                 (HTuple(-1).Append(-1)),
                                 (HTuple(-1).Append(-1)),
                                 ImageWidth1,
                                 ImageHeight1+1000);
            }
            HObject RegionsFrameMoved;
            MoveRegion(RegionFrame,&RegionsFrameMoved,1000,0);
            Union2(RegionsFrameMoved,RegionsFrameCrop,&RegionFrame);
            RegionsFrameMoved.Clear();
            RegionsFrameCrop.Clear();
            ObjectsConcat->Clear();
        } else {
            if (GlassPosition == GlassPart::HeadPart || GlassPosition == GlassPart::MidPart) {
                   if (ImageHeight>1000) {
                       //截取图像尾部1000行
                       HObject CropRectangle,ImageCropRecReduced[3];
                       GenRectangle1(&CropRectangle, ImageHeight -1 -1000, TileColumn1,ImageHeight - 1 , TileColumn2);
                       for (int i=0;i<FieldNumber-1;i++) {
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
                       //获取SelectedRegionsFrame区域左上角行坐标
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


           //*****************************************存图****************************************************************************

           HTuple isSaveCropImage;
           GetDictTuple(UserDefinedDict,"保存裁剪图像",&isSaveCropImage);
           if(isSaveCropImage==1) {
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
 //        ConcatObj(imageunit.ImageList, ImagePart[3], &imageunit.ImageList);


           HTuple ImageListNum;
           CountObj(imageunit.ImageList, &ImageListNum);
           qDebug() << "ImageListNum :" << ImageListNum.ToString().Text();
           imageunit.GlassPositionInf=GlassPosition;
           imageunit.ProcessStep = FrameCount;
           imageunit.ErrorFlag=ErrFlag;
           imageunit.ImageRegion=GlassRegion;
           imageunit.FrameRegion=RegionFrame;
           ImageQueue.enqueue(imageunit);

           for(int i=0;i<FieldNumber;i++){
               ImageReduced[i].Clear();
               ImagePart[i].Clear();
           }
           imageunit = {};
           QString info="拼图步骤"+ QString::number(FrameCount) + "完成！";
           log_singleton::Write_Log(info, Log_Level::General);
      } else {
          QString info="拼图步骤"+ QString::number(FrameCount) + "无玻璃！";
          log_singleton::Write_Log(info, Log_Level::General);
      }
      for(int i=0;i<FieldNumber;i++) {
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
        for (int i=0;i<FieldNumber;i++) {
            mosaickthread[i].MosaickResultImage.Clear();
        }
        QString info="拼图步骤"+ QString::number(FrameCount) + "异常";
        log_singleton::Write_Log(info, Log_Level::General);
    }
}

// 离线模式调用的函数
void ProcessTile::OfflineTileImageProcess(QString fullpath)
{
    qDebug()<<__FUNCTION__;
    //定义了四个 QString 类型的变量，用于存储各图像的完整路径
    QString tile1Fullpath,tile2Fullpath,tile3Fullpath,tile4Fullpath;
    if (PARAM.getIsJpg()) {
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

    // 检查每个图像文件是否存在。QFile::exists 函数返回一个布尔值，如果文件存在则返回 true，否则返回 false。
    bool res1 = QFile::exists(tile1Fullpath);
    bool res2 = QFile::exists(tile2Fullpath);
    bool res3 = QFile::exists(tile3Fullpath);
    bool res4 = QFile::exists(tile4Fullpath);

    if( res1 && res2 && res3 && res4) {

        //ReadImage：Halcon算子，读取图片
        //ReadImage(Image, Filename)：Image为输出对象，Filename为输入图片地址。
        //对于每个存在的图像文件，调用 ReadImage 函数将其读入到 mosaickthread 数组中对应的 MosaickResultImage 成员变量中。
        ReadImage(&mosaickthread[0].MosaickResultImage,tile1Fullpath.toStdString().data());
        ReadImage(&mosaickthread[1].MosaickResultImage,tile2Fullpath.toStdString().data());
        ReadImage(&mosaickthread[2].MosaickResultImage,tile3Fullpath.toStdString().data());
        ReadImage(&mosaickthread[3].MosaickResultImage,tile4Fullpath.toStdString().data());

        //GetDictTuple: Halcon算子，从字典中检索与键关联的元组
        //控制输入参数1：字典句柄；控制输入参数2：键字符串；控制输出参数：从字典中检索的元组值。
        GetDictTuple(PARAM.getRecipeDict(),"自定义参数",&UserDefinedDict);
        ProcessTile::PreProceeTile();
    } else {
        qDebug() << tile1Fullpath << tile2Fullpath << tile3Fullpath << tile4Fullpath << " is not exists()";
    }
}


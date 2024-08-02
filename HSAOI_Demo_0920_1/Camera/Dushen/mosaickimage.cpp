#include "mosaickimage.h"
#include "Global.h"
#pragma execution_character_set("utf-8")

MosaickImage::MosaickImage()
{
}

MosaickImage::MosaickImage( const MosaickImage& mo)
{
    mosaickQueue = mo.mosaickQueue;
    MosaickResultImage = mo.MosaickResultImage;
}

MosaickImage& MosaickImage::operator=(const MosaickImage& mo)
{
    if(this != &mo) {
        mosaickQueue = mo.mosaickQueue;
        MosaickResultImage = mo.MosaickResultImage;
    }
    return *this;
}


HObject MosaickImage::run()
{
    if (!mosaickQueue.empty()){
         MosaickArg arg;
         mosaickQueue.dequeue(arg);
         MosaickImage::DoMosaick(arg.CameraImageList, arg.channel, arg.PrepareImage, MosaickResultImage);
    }
    return MosaickResultImage;
}

void MosaickImage::DoMosaick(QList<HObject> CameraImageList, int channel, HObject PrepareImage, HObject& FiledImage)
{
   try{
        QElapsedTimer timer;
        timer.start();
        HTuple DefectDict;
        GetDictTuple(Global::RecipeDict,"缺陷检测",&DefectDict);
        HTuple PixelDif12,PixelDif23,PixelDif24,thickness,siyindistance,overlap,overlapsiyin;
        GetDictTuple(DefectDict,"12相机像素偏差",&PixelDif12);
        GetDictTuple(DefectDict,"玻璃厚度",&thickness);
        GetDictTuple(DefectDict,"丝印离辊道距离",&siyindistance);
        GetDictTuple(DefectDict,"23相机像素偏差",&PixelDif23);
        GetDictTuple(DefectDict,"24相机像素偏差",&PixelDif24);
        qDebug()<<"1-2相机像素偏差"<<PixelDif12.ToString().Text();

        overlapsiyin=(184-8192*(1-(1457.7-(siyindistance-6))/1457.700))/2;
        overlap=(184-8192*(1-(1457.7-(thickness-6))/1457.700))/2;

//        int Thickness=thickness;
//        switch (Thickness){
//          case 10:
//            overlap=9;
//            overlapsiyin=18;
//            break;
//          case 8:
//            overlap=92;//15 8mm:86 6mm:92\88
//            overlapsiyin=23;
//            break;
//          case 5:
//            overlap=18;
//            overlapsiyin=27;
//        }

        if(overlapsiyin<0)
            overlapsiyin=0;

        if(overlap<0)
            overlap=0;

       QList<HTuple> PixelDifList;
       PixelDifList<<PixelDif12<<PixelDif23<<PixelDif24;
       qDebug()<<"1-2相机像素偏差"<<PixelDif12.ToString().Text()<<PixelDifList[0].ToString().Text();
       HTuple ImageHeight;
       HTuple ImageWidth;

       GetImageSize(CameraImageList[0], &ImageWidth, &ImageHeight);
       qDebug() << "ImageWidth :" << ImageWidth.ToString().Text();
       qDebug() << "ImageHeight :" << ImageHeight.ToString().Text();
    // + PixelDif12
       QList<HTuple> a1,a2,a3,a4;
       a1<<50<<52<<50<<50;
       a2<<0<<overlap<<88<<38<<0<<overlapsiyin<<77<<88<<99;
       a3<<ImageWidth-overlap<<ImageWidth-overlap<<ImageWidth-29<<ImageWidth-29<<ImageWidth-overlapsiyin<<ImageWidth-overlapsiyin<<ImageWidth-15<<ImageWidth-15;
       a4<<ImageHeight - 200;
       if(channel==0) {
            for(int i=0;i<Global::camDefineNum;i++)
                CropPart(CameraImageList[i],&CameraImageList[i],a1[i],a2[i],a3[i],a4[0]);
        } else {//最后一帧
            for(int i=0;i<Global::camDefineNum;i++)
                CropPart(CameraImageList[i],&CameraImageList[i],a1[i],a2[i+4],a3[i+4],a4[0]);
        }
        GenEmptyObj(&PrepareImage);
        for (int i = 0; i < Global::camDefineNum; i++) {
             ConcatObj(PrepareImage, CameraImageList[i], &PrepareImage);
        }

        GenEmptyObj(&FiledImage);
        TileImages(PrepareImage, &FiledImage, Global::camDefineNum, "horizontal"); //对待拼接对象进行拼接操作，拼接结果放在FiledImage中
        a1.clear();
        a2.clear();
        a3.clear();
        a4.clear();
        timer.elapsed();
        qDebug() << "Function time : " << timer.elapsed() << " ms";
    }
    catch (HException e)
    {
        qDebug()<<"HException"<<"拼图算法出错！";
    }
}

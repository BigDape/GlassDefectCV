#include "mosaickimage.h"
#include "Global.h"
#pragma execution_character_set("utf-8")

MosaickImage::MosaickImage()
{
}

//拼接四张图到一张图里面
void MosaickImage::DoMosaick(HObject CameraImage1,
                             HObject CameraImage2,
                             HObject CameraImage3,
                             HObject CameraImage4,
                             HObject PrepareImage,
                             HObject& FiledImage)
{
   try{
        QElapsedTimer timer;
        timer.start();
        HTuple RecipeDict;
        HTuple CurrentRecipe = Global::CurrentRecipe.toUtf8().constData();
        ReadDict("Recipes/"+ CurrentRecipe +".json", HTuple(), HTuple(), &RecipeDict);
        HTuple DefectDict;
        GetDictTuple(RecipeDict,"缺陷检测",&DefectDict);
        HTuple PixelDif12,PixelDif23,PixelDif24;
        GetDictTuple(DefectDict,"12相机像素偏差",&PixelDif12);
        GetDictTuple(DefectDict,"23相机像素偏差",&PixelDif23);
        GetDictTuple(DefectDict,"24相机像素偏差",&PixelDif24);
        qDebug()<<"1-2相机像素偏差"<<PixelDif12.ToString().Text();

        HTuple ImageHeight;
        HTuple ImageWidth;

        GetImageSize(CameraImage1, &ImageWidth, &ImageHeight);
        // + PixelDif12
        CropPart(CameraImage1, &CameraImage1, 100, 93, ImageWidth-186, ImageHeight - 200); //裁切图片
        CropPart(CameraImage2, &CameraImage2, 100, 93, ImageWidth-186, ImageHeight - 200); //裁切图片
        CropPart(CameraImage3, &CameraImage3, 100, 88, ImageWidth-186, ImageHeight - 200); //裁切图片
        CropPart(CameraImage4, &CameraImage4, 100, 38, ImageWidth-186, ImageHeight - 200); //裁切图片
        GenEmptyObj(&PrepareImage);
        ConcatObj(CameraImage1, CameraImage2, &PrepareImage);
        ConcatObj(PrepareImage, CameraImage3, &PrepareImage);
        ConcatObj(PrepareImage, CameraImage4, &PrepareImage);
        qDebug() << "ImageWidth :" << ImageWidth.ToString().Text();
        qDebug() << "ImageHeight :" << ImageHeight.ToString().Text();
        GenEmptyObj(&FiledImage);
        TileImages(PrepareImage, &FiledImage, 4, "horizontal"); //对待拼接对象进行拼接操作，拼接结果放在FiledImage中
        timer.elapsed();
        qDebug() << "Function time : " << timer.elapsed() << " ms";
    } catch (HException e) {
        qDebug()<<"HException"<<"拼图算法出错！";
    }

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
//        overlapsiyin=(36- 16*siyindistance/5.000000)/2;
//        overlap=(36-16*thickness/5.000000)/2;
        int Thickness = thickness; //玻璃厚度
        switch (Thickness){
          case 10:
            overlap=9;
            overlapsiyin=18;
            break;
          case 8:
            overlap=15;
            overlapsiyin=23;
            break;
          case 5:
            overlap=18;
            overlapsiyin=27;
        }

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
       a1<<101<<100<<100<<100;
       a2<<0<<overlap<<88<<38<<0<<overlapsiyin<<77<<88<<99;
       a3<<ImageWidth-overlap<<ImageWidth-overlap<<ImageWidth-29<<ImageWidth-29<<ImageWidth-overlapsiyin<<ImageWidth-overlapsiyin<<ImageWidth-15<<ImageWidth-15;
       a4<<ImageHeight - 200;
       if(channel==0) {
            for(int i=0;i<Global::camDefineNum;i++)
                CropPart(CameraImageList[i],&CameraImageList[i],a1[i],a2[i],a3[i],a4[0]);
        } else {
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

ThreadDo::ThreadDo(QObject* parent)
    : QThread(parent)
{
    MosaickProcess = new MosaickImage();
}

void ThreadDo::run()
{
//     CameraImageList<<CameraImage1<<CameraImage2<<CameraImage3<<CameraImage4;
    //执行图片拼接操作
        // MosaickProcess->DoMosaick(CameraImage1, CameraImage2, CameraImage3, CameraImage4, PrepareImage, MosaickResultImage);
        MosaickProcess->DoMosaick(CameraImageList, channel, PrepareImage, MosaickResultImage);
}

#include "mosaickimage.h"
#include <QImage>
#include <QPainter>
#pragma execution_character_set("utf-8")

MosaickImage::MosaickImage()
{
}

void MosaickImage::DoMosaick(/*QList<HObject> CameraImageList, int channel, HObject PrepareImage, HObject& FiledImage*/)
{
//   try{
//        QElapsedTimer timer;
//        timer.start();
//        HTuple DefectDict;
//        GetDictTuple(Global::RecipeDict,"缺陷检测",&DefectDict);
//        HTuple PixelDif12,PixelDif23,PixelDif24,thickness,siyindistance,overlap,overlapsiyin;
//        GetDictTuple(DefectDict,"12相机像素偏差",&PixelDif12);
//        GetDictTuple(DefectDict,"玻璃厚度",&thickness);
//        GetDictTuple(DefectDict,"丝印离辊道距离",&siyindistance);
//        GetDictTuple(DefectDict,"23相机像素偏差",&PixelDif23);
//        GetDictTuple(DefectDict,"24相机像素偏差",&PixelDif24);
//        qDebug()<<"1-2相机像素偏差"<<PixelDif12.ToString().Text();

//        overlapsiyin=(184-8192*(1-(1457.7-(siyindistance-6))/1457.700))/2;
//        overlap=(184-8192*(1-(1457.7-(thickness-6))/1457.700))/2;
//        overlap=75+12+2;
////        int Thickness=thickness;
////        switch (Thickness){
////          case 10:
////            overlap=9;
////            overlapsiyin=18;
////            break;
////          case 8:
////            overlap=92;//15 8mm:86 6mm:92\88
////            overlapsiyin=23;
////            break;
////          case 5:
////            overlap=18;
////            overlapsiyin=27;
////        }

//        if(overlapsiyin<0)
//            overlapsiyin=0;

//        if(overlap<0)
//            overlap=0;

//       QList<HTuple> PixelDifList;
//       PixelDifList<<PixelDif12<<PixelDif23<<PixelDif24;
//       qDebug()<<"1-2相机像素偏差"<<PixelDif12.ToString().Text()<<PixelDifList[0].ToString().Text();
//       HTuple ImageHeight;
//       HTuple ImageWidth;

//       GetImageSize(CameraImageList[0], &ImageWidth, &ImageHeight);
//       qDebug() << "ImageWidth :" << ImageWidth.ToString().Text();
//       qDebug() << "ImageHeight :" << ImageHeight.ToString().Text();
//    // + PixelDif12
//       QList<HTuple> a1,a2,a3,a4;
//       a1<<100<<96<<100<<100;
//       int VerPix12 = PixelDif12.I();
//       int VerPix23 = PixelDif23.I();
//       a1<<VerPix12<<VerPix23<<100<<100;
//       a2<<0<<overlap<<88<<38<<0<<overlapsiyin<<77<<88<<99;
//       a3<<ImageWidth-overlap<<ImageWidth-overlap<<ImageWidth-29<<ImageWidth-29<<ImageWidth-overlapsiyin<<ImageWidth-overlapsiyin<<ImageWidth-15<<ImageWidth-15;
//       a4<<ImageHeight - 200;
//       if(channel==0) {
//            for(int i=0;i<Global::camDefineNum;i++)
//                CropPart(CameraImageList[i],&CameraImageList[i],a1[i],a2[i],a3[i],a4[0]);
//        } else {
//            for(int i=0;i<Global::camDefineNum;i++)
//                CropPart(CameraImageList[i],&CameraImageList[i],a1[i],a2[i+4],a3[i+4],a4[0]);
//        }
//        GenEmptyObj(&PrepareImage);
//        for (int i = 0; i < Global::camDefineNum; i++) {
//             ConcatObj(PrepareImage, CameraImageList[i], &PrepareImage);
//        }

//        GenEmptyObj(&FiledImage);
//        TileImages(PrepareImage, &FiledImage, Global::camDefineNum, "horizontal"); //对待拼接对象进行拼接操作，拼接结果放在FiledImage中
//        a1.clear();
//        a2.clear();
//        a3.clear();
//        a4.clear();
//        timer.elapsed();
//        qDebug() << "Function time : " << timer.elapsed() << " ms";
//    }
//    catch (HException e)
//    {
//        qDebug()<<"HException"<<"拼图算法出错！";
//    }
}

QImage MosaickImage::horizontalConcat(const QImage& img1, const QImage& img2)
{
    int width = img1.width() + img2.width();
    int height = std::max(img1.height(), img2.height());
    QImage result(width, height, QImage::Format_Grayscale8);
    QPainter painter(&result);
    painter.drawImage(0, 0, img1);
    painter.drawImage(img1.width(), 0, img2);
    return result;
}

QImage MosaickImage::verticalConcat(const QImage& img1, const QImage& img2)
{
    int width = std::max(img1.width(), img2.width());
    int height = img1.height() + img2.height();
    QImage result(width, height, QImage::Format_Grayscale8);
    QPainter painter(&result);
    painter.drawImage(0, 0, img1);
    painter.drawImage(0, img1.height(), img2);
    return result;
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
    MosaickProcess->DoMosaick(/*CameraImageList, channel, PrepareImage, MosaickResultImage*/);
}

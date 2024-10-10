#include "processtile.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <QDir>
#pragma execution_character_set("utf-8")


// 离线模式调用的函数
void ProcessTile::OfflineTileImageProcess(QString fullpath)
{
//    QString tile1Fullpath,tile2Fullpath,tile3Fullpath,tile4Fullpath;
//    if (Global::isJpg) {
//        tile1Fullpath = fullpath + QString("/tile1.jpg");
//        tile2Fullpath = fullpath + QString("/tile2.jpg");
//        tile3Fullpath = fullpath + QString("/tile3.jpg");
//        tile4Fullpath = fullpath + QString("/tile4.jpg");
//    } else {
//        tile1Fullpath = fullpath + QString("/tile1.bmp");
//        tile2Fullpath = fullpath + QString("/tile2.bmp");
//        tile3Fullpath = fullpath + QString("/tile3.bmp");
//        tile4Fullpath = fullpath + QString("/tile4.bmp");
//    }

//    bool res1 = QFile::exists(tile1Fullpath);
//    bool res2 = QFile::exists(tile2Fullpath);
//    bool res3 = QFile::exists(tile3Fullpath);
//    bool res4 = QFile::exists(tile4Fullpath);
//    if( res1 && res2 && res3 && res4) {
//        ReadImage(&mosaickthread[0].MosaickResultImage,tile1Fullpath.toStdString().data());
//        ReadImage(&mosaickthread[1].MosaickResultImage,tile2Fullpath.toStdString().data());
//        ReadImage(&mosaickthread[2].MosaickResultImage,tile3Fullpath.toStdString().data());
//        ReadImage(&mosaickthread[3].MosaickResultImage,tile4Fullpath.toStdString().data());
//        GetDictTuple(Global::RecipeDict,"自定义参数",&UserDefinedDict);
//        ProcessTile::PreProceeTile();
//    } else {
//        qDebug() << tile1Fullpath << tile2Fullpath << tile3Fullpath << tile4Fullpath << " is not exists()";
//    }
}


void ProcessTile::CV_DefectsDetected(cv::Mat image1, cv::Mat image2, cv::Mat image3)
{
    if (image1.rows > 0 ) {
       cv::Mat backgroundRow = image1.row(0);
       cv::Mat backgroundCol = image1.col(0);
       // 去除背景
       cv::Mat region  = image1 - (backgroundRow * backgroundCol);
       ProcessTile::saveMatToImage("region.jpg", region);
       // 获取region


       std::vector<std::vector<cv::Point> > contours;
       cv::findContours(region, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE); //找轮廓

       double maxArea = 0;
       int maxAreaContourIndex = -1;
       for (size_t i = 0; i < contours.size(); i++) {
           double area = cv::contourArea(contours[i]);
           if (area > maxArea) {
               maxArea = area;
               maxAreaContourIndex = i;
           }
       }

       if (maxAreaContourIndex != -1) {
           std::vector<cv::Point> largestContour = contours[maxAreaContourIndex];
           qDebug()<<"最大外轮廓的面积："<<maxArea;
           // 绘制最大轮廓
           cv::Mat drawing = cv::Mat::zeros(region.size(), CV_8UC1);
           cv::drawContours(drawing, std::vector<std::vector<cv::Point>>{largestContour}, -1, cv::Scalar(0, 255, 0), 2);
           //获取最大外接矩形，且向四周延伸128行
           cv::Rect boundingRect = cv::boundingRect(largestContour);
           int topAddition = std::min(128, boundingRect.y);
           int bottomAddition = std::min(128, image1.rows - boundingRect.y - boundingRect.height);
           int leftAddition = std::min(128, boundingRect.x);
           int rightAddition = std::min(128, image1.cols - boundingRect.x - boundingRect.width);
           boundingRect.x -= leftAddition;
           boundingRect.y -= topAddition;
           boundingRect.width += leftAddition + rightAddition;
           boundingRect.height += topAddition + bottomAddition;
           // 裁剪图像，获取面内区域
           cv::Mat croppedImage1 = image1(boundingRect);
           cv::Mat baseline;
           // 获取基准矩阵
           ProcessTile::getBaseLineFromImage(croppedImage1, baseline);
           // 边部缺陷检出
           std::vector<cv::Mat> edgeregions;
           ProcessTile::edgeDefectDetection(croppedImage1,
                                            edgeregions,
                                            topAddition,
                                            bottomAddition,
                                            leftAddition,
                                            rightAddition);
           // 面部缺陷检出
           cv::Rect FrameRect(256,256,croppedImage1.cols-256*2,croppedImage1.rows-256*2);
           cv::Mat FrameImage = croppedImage1(FrameRect);
           // 基准矩阵首尾去除掉256个元素，是边框的图像
           cv::Rect baseRect(0,255,baseline.cols-512,1);
           cv::Mat frameBaseLine = baseline(baseRect);
           std::vector<cv::Mat> defectRegions;
           ProcessTile::ScanFrameDefect(FrameImage, frameBaseLine, defectRegions);
       }
    }

}

 void ProcessTile::saveMatToImage(QString fullpath,cv::Mat& region )
 {
     // 将图像保存为新的文件
     bool success = cv::imwrite(fullpath.toStdString().c_str(), region);
     if (success) {
         std::cout << "图像保存成功。" << std::endl;
     } else {
         std::cout << "图像保存失败。" << std::endl;
     }
 }

// 左上角坐标点和右上角坐标点
void ProcessTile::cropRectangleMat(const cv::Mat image,
                                    cv::Mat &dst,
                                    int row1y,
                                    int Column1x,
                                    int row2y,
                                    int Column2x)
 {
     // 确保裁剪区域在图像范围内
     CV_Assert(row1y >= 0 && row1y < image.rows && Column1x >= 0 && Column1x < image.cols);
     CV_Assert(row2y >= 0 && row2y <= image.rows && Column2x >= 0 && Column2x <= image.cols);
     CV_Assert(row1y < row2y && Column1x < Column2x);

     // 创建裁剪区域的Rect对象
     cv::Rect roi(Column1x, row1y, Column2x - Column1x, row2y - row1y);

     // 使用ROI裁剪图像
     dst = image(roi);
 }

void ProcessTile::prewittEdgeDetection(cv::Mat& src, cv::Mat& dst) {
    cv::Mat kernelX = (cv::Mat_<int>(3, 3) << -1, 0, 1,
                       -1, 0, 1,
                       -1, 0, 1);
    cv::Mat kernelY = (cv::Mat_<int>(3, 3) << -1, -1, -1,
                       0, 0, 0,
                       1, 1, 1);

    cv::Mat gx, gy;
    cv::filter2D(src, gx, -1, kernelX);
    cv::filter2D(src, gy, -1, kernelY);

    cv::magnitude(gx, gy, dst);
}

void ProcessTile::getBaseLineFromImage(cv::Mat& region, cv::Mat& baseline)
{
    if (region.rows > 0 ) {
       cv::Mat baseLineRow1 = region.row(region.rows/4);
       cv::Mat baseLineRow2 = region.row((region.rows/4)*2);
       cv::Mat baseLineRow3 = region.row((region.rows/4)*3);
       cv::Scalar meanValue1 = cv::mean(baseLineRow1);
       double average1 = meanValue1[0];
       cv::Scalar meanValue2 = cv::mean(baseLineRow2);
       double average2 = meanValue2[0];
       cv::Scalar meanValue3 = cv::mean(baseLineRow3);
       double average3 = meanValue3[0];
       double midAverage = 0;
       if ((average1 <= average2 && average2 <= average3) || (average3 <= average2 && average2 <= average1)) {
           midAverage = average2;
           baseline = baseLineRow2;
       } else if ((average2 <= average1 && average1 <= average3) || (average3 <= average1 && average1 <= average2)) {
           midAverage = average1;
           baseline = baseLineRow1;
       } else {
           midAverage = average3;
           baseline = baseLineRow3;
       }
    }
}

void ProcessTile::edgeDefectDetection(cv::Mat& region,
                                      std::vector<cv::Mat>& edgeregions,
                                      int topAddition,
                                      int bottomAddition,
                                      int leftAddition,
                                      int rightAddition)
{
    //
    // 将边部全部切分，用来识别崩边和门夹
    //
    int regionRow = region.rows;
    int regionCol = region.cols;
    int smallRegionCount = 0;
    //
    // 沿着图像的最上边依次裁剪小图
    //
    if (topAddition != 0) {
        for (int i =0; i < regionCol/256; ++i) {
            cv::Rect rect(i*256, 0, 256, 256);
            cv::Mat smallRegion = region(rect);
            edgeregions.push_back(smallRegion);
            ++smallRegionCount;
            QString edgeFullpath = "./edge"+QString::number(smallRegionCount)+".jpg";
            ProcessTile::saveMatToImage(edgeFullpath,smallRegion );
        }
        //不足256*256部分也截取
        if (regionCol%256 != 0) {
            int lastX = regionCol - (regionCol%256);
            cv::Rect rect(lastX, 0, regionCol%256, 256);
            cv::Mat smallRegion = region(rect);
            edgeregions.push_back(smallRegion);
            ++smallRegionCount;
            QString edgeFullpath = "./edge"+QString::number(smallRegionCount)+".jpg";
            ProcessTile::saveMatToImage(edgeFullpath,smallRegion );
        }

    }
    //
    // 沿着图像的最右边开始裁剪小图
    //
    if (rightAddition != 0) {
        for (int i = 1; i < regionRow/256; ++i) {
            cv::Rect rect(regionCol-256, i*256, 256, 256);
            cv::Mat smallRegion = region(rect);
            edgeregions.push_back(smallRegion);
            ++smallRegionCount;
            QString edgeFullpath = "./edge"+QString::number(smallRegionCount)+".jpg";
            ProcessTile::saveMatToImage(edgeFullpath,smallRegion );
        }
        if (regionRow%256 != 0) {
            int lastY = regionRow - (regionRow%256);
            cv::Rect rect(regionCol-256,lastY, 256, regionRow%256);
            cv::Mat smallRegion = region(rect);
            edgeregions.push_back(smallRegion);
            ++smallRegionCount;
            QString edgeFullpath = "./edge"+QString::number(smallRegionCount)+".jpg";
            ProcessTile::saveMatToImage(edgeFullpath,smallRegion );
        }
    }
    //
    // 沿着图像最下边缘开始裁剪小图
    //
    if (bottomAddition != 0) {
        for (int i =0; i < regionCol/256 -1; ++i) {
            cv::Rect rect(i*256, regionRow - 256, 256, 256);
            cv::Mat smallRegion = region(rect);
            edgeregions.push_back(smallRegion);
            ++smallRegionCount;
        }
        if (regionCol%256 != 0) {
            int lastX = regionCol - (regionCol%256) - 256;
            cv::Rect rect(lastX, regionRow - 256, regionCol%256 , 256);
            cv::Mat smallRegion = region(rect);
            edgeregions.push_back(smallRegion);
            ++smallRegionCount;
            QString edgeFullpath = "./edge"+QString::number(smallRegionCount)+".jpg";
            ProcessTile::saveMatToImage(edgeFullpath,smallRegion );
        }
    }
    //
    // 沿着图像的最左边开始裁剪小图
    //
    if (leftAddition != 0) {
        for (int i = 1; i < regionRow/256 -1; ++i) {
            cv::Rect rect(0, i*256, 256, 256);
            cv::Mat smallRegion = region(rect);
            edgeregions.push_back(smallRegion);
            ++smallRegionCount;
            QString edgeFullpath = "./edge"+QString::number(smallRegionCount)+".jpg";
            ProcessTile::saveMatToImage(edgeFullpath,smallRegion );
        }
        if (regionRow % 256 != 0) {
            int lastY = regionRow - (regionRow%256) - 256;
            cv::Rect rect(0,lastY, 256, regionRow%256);
            cv::Mat smallRegion = region(rect);
            edgeregions.push_back(smallRegion);
            ++smallRegionCount;
            QString edgeFullpath = "./edge"+QString::number(smallRegionCount)+".jpg";
            ProcessTile::saveMatToImage(edgeFullpath,smallRegion );
        }
    }
}

void ProcessTile::ScanFrameDefect(cv::Mat& frameRegion, cv::Mat& baseLine, std::vector<cv::Mat>& defectRegions)
{
    if (frameRegion.cols == baseLine.cols) {
        for (int i=0 ; i < frameRegion.rows; ++i) {
            cv::Mat rowLine = frameRegion.row(i);
            frameRegion.row(i) = baseLine - rowLine;
        }
    }
    //
    // 二值化，备用threshold(rice, riceBW, 50, 255, THRESH_BINARY);
    //
    int rows = frameRegion.rows;
    int cols = frameRegion.cols;

    // 创建二值化后的图像矩阵
    cv::Mat binaryImage(rows, cols, CV_8UC1);

    // 进行二值化处理
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int pixelValue = frameRegion.at<uchar>(i, j);
            if (abs(pixelValue) > 10) {
                binaryImage.at<uchar>(i, j) = 1;
            } else {
                binaryImage.at<uchar>(i, j) = 0;
            }
        }
    }
    // 将相连的域联通
    cv::Mat labels;
    cv::Mat stats;
    cv::Mat centroids;
    int numComponents = connectedComponentsWithStats(binaryImage, labels, stats, centroids);//连通域
    int defectcount = 0;
    qDebug()<<"numComponents =" << numComponents;
    for (int i = 1; i < numComponents; i++) {
        int x = stats.at<int>(i, cv::CC_STAT_LEFT);
        int y = stats.at<int>(i, cv::CC_STAT_TOP);
        int width = stats.at<int>(i, cv::CC_STAT_WIDTH);
        int height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
        cv::Rect rect(x,y,width,height);
        int area = stats.at<int>(i, cv::CC_STAT_AREA);
        double areaX = centroids.at<double>(i, 0);
        double areaY = centroids.at<double>(i, 1);
        if (area > 10) {//面积大于10的缺陷会被检出
            cv::Mat defectRegion = frameRegion(rect);
            defectRegions.push_back(defectRegion);
            QString edgeFullpath = "./defect"+QString::number(defectcount)+".jpg";
            ProcessTile::saveMatToImage(edgeFullpath,defectRegion);
            qDebug()<<"areaX = " <<areaX <<",areaY ="<<areaY;
        }
    }
}


#include "processdetect.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <QQueue>
#include <QDir>
#include <QThread>
#include <math.h>
#include "processtile.h"
#include "jsoncpp.h"

#pragma execution_character_set("utf-8")

Process_Detect::Process_Detect()
{
}

Process_Detect::~Process_Detect()
{
}

//功能：计算区域中心
//halcon算子:area_center
//参数：
//  src：输入区域
//  area：区域面积
//  center：区域中心坐标
//返回值：无
void Process_Detect::area_center(cv::Mat src, int &area, cv::Point2f &center)
{

    int pixelsCount = src.rows * src.cols;
       area = 0;
       center = cv::Point2f(0, 0);
       float centerX = 0;
       float centerY = 0;
       int mcol = src.cols;
       for(int i=0;i<pixelsCount;i++)
       {
           if(src.data[i] == 255)
           {
               area++;

               int x = i % mcol;
               int y = i / mcol;

               centerX += x;
               centerY += y;
           }
       }
       if (area > 0)
       {
           centerX /= area;
           centerY /= area;
           center = cv::Point2f(centerX, centerY);
       }
}



//功能：在原图像img上绘制直线，并且筛选出特定方向的四条直线（上、下、左、右）
//参数：
//    img:原图像
//    lines:待检测的直线数据
//    rows:原图的行数
//    cols:原图的列数
//    scalar:绘制直线的颜色
//    n:绘制直线的线宽
//    linesout:检测出直线数据
//    linepoints:直线的端点坐标
//返回值：这些直线的端点坐标
std::vector<cv::Point2f> Process_Detect::drawLine(cv::Mat &img,
                                                  std::vector<cv::Vec2f> lines,
                                                  double rows,
                                                  double cols,
                                                  cv::Scalar scalar,
                                                  int n,
                                                  std::vector<cv::Vec2f> linesout,
                                                  std::vector<cv::Point2f> linepoints)
{
//    cv::Point pt1, pt2;
//    float m_rho_up=100000;
//    float m_rho_down=0;
//    float m_rho_left=100000;
//    float m_rho_right=0;

//    for (size_t i = 0; i < lines.size(); i++) {
//        float rho = lines[i][0]; //直线距离坐标原点的距离
//        float theta = lines[i][1]; //直线过坐标原点垂线与x轴的夹角
//        //上
//        if(theta>-0.2 && theta<0.2)
//         {
//            if(rho<m_rho_up)
//            {
//               m_rho_up =rho;
//               linesout[0]=lines[i];
//            }
//         }

//        //下
//        if(theta>-0.2 && theta<0.2)
//         {
//            if(rho>m_rho_down)
//            {
//               m_rho_down =rho;
//               linesout[1]=lines[i];
//            }
//         }
//        //左
//        if((theta<-1.3708 && theta>-1.7708) || (theta>1.3708 && theta<1.7708))
//         {
//            if(rho<m_rho_left)
//            {
//               m_rho_left =rho;
//               linesout[2]=lines[i];
//            }
//         }
//        //右
//         if((theta<-1.3708 && theta>-1.7708) || (theta>1.308 && theta<1.7708))
//         {
//            if(rho>m_rho_right)
//            {
//               m_rho_right =rho;
//               linesout[3]=lines[i];
//            }
//         }
//    }
//    for (size_t j = 0; j < linesout.size(); j++) {
//        float rho1 = linesout[j][0]; //直线距离坐标原点的距离
//        float theta1 = linesout[j][1]; //直线过坐标原点垂线与x轴的夹角
//        double a = cos(theta1); //夹角的余弦值
//        double b = sin(theta1);//夹角的正弦值
//        double x0 = a * rho1, y0 = b * rho1;//直角与过坐标原点的垂线交点
//        double length = std::max(rows, cols); //  图像高度的最大值、计算直线上的一点

//        pt1.x = cvRound(x0 + length * (-b));
//        pt1.y = cvRound(y0 + length * (a));

//        //计算直线上另一点
//        pt2.x = cvRound(x0 - length * (-b));
//        pt2.y = cvRound(y0 - length * (a));

//        linepoints[2*j].x=pt1.x;
//        linepoints[2*j].y=pt1.y;
//        linepoints[2*j+1].x=pt2.x;
//        linepoints[2*j+1].y=pt2.y;

//        //两点绘制一条直线
//        line(img, pt1, pt2, scalar, n);
//    }
    return linepoints;
}

//功能：填充区域中的孔洞，适合填充大量分散的小孔
//halcon算子:
//参数：
//  src：输入图像
//  dst：输出图像
//返回值：无
void Process_Detect::fill_up(cv::Mat src, cv::Mat &dst)
{
    dst = cv::Mat(src.size(), CV_8UC1, cv::Scalar(0));
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(src, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    cv::drawContours(dst, contours, -1, cv::Scalar(255), -1);
}

//功能：填充区域中孔洞的第二种方法，适合填充很大的孔洞
void Process_Detect::fillHole(const cv::Mat srcimage, cv::Mat &dstimage)
{
    cv::Size m_Size = srcimage.size();
    cv::Mat tempImage = cv::Mat::zeros(m_Size.height + 2, m_Size.width + 2, srcimage.type()); // 延展图像
    srcimage.copyTo(tempImage(cv::Range(1, m_Size.height + 1), cv::Range(1, m_Size.width + 1))); // 将原图复制到延展图像的中间部分

    // 使用floodFill函数从左上角开始填充，填充值为白色（255）
    cv::floodFill(tempImage, cv::Point(0, 0), cv::Scalar(255));

    cv::Mat cutImg; // 裁剪延展的图像
    tempImage(cv::Range(1, m_Size.height + 1), cv::Range(1, m_Size.width + 1)).copyTo(cutImg); // 裁剪回原图大小

    // 使用按位或操作将原图与裁剪后图像的补集合并，得到填充孔洞后的图像
    dstimage = srcimage | (~cutImg);
}

//功能：计算两条线段的最短间距
//参数：
//  A：输入直线1的首端坐标点
//  B：输入直线1的尾端坐标点
//  C：输入直线2的首端坐标点
//  D：输入直线2的尾端坐标点
//返回值：距离值
float Process_Detect::line_Distance(cv::Point2f A, cv::Point2f B, cv::Point2f C, cv::Point2f D) {
   cv::Point2f AB = B - A;
   cv::Point2f CD = D - C;
   cv::Point2f AC = C - A;

   // 分子：向量AB和向量AC的叉积的z分量
   float numerator = AB.x * AC.y - AB.y * AC.x;
   // 分母：向量AB和向量CD的叉积的z分量
   float denominator = AB.x * CD.y - AB.y * CD.x;

   // 分母为零，说明两条线段平行
   if (denominator != 0) {
       float t = numerator / denominator;
       float s = (AC.x + t * CD.x) / AB.x;
       // s不在0和1之间，说明交点不在线段AB上
       if (s >= 0 && s <= 1) {
//           cv::Point2f intersection = A + s * AB;
           return cv::norm(AC - s * CD);
       }
   }

   // 平行直线不相交，返回最小距离为垂直距离
   return cv::norm(AC - ((AC.dot(AB) / AB.dot(AB)) * AB));
}

//功能：图像裁剪
//参数：
//  images：图像数组
//  rects：每个图像在合并后的大图像中的位置（矩形左上角坐标x,y,宽高width,height）
//  要求：数组的大小相同,每个矩形与对应图像的位置相匹配,所有图像类型相同.
//返回值：拼接后的图像
void Process_Detect::crop_rectangle1(const cv::Mat image, cv::Mat &dst, int row1y, int Column1x, int row2y, int Column2x)
{
    // 确保裁剪区域在图像范围内
    CV_Assert(row1y >= 0 && row1y < image.rows && Column1x >= 0 && Column1x < image.cols);
    CV_Assert(row2y >= 0 && row2y <= image.rows && Column2x >= 0 && Column2x <= image.cols);
    CV_Assert(row1y < row2y && Column1x < Column2x); // 确保裁剪区域有效

    // 创建裁剪区域的Rect对象
    cv::Rect roi(Column1x, row1y, Column2x - Column1x, row2y - row1y);

    // 使用ROI裁剪图像
    cv::Mat croppedImage = image(roi);

}

//功能：将多个图像合并为一个大图像
//参数：
//  images：图像数组
//  rects：每个图像在合并后的大图像中的位置（矩形左上角坐标x,y,宽高width,height）
//  要求：数组的大小相同,每个矩形与对应图像的位置相匹配,所有图像类型相同.
//返回值：拼接后的图像
cv::Mat Process_Detect::mergeImages(const std::vector<cv::Mat>& images, const std::vector<cv::Rect>& rects) {
    // 计算拼接后的图像大小
    int maxWidth = 0;
    int totalHeight = 0;

//    for (const cv::Rect& rect : rects)  //C++11
    std::vector<cv::Rect>::const_iterator rect;  //C++98
    for (rect = rects.begin(); rect != rects.end(); ++rect){
//        maxWidth = std::max(maxWidth, rect->x + rect->width);
//        totalHeight = std::max(totalHeight, rect->y + rect->height);
    }

    // 创建拼接后的图像
    cv::Mat mergedImage(totalHeight, maxWidth, images[0].type(), cv::Scalar(0));

    // 拷贝每个图像到对应的位置
    for (size_t i = 0; i < images.size(); ++i) {
        cv::Mat roi = mergedImage(rects[i]);
        images[i].copyTo(roi);
    }

    return mergedImage;
}


//功能：使用局部阈值分割图像
//参数：
//  src：输入图像
//  pre：包含本地阈值的图像（一般可使用均值滤波后的图像）
//  dst：输出图像
//  offset：灰度偏移量（-255 ≤ offset ≤ 255）
//  type：
//      THRESHOLD_LIGHT（明）： g_src ≥ g_pre + offset
//      THRESHOLD_DARK（暗）： g_src ≤ g_pre - offset
//      THRESHOLD_EQUAL（等于）： g_pre - offset ≤ g_src ≤ g_pre + offset
//      THRESHOLD_NOT_EQUAL（不等于）： g_pre - offset > g_src || g_src > g_pre + offset
//返回值：无
void Process_Detect::dyn_threshold(cv::Mat src, cv::Mat pre, cv::Mat &dst, int offset, ThresholdType type)
{
    dst = cv::Mat(src.size(), CV_8UC1, cv::Scalar(0));
    int pixelsCount = src.rows * src.cols;

    for(int i = 0;i < pixelsCount; i++)
    {
        int g_src = src.data[i];
        int g_pre = pre.data[i];
        if (type == THRESHOLD_LIGHT)
        {
            if (g_src >= g_pre + offset)
                dst.data[i] = 255;
        }
        else if (type == THRESHOLD_DARK)
        {
            if (g_src <= g_pre - offset)
                dst.data[i] = 255;
        }
        else if (type == THRESHOLD_EQUAL)
        {
            if (g_src >= g_pre - offset && g_src <= g_pre + offset)
                dst.data[i] = 255;
        }
        else if (type == THRESHOLD_NOT_EQUAL)
        {
            if (g_src < g_pre - offset || g_src > g_pre + offset)
                dst.data[i] = 255;
        }
    }
}

//功能：变换区域的形状
//参数：
//  src：输入图像
//  dst：输出图像
//  type：变换形状
//返回值：无
void Process_Detect::shape_trans(cv::Mat src, cv::Mat &dst, ShapeTransType type)
{
    dst = cv::Mat(src.size(), CV_8UC1, cv::Scalar(0));
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(src, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    int n = contours.size();
    for (int i = 0; i < n; i++)
    {
        if (type == SHAPETRANS_RECTANGLE)
        {
            cv::Rect rect = boundingRect(contours[i]);
            cv::rectangle (dst, rect, cv::Scalar(255), -1);
        }
        else if (type == SHAPETRANS_CIRCLE)
        {
            cv::Point2f center;
            float radius;
            cv::minEnclosingCircle(contours[i], center, radius);
            cv::circle (dst, center, radius, cv::Scalar(255), -1);
        }
        else if (type == SHAPETRANS_CONVER)
        {
            std::vector<cv::Point> conver;
            convexHull(contours[i], conver);

            std::vector<std::vector<cv::Point> > pconver;
            pconver.push_back(conver);

            cv::fillPoly(dst, pconver, cv::Scalar(255));
            cv::drawContours(dst, pconver, -1, cv::Scalar(255), 1);
        }
    }
}


//功能：借助形状特征选择区域
//halcon算子:select_shape(region, selected_regions, 'area', 'and', min, max)
//参数：
//  src：输入图像
//  dst：输出图像
//  types：要检查的形状特征
//  operation：各个要素的链接类型（与、或）
//  mins：下限值
//  maxs：上限值
//返回值：0/区域数量
int Process_Detect::select_shape(cv::Mat src,
                                 cv::Mat &dst,
                                 std::vector<SelectShapeType> types,
                                 SelectOperation operation,
                                 std::vector<double> mins,
                                 std::vector<double> maxs)
{
    if (!(types.size() == mins.size() && mins.size() == maxs.size()))
            return 0;

        int num = types.size();
        dst = cv::Mat(src.size(), CV_8UC1, cv::Scalar(0));

        std::vector<std::vector<cv::Point> > contours;
        findContours(src, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
        int cnum = contours.size();

        std::vector<std::vector<cv::Point> > selectContours;
        for (int i = 0; i < cnum; i++)
        {
            bool isAnd = true;
            bool isOr = false;
            for (int j = 0; j < num; j++)
            {
                double mind = mins[j];
                double maxd = maxs[j];
                if (mind > maxd)
                {
                    mind = maxs[j];
                    maxd = mins[j];
                }
                if (types[j] == SELECT_AREA)
                {
                    cv::Mat temp = cv::Mat(src.size(), CV_8UC1, cv::Scalar(0));
                    std::vector<std::vector<cv::Point> > pconver;
                    pconver.push_back(contours[i]);
                    cv::drawContours(temp, pconver, -1, cv::Scalar(255), -1);
//                    bitwise_and(src, temp, temp);
                    int area;
                    cv::Point2f center;
                    area_center(temp, area, center);
                    if (area >= mind && area <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
                else if (types[j] == SELECT_RECTANGULARITY)
                {
                    cv::Mat temp = cv::Mat(src.size(), CV_8UC1, cv::Scalar(0));
                    std::vector<std::vector<cv::Point> > pconver;
                    pconver.push_back(contours[i]);
                    cv::drawContours(temp, pconver, -1, cv::Scalar(255), -1);
//                    bitwise_and(src, temp, temp);
                    int area;
                    cv::Point2f center;
                    area_center(temp, area, center);
                    cv::RotatedRect rect = minAreaRect(contours[i]);
                    double rectangularity = area / rect.size.area();
                    if (rectangularity >= mind && rectangularity <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
                else if (types[j] == SELECT_WIDTH)
                {
                    cv::Rect rect = boundingRect(contours[i]);
                    if (rect.width >= mind && rect.width <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
                else if (types[j] == SELECT_HEIGHT)
                {
                    cv::Rect rect = boundingRect(contours[i]);
                    if (rect.height >= mind && rect.height <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
                else if (types[j] == SELECT_ROW)
                {
                    cv::Mat temp = cv::Mat(src.size(), CV_8UC1, cv::Scalar(0));
                    std::vector<std::vector<cv::Point> > pconver;
                    pconver.push_back(contours[i]);
                    cv::drawContours(temp, pconver, -1, cv::Scalar(255), -1);
//                    bitwise_and(src, temp, temp);
                    int area;
                    cv::Point2f center;
                    area_center(temp, area, center);
                    if (center.y >= mind && center.y <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
                else if (types[j] == SELECT_COLUMN)
                {
                    cv::Mat temp = cv::Mat(src.size(), CV_8UC1, cv::Scalar(0));
                    std::vector<std::vector<cv::Point> > pconver;
                    pconver.push_back(contours[i]);
                    cv::drawContours(temp, pconver, -1, cv::Scalar(255), -1);
//                    bitwise_and(src, temp, temp);
                    int area;
                    cv::Point2f center;
                    area_center(temp, area, center);
                    if (center.x >= mind && center.x <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
                else if (types[j] == SELECT_RECT2_LEN1)
                {
                    cv::RotatedRect rect = minAreaRect(contours[i]);
                    double len = rect.size.width;
                    if (rect.size.width < rect.size.height)
                        len = rect.size.height;
                    if (len / 2 >= mind && len / 2 <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
                else if (types[j] == SELECT_RECT2_LEN2)
                {
                    cv::RotatedRect rect = minAreaRect(contours[i]);
                    double len = rect.size.height;
                    if (rect.size.width < rect.size.height)
                        len = rect.size.width;
                    if (len / 2 >= mind && len / 2 <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
                else if (types[j] == SELECT_RECT2_PHI)
                {
                    cv::RotatedRect rect = minAreaRect(contours[i]);
                    float angle = 0;
                    if (angle < 0) angle += 180;
                    if (rect.size.width < rect.size.height)
                    {
                        angle = rect.angle;
                        angle -= 90;
                        if (angle < 0) angle += 180;
                    }
                    else
                    {
                        angle = rect.angle;
                    }
                    if (angle >= mind && angle <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
                else if (types[j] == SELECT_ELLIPSE_RA)
                {
                    if (contours[i].size() < 5)
                    {
                        isAnd &= false;
                        isOr |= false;
                        continue;
                    }
                    cv::RotatedRect rect = cv::fitEllipse(contours[i]);
                    double len = rect.size.width;
                    if (rect.size.width < rect.size.height)
                        len = rect.size.height;
                    if (len / 2 >= mind && len / 2 <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
                else if (types[j] == SELECT_ELLIPSE_RB)
                {
                    if (contours[i].size() < 5)
                    {
                        isAnd &= false;
                        isOr |= false;
                        continue;
                    }
                    cv::RotatedRect rect = cv::fitEllipse(contours[i]);
                    double len = rect.size.height;
                    if (rect.size.width < rect.size.height)
                        len = rect.size.width;
                    if (len / 2 >= mind && len / 2 <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
                else if (types[j] == SELECT_ELLIPSE_PHI)
                {
                    if (contours[i].size() < 5)
                    {
                        isAnd &= false;
                        isOr |= false;
                        continue;
                    }
                    cv::RotatedRect rect = cv::fitEllipse(contours[i]);
                    float angle = 0;
                    if (angle < 0) angle += 180;
                    if (rect.size.width < rect.size.height)
                    {
                        angle = rect.angle;
                        angle -= 90;
                        if (angle < 0) angle += 180;
                    }
                    else
                    {
                        angle = rect.angle;
                    }
                    if (angle >= mind && angle <= maxd)
                    {
                        isAnd &= true;
                        isOr |= true;
                    }
                    else
                    {
                        isAnd &= false;
                        isOr |= false;
                    }
                }
            }
            if (isAnd && operation == SELECT_AND)
                selectContours.push_back(contours[i]);
            if (isOr && operation == SELECT_OR)
                selectContours.push_back(contours[i]);
        }
        cv::drawContours(dst, selectContours, -1, cv::Scalar(255), -1);
//        bitwise_and(src, dst, dst);
        return selectContours.size();

}

//功能：选择区域集合中的面积最大
//halcon算子:select_shape_std
//参数：
//  src：输入区域集合
//  dst：输出面积最大的区域
//返回值：区域面积
double Process_Detect::select_shape_std(cv::Mat src, cv::Mat &dst)
{
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(src, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    int cnum = contours.size();
    double dArea;
    double MaxArea = 0;
    std::vector<cv::Point> selectContour = contours[0];
    for (int i = 0; i < cnum; i++)
    {
        dArea = cv::contourArea(contours[i], false);
        if(dArea > MaxArea)
        {
            selectContour = contours[i];
            MaxArea = dArea;
        }
    }

    std::vector<std::vector<cv::Point> > selectContours;
    selectContours.push_back(selectContour);
    dst = cv::Mat(src.size(), CV_8UC1, cv::Scalar(0));
//    cv::fillPoly(dst, selectContours, cv::Scalar(255));
    drawContours(dst, selectContours, -1, cv::Scalar(255), -1);

    return MaxArea;
}


//功能：计算区域的差集
//halcon算子:difference
//参数：
//  src：输入区域（减数）
//  dst：输入区域（被减数）
//  diff：输出区域（src - dst）
//返回值：无
void Process_Detect::difference(cv::Mat src, cv::Mat dst, cv::Mat &diff)
{
    cv::Mat mask;
    cv::bitwise_not(dst, mask); // 计算dst的反掩膜
    cv::bitwise_and(src, mask, diff);   // src与反掩膜的交集：即src中不含dst的部分
}

void Process_Detect::intersection(cv::Mat src, cv::Mat dst, cv::Mat &inter)
{
    cv::bitwise_and(src, dst, inter);
}

//功能：由区域的相对位置对区域进行排序
//halcon算子:sort_region
//参数：
//  src：输入图像
//  contours：输入图像中的轮廓组
//  pos：已排序的轮廓索引
//  sc：排序基准点
//  isDue：
//      true：从小到大进行排序
//      false：从大到小进行排序
//  sd：排序方向
//返回值：true：排序成功
//		 false：排序失败
bool Process_Detect::sort_region(cv::Mat src,
                                 std::vector<std::vector<cv::Point> > contours,
                                 std::vector<int> &pos,
                                 SortCriterion sc,
                                 bool isDue,
                                 SortDirection sd)
{
    int count = contours.size();
    pos.resize(count);
    std::vector<cv::Point> points;
    for (int i = 0; i < count; i++)
    {
        pos[i] = i;
        cv::Rect rect = boundingRect(contours[i]);
        if (sc == FIRST_POINT)
        {
            int row = rect.y;
            for (int col = rect.x; col <= rect.x + rect.width; col++)
            {
                if (src.at<uchar>(row, col) > 0)
                {
                    points.push_back(cv::Point(col, row));
                    break;
                }
            }
        }
        else if (sc == LAST_POINT)
        {
            int row = rect.y + rect.height;
            for (int col = rect.x + rect.width; col >= rect.x; col--)
            {
                if (src.at<uchar>(row, col) > 0)
                {
                    points.push_back(cv::Point(col, row));
                    break;
                }
            }
        }
        else if (sc == UPPER_LEFT)
            points.push_back(rect.tl());
        else if (sc == UPPER_RIGHT)
            points.push_back(cv::Point(rect.x + rect.width, rect.y));
        else if (sc == LOWER_LEFT)
            points.push_back(cv::Point(rect.x, rect.y + rect.height));
        else if (sc == LOWER_RIGHT)
            points.push_back(rect.br());
    }
    int np = points.size();
    if (np != count)
        return false;
    if (sd == ROW)
    {
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - 1 - i; j++)
            {
                if (isDue)
                {
                    if (points[j].y > points[j + 1].y)
                    {
                        cv::Point temp = points[j];
                        points[j] = points[j + 1];
                        points[j + 1] = temp;

                        int index = pos[j];
                        pos[j] = pos[j + 1];
                        pos[j + 1] = index;
                    }
                }
                else
                {
                    if (points[j].y < points[j + 1].y)
                    {
                        cv::Point temp = points[j];
                        points[j] = points[j + 1];
                        points[j + 1] = temp;

                        int index = pos[j];
                        pos[j] = pos[j + 1];
                        pos[j + 1] = index;
                    }
                }
            }
        }
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - 1 - i; j++)
            {
                if (points[j].y == points[j + 1].y)
                {
                    if (isDue)
                    {
                        if (points[j].x > points[j + 1].x)
                        {
                            cv::Point temp = points[j];
                            points[j] = points[j + 1];
                            points[j + 1] = temp;

                            int index = pos[j];
                            pos[j] = pos[j + 1];
                            pos[j + 1] = index;
                        }
                    }
                    else
                    {
                        if (points[j].x < points[j + 1].x)
                        {
                            cv::Point temp = points[j];
                            points[j] = points[j + 1];
                            points[j + 1] = temp;

                            int index = pos[j];
                            pos[j] = pos[j + 1];
                            pos[j + 1] = index;
                        }
                    }
                }
            }
        }
    }
    else if (sd == COLUMN)
    {
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - 1 - i; j++)
            {
                if (isDue)
                {
                    if (points[j].x > points[j + 1].x)
                    {
                        cv::Point temp = points[j];
                        points[j] = points[j + 1];
                        points[j + 1] = temp;

                        int index = pos[j];
                        pos[j] = pos[j + 1];
                        pos[j + 1] = index;
                    }
                }
                else
                {
                    if (points[j].x < points[j + 1].x)
                    {
                        cv::Point temp = points[j];
                        points[j] = points[j + 1];
                        points[j + 1] = temp;

                        int index = pos[j];
                        pos[j] = pos[j + 1];
                        pos[j + 1] = index;
                    }
                }
            }
        }
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - 1 - i; j++)
            {
                if (points[j].x == points[j + 1].x)
                {
                    if (isDue)
                    {
                        if (points[j].y > points[j + 1].y)
                        {
                            cv::Point temp = points[j];
                            points[j] = points[j + 1];
                            points[j + 1] = temp;

                            int index = pos[j];
                            pos[j] = pos[j + 1];
                            pos[j + 1] = index;
                        }
                    }
                    else
                    {
                        if (points[j].y < points[j + 1].y)
                        {
                            cv::Point temp = points[j];
                            points[j] = points[j + 1];
                            points[j + 1] = temp;

                            int index = pos[j];
                            pos[j] = pos[j + 1];
                            pos[j + 1] = index;
                        }
                    }
                }
            }
        }
    }
    return true;
}


//功能：对区域的进行平移
//halcon算子:move_region
//参数：
//  src：输入图像
//  dst：输出图像
//  dx：平移量，向右为正
//  dy：平移量，向下为正
//返回值：无
void Process_Detect::move_region(cv::Mat src, cv::Mat &dst, int dx, int dy)
{
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(src, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    int Sum = contours.size();

    std::vector<std::vector<cv::Point> > newContours;
    for (int i = 0; i < Sum; i++)
    {
        std::vector<cv::Point> contourSelect, trContour;
        contourSelect = contours[i];
        for(int j = 0; j < contourSelect.size(); ++j)
        {
            trContour[j].x = contourSelect[j].x + dx;
            trContour[j].y = contourSelect[j].y + dx;
        }
        newContours.push_back(trContour);
    }
    dst = cv::Mat(src.size(), src.type(), cv::Scalar(0));
    cv::drawContours(dst, newContours, -1, cv::Scalar(255), 1);
}



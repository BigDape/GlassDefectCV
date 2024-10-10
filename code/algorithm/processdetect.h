#ifndef PROCESS_DETECT_H
#define PROCESS_DETECT_H

#include <QString>
#include <QtDebug>
#include <QSettings>
#include <QThreadPool>
#include <QDebug>
#include <QElapsedTimer>
#include <QMutex>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <QString>
#include "hstool.h"

class Process_Detect : public QObject
{
    Q_OBJECT
public:
    Process_Detect();
    ~Process_Detect();

    enum MorphTypes
    {
        Morph_ERODE = 0,	//腐蚀
        Morph_DILATE = 1,	//膨胀
        Morph_OPEN = 2,		//开运算
        Morph_CLOSE = 3,	//闭运算
        Morph_GRADIENT = 4, //梯度操作
        Morph_TOPHAT = 5,   //顶帽操作：原图-开运算
        Morph_BLACKHAT = 6, //黑帽操作：闭运算-原图
        Morph_HITMISS = 7   //击中和非击中
    };

    enum ThresholdTypes
    {
        THRESH_BINARY = 0,      //大于阈值部分被置为255，小于部分被置为0
        THRESH_BINARY_INV = 1,	//与上相反
        THRESH_TRUNC = 2,		//大于阈值部分被置为threshold，小于部分保持原样
        THRESH_TOZERO = 3,      //小于阈值部分被置为0，大于部分保持原样
        THRESH_TOZERO_INV = 4,  //小于阈值部分被置为0，大于部分保持原样
        THRESH_MASK = 7,
        THRESH_OTSU = 8,
        THRESH_TRIANGLE = 16
    };

    // image
    cv::Mat mergeImages(const std::vector<cv::Mat>& images, const std::vector<cv::Rect>& rects);

    void crop_rectangle1(const cv::Mat image,
                         cv::Mat &dst,
                         int row1y,
                         int Column1x,
                         int row2y,
                         int Column2x);

    // image：mean
    enum ThresholdType
    {
        THRESHOLD_LIGHT,		//明
        THRESHOLD_DARK,			//暗
        THRESHOLD_EQUAL,		//等于
        THRESHOLD_NOT_EQUAL		//不等于
    };

    void dyn_threshold(cv::Mat src,
                       cv::Mat pre,
                       cv::Mat &dst,
                       int offset,
                       ThresholdType type);

    // region
    void area_center(cv::Mat src,
                     int &area,
                     cv::Point2f &center);
    void fill_up(cv::Mat src, cv::Mat &dst);
    void fillHole(const cv::Mat srcimage, cv::Mat &dstimage);
    // region：shape
    enum ShapeTransType
    {
        SHAPETRANS_RECTANGLE,	//平行于坐标轴的最小外接矩形
        SHAPETRANS_CIRCLE,		//最小外接圆
        SHAPETRANS_CONVER		//凸包
    };
    void shape_trans(cv::Mat src,
                     cv::Mat &dst,
                     ShapeTransType type);

    enum SelectShapeType
    {
        SELECT_AREA,			//选中区域面积
        SELECT_RECTANGULARITY,	//选中区域矩形度
        SELECT_WIDTH,			//选中区域宽度（平行于坐标轴）
        SELECT_HEIGHT,			//选中区域高度（平行于坐标轴）
        SELECT_ROW,				//选中区域中心行索引
        SELECT_COLUMN,			//选中区域中心列索引
        SELECT_RECT2_LEN1,		//选中区域最小外接矩形的一半长度
        SELECT_RECT2_LEN2,		//选中区域最小外接矩形的一半宽度
        SELECT_RECT2_PHI,   	//选中区域最小外接矩形的方向
        SELECT_ELLIPSE_RA,      //选中区域外接椭圆的长半轴
        SELECT_ELLIPSE_RB,      //选中区域外接椭圆的短半轴
        SELECT_ELLIPSE_PHI      //选中区域外接椭圆的方向
    };
    enum SelectOperation
    {
        SELECT_AND,		//与
        SELECT_OR		//或
    };
    int select_shape(cv::Mat src,
                     cv::Mat &dst,
                     std::vector<SelectShapeType> types,
                     SelectOperation operation,
                     std::vector<double> mins,
                     std::vector<double> maxs);

    double select_shape_std(cv::Mat src, cv::Mat &dst);


    // region: 交、并、差、补
    void difference(cv::Mat src,
                    cv::Mat dst,
                    cv::Mat &diff);
    void intersection(cv::Mat src,
                      cv::Mat dst,
                      cv::Mat &inter);

    enum SortCriterion
    {
        FIRST_POINT,    //区域第一行的最左侧的点
        LAST_POINT,     //区域最后一行的最右侧的点
        UPPER_LEFT,     //区域周围矩形的左上角
        UPPER_RIGHT,    //区域周围矩形的右上角
        LOWER_LEFT,     //区域周围矩形的左下角
        LOWER_RIGHT     //区域周围矩形的右下角
    };
    enum SortDirection
    {
        ROW,        //区域按行排列，即从左到右，从上到下
        COLUMN      //区域按列排列，即从上到下，从左到右
    };
    bool sort_region(cv::Mat src,
                     std::vector<std::vector<cv::Point> > contours,
                     std::vector<int> &pos,
                     SortCriterion sc,
                     bool isDue,
                     SortDirection sd);

    void move_region(cv::Mat src,
                     cv::Mat &dst,
                     int dx,
                     int dy);


    // line
    std::vector<cv::Point2f> drawLine(cv::Mat &img,
                                      std::vector<cv::Vec2f> lines,
                                      double rows,
                                      double cols,
                                      cv::Scalar scalar,
                                      int n,
                                      std::vector<cv::Vec2f> linesout,
                                      std::vector<cv::Point2f> linepoints);

    float line_Distance(cv::Point2f A,
                        cv::Point2f B,
                        cv::Point2f C,
                        cv::Point2f D);
};

#endif // PROCESS_DETECT_H

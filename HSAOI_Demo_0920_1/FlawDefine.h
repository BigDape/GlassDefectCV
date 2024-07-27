#ifndef FLAWDEFINE_H
#define FLAWDEFINE_H

#include <windows.h>
#include <mutex>
#include <queue>
#include <QString>
#include <QDateTime>
#include "HDevEngineCpp.h"
#include "HalconCpp.h"

//线程安全的队列
template <typename T>
class SafeQueue{
private:
    std::queue<T> _queue;
    std::mutex _mutex;
public:
    SafeQueue(){}
    SafeQueue(SafeQueue&){}
    ~SafeQueue(){}
    bool empty(){
        std::unique_lock<std::mutex> sbguard(_mutex);
        return _queue.empty();
    }
    int size(){
        std::unique_lock<std::mutex> sbguard(_mutex);
        return _queue.size();
    }
    void inqueue(T& t){
        std::unique_lock<std::mutex> sbguard(_mutex);
        _queue.push(t);
    }
    bool dequeue(T& t){
        std::unique_lock<std::mutex> sbguard(_mutex);
        if(_queue.empty()){
            return false;
        }
        t = std::move(_queue.front());
        _queue.pop();
        return true;
    }
};

//单个缺陷
struct DefeteData{
    QString Time;
    QString DefectID;
    QString DefectType;
    QString DetectLeve;
    QString X;
    QString Y;
    QString Lenth;
    QString Width;
    QString Area;
    QString ImageNGPath;
};
//单块玻璃写入json文件中的缺陷数据
struct DefeteResult{
    int GlassID;
    std::vector<DefeteData> defetes;
    QString GlassWidth;
    QString GlassLength;
    QString GlassAngle;
    QString jsonFullPath; //json文件地址
    QDateTime currentTime;
};

//单个孔/门夹/丝印
struct HoleData {
    QString HolesID;
    QString Time;
    QString Type;
    QString HolesLeve;
    QString DistanceHorizontal;
    QString DistanceVertical;
    QString HolesWidth;
    QString HolesHeight;
    QString ImageHolesPath;
};
//单块玻璃写入json文件中的数据
struct HoleResult {
    QString GlassID;
    std::vector<HoleData> holes;
    QString GlassLength;
    QString GlassWidth;
    QString GlassAngle;
    QString ImageHolesLinePath;
    QString jsonFullPath; //json文件地址
};
//halcon ProcessHoles算法执行结果
struct ProcessHolesAlgorithmResults {
    QString GlassID;
    HalconCpp::HObject HolesImage;
    HalconCpp::HObject OutLineImage;
    HalconCpp::HTuple ResultDictHoles;
    HalconCpp::HTuple Type;
    HalconCpp::HTuple HolesOK;
    HalconCpp::HTuple DistanceHorizontal;
    HalconCpp::HTuple DistanceVertical;
    HalconCpp::HTuple HolesWidth;
    HalconCpp::HTuple HolesHeight;
    HalconCpp::HTuple GlassLength;
    HalconCpp::HTuple GlassWidth;
    HalconCpp::HTuple GlassAngle;
};
//halcon ProcessVision算法执行结果
struct ProcessVisionAlgorithmResults{
    HalconCpp::HObject ErrImage1;
    HalconCpp::HObject ErrImage2;
    HalconCpp::HObject ErrImage3;
    HalconCpp::HTuple ResultDict;
    HalconCpp::HTuple ErrName;
    HalconCpp::HTuple ErrType;
    HalconCpp::HTuple DefectLevel;
    HalconCpp::HTuple ErrX;
    HalconCpp::HTuple ErrY;
    HalconCpp::HTuple ErrW;
    HalconCpp::HTuple ErrL;
    HalconCpp::HTuple ErrArea;
    HalconCpp::HTuple YCoordOut;
    HalconCpp::HTuple GlassLength;
    HalconCpp::HTuple GlassWidth;
    HalconCpp::HTuple GlassAngle;
    HalconCpp::HTuple XValues;
    HalconCpp::HTuple YValues;
};
//数据统计信息
struct GlassDataBaseInfo{
    size_t id;              // 玻璃的id，唯一的主键
    QString time;           // 时间
    QString OKorNG;         // 整体情况OK或者NG
    QString sizeOKorNG;     // 尺寸OK或者NG
    double length;          // 玻璃的长度
    double width;           // 玻璃的宽度
    double duijiaoxian1;    // 玻璃的对角线1
    double duijiaoxian2;    // 玻璃的对角线2
    int defectNumber;       // 玻璃的缺陷数量
    QString defectOKorNG;   // 缺陷OK或者NG
    int huashanNumber;      // 划伤数量
    int qipaoNumber;        // 气泡数量
    int jieshiNumber;       // 结石数量
    int benbianNumber;      // 崩边数量
    int zanwuNumber;        // 脏污数量
    int liewenNumber;       // 裂纹数量
    int qitaNumber;         // 其它数量
};
//数据总的统计结果
struct SummaryResult {
    int GlassNum;       //玻璃总数
    int ngNum;          //NG数目
    int okNum;          //OK数目
    double suceessRate; //合格率
    int sorted;         //已分拣
    int unsorted;       //待分检
    int exceptNum;      //异常数
    bool currentOKorNG; //当前玻璃OK或者NG
    bool currentSort;   //当前玻璃是否分拣
    SummaryResult():GlassNum(0),
        ngNum(0),
        okNum(0),
        suceessRate(0.0),
        sorted(0),
        unsorted(0),
        exceptNum(0),
        currentOKorNG(false),
        currentSort(false){}
};
//孔洞门夹算法处理参数
struct HoleUnit {
    HalconCpp::HObject ImageTile1R;
    HalconCpp::HObject ImageTile2R;
    HalconCpp::HObject ImageTile3R;
    HalconCpp::HObject ImageTile4R;
    int  Cam1pixs;
    int  Cam1Width;
    int  Tile2Column1;
};
//缺陷算法一组图片单元参数
struct ImageUnit {
    int ProcessStep;
    int GlassPositionInf;
    bool ErrorFlag;
    HalconCpp::HObject ImageRegion;
    HalconCpp::HObject FrameRegion;
    HalconCpp::HObject ImageList;
};


#endif // FLAWDEFINE_H

#ifndef FLAWDEFINE_H
#define FLAWDEFINE_H

#include <windows.h>
#include <mutex>
#include <queue>
#include <QString>
#include <QDateTime>
#include <mutex>
#include <thread>
#include <list>
#include <memory>
#include <vector>
#include <utility>
#include <queue>
#include <future>
#include <functional>
#include <condition_variable>
#include "HDevEngineCpp.h"
#include "HalconCpp.h"
#include <unordered_map>
#include <QDebug>

//线程安全的队列
template <typename T>
class SafeQueue{
public:
    std::queue<T> _queue;
    std::mutex _mutex;
    std::condition_variable _condition_variable;
    int _maxcount;
public:
    SafeQueue(int count = INT_MAX):_maxcount(count){
    }
    SafeQueue(SafeQueue& q) {
        if(this != &q) {
            _queue = q._queue;
        }
    }
    SafeQueue& operator=(const SafeQueue& q){
        if(this != &q) {
            _queue = q._queue;
        }
        return *this;
    }
    ~SafeQueue(){}
    bool empty(){
        std::unique_lock<std::mutex> sbguard(_mutex);
        return _queue.empty();
    }
    bool empty(std::chrono::milliseconds timeout){//如果为空，则延时等待timeout
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait_for(sbguard,timeout,[this]{
            if(_queue.empty())
                return false;
                    return true;
        });
        return _queue.empty();
    }
    int size(){
        std::unique_lock<std::mutex> sbguard(_mutex);
        return _queue.size();
    }
    T& front() {
        std::unique_lock<std::mutex> sbguard(_mutex);
        return (_queue.front());
    }
    T& back(){
        std::unique_lock<std::mutex> sbguard(_mutex);
        return (_queue.back());
    }
    void push(T& t) {//压入元素
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait(sbguard,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    void push(T& t,std::chrono::milliseconds timeout) {//压入元素
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait_for(sbguard,timeout,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    void push_back(T& t) {//压入元素
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait(sbguard,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    void push_back(T& t,std::chrono::milliseconds timeout) {//压入元素
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait_for(sbguard,timeout,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    void inqueue(T& t){
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait(sbguard,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    void inqueue(T& t,std::chrono::milliseconds timeout){
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait_for(sbguard,timeout,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    bool dequeue(T& t){
        std::unique_lock<std::mutex> sbguard(_mutex);
        if(_queue.empty()){
            _condition_variable.notify_all();
            return false;
        }
        t = std::move(_queue.front());
        _queue.pop();
        _condition_variable.notify_one();
        return true;
    }
};

class HSThreadPool{
private:
    //内置线程工作类
    class ThreadWorker{
    private:
        HSThreadPool* _pool;
        int _id;
    public:
        ThreadWorker(HSThreadPool* pool,const int id)
        :_pool(pool),_id(id){
        }
        void operator()(){
            std::function<void()> func;
            bool dequeued;
            while(!_pool->_shutdown){
                {
                    std::unique_lock<std::mutex> lock(_pool->_conditional_mutex);
                    _pool->_conditional_lock.wait(lock,[this]{if(!_pool->_queue.empty() || _pool->_shutdown)
                                                                        return true;
                                                                   return false;});
                    dequeued = _pool->_queue.dequeue(func);
                }
                if(dequeued){
                    try {
                        func();
                    } catch (...) {
                        std::cout<<std::this_thread::get_id()<<" has throw a exception";
                    }

                }
            }
        }
    };

    bool _shutdown;                                     //线程池是否关闭
    SafeQueue<std::function<void()>> _queue;            //执行函数安全队列，即任务队列
    std::vector<std::thread> _threads;                  //工作线程队列
    std::mutex _conditional_mutex;                      //线程休眠锁互斥量
    std::condition_variable _conditional_lock;          //线程环境锁，让线程可以处于休眠或者唤醒状态

public:
    explicit HSThreadPool(const int n_threads = std::thread::hardware_concurrency(), const int n_taskmaxcount = INT_MAX)
    :_shutdown(false),
     _threads(std::vector<std::thread>(n_threads)){
        _queue = SafeQueue<std::function<void()>>(n_taskmaxcount);
        for(int i=0;i<(int)_threads.size();++i){//生成指定个数线程
            _threads[i]=std::thread(ThreadWorker(this,i));
        }
    }
    HSThreadPool(const HSThreadPool&)=delete;
    HSThreadPool(HSThreadPool&&)=delete;
    HSThreadPool& operator=(const HSThreadPool&)=delete;
    HSThreadPool& operator=(HSThreadPool&&)=delete;

    void wait(){//等待所有线程执行完成
        _shutdown = true;
        _conditional_lock.notify_all(); //通知 唤醒所有工作线程

        for (int i = 0; i < (int)_threads.size(); ++i) {
            if(_threads[i].joinable()) { //判断线程是否正在等待
                _threads[i].join();  //将线程加入等待队列
            }
        }
    }

    template <typename F, typename...Args>
    auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        //连接函数和参数定义，特殊函数类型,避免左、右值错误
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        //封装获取任务对象，方便另外一个线程查看结果
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        //利用正则表达式，返回一个函数对象
        std::function<void()> wrapper_func = [task_ptr]() {
            (*task_ptr)();
        };
        // 队列通用安全封包函数，并压入安全队列
        _queue.inqueue(wrapper_func);
        // 唤醒一个等待中的线程
        _conditional_lock.notify_one();
        // 返回先前注册的任务指针
        return task_ptr->get_future();
  }
};

////单个缺陷信息
//struct GlassDefect{
//    size_t id;              // 主键id,在所有缺陷中的顺序
//    int defectId;           // 缺陷id，在一块玻璃中缺陷的顺序
//    QString time;           // 缺陷检测时间
//    QString defectType;     // 缺陷类型
//    QString defectLevel;    // 缺陷等级，OK NG
//    double x;               // 缺陷在玻璃上的X坐标
//    double y;               // 缺陷在玻璃上的Y坐标
//    double length;          // 缺陷的长度
//    double width;           // 缺陷的宽度
//    double area;            // 缺陷面积大小
//    size_t glassid;         // 外键id,玻璃的id
//    QString imagePath;      // 缺陷图片的路径
//};

//// 孔洞、门夹、丝印信息
//struct GlassSizeInfo{
//    size_t id;              // 主键id,玻璃尺寸信息的顺序id
//    int sizeno;             // 孔、门夹、丝印排列顺序
//    QString time;           // 时间
//    QString sizeType;       // 类型
//    QString sizeLevel;      // 等级
//    double lengthX;         // 长X(mm)
//    double widthY;          // 宽Y(mm)
//    double marginsX;        // 边距X(mm)
//    double marginsY;        // 边距Y(mm)
//    size_t glassid;         // 外键id,玻璃的id
//    QString imagePath;      // 缺陷图片的路径
//};

////单个缺陷
//struct DefeteData{
//    QString Time;
//    int DefectID;
//    QString DefectType;
//    QString DetectLeve;
//    double X;
//    double Y;
//    double Lenth;
//    double Width;
//    double Area;
//    QString ImageNGPath;
//};
////单块玻璃写入json文件中的缺陷数据
//struct DefeteResult{
//    int GlassID;
//    std::vector<DefeteData> defetes;
//    double GlassWidth;
//    double GlassLength;
//    double GlassAngle;
//    QString jsonFullPath; //json文件地址
//    QDateTime currentTime;
//};

////单个孔/门夹/丝印
//struct HoleData {
//    QString HolesID;
//    QString Time;
//    QString Type;
//    QString HolesLeve;
//    double DistanceHorizontal;
//    double DistanceVertical;
//    double HolesWidth;
//    double HolesHeight;
//    QString ImageHolesPath;
//};
////单块玻璃写入json文件中的数据
//struct HoleResult {
//    int GlassID;
//    std::vector<HoleData> holes;
//    double GlassLength;
//    double GlassWidth;
//    double GlassAngle;
//    QString ImageHolesLinePath;
//    QString jsonFullPath; //json文件地址
//};
////halcon ProcessHoles算法执行结果
//struct ProcessHolesAlgorithmResults {
//    int GlassID;
//    HalconCpp::HObject HolesImage;
//    HalconCpp::HObject OutLineImage;
//    HalconCpp::HTuple ResultDictHoles;
//    HalconCpp::HTuple Type;
//    HalconCpp::HTuple HolesOK;
//    HalconCpp::HTuple DistanceHorizontal;
//    HalconCpp::HTuple DistanceVertical;
//    HalconCpp::HTuple HolesWidth;
//    HalconCpp::HTuple HolesHeight;
//    HalconCpp::HTuple GlassLength;
//    HalconCpp::HTuple GlassWidth;
//    HalconCpp::HTuple GlassAngle;
//};
////halcon ProcessVision算法执行结果
//struct ProcessVisionAlgorithmResults{
//    int GlassID;
//    QString time;
//    HalconCpp::HObject ErrImage1;
//    HalconCpp::HObject ErrImage2;
//    HalconCpp::HObject ErrImage3;
//    HalconCpp::HTuple ResultDict;
//    HalconCpp::HTuple ErrName;
//    HalconCpp::HTuple ErrType;
//    HalconCpp::HTuple DefectLevel;
//    HalconCpp::HTuple ErrX;
//    HalconCpp::HTuple ErrY;
//    HalconCpp::HTuple ErrW;
//    HalconCpp::HTuple ErrL;
//    HalconCpp::HTuple ErrArea;
//    HalconCpp::HTuple YCoordOut;
//    HalconCpp::HTuple GlassLength;
//    HalconCpp::HTuple GlassWidth;
//    HalconCpp::HTuple GlassAngle;
//    HalconCpp::HTuple XValues;
//    HalconCpp::HTuple YValues;
//};
////数据统计信息
//struct GlassDataBaseInfo{
//    int id;              // 玻璃的id，唯一的主键
//    QString time;           // 时间
//    QString OKorNG;         // 整体情况OK或者NG
//    QString sizeOKorNG;     // 尺寸OK或者NG
//    double length;          // 玻璃的长度
//    double width;           // 玻璃的宽度
//    double duijiaoxian1;    // 玻璃的对角线1
//    double duijiaoxian2;    // 玻璃的对角线2
//    int defectNumber;       // 玻璃的缺陷数量
//    QString defectOKorNG;   // 缺陷OK或者NG
//    int huashanNumber;      // 划伤数量
//    int qipaoNumber;        // 气泡数量
//    int jieshiNumber;       // 结石数量
//    int benbianNumber;      // 崩边数量
//    int zanwuNumber;        // 脏污数量
//    int liewenNumber;       // 裂纹数量
//    int qitaNumber;         // 其它数量
//    GlassDataBaseInfo(){
//        id =0;
//        time = "0";
//        OKorNG = "OK";
//        sizeOKorNG = "OK";
//        length =0;
//        width =0;
//        duijiaoxian1 = 0;
//        duijiaoxian2 =0;
//        defectNumber = 0;
//        defectOKorNG = "OK";
//        huashanNumber = 0;
//        qipaoNumber = 0;
//        jieshiNumber = 0;
//        benbianNumber = 0;
//        zanwuNumber = 0;
//        liewenNumber = 0;
//        qitaNumber = 0;
//    }
//};
////数据总的统计结果
//struct SummaryResult {
//    int GlassNum;       //玻璃总数
//    int ngNum;          //NG数目
//    int okNum;          //OK数目
//    double suceessRate; //合格率
//    int sorted;         //已分拣
//    int unsorted;       //待分检
//    int exceptNum;      //异常数
//    bool currentOKorNG; //当前玻璃OK或者NG
//    bool currentSort;   //当前玻璃是否分拣
//    SummaryResult():GlassNum(0),
//        ngNum(0),
//        okNum(0),
//        suceessRate(0.0),
//        sorted(0),
//        unsorted(0),
//        exceptNum(0),
//        currentOKorNG(false),
//        currentSort(false){}
//};
////孔洞门夹算法处理参数
//struct HoleUnit {
//    HalconCpp::HObject ImageTile1R;
//    HalconCpp::HObject ImageTile2R;
//    HalconCpp::HObject ImageTile3R;
//    HalconCpp::HObject ImageTile4R;
//    int  Cam1pixs;
//    int  Cam1Width;
//    int  Tile2Column1;
//};
////缺陷算法一组图片单元参数
//struct ImageUnit {
//    int ProcessStep;
//    int GlassPositionInf;
//    bool ErrorFlag;
//    HalconCpp::HObject ImageRegion;
//    HalconCpp::HObject FrameRegion;
//    HalconCpp::HObject ImageList;
//};


#endif // FLAWDEFINE_H

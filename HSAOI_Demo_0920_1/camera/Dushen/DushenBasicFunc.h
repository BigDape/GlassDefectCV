/*******************************************
    @ClassName   : DushenBasicFunc
    @Description : 度申相机基类
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-06-20
********************************************/
#ifndef DUSHENBASICFUNC_H
#define DUSHENBASICFUNC_H

#include <QDir>
#include <QFileInfo>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMutex>
#include <QObject>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <queue>
#include "DVPCamera.h"
#include "hstool_global.h"
#include "hstool.h"

#define GRABTIMEOUT 3000 // 图像获取的超时时间 ms

struct DushenCameraArgs{
    double expo;        // 相机曝光时间
    double gain;        // 相机增益
    double height;      // 相机行数
    double framecount;  // 相机多少帧
    int fieldnumberset; // 场的数量
    int camNumber;      // 相机个数
    QString camName;    // 相机名称
};


template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() {}

     void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        condition_.notify_one();
    }

    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this](){ return!queue_.empty(); });
        if (queue_.empty()) {
            return false;
        }
        item = queue_.front();
        queue_.pop();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
};

class DushenBasicFunc : public QObject
{
    Q_OBJECT
public:
    explicit DushenBasicFunc(QObject* parent,DushenCameraArgs args);

    bool IsValidHandle(dvpHandle handle);                                       //检查相机是否存在
    void IsMonoCamera(dvpHandle handle);                                        //检查是否为黑白相机
    void InitSpinExpoTime();                                                    //初始化曝光时间
    void InitSpinGain();                                                        //初始化增益
    void InitFrameCount();                                                      //初始化帧次
    void InitImageHeight();                                                     //初始化相机高度
    void InitAEMode();
    void InitAETarget();
    void InitTrigger();                                                         //初始化trigger
    void InitROIMode();
    void InitTargetFormat();
    void InitColorSolution();
    int WIDTH_BYTES(int BitCount, int Width);
    void startGetFrameBuffer();
    void slotGrabFrames();    // 获取相机buffer
    void setThreadSafeQueue(std::shared_ptr<ThreadSafeQueue<FrameImage>> queue){ ImageQueue = queue;}
    void setFieldSelectedView(int view){ FieldSelectedView = view; }
public:
    dvpQuickRoi QuickRoiDetail;
    QString QuickRoiDetailInfo[16];
    dvpUint32 QuickRoiSel;
    dvpUint32 ColorSolutionSel;
    bool bTrigStatus;
    bool IsOpened = false;
    bool CameraState;
    bool IsStarted = false;
    unsigned int m_DisplayCount;
    unsigned int m_DisplayCountBackUp;
    QString strFrameInfo; // 帧数信息
    bool SoftTriggerFlag; // 软触发信号
    bool bMono;
    QString strFrameCount; // 相机获取到的图像帧数
    QString strFrameRate; // 图像获取帧率
    QString strFilePath; // 保存图像时用到的完整路径
    QString strDir; // 图像保存的路径
    QString strLoadPath;
    QString m_FriendlyName;
    dvpStreamState state;
    bool IsScanned;   //是否扫描
    dvpUint32 CameraCounts; //相机数量
    dvpCameraInfo info[16]; //相机信息
    int FieldNumberSet;     //场的数量
    std::atomic<int> frameSignal; //帧信号：1开始拍照，0结束拍照
private:
    dvpHandle m_handle;
    dvpFrameCount FrameCount;
    QThread* m_pThread = nullptr;
    QTimer* m_timer; // 定时器
    double m_expo;//曝光时间
    double m_gain;//相机增益
    double m_height;//拍照行数
    int m_framecount;;//帧次
    QTimer* timer; //定时器
    byte** Last_Buffer; //图片buffer缓存
    QImage m_ShowImage;  // 相机界面显示小图
    int FieldSelectedView; //相机选择的场
    std::shared_ptr<ThreadSafeQueue<FrameImage>> ImageQueue; //线程安全的队列
protected:
    void changeEvent(QEvent* e);
signals:
    void sig_DeliverImage(QImage);
    void sig_DeliverFrameRate(QString);

public slots:
    bool slot_OpenFunc(QString DeviceName);
    void slot_ScanFunc();
    void slot_Closefunc(QString DeviceName);
    void slot_StartFunc();
    void slot_StopFunc();
    void slot_ShowProperty(HWND windowsID);
    void slot_TriggerFunc();
    void slotDispRate();
    void slotDispImage();
    void slot_GetCameraState();
    bool slot_SearchCamera(QString DeviceName);
    bool slot_SaveIni(QString DeviceName);
    bool slot_LoadIni(QString DeviceName);
};

#endif // DUSHENBASICFUNC_H

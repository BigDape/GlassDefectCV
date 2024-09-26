#ifndef PROCESSTILE_H
#define PROCESSTILE_H

#include "HDevEngineCpp.h"
#include "HalconCpp.h"
#include <QObject>
#include <QQueue>
#include <QString>
#include <QtDebug>
#include <QThreadPool>
#include "hstool.h"



template <typename T>
class SafeQueue {
public:
    SafeQueue() {}

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

class ProcessTile : public QObject,public QRunnable
{
    Q_OBJECT
public:
    int MosaickNum;
    std::atomic<bool> hasStopThread;    //线程停止
public:
    ProcessTile();
    void OfflineTileImageProcess(QString fullpath);
private:
//    QList<DushenBasicFunc*> m_Cameras;
    void init_ProcessTile();
    void PreProceeTile();
    void run() ;
public:
    int FieldNumber;
    bool stopFlag_Tile;
    int TileStep;
    int FrameCount;
    int framecount;
    int GlassPosition;
    int lastGlassPosition;
    bool FirstFrame;

    int  Cam1pixs;
    int  Cam1Width;
    int  Tile2Column1;

    bool ErrFlag;
    bool LastErrFlag;
    std::mutex _mutex; // 互斥量
public slots:
    void TileImageProcess();

};


#endif // PROCESSTILE_H

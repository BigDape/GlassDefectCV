/*******************************************
    @ClassName   : ProcessTile
    @Description : Description
    @Creator     : Yangruyi
    @Author      : Yangruyi
    @Date        : 2023-09-19
********************************************/
#ifndef PROCESSTILE_H
#define PROCESSTILE_H

#include "Camera/Dushen/DushenBasicFunc.h"
#include "Camera/Dushen/mosaickimage.h"
#include "Global.h"
#include "HDevEngineCpp.h"
#include "HalconCpp.h"
#include <QObject>
#include <QQueue>
#include <QString>
#include <QtDebug>
#include "FlawDefine.h"
#include <QThreadPool>
using namespace HalconCpp;
using namespace HDevEngineCpp;

struct PDArgs{
    ImageUnit imageunit;    //缺陷算子参数
    HoleUnit holeunit;      //尺寸算子参数
};

class ProcessTile : public QObject,public QRunnable
{
    Q_OBJECT
public:
    int MosaickNum;
    HObject* MosaickHobject;
    std::atomic<bool> hasStopThread;    //线程停止
    ThreadDo* mosaickthread;
public:
    ProcessTile(QList<DushenBasicFunc*> Cameras);
    void OfflineTileImageProcess(QString fullpath);
private:
    QList<DushenBasicFunc*> m_Cameras;
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
    HTuple UserDefinedDict;

    HTuple TileColumn1;
    HTuple TileColumn2;
    HObject TileRectangle;
    HObject BackGroundImage;
    HObject GlassRegion;
    HObject ImageCrop[3];
    HObject RegionsFrameCrop;
    HObject RegionFrame;
    HObject ImageTile1;
    HObject ImageTile2;
    HObject ImageTile3;
    HObject ImageTile4;
    static HObject ImageTile1R;
    static HObject ImageTile2R;
    static HObject ImageTile3R;
    static HObject ImageTile4R;
    static int  Cam1pixs;
    static int  Cam1Width;
    static int  Tile2Column1;
    PDArgs _args;
    static bool ErrFlag;
    static bool LastErrFlag;
    std::mutex _mutex; // 互斥量
    static SafeQueue<PDArgs> preImageQueue;
    std::vector<HObject> mosaickResult;
    static QQueue<ImageUnit> ImageQueue;
public slots:
    void TileImageProcess();

};

#endif // PROCESSTILE_H

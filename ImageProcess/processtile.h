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
using namespace HalconCpp;
using namespace HDevEngineCpp;

enum GlassPart{
    UnknowPart = -1,
    Complete = 0,
    HeadPart = 1,
    MidPart = 2,
    TailPart = 3
};

class ProcessTile : public QObject {
    Q_OBJECT
    int MosaickNum;
    ThreadDo* mosaickthread;

    HObject* MosaickHobject;

public:
    ProcessTile(QList<DushenBasicFunc*> Cameras);
    void OfflineTileImageProcess(QString fullpath);
private:
    QList<DushenBasicFunc*> m_Cameras;
    void init_ProcessTile();
    void PreProceeTile();
public:
    int FieldNumber;
    bool stopFlag_Tile;
    int TileStep;
    int FrameCount;
    int framecount;
    GlassPart GlassPosition;
    GlassPart lastGlassPosition;
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
    struct ImageUnit {
        int ProcessStep;
        int GlassPositionInf;
        bool ErrorFlag;
        HObject ImageRegion;
        HObject FrameRegion;
        HObject ImageList;    
    };
    ImageUnit imageunit;
    static QQueue<ImageUnit> ImageQueue;
    static bool ErrFlag;
    static bool LastErrFlag;
public slots:
    void TileImageProcess();

};

#endif // PROCESSTILE_H

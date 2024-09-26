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
#include "HSCameraInterface.h"
#include "DVPCamera.h"
#include "hstool_global.h"
#include "hstool.h"

// 图像获取的超时时间 ms
#define GRABTIMEOUT 3000

class DushenBasicFunc : public CameraNameSpace::HSCameraInterface
{
public:
    explicit DushenBasicFunc(){}
    virtual ~DushenBasicFunc(){}

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

public:
    virtual CameraNameSpace::HSCameraError InitCamera(DushenCameraArgs args) override;
    virtual unsigned int getCameraCounts() override;
    virtual std::vector<QString> getCameraFriendlyNames() override;
    virtual QString getCurrentCameraFriendlyName() override;
    virtual bool IsScanned(const QString FriendlyName) override;
    virtual bool IsOpened(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError StopFunc(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError Closefunc(const QString FriendlyName) override;
    virtual bool SearchCamera(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError OpenFunc(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError LoadIni(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError ScanFunc(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError ShowProperty(const QString FriendlyName,HWND windowsID) override;
    virtual CameraNameSpace::HSCameraError TriggerFunc(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError SaveIni(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError setFieldSelectedView(int field) override;
    virtual CameraNameSpace::HSCameraError setSoftTriggerFlag(bool flag) override;
    virtual CameraNameSpace::HSCameraError StartFunc(const QString FriendlyName) override;
    virtual bool IsStarted(const QString FriendlyName) override;
    virtual bool GetCameraState(const QString FriendlyName) override;
    virtual QString DispRate() override;
    virtual QImage DispImage() override;
    virtual CameraNameSpace::HSCameraError startGetFrameBuffer(FrameImage& imageunit) override;

private:
    dvpQuickRoi QuickRoiDetail;
    QString QuickRoiDetailInfo[16];
    dvpUint32 QuickRoiSel = 0;              //分辨率模式索引
    dvpUint32 ColorSolutionSel = 0;
    bool bTrigStatus =  false;
    bool m_IsOpened = false;
    bool CameraState = false;               //相机状态：true：start,false:stop
    bool m_IsStarted = false;
    bool bMono;
    QString strFrameCount;                  // 相机获取到的图像帧数
    QString strFilePath;                    // 保存图像时用到的完整路径
    QString strDir;                         // 图像保存的路径
    QString strLoadPath;
    QString m_FriendlyName;
    dvpStreamState state;
    bool m_IsScanned = false;               // 是否扫描
    dvpUint32 m_CameraCounts = 0;           // 相机数量
    dvpCameraInfo info[16];                 // 相机信息
    int FieldNumberSet;                     // 场的数量
    std::atomic<int> frameSignal;           // 帧信号：1开始拍照，0结束拍照
    dvpHandle m_handle = 0;                 // 相机句柄
    dvpFrameCount FrameCount;
    QThread* m_pThread = nullptr;
    double m_expo;                          // 曝光时间
    double m_gain;                          // 相机增益
    double m_height;                        // 拍照行数
    int m_framecount;                       // 帧次
    QTimer* timer;                          // 定时器
    byte** Last_Buffer;                     // 图片buffer缓存
    QImage m_ShowImage;                     // 相机界面显示小图
    QString m_currentFriendlyName;          // 当前对象的相机名称
    QString m_currentIniPath;               // 当前相机配置文件路径
    int m_FieldSelectedView = 1;            // 相机选择的场
    bool m_SoftTriggerFlag =  false;        // 软触发信号
    int ImageOffset = 200;                  // 偏移行数
    int ImageLineSize = 0;                  // 一行像元的字节数
};

#endif // DUSHENBASICFUNC_H

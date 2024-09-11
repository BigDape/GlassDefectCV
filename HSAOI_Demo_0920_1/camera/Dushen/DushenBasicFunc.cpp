#include "DushenBasicFunc.h"
#include <QMessageBox>
#include <QDebug>
#pragma execution_character_set("utf-8")

DushenBasicFunc::DushenBasicFunc(QObject* parent,DushenCameraArgs args)
    : QObject(parent)
{
    FieldSelectedView = 1;
    m_expo = args.expo;//曝光时间
    m_gain = args.gain;//相机增益
    m_height = args.height;//拍照行数
    m_framecount = (int)args.framecount;//帧次
    m_handle = 0;
    SoftTriggerFlag = false;
    QuickRoiSel = 0;
    ColorSolutionSel = 0;
    bTrigStatus = false;
    CameraState = false;
    IsScanned = false;
    CameraCounts = 0;
    FieldNumberSet = args.fieldnumberset;//一共有多少个光场
    Last_Buffer = NULL;
    ImageQueue =  std::make_shared<ThreadSafeQueue<FrameImage>>();
    DushenBasicFunc::slot_ScanFunc();
}

void DushenBasicFunc::slot_ScanFunc()
{
    dvpStatus status;
    dvpUint32 i;

    if (!IsScanned) {
        status = dvpRefresh(&CameraCounts);
//        QString cameramountLog = "当前相机数量为 " + QString::number(CameraCounts);
//        log_singleton::Write_Log(cameramountLog, Log_Level::General);

        if (CameraCounts < 1) {
            IsScanned = false;
            return;
        }

        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Refresh fail!");
            IsScanned = false;
            return;
        }

        if (status == DVP_STATUS_OK) {
            if (CameraCounts > 16)
                CameraCounts = 16;
            for (i = 0; i < CameraCounts; i++) {
                status = dvpEnum(i, &info[i]);
                qDebug() << info[i].FriendlyName;
            }
            IsScanned = true;
        } else {
            IsScanned = false;
        }
    }
}

bool DushenBasicFunc::slot_OpenFunc(QString DeviceName)
{
    dvpStatus status;

    if (!IsScanned) {
        QMessageBox::about(NULL, "About", "Devices has not been SCANNED");
        return false;
    }

    for (dvpUint32 i = 0; i < CameraCounts; i++) {
        if (DeviceName == tr(info[i].FriendlyName)) {
            break;
        }
        if (i == (CameraCounts - 1)) {
            if (DeviceName != tr(info[i].FriendlyName)) {
                QMessageBox::about(NULL, "About", "No such Devices");
                return false;
            }
        }
    }

    if (!DushenBasicFunc::IsValidHandle(m_handle)) {

        status = dvpOpenByName(DeviceName.toLatin1().data(), OPEN_NORMAL, &m_handle);//这里获取相机句柄
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Open the camera fail!");
            return false;
        }
        m_FriendlyName = DeviceName;

        //此处添加一系列初始化流程
        DushenBasicFunc::IsMonoCamera(m_handle);
        DushenBasicFunc::InitTrigger();
        DushenBasicFunc::InitAETarget();
        DushenBasicFunc::InitROIMode();
        DushenBasicFunc::InitTargetFormat();
        DushenBasicFunc::InitColorSolution();

        status = dvpGetStreamState(m_handle, &state);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get the stream state fail!");
            return false;
        }
        if (state == STATE_STARTED) {
            status = dvpStop(m_handle);
        }

        IsOpened = true;
        return true;
    } else {
        return false;
    }
}

void DushenBasicFunc::slot_Closefunc(QString DeviceName)
{
    dvpStatus status;
    if (!IsOpened)
        return;

    status = dvpGetStreamState(m_handle, &state);
    if (state == STATE_STARTED) {

        slot_StopFunc();
        //此处添加停止采集函数
    }
    status = dvpSaveConfig(m_handle, 0);
    status = dvpClose(m_handle);
    m_handle = 0;

    IsOpened = false;
}

void DushenBasicFunc::slot_StartFunc()
{
    if (!IsOpened)
        return;

    dvpStatus status;

    if (IsValidHandle(m_handle)) {
        status = dvpGetStreamState(m_handle, &state);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get the stream state fail!");
        }
        if (state == STATE_STOPED) {
            status = dvpGetTriggerState(m_handle, &bTrigStatus);
            if (status != DVP_STATUS_FUNCTION_INVALID) {
                // 在启动视频流之前先设置为触发模式
                status = dvpSetTriggerState(m_handle, SoftTriggerFlag ? true : false);
                if (status != DVP_STATUS_OK) {
                    QMessageBox::about(NULL, "About", "Set status of trigger fail!");
                }
            }
            status = dvpStart(m_handle);
            if (status != DVP_STATUS_OK) {
                QMessageBox::about(NULL, "About", "Start the video stream fail!");
            } else {

                DushenBasicFunc::InitSpinExpoTime();        //初始化曝光时间
                DushenBasicFunc::InitSpinGain();            //初始化增益
                DushenBasicFunc::InitImageHeight();         //初始化相机高度；
                DushenBasicFunc::InitFrameCount();          //初始化帧次；

                //创建定时器
                m_timer = new QTimer(this);
                m_timer->start(1000); // 开启计算显示帧率的定时器 1000ms
                //将定时器超时信号与槽(功能函数)联系起来
                connect(m_timer, SIGNAL(timeout()), this, SLOT(slotDispRate()));
                IsStarted = true;
            }
        }
    }
}

void DushenBasicFunc::slot_StopFunc()
{
    dvpStatus status = dvpStop(m_handle);
    if (status == DVP_STATUS_OK) {
        if (m_timer->isActive()) {
            m_timer->stop();
        }
        m_pThread->requestInterruption();
        m_pThread->quit();
        m_pThread->wait();
        IsStarted = false;
    }
}


bool DushenBasicFunc::IsValidHandle(dvpHandle handle)
{
    bool bValidHandle;
    dvpIsValid(handle, &bValidHandle);
    return bValidHandle;
}

void DushenBasicFunc::IsMonoCamera(dvpHandle handle)
{
    dvpSensorInfo sSensorInfo;
    dvpStatus status = dvpGetSensorInfo(handle, &sSensorInfo);
    if (status == DVP_STATUS_OK) {
        if (SENSOR_PIXEL_MONO == sSensorInfo.pixel)
            bMono = true;
        else
            bMono = false;
    } else if (status != DVP_STATUS_OK) {
        QMessageBox::about(NULL, "About", "Get sensor information fail!");
    }
}

void DushenBasicFunc::InitSpinExpoTime()
{
    dvpDoubleDescr ExpoTimeDescr;
    dvpStatus status;

    if (IsValidHandle(m_handle)) {
        status = dvpGetExposureDescr(m_handle, &ExpoTimeDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get exposure time description fail!");
        }
        status = dvpSetExposure(m_handle, m_expo);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Set exposure time fail!");
        }
    }
}

void DushenBasicFunc::InitSpinGain()
{
    dvpStatus status;
    dvpFloatDescr AnalogGainDescr;

    if (IsValidHandle(m_handle)) {
        status = dvpGetAnalogGainDescr(m_handle, &AnalogGainDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get analog gain description fail!");
        }
        status = dvpSetAnalogGain(m_handle, m_gain);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Set analog gain fail!");
        }
    }
}

void DushenBasicFunc::InitImageHeight()
{
    dvpStatus status;

    if (IsValidHandle(m_handle)) {
        dvpRegion roi;
        status = dvpGetRoi(m_handle,&roi);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get ROI fail!");
        } else {
            roi.H = m_height;
            status = dvpSetRoi(m_handle,roi);
            if (status != DVP_STATUS_OK) {
                QMessageBox::about(NULL, "About", "Set ImageHeight fail!");
            }
            status = dvpGetRoi(m_handle,&roi);
            qDebug()<<"Height"<<roi.H;
        }
    }
}
void DushenBasicFunc::InitFrameCount()
{
    dvpStatus status;
    if (IsValidHandle(m_handle)) {
        status = dvpSetFramesPerTrigger(m_handle, m_framecount);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "set framecount fail!");
        }
    }
}

void DushenBasicFunc::InitAETarget()
{
    dvpStatus status;
    QString strValue;
    dvpInt32 iAETarget;
    dvpIntDescr sAETargetDescr;

    if (IsValidHandle(m_handle)) {
        status = dvpGetAeTargetDescr(m_handle, &sAETargetDescr);
        if (status != DVP_STATUS_OK)
            QMessageBox::about(NULL, "About", "Get AE target description fails!");
        status = dvpGetAeTarget(m_handle, &iAETarget);
        if (status != DVP_STATUS_OK)
            QMessageBox::about(NULL, "About", "Get AE target fail!");
    }
}

void DushenBasicFunc::InitTrigger()
{
    dvpStatus status;
    if (IsValidHandle(m_handle)) {
        status = dvpGetTriggerState(m_handle, &SoftTriggerFlag);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get Trigger description fail!");
        }
    }
}

void DushenBasicFunc::InitROIMode()
{

    dvpStatus status;
    dvpSelectionDescr QuickRoiDescr;

    if (IsValidHandle(m_handle)) {
        // 获取相机分辨率索引号
        status = dvpGetQuickRoiSelDescr(m_handle, &QuickRoiDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get quick roi sel description fail!");
        } else {
            for (unsigned int iNum = 0; iNum < QuickRoiDescr.uCount; iNum++) {
                status = dvpGetQuickRoiSelDetail(m_handle, iNum, &QuickRoiDetail);
                QuickRoiDetailInfo[iNum] = (QString)QuickRoiDetail.selection.string;
                //                QuickRoiDetail++; //指针后移
            }
        }
        // 获取分辨率模式索引
        status = dvpGetResolutionModeSel(m_handle, &QuickRoiSel);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get roi sel fail!");
        }
    }
}

void DushenBasicFunc::InitTargetFormat()
{
    dvpStatus status;
    if (IsValidHandle(m_handle)) {
        status = dvpSetTargetFormat(m_handle, S_BGR24);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Set target format fail!");
        }
    }
}

void DushenBasicFunc::InitColorSolution()
{

    dvpSelection ColorSolutionDetail;
    dvpStatus status;
    dvpSelectionDescr ColorSolutionDescr;

    if (IsValidHandle(m_handle)) {
        if (bMono)
            return;
        // 获取索引号
        status = dvpGetColorSolutionSelDescr(m_handle, &ColorSolutionDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get ColorSolutionDescr fail!");
        } else {
            for (unsigned int iNum = 0; iNum < ColorSolutionDescr.uCount; iNum++) {
                status = dvpGetColorSolutionSelDetail(m_handle, iNum, &ColorSolutionDetail);
            }
        }
        // 获取分辨率模式索引
        status = dvpGetColorSolutionSel(m_handle, &ColorSolutionSel);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get ColorSolutionSel fail!");
        }
    }
}




void DushenBasicFunc::slot_ShowProperty(HWND windowsID)
{
    if (IsValidHandle(m_handle)) {
        //能否显示待测试
#ifdef Q_OS_WIN32
        dvpShowPropertyModalDialog(m_handle, windowsID);
#endif
    } else {
        qDebug() << "Show Nothing";
    }
}

void DushenBasicFunc::slot_TriggerFunc()
{
    dvpStatus status;
    bool triggerState;

    status = dvpGetTriggerState(m_handle, &triggerState);
    if (status != DVP_STATUS_FUNCTION_INVALID) {
        status = dvpTriggerFire(m_handle);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Trigger fail!");
        }
    }
}

void DushenBasicFunc::slotDispRate()
{
    dvpStatus status;
    if (IsValidHandle(m_handle)) {
        //更新帧率信息
        status = dvpGetFrameCount(m_handle, &FrameCount);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get frame count fail!");
        }
        strFrameCount = QString::number(FrameCount.uFrameCount);
        strFrameRate = QString::number(FrameCount.fFrameRate);
        strFrameInfo = "采集帧数 " + strFrameCount + " 采集帧率 " + strFrameRate + " fps 显示帧率 " + QString::number(m_DisplayCount - m_DisplayCountBackUp) + " fps";
        m_DisplayCountBackUp = m_DisplayCount;
        emit sig_DeliverFrameRate(strFrameRate); //更新窗口上的帧率
    }
}

void DushenBasicFunc::slotDispImage()
{
    if (!m_ShowImage.isNull() ) {
        emit sig_DeliverImage(m_ShowImage); //图像数据到显示控件
    } else {
        return;
    }
    if (m_DisplayCount >= INT_MAX - 1) {//防止m_DisplayCount溢出
        m_DisplayCount = 0;
        m_DisplayCountBackUp = 0;
    }
    m_DisplayCount++;
}

void DushenBasicFunc::slot_GetCameraState()
{
    dvpStatus status;
    dvpStreamState state;

    status = dvpGetStreamState(m_handle, &state);
    if (status != DVP_STATUS_OK) {
        QMessageBox::about(NULL, "About", "Get the stream state fail!");
    }

    if (state == STATE_STOPED) {
        qDebug() << "CameraState is STATE_STOPED";
        CameraState = false;
    }
    if (state == STATE_STARTED) {
        qDebug() << "CameraState is STATE_STARTED";
        CameraState = true;
    }
}

bool DushenBasicFunc::slot_SearchCamera(QString DeviceName)
{
    if (!IsScanned) {
        QMessageBox::about(NULL, "About", "Devices has not been SCANNED");
        return false;
    }

    for (dvpUint32 i = 0; i < CameraCounts; i++) {
        if (DeviceName == tr(info[i].FriendlyName)) {
            qDebug() << "We Have This Camera " << DeviceName;
            break;
        }
        if (i == (CameraCounts - 1)) {
            if (DeviceName != tr(info[i].FriendlyName)) {
                qDebug() << "No such Devices";
                return false;
            }
        }
    }
    return true;
}

bool DushenBasicFunc::slot_SaveIni(QString DeviceName)
{
    char* SaveIniPath = NULL;
    QByteArray transiniVar;
    QString strSaveIni;
    dvpStatus status;

    strSaveIni = DeviceName;
    QFileInfo fi = (strSaveIni);

    if ("ini" != fi.suffix()) {
        strSaveIni = strSaveIni + ".ini";
    }

    QString currentPath = QDir::currentPath();

    QString strpath = currentPath + "/SystemParam/" + strSaveIni;
    qDebug() << strpath;

    transiniVar = strpath.toLatin1();
    SaveIniPath = transiniVar.data();

    status = dvpSaveConfig(m_handle, SaveIniPath);

    if (DVP_STATUS_OK != status) {
        QMessageBox::about(NULL, "About", "Save ini file fail!");
        return false;
    }
    return true;
}

bool DushenBasicFunc::slot_LoadIni(QString DeviceName)
{
    char* LoadPath = NULL;
    QByteArray transVar;
    dvpStatus status;

    QString currentPath = QDir::currentPath();

    strLoadPath = currentPath + "/SystemParam/" + DeviceName + ".ini";
    transVar = strLoadPath.toLatin1();
    LoadPath = transVar.data();

    status = dvpLoadConfig(m_handle, LoadPath);
    if (status != DVP_STATUS_OK) {
        QMessageBox::about(NULL, "About", "Load fail!");
        return false;
    }
    return true;
}

void DushenBasicFunc::startGetFrameBuffer()
{
    int ImageOffset = 200; // 偏移行数
    int ImageLineSize = WIDTH_BYTES(8, 8192);// 计算图像一行需要多少字节
    // 初始化数组指针
    Last_Buffer = new byte*[FieldNumberSet];
    for (int i = 0; i < FieldNumberSet; i++) {
        Last_Buffer[i] = new byte[ImageLineSize * ImageOffset];
    }
    //将定时器超时信号与槽(功能函数)联系起来
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotGrabFrames()));
    //定时器每50毫秒采集一次，显示帧率大概维持在20帧每秒
    timer->start(50);
}

void DushenBasicFunc::slotGrabFrames()
{
//    if (Global::SystemStatus == 0) return; //todo:停止的时候如何退出获取数据
    dvpFrame pFrame;            // 采集到的图像的结构体指针
    void* pBuffer = NULL;       // 采集到的图像的内存首地址

    int ImageLineSize = WIDTH_BYTES(8, 8192);// 计算图像一行需要多少字节
    int ImageOffset = 200;
    if(ImageQueue == nullptr ) {
        qFatal("ImageQueue = nullptr");
        return;
    }
    dvpStatus status;           // 采集结果
    {
       //std::lock_guard<std::mutex> sbguard(m_threadMutex);
       status = dvpGetFrame(m_handle, &pFrame, &pBuffer, GRABTIMEOUT);//从采集卡中获取一帧buffer
    }
    //pFrame.uFrameID; //帧编号
    FrameImage imageunit;
    if (status == DVP_STATUS_OK) {

        try {
            if(frameSignal.load() == 1) {
                imageunit.framecount=1;
            } else {
                imageunit.framecount++;
            }
            qDebug() << "imageunit.framecount = " << imageunit.framecount;

            //单通道图像宽度
            int FrameWidth = pFrame.iWidth;
            //单通道图像高度
            int FrameHeight;
            if (imageunit.framecount % m_framecount  == 1 || m_framecount == 1) {//第一帧是不带偏移的高度
                FrameHeight = pFrame.iHeight / FieldNumberSet;        //每个光场的高度
            } else {//非第一帧，加上200行偏移量
                FrameHeight = pFrame.iHeight / FieldNumberSet + ImageOffset;
            }

            qDebug() << "pFrame.format ="<<pFrame.format;
            int ImageSize = ImageLineSize * FrameHeight;
            byte** Dest_Buffer = new byte*[FieldNumberSet];
            for (int i = 0; i < FieldNumberSet; i++) {
                Dest_Buffer[i] = new byte[ImageSize];
            }
            //重叠区域复制
            if (imageunit.framecount % m_framecount != 1 && m_framecount > 1) {
                for (int lightnum1 = 0; lightnum1 < FieldNumberSet; lightnum1++) {
                    memcpy(Dest_Buffer[lightnum1], Last_Buffer[lightnum1], ImageLineSize * ImageOffset);
                }
            }
            // 图片重组
            for (int HeightCount = 0; HeightCount < pFrame.iHeight / FieldNumberSet; HeightCount++) {
                for (int lightnum2 = 0; lightnum2 < FieldNumberSet; lightnum2++) {
                    if (imageunit.framecount % m_framecount == 1 || m_framecount == 1) {
                        memcpy(Dest_Buffer[lightnum2] + HeightCount * ImageLineSize,
                               (byte*)pBuffer + (FieldNumberSet * HeightCount + lightnum2) * ImageLineSize,
                               ImageLineSize);
                    } else {
                        memcpy(Dest_Buffer[lightnum2] + (HeightCount + ImageOffset) * ImageLineSize,
                               (byte*)pBuffer + (FieldNumberSet * HeightCount + lightnum2) * ImageLineSize,
                               ImageLineSize);
                    }
                }
                //重叠区域获取
                if (HeightCount >= pFrame.iHeight / FieldNumberSet - ImageOffset) {
                    for (int lightnum3 = 0; lightnum3 < FieldNumberSet; lightnum3++) {
                        memcpy(Last_Buffer[lightnum3] + (HeightCount - (pFrame.iHeight / FieldNumberSet - ImageOffset)) * ImageLineSize,
                               (byte*)pBuffer + (FieldNumberSet * HeightCount + lightnum3) * ImageLineSize,
                               ImageLineSize);
                    }
                }
            }
            int PicvViewSelect = 0;
            for (int lightnum4 = 0; lightnum4 < FieldNumberSet; lightnum4++) {
                if(FieldSelectedView > 0 && FieldSelectedView <= FieldNumberSet) {
                    PicvViewSelect = FieldSelectedView - 1;
                }
                QImage buffer;
                if (pFrame.format == FORMAT_BGR24) { //其他版本先把BGR数据转成RGB数据，再用RGB数据转QImage
                    buffer = QImage((uchar*)Dest_Buffer[lightnum4], FrameWidth, FrameHeight, QImage::Format_RGB888);
                } else { //Dushen非FORMAT_BGR24类型
                    buffer = QImage((uchar*)Dest_Buffer[lightnum4], FrameWidth, FrameHeight, QImage::Format_Grayscale8);
                }

                if (lightnum4 == PicvViewSelect) {
                    m_ShowImage = buffer;
                }
                imageunit.buffer = buffer;
                delete[] Dest_Buffer[lightnum4];
            }
            delete[] Dest_Buffer;
            Dest_Buffer = nullptr;
            ImageQueue->push(imageunit);
//            QString info="相机"+ QString::number(m_handle) + "图像采集完成！";
//            log_singleton::Write_Log(info, Log_Level::General);
           DushenBasicFunc::slotDispImage();
        } catch (EXCEPINFO e) {
            qDebug()<<"多场分离报错！";
        }
    }
}

int DushenBasicFunc::WIDTH_BYTES(int BitCount, int Width)
{
    int nwBytePerLine;
    nwBytePerLine = (Width * BitCount + 31) / 32 * 4;
    return nwBytePerLine;
}


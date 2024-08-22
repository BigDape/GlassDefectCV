#include "ImageAcquisition.h"
#include "DVPCamera.h"
#include "Global.h"
//#include "log_singleton.h"
#pragma execution_character_set("utf-8")
QImageAcquisition::QImageAcquisition(dvpHandle& handle, QObject* parent, int FieldCount)
    : QObject(parent)
{
    // 初始化成员变量
    m_handle = handle;
    pBuffer = NULL;
    m_FieldCount = FieldCount;
    qDebug()<<"m_FieldCount"<<m_FieldCount;

    ImageLineSize = WIDTH_BYTES(8, 8192);
    Last_Buffer = new byte*[m_FieldCount];
    for (int i = 0; i < m_FieldCount; i++) {
        Last_Buffer[i] = new byte[ImageLineSize * ImageOffset];
    }
    imageunit.ImageList.clear();
    imageunit.FrameCount=0;
    strFrameCount=0;

    //将定时器超时信号与槽(功能函数)联系起来
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotGrabFrames()));
    //定时器每50毫秒采集一次，显示帧率大概维持在20帧每秒
    m_timer->start(50);
    //qDebug()<< __FUNCTION__ << " id = "<< QThread::currentThreadId();
}

QImageAcquisition::~QImageAcquisition()
{
    if (m_timer->isActive()) {
        m_timer->stop();
        delete m_timer;
    }
}

bool QImageAcquisition::IsValidHandle(dvpHandle handle)
{
    bool bValidHandle = false;
    dvpIsValid(handle, &bValidHandle);

    return bValidHandle;
}

int QImageAcquisition::WIDTH_BYTES(int BitCount, int Width)
{
    int nwBytePerLine;
    nwBytePerLine = (Width * BitCount + 31) / 32 * 4;
    return nwBytePerLine;
}

void QImageAcquisition::slotGrabFrames()
{
    if (Global::SystemStatus == 0) return;
    std::unique_lock<std::mutex> sbguard(m_threadMutex);
    dvpStatus status;
    //pBuffer为图片缓存,在此处做多场分离
    status = dvpGetFrame(m_handle, &m_pFrame, &pBuffer, GRABTIMEOUT);
    if (status == DVP_STATUS_OK) {
        try {
            if(Global::FrameSignal==1) {
                Global::GlobalLock.lock();
                imageunit.FrameCount=1;
                Global::GlobalLock.unlock();
            } else {
                Global::GlobalLock.lock();
                imageunit.FrameCount++;
                Global::GlobalLock.unlock();
            }
            Global::GlobalLock.lock();
            strFrameCount = imageunit.FrameCount;
            Global::GlobalLock.unlock();
            int m_FramesPerTri = int(Global::FramesPerTri);

            if (strFrameCount % m_FramesPerTri == 0) {
                    qDebug() << "strFrameCount = " << strFrameCount;
            }
            //单通道图像宽度
            FrameWidth = m_pFrame.iWidth;
            //单通道图像高度
            if (strFrameCount % m_FramesPerTri == 1 || m_FramesPerTri==1) {
                FrameHeight = m_pFrame.iHeight / m_FieldCount;
            } else {
                FrameHeight = m_pFrame.iHeight / m_FieldCount + ImageOffset;
            }

            qDebug() << "m_FramesPerTri++++++++++++++++++++++++++++++++ " << m_FramesPerTri;
            if (m_pFrame.format == FORMAT_BGR24) {
                //其他版本先把BGR数据转成RGB数据，再用RGB数据转QImage
                int ImageSize = 0;
                ImageSize = ImageLineSize * FrameHeight;
                byte** Dest_Buffer = new byte*[m_FieldCount];
                for (int i = 0; i < m_FieldCount; i++) {
                    Dest_Buffer[i] = new byte[ImageSize];
                }
                //重叠区域复制
                if (strFrameCount % m_FramesPerTri != 1 && m_FramesPerTri>1) {
                    for (int lightnum1 = 0; lightnum1 < m_FieldCount; lightnum1++) {
                        memcpy(Dest_Buffer[lightnum1], Last_Buffer[lightnum1], ImageLineSize * ImageOffset);
                    }
                }
                // 图片重组
                for (int HeightCount = 0; HeightCount < m_pFrame.iHeight / m_FieldCount; HeightCount++) {
                    for (int lightnum2 = 0; lightnum2 < m_FieldCount; lightnum2++) {
                        if (strFrameCount % m_FramesPerTri == 1 || m_FramesPerTri==1) {
                            memcpy(Dest_Buffer[lightnum2] + HeightCount * ImageLineSize, (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum2) * ImageLineSize, ImageLineSize);
                        } else {
                            memcpy(Dest_Buffer[lightnum2] + (HeightCount + ImageOffset) * ImageLineSize, (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum2) * ImageLineSize, ImageLineSize);
                        }
                    }
                    //重叠区域获取
                    if (HeightCount >= m_pFrame.iHeight / m_FieldCount - ImageOffset) {
                        for (int lightnum3 = 0; lightnum3 < m_FieldCount; lightnum3++) {
                            memcpy(Last_Buffer[lightnum3] + (HeightCount - (m_pFrame.iHeight / m_FieldCount - ImageOffset)) * ImageLineSize, (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum3) * ImageLineSize, ImageLineSize);
                        }
                    }
                }
                int PicvViewSelect = 0;
                for (int lightnum4 = 0; lightnum4 < m_FieldCount; lightnum4++) {
                    if(Global::FieldSelectedView[0]>0 && Global::FieldSelectedView[0]<=Global::FieldNumberSet) {
                        PicvViewSelect=Global::FieldSelectedView[0]-1;
                    }
                    if (lightnum4 == PicvViewSelect) {
                        m_ShowImage1 = QImage((uchar*)Dest_Buffer[lightnum4], FrameWidth, FrameHeight, QImage::Format_RGB888);
                        m_ShowImage1 = m_ShowImage1.rgbSwapped();
                        m_ShowImage = m_ShowImage1.copy();
                    }
                    HObject image;
                    byte* p = Dest_Buffer[lightnum4];
                    intptr_t intPtr = reinterpret_cast<intptr_t>(p);

                    GenImage1(&image, "byte", FrameWidth, FrameHeight, intPtr);
                    Global::GlobalLock.lock();
                    imageunit.ImageList.append(image);
                    Global::GlobalLock.unlock();
                    delete[] Dest_Buffer[lightnum4];
                }
                delete[] Dest_Buffer;
                Dest_Buffer = nullptr;
            } else {
                DWORD A = GetCurrentTime();
                qDebug() << "A:" << A;
                int ImageSize = 0;
                ImageSize = ImageLineSize * FrameHeight;
                byte** Dest_Buffer = new byte*[m_FieldCount];
                for (int i = 0; i < m_FieldCount; i++) {
                    Dest_Buffer[i] = new byte[ImageSize];
                }
                //重叠区域复制
                if (strFrameCount % m_FramesPerTri != 1 && m_FramesPerTri>1) {
                    for (int lightnum1 = 0; lightnum1 < m_FieldCount; lightnum1++) {
                        memcpy(Dest_Buffer[lightnum1], Last_Buffer[lightnum1], ImageLineSize * ImageOffset);
                    }
                }
                // 图片重组
                for (int HeightCount = 0; HeightCount < m_pFrame.iHeight / m_FieldCount; HeightCount++) {
                    for (int lightnum2 = 0; lightnum2 < m_FieldCount; lightnum2++) {
                        if (strFrameCount % m_FramesPerTri == 1 || m_FramesPerTri==1) {
                            memcpy(Dest_Buffer[lightnum2] + HeightCount * ImageLineSize, (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum2) * ImageLineSize, ImageLineSize);
                         } else {
                            memcpy(Dest_Buffer[lightnum2] + (HeightCount + ImageOffset) * ImageLineSize, (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum2) * ImageLineSize, ImageLineSize);
                         }
                    }
                    //重叠区域获取
                    if (HeightCount >= m_pFrame.iHeight / m_FieldCount - ImageOffset) {
                        for (int lightnum3 = 0; lightnum3 < m_FieldCount; lightnum3++) {
                            memcpy(Last_Buffer[lightnum3] + (HeightCount - (m_pFrame.iHeight / m_FieldCount - ImageOffset)) * ImageLineSize, (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum3) * ImageLineSize, ImageLineSize);
                        }
                    }
                }
                DWORD F = GetCurrentTime();
                DWORD G = F - A;
                qDebug() << "G:" << G;
                int PicvViewSelect = 0;
                for (int lightnum4 = 0; lightnum4 < m_FieldCount; lightnum4++) {
                    if(Global::FieldSelectedView[0]>0 && Global::FieldSelectedView[0]<=Global::FieldNumberSet) {
                        PicvViewSelect=Global::FieldSelectedView[0]-1;
                    }
                    if (lightnum4 == PicvViewSelect) {
                        m_ShowImage1 = QImage((uchar*)Dest_Buffer[lightnum4], FrameWidth, FrameHeight, QImage::Format_Grayscale8);
                        m_ShowImage = m_ShowImage1.copy();
                    }

                    HObject image;
                    byte* p = Dest_Buffer[lightnum4];
                    intptr_t intPtr = reinterpret_cast<intptr_t>(p);
                    GenImage1(&image, "byte", FrameWidth, FrameHeight, intPtr);
                    Global::GlobalLock.lock();
                    imageunit.ImageList.append(image);
                    Global::GlobalLock.unlock();
                    delete[] Dest_Buffer[lightnum4];
                }
                delete[] Dest_Buffer;
                Dest_Buffer = nullptr;
                DWORD H = GetCurrentTime();
                DWORD I = H - A;
                qDebug() << "I:" << I;
            }
            Global::GlobalLock.lock();
            ImageQueue.enqueue(imageunit);
            Global::GlobalLock.unlock();
            qDebug() << "ImageList has image count: " << imageunit.ImageList.size();
            imageunit.ImageList.clear();
            QString info="相机"+ QString::number(m_handle) + "图像采集完成！";
            log_singleton::Write_Log(info, Log_Level::General);
            emit signalDisplay();
        } catch (EXCEPINFO e) {
            qDebug()<<"多场分离报错！";
        }
    }
}

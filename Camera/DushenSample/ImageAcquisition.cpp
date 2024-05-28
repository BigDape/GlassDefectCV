#include "ImageAcquisition.h"
#include "DVPCamera.h"
#include "Global.h"

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
//    ImageList.clear();
    ImageQueue.clear();
    strFrameCount=0;
    m_timer = new QTimer();

    //将定时器超时信号与槽(功能函数)联系起来
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
    //
    // pBuffer为图片缓存,在此处做多场分离。pBuffer为线扫相机拍摄的一行透视亮场、一行反射暗场、一行反射亮场的一张图片
    //
    dvpStatus status = dvpGetFrame(m_handle, &m_pFrame, &pBuffer, GRABTIMEOUT);
    if (status == DVP_STATUS_OK) {
        try {
            if (m_threadMutex.tryLock()) {
                if (PARAM.getFrameSignal() == 1) {//拼图完成帧信号会置1，控制器进行拍照也会置1，问题：哪个会影响到判断？？？
                    imageunit.FrameCount = 1;
                } else {
                    imageunit.FrameCount++;
                }
                qDebug() << "FrameCount = " << imageunit.FrameCount;
                strFrameCount = imageunit.FrameCount;
                int m_FramesPerTri = int(PARAM.getFramesPerTri());//相机的帧次

                if (strFrameCount % m_FramesPerTri == 0) { //输出完成的帧次
                    qDebug() << "strFrameCount = " << strFrameCount;
                }

                FrameWidth = m_pFrame.iWidth;//单通道图像宽度
                //单通道图像高度
                if (strFrameCount % m_FramesPerTri == 1 || m_FramesPerTri==1) {
                    FrameHeight = m_pFrame.iHeight / m_FieldCount;//相机为1帧或者第一帧的高度
                } else {
                    FrameHeight = m_pFrame.iHeight / m_FieldCount + ImageOffset;//ImageOffset为重复部分，为了拼图做准备
                }

                qDebug() << "strFrameCount " << strFrameCount;
                qDebug() << "pBuffer" << pBuffer;

                if (m_pFrame.format == FORMAT_BGR24) {//BGR三通道24bit图
                    //其他版本先把BGR数据转成RGB数据，再用RGB数据转QImage
                    int ImageSize = 0;
                    ImageSize = ImageLineSize * FrameHeight;        //图像大小
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
                    //
                    // 图片重组:把线扫相机的三个场给分离出来
                    //
                    for (int HeightCount = 0; HeightCount < m_pFrame.iHeight / m_FieldCount; HeightCount++) {
                        for (int lightnum2 = 0; lightnum2 < 3; lightnum2++) {
                            if (strFrameCount % m_FramesPerTri == 1 || m_FramesPerTri==1) {
                                memcpy(Dest_Buffer[lightnum2] + HeightCount * ImageLineSize,
                                       (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum2) * ImageLineSize,
                                       ImageLineSize);
                            } else {
                                memcpy(Dest_Buffer[lightnum2] + (HeightCount + ImageOffset) * ImageLineSize,
                                       (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum2) * ImageLineSize,
                                       ImageLineSize);
                            }
                        }
                        //重叠区域获取，重叠区域复制过来
                        if (HeightCount >= m_pFrame.iHeight / m_FieldCount - ImageOffset) {
                            for (int lightnum3 = 0; lightnum3 < m_FieldCount; lightnum3++) {
                                memcpy(Last_Buffer[lightnum3] + (HeightCount - (m_pFrame.iHeight / m_FieldCount - ImageOffset)) * ImageLineSize,
                                       (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum3) * ImageLineSize,
                                       ImageLineSize);
                            }
                        }
                    }
                    int PicvViewSelect = 0;
                    for (int lightnum4 = 0; lightnum4 < m_FieldCount; lightnum4++) {
                        //
                        // 相机界面显示小图
                        //
                        if(PARAM.getFieldSelectedView()[0] > 0 && PARAM.getFieldSelectedView()[0] <= PARAM.getFieldNumberSet()) {
                            PicvViewSelect = PARAM.getFieldSelectedView()[0] - 1;
                        }
                        if (lightnum4 == PicvViewSelect) {
                            m_ShowImage1 = QImage((uchar*)Dest_Buffer[lightnum4], FrameWidth, FrameHeight, QImage::Format_RGB888);
                            m_ShowImage1 = m_ShowImage1.convertToFormat(QImage::Format_ARGB32).rgbSwapped();
                            m_ShowImage = m_ShowImage1.copy();
                        }
                        HObject image;
                        byte* p = Dest_Buffer[lightnum4];
                        intptr_t intPtr = reinterpret_cast<intptr_t>(p);

                        GenImage1(&image, "byte", FrameWidth, FrameHeight, intPtr);
                        imageunit.ImageList.append(image);//把每个场的照片翻入ImageList

                        delete[] Dest_Buffer[lightnum4];
                    }
                    delete[] Dest_Buffer;
                    Dest_Buffer = nullptr;

                } else {
                    DWORD A = GetCurrentTime();
                    qDebug() << "A = " << A;
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
                        for (int lightnum2 = 0; lightnum2 < 3; lightnum2++) {
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

                        if(PARAM.getFieldSelectedView()[0]>0 && PARAM.getFieldSelectedView()[0]<=PARAM.getFieldNumberSet())
                        {
                            PicvViewSelect = PARAM.getFieldSelectedView()[0]-1;
                        }
                        if (lightnum4 == PicvViewSelect) {
                            m_ShowImage1 = QImage((uchar*)Dest_Buffer[lightnum4], FrameWidth, FrameHeight, QImage::Format_Grayscale8);
                            m_ShowImage = m_ShowImage1.copy();
                        }

                        //                                        ImageList.append(m_ShowImage);
                        HObject image;
                        byte* p = Dest_Buffer[lightnum4];
                        intptr_t intPtr = reinterpret_cast<intptr_t>(p);

                        GenImage1(&image, "byte", FrameWidth, FrameHeight, intPtr);
                        imageunit.ImageList.append(image);
                        //   delete p;

                        delete[] Dest_Buffer[lightnum4];
                    }
                    delete[] Dest_Buffer;
                    Dest_Buffer = nullptr;
                    DWORD H = GetCurrentTime();
                    DWORD I = H - A;
                    qDebug() << "I:" << I;
                }
                m_threadMutex.unlock();
                ImageQueue.enqueue(imageunit);
                qDebug() << "ImageList has image count: " << imageunit.ImageList.size();
                imageunit.ImageList.clear();



    //            status=dvpGetCameraInfo(m_handle, m_dvpCameraInfo);
                QString info="相机"+ QString::number(m_handle) + "图像采集完成！";

                log_singleton::Write_Log(info, Log_Level::General);
            }
            emit signalDisplay();

            } catch (EXCEPINFO e){
                qDebug()<<"多场分离报错！";
            }

    } // if (status == DVP_STATUS_OK)
}

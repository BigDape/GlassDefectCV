#ifndef DUSHENCAMERAWIDGET_H
#define DUSHENCAMERAWIDGET_H

#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class DushenCameraWidget;
}

struct DushenCameraArgs;
class MyGraphicsItem;
class DushenBasicFunc;
template <typename T> class ThreadSafeQueue;
struct FrameImage;

class DushenCameraWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief DushenCameraWidget构造函数
     * @param parent父窗口指针
     * @param CameraName 相机名称
     * @param CameraNum 相机个数
     * @param args 相机参数
     */
    explicit DushenCameraWidget(QWidget* parent, DushenCameraArgs args);

    ~DushenCameraWidget();

    void setThreadSafeQueue(std::shared_ptr<ThreadSafeQueue<FrameImage>> queue);

    QString RealCameraName;   // 相机的真实名称
    int m_CameraNum;          // 相机的个数

    std::shared_ptr<DushenBasicFunc> CameraBase;
    MyGraphicsItem* loadedPixmapItem;
    QGraphicsScene* scene;

    int CameraFieldNum;

private slots:
    void on_pushButton_Scan_clicked();

    void on_pushButton_Open_clicked();

    void on_pushButton_Property_clicked();

    void slot_ShowImage(QImage image);

    void slot_ShowFrameRate(QString FrameRate);

    void on_pushButton_trigger_clicked();

    void on_pushButton_Save_clicked();

    void AutoOpen();

    void on_pushButton_Saveini_clicked();


    void on_pushButton_MultiFieldSelect_clicked();

public slots:

    void slot_StartCamera();

    void slot_CameraStop();

private:
    Ui::DushenCameraWidget* ui;
signals:
    void sig_SaveCameraName(QString CameraNum, QString CameraName);
};

#endif // DUSHENCAMERAWIDGET_H

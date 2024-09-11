#ifndef SINGLEFLAWSHOWWIDGET_H
#define SINGLEFLAWSHOWWIDGET_H

#include <QDate>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>
#include <unordered_map>
#include <utility>
#include "Form/MyGraphicsitem.h"
#include "Form/glassstatictablewidget.h"
#include "Form/FlawShowWidget.h"


namespace Ui {
class SingleFlawShowWidget;
}

class SingleFlawShowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleFlawShowWidget(Qt::Orientation ori,
                                Qt::Orientation pic_ori,
                                QWidget* parent = 0);
    ~SingleFlawShowWidget();
    void initLayout();
    void PickerCheckData(/*const FlawPoint& flawpoint*/);

public slots:
    void showFlawImage(QTableWidgetItem* item);
    void onItemDoubleClicked(QTableWidgetItem*);
    void slot_RecieveID(QString jsonFullPath, int glassid);
    void slot_FlawTrack(QTableWidgetItem* item);
    void slot_ButtonExportClicked();
    void slot_refrshFlaw(QString jsonFullPath,int glassid);

signals:
    void sig_paintFlawPoint(QString x, QString y);

private:
    Ui::SingleFlawShowWidget* ui;
    Qt::Orientation m_orientation;
    Qt::Orientation m_pic_orientation;
    MyGraphicsItem* loadedPixmapItem;
    QGraphicsScene* scene;
    MyGraphicsItem* loadedPixmapItem2;
    QGraphicsScene* scene2;
    MyGraphicsItem* loadedPixmapItem3;
    QGraphicsScene* scene3;
    std::unordered_map<int,std::pair<QString,QString>> rowMapXY;
    QString jsonFileName;
    int GlassID;
    QString Date;
    int LastGlassID;
    QString _selectedDir;
};

#endif  // SINGLEFLAWSHOWWIDGET_H

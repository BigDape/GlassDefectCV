#include "FlawShowWidget.h"
#include "common_func.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPushButton>
#include <QtDebug>
#include <Qwt/qwt_picker_machine.h>
#include <Qwt/qwt_legend_label.h>
#include <QCheckBox>
#include <QLineF>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <QProgressDialog>
#include <QString>
#include <fstream>
#include <QTextStream>

#pragma execution_character_set("utf-8")

FlawShowWidget::FlawShowWidget(QWidget* parent, JsonParse2Map* m_recipe)
    : QWidget(parent)
{
    RECIPE = m_recipe;
    m_plot = std::make_shared<QwtPlot>(this);
    PARAM.setPlot(m_plot);

    symbol1 = NULL;
    symbol2 = NULL;
    symbol3 = NULL;
    symbol4 = NULL;
    symbol5 = NULL;
    symbol6 = NULL;
    symbol7 = NULL;

    clock = new MsvLCDNumClockWidget(this);
    widget = new QWidget(this);


    plotpicker=new QwtPlotPicker(QwtPlot::xBottom,QwtPlot::yLeft,QwtPlotPicker::CrossRubberBand,QwtPicker::AlwaysOn,m_plot->canvas());
    plotpicker->setTrackerMode(QwtPicker::ActiveOnly);
    plotpicker->setStateMachine(new QwtPickerDragPointMachine);
    connect(plotpicker,SIGNAL(appended(const QPointF&)),this,SLOT(slot_PlotPicker(QPointF)));

    QHBoxLayout* layout0 = new QHBoxLayout(this);
    QVBoxLayout* layout1 = new QVBoxLayout(this);
    this->setLayout(layout0);

    layout0->addWidget(m_plot.get());
    layout0->addLayout(layout1);
    layout1->addWidget(clock);

    layout1->addWidget(widget);
    label1 = new QLabel("玻璃总数:", widget);
    label2 = new QLabel("OK:", widget);
    label3 = new QLabel("NG:", widget);
    label4 = new QLabel("合格率:", widget);
    label5 = new QLabel("异常数:", widget);
    label6 = new QLabel("已分拣:", widget);
    label7 = new QLabel("待分拣:", widget);

    lineedit1 = new QLineEdit(widget);
    lineedit2 = new QLineEdit(widget);
    lineedit3 = new QLineEdit(widget);
    lineedit4 = new QLineEdit(widget);
    lineedit5 = new QLineEdit(widget);
    lineedit6 = new QLineEdit(widget);
    lineedit7 = new QLineEdit(widget);

    label1->setGeometry(80, 5, 80, 25);
    label2->setGeometry(0, 45, 60, 25);
    label3->setGeometry(150, 45, 60, 25);
    label4->setGeometry(0, 90, 60, 25);
    label5->setGeometry(150, 90, 60, 25);
    label6->setGeometry(0, 135, 60, 25);
    label7->setGeometry(150, 135, 60, 25);
    QFont font1;
    font1.setPointSize(12);
    label1->setFont(font1);
    label2->setFont(font1);
    label3->setFont(font1);
    label4->setFont(font1);
    label5->setFont(font1);
    label6->setFont(font1);
    label7->setFont(font1);

    label1->setAlignment(Qt::AlignRight);
    label2->setAlignment(Qt::AlignRight);
    label3->setAlignment(Qt::AlignRight);
    label4->setAlignment(Qt::AlignRight);
    label5->setAlignment(Qt::AlignRight);
    label6->setAlignment(Qt::AlignRight);
    label7->setAlignment(Qt::AlignRight);

    QFont font2;
    font2.setPointSize(10);
    lineedit1->setFont(font2);
    lineedit2->setFont(font2);
    lineedit3->setFont(font2);
    lineedit4->setFont(font2);
    lineedit5->setFont(font2);
    lineedit6->setFont(font2);
    lineedit7->setFont(font2);

    lineedit1->setGeometry(170, 0, 60, 25);
    lineedit2->setGeometry(70, 40, 60, 25);
    lineedit3->setGeometry(220, 40, 60, 25);
    lineedit4->setGeometry(70, 85, 60, 25);
    lineedit5->setGeometry(220, 85, 60, 25);
    lineedit6->setGeometry(70, 130, 60, 25);
    lineedit7->setGeometry(220, 130, 60, 25);

    lineedit1->setReadOnly(true);
    lineedit2->setReadOnly(true);
    lineedit3->setReadOnly(true);
    lineedit4->setReadOnly(true);
    lineedit5->setReadOnly(true);
    lineedit6->setReadOnly(true);
    lineedit7->setReadOnly(true);

    lineedit1->setAlignment(Qt::AlignCenter);
    lineedit2->setAlignment(Qt::AlignCenter);
    lineedit3->setAlignment(Qt::AlignCenter);
    lineedit4->setAlignment(Qt::AlignCenter);
    lineedit5->setAlignment(Qt::AlignCenter);
    lineedit6->setAlignment(Qt::AlignCenter);
    lineedit7->setAlignment(Qt::AlignCenter);

    lineedit1->setStyleSheet("color: black; background-color: lightblue;");
    lineedit2->setStyleSheet("color: black; background-color: lightblue;");
    lineedit3->setStyleSheet("color: black; background-color: lightblue;");
    lineedit4->setStyleSheet("color: black; background-color: lightblue;");
    lineedit5->setStyleSheet("color: black; background-color: lightblue;");
    lineedit6->setStyleSheet("color: black; background-color: lightblue;");
    lineedit7->setStyleSheet("color: black; background-color: lightblue;");

    buttonClear = new QPushButton(widget);
    buttonClear->setGeometry(200, 170, 80, 30);
    buttonClear->setText("清除");
    buttonClear->setFont(font1);

    runninginfo = new ResultINFO();
    
    connect(buttonClear, SIGNAL(clicked()), this, SLOT(slot_ButtonClearClicked()));


    slot_ChangeFlawShow();

}

FlawShowWidget::~FlawShowWidget()
{
}

void FlawShowWidget::drawGlass(double x_length, double y_length)
{
//    QwtPlotShapeItem* rectangleItem = new QwtPlotShapeItem;
//    rectangleItem->setPen(QPen(Qt::black));
//    rectangleItem->setBrush(QBrush(Qt::lightGray));
//    QRectF rectangleRect(0, 0, x_length, y_length);

//    rectangleItem->setRect(rectangleRect);
//    rectangleItem->attach(m_plot);
    int count = PARAM.getCourtourMapXY().size();
    qDebug()<<"Global::courtourMapXY.size() ="<<count;
    for (int i =0; i < count; ++i) {
        QwtPlotMarker* m = new QwtPlotMarker();
        m->setSymbol(new QwtSymbol(QwtSymbol::Rect, QBrush(Qt::green), QPen(Qt::green), QSize(4, 4)));
        m->setValue(PARAM.getCourtourMapXY()[i].x.toDouble(), -PARAM.getCourtourMapXY()[i].y.toDouble());//y值都为负值
        m->attach(m_plot.get());
    }
    isGetGlassSize = false;
}

void FlawShowWidget::drawFlaw(QList<FlawPoint>* m_FlawPointList)
{
    FlawShowWidget::drawLegend();
    int ListLength = m_FlawPointList->count();
    for (int i = 0; i < ListLength; i++) {
        QwtPlotMarker* maker = new QwtPlotMarker();
        switch (m_FlawPointList->at(i).FlawType) {
        case 1:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Cross, QBrush(Qt::blue), QPen(Qt::blue), QSize(10, 10)));

            break;
        case 2:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Rect, QBrush(Qt::red), QPen(Qt::red), QSize(10, 10)));
            break;
        case 3:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Star1, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(10, 10)));
            break;
        case 4:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Triangle, QBrush(Qt::blue), QPen(Qt::blue), QSize(10, 10)));
            break;
        case 5:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Diamond, QBrush(Qt::red), QPen(Qt::red), QSize(10, 10)));
            break;
        case 6:
            maker->setSymbol(new QwtSymbol(QwtSymbol::XCross, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(10, 10)));
            break;
        case 7:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Star2, QBrush(Qt::blue),QPen(Qt::blue), QSize(10, 10)));
            break;
        }
        maker->attach(m_plot.get());
        maker->setValue(QPointF(m_FlawPointList->at(i).x, m_FlawPointList->at(i).y));
    }
    isGetFlawPoints = false;
}

void FlawShowWidget::paintEvent(QPaintEvent* e)
{
    if (isGetGlassSize && isGetFlawPoints ) {
        m_plot->detachItems();
        drawGlass(w, h);
        drawFlaw(&FlawPointList);
        m_plot->replot();
    }
}

void FlawShowWidget::resizeEvent(QResizeEvent* e)
{
    update();
}

void FlawShowWidget::slot_resize()
{
    update();
}

void FlawShowWidget::slot_GetGlassSize(GLASSINFO* info)
{
    //此处添加实际坐标与显示坐标的转换
    h = info->GlassLength;
    w = info->GlassWidth;
    isGetGlassSize = true;
    isGetFlawPoints = true;
    slot_resize();

    int MaxLength = h * 1.1;
    int MaxWidth = w * 1.1;


    qDebug() << "length = " << MaxLength << "width = " << MaxWidth;

    m_plot->setAxisScale(QwtPlot::xBottom, 0, MaxWidth);
    m_plot->setAxisScale(QwtPlot::yLeft, 0, MaxLength);
}

void FlawShowWidget::slot_GetFlawPoints(QList<FlawPoint>* n_FlawPointList)
{
    FlawPointList = *n_FlawPointList;
    isGetFlawPoints = true;
}

void FlawShowWidget::slot_ChangeFlawShow()
{
    QString Keyword4Length = "尺寸测量.长度";
    QString Keyword4Width = "尺寸测量.宽度";
    double length;
    RECIPE->getParameter(Keyword4Length, length);
    double width;
    RECIPE->getParameter(Keyword4Width, width);

    int MaxLength = length * 1.1;
    int MaxWidth = width * 1.1;

    m_plot->setAxisScale(QwtPlot::xBottom, 0, MaxWidth);
    m_plot->setAxisScale(QwtPlot::yLeft, 0, MaxLength);
}

void FlawShowWidget::slot_GetGlassResult(ResultINFO* ResInfo)
{

    runninginfo = ResInfo;

    UINT64 glassnum = ResInfo->GlassNum;
    uint ok = ResInfo->okNum;
    uint ng = ResInfo->ngNum;
    double pass = ResInfo->passRate;
    uint exceptnum = ResInfo->exceptNum;
    uint sort = ResInfo->sorted;
    uint unsort = ResInfo->unsorted;
    bool preres = ResInfo->pre_result;
    qDebug() << "glassnum" << glassnum;
    qDebug() << "ok" << ok;
    qDebug() << "ng" << ng;
    qDebug() << "pass" << pass;
    qDebug() << "exceptnum" << exceptnum;
    qDebug() << "sort" << sort;
    qDebug() << "unsort" << unsort;
    lineedit1->setText(QString::number(glassnum));
    lineedit2->setText(QString::number(ok));
    lineedit3->setText(QString::number(ng));
    lineedit4->setText(QString::number(pass));
    lineedit5->setText(QString::number(exceptnum));
    lineedit6->setText(QString::number(sort));
    lineedit7->setText(QString::number(unsort));

    emit sig_updatePreGlassRes(preres);
}

void FlawShowWidget::slot_ButtonClearClicked()
{
    lineedit1->setText("0");
    lineedit2->setText("0");
    lineedit3->setText("0");
    lineedit4->setText("0");
    lineedit5->setText("0");
    lineedit6->setText("0");
    lineedit7->setText("0");
    runninginfo->ngNum=0;
    runninginfo->ngNum=0;
    runninginfo->okNum=0;
    runninginfo->sorted=0;
    runninginfo->GlassNum=0;
    runninginfo->passRate=0;
    runninginfo->unsorted=0;
    runninginfo->exceptNum=0;
    runninginfo->pre_result="OK";
    runninginfo->sort_result="OK";
    emit sig_ClearDate();
}

void FlawShowWidget::slot_PlotPicker(const QPointF &pos)
{
    qDebug()<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
    for(const FlawPoint&flawPoints:FlawPointList){
        QPointF flawpt(flawPoints.x,flawPoints.y);
        double distance=QLineF(flawpt,pos).length();
        if(distance<10){
            qDebug()<<"**************************************************************************************************";
            qDebug()<<"缺陷"<<flawpt.x()<<" "<<flawpt.y();
            emit sig_sendFlawPoint(flawPoints);
        }

    }
}

//  画出图例
void FlawShowWidget::drawLegend()
{
    //添加图例
    legend = new QwtLegend();
    legend->setDefaultItemMode(QwtLegendData::Checkable);
    m_plot->insertLegend(legend);
    //划伤标记
    curve1 = new QwtPlotCurve("划伤");
    symbol1 = new QwtSymbol(QwtSymbol::Cross, QBrush(Qt::blue), QPen(Qt::blue), QSize(5, 5));
    curve1->setSymbol(symbol1);
    curve1->setLegendAttribute(QwtPlotCurve::LegendShowSymbol );
    curve1->attach(m_plot.get());
    //气结标记
    curve2 = new QwtPlotCurve("气泡");
    symbol2 = new QwtSymbol(QwtSymbol::Rect, QBrush(Qt::red), QPen(Qt::red), QSize(5, 5));
    curve2->setSymbol(symbol2);
    curve2->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve2->attach(m_plot.get());
    //崩边标记
    curve3 = new QwtPlotCurve("崩边");
    symbol3 = new QwtSymbol(QwtSymbol::Star1, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(5, 5));
    curve3->setSymbol(symbol3);
    curve3->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve3->attach(m_plot.get());
    //脏污标记
    curve4 = new QwtPlotCurve("脏污");
    symbol4 = new QwtSymbol(QwtSymbol::Triangle, QBrush(Qt::blue), QPen(Qt::blue), QSize(5, 5));
    curve4->setSymbol(symbol4);
    curve4->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve4->attach(m_plot.get());
    //裂纹标记
    curve5 = new QwtPlotCurve("裂纹");
    symbol5 = new QwtSymbol(QwtSymbol::Diamond, QBrush(Qt::red), QPen(Qt::red), QSize(5, 5));
    curve5->setSymbol(symbol5);
    curve5->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve5->attach(m_plot.get());
    //其他标记
    curve6 = new QwtPlotCurve("其他");
    symbol6 = new QwtSymbol(QwtSymbol::XCross, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(5, 5));
    curve6->setSymbol(symbol6);
    curve6->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve6->attach(m_plot.get());
    //缺陷7标记
    curve7 = new QwtPlotCurve("结石");
    symbol7 =  new QwtSymbol(QwtSymbol::Star2, QBrush(Qt::blue),QPen(Qt::blue), QSize(5, 5));
    curve7->setSymbol(symbol7);
    curve7->setLegendAttribute( QwtPlotCurve::LegendShowSymbol );
    curve7->attach(m_plot.get());

    QwtPlotItemList items = m_plot->itemList(QwtPlotItem::Rtti_PlotCurve);
    qDebug()<<"items.size() ="<<items.size();
    for (int i=0; i < items.size(); ++i )
    {
        if (legendVec.size() == 7)
            legendVec.clear();
        legendVec.push_back(items[i]);//依次保存图例
        const QVariant itemInfo = m_plot->itemToInfo( items[i] );
        QwtLegendLabel *legendLabel = (QwtLegendLabel *)legend->legendWidget( itemInfo ) ;
        if ( legendLabel ) {
            	legendLabel->setChecked( true );
            	replotMap[i] = true;
        }

    }
    //绑定槽函数
    connect(legend,SIGNAL(checked( const QVariant &, bool, int )), this, SLOT( slot_LegendChecked(const QVariant &, bool, int)));
}

void FlawShowWidget::slot_LegendChecked(const QVariant &itemInfo, bool on, int index)
{
    //获取曲线
    QwtPlotItem *plotItem = m_plot->infoToItem( itemInfo );
    qDebug()<<"on = "<<on;
    int result = 0;
    for(size_t i=0; i< legendVec.size(); ++i) {
        if (plotItem == legendVec[i]) { //i-1防止数组越界
           result = (int)i;
           replotMap[result] = on;
           break;
        }
    }
    //1~7对应各个缺陷类型
    FlawShowWidget::reDrawFlaw(&FlawPointList);

}

void FlawShowWidget::reDrawFlaw(QList<FlawPoint>* m_FlawPointList)
{
    m_plot->detachItems(QwtPlotItem::Rtti_PlotMarker);//清除画布上的所有
    m_plot->replot();
    //画轮廓
    for (int i =0; i < PARAM.getCourtourMapXY().size(); ++i) {
        QwtPlotMarker* m = new QwtPlotMarker();
        m->setSymbol(new QwtSymbol(QwtSymbol::Rect, QBrush(Qt::green), QPen(Qt::green), QSize(4, 4)));
        m->setValue(PARAM.getCourtourMapXY()[i].x.toDouble(), -PARAM.getCourtourMapXY()[i].y.toDouble());//y值都为负值
        m->attach(m_plot.get());
    }
    int ListLength = m_FlawPointList->count();
    for (int i = 0; i < ListLength; i++) {
        QwtPlotMarker* maker = new QwtPlotMarker();
        int tempType = m_FlawPointList->at(i).FlawType;
        if(replotMap.count(tempType -1) != 0 && replotMap[tempType -1] == true) { //缺陷类别能找到，且被点击为了true
            switch (tempType) {
            case 1:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Cross, QBrush(Qt::blue), QPen(Qt::blue), QSize(10, 10)));
                break;
            case 2:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Rect, QBrush(Qt::red), QPen(Qt::red), QSize(10, 10)));
                break;
            case 3:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Star1, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(10, 10)));
                break;
            case 4:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Triangle, QBrush(Qt::blue), QPen(Qt::blue), QSize(10, 10)));
                break;
            case 5:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Diamond, QBrush(Qt::red), QPen(Qt::red), QSize(10, 10)));
                break;
            case 6:
                maker->setSymbol(new QwtSymbol(QwtSymbol::XCross, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(10, 10)));
                break;
            case 7:
                maker->setSymbol(new QwtSymbol(QwtSymbol::Star2, QBrush(Qt::blue),QPen(Qt::blue), QSize(10, 10)));
                break;
            }
            maker->attach(m_plot.get());
            maker->setValue(QPointF(m_FlawPointList->at(i).x, m_FlawPointList->at(i).y));
        }
    }
    m_plot->replot();
}




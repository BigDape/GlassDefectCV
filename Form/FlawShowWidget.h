/*******************************************
    @ClassName   : FlawShowWidget
    @Description : 缺陷显示示意图
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-09-04
********************************************/
#ifndef FLAWSHOWWIDGET_H
#define FLAWSHOWWIDGET_H

#include <unordered_map>
#include <memory>
#include <Qwt/qwt_legend.h>
#include <Qwt/qwt_plot.h>
#include <Qwt/qwt_plot_canvas.h>
#include <Qwt/qwt_plot_grid.h>
#include <Qwt/qwt_plot_magnifier.h>
#include <Qwt/qwt_plot_marker.h>
#include <Qwt/qwt_plot_panner.h>
#include <Qwt/qwt_plot_renderer.h>
#include <Qwt/qwt_plot_shapeitem.h>
#include <Qwt/qwt_plot_textlabel.h>
#include <Qwt/qwt_plot_zoomer.h>
#include <Qwt/qwt_scale_draw.h>
#include <Qwt/qwt_scale_widget.h>
#include <Qwt/qwt_symbol.h>
#include <Qwt/qwt_text.h>
#include <QElapsedTimer>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollArea>
#include <QTimer>
#include <QWidget>
#include "Form/msvlcdnumclockwidget.h"
#include "Global.h"
#include "Parameter/JsonParse2Map.h"
#include "ImageProcess/processdetect.h"
#include "Qwt/qwt_plot_picker.h"
#include <Qwt/qwt_plot_curve.h>

class FlawShowWidget : public QWidget {
  Q_OBJECT
 public:
  explicit FlawShowWidget(QWidget* parent = nullptr,
                          JsonParse2Map* recipe = nullptr);
  virtual ~FlawShowWidget();

  enum FlawMoveWay {
    LeftToRightUp = 0,
    RightToLeftUp = 1,
    LeftToRightDown = 2,
    RightToLeftDown = 3
  };

 private:
  int w = 300, h = 200;
  int x = 10, y = 10;
 // QPainter* m_painter;

  bool isGetGlassSize = false;
  bool isGetFlawPoints = false;
  JsonParse2Map* RECIPE;

  MsvLCDNumClockWidget* clock;

  QWidget* widget;

 public:
  void drawGlass(double x_length, double y_length);
  void drawFlaw(QList<FlawPoint>* m_FlawPointList);
  void reDrawFlaw(QList<FlawPoint>* m_FlawPointList);
  void drawLegend(); //画出图例

  QLabel* label1;
  QLabel* label2;
  QLabel* label3;
  QLabel* label4;
  QLabel* label5;
  QLabel* label6;
  QLabel* label7;

  QLineEdit* lineedit1;
  QLineEdit* lineedit2;
  QLineEdit* lineedit3;
  QLineEdit* lineedit4;
  QLineEdit* lineedit5;
  QLineEdit* lineedit6;
  QLineEdit* lineedit7;

  QPushButton* buttonClear;
  QPushButton* buttonExport;

  QList<FlawPoint> FlawPointList;

  QwtPlot* m_plot;
  QwtPlotPicker* plotpicker;

  ResultINFO* runninginfo;

  QwtSymbol* symbol1;
  QwtSymbol* symbol2;
  QwtSymbol* symbol3;
  QwtSymbol* symbol4;
  QwtSymbol* symbol5;
  QwtSymbol* symbol6;
  QwtSymbol* symbol7;
  QwtLegend* legend;
  QwtPlotCurve* curve1;
  QwtPlotCurve* curve2;
  QwtPlotCurve* curve3;
  QwtPlotCurve* curve4;
  QwtPlotCurve* curve5;
  QwtPlotCurve* curve6;
  QwtPlotCurve* curve7;

  std::vector<QwtPlotItem*> legendVec;
  std::unordered_map<int,bool> replotMap;

 protected:
  void paintEvent(QPaintEvent* e);
  void resizeEvent(QResizeEvent* e);

 signals:
  void sig_updatePreGlassRes(bool);
  void sig_ClearDate();
  void sig_sendFlawPoint(const FlawPoint&flawpoint);

 public slots:
  void slot_resize();
//  void slot_GetGlassSize(GLASSINFO* info);
  void slot_GetGlassSize(GLASSINFO* info);
  void slot_GetFlawPoints(QList<FlawPoint>* n_FlawPointList);
  void slot_ChangeFlawShow();
  void slot_GetGlassResult(ResultINFO* ResInfo);
  void slot_ButtonClearClicked();
  void slot_PlotPicker(const QPointF&pos);
  void slot_LegendChecked(const QVariant &itemInfo,bool on, int index);
};

#endif  // FLAWSHOWWIDGET_H

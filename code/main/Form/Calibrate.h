#ifndef CALIBRATE_H
#define CALIBRATE_H

#include <QWidget>

namespace Ui {
class Calibrate;
}

class Calibrate : public QWidget
{
    Q_OBJECT

public:
    explicit Calibrate(QWidget *parent = nullptr);
    ~Calibrate();

private:
    Ui::Calibrate *ui;
};

#endif // CALIBRATE_H

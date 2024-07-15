#ifndef REALTIMEDEFECTS_H
#define REALTIMEDEFECTS_H

#include <QWidget>

namespace Ui {
class RealtimeDefects;
}

class RealtimeDefects : public QWidget
{
    Q_OBJECT

public:
    explicit RealtimeDefects(QWidget *parent = nullptr);
    ~RealtimeDefects();

private:
    Ui::RealtimeDefects *ui;
};

#endif // REALTIMEDEFECTS_H

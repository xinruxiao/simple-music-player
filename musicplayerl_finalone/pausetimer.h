#ifndef PAUSETIMER_H
#define PAUSETIMER_H

#include <QDialog>

#include <QTimer>
#include <QTime>
namespace Ui {
class PauseTimer;
}

class PauseTimer : public QDialog
{
    Q_OBJECT
    QTimer *timer;

public:
    explicit PauseTimer(QWidget *parent = 0);
    ~PauseTimer();
signals:

    // 这个信号是发给父窗口的。
    void ChildWindowEvent();

private:
    Ui::PauseTimer *ui;

protected slots:

    // 点击子窗口中按钮的slot
    void ClickedBtn()
    {

        // 触发子窗口的信号给父窗口接收。
        emit ChildWindowEvent();
    }


void minutes5()
{
    QTimer *timer= new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(ClickedBtn()));
    timer->start(300*1000);
}

void minutes10()
{
    QTimer *timer= new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(ClickedBtn()));
    timer->start(600*1000);
}

void minutes20()
{
    QTimer *timer= new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(ClickedBtn()));
    timer->start(1200*1000);
}

void minutes30()
{
    QTimer *timer= new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(ClickedBtn()));
    timer->start(1800*1000);
}

void minutes45()
{
    QTimer *timer= new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(ClickedBtn()));
    timer->start(2700*1000);
}

void minutes60()
{
    QTimer *timer= new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(ClickedBtn()));
    timer->start(3600*1000);
}
};

#endif // PAUSETIMER_H

#ifndef PLAYTIMER_H
#define PLAYTIMER_H

#include <QDialog>
#include <QTimer>
#include <QTime>

namespace Ui
{
    class PlayTimer;
}

class PlayTimer : public QDialog
{
    Q_OBJECT
    QTimer *timer2;

public:

    explicit PlayTimer(QWidget *parent = 0);
    ~PlayTimer();  


private:
    Ui::PlayTimer *ui;

protected slots:

    void ClickedBtn2()    // 点击子窗口中按钮的slot
    {   
        emit ChildWindowEvent2();  // 触发子窗口的信号给父窗口接收。
    }

    void minutes5()
    {
        QTimer *timer2= new QTimer(this);
        connect(timer2, SIGNAL(timeout()), this, SLOT(ClickedBtn2()));
        timer2->start(300*1000);
    }
    void minutes10()
    {
        QTimer *timer2= new QTimer(this);
        connect(timer2, SIGNAL(timeout()), this, SLOT(ClickedBtn2()));
        timer2->start(600*1000);
    }
    void minutes20()
    {
        QTimer *timer2= new QTimer(this);
        connect(timer2, SIGNAL(timeout()), this, SLOT(ClickedBtn2()));
        timer2->start(1200*1000);
    }
    void minutes30()
    {
        QTimer *timer2= new QTimer(this);
        connect(timer2, SIGNAL(timeout()), this, SLOT(ClickedBtn2()));
        timer2->start(1800*1000);
    }
    void minutes45()
    {
        QTimer *timer2= new QTimer(this);
        connect(timer2, SIGNAL(timeout()), this, SLOT(ClickedBtn2()));
        timer2->start(2700*1000);
    }
    void minutes60()
    {
        QTimer *timer2= new QTimer(this);
        connect(timer2, SIGNAL(timeout()), this, SLOT(ClickedBtn2()));
        timer2->start(3600*1000);
    }
signals:

    void ChildWindowEvent2(); // 这个信号是发给父窗口的。
};

#endif // PLAYTIMER_H

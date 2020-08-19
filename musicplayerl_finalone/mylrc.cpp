#include "mylrc.h"
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include"ui_mylrc.h"
MyLrc::MyLrc(QWidget *parent) :
    QLabel(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // 设置背景透明
    setAttribute(Qt::WA_TranslucentBackground);

    // 固定部件大小
    setMaximumSize(1000, 100);
    setMinimumSize(1000, 100);

    // 歌词的线性渐变填充
    linearGradient.setStart(0, 10);
    linearGradient.setFinalStop(0, 100);
    linearGradient.setColorAt(0.1, QColor(14, 179, 255));
    linearGradient.setColorAt(0.5, QColor(114, 232, 255));
    linearGradient.setColorAt(0.9, QColor(14, 179, 255));
    // 遮罩的线性渐变填充
    maskLinearGradient.setStart(0, 10);
    maskLinearGradient.setFinalStop(0, 100);
    maskLinearGradient.setColorAt(0.1, QColor(222, 54, 4));
    maskLinearGradient.setColorAt(0.5, QColor(255, 72, 16));
    maskLinearGradient.setColorAt(0.9, QColor(222, 54, 4));
    // 设置字体
    font.setFamily("Times New Roman");
    font.setBold(true);
    font.setPointSize(30);
    // 设置定时器
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    lrcMaskWidth = 0;
    lrcMaskWidthInterval = 0;
}

void MyLrc::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setFont(font);

    painter.setPen(QColor(0, 0, 0, 200));  // 先绘制底层文字，作为阴影，这样会使显示效果更加清晰，且更有质感
    painter.drawText(1, 1, 800, 60, Qt::AlignLeft, text());

    painter.setPen(QPen(linearGradient, 0));  // 再在上面绘制渐变文字
    painter.drawText(0, 0, 800, 60, Qt::AlignLeft,  text());


    painter.setPen(QPen(maskLinearGradient, 0));   // 设置歌词遮罩
    painter.drawText(0, 0, lrcMaskWidth, 60, Qt::AlignLeft,  text());
}


void MyLrc::startLrcMask(qint64 intervalTime)  // 开启遮罩，需要指定当前歌词开始与结束之间的时间间隔
{

    /*这里设置每隔30毫秒更新一次遮罩的宽度，因为如果更新太频繁
       会增加CPU占用率，而如果时间间隔太大，则动画效果就不流畅了 */


    qreal count = intervalTime / 30;    
    lrcMaskWidthInterval = 1000 / count;
    lrcMaskWidth = 0;
    timer->start(30);
}


void MyLrc::stopLrcMask()    // 停止遮罩
{
    timer->stop();
    lrcMaskWidth = 0;
    update();
}

void MyLrc::mousePressEvent(QMouseEvent *event)  // 两个鼠标事件处理函数实现了部件的拖动
{
    if (event->button() == Qt::LeftButton)
        offset = event->globalPos() - frameGeometry().topLeft();
}

void MyLrc::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
         setCursor(Qt::PointingHandCursor);
         move(event->globalPos() - offset);
    }
}


void MyLrc::contextMenuEvent(QContextMenuEvent *event)  // 实现右键菜单来隐藏部件
{
    QMenu menu;
    menu.addAction(tr("隐藏"), this, SLOT(hide()));
    menu.exec(event->globalPos());
}

void MyLrc::timeout()  // 定时器溢出时增加遮罩的宽度，并更新显示
{
    lrcMaskWidth += lrcMaskWidthInterval;
    update();
}

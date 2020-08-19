#include "controlvoice.h"
#include "ui_controlvoice.h"
#include"mainwindow.h"
#include <QSlider>
#include<QtMultimedia>

Controlvoice::Controlvoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Controlvoice)
{
    ui->setupUi(this);
    setWindowTitle(tr("调节音量"));
    this->setWindowOpacity(0.85);
    this->setMaximumSize(400,64);
    this->setMinimumSize(400,64);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(100);
    connect(ui->horizontalSlider,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    connect(ui->horizontalSlider,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
}

Controlvoice::~Controlvoice()
{
    delete ui;
}

void Controlvoice::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        dragPos=event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
}

void Controlvoice::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        move(event->globalPos()-dragPos);
        event->accept();
    }
}

void Controlvoice::positionChanged(qint64 position)
{
    ui->horizontalSlider->setValue(position);
}

void Controlvoice::durationChanged(qint64 duration)
{
    ui->horizontalSlider->setRange(0,duration);
}

void Controlvoice::on_horizontalSlider_valueChanged(int value)
{
    ui->lineEdit->setText(QString ::number(value));
    emit send(value);
}

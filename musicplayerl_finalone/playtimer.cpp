#include "playtimer.h"
#include "ui_playtimer.h"
#include <QTimer>
#include <QTime>
PlayTimer::PlayTimer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayTimer)
{
    ui->setupUi(this);
    setWindowTitle(tr("定时播放"));
    this->setWindowOpacity(0.85);
    this->setMaximumSize(358,441);
       this->setMinimumSize(358,441);
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(minutes5()));
        connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(minutes10()));
        connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(minutes20()));
        connect(ui->pushButton_5, SIGNAL(clicked()), SLOT(minutes30()));
        connect(ui->pushButton_6, SIGNAL(clicked()), SLOT(minutes45()));
        connect(ui->pushButton_7, SIGNAL(clicked()), SLOT(minutes60()));
}

PlayTimer::~PlayTimer()
{
    delete ui;
}





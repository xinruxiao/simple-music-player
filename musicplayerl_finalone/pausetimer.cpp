#include "pausetimer.h"
#include "ui_pausetimer.h"
#include"mainwindow.h"
#include <QTimer>
#include <QTime>

PauseTimer::PauseTimer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PauseTimer)
{
    ui->setupUi(this);
    setWindowTitle(tr("定时停止"));
    this->setWindowOpacity(0.85);
    this->setMaximumSize(334,443);
    this->setMinimumSize(334,443);
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(minutes5()));
    connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(minutes10()));
    connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(minutes20()));
    connect(ui->pushButton_9, SIGNAL(clicked()), SLOT(minutes30()));
    connect(ui->pushButton_5, SIGNAL(clicked()), SLOT(minutes45()));
    connect(ui->pushButton_7, SIGNAL(clicked()), SLOT(minutes60()));
}

PauseTimer::~PauseTimer()
{
    delete ui;
}


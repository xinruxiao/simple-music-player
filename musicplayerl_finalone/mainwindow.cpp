#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtMultimedia>
#include <QFileDialog>
#include<QTableWidgetItem>
#include<QtWidgets>
#include<QDir>
#include <QSlider>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"controlvoice.h"
#include <QLabel>
#include <QToolBar>
#include <QTime>
#include <QMessageBox>
#include<QFile>
#include <QFileInfo>
#include <QFileDialog>
#include<QDebug>
#include <QDesktopServices>
using namespace std;
#include "mylrc.h"
#include <QTextCodec>
#include<QTimer>
#include <QSystemTrayIcon>
#include "pausetimer.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle (tr("player"));
    this->setWindowOpacity(0.85);
    this->setMaximumSize(462,722);
    this->setMinimumSize(462,722);

    connect(&pa2, SIGNAL(ChildWindowEvent()), SLOT(ChildWindowEventSlot()));
    connect(&pl2, SIGNAL(ChildWindowEvent2()), SLOT(ChildWindowEventSlot2()));
    qplaylist=new Playlist;
    connect(qplaylist,SIGNAL(sendRow(int)),this,SLOT(receiveRow(int)));
    connect(qplaylist,SIGNAL(sendDeleterow(int)),this,SLOT(receiveDeleterow(int)));
    connect(qplaylist,SIGNAL(sendToppiece(int)),this,SLOT(receiveToppiece(int)));

    qmyLove=new myLove;
    connect(qmyLove,SIGNAL(sendRow(int)),this,SLOT(receiveRow(int)));

    con=new Controlvoice(this);
    QObject::connect(con,SIGNAL(send(int)),this,SLOT(changeVolumn(int)));

    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(setPosition(int)));
    connect(ui->comboBox_2,SIGNAL(currentIndexChanged(int)),this,SLOT(patternChange()));

    create();
    build();

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LoveButton_clicked()
{
  qmyLove->show();
}

void MainWindow::on_StopButton_clicked()
{
    pl2.show();
}

void MainWindow::on_StartButton_clicked()
{
    pa2.show();
}

void MainWindow::on_PlaylistButton_clicked()
{

    qplaylist->show();
}

void MainWindow::on_VoiceButton_clicked()
{

    con->show();
}

void MainWindow::on_PlayButton_clicked()
{
    if(flag!=0)
        player->pause();

    player->play();
    showsong();

    flag=1;

    resolveLrc(player->metaData(QMediaMetaData::Title).toString());//接在所有play后;
}

void MainWindow::on_StopPieceButton_clicked()
{
   player->stop();
    lrc2.stopLrcMask();
   flag=0;
}

void MainWindow::on_PauseButton_clicked()
{
    player->pause();
    flag=0;
}

void MainWindow::on_pushButton_24_clicked()
{
    this->hide();
    if(n==0)
    {
        tuopan();
        n++;
    }
}

void MainWindow::tuopan()
{
            QSystemTrayIcon *trayicon = new QSystemTrayIcon(this);
            QMenu * trayiconMenu=new QMenu(this);
            QAction *pre=new QAction(QIcon("://resources/1.png"),tr("上一首"),this);
            QAction *next=new QAction(QIcon("://resources/22.png"),tr("下一首"),this);
            QAction *zanting=new QAction(QIcon("://resources/21.png"),tr("暂停"),this);
            QAction *quit=new QAction(QIcon("://resources/25.png"),tr("退出"),this);

            trayiconMenu->addAction(pre);

            trayiconMenu->addAction(next);
            trayiconMenu->addAction(zanting);
            trayiconMenu->addAction(quit);

            //点击菜单中的退出时，退出程序
            connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
            //点击菜单中的上一首时，切换到上一首歌曲
            connect(pre, SIGNAL(triggered()), this, SLOT(on_LatPieceButton_clicked()));
            //点击菜单中的下一首时，切换到下一首歌曲
            connect(next, SIGNAL(triggered()), this, SLOT(on_NextPieceButton_clicked()));
            //暂停
            connect(zanting, SIGNAL(triggered()), this, SLOT(on_PauseButton_clicked()));

            trayicon->setContextMenu(trayiconMenu);
            trayicon->setIcon(QIcon("://resources/logo.png"));//显示托盘图标
            trayicon->setToolTip(tr("明天的网易云音乐"));
            trayiconMenu = new QMenu(this);
            trayicon->show();
            //为系统托盘绑定单击信号的槽 即图标激活时
            connect(trayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason)));

}

void MainWindow::onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason==QSystemTrayIcon::Trigger)
        this->show();
}

void MainWindow::on_LatPieceButton_clicked()
{
    lrc2.stopLrcMask();
    int currentIndex=playlist->currentIndex();
    if(--currentIndex<0)
        currentIndex=0;
    playlist->setCurrentIndex(currentIndex);
    if(flag!=0)
        player->pause();
    player->play();
    MainWindow::showsong();
    flag=1;

    on_PlayButton_clicked();
}

void MainWindow::on_NextPieceButton_clicked()
{
    lrc2.stopLrcMask();
    int currentIndex=playlist->currentIndex();
    if(++currentIndex==playlist->mediaCount())
        currentIndex=0;
    playlist->setCurrentIndex(currentIndex);
    if(flag!=0)
    {
         player->pause();

    }
    player->play();
    showsong();
    flag=1;
    showsong();
    on_PlayButton_clicked();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        dragPos=event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        move(event->globalPos()-dragPos);
        event->accept();
    }


}

void MainWindow::positionChanged(qint64 position)
{
    ui->horizontalSlider->setValue(position);
    MainWindow::updateDurationInfo(position / 1000);

}

void MainWindow::durationChanged(qint64 duration)
{
    ui->horizontalSlider->setRange(0,duration);
    MainWindow::updateDurationInfo(duration / 1000);

}

void MainWindow::setPosition(int position)
{
    player->setPosition(position);
    MainWindow::updateDurationInfo(position / 1000);
}

void MainWindow::patternChange()
{
    if(ui->comboBox_2->currentIndex()==0)
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
    if(ui->comboBox_2->currentIndex()==1)
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    if(ui->comboBox_2->currentIndex()==2)
    {

        playlist->clear();


        srand(time(0));
        int *p,j=0,m;
        p=new int[playlists.size()];
        int i=rand()%playlists.size()+0;
        int flag=0;
        for(;j<=playlists.size();i=rand()%playlists.size())
        {
            p[j]=i;
            if(flag==0)
            {
                playlist->addMedia(QUrl::fromLocalFile(playlists.at(i).absoluteFilePath()));
                p[j]=i;
                flag=1;
                j++;
             }

             if(flag==1)
             {
                 for(m=0;m<j;m++)
                 {
                     if( p[j]==p[m])
                         break;
                 }
                 if(m==j)
                 {
                      playlist->addMedia(QUrl::fromLocalFile(playlists.at(i).absoluteFilePath()));
                      p[j]=i;
                      j++;
                 }
             }
        }
        playlist->setPlaybackMode(QMediaPlaylist::Random);
    }

}

void MainWindow::updateDurationInfo(qint64 currentInfo)
 {
    int duration=player->metaData(QMediaMetaData::Duration).toInt();
    QString tStr,tStr2;
    if(currentInfo ||duration)
    {
         QTime currentTime((currentInfo/3600)%60, (currentInfo/60)%60,currentInfo%60, (currentInfo*1000)%1000);
         QTime totalTime((duration/3600)%60, (duration/60)%60,duration%60, (duration*1000)%1000);
         QString format = "mm:ss";

         tStr = currentTime.toString(format) ;
         tStr2= totalTime.toString(format);

    }

    ui->label_3 ->setText(tStr);

    if(!lrcMap.isEmpty())
    {
        /* 获取当前时间在歌词中的前后两个时间点 */
        qint64 previous = 0;
        qint64 later = 0;
        foreach (qint64 value, lrcMap.keys())
        {
            if ((currentInfo*1000+1500)>=value )
            {
                 previous = value;
            }
            else
            {
                   later = value;
                   break;
            }
        }

           /*达到最后一行,将later设置为歌曲总时间的值*/
        if(later == 0)
            later = duration-6000;


           /* 获取当前时间所对应的歌词内容*/
        QString currentLrc = lrcMap.value(previous);

           /*没有内容时*/
        if(currentLrc.length() < 2)
              currentLrc = tr(" ");

           /*如果是新的一行歌词，那么重新开始显示歌词遮罩*/
        if(currentLrc != lrc2.text())
        {
               lrc2.setText(currentLrc);
               qint64 intervalTime = later - previous;
               lrc2.startLrcMask(intervalTime);
        }
    }
    else
    {
        lrc2.setText(QFileInfo((player->metaData(QMediaMetaData::Title).toString())).baseName());
    }
}

void MainWindow::changeVolumn(int value)
{
   player->setVolume(value);
}

void MainWindow::receiveRow(int row)
{
    piece=row;
    if(flag!=0)
        player->pause();
    playlist->clear();
    build();            //建立播放列表
    player->play();
    MainWindow::showsong();
    flag=1;
}

void MainWindow::build()
{
    int volume=80;
    playlist=new QMediaPlaylist;

    /*根据播放列表反馈的信号调整主界面的运行*/
    if(DeleteRow==-1)     //如果播放列表没有删除歌曲
        {
            if(Toppiece!=-1)   //如果播放列表顶歌
            {
                playlist->clear();
                if(Topflag==0)
                {
                    playlist->addMedia(QUrl::fromLocalFile(playlists.at(Toppiece).absoluteFilePath()));
                    int n;
                    for(n=0;n<playlists.size();++n)
                    if(n!=Toppiece)
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(n).absoluteFilePath()));
                    Topflag=1;
                    tempToppiece=Toppiece;
                }
                else
                {
                    if(Toppiece<tempToppiece)
                    {
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(Toppiece-1).absoluteFilePath()));
                        int n;
                        for(n=0;n<playlists.size();++n)
                        if(n!=Toppiece-1)
                            playlist->addMedia(QUrl::fromLocalFile(playlists.at(n).absoluteFilePath()));
                    }
                    else
                    {
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(Toppiece).absoluteFilePath()));
                        int n;
                        for(n=0;n<playlists.size();++n)
                        if(n!=Toppiece)
                            playlist->addMedia(QUrl::fromLocalFile(playlists.at(n).absoluteFilePath()));
                    }
                    tempToppiece=Toppiece;
                }
                if(piece!=-1)   //如果播放列表双击歌曲
                {
                    playlist->clear();
                    int j;

                    for(j=piece-1;j<playlists.size();j++)
                         playlist->addMedia(QUrl::fromLocalFile(playlists.at(j).absoluteFilePath()));
                    for(j=0;j<piece-1;++j)
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(j).absoluteFilePath()));
                    piece=-1;
                }

            }
            else
            {

                if(piece!=-1)  //如果播放列表双击歌曲
                {
                    int j;
                    for(j=piece;j<playlists.size();j++)
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(j).absoluteFilePath()));
                    for(j=0;j<piece;++j)
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(j).absoluteFilePath()));
                    piece=-1;
                }
                else
                {
                    for(int i=0;i<playlists.size();i++)
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(i).absoluteFilePath()));
                }
            }
        }
        else   //如果播放列表删除歌曲
        {
            if(Toppiece!=-1)
            {
                playlist->clear();
                if(Topflag==0)
                {
                    playlist->addMedia(QUrl::fromLocalFile(playlists.at(Toppiece).absoluteFilePath()));
                    int n;
                    for(n=0;n<playlists.size();++n)
                    if(n!=Toppiece)
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(n).absoluteFilePath()));
                    Topflag=1;
                    tempToppiece=Toppiece;
                }
                else
                {
                    if(Toppiece<tempToppiece)
                    {
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(Toppiece-1).absoluteFilePath()));
                        int n;
                        for(n=0;n<playlists.size();++n)
                        if(n!=Toppiece-1)
                            playlist->addMedia(QUrl::fromLocalFile(playlists.at(n).absoluteFilePath()));
                    }
                    else
                    {
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(Toppiece).absoluteFilePath()));
                        int n;
                        for(n=0;n<playlists.size();++n)
                        if(n!=Toppiece)
                            playlist->addMedia(QUrl::fromLocalFile(playlists.at(n).absoluteFilePath()));
                    }
                    tempToppiece=Toppiece;
                }
                if(piece!=-1)  //如果播放列表双击歌曲
                {
                    playlist->clear();
                    int j;

                    for(j=piece-1;j<playlists.size();j++)
                         playlist->addMedia(QUrl::fromLocalFile(playlists.at(j).absoluteFilePath()));
                    for(j=0;j<piece-1;++j)
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(j).absoluteFilePath()));
                    piece=-1;
                }

            }
            else
            {

                if(piece!=-1)  //如果播放列表双击歌曲
                {
                    int j;
                    for(j=piece;j<playlists.size();j++)
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(j).absoluteFilePath()));
                    for(j=0;j<piece;++j)
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(j).absoluteFilePath()));
                    piece=-1;
                }
                else
                {
                    for(int i=0;i<playlists.size();i++)
                        playlist->addMedia(QUrl::fromLocalFile(playlists.at(i).absoluteFilePath()));
                }
            }
        }

         playlist->setPlaybackMode(QMediaPlaylist::Loop);
         player=new QMediaPlayer;
         player->setPlaylist((playlist));

         player->setVolume(volume);
         connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
         connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));

}

void MainWindow::receiveDeleterow(int deleterow)
{
    DeleteRow=deleterow;
    if(DeleteRow!=-1)
        {
            playlists.removeAt(DeleteRow);
            playlist->clear();
        }
        build();
        if(flag!=0)
            player->pause();
        player->play();
        flag=1;
}
void MainWindow::receiveToppiece(int toppiece)
{
    Toppiece=toppiece;
    playlist->clear();
    playlist=new QMediaPlaylist;

    build();

    if(flag!=0)
        player->pause();
    player->play();
    flag=1;

}
void MainWindow::create()
{
    QDir dir("E:/CloudMusic/");
    QStringList filters;
    filters<<"*.mp3";
    dir.setNameFilters(filters);
    playlists=dir.entryInfoList(filters);
}

void MainWindow::showsong()
{

   QString Name=player->metaData(QMediaMetaData::Title).toString();
   ui->label_5->setText( Name);
}

void MainWindow::resolveLrc(const QString &sourceFileName)  //解析LRC歌词
{

    lrcMap.clear();  // 先清空以前的内容
    if(sourceFileName.isEmpty())  // 获取LRC歌词的文件名
        return ;

    QString fileName = sourceFileName;
    QString lrcFileName ="E:/CloudMusic/"+fileName + ".lrc";


    QFile *file1=new QFile;  // 打开歌词文件
    file1->setFileName(lrcFileName);
    bool ok=file1->open(QIODevice::ReadOnly);

    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale()); // 设置字符串编码
    QString allText = QString(file1->readAll());// 获取全部歌词信息

    file1->close();    
    QStringList lines = allText.split("\n");  // 将歌词按行分解为歌词列表

    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");   // 使用正则表达式将时间标签和歌词内容分离
    foreach (QString oneLine, lines)   // 先在当前行的歌词的备份中将时间内容清除，这样就获得了歌词文本
    {
        QString temp = oneLine;
        temp.replace(rx, "");

        /* 然后依次获取当前行中的所有时间标签，并分别与歌词文本存入QMap中*/
        int pos = rx.indexIn(oneLine, 0);

        while (pos != -1) {
        QString cap = rx.cap(0);

        /*将时间标签转换为时间数值，以毫秒为单位*/
        QRegExp regexp;
        regexp.setPattern("\\d{2}(?=:)");
        regexp.indexIn(cap);
        int minute = regexp.cap(0).toInt();
        regexp.setPattern("\\d{2}(?=\\.)");
        regexp.indexIn(cap);

        int second = regexp.cap(0).toInt();
        regexp.setPattern("\\d{2}(?=\\])");
        regexp.indexIn(cap);
        int millisecond = regexp.cap(0).toInt();
        qint64 totalTime = minute * 60000 + second * 1000 + millisecond*10 ;
        lrcMap.insert(totalTime, temp);
        pos += rx.matchedLength();
        pos = rx.indexIn(oneLine, pos);

    }

    /*如果lrcMap为空*/
    if (lrcMap.isEmpty())
    {
        lrc2.setText(QFileInfo((player->metaData(QMediaMetaData::Title).toString())).baseName()+ tr(" --- 未找到歌词文件！"));
        return;
    }
}

}
void MainWindow::on_pushButton_clicked()
{
    lrc2.show();
}




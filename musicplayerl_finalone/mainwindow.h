
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include"mylove.h"
#include"playtimer.h"
#include"pausetimer.h"
#include"search.h"
#include"playlist.h"
#include"controlvoice.h"
#include<QtMultimedia>
#include"controlvoice.h"
#include<QWidget>
#include"mylrc.h"
#include<QMediaPlayer>
#include<QTime>
#include<QTimer>
#include<QFileInfoList>
class QLabel;
#include <QSystemTrayIcon>

namespace Ui
{
     class MainWindow;
}

class MainWindow : public QMainWindow
{
     Q_OBJECT
     int n=0;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QFileInfoList playlists;
    void updateDurationInfo(qint64 currentInfo);
    Controlvoice *con;
    Playlist *qplaylist;
    void stateChanged(QMediaPlayer::State);
    void showsong();
    myLove *qmyLove;

private slots:

    void on_LoveButton_clicked();

    void on_StopButton_clicked();

    void on_StartButton_clicked();

    void on_SearchButton_clicked();

    void on_PlaylistButton_clicked();

    void on_VoiceButton_clicked();

    void on_PlayButton_clicked();

    void on_StopPieceButton_clicked();

    void on_PauseButton_clicked();

    void on_LatPieceButton_clicked();

    void on_NextPieceButton_clicked();

    void positionChanged(qint64);

    void durationChanged(qint64);

    void setPosition(int);

    void patternChange();

    void changeVolumn(int value);

    void receiveRow(int row);

    void receiveDeleterow(int deleterow);

    void on_pushButton_clicked();

    void on_pushButton_24_clicked();

    void onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason);

    void receiveToppiece(int toppiece);

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void tuopan();


private:
    Ui::MainWindow *ui;
    QPoint dragPos;
    PlayTimer pl2;
    PauseTimer pa2;
    Controlvoice co2;
    MyLrc lrc2;
    int flag=0;
    int piece=-1;
    void build();
    int DeleteRow=-1;
    MyLrc *lrc;
    QMap<qint64, QString> lrcMap;
    void resolveLrc(const QString &sourceFileName);
    int Toppiece=-1;
    int Topflag=0;
    int tempToppiece=-1;
    void create();
protected slots:

    // 父窗口用于接收子窗口信号的slot。
    void ChildWindowEventSlot()
    {
        on_PauseButton_clicked();
    }

    void ChildWindowEventSlot2()
    {
        on_PlayButton_clicked();
    }
};

#endif // MAINWINDOW_H

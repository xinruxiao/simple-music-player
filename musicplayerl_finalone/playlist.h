#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QDialog>
#include <QWidget>
#include<QMediaPlaylist>
#include<QMediaPlayer>
#include<QTableWidgetItem>
#include<QFileInfoList>
namespace Ui {
class Playlist;
}

class Playlist : public QDialog
{
    Q_OBJECT

public:
    explicit Playlist(QWidget *parent = 0);
    ~Playlist();
    QMediaPlayer *player=NULL;
     QFileInfoList playlists;


private slots:
    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void build();

private:
    Ui::Playlist *ui;
    int tempRow=-1;
    void create();
    int deleterow=-1;
    int toppiece=-1;
    int Topflag=0;
    int tempToppiece=-1;

signals:
    void sendRow(int);
    void sendDeleterow(int);
    void sendToppiece(int);
    void sendLoverow(int);

};

#endif // PLAYLIST_H

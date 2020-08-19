#ifndef MYLOVE_H
#define MYLOVE_H

#include <QDialog>
#include<QTableWidgetItem>
#include<playlist.h>
#include<QFileInfoList>
#include<QMediaPlaylist>

namespace Ui {
class myLove;
}
static int i=0;
class myLove : public QDialog
{
    Q_OBJECT

public:
    explicit myLove(QWidget *parent = 0);
    ~myLove();
    Playlist *qplaylist;
    QFileInfoList playlists;
    QMediaPlaylist *playlist;

private slots:
    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void receiveRow(int receiverow);

    void on_pushButton_clicked();
private:
    Ui::myLove *ui;
    int temprow=-1;
       int receivepiece=-1;
       int piecenumber=0;
       void create();
       int piece[100];

   signals:
       void sendRow(int);
       void sendDelete(int);
};

#endif // MYLOVE_H

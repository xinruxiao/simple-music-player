#include "mylove.h"
#include "ui_mylove.h"
#include "playlist.h"
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QDir>

myLove::myLove(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myLove)
{
    ui->setupUi(this);
    setWindowTitle(tr("我喜欢的"));
    this->setWindowOpacity(0.85);
    this->setMaximumSize(360,469);
    this->setMinimumSize(360,469);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(100);

      create();

      QTableWidgetItem *newItem = new QTableWidgetItem;
      newItem->setText(newItem->text()+"");
      ui->tableWidget->setItem(0,0,newItem);


      ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
      ui->tableWidget->horizontalHeader()->resizeSection(0,200);    //设置列的宽度
      ui->tableWidget->horizontalHeader()->resizeSection(1,50);
      ui->tableWidget->horizontalHeader()->setCascadingSectionResizes(false);//
      ui->tableWidget->setShowGrid(false);  //设置不显示格子线
      ui->tableWidget->verticalHeader()->setVisible(false);  //设置垂直头不可见

      QStringList header;
      header<<tr("歌曲列表")<<tr("删除");
      ui->tableWidget->setHorizontalHeaderLabels(header);

      qplaylist=new Playlist;
      connect(qplaylist,SIGNAL(sendLoverow(int)),this,SLOT(receiveRow(int)));
}

myLove::~myLove()
{
    delete ui;
}

void myLove::on_tableWidget_itemClicked(QTableWidgetItem *item)
{


    int row=ui->tableWidget->row(item);
    int column=ui->tableWidget->column(item);

    /*双击播放列表中显示的歌曲*/
    if(temprow==row&&column==0)
    {
        emit sendRow(piece[row]);
    }
    temprow=row;

    /*点击，删除喜欢列表中该首歌曲*/
    if(column==1)
    {
        int m;
        for(m=row;m<i;++m)
            piece[m]=piece[m+1];
        --i;

        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(2);
        ui->tableWidget->setRowCount(i+1);

        for(int n=0;n<i;++n)
        {

            QTableWidgetItem *newItem = new QTableWidgetItem;
            newItem->setText(newItem->text()+playlists.at(piece[n]).baseName());
            ui->tableWidget->setItem(n,0,newItem);
            newItem = new QTableWidgetItem;
            newItem->setText(newItem->text()+"删除");
            ui->tableWidget->setItem(n,1,newItem);


            ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
            ui->tableWidget->horizontalHeader()->resizeSection(0,200);    //设置列的宽度
            ui->tableWidget->horizontalHeader()->resizeSection(1,50);
            ui->tableWidget->horizontalHeader()->setCascadingSectionResizes(false);//
            ui->tableWidget->setShowGrid(false);  //设置不显示格子线
            ui->tableWidget->verticalHeader()->setVisible(false);  //设置垂直头不可见
            QStringList header;
            header<<tr("歌曲列表")<<tr("删除");
            ui->tableWidget->setHorizontalHeaderLabels(header);
        }
    }
}

void myLove::receiveRow(int receiverow)
{

    receivepiece=receiverow;
    if(receivepiece!=-1)
    {
        playlist=new QMediaPlaylist;
        playlist->addMedia(QUrl::fromLocalFile(playlists.at(receivepiece).absoluteFilePath()));
        piece[piecenumber]=receivepiece;
        ++piecenumber;
        if(i==0)
            ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(2);
        ui->tableWidget->setRowCount(i+1);



        QTableWidgetItem *newItem = new QTableWidgetItem;
        newItem->setText(newItem->text()+playlists.at(receivepiece).baseName());
        ui->tableWidget->setItem(i,0,newItem);
        newItem = new QTableWidgetItem;
        newItem->setText(newItem->text()+"删除");
        ui->tableWidget->setItem(i,1,newItem);
        ++i;

        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
        ui->tableWidget->horizontalHeader()->resizeSection(0,200);    //设置列的宽度
        ui->tableWidget->horizontalHeader()->resizeSection(1,50);
        ui->tableWidget->horizontalHeader()->setCascadingSectionResizes(false);//
        ui->tableWidget->setShowGrid(false);  //设置不显示格子线
        ui->tableWidget->verticalHeader()->setVisible(false);  //设置垂直头不可见
        QStringList header;
        header<<tr("歌曲列表")<<tr("删除");
        ui->tableWidget->setHorizontalHeaderLabels(header);
    }

}

void myLove::create()
{
    QDir dir("E:/CloudMusic/");
    QStringList filters;
    filters << "*.mp3";
    dir.setNameFilters(filters);
    playlists=dir.entryInfoList(filters);
}

void myLove::on_pushButton_clicked()
{
    this->show();
    qplaylist->show();
}

#include "playlist.h"
#include "ui_playlist.h"
#include<QDir>
#include<QStringList>
#include<QString>
#include<QMediaPlaylist>
#include<QMediaPlayer>
#include<QProcess>
#include<QTableWidget>
#include<QAbstractItemView>
#include<QFrame>
Playlist::Playlist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Playlist)
{
    ui->setupUi(this);
    setWindowTitle(tr("播放列表"));
    this->setWindowOpacity(0.85);
    this->setMaximumSize(400,536);
    this->setMinimumSize(400,536);
    QObject::connect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),
                     this, SLOT(on_tableWidget_itemClicked(QTableWidgetItem *item)));


    build();
     create();

}

Playlist::~Playlist()
{
    delete ui;
}

void Playlist::on_tableWidget_itemClicked(QTableWidgetItem *item)
{

    /*实现双击播放*/
    int row=ui->tableWidget->row(item);
    int column=ui->tableWidget->column(item);
    if(tempRow==row&&column==1)
        emit sendRow(row);
    tempRow=row;

    /*歌曲从列表中移出*/
    if(column==2)
    {
        deleterow=row;
        emit sendDeleterow(deleterow);
        ui->tableWidget->clear();
         playlists.removeAt(row);
        create();
    }

    /*顶歌*/
     if(column==3)
     {
         toppiece=row;
         emit sendToppiece(toppiece);
         ui->tableWidget->clear();
         create();
     }

     /*收藏到myLove列表*/
     if(column==0)
         emit sendLoverow(row);
}
void Playlist::create()
{
    int row;

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(playlists.size());
    int size=playlists.size();

    if(toppiece==-1)
       {
           for(row=0;row<size;++row)
           {
               QTableWidgetItem *newItem = new QTableWidgetItem;
               newItem->setText(newItem->text()+playlists.at(row).baseName());
               ui->tableWidget->setItem(row,1,newItem);
           }
       }
       else
       {
           ui->tableWidget->clear();
           int temprow;
           if(Topflag==0)
           {
               for(row=1,temprow=0;temprow<size;++row,++temprow)
               {
                   if(temprow!=toppiece)
                   {
                       QTableWidgetItem *newItem = new QTableWidgetItem;
                       newItem->setText(newItem->text()+playlists.at(temprow).baseName());
                       ui->tableWidget->setItem(row,1,newItem);
                   }
                   else
                       --row;
               }
               QTableWidgetItem *newItem = new QTableWidgetItem;
               newItem->setText(newItem->text()+playlists.at(toppiece).baseName());
               ui->tableWidget->setItem(0,1,newItem);
               Topflag=1;
               tempToppiece=toppiece;
           }
           else
           {
               if(toppiece<tempToppiece)
               {
                   for(row=1,temprow=0;temprow<size;++row,++temprow)
                   {
                       if(temprow!=toppiece-1)
                       {
                           QTableWidgetItem *newItem = new QTableWidgetItem;
                           newItem->setText(newItem->text()+playlists.at(temprow).baseName());
                           ui->tableWidget->setItem(row,1,newItem);
                       }
                       else
                           --row;
                   }
                   QTableWidgetItem *newItem = new QTableWidgetItem;
                   newItem->setText(newItem->text()+playlists.at(toppiece-1).baseName());
                   ui->tableWidget->setItem(0,1,newItem);
               }
               else
               {
                   for(row=1,temprow=0;temprow<size;++row,++temprow)
                   {
                       if(temprow!=toppiece)
                       {
                           QTableWidgetItem *newItem = new QTableWidgetItem;
                           newItem->setText(newItem->text()+playlists.at(temprow).baseName());
                           ui->tableWidget->setItem(row,1,newItem);
                       }
                       else
                           --row;
                   }
                   QTableWidgetItem *newItem = new QTableWidgetItem;
                   newItem->setText(newItem->text()+playlists.at(toppiece).baseName());
                   ui->tableWidget->setItem(0,1,newItem);
               }
               tempToppiece=toppiece;
           }
       }
       for(row=0;row<size;++row)
       {
               QTableWidgetItem *newItem = new QTableWidgetItem;
               newItem->setText(newItem->text()+"LOVE");
               ui->tableWidget->setItem(row,0,newItem);
       }
       for(row=0;row<size;++row)
       {
               QTableWidgetItem *newItem = new QTableWidgetItem;
               newItem->setText(newItem->text()+"删除");
               ui->tableWidget->setItem(row,2,newItem);
       }
       for(row=0;row<size;++row)
       {
               QTableWidgetItem *newItem = new QTableWidgetItem;
               newItem->setText(newItem->text()+"顶歌");
               ui->tableWidget->setItem(row,3,newItem);
       }

       ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
       ui->tableWidget->horizontalHeader()->resizeSection(0,50);    //设置列的宽度
       ui->tableWidget->horizontalHeader()->resizeSection(1,200);
       ui->tableWidget->horizontalHeader()->resizeSection(2,50);
       ui->tableWidget->horizontalHeader()->resizeSection(3,50);
       ui->tableWidget->horizontalHeader()->setCascadingSectionResizes(false);//
       ui->tableWidget->setShowGrid(false);  //设置不显示格子线
       ui->tableWidget->verticalHeader()->setVisible(false);  //设置垂直头不可见
       QStringList header;
       header<<tr("喜欢")<<tr("歌曲列表")<<tr("删除")<<tr("顶歌");
       ui->tableWidget->setHorizontalHeaderLabels(header);
}

void Playlist::build()
{
    QDir dir("E:/CloudMusic/");
    QStringList filters;
    filters << "*.mp3";
    dir.setNameFilters(filters);
    playlists=dir.entryInfoList(filters);
}


#include "DoneWorks.h"
#include "ui_DoneWorks.h"

DoneWorks::DoneWorks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoneWorks)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
}

DoneWorks::~DoneWorks()
{
    delete ui;
}

void DoneWorks::initWorkUI()
{
    //完成列表--电影
    ui->listWidget_prod_movies->setViewMode(QListView::IconMode);
    ui->listWidget_prod_movies->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_movies->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_movies->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_movies->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_movies->horizontalScrollBar()->setDisabled(true);
    //完成列表--网络剧
    ui->listWidget_prod_netdrama->setViewMode(QListView::IconMode);
    ui->listWidget_prod_netdrama->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_netdrama->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_netdrama->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_netdrama->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_netdrama->horizontalScrollBar()->setDisabled(true);
    //完成列表--短视频
    ui->listWidget_prod_shortvideos->setViewMode(QListView::IconMode);
    ui->listWidget_prod_shortvideos->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_shortvideos->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_shortvideos->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_shortvideos->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_shortvideos->horizontalScrollBar()->setDisabled(true);
    //完成列表--中视频
    ui->listWidget_prod_midvideos->setViewMode(QListView::IconMode);
    ui->listWidget_prod_midvideos->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_midvideos->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_midvideos->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_midvideos->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_midvideos->horizontalScrollBar()->setDisabled(true);
    //完成列表--音乐
    ui->listWidget_prod_musics->setViewMode(QListView::IconMode);
    ui->listWidget_prod_musics->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_musics->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_musics->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_musics->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_musics->horizontalScrollBar()->setDisabled(true);
    //完成列表--图片
    ui->listWidget_prod_pictures->setViewMode(QListView::IconMode);
    ui->listWidget_prod_pictures->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_pictures->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_pictures->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_pictures->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_pictures->horizontalScrollBar()->setDisabled(true);


    //作品列表--左侧
    for(int i = 0; i<m_producelist.count();i++)
    {
        QListWidgetItem *item = new QListWidgetItem(m_producelist.at(i));
        item->setData(Qt::UserRole,m_datalist.at(i));
        item->setTextAlignment(Qt::AlignCenter);
        ui->listWidget_producelist->addItem(item);//添加列表
    }
}

void DoneWorks::handleSignalsAndSlots()
{
    //媒体列表
    connect(ui->listWidget_producelist,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        if(item->text() == QString(u8"电影"))
        {
            ui->stackedWidget_produce->setCurrentIndex(0);
            ui->listWidget_prod_movies->clear();
        }
        else if(item->text() == QString(u8"网络剧"))
        {
            ui->stackedWidget_produce->setCurrentIndex(1);
            ui->listWidget_prod_netdrama->clear();
        }
        else if(item->text() == QString(u8"短视频"))
        {
            ui->stackedWidget_produce->setCurrentIndex(2);
            ui->listWidget_prod_shortvideos->clear();
        }
        else if(item->text() == QString(u8"中视频"))
        {
            ui->stackedWidget_produce->setCurrentIndex(3);
            ui->listWidget_prod_midvideos->clear();
        }
        else if(item->text() == QString(u8"音乐"))
        {
            ui->stackedWidget_produce->setCurrentIndex(4);
            ui->listWidget_prod_musics->clear();
        }
        else if(item->text() == QString(u8"图片"))
        {
            ui->stackedWidget_produce->setCurrentIndex(5);
            ui->listWidget_prod_pictures->clear();
        }

        dataBase::getInstance()->creator_getdoneWorks(item->data(Qt::UserRole).toString());
    });

    connect(dataBase::getInstance(),&dataBase::sig_sendUserDoneWorks,this,&DoneWorks::slot_receivedData_findTypeResult);

}

void DoneWorks::setInstallEventer()
{
    ui->listWidget_producelist->installEventFilter(this);
}

void DoneWorks::slot_receivedData_findTypeResult(QVariant media)
{
        fileBody body = media.value<fileBody>();//通用类型转为专用类型
        qDebug() << QString(u8"已经上传完成的视频，要被创建新的ITEM信息如下:") << endl;
        qDebug() << "fnick" << body.fnick << endl;
        qDebug() << "furl"  << body.furl << endl;
        qDebug() << "fduration" << body.fduration << endl;
        qDebug() << "fcover" << body.fcover << endl;
        qDebug() << "fmedtype" << body.fmedtype << endl;
        qDebug() << "fmedtheme" << body.fmedtheme << endl;
        qDebug() << "fsize" << body.fsize << endl;

        QListWidgetItem *item = new QListWidgetItem(body.fnick);
        item->setData(Qt::UserRole,body.furl);
        FilesItem *itemWidget = new FilesItem(FILEEDIT::CANEDIT,body.furl,body.fsize,body.fcover);
        itemWidget->initFileItem(body);
        item->setSizeHint(DITEMSIZE);
        item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
        if(body.fmedtype == QString("movies"))
        {
            ui->listWidget_prod_movies->addItem(item);
            ui->listWidget_prod_movies->setItemWidget(item,itemWidget);
        }
        else if(body.fmedtype == QString("netdrama"))
        {
            ui->listWidget_prod_netdrama->addItem(item);
            ui->listWidget_prod_netdrama->setItemWidget(item,itemWidget);
        }
        else if(body.fmedtype == QString("shortvideos"))
        {
            ui->listWidget_prod_shortvideos->addItem(item);
            ui->listWidget_prod_shortvideos->setItemWidget(item,itemWidget);
        }
        else if(body.fmedtype == QString("midvideos"))
        {
            ui->listWidget_prod_midvideos->addItem(item);
            ui->listWidget_prod_midvideos->setItemWidget(item,itemWidget);
        }
        else if(body.fmedtype == QString("musics"))
        {
            ui->listWidget_prod_musics->addItem(item);
            ui->listWidget_prod_musics->setItemWidget(item,itemWidget);
        }
        else if(body.fmedtype == QString("pictures"))
        {
            ui->listWidget_prod_pictures->addItem(item);
            ui->listWidget_prod_pictures->setItemWidget(item,itemWidget);
        }

        //信号与槽函数
        //移除
        connect(itemWidget,&FilesItem::sig_sendItem_remove,[=](){
            itemWidget->disconnect();
            itemWidget->deleteLater();
            item->listWidget()->takeItem(item->listWidget()->row(item));
            delete item;
        });
        //播放
        connect(itemWidget,&FilesItem::sig_sendItem_play,[=](){
        MultipPlayer::getInstance()->show();
        MultipPlayer::getInstance()->slot_addTempPlaylist(666,QStringList{item->data(Qt::UserRole).toString()},item->text());
    //        qDebug() << QString(u8"接收到的播放地址：")<< item->data(Qt::UserRole).toString();
        });
}

bool DoneWorks::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_producelist && event->type() == QEvent::Enter)
    {
        setCursor(Qt::ArrowCursor);
    }
    return QWidget::eventFilter(watched,event);
}

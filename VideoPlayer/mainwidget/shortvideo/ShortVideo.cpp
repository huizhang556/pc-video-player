#include "ShortVideo.h"
#include "ui_ShortVideo.h"

ShortVideo::ShortVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShortVideo)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSLots();
}

ShortVideo::~ShortVideo()
{
    delete ui;
}

void ShortVideo::initWorkUI()
{
//    ui->stackedWidget_player->installEventFilter(this);
    ui->label_novideo->constructItem(":/images/bgpic/cusvideoitem2.png","://images/user/itemmark_vyp.png",QString(u8"6.6"),false,true,false);
    ui->pushButton_title->setText(QString(u8"热点资讯"));
    ui->pushButton_love->setIcon(QIcon("://images/user/default_woman00.png"));
    ui->pushButton_toPlayer->setToolTip(QString(u8"转到主播放器"));
    ui->pushButton_collect->setToolTip(QString(u8"收藏"));
    ui->pushButton_download->setToolTip(QString(u8"下载"));
    ui->pushButton_suggest->setToolTip(QString(u8"反馈"));
    ui->pushButton_collect->setCheckable(true);
    ui->pushButton_collect->setChecked(false);

    ui->listWidget_type->setFixedWidth(900);//固定900，不动态变化调整
    ui->listWidget_type->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_type->setViewMode(QListView::IconMode);
    ui->listWidget_type->setWrapping(false);
    ui->listWidget_type->setMovement(QListView::Static);
    ui->listWidget_type->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_type->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_type->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
    ui->listWidget_type->setOffset(180,0,7,0,3);
    ui->listWidget_type->setButtonControl(true);
    ui->listWidget_type->setAdjist(false);//不动态调节

    ui->listWidget_medialist->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_medialist->setViewMode(QListView::ListMode);
    ui->listWidget_medialist->setWrapping(false);
    ui->listWidget_medialist->setMovement(QListView::Static);
    ui->listWidget_medialist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_medialist->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->listWidget_medialist->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->stackedWidget_player->setCurrentWidget(ui->stackPage_novideo);

    slot_addSelectTypeToList(typelist);
}

void ShortVideo::handleSignalsAndSLots()
{
    //节目类型选择
    connect(ui->listWidget_type,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        qDebug() << item->text();
    });

    connect(ui->listWidget_medialist,&QListWidget::currentItemChanged,[=](QListWidgetItem *current,QListWidgetItem *previous)
    {
        if(previous != nullptr)
        {
            getListWidgetItemButton(previous,"pushButton_videoInfo")->setChecked(false);
        }
        if(current != nullptr)
        {
            getListWidgetItemButton(current,"pushButton_videoInfo")->setChecked(true);
            m_curMediaUrl = current->text();//url
            m_curMediaName = current->data(Qt::UserRole).toString();//介绍
            ui->widget_player->slot_receivePlayMediaFile(m_curMediaUrl,m_curMediaName);//URL+介绍
        }
    });

    //转到主 播放器(固定编号777)
    connect(ui->pushButton_toPlayer,&QPushButton::clicked,[=](){
        QString pos = QString::number(ui->widget_player->slot_player_pos());
        qDebug() <<QString(u8"当前播放点：%1").arg(pos);
        QUrlQuery query;
        query.addQueryItem(u8"url",m_curMediaUrl);
        query.addQueryItem(u8"nick",m_curMediaName);
        query.addQueryItem(u8"pos",pos);
        ui->widget_player->slot_stopPlayer();//停止mini播放器播放
        emit sig_sendToMainPlayer(777,QStringList{m_curMediaUrl},query);
        qDebug() << QString(u8"转到主 播放器");
    });

    //收藏
    connect(ui->pushButton_collect,&QPushButton::clicked,[=](bool checked){
//        qDebug() << QString(u8"收藏状态：")<<checked;
        ui->pushButton_collect->setChecked(checked);
    });

    //下载
    connect(ui->pushButton_download,&QPushButton::clicked,[=](){
        DownloadType::getInstance()->showDownloadForm(1,m_curMediaName,m_curMediaUrl);
    });

    //反馈
    connect(ui->pushButton_suggest,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"反馈");
    });

    //播放器下一首
    connect(ui->widget_player,&MiniPlayer::sig_player_next,[=](){
        if(ui->listWidget_medialist->currentRow() == ui->listWidget_medialist->count()-1)
        {
            ui->listWidget_medialist->setCurrentItem(ui->listWidget_medialist->item(0));
        }
        else
        {
            ui->listWidget_medialist->setCurrentItem(ui->listWidget_medialist->item(ui->listWidget_medialist->currentRow()+1));
        }
    });

    //播放器状态改变
    connect(ui->widget_player,&MiniPlayer::sig_player_status,[=](bool playing){
        if(playing)
        {
            ui->stackedWidget_player->setCurrentWidget(ui->stackPage_video);
        }
        else
        {
            ui->stackedWidget_player->setCurrentWidget(ui->stackPage_novideo);
        }
    });

    //非视频页播放视频
    connect(ui->label_novideo,&CusLabelItem::sig_sendPlayOn,[=](){
        ui->stackedWidget_player->setCurrentWidget(ui->stackPage_video);
        ui->widget_player->slot_player_on();//播放视频
    });

    //播放器---右键--下载
    connect(ui->widget_player,&MiniPlayer::sig_player_download,[=](){
        ui->pushButton_download->click();//模拟下载按钮
    });

    //播放器---右键--主播放器播放
    connect(ui->widget_player,&MiniPlayer::sig_player_toMainPlayer,[=](){
        ui->pushButton_toPlayer->click();//模拟下载按钮
    });

    //播放器---右键--视频信息
    connect(ui->widget_player,&MiniPlayer::sig_player_videoInfo,[=](){
        qDebug() << QString(u8"接收到显示视频信息请求！");
    });

    //播放器---右键--视频设置
    connect(ui->widget_player,&MiniPlayer::sig_player_videoSetting,[=](){
        qDebug() << QString(u8"接收到视频设置请求！");
    });
}

void ShortVideo::slot_addSelectTypeToList(const QStringList &typelist)
{
    foreach (const QString itenText, typelist)
    {
        QListWidgetItem *item = new QListWidgetItem(itenText);
        item->setSizeHint(QSize(180,75));
        ui->listWidget_type->addItem(item);
    }
    if(ui->listWidget_type->count() != 0)
        ui->listWidget_type->setCurrentRow(0);
}

bool ShortVideo::slot_addShortVideoItem(QVariant musicVariant)
{
    MusicData data = musicVariant.value<MusicData>();// 通用类型转为专用类型
    RecVideoItem *videoItem = new RecVideoItem(data.url,data.cover,data.duration,data.alias,data.uplove);
    QListWidgetItem *item = new QListWidgetItem(data.url);
    item->setSizeHint(videoItem->size());//留出来1px的边框
    item->setData(Qt::UserRole,data.alias);
    ui->listWidget_medialist->addItem(item);
    ui->listWidget_medialist->setItemWidget(item,videoItem);


    //信号与槽函数
    connect(videoItem,&RecVideoItem::sig_sendVideoUrl,[=](){
        ui->listWidget_medialist->setCurrentItem(item);//实现选中样式
    });
    return true;
}

bool ShortVideo::slot_addShortVideoItem(QString url, QString path, QString time, QString info, QString count)
{
    RecVideoItem *videoItem = new RecVideoItem(url,path,time,info,count);
    QListWidgetItem *item = new QListWidgetItem(url);
    item->setSizeHint(videoItem->size());//留出来1px的边框
    item->setData(Qt::UserRole,info);
    ui->listWidget_medialist->addItem(item);
    ui->listWidget_medialist->setItemWidget(item,videoItem);

    //信号与槽函数
    connect(videoItem,&RecVideoItem::sig_sendVideoUrl,[=](){
        ui->listWidget_medialist->setCurrentItem(item);//实现选中样式
    });
    return true;
}

void ShortVideo::slot_clearShortLists()
{
//    if(ui->listWidget_medialist->count() != 0)
//    ui->listWidget_medialist->clear();
}

bool ShortVideo::eventFilter(QObject *watched, QEvent *event)
{
//    if(watched == ui->stackedWidget_player)
//    {
//        if(event->type() == QEvent::Enter)
//        {
//            ui->widget_player->slot_mouseEnter();
//            qDebug() <<
//        }
//        else if(event->type() == QEvent::Leave)
//        {
//            ui->widget_player->slot_mouseLeave();
//        }
//    }
    return QWidget::eventFilter(watched,event);
}

QPushButton *ShortVideo::getListWidgetItemButton(QListWidgetItem *item, QString objname)
{
    QWidget* itemWidget = ui->listWidget_medialist->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QPushButton *itemBtn = itemWidget->findChild<QPushButton*>(objname);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemBtn)
        return itemBtn;
    }
}

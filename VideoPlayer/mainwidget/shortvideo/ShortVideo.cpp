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
    m_manager = new QNetworkAccessManager(this);
    ui->pushButton_themeflush->setIcon(QIcon(":/images/home/vtitle_switch.png"));
    ui->pushButton_themeflush->setText(QString(u8"换一换"));
//    ui->stackedWidget_player->installEventFilter(this);
    ui->label_novideo->constructItem(":/images/bgpic/cusvideoitem2.png","://images/user/itemmark_vyp.png",QString(u8"6.6"),false,true,false);
    ui->pushButton_title->setText(QString(u8"热点资讯"));
    ui->label_usrheader->setPixmap_(QPixmap(":/images/bgpic/dieji3.png"));
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
    ui->stackedWidget_dramalist->setCurrentIndex(0);

    //关注按钮
    ui->pushButton_love->setText(QString(u8"点赞关注+"));
    ui->pushButton_love->setCheckable(true);
    ui->pushButton_love->setEnabled(false);
    //收藏按钮
    ui->pushButton_collect->setCheckable(true);
    ui->pushButton_collect->setEnabled(false);

}

void ShortVideo::handleSignalsAndSLots()
{
    connect(m_manager,&QNetworkAccessManager::finished,this,&ShortVideo::slot_receivedUserHeader,Qt::UniqueConnection);

    //换一换
    connect(ui->pushButton_themeflush,&QPushButton::clicked,[=](){
        if(m_curTheme == ui->listWidget_type->currentItem()->text())//主题未改变
        {
            m_startpos += 10;
        }
        else
        {
            m_startpos = 0;
        }
        ui->listWidget_medialist->clear();
        emit sig_sendTheme(ui->listWidget_type->currentItem()->text(),m_startpos,10);//主题改变
    });

    //节目类型选择
    connect(ui->listWidget_type,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        qDebug() << QString(u8"当前查找主题：") << item->text();
        //数据库查询数据并展示
            ui->listWidget_medialist->clear();
            m_curTheme = item->text();
            m_startpos = 0;
            emit sig_sendTheme(item->text(),m_startpos,10);//主题改变
    });

    //手动选择item转到播放器
    connect(ui->listWidget_medialist,&QListWidget::currentItemChanged,[=](QListWidgetItem *current,QListWidgetItem *previous)
    {
        if(previous != nullptr)
        {
            getListWidgetItemButton(previous,"pushButton_videoInfo")->setChecked(false);
        }
        if(current != nullptr)
        {
            getListWidgetItemButton(current,"pushButton_videoInfo")->setChecked(true);
            m_curMediaId = current->data(Qt::UserRole+1).toInt();//介绍

            //设置当前媒体所属用户头像
            QUrlQuery query_url= dataBase::getInstance()->adv_getCurMediaUserInfo(m_curMediaId);
            slot_setCurMediaHeader(query_url.queryItemValue(u8"userhead"));

            m_curUserName = query_url.queryItemValue(u8"username");
            slot_setCurMediaUsrName(QString(u8"用户：") + m_curUserName);

            m_curUserId = query_url.queryItemValue(u8"userid");

            //设置收藏状态
            slot_setCurMediaColStatus(dataBase::getInstance()->getCurrentUserID(),m_curMediaId);

            //设置粉丝关注状态
            slot_setCurUserFansStatus(m_curUserId,dataBase::getInstance()->getCurrentUserID());

            qDebug() << QString(u8"短视频----------当前播放视频id:") << m_curMediaId;
            m_curMediaUrl = current->text();//url
            m_curMediaName = current->data(Qt::UserRole).toString();//介绍
            ui->widget_player->slot_receivePlayMediaFile(m_curMediaUrl,m_curMediaName);//URL+介绍
            dataBase::getInstance()->user_operate_setToWatch(m_curMediaId);//更新播放量
        }
    });

    //转到主 播放器(固定编号777)
    connect(ui->pushButton_toPlayer,&QPushButton::clicked,[=](){
        QString pos = QString::number(ui->widget_player->slot_player_pos());
        qDebug() <<QString(u8"当前播放点：%1").arg(pos);
        QUrlQuery query;
        query.addQueryItem(u8"id",QString::number(m_curMediaId));
        query.addQueryItem(u8"url",m_curMediaUrl);
        query.addQueryItem(u8"nick",m_curMediaName);
        query.addQueryItem(u8"pos",pos);
        ui->widget_player->slot_stopPlayer();//停止mini播放器播放
        emit sig_sendToMainPlayer(777,QStringList{m_curMediaUrl},query);
        qDebug() << QString(u8"转到主播放器");
    });



    //下载
    connect(ui->pushButton_download,&QPushButton::clicked,[=](){
        DownloadType::getInstance()->showDownloadForm(1,m_curMediaName,m_curMediaUrl);
    });

    //反馈
    connect(ui->pushButton_suggest,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"反馈");
    });

    //检测到媒体结束，自动播放下一首

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
        ui->widget_player->slot_player_on();//模拟点击播放视频
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

    //关注用户
    connect(ui->pushButton_love,&QPushButton::clicked,[=](bool checked){
        if(checked)
        {
            qDebug(u8"成为粉丝");
            bool ok = dataBase::getInstance()->user_operate_setToFollow(true,dataBase::getInstance()->getCurrentUserID(),m_curUserId);
            if(ok)
            {
                ui->pushButton_love->setText(QString(u8"已关注"));
            }
        }
        else
        {
            qDebug(u8"取消粉丝");
           bool ok = dataBase::getInstance()->user_operate_setToFollow(false,dataBase::getInstance()->getCurrentUserID(),m_curUserId);
            if(ok)
            {
                ui->pushButton_love->setText(QString(u8"点赞关注+"));
            }
        }

    });

    //收藏
    connect(ui->pushButton_collect,&QPushButton::clicked,[=](bool checked){
        if(checked)
        {
            qDebug(u8"收藏视频");
            dataBase::getInstance()->user_operate_setToUplove(true,dataBase::getInstance()->getCurrentUserID(),m_curUserId,m_curMediaId);
        }
        else
        {
            qDebug(u8"取消收藏视频");
            dataBase::getInstance()->user_operate_setToUplove(false,dataBase::getInstance()->getCurrentUserID(),m_curUserId,m_curMediaId);
        }
    });

    //点击跳转
    connect(ui->label_usrheader,&RoundLab::sig_clicked,[=](){
        emit sig_sendToUserInfo(m_curUserId);
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
    {
        ui->listWidget_type->setCurrentRow(0);
        m_curTheme = ui->listWidget_type->currentItem()->text();
    }
}

//重载函数1
bool ShortVideo::slot_addShortVideoItem(QVariant& musicVariant)
{
    MusicData data = musicVariant.value<MusicData>();// 通用类型转为专用类型
    RecVideoItem *videoItem = new RecVideoItem(data.url,data.cover,data.duration,data.alias,data.uplove);
    QListWidgetItem *item = new QListWidgetItem(data.url);
    item->setSizeHint(videoItem->size());//留出来1px的边框
    item->setData(Qt::UserRole,data.alias);
    item->setData(Qt::UserRole+1,data.id);
    ui->listWidget_medialist->addItem(item);
    ui->listWidget_medialist->setItemWidget(item,videoItem);

    //信号与槽函数
    connect(videoItem,&RecVideoItem::sig_sendVideoUrl,[=](){
        ui->listWidget_medialist->setCurrentItem(item);//实现选中样式
    });
    return true;
}

//重载函数2
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

void ShortVideo::slot_setCurThemeCounts(int num)
{
    if(num == 0)
    {
        setContentTips(QString(u8"暂无该类型资源！"));
        ui->label_blank->setPixmap(QPixmap(":/images/bgpic/nothing.png"));
        ui->label_blank->setScaledContents(true);
        ui->stackedWidget_dramalist->setCurrentWidget(ui->page_blank);
    }
    else if(num > 0)
    {
        setContentTips(QString(u8"资源正在加载中..."));
        ui->label_blank->setPixmap(QPixmap(":/images/bgpic/nothing.png"));
        ui->label_blank->setScaledContents(true);
        QTimer::singleShot(1500,0,[=](){
            ui->stackedWidget_dramalist->setCurrentWidget(ui->page_themevideo);
        });
    }
    else
    {
        ui->stackedWidget_dramalist->setCurrentWidget(ui->page_themevideo);
    }
}

void ShortVideo::slot_setVideoMediaType(const QStringList &list)
{
    ui->listWidget_type->clear();
    videoTypeList = list;
    slot_addSelectTypeToList(videoTypeList);
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

void ShortVideo::setContentTips(const QString &tips)
{
    ui->pushButton_tips->setText(tips);

}

void ShortVideo::setErrorStatusTips(const QString &tips)
{
    ui->label_logintips->setText(tips);
    QTimer::singleShot(2000,0,[=](){
        ui->label_logintips->clear();
    });
}

void ShortVideo::slot_setCurMediaHeader(const QString &headpic)
{
    qDebug() << QString(u8"mini接收到的用户头像连接：") << headpic;
    m_manager->get(QNetworkRequest(QUrl(headpic)));
}

void ShortVideo::slot_setCurMediaUsrName(const QString &usrname)
{
    ui->label_usrheader->setToolTip(usrname);
}

//设置粉丝关注状态
void ShortVideo::slot_setCurUserFansStatus(const QString &user_id, const QString &follow_id)
{
    if(!dataBase::getInstance()->getCurrentUserOnline() || dataBase::getInstance()->getCurrentUserID() ==  user_id)
    {
        ui->pushButton_love->setText(QString(u8"点赞关注+"));
        ui->pushButton_love->setChecked(false);
        ui->pushButton_love->setEnabled(false);
        setErrorStatusTips(QString(u8"您的账号暂未登录,请先登录您的账号~"));
        return;
    }
    else
    {
        ui->pushButton_love->setEnabled(true);
        bool isok = dataBase::getInstance()->user_operate_getFollow(user_id,follow_id);
        if(isok)
        {
            ui->pushButton_love->setText(QString(u8"已关注"));
            ui->pushButton_love->setChecked(true);
        }
        else
        {
            ui->pushButton_love->setText(QString(u8"点赞关注+"));
            ui->pushButton_love->setChecked(false);
        }
    }
}

//设置媒体收藏状态
void ShortVideo::slot_setCurMediaColStatus(const QString &user_id, const int media_id)
{
    if(!dataBase::getInstance()->getCurrentUserOnline())
    {
        ui->pushButton_collect->setChecked(false);
        ui->pushButton_collect->setEnabled(false);
        setErrorStatusTips(QString(u8"您的账号暂未登录,请先登录您的账号~"));
        return;
    }
    else
    {
        ui->pushButton_collect->setEnabled(true);
        bool isok = dataBase::getInstance()->user_operate_getUplove(user_id,media_id);
        if(isok)
        {
            ui->pushButton_collect->setChecked(true);
        }
        else
        {
            ui->pushButton_collect->setChecked(false);
        }
    }
}

void ShortVideo::slot_updateFansStatus()
{
    slot_setCurUserFansStatus(m_curUserId,dataBase::getInstance()->getCurrentUserID());
}

void ShortVideo::slot_receivedUserHeader(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        ui->label_usrheader->setPixmap_(pixmap);
        qDebug() <<QString::fromLocal8Bit("mini放器播当前媒体用户头网络图片设置成功！");
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("mini播放器播当前媒体用户头网络图片像请求错误：")<<reply->errorString();
        QPixmap pixmap(":/images/bgpic/dieji3.png");//默认图标
        ui->label_usrheader->setPixmap_(pixmap);
    }
}


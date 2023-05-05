#include "AdvDialog.h"
#include "ui_AdvDialog.h"

//类外初始化
AdvDialog* AdvDialog::m_pInstance = nullptr;

AdvDialog::AdvDialog(QWidget *parent) :
    QDialog(parent),
    m_curTheme(u8"搞笑"),
    ui(new Ui::AdvDialog)
{
    ui->setupUi(this);
    setFixedSize(678,360);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setModal(false);
    initWorkUI();
    handleSignalsAndSlots();
}

AdvDialog::~AdvDialog()
{
    delete ui;
    //删除创建的单例
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void AdvDialog::slot_receivedUserHeader(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        ui->label_header->setPixmap_(pixmap);
        ui->label_header->setScaledContents(true);
        qDebug() <<QString::fromLocal8Bit("广告部分网络头像请求图片设置成功！");
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("广告部分网络头像请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/user/default_woman00.png");//默认图标
        ui->label_header->setPixmap_(pixmap);
        ui->label_header->setScaledContents(true);
    }
}

void AdvDialog::slot_setUserHeader(const QString &userHeader)
{
    m_manager->get(QNetworkRequest(QUrl(userHeader)));
}

void AdvDialog::initWorkUI()
{
    m_manager = new QNetworkAccessManager(this);
    ui->stackedWidget_advswitch->setCurrentWidget(ui->page_next);
    //重播
    ui->toolButton_replay->installEventFilter(this);
    ui->toolButton_replay->setIcon(QIcon(":/images/advterise/adv_replay.png"));
    ui->toolButton_replay->setIconSize(QSize(26,26));
    ui->toolButton_replay->setText(QString(u8"重播"));
    ui->toolButton_replay->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //点赞
    ui->toolButton_like->installEventFilter(this);
    ui->toolButton_like->setIcon(QIcon(":/images/advterise/adv_like.png"));
    ui->toolButton_like->setIconSize(QSize(33,30));
    ui->toolButton_like->setText(QString(u8"点赞"));
    ui->toolButton_like->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //投币
    ui->toolButton_toubi->installEventFilter(this);
    ui->toolButton_toubi->setIcon(QIcon(":/images/advterise/adv_toubi.png"));
    ui->toolButton_toubi->setIconSize(QSize(30,30));
    ui->toolButton_toubi->setText(QString(u8"投币"));
    ui->toolButton_toubi->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //收藏
    ui->toolButton_collect->installEventFilter(this);
    ui->toolButton_collect->setIcon(QIcon(":/images/advterise/adv_collect.png"));
    ui->toolButton_collect->setIconSize(QSize(26,26));
    ui->toolButton_collect->setText(QString(u8"收藏"));
    ui->toolButton_collect->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //缓存
    ui->toolButton_cache->installEventFilter(this);
    ui->toolButton_cache->setIcon(QIcon(":/images/advterise/adv-cache.png"));
    ui->toolButton_cache->setIconSize(QSize(26,26));
    ui->toolButton_cache->setText(QString(u8"缓存"));
    ui->toolButton_cache->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //转发
    ui->toolButton_relay->installEventFilter(this);
    ui->toolButton_relay->setIcon(QIcon(":/images/advterise/adv_relay.png"));
    ui->toolButton_relay->setIconSize(QSize(26,26));
    ui->toolButton_relay->setText(QString(u8"转发"));
    ui->toolButton_relay->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //列表属性设置
    //上传列表
    ui->listWidget_userlist->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_userlist->setViewMode(QListView::IconMode);
    ui->listWidget_userlist->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_userlist->setResizeMode(QListWidget::Adjust);
    ui->listWidget_userlist->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_userlist->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_userlist->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_userlist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_userlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_userlist->setSelectionMode(QAbstractItemView::SingleSelection);//设置选择模式为单选
}

void AdvDialog::handleSignalsAndSlots()
{
    connect(m_manager,&QNetworkAccessManager::finished,this,&AdvDialog::slot_receivedUserHeader,Qt::UniqueConnection);
    //重播
    connect(ui->toolButton_replay,&QPushButton::clicked,[=](){
        m_curPlayList.clear();
        m_curPlayList = QStringList{m_curMediaUrl};
        m_curQurlQuery.clear();
        m_curQurlQuery.addQueryItem(u8"id",QString::number(m_media_id));
        m_curQurlQuery.addQueryItem(u8"url",m_curMediaUrl);
        m_curQurlQuery.addQueryItem(u8"nick",m_curMedialias);
        m_curQurlQuery.addQueryItem(u8"pos",u8"0");
        emit sig_play_continue(666,QStringList{m_curMediaUrl},m_curQurlQuery);
        this->hide();
    });
}

AdvDialog *AdvDialog::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new AdvDialog();
    }
    return m_pInstance;
}

void AdvDialog::exec_(POPTYPE type, const int media_id)
{
    qDebug() << QString(u8"--------------广告界面接收到的当前媒体ID:") << media_id;
    m_curType = type;
    slot_getCurUserInfo(media_id);//获取用户相关信息
    //更新头像、名称、点赞数、等等
    slot_setUserHeader(m_curHeader);
    slot_setUserName(m_curUserName);
    qDebug() << QString(u8"即将要请求的4个推荐视频的主题：%1 起始点：%2 ").arg(m_curTheme).arg(m_startpos);
    QList<QVariant> medias = dataBase::getInstance()->adv_getNext4Medais(m_curTheme,m_startpos,4);
    qDebug() << QString(u8"广告请求到的数量：") << medias.count();

    if(medias.count() != 0)
    {
        slot_addItemTo_ContinueNextList(medias);
    }
    //延时出现，让数据先加载出来
    QTimer::singleShot(0,0,[=](){
        this->raise();
        this->show();
    });

//    switch (type)
//    {
//    case T_NEXTMEDIA:
//    {
//    }
//        break;
//    case T_BREAKMEDIA:
//    {
//    }
//        break;
//    case T_OTHEREDIA:
//    {
//    }
//        break;
//    case T_UNKNOW:
//    {
//    }
//        break;
//    default:
//        break;
    //    }
}

void AdvDialog::hide_()
{
    this->blockSignals(true);//停止一切信号发射
    this->hide();
}

void AdvDialog::slot_setUserName(const QString& userName)
{
    ui->pushButton_name->setText(userName);
}

void AdvDialog::slot_getCurUserInfo(const int media_id)
{
    QUrlQuery media_info = dataBase::getInstance()->adv_getCurMediaUserInfo(media_id);
    if(!media_info.isEmpty())
    {
        m_media_id      = media_id;
        m_curUserName   = media_info.queryItemValue(u8"username");
        m_curHeader     = media_info.queryItemValue(u8"userhead");
        m_curUserId     = media_info.queryItemValue(u8"userid");
        m_curMediaUrl   = media_info.queryItemValue(u8"url");
        m_curMedialias  = media_info.queryItemValue(u8"alias");
        QString theme   = media_info.queryItemValue(u8"theme");

        qDebug() << QString(u8"--------广告接收到当前播放完毕的视频信息：--------") << endl
                 << QString(u8"媒体ID:") << m_media_id << endl
                 << QString(u8"所属用户ID:") << m_curUserId << endl
                 << QString(u8"媒体用户名称:") << m_curUserName << endl
                 << QString(u8"媒体所属主题:") << theme << endl
                 << QString(u8"媒体URL:") << m_curMediaUrl << endl
                 << QString(u8"媒体ALIAS:") << m_curMedialias << endl
                 << QString(u8"媒体用户头像:") << m_curHeader << endl;

        if(m_curTheme == theme)//本次请求主题相同
        {
            m_startpos++;
            qDebug() <<QString(u8"请求主题相同");
        }
        else
        {
            m_startpos = 1;//不同主题加载从0开始
            qDebug() <<QString(u8"请求主题不同");
        }
        m_curTheme = theme;
    }
    else
        {
        qDebug() << QString(u8"广告界面接收到的当前视频用户信息为空！");
    }
}

void AdvDialog::slot_addItemTo_ContinueNextList(QList<QVariant> &medias)
{
    ui->listWidget_userlist->clear();//不管请求到没请求到，都清空推荐列表。
    for(int i = 0; i < medias.count(); i++)
    {
        MusicData advdata = medias.at(i).value<MusicData>();// 通用类型转为专用类型
        AdvterItem *itemWidget = nullptr;
        if(i == 0 && m_curType == P_NEXTMEDIA)
        {

            itemWidget = new AdvterItem(ADVTYPE::ADV_CONTINUE,advdata.url,advdata.cover,advdata.duration,advdata.alias,advdata.uplove);
        }
        else
        {
            itemWidget = new AdvterItem(ADVTYPE::ADV_NOCONTINUE,advdata.url,advdata.cover,advdata.duration,advdata.alias,advdata.uplove);
        }
        QListWidgetItem *item = new QListWidgetItem(advdata.url);
        item->setData(Qt::UserRole,advdata.id);//介绍
        item->setSizeHint(QSize(167,195));
        ui->listWidget_userlist->addItem(item);
        ui->listWidget_userlist->setItemWidget(item,itemWidget);

        //信号与槽函数
        connect(itemWidget,&AdvterItem::sig_item_continue,[=](QString url){
            slot_getCurUserInfo(advdata.id);//获取视频相关信息，并更新使用拥有者用户信息
            QUrlQuery query;
            query.addQueryItem(u8"id",QString::number(advdata.id));
            query.addQueryItem(u8"url",m_curMediaUrl);
            query.addQueryItem(u8"nick",m_curMedialias);
            query.addQueryItem(u8"pos",u8"0");
            m_curQurlQuery.clear();
            m_curQurlQuery = query;
            emit sig_play_continue(666,QStringList{m_curMediaUrl},m_curQurlQuery);
            qDebug() << QString::fromLocal8Bit("已发送临时播放连接url:%1 ,NICK:%2").arg(m_curMediaUrl).arg(m_curMedialias);
            this->hide();
        });
    }
}

bool AdvDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->toolButton_replay)
    {
        if(event->type() == QEvent::Enter)
        {

        }
        else if(event->type() == QEvent::Leave)
        {

        }
    }

    if(watched == ui->toolButton_replay)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->toolButton_replay->setIconSize(QSize(30,30));
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->toolButton_replay->setIconSize(QSize(26,26));
        }
    }

    if(watched == ui->toolButton_like)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->toolButton_like->setIconSize(QSize(35,32));
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->toolButton_like->setIconSize(QSize(33,30));
        }
    }

    if(watched == ui->toolButton_toubi)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->toolButton_toubi->setIconSize(QSize(32,32));
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->toolButton_toubi->setIconSize(QSize(30,30));
        }
    }

    if(watched == ui->toolButton_collect)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->toolButton_collect->setIconSize(QSize(30,30));
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->toolButton_collect->setIconSize(QSize(26,26));
        }
    }

    if(watched == ui->toolButton_cache)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->toolButton_cache->setIconSize(QSize(30,30));
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->toolButton_cache->setIconSize(QSize(26,26));
        }
    }

    if(watched == ui->toolButton_relay)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->toolButton_relay->setIconSize(QSize(30,30));
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->toolButton_relay->setIconSize(QSize(26,26));
        }
    }
    return QDialog::eventFilter(watched,event);
}

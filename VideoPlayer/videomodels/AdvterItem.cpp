#include "AdvterItem.h"
#include "ui_AdvterItem.h"

AdvterItem::AdvterItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvterItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

AdvterItem::AdvterItem(ADVTYPE type, const QString &url, const QString &cover, const QString &duration, const QString &intro,const QString &like, QWidget *parent):
    QWidget(parent),
    m_type(type),
    m_url(url),
    m_cover(cover),
    m_duration(duration),
    m_intro(intro),
    m_like(like),
    ui(new Ui::AdvterItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setItem_type();
    setItem_cover();
    setItemIntro();
    setItem_duration();
    setItemLike();
}

AdvterItem::~AdvterItem()
{
    delete ui;
}

void AdvterItem::initWorkUI()
{
    ui->label_cover->installEventFilter(this);

    m_manager = new QNetworkAccessManager(this);
    ui->label_intro->setWordWrap(true);
    ui->pushButton_playcount->setIcon(QIcon(":/images/advterise/adv_playcount.png"));
    ui->pushButton_playcount->setIconSize(QSize(20,30));
    ui->pushButton_comcount->setIcon(QIcon(":/images/advterise/adv_comcount.png"));
    ui->pushButton_comcount->setIconSize(QSize(17,15));
    ui->pushButton_comcount->setText(QString(u8"7.7万"));
    m_timer = new QTimer(this);
}

void AdvterItem::handleSignalsAndSlots()
{

    connect(m_manager,&QNetworkAccessManager::finished,this,&AdvterItem::slot_receiveMediaCover,Qt::UniqueConnection);
    connect(m_timer,&QTimer::timeout,[=](){
        if(time-- < 1)
        {
            ui->label_cover->setContinuePlay("");
            ui->label_cover->setPlayButtonCtl(true);
            m_timer->stop();
            emit sig_item_continue(m_url);//倒计时完成，发送信号
        }
        else
        {
            ui->label_cover->setCountDown(QString::number(time));
        }
    });

    //点击取消，取消定时器
    connect(ui->label_cover,&AdvCoverLab::sig_cancel,[=](){
        if(m_timer->isActive())
        {
            m_timer->stop();
            qDebug() << QString(u8"倒计时已取消");
        }
    });

    //点击播放其他视频，取消定时器
    connect(ui->label_cover,&AdvCoverLab::sig_play,[=](){
        if(m_timer->isActive())
        {
            m_timer->stop();
            qDebug() << QString(u8"倒计时已取消");
        }
        emit    sig_item_continue(m_url);//播放非目前媒体
    });
}

void AdvterItem::setItem_type()
{
    if(m_type == ADVTYPE::ADV_CONTINUE)
    {
        ui->label_cover->setContinuePlay(QString(u8"取消连播"));
        ui->label_cover->setPlayButtonCtl(false);
        //启动定时器
        m_timer->start(1000);
    }
    else if(m_type == ADVTYPE::ADV_NOCONTINUE)
    {
        ui->label_cover->setContinuePlay(QString(u8""));
        ui->label_cover->setPlayButtonCtl(true);
    }
    else
    {
        ui->label_cover->setContinuePlay(QString(u8""));
        ui->label_cover->setPlayButtonCtl(true);
    }
}


void AdvterItem::setItem_cover()
{
    m_manager->get(QNetworkRequest(QUrl(m_cover)));
}

void AdvterItem::setItemIntro()
{
    ui->label_intro->setText(m_intro);
}

void AdvterItem::setItem_duration()
{
    ui->label_cover->setDuration(m_duration);
}

void AdvterItem::setItemLike()
{
    ui->pushButton_playcount->setText(m_like);
}

bool AdvterItem::eventFilter(QObject *watched, QEvent *event)
{
//    if(watched == ui->label_cover && event->type() == QEvent::MouseButtonPress && m_clicked)
//    {
//        emit sig_item_continue(m_url);
//        m_clicked = true;
//    }
    return QWidget::eventFilter(watched,event);
}

void AdvterItem::slot_receiveMediaCover(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        ui->label_cover->setPixmap(pixmap);
        ui->label_cover->setScaledContents(true);//内容自适应
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/status/video_pixfaild.png");
        ui->label_cover->setPixmap(pixmap);
        ui->label_cover->setScaledContents(true);//内容自适应
    }
}

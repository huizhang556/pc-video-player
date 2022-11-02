#include "RecVideoItem.h"
#include "ui_RecVideoItem.h"

#include <QFontMetrics>
#include <QPixmap>
#include <QDebug>

RecVideoItem::RecVideoItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecVideoItem)
{
    ui->setupUi(this);
    this->setFixedHeight(85);
    this->setFixedWidth(260);
    handleSignalsAndSlots();
    manager = new QNetworkAccessManager(this);
    ui->label_videoPic->installEventFilter(this);
    ui->pushButton_videoInfo->setCheckable(true);
    ui->pushButton_videoInfo->setChecked(false);

    ui->pushButton_playAmount->setIcon(QIcon("://images/icon/recvideo_amount.png"));
}

RecVideoItem::RecVideoItem(const QString &url, const QString& path, const QString time, QString info, QString count, QWidget *parent) :
    QWidget(parent),
    m_videoUrl(url),
    m_picPath(path),
    m_picTime(time),
    m_picInfo(info),
    m_picCount(count),
    ui(new Ui::RecVideoItem)
{
    ui->setupUi(this);
    this->setFixedHeight(85);
    this->setFixedWidth(250);
    manager = new QNetworkAccessManager(this);
    handleSignalsAndSlots();
    ui->label_videoPic->installEventFilter(this);//获取点击事件
    ui->pushButton_videoInfo->setCheckable(true);
    ui->pushButton_videoInfo->setChecked(false);

    ui->pushButton_playAmount->setIcon(QIcon("://images/icon/recvideo_amount.png"));
    setVideoPicture(m_picPath);
    setVideoTime(m_picTime);
    setVideoText(m_picInfo);
    setVideoUpvoye(m_picCount);
}

RecVideoItem::~RecVideoItem()
{
    delete ui;
}

void RecVideoItem::handleSignalsAndSlots()
{
    //点击 信息部分 获取播放连接
    connect(ui->pushButton_videoInfo,&QPushButton::clicked,[=](){emit sig_sendVideoUrl();});
    //点击 播放部分 获取播放连接
    connect(ui->pushButton_play,&QPushButton::clicked,[=](){emit sig_sendVideoUrl();});
}

void RecVideoItem::setVideoPicture(const QString path)
{
//    QPixmap pix(path);
//    pix.scaled(ui->label_videoPic->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    manager->get(QNetworkRequest(QUrl(path)));
    //获取网络图片(注意：使用的是manager的finished信号)
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_replyFinished(QNetworkReply*)));
}

void RecVideoItem::setItemPicture(const QString path)
{
    ui->label_videoPic->setPixmap(QPixmap(path));
    ui->label_videoPic->setScaledContents(true);
}

void RecVideoItem::setVideoTime(const QString &time)
{
    ui->label_videoTime->setText(time);
}

void RecVideoItem::setVideoText(QString &info)
{
    if(info.length() > 10)
    {
        info = info.insert(10,"\n");
    }
    QFont font;
    font.setPixelSize(10);
    QFontMetrics fontMetric = QFontMetrics(font);
    QString text = fontMetric.elidedText(info,Qt::ElideRight,190,0);//19个字宽以后，省略为...(10x19，字号x字数)
    ui->pushButton_videoInfo->setText(text);
}

void RecVideoItem::setVideoUpvoye(const QString &count)
{
    ui->pushButton_playAmount->setText(count);
}

void RecVideoItem::slot_replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        ui->label_videoPic->setPixmap(pixmap);
        ui->label_videoPic->setScaledContents(true);//内容自适应
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/icon/createhover.png");
        ui->label_videoPic->setPixmap(pixmap);
        ui->label_videoPic->setScaledContents(true);//内容自适应
    }
}


bool RecVideoItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label_videoPic)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            emit sig_sendVideoUrl();
        }
    }
    return QWidget::eventFilter(watched,event);

}

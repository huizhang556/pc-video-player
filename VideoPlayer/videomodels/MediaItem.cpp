#include "MediaItem.h"
#include "ui_MediaItem.h"
#include <QDebug>

MediaItem::MediaItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalAndSlots();
}

MediaItem::MediaItem(const QString &mediaurl, const QString &icon, const QString &mediaName, bool islove, QWidget *parent):
    QWidget(parent),
    m_mediaUrl(mediaurl),
    m_mediaIcon(icon),
    m_mediaName(mediaName),
    m_isLove(islove),
    ui(new Ui::MediaItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalAndSlots();

    setMedia_icon();
    setMedia_name();
    setMedia_islove();
}

MediaItem::~MediaItem()
{
    delete ui;
}

void MediaItem::initWorkUI()
{
    ui->pushButton_collect->setCheckable(true);
    ui->stackedWidget_control->setCurrentIndex(0);
    ui->pushButton_mediaName->setAttribute(Qt::WA_TransparentForMouseEvents,true);
}

void MediaItem::handleSignalAndSlots()
{
    //收藏按钮
    connect(ui->pushButton_collect,&QPushButton::clicked,[=](){
        m_isLove = !m_isLove;
        emit sig_media_collect(m_isLove);
        setMedia_islove();
        qDebug() <<QString(u8"选中状态：")<<m_isLove;
    });

    //删除按钮
    connect(ui->pushButton_delete,&QPushButton::clicked,[=](){
        emit sig_media_delete();
        qDebug() <<QString(u8"删除：")<<m_mediaName;
    });

    //下载按钮
    connect(ui->pushButton_download,&QPushButton::clicked,[=](){
        emit sig_media_download();
        qDebug() <<QString(u8"下载：")<<m_mediaName;
    });
}


void MediaItem::setMedia_icon()
{
    ui->label_mediaIcon->setPixmap(QPixmap(m_mediaIcon));
    ui->label_mediaIcon->setScaledContents(true);
}

void MediaItem::setMedia_name()
{

    QFont font;
    font.setPixelSize(10);
    QFontMetrics fontMetric = QFontMetrics(font);
    QString text = fontMetric.elidedText(m_mediaName,Qt::ElideRight,120,0);//12个字宽以后，省略为...(10x12，字号x字数)
    ui->pushButton_mediaName->setText(text);
//    ui->pushButton_mediaName->setToolTip(m_mediaName);//设置鼠标穿透后，tooltip失效
}

void MediaItem::setMedia_islove()
{
    ui->pushButton_collect->setChecked(m_isLove);
}

const QString MediaItem::getMedia_url()
{
    return m_mediaUrl;
}

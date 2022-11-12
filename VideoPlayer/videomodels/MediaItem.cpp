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


MediaItem::MediaItem(MEDTYPE type, const QString &mediaurl, const QString &icon, const QString &mediaName, bool islove, const QString &mediaDuration, QWidget *parent):
    QWidget(parent),
    m_mediaType(type),
    m_mediaUrl(mediaurl),
    m_mediaIcon(icon),
    m_mediaName(mediaName),
    m_mediaDuration(mediaDuration),
    m_isLove(islove),
    ui(new Ui::MediaItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalAndSlots();

    setMedia_type();
    setMedia_icon();
    setMedia_name();
    setMedia_islove();
    setMedia_duration();
}

MediaItem::~MediaItem()
{
    delete ui;
}

void MediaItem::initWorkUI()
{
    ui->pushButton_collect->setCheckable(true);
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

void MediaItem::setMediaTypeStackPage(MEDTYPE type)
{
    switch (type)
    {
        case MEDTYPE::MED_NORMAL:
        {
        ui->pushButton_more->hide();
        ui->stackedWidget_control->setCurrentWidget(ui->page1);
        qDebug() << QString(u8"item--》为正常item");
        }
            break;
        case MEDTYPE::MED_COLLECT:
        {
        ui->pushButton_delete->hide();
        ui->stackedWidget_control->setCurrentWidget(ui->page1);
        qDebug() << QString(u8"item--》为收藏item");
        }
            break;
        case MEDTYPE::MED_HISTORY:
        {
        ui->stackedWidget_control->setCurrentWidget(ui->page2);
        qDebug() << QString(u8"item--》为历史item");
        }
            break;
    default:
        break;
    }
}


void MediaItem::setMedia_icon()
{
    ui->label_mediaIcon->setPixmap(QPixmap(m_mediaIcon));
    ui->label_mediaIcon->setScaledContents(true);
}

void MediaItem::setMedia_name()
{

    QFont font = ui->pushButton_mediaName->font();
    font.setPixelSize(18);
    ui->pushButton_mediaName->setFont(font);
    QFontMetrics fontMetric(font);
    int pxWidth = fontMetric.width(m_mediaName);
    if(pxWidth > ui->pushButton_mediaName->width())
    {
        QString subStr = fontMetric.elidedText(m_mediaName, Qt::ElideRight, ui->pushButton_mediaName->width()+40);
        ui->pushButton_mediaName->setText(subStr);
    }
    else
    {
    ui->pushButton_mediaName->setText(m_mediaName);
    }
}

void MediaItem::setMedia_islove()
{
    ui->pushButton_collect->setChecked(m_isLove);
}

void MediaItem::setMedia_duration()
{
    ui->pushButton_duration->setText(m_mediaDuration);
}

const QString MediaItem::getMedia_url()
{
    return m_mediaUrl;
}

void MediaItem::setMedia_type()
{
    switch (m_mediaType)
    {
        case MEDTYPE::MED_NORMAL:
        {
        ui->pushButton_more->hide();
        ui->stackedWidget_control->setCurrentWidget(ui->page1);
        qDebug() << QString(u8"item为正常item");
        }
            break;
        case MEDTYPE::MED_COLLECT:
        {
        ui->pushButton_delete->hide();
        ui->stackedWidget_control->setCurrentWidget(ui->page1);
        qDebug() << QString(u8"item为收藏item");
        }
            break;
        case MEDTYPE::MED_HISTORY:
        {
        ui->pushButton_collect->hide();
        ui->pushButton_delete->hide();
        ui->pushButton_download->hide();
        ui->stackedWidget_control->setCurrentWidget(ui->page2);
        qDebug() << QString(u8"item为历史item");
        }
            break;
    default:
        break;
    }
}

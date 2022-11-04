#include "SongItemForm.h"
#include "ui_SongItemForm.h"
#include "fileshandle/DownloadType.h"
#include <QFontMetrics>
#include <QDebug>

SongItemForm::SongItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SongItemForm)
{
    ui->setupUi(this);
}

SongItemForm::SongItemForm(const QString &num, const QString &son_name, bool vip, bool col, const QString &songer, const QString &album, const QString &quality, QWidget *parent) :
    QWidget(parent),
    m_number(num),
    m_songName(son_name),
    m_vip(vip),
    m_colStatus(col),
    m_songerName(songer),
    m_album(album),
    m_quality(quality),
    ui(new Ui::SongItemForm)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

SongItemForm::~SongItemForm()
{
    delete ui;
}

void SongItemForm::initWorkUI()
{
    ui->pushButton_son_collect->setFixedSize(18,18);
    ui->pushButton_son_collect->setCheckable(true);
    ui->pushButton_son_download->setFixedSize(21,21);
    ui->pushButton_son_delete->setFixedSize(21,21);
    ui->pushButton_son_more->setFixedSize(21,21);
    ui->pushButton_son_mv->setFixedSize(21,21);

    ui->pushButton_son_collect->setToolTip(QString(u8"收藏"));
    ui->pushButton_son_download->setToolTip(QString(u8"下载"));
    ui->pushButton_son_delete->setToolTip(QString(u8"删除"));
    ui->pushButton_son_more->setToolTip(QString(u8"更多"));
    ui->pushButton_son_mv->setToolTip(QString(u8"MV"));

    setItemNumber(addPrefixNum(m_number));
    setItemSongNameAndVip(m_songName,m_vip);
    setItemSongCollectStatus(m_colStatus);
    setItemSongSonger(m_songerName);
    setItemSongAlbum(m_album);
    setItemSongQuality(m_quality);
}

void SongItemForm::handleSignalsAndSlots()
{
    //播放按钮
    connect(ui->pushButton_son_name,&QPushButton::clicked,[=](){
        emit sig_son_playbtn_clicked(ui->label_order->text().toInt());
        qDebug() <<  ui->pushButton_son_name->objectName();
        qDebug() << "clicked playbtn" << ui->label_order->text().toInt();
        qDebug() << ui->pushButton_son_name->parentWidget()->parentWidget()->parentWidget()->objectName();
    });

    //MV播放按钮
    connect(ui->pushButton_son_mv,&QPushButton::clicked,[=](){
        emit sig_son_mvbtn_clicked(ui->label_order->text().toInt());
        qDebug() << "clicked MVbtn" << ui->label_order->text().toInt();
        qDebug() << ui->pushButton_son_mv->parentWidget()->parentWidget()->parentWidget()->objectName();
    });
    //收藏按钮
    connect(ui->pushButton_son_collect,&QPushButton::clicked,[=](){
        emit sig_son_collectbtn_clicked(ui->label_order->text().toInt());
        qDebug() << "clicked collectbtn" << ui->label_order->text().toInt();
        if(m_colStatus)//取反操作
        {
           ui->pushButton_son_collect->setChecked(false);
           m_colStatus = false;
        }
        else
        {
           ui->pushButton_son_collect->setChecked(true);
           m_colStatus = true;
        }
    });
    //下载按钮
    connect(ui->pushButton_son_download,&QPushButton::clicked,[=](){
        emit sig_son_downloadbtn_clicked(ui->label_order->text().toInt());
        qDebug() << "clicked downloadbtn"<< ui->label_order->text().toInt();
        qDebug() << ui->pushButton_son_download->parentWidget()->parentWidget()->parentWidget()->objectName();
        DownloadType::getInstance()->showDownloadForm(0,m_songName);
    });
    //删除按钮
    connect(ui->pushButton_son_delete,&QPushButton::clicked,[=](){
        emit sig_son_deletebtn_clicked(ui->label_order->text().toInt());
        qDebug() << "clicked deletebtn"<< ui->label_order->text().toInt();
        qDebug() << ui->pushButton_son_delete->parentWidget()->parentWidget()->parentWidget()->objectName();
    });
    //更多信息按钮
    connect(ui->pushButton_son_more,&QPushButton::clicked,[=](){
        emit sig_son_morebtn_clicked(ui->label_order->text().toInt());
        qDebug() << "clicked morebtn"<< ui->label_order->text().toInt();
        qDebug() << ui->pushButton_son_more->parentWidget()->parentWidget()->parentWidget()->objectName();
    });
    //音质按钮
    connect(ui->pushButton_yinzhi,&QPushButton::clicked,[=](){
        emit sig_son_qualityBtn_clicked(ui->label_order->text().toInt());
        qDebug() << "clicked qualitybtn"<< ui->label_order->text().toInt();
        qDebug() << ui->pushButton_yinzhi->parentWidget()->parentWidget()->objectName();
    });
}

void SongItemForm::setInstallEventFilter()
{

}

QString SongItemForm::addPrefixNum(QString num)
{
    if(num.length() == 1)
    {
        return QString::fromLocal8Bit("00")+num;
    }
    else if(num.length() == 2)
    {
        return QString::fromLocal8Bit("0")+num;
    }
    else
    {
        return num;
    }
}


void SongItemForm::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
//    ui->frame_make->show();
}

void SongItemForm::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
//    ui->frame_make->hide();
}

void SongItemForm::setItemNumber(const QString &num)
{
    ui->label_order->setText(addPrefixNum(num));
}

void SongItemForm::setItemSongNameAndVip(const QString &name, bool vip)
{
    ui->pushButton_son_name->setLayoutDirection(Qt::RightToLeft);//图标在右
    QFontMetrics fontMetric(ui->pushButton_son_name->font());
    QString t_text = fontMetric.elidedText(name,Qt::ElideRight,ui->pushButton_son_name->width()-40);
    ui->pushButton_son_name->setText(t_text);
    ui->pushButton_son_name->setToolTip(name);
    if(vip)
    {
        ui->pushButton_son_name->setIcon(QIcon("://images/home/file_music_vip.png"));
    }
}

void SongItemForm::setItemSongCollectStatus(bool collect)
{
    if(collect)//收藏状态显示红心
    {
        ui->pushButton_son_collect->setChecked(true);
        m_colStatus = true;
    }
    else//未收藏状态显示非红心
    {
        ui->pushButton_son_collect->setChecked(false);
        m_colStatus = false;
    }
}

void SongItemForm::setItemSongSonger(const QString &songer)
{
    QFontMetrics fontMetric(ui->pushButton_songer->font());
    QString t_text = fontMetric.elidedText(songer,Qt::ElideRight,ui->pushButton_songer->width());
    ui->pushButton_songer->setText(t_text);
    ui->pushButton_songer->setToolTip(songer);
}

void SongItemForm::setItemSongAlbum(const QString &album)
{
    QFontMetrics fontMetric(ui->pushButton_zhuanji->font());
    QString t_text = fontMetric.elidedText(album,Qt::ElideRight,ui->pushButton_zhuanji->width());
    ui->pushButton_zhuanji->setText(t_text);
    ui->pushButton_zhuanji->setToolTip(album);
}

void SongItemForm::setItemSongQuality(const QString &quality)
{
    ui->pushButton_yinzhi->setText(quality);
}


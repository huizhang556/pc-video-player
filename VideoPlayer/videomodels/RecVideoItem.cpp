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
    this->setFixedHeight(90);
    this->setFixedWidth(250);

    ui->label_video->installEventFilter(this);
    ui->label_video->hide();
    ui->pushButton_videoInfo->setCheckable(true);
    ui->pushButton_videoInfo->setChecked(false);

    ui->pushButton_playAmount->setIcon(QIcon("://images/icon/recvideo_amount.png"));
}

RecVideoItem::RecVideoItem(const QString& path, const QString time, QString info, QString count, QWidget *parent) :
    QWidget(parent),
    m_picPath(path),
    m_picTime(time),
    m_picInfo(info),
    m_picCount(count),
    ui(new Ui::RecVideoItem)
{
    ui->setupUi(this);
    this->setFixedHeight(90);
    this->setFixedWidth(250);

    ui->label_video->installEventFilter(this);
    ui->label_video->hide();
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

void RecVideoItem::setVideoPicture(const QString path)
{
    qDebug() << "picture path =" << path;
    QPixmap pix(path);
    ui->label_video->setPixmap(pix);
    ui->label_video->setScaledContents(true);//内容自适应
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
    QString text = fontMetric.elidedText(info,Qt::ElideRight,210,0);//21个字宽以后，省略为...
    ui->pushButton_videoInfo->setText(text);
}

void RecVideoItem::setVideoUpvoye(const QString &count)
{
    ui->pushButton_playAmount->setText(count);
}


bool RecVideoItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label_video)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->pushButton_play->show();
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->pushButton_play->hide();
        }
    }
    return QWidget::eventFilter(watched,event);

}

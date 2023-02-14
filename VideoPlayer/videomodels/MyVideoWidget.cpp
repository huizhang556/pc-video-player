#include "MyVideoWidget.h"
#include <QDebug>

MyVideoWidget::MyVideoWidget(QWidget *parent) :
    QVideoWidget()
{
    Q_UNUSED(parent);
//    this->setWindowFlags(Qt::FramelessWindowHint);
//    int brightness() const;
//    int contrast() const;
//    int hue() const;
//    int saturation() const;
    //监听player播放状态
//    m_playAdjust = new PlayCtlAdjustForm();
//    m_playAdjust->setObjectName(QString::fromLocal8Bit("m_playAdjust"));
//    setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(this,&MyVideoWidget::customContextMenuRequested,[=](){
//        createRightMenu();
//    });
    installEventFilter(this);
}

MyVideoWidget::~MyVideoWidget()
{

}

bool MyVideoWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            emit sig_video_clicked();
            qDebug() <<QString(u8"视频界面点击了！");
        }
    }
    return QVideoWidget::eventFilter(watched,event);
}

void MyVideoWidget::enterEvent(QEvent *e)
{
    Q_UNUSED(e);
//    emit mouseEnterToVideoUI();
//    updatePlayAdustForm();
//    qDebug() << "the mouse enter video";
}

void MyVideoWidget::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);
//    emit mouseLeaveFromVideoUI();
//    m_playAdjust->hide();
    //    qDebug() << "the mouse leave video";
}



void MyVideoWidget::createRightMenu()
{
    m_videoMenu = new QMenu(this);
    m_videoMenu->setObjectName(QString::fromUtf8("m_mainVideoMenu"));
    m_videoMenu->addAction(QString(u8"主播放器打开"),this,SLOT(slot_menu_mainPlayer()));
    m_videoMenu->addAction(QString(u8"下载"),this,SLOT(slot_menu_download()));
    m_videoMenu->addAction(QString(u8"全屏"),this,SLOT(slot_menu_fullscreen()));
    m_videoMenu->addSeparator();
    m_videoMenu->addAction(QString(u8"画面比例"),this,SLOT(slot_menu_scale()));
    m_videoMenu->addAction(QString(u8"视频信息"),this,SLOT(slot_menu_videoinfo()));
    m_videoMenu->addAction(QString(u8"设置"),this,SLOT(slot_menu_setting()));
    m_videoMenu->exec(QCursor::pos());
    qDebug() << QString(u8"右键触发！");
    delete m_videoMenu;
}

void MyVideoWidget::slot_menu_mainPlayer()
{

}

void MyVideoWidget::slot_menu_download()
{

}

void MyVideoWidget::slot_menu_fullscreen()
{

}

void MyVideoWidget::slot_menu_scale()
{

}

void MyVideoWidget::slot_menu_videoinfo()
{

}

void MyVideoWidget::slot_menu_setting()
{

}

/*更新播放栏目位置*/
//void MyVideoWidget::updatePlayAdustForm()
//{
//    m_playAdjust->setGeometry(0,this->height(),this->width(),60);
//    m_playAdjust->raise();
//    m_playAdjust->show();
//}


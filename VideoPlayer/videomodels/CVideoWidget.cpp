#include "CVideoWidget.h"
#include "ui_CVideoWidget.h"

CVideoWidget::CVideoWidget(QWidget *parent) :
    QVideoWidget(parent),
    ui(new Ui::CVideoWidget)
{
    ui->setupUi(this);
    installEventFilter(this);
}

CVideoWidget::~CVideoWidget()
{
    delete m_videoMenu;
    delete ui;
}

void CVideoWidget::setCurPlayStatus(bool play)
{
    if(play)//播放
    {
        ui->pushButton_status->setProperty("status",true);
    }
    else
    {
        ui->pushButton_status->setProperty("status",false);
    }
}

bool CVideoWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            emit sig_video_clicked();
            setCurPlayStatus(true);
            qDebug() <<QString(u8"视频界面点击了！");
        }
    }
    return QVideoWidget::eventFilter(watched,event);
}

void CVideoWidget::createRightMenu()
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

}

void CVideoWidget::slot_menu_mainPlayer()
{

}

void CVideoWidget::slot_menu_download()
{

}

void CVideoWidget::slot_menu_fullscreen()
{

}

void CVideoWidget::slot_menu_scale()
{

}

void CVideoWidget::slot_menu_videoinfo()
{

}

void CVideoWidget::slot_menu_setting()
{

}

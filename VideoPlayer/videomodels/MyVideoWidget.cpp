#include "MyVideoWidget.h"
#include "ui_MyVideoWidget.h"

MyVideoWidget::MyVideoWidget(QWidget *parent) :
    QVideoWidget(),
    ui(new Ui::MyVideoWidget)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MyVideoWidget::~MyVideoWidget()
{
    delete ui;
}

void MyVideoWidget::initWorkUI()
{

}

void MyVideoWidget::handleSignalsAndSlots()
{

}

void MyVideoWidget::setInstallEventFilter()
{
    this->installEventFilter(this);
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

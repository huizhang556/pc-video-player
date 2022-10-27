#include "VideoHeadItem.h"
#include "ui_VideoHeadItem.h"
#include <QDebug>

VideoHeadItem::VideoHeadItem(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::VideoHeadItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setEventFilter();
}

VideoHeadItem::~VideoHeadItem()
{
    delete ui;
}

void VideoHeadItem::initWorkUI()
{
//    this->setAttribute(Qt::WA_TranslucentBackground,true);
    ui->pushButton_mainPlayer->hide();
}

void VideoHeadItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_mainPlayer,&QPushButton::clicked,[=](){
        qDebug() << "player clicked";
        emit sig_sendPlayer();
    });
}

void VideoHeadItem::setEventFilter()
{
    this->installEventFilter(this);
}

bool VideoHeadItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->pushButton_mainPlayer->show();
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->pushButton_mainPlayer->hide();
        }
    }
    return QWidget::eventFilter(watched,event);
}

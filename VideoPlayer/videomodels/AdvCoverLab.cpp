#include "AdvCoverLab.h"
#include "ui_AdvCoverLab.h"

AdvCoverLab::AdvCoverLab(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::AdvCoverLab)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

AdvCoverLab::~AdvCoverLab()
{
    delete ui;
}

void AdvCoverLab::initWorkUI()
{
    this->installEventFilter(this);
}

void AdvCoverLab::handleSignalsAndSlots()
{
    connect(ui->pushButton_cancelplay,&QPushButton::clicked,[=](){
        emit sig_cancel();
        ui->pushButton_cancelplay->setText("");
        ui->pushButton_cancelplay->hide();
        setPlayButtonCtl(true);
    });
    connect(ui->pushButton_pause,&QPushButton::clicked,[=](){
        if(!m_clicked)
        {
            emit sig_play();
        }
    });
}

void AdvCoverLab::setContinuePlay(const QString &text)
{
    if(!text.isEmpty())
    {
        ui->pushButton_cancelplay->setText(text);
    }
    else
    {
        ui->pushButton_cancelplay->setText(text);
        ui->pushButton_cancelplay->hide();
    }
}

void AdvCoverLab::setDuration(const QString &duration)
{
    ui->pushButton_duration->setText(duration);
}

void AdvCoverLab::setCountDown(const QString &num)
{
    if(num.isEmpty())
    {
    }
    else
    {
        ui->pushButton_pause->setText(num);
    }
}

void AdvCoverLab::setPlayButtonCtl(bool show)
{
    if(show)
    {
        ui->pushButton_pause->setText("");
        ui->pushButton_pause->setProperty("pause",true);
    }
    else
    {
        ui->pushButton_pause->setProperty("pause",false);
    }
    ui->pushButton_pause->style()->polish(ui->pushButton_pause);
}

bool AdvCoverLab::eventFilter(QObject *watched, QEvent *event)
{
//    if(watched == this && event->type() == QEvent::MouseButtonPress && m_clicked)
//    {
//        emit sig_play();
//        m_clicked = false;
//    }
    return QLabel::eventFilter(watched,event);
}

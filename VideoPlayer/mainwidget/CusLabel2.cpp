#include "CusLabel2.h"
#include "ui_CusLabel2.h"

CusLabel2::CusLabel2(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::CusLabel2)
{
    ui->setupUi(this);
    installEventFilter(this);
    initWorkUI();
    handleSignalsAndSlots();
}

CusLabel2::CusLabel2(const QString &mainPic, const QString &topRightMark, const QString &playCounts, const bool play_on, QWidget *parent):
    QLabel(parent),
    m_playOn(play_on),
    ui(new Ui::CusLabel2)
{
    ui->setupUi(this);
    installEventFilter(this);
    initWorkUI();
    handleSignalsAndSlots();
    this->setPixmap(QPixmap(mainPic));
    this->setScaledContents(true);
    ui->pushButton_rightMark->setIcon(QIcon(topRightMark));
    ui->pushButton_playcounts->setText(playCounts);
}

CusLabel2::~CusLabel2()
{
    delete ui;
}

void CusLabel2::initWorkUI()
{
    ui->pushButton_play->hide();
}

void CusLabel2::handleSignalsAndSlots()
{
    connect(ui->pushButton_play,&QPushButton::clicked,[=](){
        emit sig_buttonClicked();
    });
}

bool CusLabel2::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
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

#include "CusListItem1.h"
#include "ui_CusListItem1.h"

#include <QDebug>

CusListItem1::CusListItem1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusListItem1)
{
    ui->setupUi(this);
    initWorkUI();
}

CusListItem1::CusListItem1(const QString &first, const QString &second, QWidget *parent):
    QWidget(parent),
    m_firstText(first),
    m_secTopText(first),
    m_secBomText(second),
    ui(new Ui::CusListItem1)
{
    ui->setupUi(this);
    initWorkUI();
    setFirstPageText();
    setSecondTopText();
    setSecondBottomText();
}

CusListItem1::~CusListItem1()
{
    delete ui;
}

void CusListItem1::initWorkUI()
{
    this->installEventFilter(this);
    ui->pushButton_first->installEventFilter(this);
    ui->pushButton_bottom->installEventFilter(this);
    ui->pushButton_top->installEventFilter(this);

    ui->stackedWidget_switch->setCurrentIndex(0);
    m_font.setFamily(QString(u8"宋体"));
    m_font.setPointSize(14);
}

void CusListItem1::setFirstPageText()
{
    ui->pushButton_first->setText(m_firstText);
}

void CusListItem1::setSecondTopText()
{
    ui->pushButton_top->setText(m_secTopText);
    ui->pushButton_top->setIcon(QIcon("://images/home/vtitle_vvip.png"));
    ui->pushButton_top->setIconSize(QSize(28,16));
}

void CusListItem1::setSecondBottomText()
{
    ui->pushButton_bottom->setText(m_secBomText);
}

void CusListItem1::slot_setCurrentItemPage(int index)
{
    ui->stackedWidget_switch->setCurrentIndex(index);
}

bool CusListItem1::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            emit sig_itemEnter();
//            qDebug()<< QString(u8"stack enter");
        }
        else if(event->type() == QEvent::Leave)
        {
            emit sig_itemLeave();
//            qDebug()<< QString(u8"stack leave");
        }
    }
    return QWidget::eventFilter(watched,event);
}

void CusListItem1::setFontSize(int size)
{
    m_font.setPointSize(size);
}

void CusListItem1::setFontFamily(const QString &family)
{
    m_font.setFamily(family);
}

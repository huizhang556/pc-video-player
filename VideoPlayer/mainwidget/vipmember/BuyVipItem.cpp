#include "BuyVipItem.h"
#include "ui_BuyVipItem.h"

BuyVipItem::BuyVipItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuyVipItem)
{
    ui->setupUi(this);
    setFixedSize(170,100);
    initWorkUI();
    handleSignalsAndSlots();
    this->installEventFilter(this);
    setItemMark("://images/home/songlist_hot.png");
    ui->pushButton_pricetype->installEventFilter(this);
}

BuyVipItem::~BuyVipItem()
{
    delete ui;
}

void BuyVipItem::initWorkUI()
{
    m_itemMarkButton = new QPushButton();
    m_itemMarkButton->setFixedSize(60,18);
    m_itemMarkButton->setObjectName(QString(u8"m_itemMarkButton"));
}

void BuyVipItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_pricetype,&QPushButton::clicked,[=](){
        emit    sig_sendMouseClicked(ui->pushButton_pricetype->text());
    });
}

void BuyVipItem::setItemMark(const QString &path)
{
    if(path.isEmpty())
    {
        m_itemMarkButton->hide();
    }
    else
    {
        m_itemMarkButton->setParent(this);
//        m_itemMarkButton->setIcon(QIcon(path));
        m_itemMarkButton->setText(QString(u8"特价优惠"));
        m_itemMarkButton->move(65,35);
    }


}

bool BuyVipItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            emit sig_sendMouseClicked(ui->pushButton_pricetype->text());
        }
    }
    return QWidget::eventFilter(watched,event);
}

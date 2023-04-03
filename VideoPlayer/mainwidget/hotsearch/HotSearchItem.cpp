#include "HotSearchItem.h"
#include "ui_HotSearchItem.h"

HotSearchItem::HotSearchItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotSearchItem)
{
    ui->setupUi(this);
    setFixedHeight(46);
    initWorkUI();
    handleSignalsAndSlots();
}

HotSearchItem::HotSearchItem(const QString order, const QString hotStr, bool up, QWidget *parent):
    QWidget(parent),
    ui(new Ui::HotSearchItem)
{
    ui->setupUi(this);
    setFixedHeight(46);
    setItemOrderText(order);
    ui->pushButton->setText(hotStr);
    if(!ui->pushButton->text().isEmpty())
        ui->pushButton->setIcon(QIcon("://images/icon/hot0.png"));
    if(up)
        ui->label_updown->setPixmap(QPixmap("://images/fileitem/hot_up.png"));
    else
        ui->label_updown->setPixmap(QPixmap("://images/fileitem/hot_down.png"));
    initWorkUI();
    handleSignalsAndSlots();
}

HotSearchItem::~HotSearchItem()
{
    delete ui;
}

void HotSearchItem::initWorkUI()
{

}

void HotSearchItem::handleSignalsAndSlots()
{
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        emit sig_sendItemText(ui->pushButton->text());
    });
}

void HotSearchItem::setItemOrderText(const QString &order)
{
    if(order == "1")
    {
        ui->label->setProperty("first",true);
    }
    else if(order == "2")
    {
        ui->label->setProperty("second",true);
    }
    else if(order == "3")
    {
        ui->label->setProperty("third",true);
    }
    else
    {
        ui->label->setProperty("other",true);
    }
    ui->label->setText(order);
    ui->label->style()->polish(ui->label);//样式生效
}

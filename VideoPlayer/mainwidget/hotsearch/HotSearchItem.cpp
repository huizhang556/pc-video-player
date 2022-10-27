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
    ui->label->setText(order);
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

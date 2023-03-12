#include "UserItem.h"
#include "ui_UserItem.h"

UserItem::UserItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSLots();

}

UserItem::UserItem(QString name, QWidget *parent):
    QWidget(parent),
    m_userName(name),
    ui(new Ui::UserItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSLots();
    setUserName(name);
}

UserItem::~UserItem()
{
    delete ui;
}

void UserItem::initWorkUI()
{

}

void UserItem::handleSignalsAndSLots()
{
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        emit sig_item_remove();
    });

    connect(ui->pushButton_name,&QPushButton::clicked,[=](){
        emit sig_item_clicked(ui->pushButton_name->text());
    });
}

void UserItem::setUserName(const QString name)
{
    m_userName = name;
    ui->pushButton_name->setText(m_userName);
}

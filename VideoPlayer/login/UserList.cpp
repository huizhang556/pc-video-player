#include "UserList.h"
#include "ui_UserList.h"

UserList::UserList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserList)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground);
    setFocusPolicy(Qt::NoFocus);
    initWorkUI();
    installEventFilter(this);
}

UserList::~UserList()
{
    delete ui;
}

void UserList::initWorkUI()
{
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0; i < nameList.size(); i++)
    {
        slot_addItem(nameList.at(i));
    }
}

void UserList::slot_addItem(QString name)
{
    UserItem *item = new UserItem(name);
    ui->verAddLayout->insertWidget(0,item);
    connect(item,&UserItem::sig_item_remove,[=](){
        ui->verAddLayout->removeWidget(item);
        item->deleteLater();
    });

    connect(item,&UserItem::sig_item_clicked,[=](QString name){
        emit sig_list_username(name);
    });
}

void UserList::slot_removeItem()
{

}

bool UserList::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && event->type() == QEvent::Leave)
    {
        this->close();
    }
    return  QWidget::eventFilter(watched,event);
}

void UserList::checkedItemsCounts()
{
    if(ui->verticalLayout->count() < 2)
    {
        setFixedHeight(ui->verAddLayout->count()*48);
        qDebug() << QString(u8"三个及以下！");
    }
    else
    {
        setFixedHeight(156);
        qDebug() << QString(u8"三个以上！");
    }
}

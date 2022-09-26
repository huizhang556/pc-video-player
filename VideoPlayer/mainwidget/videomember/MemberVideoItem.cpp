#include "MemberVideoItem.h"
#include "ui_MemberVideoItem.h"
#include "global/Global.h"
#include <QDebug>

MemberVideoItem::MemberVideoItem(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::MemberVideoItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MemberVideoItem::MemberVideoItem(const QString &picpath, const QString &name, const QString &author, QWidget *parent) :
    QLabel(parent),
    ui(new Ui::MemberVideoItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();

    ui->label_videoPic->setPixmap(QPixmap(picpath));
    this->setScaledContents(true);

    ui->pushButton_intro->setText(name);
    ui->pushButton_name->setText(author);
}

MemberVideoItem::~MemberVideoItem()
{
    delete ui;
}

void MemberVideoItem::initWorkUI()
{
//    QString path = Global::appDirPath + QString("/pictures/mylike/list_intro6.png");
//    ui->label_videoPic->setPixmap(QPixmap(path));
//    this->setScaledContents(true);
}

void MemberVideoItem::handleSignalsAndSlots()
{

}

void MemberVideoItem::setInstallEventFilter()
{

}

bool MemberVideoItem::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched,event);
}

void MemberVideoItem::slot_setItemPictures(const QString &picpath)
{
    this->setPixmap(QPixmap(picpath));
    this->setScaledContents(true);
}

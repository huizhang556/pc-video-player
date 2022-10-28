#include "MemberVideoItem.h"
#include "ui_MemberVideoItem.h"
#include "global/Global.h"
#include <QDebug>

MemberVideoItem::MemberVideoItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemberVideoItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MemberVideoItem::MemberVideoItem(const QString &picpath, const QString &name, const QString &author, QWidget *parent) :
    QWidget(parent),
    m_picPath(picpath),
    m_info1(name),
    m_info2(author),
    ui(new Ui::MemberVideoItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    slot_setItemPictures();
    slot_setItemInfos();
}

MemberVideoItem::~MemberVideoItem()
{
    delete ui;
}

void MemberVideoItem::initWorkUI()
{
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

void MemberVideoItem::slot_setItemPictures()
{
//    ui->label_videoPic->setPixmap(QPixmap(m_picPath));
//    ui->label_videoPic->setScaledContents(true);
    ui->label_videoPic->setItemPicture(m_picPath);
}

void MemberVideoItem::slot_setItemInfos()
{
    ui->pushButton_intro->setText(m_info1);
    ui->pushButton_name->setText(m_info2);
}

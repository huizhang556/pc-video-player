#include "MemberVideoItem.h"
#include "ui_MemberVideoItem.h"

#ifdef QT_DEBUG
        QString MemberVideoItem::m_appDir = QString("E:/TEST/VipMemberVideo");
#else
        QString MemberVideoItem::m_appDir = QDir::currentPath();//release时使用
#endif

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

MemberVideoItem::~MemberVideoItem()
{
    delete ui;
}

void MemberVideoItem::initWorkUI()
{
    QString path = m_appDir + QString("/pictures/mylike/list_intro6.png");
    this->setPixmap(QPixmap(path));
    this->setScaledContents(true);
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

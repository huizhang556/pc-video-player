#include "VideoItem.h"
#include "ui_VideoItem.h"

VideoItem::VideoItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

VideoItem::VideoItem(const QString &picPath, const QString &introduce, const QString &author, QWidget *parent):
    QWidget(parent),
    m_picPath(picPath),
    m_intro(introduce),
    m_author(author),
    ui(new Ui::VideoItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    setItemPicture();
    setItemIntroduce();
    setItemAuthor();
}

VideoItem::~VideoItem()
{
    delete ui;
}

void VideoItem::initWorkUI()
{

}

void VideoItem::handleSignalsAndSlots()
{

}

void VideoItem::setInstallEventFilter()
{

}

void VideoItem::setItemPicture()
{
//    ui->label_mvPic->setPixmap(QPixmap(m_picPath));
//    ui->label_mvPic->setScaledContents(true);
    ui->label_mvPic->setItemPicture(m_picPath);
}

void VideoItem::setItemIntroduce()
{
    ui->pushButton_name->setText(m_intro);
}

void VideoItem::setItemAuthor()
{
    ui->pushButton_author->setText(m_author);
}

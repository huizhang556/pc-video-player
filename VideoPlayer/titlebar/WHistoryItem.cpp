#include "WHistoryItem.h"
#include "ui_WHistoryItem.h"

WHistoryItem::WHistoryItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WHistoryItem)
{
    ui->setupUi(this);
}

WHistoryItem::WHistoryItem(const QString &picpath, const QString &info, const QString &progress, QWidget *parent):
    QWidget(parent),
    m_picpath(picpath),
    m_info(info),
    m_progress(progress),
    ui(new Ui::WHistoryItem)
{
    ui->setupUi(this);
    setItemPicture();
    setItemInfo();
    setItemProgress();
}


WHistoryItem::~WHistoryItem()
{
    delete ui;
}

void WHistoryItem::setItemPicture()
{
    ui->label_header->setPixmap(QPixmap(m_picpath));
    ui->label_header->setScaledContents(true);
}

void WHistoryItem::setItemInfo()
{
    ui->textEdit_intro->setReadOnly(true);
    ui->textEdit_intro->setPlainText(m_info);
}

void WHistoryItem::setItemProgress()
{
    ui->pushButton_progress->setText(m_progress);
}

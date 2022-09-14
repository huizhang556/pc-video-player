#include "HotDownloadItem.h"
#include "ui_HotDownloadItem.h"

HotDownloadItem::HotDownloadItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotDownloadItem)
{
    ui->setupUi(this);
//    setMinimumWidth(550);
    initWorkUI();
    handleSignalsAndSlots();
}

HotDownloadItem::~HotDownloadItem()
{
    delete ui;
}

void HotDownloadItem::initWorkUI()
{

}

void HotDownloadItem::handleSignalsAndSlots()
{

}

bool HotDownloadItem::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched,event);
}

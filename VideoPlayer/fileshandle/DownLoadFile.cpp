#include "DownLoadFile.h"
#include "ui_DownLoadFile.h"
#include "fileshandle/FileItem.h"

#include <QListWidgetItem>
#include <QDebug>

DownLoadFile::DownLoadFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownLoadFile)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

DownLoadFile::~DownLoadFile()
{
    delete ui;
}

void DownLoadFile::initWorkUI()
{
//    ui->listWidget_downloadlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_downloadlist->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    for(int i = 0; i< 50; i++)
    {
        QListWidgetItem *item = new QListWidgetItem();
        FileItem *fileItem = new FileItem();
        item->setSizeHint(fileItem->size());
        ui->listWidget_downloadlist->addItem(item);
        ui->listWidget_downloadlist->setItemWidget(item,fileItem);
    }
}

void DownLoadFile::handleSignalsAndSlots()
{
    //清除所有
    connect(ui->pushButton_cancelall,&QPushButton::clicked,[=](){ui->listWidget_downloadlist->clear();});
}

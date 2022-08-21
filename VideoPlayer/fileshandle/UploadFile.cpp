#include "UploadFile.h"
#include "ui_UploadFile.h"
#include "fileshandle/FileItem.h"

#include <QListWidgetItem>
#include <QDebug>

UploadFile::UploadFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UploadFile)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

UploadFile::~UploadFile()
{
    delete ui;
}

void UploadFile::initWorkUI()
{
//    ui->listWidget_uploadlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_uploadlist->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    for(int i = 0; i< 50; i++)
    {
        QListWidgetItem *item = new QListWidgetItem();
        FileItem *fileItem = new FileItem();
        item->setSizeHint(fileItem->size());
        ui->listWidget_uploadlist->addItem(item);
        ui->listWidget_uploadlist->setItemWidget(item,fileItem);
    }
}

void UploadFile::handleSignalsAndSlots()
{
    //清除所有
    connect(ui->pushButton_cancelall,&QPushButton::clicked,[=](){ui->listWidget_uploadlist->clear();});
}

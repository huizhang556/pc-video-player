#include "CompletedFiles.h"
#include "ui_CompletedFiles.h"
#include "fileshandle/FileItem.h"

#include <QListWidgetItem>
#include <QDebug>

CompletedFiles::CompletedFiles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompletedFiles)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

CompletedFiles::~CompletedFiles()
{
    delete ui;
}

void CompletedFiles::initWorkUI()
{
//    ui->listWidget_completedlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_completedlist->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    for(int i = 0; i< 50; i++)
    {
        QListWidgetItem *item = new QListWidgetItem();
        FileItem *fileItem = new FileItem();
        item->setSizeHint(fileItem->size());
        ui->listWidget_completedlist->addItem(item);
        ui->listWidget_completedlist->setItemWidget(item,fileItem);
    }
}

void CompletedFiles::handleSignalsAndSlots()
{
    //清除所有
    connect(ui->pushButton_clearall,&QPushButton::clicked,[=](){ui->listWidget_completedlist->clear();});
}

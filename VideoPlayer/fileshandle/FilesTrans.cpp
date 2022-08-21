#include "FilesTrans.h"
#include "ui_FilesTrans.h"

#include <QListWidgetItem>
#include <QDebug>

FilesTrans::FilesTrans(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilesTrans)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

FilesTrans::~FilesTrans()
{
    delete ui;
}

void FilesTrans::initWorkUI()
{
    QListWidgetItem *downItem       = new QListWidgetItem(QIcon(":/images/fileitem/file_download.png"),QString::fromLocal8Bit("正在下载"));
    QListWidgetItem *uploadItem     = new QListWidgetItem(QIcon(":/images/fileitem/file_upload.png"),QString::fromLocal8Bit("正在上传"));
    QListWidgetItem *completeItem   = new QListWidgetItem(QIcon(":/images/fileitem/file_completed.png"),QString::fromLocal8Bit("传输完成"));

    downItem->setSizeHint(QSize(120,50));
    ui->listWidget_trans->addItem(downItem);
    uploadItem->setSizeHint(QSize(120,50));
    ui->listWidget_trans->addItem(uploadItem);
    completeItem->setSizeHint(QSize(120,50));
    ui->listWidget_trans->addItem(completeItem);

    ui->listWidget_trans->setCurrentItem(downItem);
    ui->listWidget_trans->setFixedWidth(122);

    m_uploadFiles = new UploadFile();
    m_uploadFiles->setObjectName(QString::fromLocal8Bit("m_uploadFiles"));

    m_downloadFiles = new DownLoadFile();
    m_downloadFiles->setObjectName(QString::fromLocal8Bit("m_downloadFiles"));

    m_completeFiles = new CompletedFiles();
    m_completeFiles->setObjectName(QString::fromLocal8Bit("m_completeFiles"));

    ui->stackedWidget_trans->addWidget(m_downloadFiles);
    ui->stackedWidget_trans->addWidget(m_uploadFiles);
    ui->stackedWidget_trans->addWidget(m_completeFiles);

}

void FilesTrans::handleSignalsAndSlots()
{
    connect(ui->listWidget_trans,&QListWidget::itemClicked,[=](QListWidgetItem* item){
        setCurrentShowPage(item->text());
    });
}

void FilesTrans::setCurrentShowPage(QString page)
{
    if(QString::fromLocal8Bit("正在下载") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(0);
    }
    else if(QString::fromLocal8Bit("正在上传") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(1);
    }
    else if(QString::fromLocal8Bit("传输完成") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(2);
    }
    else
    {
        ui->stackedWidget_trans->setCurrentIndex(2);
    }
}

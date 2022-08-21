#include "FileItem.h"
#include "ui_FileItem.h"

FileItem::FileItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

FileItem::~FileItem()
{
    delete ui;
}

void FileItem::initWorkUI()
{

    ui->stackedWidget_fileinfo->setCurrentIndex(0);
    ui->stackedWidget_speedtime->setCurrentIndex(0);
    ui->stackedWidget_progressbar->setCurrentIndex(0);
    ui->stackedWidget_control->setCurrentIndex(0);

    //事件过滤器
    ui->stackedWidget_speedtime->installEventFilter(this);

    ui->pushButton_fast->setIcon(QIcon(":/images/fileitem/fileitem_fastdownload.png"));
    ui->pushButton_fast->setHidden(true);
    ui->pushButton_fastupload->setIcon(QIcon(":/images/fileitem/fileitem_fastupload.png"));
    //开始-暂停
    ui->pushButton_filePause->setToolTip(QString::fromLocal8Bit("暂停下载"));
    ui->pushButton_filePause->setIcon(QIcon("://images/fileitem/fileitem_pause.png"));
    //取消
    ui->pushButton_fileCancel->setToolTip(QString::fromLocal8Bit("取消下载"));
    ui->pushButton_fileCancel->setIcon(QIcon("://images/fileitem/fileitem_cancel.png"));
    //打开目录
    ui->pushButton_fileOpen->setToolTip(QString::fromLocal8Bit("打开目录"));
    ui->pushButton_fileOpen->setIcon(QIcon("://images/fileitem/fileitem_directory.png"));
    //打开文件
    ui->pushButton_openFile->setToolTip(QString::fromLocal8Bit("打开文件"));
    ui->pushButton_openFile->setIcon(QIcon("://images/fileitem/fileitem_use.png"));
    //打开目录
    ui->pushButton_directory->setToolTip(QString::fromLocal8Bit("打开目录"));
    ui->pushButton_directory->setIcon(QIcon("://images/fileitem/fileitem_directory.png"));
    //删除文件
    ui->pushButton_filedelete->setToolTip(QString::fromLocal8Bit("删除文件"));
    ui->pushButton_filedelete->setIcon(QIcon("://images/fileitem/fileitem_clear.png"));
}

void FileItem::handleSignalsAndSlots()
{
    //开始暂停
    connect(ui->pushButton_filePause,&QPushButton::clicked,[=](){ emit sig_sendStartPause(true); });
    //取消下载
    connect(ui->pushButton_fileCancel,&QPushButton::clicked,[=](){  emit sig_sendCancel(); });
    //打开目录
    connect(ui->pushButton_fileOpen,&QPushButton::clicked,[=](){  emit sig_sendOpenDirectory(); });
    //打开文件
    connect(ui->pushButton_openFile,&QPushButton::clicked,[=](){  emit sig_sendOpenFileContent(); });
    //打开目录
    connect(ui->pushButton_directory,&QPushButton::clicked,[=](){  emit sig_sendOpenLocalDirectory(); });
    //删除文件
    connect(ui->pushButton_filedelete,&QPushButton::clicked,[=](){  emit sig_senDdeleteFile(); });
}

bool FileItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->stackedWidget_speedtime)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->pushButton_fast->setHidden(false);
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->pushButton_fast->setHidden(true);
        }
    }
    return QWidget::eventFilter(watched,event);
}

//设置文件图标
void FileItem::slot_setFilePicType(QString type)
{
    QPixmap pix("");
    ui->label_filePic->setPixmap(pix);
    ui->label_filePic->setScaledContents(true);
}

//设置文件名
void FileItem::slot_setFileName(const QString name)
{
    ui->pushButton_filename->setText(name);
}

//设置文件大小
void FileItem::slot_setFileSize(const QString size)
{
    ui->label_fileSize->setText(size);
}

//完成时间/剩余时间/下载状态
void FileItem::slot_setFileTime(const QString time)
{
    ui->label_useTime->setText(time);
}

//设置进度
void FileItem::slot_setProgressBarValue(qint64 received, qint64 total)
{
    int value = received*100/total;
    ui->progressBar_jindu->setValue(value);
}

void FileItem::slot_setFileSpeed(const QString speed)
{
    ui->label_fileSpeed->setText(speed);
}

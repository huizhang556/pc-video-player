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
    ui->listWidget_trans->setFixedHeight(70);
    ui->listWidget_trans->setViewMode(QListView::IconMode);//默认是自动换行的
    ui->listWidget_trans->setMovement(QListView::Static);//不可拖动
    ui->listWidget_trans->setResizeMode(QListWidget::Adjust);
    ui->listWidget_trans->setWrapping(false);// 不自动换行
    ui->listWidget_trans->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_trans->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_trans->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //setLayoutDirection
    //在列表模式下，控制图标在文本左（LeftToRight）边还是在右（RightToLeft）
    //在图标模式下，不起作用
//    ui->listWidget_trans->setLayoutDirection(Qt::LeftToRight);


    QListWidgetItem *myFileItem     = new QListWidgetItem(QIcon(":/images/fileitem/fileitem_files.png"),QString::fromLocal8Bit("我的文件"));
    QListWidgetItem *recentlyItem   = new QListWidgetItem(QIcon(":/images/fileitem/fileitem_recent.png"),QString::fromLocal8Bit("最近传输"));
    QListWidgetItem *videoItem      = new QListWidgetItem(QIcon(":/images/fileitem/fileitem_videos.png"),QString::fromLocal8Bit("我的视频"));
    QListWidgetItem *musicItem      = new QListWidgetItem(QIcon(":/images/fileitem/fileitem_musics.png"),QString::fromLocal8Bit("我的音乐"));
    QListWidgetItem *imageItem      = new QListWidgetItem(QIcon(":/images/fileitem/fileitem_images.png"),QString::fromLocal8Bit("我的图片"));
    QListWidgetItem *documentItem   = new QListWidgetItem(QIcon(":/images/fileitem/fileitem_documents.png"),QString::fromLocal8Bit("我的文档"));
    QListWidgetItem *downItem       = new QListWidgetItem(QIcon(":/images/fileitem/file_download.png"),QString::fromLocal8Bit("正在下载"));
    QListWidgetItem *uploadItem     = new QListWidgetItem(QIcon(":/images/fileitem/file_upload.png"),QString::fromLocal8Bit("正在上传"));
    QListWidgetItem *completeItem   = new QListWidgetItem(QIcon(":/images/fileitem/file_completed.png"),QString::fromLocal8Bit("传输完成"));


    myFileItem->setSizeHint(QSize(100,70));
    ui->listWidget_trans->addItem(myFileItem);

    recentlyItem->setSizeHint(QSize(100,70));
    ui->listWidget_trans->addItem(recentlyItem);

    videoItem->setSizeHint(QSize(100,70));
    ui->listWidget_trans->addItem(videoItem);

    musicItem->setSizeHint(QSize(100,70));
    ui->listWidget_trans->addItem(musicItem);

    imageItem->setSizeHint(QSize(100,70));
    ui->listWidget_trans->addItem(imageItem);

    documentItem->setSizeHint(QSize(100,70));
    ui->listWidget_trans->addItem(documentItem);

    downItem->setSizeHint(QSize(100,70));
    ui->listWidget_trans->addItem(downItem);

    uploadItem->setSizeHint(QSize(100,70));
    ui->listWidget_trans->addItem(uploadItem);

    completeItem->setSizeHint(QSize(100,70));
    ui->listWidget_trans->addItem(completeItem);

    ui->listWidget_trans->setCurrentRow(0);

    //所有文件
    m_myAllFiles = new MyAllFile();
    m_myAllFiles->setObjectName(QString::fromLocal8Bit("m_myAllFiles"));
    //最近传输
    m_myLastFiles  = new MyLastFile();
    m_myLastFiles->setObjectName(QString::fromLocal8Bit("m_myLastFiles"));
    //视频文件
    m_myVideoFiles = new MyVideosFile();
    m_myVideoFiles->setObjectName(QString::fromLocal8Bit("m_myVideoFiles"));
    //音乐
    m_myMusicFiles = new MyMusicsFile();
    m_myMusicFiles->setObjectName(QString::fromLocal8Bit("m_myMusicFiles"));
    //图片
    m_myPicFiles  = new MyPicFile();
    m_myPicFiles->setObjectName(QString::fromLocal8Bit("m_myPicFiles"));
    //文档
    m_myDocFiles =  new MyDocFile();
    m_myDocFiles->setObjectName(QString::fromLocal8Bit("m_myDocFiles"));
    //上传记录
    m_uploadFiles = new UploadFile();
    m_uploadFiles->setObjectName(QString::fromLocal8Bit("m_uploadFiles"));
    //下载记录
    m_downloadFiles = new DownLoadFile();
    m_downloadFiles->setObjectName(QString::fromLocal8Bit("m_downloadFiles"));
    //总完成记录
    m_completeFiles = new CompletedFiles();
    m_completeFiles->setObjectName(QString::fromLocal8Bit("m_completeFiles"));

    ui->stackedWidget_trans->addWidget(m_myAllFiles);
    ui->stackedWidget_trans->addWidget(m_myLastFiles);
    ui->stackedWidget_trans->addWidget(m_myVideoFiles);
    ui->stackedWidget_trans->addWidget(m_myMusicFiles);
    ui->stackedWidget_trans->addWidget(m_myPicFiles);
    ui->stackedWidget_trans->addWidget(m_myDocFiles);
    ui->stackedWidget_trans->addWidget(m_downloadFiles);
    ui->stackedWidget_trans->addWidget(m_uploadFiles);
    ui->stackedWidget_trans->addWidget(m_completeFiles);
    ui->stackedWidget_trans->setCurrentIndex(0);//默认显示第一页

}

void FilesTrans::handleSignalsAndSlots()
{
    connect(ui->listWidget_trans,&QListWidget::itemClicked,[=](QListWidgetItem* item){
        setCurrentShowPage(item->text());
    });
}

void FilesTrans::setCurrentShowPage(QString page)
{
    if(QString::fromLocal8Bit("我的文件") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(0);
    }
    else if(QString::fromLocal8Bit("最近传输") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(1);
    }
    else if(QString::fromLocal8Bit("我的视频") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(2);
    }
    else if(QString::fromLocal8Bit("我的音乐") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(3);
    }
    else if(QString::fromLocal8Bit("我的图片") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(4);
    }
    else if(QString::fromLocal8Bit("我的文档") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(5);
    }
    else if(QString::fromLocal8Bit("正在下载") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(6);
    }
    else if(QString::fromLocal8Bit("正在上传") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(7);
    }
    else if(QString::fromLocal8Bit("传输完成") == page)
    {
        ui->stackedWidget_trans->setCurrentIndex(8);
    }
    else
    {
        ui->stackedWidget_trans->setCurrentIndex(0);
    }
}

void FilesTrans::setCurrentShowPage(QListWidgetItem *item)
{
    ui->stackedWidget_trans->setCurrentIndex(ui->listWidget_trans->row(item));
}

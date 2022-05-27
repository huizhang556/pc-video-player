#include "WebDownLoadList.h"
#include "ui_WebDownLoadList.h"
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>

WebDownLoadList* WebDownLoadList::m_pInstance = nullptr;

WebDownLoadList::WebDownLoadList(QWidget *parent) :
    QWidget(parent),
    m_start(true),//默认是开始下载状态
    m_count(0),
    ui(new Ui::WebDownLoadList)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("下载栏"));
    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground,true);
    this->setFixedSize(615,400);//记得滚动条的10px宽度
    initWorkUI();
    chandleSignalsAndSLots();
}

void WebDownLoadList::getButtonInfo()
{
    qDebug() <<QString::fromLocal8Bit("接收到信号！");
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    qDebug() << btn->parentWidget();
    qDebug() << btn->objectName()<<btn;
}

WebDownLoadList::~WebDownLoadList()
{
    delete ui;
    if(m_pInstance != nullptr)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

//获取单例
WebDownLoadList *WebDownLoadList::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new WebDownLoadList();
    }
    return m_pInstance;
}

DownLoadItem *WebDownLoadList::getDownloadItem()
{
    return m_downLoadItem;
}


void WebDownLoadList::initWorkUI()
{
    ui->lineEdit_search->setPlaceholderText(QString::fromLocal8Bit("搜索下载内容"));
    ui->lineEdit_inputurl->setPlaceholderText(QString::fromLocal8Bit("请输入下载地址,按Enter键下载"));
    ui->listWidget_list->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->stackedWidget_center->setCurrentIndex(0);
    ui->stackedWidget_bottom->setCurrentIndex(0);
}

void WebDownLoadList::chandleSignalsAndSLots()
{
    //新建下载---调出界面
    connect(ui->pushButton_addrecord,&QPushButton::clicked,[=](){ui->stackedWidget_bottom->setCurrentIndex(1);});
    //新建下载--发送下载信息
    connect(ui->lineEdit_inputurl,&QLineEdit::returnPressed,[=](){
        QString netAddress   = ui->lineEdit_inputurl->text().trimmed();
        if(netAddress.isEmpty()) return;
        emit sig_newDownloadRequest(netAddress);//发送下载地址，文件名
        ui->lineEdit_inputurl->clear();
        this->hide();
    });
    //返回
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){ui->stackedWidget_bottom->setCurrentIndex(0);});
    //清空列表
    connect(ui->pushButton_clearlist,&QPushButton::clicked,[=](){ ui->listWidget_list->clear();ui->stackedWidget_center->setCurrentIndex(1);});
    //下载设置
    connect(ui->pushButton_downsetting,&QPushButton::clicked,[=](){emit sig_setConfig();});
    //停止
    connect(stopbtn,&QPushButton::clicked,[=]()
    {
//        QPushButton *stopbtn = qobject_cast<QPushButton*>(sender());
//        QLabel *num = stopbtn->parentWidget()->findChild<QLabel*>();
//        emit sig_pause(num->text().toInt());
        slot_setStartStatus(stopbtn,m_start);
        qDebug()<< QString::fromLocal8Bit("暂停") << lab_num->text();
    });

    //暂停
    connect(m_downLoadItem,SIGNAL(sig_downloadStatus(bool)),this,SLOT(getButtonInfo()));
    //取消
    connect(m_downLoadItem,SIGNAL(sig_download_cancel()),this,SLOT(getButtonInfo()));
    //删除
    connect(m_downLoadItem,SIGNAL(sig_download_delete()),this,SLOT(getButtonInfo()));
    //重新下载
    connect(m_downLoadItem,SIGNAL(sig_download_reload()),this,SLOT(getButtonInfo()));
    //从列表中删除任务
    connect(m_downLoadItem,SIGNAL(sig_download_deleteItem()),this,SLOT(getButtonInfo()));
}

bool WebDownLoadList::slot_addDownLoadRecordToList(const QUrl &url, const QString &filename, const QString &savepath,bool openStatus)
{
    QFileInfo info(url.toString());
    m_fileSuffix = info.suffix();
    m_fileSize   = info.size();
    m_fileName   = filename;
    m_filePath = savepath + "/" + filename;
    ui->stackedWidget_center->setCurrentIndex(0);
//    m_barStackWgt = new QStackedWidget();
//    m_barStackWgt->setObjectName(QString::fromLocal8Bit("m_barStackWgt"));

//    m_ctlStackWgt = new QStackedWidget();
//    m_ctlStackWgt->setObjectName(QString::fromLocal8Bit("m_ctlStackWgt"));

////    QLabel *num = new QLabel(QString::number(m_count));
//    lab_num = new QLabel(QString::number(m_count));
//    lab_num->setObjectName(QString::fromLocal8Bit("dl_num"));
//    lab_num->setAlignment(Qt::AlignCenter);//文字居
//    slot_setItemPicture();//设置图标

////    QProgressBar *progressbar = new QProgressBar();
//    progressbar = new QProgressBar();
//    progressbar->setObjectName(QString::fromLocal8Bit("dl_progressbar"));
//    progressbar->setValue(0);

//    lab_fileSize = new QLabel();
//    lab_fileSize->setObjectName(QString::fromLocal8Bit("dl_fileSize"));
//    slot_setItemFileSize();

//    lab_fileName = new QLabel();
//    lab_fileName->setObjectName(QString::fromLocal8Bit("dl_fileName"));
//    slot_setItemFileName();

//    hblayout0 = new QHBoxLayout();
//    hblayout0->addSpacerItem(new QSpacerItem(5, 18, QSizePolicy::Fixed));
//    hblayout0->addWidget(lab_fileName);
//    hblayout0->addWidget(lab_fileSize);
//    hblayout0->setContentsMargins(0,0,0,0);

//    vblayout0 = new QVBoxLayout();
//    vblayout0->addWidget(progressbar);
//    vblayout0->addLayout(hblayout0);
//    vblayout0->setContentsMargins(0,0,0,0);

////    QPushButton *stopbtn = new QPushButton();
//    stopbtn = new QPushButton();
//    stopbtn->setObjectName(QString::fromLocal8Bit("dl_stopbtn"));
//    stopbtn->setToolTip(QString::fromLocal8Bit("暂停"));
////    QPushButton *downloadlbtn = new QPushButton();
//    downloadlbtn = new QPushButton();
//    downloadlbtn->setObjectName(QString::fromLocal8Bit("dl_downloadlbtn"));
//    downloadlbtn->setToolTip(QString::fromLocal8Bit("下载"));
////    QPushButton *deletebtn = new QPushButton();
//    deletebtn = new QPushButton();
//    deletebtn->setObjectName(QString::fromLocal8Bit("dl_deletebtn"));
//    deletebtn->setToolTip(QString::fromLocal8Bit("删除"));
////    QPushButton *openbtn = new QPushButton();
//    openbtn = new QPushButton();
//    openbtn->setObjectName(QString::fromLocal8Bit("dl_openbtn"));
//    openbtn->setToolTip(QString::fromLocal8Bit("打开文件"));
//    lab_num->setFixedSize(QSize(26,26));
//    progressbar->setFixedSize(360,18);
//    stopbtn->setFixedSize(QSize(18,18));
//    deletebtn->setFixedSize(QSize(18,18));
//    downloadlbtn->setFixedSize(QSize(18,18));
//    openbtn->setFixedSize(QSize(18,18));
////    QHBoxLayout *hblayout1 = new QHBoxLayout();
//    hblayout1 = new QHBoxLayout();
////    QHBoxLayout *hblayout2 = new QHBoxLayout();
//    hblayout2 = new QHBoxLayout();
//    hblayout2->addWidget(stopbtn);//暂停
//    hblayout2->addWidget(downloadlbtn);//下载
//    hblayout2->addWidget(deletebtn);//删除
//    hblayout2->addWidget(openbtn);//打开
//    hblayout2->setSpacing(10);

//    hblayout1->addWidget(lab_num);//序号
//    hblayout1->addLayout(vblayout0);//进度条整体
//    hblayout1->addSpacerItem(new QSpacerItem(5, 18, QSizePolicy::Fixed));//最小 30 26，可扩大
//    hblayout1->addLayout(hblayout2);//操作按钮
//    hblayout1->addSpacerItem(new QSpacerItem(5,18,QSizePolicy::Fixed));//右边界固定
////    QWidget *tempwdt = new QWidget();
//    tempwdt = new QWidget();
//    tempwdt->setFixedSize(600,40);
//    tempwdt->setLayout(hblayout1);
//    tempwdt->layout()->setContentsMargins(0,0,0,0);
//    tempwdt->layout()->setMargin(0);
////    QListWidgetItem *item = new QListWidgetItem();
    item = new QListWidgetItem();
    m_downLoadItem = new DownLoadItem(url,filename,savepath,openStatus);
    //堆变量每次分配不同的地址
    qDebug() <<QString::fromLocal8Bit("新分配的堆变量地址：") << m_downLoadItem;
    item->setSizeHint(m_downLoadItem->size());
    ui->listWidget_list->insertItem(0,item);
    ui->listWidget_list->setItemWidget(item,m_downLoadItem);
    qDebug() << QString::fromLocal8Bit("已经创建item!");
    return true;
}

void WebDownLoadList::slot_searchDownloadHirtory(QString text)
{

}

void WebDownLoadList::slot_setDownloadProgressbar(qint64 bytesReceived, qint64 bytesTotal)
{
//    progressbar->setValue(bytesReceived*100/bytesTotal);
//    if(bytesReceived*100/bytesTotal == 100)
//    {
//        emit sig_receiveFinished();
//        qDebug() <<QString::fromLocal8Bit("下载完成信号已发出！");
//    }
    m_downLoadItem->slot_setItemDownProgress(bytesReceived,bytesTotal);
}

void WebDownLoadList::slot_receivedNewWorkFinished()
{
    qDebug() << QString::fromLocal8Bit("任务栏已经收到下载结束信号！");
    //播放音频几种方式：
    //01.QSound,       播放wav格式
    //02.QSoundEffect, 可以调整音量大小，播放wav格式
    //03.QMediaPlayer，播放格式多种
//    QSoundEffect *sound = new QSoundEffect(":/audio/browser/finished.wav",this);
//    sound->setLoops(1);//循环次数
//    sound->play();
    m_downLoadItem->slot_receive_finished();
    QSoundEffect *effect = new QSoundEffect;
    effect->setSource(QUrl::fromLocalFile(":/audio/browser/finished.wav"));
    effect->setLoopCount(1);  //循环次数
    effect->setVolume(0.25f); //音量  0~1之间
    effect->play();
}

void WebDownLoadList::slot_setItemPicture()
{
    if("pdf" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_pdf.png);"
                           "}");
    }
    else if("doc" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_doc.png);"
                           "}");
    }
    else if("ppt" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_ppt.png);"
                           "}");
    }
    else if("xlsx" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_xlsx.png);"
                           "}");
    }
    else if("html" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_html.png);"
                           "}");
    }
    else if("mp4" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_mp4.png);"
                           "}");
    }
    else if("mp3" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_mp31.png);"
                           "}");
    }
    else if("zip" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_zip.png);"
                           "}");
    }
    else if("png" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_png.png);"
                           "}");
    }
    else if("jpg" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_jpg.png);"
                           "}");
    }
    else if("psd" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_psd.png);"
                           "}");
    }
    else if("rar" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_rar.png);"
                           "}");
    }
    else if("exe" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_exe.png);"
                           "}");
    }
    else if("mov" == m_fileSuffix)
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_mov.png);"
                           "}");
    }
    else
    {
        lab_num->setStyleSheet("#dl_num{"
                           "border-image:url(://images/function/download_unknow.png);"
                           "}");
    }
}

void WebDownLoadList::slot_setItemFileName()
{
    lab_fileName->setText(m_fileName);
}

void WebDownLoadList::slot_setItemFileSize()
{
    lab_fileSize->setText(QString::number(m_fileSize));
}

void WebDownLoadList::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
   QPoint winPos = this->pos();//界面位置
    QPoint nowPos = event->globalPos();//鼠标位置
    m_mvPos = nowPos - winPos;
}

void WebDownLoadList::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->move(event->globalPos() - m_mvPos);
}

void WebDownLoadList::on_pushButton_min_clicked()
{
    this->showMinimized();
}

void WebDownLoadList::on_pushButton_close_clicked()
{
    this->hide();
}

void WebDownLoadList::slot_setStartStatus(QPushButton *button, bool status)
{
    if(status)
    {
        button->setStyleSheet("#dl_stopbtn{"
                               "border-image:url(://images/function/download_start.png);"
                               "}");
        button->setToolTip(QString::fromLocal8Bit("开始"));
    }
    else
    {
        button->setStyleSheet("#dl_stopbtn{"
                               "border-image:url(://images/function/download_pause.png);"
                               "}");
        button->setToolTip(QString::fromLocal8Bit("暂停"));
    }
    m_start = !m_start;//状态置反
}

void WebDownLoadList::slot_openLocalFile()
{

}

void WebDownLoadList::slot_deleteFile()
{

}

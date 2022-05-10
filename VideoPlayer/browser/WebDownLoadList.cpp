#include "WebDownLoadList.h"
#include "ui_WebDownLoadList.h"

WebDownLoadList::WebDownLoadList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebDownLoadList)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    initWorkUI();
    chandleSignalsAndSLots();
}

WebDownLoadList::~WebDownLoadList()
{
    delete ui;
}

void WebDownLoadList::initWorkUI()
{
    this->setFixedSize(720,400);
    ui->listWidget_list->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    for(int i = 0; i<20; i++)
    slot_addDownLoadRecordToList(i+1);
}

void WebDownLoadList::chandleSignalsAndSLots()
{
    //新建下载
    connect(ui->pushButton_addrecord,&QPushButton::clicked,[=](){ui->stackedWidget_bottom->setCurrentIndex(1);});
    //返回
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){ui->stackedWidget_bottom->setCurrentIndex(0);});
    //清空列表
    connect(ui->pushButton_clearlist,&QPushButton::clicked,[=](){ ui->listWidget_list->clear(); });
    //下载设置
    connect(ui->pushButton_downsetting,&QPushButton::clicked,[=](){emit sig_setConfig();});
}

bool WebDownLoadList::slot_addDownLoadRecordToList(int order)
{
    QLabel  *num = new QLabel(QString::number(order));
    num->setObjectName(QString::fromLocal8Bit("dl_num"));
    QProgressBar *progressbar = new QProgressBar();
    progressbar->setObjectName(QString::fromLocal8Bit("dl_progressbar"));
    progressbar->setValue(20);
//    QLabel  *percent = new QLabel(QString::fromLocal8Bit("进度"));
//    percent->setObjectName(QString::fromLocal8Bit("dl_percent"));
    QPushButton *stopbtn = new QPushButton(QString::fromLocal8Bit("暂停"));
    stopbtn->setObjectName(QString::fromLocal8Bit("dl_stopbtn"));
    QPushButton *cancelbtn = new QPushButton(QString::fromLocal8Bit("取消"));
    cancelbtn->setObjectName(QString::fromLocal8Bit("dl_cancelbtn"));
    QPushButton *deletebtn = new QPushButton(QString::fromLocal8Bit("删除"));
    deletebtn->setObjectName(QString::fromLocal8Bit("dl_deletebtn"));
    QPushButton *openbtn = new QPushButton(QString::fromLocal8Bit("打开"));
    openbtn->setObjectName(QString::fromLocal8Bit("dl_openbtn"));
    num->setFixedSize(QSize(30,26));
//    percent->setFixedSize(QSize(30,30));
    progressbar->setMaximumSize(400,26);
    stopbtn->setFixedSize(QSize(30,26));
    deletebtn->setFixedSize(QSize(30,26));
    cancelbtn->setFixedSize(QSize(30,26));
    openbtn->setFixedSize(QSize(30,26));
    QHBoxLayout *hblayout1 = new QHBoxLayout();
    QHBoxLayout *hblayout2 = new QHBoxLayout();
    hblayout2->addWidget(stopbtn);
    hblayout2->addWidget(cancelbtn);
    hblayout2->addWidget(deletebtn);
    hblayout2->addWidget(openbtn);
    hblayout1->addWidget(num);
    hblayout1->addWidget(progressbar);
//    hblayout->addWidget(percent);
    hblayout1->addLayout(hblayout2);
    hblayout1->setSpacing(10);
    hblayout1->setContentsMargins(0,0,0,0);
    QWidget *tempwdt = new QWidget();
    tempwdt->setFixedSize(700,26);
    tempwdt->setLayout(hblayout1);
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(tempwdt->size());
    ui->listWidget_list->addItem(item);
    ui->listWidget_list->setItemWidget(item,tempwdt);
    return true;
}

bool WebDownLoadList::slot_setDownLoadStatus()
{
    return true;
}

bool WebDownLoadList::slot_chandleCancel()
{
    return true;
}


void WebDownLoadList::slot_searchDownloadHirtory(QString text)
{

}

void WebDownLoadList::slot_setDownloadProgressbar(int value)
{

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

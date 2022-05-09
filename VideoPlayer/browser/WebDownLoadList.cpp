#include "WebDownLoadList.h"
#include "ui_WebDownLoadList.h"

WebDownLoadList::WebDownLoadList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebDownLoadList)
{
    ui->setupUi(this);
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
    slot_addDownLoadRecordToList();
}

void WebDownLoadList::chandleSignalsAndSLots()
{
    //新建下载
    connect(ui->pushButton_addrecord,&QPushButton::clicked,[=](){ui->stackedWidget_bottom->setCurrentIndex(1);});
    //返回
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){ui->stackedWidget_bottom->setCurrentIndex(0);});
}

bool WebDownLoadList::slot_addDownLoadRecordToList()
{
    QLabel  *num = new QLabel(QString::fromLocal8Bit("序号"));
    num->setObjectName(QString::fromLocal8Bit("dl_num"));
    QSlider *hslider = new QSlider(Qt::Horizontal);
    hslider->setObjectName(QString::fromLocal8Bit("dl_hslider"));
    QLabel  *percent = new QLabel(QString::fromLocal8Bit("进度"));
    percent->setObjectName(QString::fromLocal8Bit("dl_percent"));
    QPushButton *stopbtn = new QPushButton(QString::fromLocal8Bit("暂停"));
    stopbtn->setObjectName(QString::fromLocal8Bit("dl_stopbtn"));
    QPushButton *cancelbtn = new QPushButton(QString::fromLocal8Bit("取消"));
    cancelbtn->setObjectName(QString::fromLocal8Bit("dl_cancelbtn"));
    QPushButton *deletebtn = new QPushButton(QString::fromLocal8Bit("删除"));
    deletebtn->setObjectName(QString::fromLocal8Bit("dl_deletebtn"));
    QPushButton *openbtn = new QPushButton(QString::fromLocal8Bit("打开"));
    openbtn->setObjectName(QString::fromLocal8Bit("dl_openbtn"));
    num->setFixedSize(QSize(30,30));
    percent->setFixedSize(QSize(30,30));
    hslider->setMinimumSize(225,30);
    stopbtn->setFixedSize(QSize(30,30));
    deletebtn->setFixedSize(QSize(30,30));
    cancelbtn->setFixedSize(QSize(30,30));
    openbtn->setFixedSize(QSize(30,30));
    QHBoxLayout *hblayout = new QHBoxLayout();
    hblayout->addWidget(num);
    hblayout->addWidget(hslider);
    hblayout->addWidget(percent);
    hblayout->addWidget(stopbtn);
    hblayout->addWidget(cancelbtn);
    hblayout->addWidget(deletebtn);
    hblayout->addWidget(openbtn);
    hblayout->setSpacing(10);
    hblayout->setContentsMargins(0,0,0,0);
    QWidget *tempwdt = new QWidget();
    tempwdt->setFixedSize(700,30);
    tempwdt->setLayout(hblayout);
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

bool WebDownLoadList::slot_clearHistoryList()
{
    return true;
}

bool WebDownLoadList::slot_setDownLoadConfig()
{
    return true;
}

void WebDownLoadList::slot_searchDownloadHirtory(QString text)
{

}

void WebDownLoadList::on_pushButton_min_clicked()
{
    this->showMinimized();
}

void WebDownLoadList::on_pushButton_close_clicked()
{
    this->hide();
}

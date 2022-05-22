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
    setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(615,400);//记得滚动条的10px宽度
    initWorkUI();
    chandleSignalsAndSLots();
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


void WebDownLoadList::initWorkUI()
{
    ui->lineEdit_search->setPlaceholderText(QString::fromLocal8Bit("搜索下载内容"));
    ui->lineEdit_inputurl->setPlaceholderText(QString::fromLocal8Bit("请输入下载地址,按Enter键下载"));
    ui->listWidget_list->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->stackedWidget->setCurrentIndex(0);
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
        this->hide();
    });
    //返回
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){ui->stackedWidget_bottom->setCurrentIndex(0);});
    //清空列表
    connect(ui->pushButton_clearlist,&QPushButton::clicked,[=](){ ui->listWidget_list->clear(); });
    //下载设置
    connect(ui->pushButton_downsetting,&QPushButton::clicked,[=](){emit sig_setConfig();});
    //停止
    connect(stopbtn,&QPushButton::clicked,[=]()
    {
//        QPushButton *stopbtn = qobject_cast<QPushButton*>(sender());
//        QLabel *num = stopbtn->parentWidget()->findChild<QLabel*>();
//        emit sig_pause(num->text().toInt());
        slot_setStartStatus(stopbtn,m_start);
        qDebug()<< QString::fromLocal8Bit("暂停") << num->text();
    });
}

bool WebDownLoadList::slot_addDownLoadRecordToList()
{
//    QLabel *num = new QLabel(QString::number(m_count));
    num = new QLabel(QString::number(m_count));
    num->setObjectName(QString::fromLocal8Bit("dl_num"));
    num->setAlignment(Qt::AlignCenter);//文字居中
//    QProgressBar *progressbar = new QProgressBar();
    progressbar = new QProgressBar();
    progressbar->setObjectName(QString::fromLocal8Bit("dl_progressbar"));
    progressbar->setValue(0);
//    QPushButton *stopbtn = new QPushButton();
    stopbtn = new QPushButton();
    stopbtn->setObjectName(QString::fromLocal8Bit("dl_stopbtn"));
    stopbtn->setToolTip(QString::fromLocal8Bit("暂停"));
//    QPushButton *downloadlbtn = new QPushButton();
    downloadlbtn = new QPushButton();
    downloadlbtn->setObjectName(QString::fromLocal8Bit("dl_downloadlbtn"));
    downloadlbtn->setToolTip(QString::fromLocal8Bit("下载"));
//    QPushButton *deletebtn = new QPushButton();
    deletebtn = new QPushButton();
    deletebtn->setObjectName(QString::fromLocal8Bit("dl_deletebtn"));
    deletebtn->setToolTip(QString::fromLocal8Bit("删除"));
//    QPushButton *openbtn = new QPushButton();
    openbtn = new QPushButton();
    openbtn->setObjectName(QString::fromLocal8Bit("dl_openbtn"));
    openbtn->setToolTip(QString::fromLocal8Bit("打开文件"));
    num->setFixedSize(QSize(26,26));
    progressbar->setFixedSize(360,18);
    stopbtn->setFixedSize(QSize(18,18));
    deletebtn->setFixedSize(QSize(18,18));
    downloadlbtn->setFixedSize(QSize(18,18));
    openbtn->setFixedSize(QSize(18,18));
//    QHBoxLayout *hblayout1 = new QHBoxLayout();
    hblayout1 = new QHBoxLayout();
//    QHBoxLayout *hblayout2 = new QHBoxLayout();
    hblayout2 = new QHBoxLayout();
    hblayout2->addWidget(stopbtn);//暂停
    hblayout2->addWidget(downloadlbtn);//下载
    hblayout2->addWidget(deletebtn);//删除
    hblayout2->addWidget(openbtn);//打开
    hblayout2->setSpacing(10);
    hblayout1->addWidget(num);//序号
    hblayout1->addWidget(progressbar);//进度条
    hblayout1->addSpacerItem(new QSpacerItem(5, 18, QSizePolicy::Fixed));//最小 30 26，可扩大
    hblayout1->addLayout(hblayout2);//操作按钮
    hblayout1->addSpacerItem(new QSpacerItem(5,18,QSizePolicy::Fixed));//右边界固定
//    QWidget *tempwdt = new QWidget();
    tempwdt = new QWidget();
    tempwdt->setFixedSize(600,40);
    tempwdt->setLayout(hblayout1);
    tempwdt->layout()->setContentsMargins(0,0,0,0);
    tempwdt->layout()->setMargin(0);
//    QListWidgetItem *item = new QListWidgetItem();
    item = new QListWidgetItem();
    item->setSizeHint(tempwdt->size());
    ui->listWidget_list->addItem(item);
    ui->listWidget_list->setItemWidget(item,tempwdt);
    m_count++;
    return true;
}

void WebDownLoadList::slot_searchDownloadHirtory(QString text)
{

}

void WebDownLoadList::slot_setDownloadProgressbar(qint64 bytesReceived, qint64 bytesTotal)
{
    progressbar->setValue(bytesReceived*100/bytesTotal);
    if(bytesReceived*100/bytesTotal == 100)
    {
        emit sig_receiveFinished();
        qDebug() <<QString::fromLocal8Bit("下载完成信号已发出！");
    }
}

void WebDownLoadList::slot_receivedNewWorkFinished()
{
    qDebug() << QString::fromLocal8Bit("任务栏已经收到下载结束信号！");
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

//打开文件
void WebDownLoadList::slot_receiveData_openFile(const QString &filepath)
{
    QFileDialog::getOpenFileNames(this,//不指定父窗口，设置自己的样式
                                  QString::fromLocal8Bit("选择文件"),
                                  filepath,
                                  QString::fromLocal8Bit("Videos(*avi *mp4 *flv *mp3 *wmv)"),
                                                         0);
}

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
    ui->listWidget_list->installEventFilter(this);
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

void WebDownLoadList::slot_findFileFromLineEdit(QString name)
{
    name.remove(QRegExp("\\s"));
    if(name.isEmpty())
    {
        for(int i = 0; i < ui->listWidget_list->model()->rowCount(); i++)
            ui->listWidget_list->setRowHidden(i,false);

    }
    else
    {
        for(int i = 0; i <ui->listWidget_list->model()->rowCount(); i++)
        {
            ui->listWidget_list->setRowHidden(i,true);
            QString curname = "";
            QAbstractItemModel *model = ui->listWidget_list->model();
            QModelIndex index;
            for(int j = 0; j <ui->listWidget_list->model()->columnCount(); j++)
            {
                index = model->index(i,j);
                curname += model->data(index).toString();
            }
            curname.remove(QRegExp("\\s"));
            if(curname.contains(name,Qt::CaseInsensitive)) //CaseSensitive:敏感
               ui->listWidget_list->setRowHidden(i,false);
        }
    }
}

void WebDownLoadList::slot_receiveThreadStarted()
{
    qDebug() << QString::fromLocal8Bit("线程开始！");
}

void WebDownLoadList::slot_receiveThreadFinished()
{
    qDebug() << QString::fromLocal8Bit("线程结束！");
}

//删除已经下载完成的item
void WebDownLoadList::slot_itemRemove(DownLoadItem *item)
{
//    注意删除顺序，先删除itemWidget,再删除listwidgetitem,最后释放内存
//    方法1：根据鼠标得到item
//    QListWidget删除一个item,会自动对索引进行排序，且索引是连续的。
//    QPoint pPoint = ui->listWidget_list->mapFromGlobal(QCursor::pos());
//    auto item = ui->listWidget_list->itemAt(pPoint);
//    ui->listWidget_list->removeItemWidget(item);

//    方法2：对比m_downLoadItem的指针（地址），一样则删除

//    方法3：传this指针（地址），一样则删除
    if(0 < ui->listWidget_list->count())
    {
        for(int i = 0; i < ui->listWidget_list->count();i++)
        {
          QListWidgetItem *item_tmp =  ui->listWidget_list->item(i);
          if(item = (DownLoadItem *)(ui->listWidget_list->itemWidget(item_tmp)))
          {
              ui->listWidget_list->removeItemWidget(item_tmp);
              item->deleteLater();
          }
        }
    }

}

void WebDownLoadList::slot_freeItem(QListWidget *listWidget,QWidget *itemWidget,QListWidgetItem *item)
{
    //注意删除顺序，先删除itemWidget，再删除QListWidgetItem，最后释放内存空间
    itemWidget->deleteLater();
    listWidget->takeItem(listWidget->row(item));
    delete item;
    if(listWidget->count() == 0)
        ui->stackedWidget_center->setCurrentIndex(1);
}

WebDownLoadList::~WebDownLoadList()
{
    delete ui;
    if(m_pInstance != nullptr)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }

    if(m_workThread != nullptr)
    {
        m_workThread->quit();
    }
    m_workThread->wait();
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
    ui->stackedWidget_center->setCurrentIndex(1);
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
    //自定义下载---返回
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){ui->stackedWidget_bottom->setCurrentIndex(0);});
    //清空下载记录列表
    connect(ui->pushButton_clearlist,&QPushButton::clicked,[=](){ ui->listWidget_list->clear();ui->stackedWidget_center->setCurrentIndex(1);});
    //下载设置（存储目录）
    connect(ui->pushButton_downsetting,&QPushButton::clicked,[=](){emit sig_setConfig();});
    //搜索下载记录
    connect(ui->lineEdit_search,&QLineEdit::textChanged,[=](QString str){slot_findFileFromLineEdit(str);});
}

//收到下载信号，创建下载列表任务，列表添加一条下载记录
bool WebDownLoadList::slot_addDownLoadRecordToList(const QUrl &url, const QString &filename, const QString &savepath,bool openStatus)
{
    QFileInfo info(url.toString()); qDebug() <<QString::fromLocal8Bit("接收到---url:")<<url;
    m_fileSuffix = info.suffix();   qDebug() <<QString::fromLocal8Bit("接收到---后缀:")<<m_fileSuffix;
    m_fileSize   = info.size();     qDebug() <<QString::fromLocal8Bit("接收到---文件大小:")<<m_fileSize;
    m_fileName   = filename;        qDebug() <<QString::fromLocal8Bit("接收到---文件名:")<<m_fileName;
    m_filePath = savepath + "/" + filename;  qDebug() <<QString::fromLocal8Bit("接收到---存储路径:")<<m_filePath;
    ui->stackedWidget_center->setCurrentIndex(0);

    //00:创建线程 01.创建工作 02.开始线程
    slot_createNewDownloadWork();//必须在关联之前创建
    //收到下载信号，创建线程下载
    QListWidgetItem *m_workItem   = new QListWidgetItem(filename);//有字，颜色为透明，看不见，便于搜索
    DownLoadItem *m_downLoadItem  = new DownLoadItem(url,filename,savepath,openStatus);
    m_worker->slot_receiveData_accept(url,filename,savepath);//创建变量必须在使用之前（比如有信号链接）
    //堆变量每次分配不同的地址
    qDebug() <<QString::fromLocal8Bit("新分配DownLoadItem堆变量地址：") << m_downLoadItem;
    qDebug() <<QString::fromLocal8Bit("新分配线程变量地址：") << m_worker;
    m_workItem->setSizeHint(m_downLoadItem->size());
    ui->listWidget_list->insertItem(0,m_workItem);
    ui->listWidget_list->setItemWidget(m_workItem,m_downLoadItem);
    ui->stackedWidget_center->setCurrentIndex(0);
    //有关文件操作的信号与槽函数
    connect(m_workThread,&QThread::finished,m_worker,&QObject::deleteLater);//线程结束时，自动删除
    connect(m_workThread,&QThread::finished,m_workThread,&QThread::deleteLater);//线程结束时，线程内对象自动删除
    connect(m_workThread,&QThread::started,this,&WebDownLoadList::slot_receiveThreadStarted);//打印以下线程完毕是否结束
    connect(m_workThread,&QThread::finished,this,&WebDownLoadList::slot_receiveThreadFinished);//打印以下线程完毕是否结束了
    //关联文件下载进度
    connect(m_worker,SIGNAL(sig_receiveData_progressbar(qint64,qint64)),m_downLoadItem,SLOT(slot_setItemDownProgress(qint64,qint64)));
    //文件完成提示音
    connect(m_worker,&Worker::sig_receiveData_finished,m_downLoadItem,&DownLoadItem::slot_receive_finished);
    //继续/暂停
    connect(m_downLoadItem,SIGNAL(sig_downloadStatus(int,bool)),m_worker,SLOT(slot_receiveData_pause(int,bool)));
    //取消
    connect(m_downLoadItem,SIGNAL(sig_download_cancel(int)),m_worker,SLOT(slot_receiveData_cancel(int)));
    //删除
    connect(m_downLoadItem,SIGNAL(sig_download_delete(int)),m_worker,SLOT(slot_receiveData_deleteWork(int)));
    //重新下载
    connect(m_downLoadItem,SIGNAL(sig_download_reload(int)),m_worker,SLOT(slot_receiveData_itemReDownload(int)));
    //从列表中删除任务
    connect(m_downLoadItem,&DownLoadItem::sig_download_deleteItem,[=](){slot_freeItem(ui->listWidget_list,m_downLoadItem,m_workItem);});
    return true;
}

void WebDownLoadList::slot_searchDownloadHirtory(QString text)
{

}

//创建线程以及工作对象
void WebDownLoadList::slot_createNewDownloadWork()
{
    //01.工作处理对象
    m_worker = new Worker();
    //02.创建一个新的线程对象
    m_workThread = new QThread();
    m_worker->moveToThread(m_workThread);
    m_workThread->start();
    qDebug() << QString::fromLocal8Bit("新的线程已经启动！") << QString::fromLocal8Bit("新的线程地址=")<< m_workThread;
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

bool WebDownLoadList::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched,event);
}

void WebDownLoadList::on_pushButton_min_clicked()
{
    this->showMinimized();
}

void WebDownLoadList::on_pushButton_close_clicked()
{
    this->hide();
}



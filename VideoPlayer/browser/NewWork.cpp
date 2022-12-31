#include "NewWork.h"
#include "ui_NewWork.h"
#include <QDebug>
#include <QDateTime>
#include <QFileInfo>
#include <QScrollBar>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QWebEngineDownloadItem>

NewWork* NewWork::m_pInstance = nullptr;

NewWork::NewWork(QWidget *parent) :
    QDialog(parent),
    m_count(0),
    ui(new Ui::NewWork)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("添加新任务"));
    setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
    this->setFixedSize(450,230);//记得滚动条的10px宽度
    initWorkUI();
    chandleSignalsAndSlots();
}

NewWork::~NewWork()
{
    delete ui;
    if(m_pInstance != nullptr)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }   
}

NewWork *NewWork::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new NewWork();
    }
    return m_pInstance;
}

void NewWork::initWorkUI()
{
    ui->lineEdit_savepath->setText(Global::appDirPath + QString::fromLocal8Bit("/download"));//默认的路径
    ui->lineEdit_savepath->setToolTip(Global::appDirPath + QString::fromLocal8Bit("/download"));
    ui->lineEdit_savepath->setCursorPosition(0);
    m_clearBtn = new QPushButton(QString::fromLocal8Bit("清除历史记录"));
    m_clearBtn->setObjectName(QString::fromLocal8Bit("newwork_m_clearBtn"));
    m_clearBtn->setFixedHeight(26);

    m_listWdgt_path = new QListWidget();
    m_listWdgt_path->setObjectName(QString::fromLocal8Bit("newwork_m_listWdgt_path"));
    m_listWdgt_path->setFixedWidth(375);
    m_listWdgt_path->setFixedHeight(65);
    m_listWdgt_path->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWdgt_path->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QHBoxLayout *m_hbLayout = new QHBoxLayout();
    m_hbLayout->addWidget(m_clearBtn);
    m_hbLayout->addStretch();
    m_hbLayout->setContentsMargins(0,0,0,0);
    m_hbLayout->setSpacing(0);
    QVBoxLayout *m_vbLayout = new QVBoxLayout();
    m_vbLayout->setObjectName(QString::fromLocal8Bit("m_vbLayout"));
    m_vbLayout->setContentsMargins(0,0,0,0);
    m_vbLayout->setSpacing(0);
    m_vbLayout->addWidget(m_listWdgt_path);
    m_vbLayout->addLayout(m_hbLayout);

    m_hisWdgt = new QWidget();
    m_hisWdgt->setObjectName(QString::fromLocal8Bit("newwork_m_hisWdgt"));
    m_hisWdgt->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    m_hisWdgt->installEventFilter(this);
    m_hisWdgt->setLayout(m_vbLayout);
    m_hbLayout->layout()->setContentsMargins(0,0,0,0);
    m_hbLayout->layout()->setSpacing(0);

    m_fileSize = new QAction(QString::fromLocal8Bit("文件大小"));
    m_fileSize->setObjectName(QString::fromLocal8Bit("m_fileSize"));

    m_spaceSize = new QAction(QString::fromLocal8Bit("剩余空间"));
    m_spaceSize->setObjectName(QString::fromLocal8Bit("m_spaceSize"));

//    ui->lineEdit_filename->addAction(QIcon("://images/function/download_delete.png"),QLineEdit::TrailingPosition);
//    ui->lineEdit_savepath->addAction(QIcon("://images/function/download_delete.png"),QLineEdit::TrailingPosition);
    ui->lineEdit_address->setReadOnly(true);//目的是不让编辑
    ui->pushButton_download->setDefault(true);//默认直接下载
}

void NewWork::chandleSignalsAndSlots()
{
    connect(m_fileSize,&QAction::triggered,[=](){ qDebug() << QString::fromLocal8Bit("文件大小");});
    connect(m_spaceSize,&QAction::triggered,[=](){ qDebug() << QString::fromLocal8Bit("剩余空间");});
    connect(ui->pushButton_his,&QPushButton::clicked,this,&NewWork::slot_updateShowListPathWidget);
    connect(m_clearBtn,&QPushButton::clicked,[=](){m_listWdgt_path->clear();});
    //向外部发射含有下载信息的信号供外部使用
    connect(this,SIGNAL(sig_download(QUrl,QString,QString,bool)),WebDownLoadList::getInstance(),SLOT(slot_addDownLoadRecordToList(QUrl,QString,QString,bool)));

    //确定下载并打开,打开状态为true
    connect(ui->pushButton_dlandopen,&QPushButton::clicked,[=](){
        //确定下载并打开（下载地址--文件名--保存路径）
        emit sig_download(ui->lineEdit_address->text().trimmed(),ui->lineEdit_filename->text().replace(" ","_"),ui->lineEdit_savepath->text(),true);
        qDebug() << QString::fromLocal8Bit("下载网址：") << ui->lineEdit_address->text().trimmed();
        qDebug() << QString::fromLocal8Bit("文件名称：") << ui->lineEdit_filename->text().replace(" ","_");
        qDebug() << QString::fromLocal8Bit("保存地址：") << ui->lineEdit_savepath->text();
        this->hide();
    });
    //确定下载---确定按钮点击
    connect(ui->pushButton_download,&QPushButton::clicked,[=](){
        qDebug() <<QString::fromLocal8Bit("当前UI线程id:") << QThread::currentThreadId();
        //确定下载（下载地址--文件名--保存路径）
        emit sig_download(ui->lineEdit_address->text().trimmed(),ui->lineEdit_filename->text().replace(" ","_"),ui->lineEdit_savepath->text(),false);
        qDebug() << QString::fromLocal8Bit("下载网址：") << ui->lineEdit_address->text().trimmed();
        qDebug() << QString::fromLocal8Bit("文件名称：") << ui->lineEdit_filename->text().replace(" ","_");
        qDebug() << QString::fromLocal8Bit("保存地址：") << ui->lineEdit_savepath->text();
        this->hide();
    });

    //下载列表自建下载请求--回车--弹出对话框--上显下载信息
    connect(WebDownLoadList::getInstance(),&WebDownLoadList::sig_newDownloadRequest,[=](QString address){
        slot_receiveDownloadRequested(address);//弹出选择对话框
    });

    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        emit sig_cancel();this->close();
    });
    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){
        emit  sig_cancel();this->hide();
    });
    //选择存储文件夹
    connect(ui->pushButton_lookin,&QPushButton::clicked,[=](){
        QString path = openLocalFileSystem();
        if(path.isEmpty()) return;
        ui->lineEdit_savepath->setText(path);
        m_savePath = ui->lineEdit_savepath->text()+"/"+m_fileName;
        slot_addPathToList(path);
    });

    //单击回显选择的文字
    connect(m_listWdgt_path,&QListWidget::itemClicked,[=](QListWidgetItem *item)
    {
        slot_setLineEditText(ui->lineEdit_savepath,item->text());//上显的同时m_savePath也改变
    });
    //文件名改变（用户修改）
    connect(ui->lineEdit_filename,&QLineEdit::textChanged,[=](QString text){
        m_fileName = text;
        ui->lineEdit_filename->setText(text);
        ui->lineEdit_filename->setToolTip(text);
    });

    //存储路径改变
    connect(ui->lineEdit_savepath,&QLineEdit::textChanged,[=](QString text){
        m_savePath = text + "/" + m_fileName;
        if(isFileExist(m_savePath))//指定路径下存在同名文件
        {
            QString reName = QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + m_fileName;
//            m_fileName = reName;
            ui->lineEdit_filename->setText(reName);//加上当前时间
            ui->lineEdit_filename->setToolTip(reName);
            ui->lineEdit_filename->setCursorPosition(0);
        }
        else
        {
            ui->lineEdit_filename->setText(m_fileName);//加上当前时间
            ui->lineEdit_filename->setToolTip(m_fileName);
            ui->lineEdit_filename->setCursorPosition(0);
        }
        ui->lineEdit_savepath->setToolTip(text);
        ui->lineEdit_filename->setCursorPosition(0);
    });
}

//收到浏览器点击下载请求---弹出对话框
void NewWork::slot_receiveDownloadRequested(QWebEngineDownloadItem *item)
{
    qDebug() << QString::fromLocal8Bit("已接收到请求...");
    qDebug() << QString::fromLocal8Bit("请求地址：") << item->url().toString();
    QFileInfo info(item->url().toString());
    //pos截取不到，返回-1，截取到，返回具体的位置
    int pos = item->url().toString().indexOf("?");//以从左往右第一个?的位置往左边截取
//    qDebug() << QString::fromLocal8Bit("截取的位置：") << pos;
    QString t_fileName = item->url().toString().left(pos);
    QFileInfo t_info(t_fileName);
    ui->lineEdit_address->setText(item->url().toString());
    ui->lineEdit_address->setToolTip(item->url().toString());
    ui->lineEdit_address->setCursorPosition(0);
    //文件名中的空格使用_代替
    ui->lineEdit_filename->setText(t_info.fileName().replace(" ","_"));
    ui->lineEdit_filename->setCursorPosition(0);
    ui->lineEdit_filename->setToolTip(t_info.fileName().replace(" ","_"));
    m_fileName = t_info.fileName().replace(" ","_");
    m_savePath = QString(ui->lineEdit_savepath->text() + "/" + m_fileName);
    m_fileUrl = item->url();
    this->setWindowModality(Qt::ApplicationModal);
    this->show();

     if(isFileExist(m_savePath))//指定路径下存在同名文件
     {
         QString reName = QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + info.fileName();
//         m_fileName = reName;
         ui->lineEdit_filename->setText(reName);//加上当前时间
         ui->lineEdit_filename->setToolTip(reName);
         ui->lineEdit_filename->setCursorPosition(0);
     }
     qDebug() <<QString::fromLocal8Bit("QWebEngineDownloadItem下，下载保存路径为：") << m_savePath;
}

//收到自建的连接请求---弹出对话框
void NewWork::slot_receiveDownloadRequested(const QUrl url)
{
    qDebug() << QString::fromLocal8Bit("已接收到请求...");
    qDebug() << QString::fromLocal8Bit("请求地址：") << url.toString();
    QFileInfo info(url.toString());
    //pos截取不到，返回-1，截取到，返回具体的位置
    int pos = url.toString().indexOf("?");
    QString t_fileName = url.toString().left(pos);
    QFileInfo t_info(t_fileName);
    ui->lineEdit_address->setText(url.toString());
    ui->lineEdit_address->setToolTip(url.toString());
    ui->lineEdit_address->setCursorPosition(0);
    //下载文件名不能有空格
    ui->lineEdit_filename->setText(t_info.fileName());
    ui->lineEdit_address->setToolTip(t_info.fileName());
    ui->lineEdit_filename->setCursorPosition(0);
    m_fileName = t_info.fileName();
    m_savePath = QString(ui->lineEdit_savepath->text() + "/" + m_fileName);
    m_fileUrl = url;

    this->setWindowModality(Qt::ApplicationModal);
    this->show();

    if(isFileExist(m_savePath))//指定路径下存在同名文件
    {
        QString reName = QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + info.fileName();
        ui->lineEdit_filename->setText(reName);//加上当前时间
        ui->lineEdit_filename->setToolTip(reName);
        ui->lineEdit_filename->setCursorPosition(0);
    }
    qDebug() <<QString::fromLocal8Bit("QUrl下，下载保存路径为：") << m_savePath;
}

QString NewWork::openLocalFileSystem()
{
    QString fpath = QFileDialog::getExistingDirectory(this,
                                                QString::fromLocal8Bit("选择路径"),
                                                QString::fromLocal8Bit("C:\\Users\\24939\\Desktop"));
    if(!fpath.isEmpty())//不为空
    {
        return fpath;
    }
}

bool NewWork::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_hisWdgt)
    {
        if(event->type() == QEvent::Leave)
        {
            m_hisWdgt->hide();
        }
    }
    return QDialog::eventFilter(watched,event);
}

void NewWork::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_mvPos = event->globalPos() - this->pos();
}

void NewWork::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    this->move(event->globalPos() - m_mvPos);
}

//判断指定路径下文件是否存在
bool NewWork::isFileExist(QString fullFileName)
{
    QFile file(fullFileName);
    if(file.exists())
    {
        qDebug() <<QString::fromLocal8Bit("文件已经存在");
        return true;
    }
    else
    {
        qDebug() <<QString::fromLocal8Bit("文件不存在");
        return false;
    }
}

bool NewWork::slot_judgePathExist(const QString &path)
{
    for(int i = 0; i < m_listWdgt_path->count(); i++)
    {
        if(path == m_listWdgt_path->item(i)->text())
            return true;//存在
    }
    return false;//不存在
}

void NewWork::slot_updateShowListPathWidget()
{
    if(m_hisWdgt)
    {
       if(m_hisWdgt->isHidden())
       {
           int x = ui->lineEdit_savepath->parentWidget()->mapToGlobal(ui->lineEdit_savepath->pos()).x();
           int y = ui->lineEdit_savepath->parentWidget()->mapToGlobal(ui->lineEdit_savepath->pos()).y();
           m_hisWdgt->setGeometry(x,y + ui->lineEdit_savepath->height(),
                                   m_listWdgt_path->width(),m_listWdgt_path->height());
           m_hisWdgt->show();
       }
       else
       {
           m_hisWdgt->hide();
       }
    }
}

void NewWork::slot_receiveWorkerFinished()
{
    qDebug() << QString::fromLocal8Bit("第%1个任务下载结束").arg(m_count);
}

void NewWork::slot_addPathToList(const QString &path)
{
    if(path.isEmpty()) return;
    bool exist = slot_judgePathExist(path);
    if(!exist)
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon("://images/function/new_disc.png"),path);
        m_listWdgt_path->addItem(item);
    }
    else
    {
        return;
    }
}

void NewWork::slot_setLineEditText(QLineEdit *edit, const QString &text)
{
    edit->setText(text);
    edit->setCursorPosition(0);//字符串过长时，显示的依旧是最左端文字
    m_savePath = ui->lineEdit_savepath->text()+"/"+m_fileName;//重新设置m_savePath
}

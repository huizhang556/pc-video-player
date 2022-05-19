#include "NewWork.h"
#include "ui_NewWork.h"
#include <QDebug>
#include <QFileInfo>
#include <QScrollBar>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QWebEngineDownloadItem>

NewWork* NewWork::m_pInstance = nullptr;

NewWork::NewWork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewWork)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("添加新任务"));
    setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
    this->setFixedSize(450,226);//记得滚动条的10px宽度
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

void NewWork::initWorkUI()
{
    ui->lineEdit_savepath->setText(QString::fromLocal8Bit("C:/Users/24939/Downloads"));//默认的路径

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
}

void NewWork::chandleSignalsAndSlots()
{
    connect(m_fileSize,&QAction::triggered,[=](){ qDebug() << QString::fromLocal8Bit("文件大小");});
    connect(m_spaceSize,&QAction::triggered,[=](){ qDebug() << QString::fromLocal8Bit("剩余空间");});
    connect(ui->pushButton_his,&QPushButton::clicked,this,&NewWork::slot_updateShowListPathWidget);
    connect(m_clearBtn,&QPushButton::clicked,[=](){m_listWdgt_path->clear();});
    connect(ui->pushButton_close,&QPushButton::clicked,[=]()
    {
        emit sig_cancel();
        this->close();
    });
    connect(ui->pushButton_lookin,&QPushButton::clicked,[=]()
    {
        QString path = openLocalFileSystem();
        if(path.isEmpty()) return;
        ui->lineEdit_savepath->setText(path);
        slot_addPathToList(path);
    });
    connect(ui->pushButton_download,&QPushButton::clicked,[=]()
    {
        //确认下载将文件名和保存地址传过去
        emit sig_download(ui->lineEdit_filename->text(),ui->lineEdit_savepath->text());
        qDebug() << "emit sig_download(true);" << QString::fromLocal8Bit("确认下载");
    });
    connect(ui->pushButton_cancel,&QPushButton::clicked,[=]()
    {
        emit  sig_cancel();
        qDebug() << "emit sig_download(false);" << QString::fromLocal8Bit("取消下载");
        this->hide();
    });
    connect(ui->pushButton_dlandopen,&QPushButton::clicked,[=]()
    {
        emit sig_downloadOpen();
        qDebug() << "emit sig_downloadOpen();";
    });

    //单击回显选择的文字
    connect(m_listWdgt_path,&QListWidget::itemClicked,[=](QListWidgetItem *item)
    {
        slot_setLineEditText(ui->lineEdit_savepath,item->text());
    });
}

//收到请求---弹出对话框
void NewWork::slot_receiveDownloadRequested(QWebEngineDownloadItem *item)
{
    qDebug() << QString::fromLocal8Bit("已接收到请求...");
    qDebug() << QString::fromLocal8Bit("请求地址：") << item->url().toString();
    QFileInfo info(item->url().toString());
    ui->lineEdit_address->setText(item->url().toString());
    ui->lineEdit_address->setCursorPosition(0);
    ui->lineEdit_filename->setText(info.fileName());
    ui->lineEdit_filename->setCursorPosition(0);
    item->setPath(Global::appDirPath + "/download/" + info.fileName());
    qDebug() <<QString::fromLocal8Bit("下载保存路径为：") << Global::appDirPath + "/download/" + info.fileName();
    item->accept();
//    this->setWindowModality(Qt::ApplicationModal);
//    this->show();
}

NewWork *NewWork::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new NewWork();
    }
    return m_pInstance;
}

QString NewWork::openLocalFileSystem()
{
    QString fpath = QFileDialog::getExistingDirectory(this,
                                                QString::fromLocal8Bit("选择路径"),
                                                QString::fromLocal8Bit("C:\\Users\\24939\\Desktop"));
    if(!fpath.isEmpty())//不为空
    {
//        fpath = fpath + QString(tr("/"));
        return fpath;
    }
    else
    {
        return false;//打开不选择有问题
    }
}

void NewWork::slot_receivedNewWorkInfo(const QString &adress, const QString &filename)
{
    if(adress.isEmpty()) return;
    if(filename.isEmpty()) return;


}


//下载过程
//void NewWork::slot_downLoad_progress(qint64 bytesReceived, qint64 bytesTotal)
//{
//    qDebug() << QString::fromLocal8Bit("已接受数据：")<<bytesReceived << QString::fromLocal8Bit("百分比：%1%").arg((bytesReceived*100)/bytesTotal)  << QString::fromLocal8Bit("文件总大小：") << bytesTotal;
//}

//下载结束
//void NewWork::slot_downLoad_finished()
//{
//    qDebug() <<QString::fromLocal8Bit("下载结束！");
//}

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
    Q_UNUSED(event);
    QPoint winPos = this->pos();//界面位置
    QPoint nowPos = event->globalPos();//鼠标位置
    m_mvPos = nowPos - winPos;
}

void NewWork::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->move(event->globalPos() - m_mvPos);
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
}

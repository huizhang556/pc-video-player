#include "DownLoadItem.h"
#include "ui_DownLoadItem.h"
#include <QDebug>

DownLoadItem::DownLoadItem(QWidget *parent):
    QWidget(parent)
{
    ui->setupUi(this);
    ui->setupUi(this);
    setFixedSize(600,40);
    initWorkUI();
    chandleSignalsAndSlots();
}

DownLoadItem::DownLoadItem(QUrl url, QString fileName, QString path, bool open, QWidget *parent) :
    QWidget(parent),
    m_open(open),
    m_start(true),
    m_fileUrl(url.toString()),
    m_fileName(fileName),
    m_savePath(path),
    ui(new Ui::DownLoadItem)
{
    ui->setupUi(this);
    setFixedSize(600,40);
    initWorkUI();
    chandleSignalsAndSlots();
    slot_receive_start();
}

DownLoadItem::~DownLoadItem()
{
    delete ui;
}

void DownLoadItem::initWorkUI()
{
    ui->stackedWidget_progressbar->setCurrentIndex(0);
    ui->stackedWidget_control->setCurrentIndex(0);
    ui->progressBar->setValue(0);
    ui->pushButton_dl_pause->setToolTip(QString::fromLocal8Bit("暂停任务"));
    setItemDownloadStatus(m_start);
    ui->pushButton_dl_cancel->setToolTip(QString::fromLocal8Bit("取消任务"));
    ui->pushButton_dl_delete->setToolTip(QString::fromLocal8Bit("删除任务"));
    ui->pushButton_dl_openfile->setToolTip(QString::fromLocal8Bit("打开目录"));
    ui->pushButton_dl_redown->setToolTip(QString::fromLocal8Bit("重新下载"));
    ui->pushButton_dl_deleteItem->setToolTip(QString::fromLocal8Bit("从列表中删除"));
}

void DownLoadItem::chandleSignalsAndSlots()
{
    //暂停/开始
    connect(ui->pushButton_dl_pause,&QPushButton::clicked,[=](){setItemDownloadStatus(m_start); emit sig_downloadStatus(m_start);});
    //取消下载
    connect(ui->pushButton_dl_cancel,&QPushButton::clicked,[=](){emit sig_download_cancel();});
    //删除任务
    connect(ui->pushButton_dl_delete,&QPushButton::clicked,[=](){emit sig_download_delete();});
    //打开文件所在路径
    connect(ui->pushButton_dl_openfile,&QPushButton::clicked,[=](){openLocalFileSaveDirectory(m_savePath);});
    //重新下载
    connect(ui->pushButton_dl_redown,&QPushButton::clicked,[=](){emit sig_download_reload();});
    //删除视图item
    connect(ui->pushButton_dl_deleteItem,&QPushButton::clicked,[=](){emit sig_download_deleteItem();});
    connect(ui->pushButton_dl_deleteItem,SIGNAL(clicked(bool)),this,SLOT(slot_judgeDeleteWorkItem()));//必须使用Qt4方式连接
}

void DownLoadItem::setItemDownloadStatus(bool status)
{
    if(status)
    {
        ui->pushButton_dl_pause->setStyleSheet("#pushButton_dl_pause{"
                                               "border-image: url(:/images/function/download_pause.png);"
                                               "}");
        ui->pushButton_dl_pause->setToolTip(QString::fromLocal8Bit("暂停"));
    }
    else
    {
        ui->pushButton_dl_pause->setStyleSheet("#pushButton_dl_pause{"
                                               "border-image: url(://images/function/download_start.png);"
                                               "}");
        ui->pushButton_dl_pause->setToolTip(QString::fromLocal8Bit("继续"));
    }
    m_start = !m_start;
}

void DownLoadItem::slot_setItemIcon()
{
    QFileInfo info(m_fileUrl);
    m_fileType = info.suffix();
    setItemFileType(m_fileType);
}

QString DownLoadItem::calCurrentItemLoadedSize(qint64 bytesReceived)
{
    //bytesReceived按字节数统计的
    if(0 <= bytesReceived < 1024)//B
    {
        return QString::number(bytesReceived)+"B";
    }
    else if(1024 <= bytesReceived < (1024*1024))//KB 1024*1024=1048576
    {
        QString KB = QString::number(bytesReceived/1024);
        return KB + "KB";
    }
    else if((1024*1024) <= bytesReceived < (1024*1024*1024))//MB 1024*1024*1024=1073741824
    {
        QString MB = QString::number(bytesReceived/(1024*1024));
        return MB + "MB";
    }
    else if((1024*1024*1024) <= bytesReceived < (1024*1024*1024*1024))//GB
    {
        QString GB = QString::number(bytesReceived/(1024*1024*1024));
        return GB + "GB";
    }
    else
    {
        return "unknow size";
    }
}

QString DownLoadItem::calCurrentItemSize(qint64 bytesTotal)
{
    //bytesTotal按字节计，number不四舍五入
    if(0 <= bytesTotal < 1024)//B
    {
        return QString::number(bytesTotal)+"B";
    }
    else if(1024 <= bytesTotal < (1024*1024))//KB
    {
        QString KB = QString::number(bytesTotal/1024);
        return KB + "KB";
    }
    else if((1024*1024) <= bytesTotal < (1024*1024*1024))//MB
    {
        QString MB = QString::number(bytesTotal/(1024*1024));
        return MB + "MB";
    }
    else if((1024*1024*1024) <= bytesTotal < 1024*1024*1024*1024)//GB
    {
        QString GB = QString::number(bytesTotal/(1024*1024*1024));
        return GB + "GB";
    }
    else
    {
        return "unknow size";
    }
}

bool DownLoadItem::setItemFileType(const QString &suffix)
{
    if("pdf" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_pdf.png);"
                           "}");
    }
    else if("doc" == suffix ||"docx" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_doc.png);"
                           "}");
    }
    else if("ppt" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_ppt.png);"
                           "}");
    }
    else if("xlsx" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_xlsx.png);"
                           "}");
    }
    else if("html" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_html.png);"
                           "}");
    }
    else if("mp4" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_mp4.png);"
                           "}");
    }
    else if("mp3" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_mp31.png);"
                           "}");
    }
    else if("zip" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_zip.png);"
                           "}");
    }
    else if("png" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_png.png);"
                           "}");
    }
    else if("jpg" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_jpg.png);"
                           "}");
    }
    else if("psd" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_psd.png);"
                           "}");
    }
    else if("rar" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_rar.png);"
                           "}");
    }
    else if("exe" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_exe.png);"
                           "}");
    }
    else if("iso" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_system.png);"
                           "}");
    }
    else if("mov" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_mov.png);"
                           "}");
    }
    else if("txt" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_txt.png);"
                           "}");
    }
    else if("crx" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_crx.png);"
                           "}");
    }
    else if("deb" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_deb.png);"
                           "}");
    }
    else if("deleted" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_deleted.png);"
                           "}");
    }
    else
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_unknow.png);"
                           "}");
    }
    return true;
}

void DownLoadItem::openLocalFileSaveDirectory(const QString &dir)
{
    if(!checkItemFileIsExist(dir+"/"+m_fileName)) return;//不存在
//    QFileDialog::getOpenFileName(this,//不指定父窗口，设置自己的样式
//                                 QString::fromLocal8Bit("选择文件"),
//                                 dir,
//                                 QString::fromLocal8Bit("ALL(*)")
//                                 );
    QProcess process;
    QString filePath = (dir+"/"+m_fileName);//路径有空格不能打开路径
    qDebug() << QString::fromLocal8Bit("打开路径:") << filePath;
    filePath.replace("/", "\\"); // 只能识别 "\"
    QString cmd = QString("explorer.exe /select,\"%1\"").arg(filePath);
    process.startDetached(cmd);
}


//判断删除的是哪个item
void DownLoadItem::slot_judgeDeleteWorkItem()
{
    QPushButton *pButton = qobject_cast<QPushButton*>(sender());
    qDebug() <<  pButton <<pButton->text();
    QWidget *widget = pButton->nativeParentWidget();
    qDebug() << widget->objectName()<<QString::fromLocal8Bit("父亲地址:") << widget;
}

void DownLoadItem::slot_setItemDownProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << QString::fromLocal8Bit("单个item已经接收到数据！");
    slot_setItemByteLoad(bytesReceived,bytesTotal);//下载占比
    ui->progressBar->setValue(bytesReceived*100/bytesTotal);//下载进度
    if(bytesReceived*100/bytesTotal == 100)//表示结束完所有数据
    {
        slot_setItemFileSize(calCurrentItemSize(bytesTotal));
        slot_setItemFileName();
        slot_setItemExistStatus(0);
        slot_receive_openDir(m_open);
        slot_receive_finished();//转换界面,文件信息，文件控制界面
    }
}

void DownLoadItem::slot_setItemByteLoad(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << calCurrentItemLoadedSize(bytesReceived)<<"------"<<calCurrentItemSize(bytesTotal);
    ui->label_prosize->setText(calCurrentItemLoadedSize(bytesReceived) + "/" + calCurrentItemSize(bytesTotal));
}

void DownLoadItem::slot_setItemFileSize(QString size)
{
    ui->label_total->setText(size);//文件总大小
    ui->label_completed->setText(QString::fromLocal8Bit("--完成"));
}

void DownLoadItem::slot_setItemFileName()
{
    ui->label_fileName->setText(m_fileName);
}

void DownLoadItem::slot_setItemExistStatus(int status)
{
//    if(!(status == 0 || status == 1)) return;
    if(status == 0)
    {
        ui->label_completed->setText(QString::fromLocal8Bit("-- 完成"));
    }
    else
    {
        ui->label_completed->setText(QString::fromLocal8Bit("--文件已删除"));
    }
}

bool DownLoadItem::checkItemFileIsExist(QString fullpath)
{
    QFile file(fullpath);
    if(file.exists())
    {
        qDebug() <<QString::fromLocal8Bit("文件已经存在");
        return true;
    }
    else
    {
        qDebug() <<QString::fromLocal8Bit("文件不存在");
        setItemFileType("deleted");//删除图标
        slot_setItemExistStatus(1);//0--存在 1--删除
        return false;
    }
}

void DownLoadItem::slot_receive_start()
{
    //01.设置图标
    slot_setItemIcon();
    //02.设置进度条
    //03.设置接收进度
}

void DownLoadItem::slot_receive_finished()
{
    ui->stackedWidget_progressbar->setCurrentIndex(1);
    ui->stackedWidget_control->setCurrentIndex(1);
    qDebug() << QString::fromLocal8Bit("文件下载已完成！");
}

void DownLoadItem::slot_receive_openDir(bool open)
{
    if(open)
    {
        openLocalFileSaveDirectory(m_savePath);
    }
    else
    {
        return;
    }
}

bool DownLoadItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
//            ui->pushButton_dl_deleteItem->setEnabled(true);
        }
        else if(event->type() == QEvent::Leave)
        {
//            ui->pushButton_dl_deleteItem->setEnabled(false);
        }
    }
    return QWidget::eventFilter(watched,event);
}

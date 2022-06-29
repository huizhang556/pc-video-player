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
    connect(ui->pushButton_dl_pause,&QPushButton::clicked,[=](){setItemDownloadStatus(m_start); emit sig_downloadStatus(getItemOrder(),m_start);});
    //取消下载
    connect(ui->pushButton_dl_cancel,&QPushButton::clicked,[=](){emit sig_download_cancel(getItemOrder());});
    //删除任务
    connect(ui->pushButton_dl_delete,&QPushButton::clicked,[=](){emit sig_download_delete(getItemOrder());});
    //打开文件所在路径
    connect(ui->pushButton_dl_openfile,&QPushButton::clicked,[=](){openLocalFileSaveDirectory(m_savePath);});
    //重新下载
    connect(ui->pushButton_dl_redown,&QPushButton::clicked,[=](){emit sig_download_reload(getItemOrder());});
    //删除视图item
    connect(ui->pushButton_dl_deleteItem,&QPushButton::clicked,[=](){emit sig_download_deleteItem(getItemOrder());});
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
    //说明：此处文件类型的判断是独立根据url判断的；
    //此处文件类型判断有误，应该先以'？'为标志取'？'左边字符串，然后获取文件类型
    //indexOf：查找某个字符串在字符串首次出现的位置
    //lastIndexOf：从右往左查找某个字符串在字符串中最后一次出现的位置
    //lastIndexOf()方法虽然是从后往前搜索，但返回的位置是从前开始数的
    //pos截取不到，返回-1，截取到，返回具体的位置
    int pos = m_fileUrl.indexOf("?");
    QString tempUrl = m_fileUrl.left(pos);
    QFileInfo info(tempUrl);
    m_fileType = info.suffix();
    setItemFileType(m_fileType);
}

QString DownLoadItem::calCurrentItemLoadedSize(qint64 bytesReceived)
{
    //bytesReceived按字节数统计的
//    if(0 <= bytesReceived < 1024)//B
//    {
//        return QString::number(bytesReceived)+"B";
//    }
//    else if(1024 <= bytesReceived < (1024*1024))//KB 1024*1024=1048576
//    {
//        QString KB = QString::number(bytesReceived/1024);
//        return KB + "KB";
//    }
//    else if((1024*1024) <= bytesReceived < (1024*1024*1024))//MB 1024*1024*1024=1073741824
//    {
//        QString MB = QString::number(bytesReceived/(1024*1024));
//        return MB + "MB";
//    }
//    else if((1024*1024*1024) <= bytesReceived < (1024*1024*1024*1024))//GB
//    {
//        QString GB = QString::number(bytesReceived/(1024*1024*1024));
//        return GB + "GB";
//    }
//    else
//    {
//        return "unknow size";
//    }
    int integer = 0;  //整数位
    int decimal = 0;  //小数位，保留三位
    char unit ='B';
    qint64 standardSize = bytesReceived;
    qint64 curSize = bytesReceived;

    if(standardSize > 1024) {
        curSize = standardSize * 1000;
        curSize /= 1024;
        integer = curSize / 1000;
        decimal = curSize % 1000;
        standardSize /= 1024;
        unit = 'K';
        if(standardSize > 1024) {
            curSize = standardSize * 1000;
            curSize /= 1024;
            integer = curSize / 1000;
            decimal = curSize % 1000;
            standardSize /= 1024;
            unit = 'M';
            if(standardSize > 1024) {
                curSize = standardSize * 1000;
                curSize /= 1024;
                integer = curSize / 1000;
                decimal = curSize % 1000;
                unit = 'G';
            }
        }
    }

    QString dec = "0";
    if (0 <= decimal && decimal <= 9) {
        dec = dec + dec + QString::number(decimal);
    }

    if (10 <= decimal && decimal <= 99) {
        dec = "0" + QString::number(decimal);
    }

    if (100 <= decimal && decimal <= 999) {
        dec = QString::number(decimal);
    }

    return QString::number(integer) + "." + dec + unit;
}

QString DownLoadItem::calCurrentItemSize(qint64 bytesTotal)
{
//    //bytesTotal按字节计，number不四舍五入
//    if(0 <= bytesTotal < 1024)//B
//    {
//        return QString::number(bytesTotal)+"B";
//    }
//    else if(1024 <= bytesTotal < (1024*1024))//KB   1048576
//    {
//        QString KB = QString::number(bytesTotal/1024);
//        return KB + "KB";
//    }
//    else if((1024*1024) <= bytesTotal < (1024*1024*1024))//MB   1073 741 824
//    {
//        QString MB = QString::number(bytesTotal/(1024*1024));
//        return MB + "MB";
//    }
//    else if((1024*1024*1024) <= bytesTotal < 1024*1024*1024*1024)//GB  1099 511 627 776
//    {
//        QString GB = QString::number(bytesTotal/(1024*1024*1024));
//        return GB + "GB";
//    }
//    else
//    {
//        return "unknow size";
//    }

    int integer = 0;  //整数位
    int decimal = 0;  //小数位，保留三位
    char unit ='B';
    qint64 standardSize = bytesTotal;//qint64 long long int
    qint64 curSize = bytesTotal;

    if(standardSize > 1024) {
        curSize = standardSize * 1000;//目的是扩大为整数求取小数部分好计算
        curSize /= 1024;//curSize = curSize/1024 curSize单位为（B）
        integer = curSize / 1000;//变为B大小后，求整数部分
        decimal = curSize % 1000;//求余数mod()
        standardSize /= 1024;//整正的大小 standardSize
        unit = 'K';
        if(standardSize > 1024) {//KB大大小大于1024
            curSize = standardSize * 1000;
            curSize /= 1024;
            integer = curSize / 1000;
            decimal = curSize % 1000;
            standardSize /= 1024;
            unit = 'M';
            if(standardSize > 1024) {
                curSize = standardSize * 1000;
                curSize /= 1024;
                integer = curSize / 1000;
                decimal = curSize % 1000;
                unit = 'G';
            }
        }
    }

    QString dec = "0";
    if (0 <= decimal && decimal <= 9) {
        dec = dec + dec + QString::number(decimal);
    }

    if (10 <= decimal && decimal <= 99) {
        dec = "0" + QString::number(decimal);
    }

    if (100 <= decimal && decimal <= 999) {
        dec = QString::number(decimal);
    }

    return QString::number(integer) + "." + dec + unit;
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

    else if("apk" == suffix)
    {
        ui->label_icon->setStyleSheet("#label_icon{"
                           "border-image:url(://images/function/download_apk.png);"
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

void DownLoadItem::setItemOrder(int num)
{
    ui->label_itemorder->setText(QString::number(num));
}

int DownLoadItem::getItemOrder()
{
    return ui->label_itemorder->text().toInt();
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
    ui->label_completed->setText(QString::fromLocal8Bit("-- 完成"));
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
        ui->label_completed->setText(QString::fromLocal8Bit("-- 文件已删除"));
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

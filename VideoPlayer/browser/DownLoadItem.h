#ifndef DOWNLOADITEM_H
#define DOWNLOADITEM_H

#include <QUrl>
#include <QTime>
#include <QWidget>
#include <QProcess>
#include <QFileInfo>
#include <QFileDialog>
#include <QSoundEffect>

namespace Ui {
class DownLoadItem;
}

class DownLoadItem : public QWidget
{
    Q_OBJECT

public:
    explicit DownLoadItem(QWidget *parent = nullptr);
    explicit DownLoadItem(QUrl url,QString fileName,QString path,bool open,QWidget *parent = nullptr);
    ~DownLoadItem();
    void            initWorkUI();
    void            chandleSignalsAndSlots();
    void            setItemDownloadStatus(bool status);
    QString         calCurrentItemLoadedSize(qint64 bytesReceived);//已加载大小
    QString         calCurrentItemSize(qint64 bytesTotal);//总大小
    QString         calCurrentUnitSize(qreal bytes);//计算网速
    bool            setItemFileType(const QString& suffix);//判断文件类型
    void            setItemDownloadStatusText();
    void            setItemOrder(int num);
    int             getItemOrder();
    void            openLocalFileSaveDirectory(const QString& dir);//打开目录

public slots:
    void            slot_judgeDeleteWorkItem();//判断删除的是哪个item
    void            slot_setItemIcon();//设置文件类型
    void            slot_setItemDownProgress(qint64 bytesReceived, qint64 bytesTotal);//设置下载进度
    void            slot_setItemProgressBarValue(qint64 bytesReceived, qint64 bytesTotal);//设置进度条进度
    void            slot_setItemByteLoad(qint64 bytesReceived, qint64 bytesTotal);//设置已下载的大小
    void            slot_setItemDownSpeed(qint64 bytesReceived, qint64 bytesTotal);//设置下载网速
    void            slot_setItemFileSize(QString size);//设置文件大小
    void            slot_setItemFileName(const QString &filename);//设置文件名
    void            slot_setItemExistStatus(int status);//设置文件状态
    void            slot_receive_start();//下载开始
    void            slot_receive_finished();//文件接收完成
    void            slot_receive_openDir(bool open);//下载完打开目录
protected:
    bool            eventFilter(QObject *watched, QEvent *event) override;
    bool            checkItemFileIsExist(QString fullpath);//检查文件是否存在
private slots:


private:
    Ui::DownLoadItem *ui;
    QTime           m_speedTime;
    bool            m_open;//下载完成是否直接打开
    bool            m_start;
    QString         m_fileUrl;
    QString         m_fileType;
    QString         m_fileName;
    QString         m_savePath;

signals:
    void            sig_downloadStatus(int num,bool status);//暂停/继续
    void            sig_download_cancel(int num);//取消下载
    void            sig_download_delete(int num);//删除正在下载的item
    void            sig_download_reload(int num);//重新下载
    void            sig_download_deleteItem(DownLoadItem *item);//删除已经完成的item
};

#endif // DOWNLOADITEM_H

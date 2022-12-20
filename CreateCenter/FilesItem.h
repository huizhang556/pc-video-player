#ifndef FILESITEM_H
#define FILESITEM_H
//#include "database/dataBase.h"
#include <QUrl>
#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QLineEdit>
#include <QComboBox>
#include <QListView>
#include <QStringList>
#include <QFileDialog>
#include <QDebug>

struct fileBody
{
    QString furl;       //源地址
    QString fmd5;       //md5
    qint64  fsize;      //大小
    QString fname;      //自定义名称
    QString fcover;      //video music picture 封面
    QString fnick;      //视频展示介绍
    QString fmedtype;   //媒体类型（电影，音乐。。。）
    QString fmedtheme;  //媒体题材
    QString fduration;  //媒体时长
};

enum FILEEDIT
{
    CANWRITE,//可编辑
    CANEDIT  //只读
};

enum FILESTATUS
{
    READY,      //待上传
    WAITING,    //等待中
    UPLOADING,  //上传中
    FINISHED,   //已完成
    UNKNOW      //未知错误
};

namespace Ui {
class FilesItem;
}

class FilesItem : public QWidget
{
    Q_OBJECT

public:
    explicit FilesItem(QWidget *parent = nullptr);
    explicit FilesItem(const FILEEDIT edit, const QUrl& url, const qint64 size, const QString& picpath, QWidget *parent = nullptr);
    ~FilesItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();
    void    initFileItem(const fileBody& body);

public slots:
    void    slot_setItemEdit(const FILEEDIT edit);
    void    slot_setItemStatus(FILESTATUS status);
    void    slot_setItemStatusText();
    void    slot_setItemStart(bool start);
    void    slot_setItemSize();
    void    slot_setItemName();
    void    slot_setItemPicture();
    void    slot_updateProgress(qint64 bytesSent, qint64 bytesTotal);
    void    slot_updateProgress_header(qint64 bytesSent, qint64 bytesTotal);
    void    slot_updateStatus(qint64 bytesSent, qint64 bytesTotal);
    void    slot_update_url_md5(const QString& url,const QString& md5);
    void    slot_update_header(const QString& url_header,const QString& md5);
    void    slot_pauseButtonClick();//模拟暂停按钮点击
    void    slot_statusButtonClick();//模拟状态按钮点击
private:
    QString    calCurrentFileSize(qint64 bytesTotal);
    int        getCurtentComboBoxIndex(const QComboBox* combobox, const QString& itemtext);
    QString    getCurtentComboBoxText(const QComboBox* combobox, const QString& itemtext);
    void       file_insertItemDataTodb(const fileBody& body);//插入数据库媒体信息

private:
    Ui::FilesItem *ui;
    FILEEDIT    m_canedit;
    FILESTATUS  m_status;
    QString     m_curStatus;
    QString     m_furl;
    QString     m_name;
    QString     m_picpath;
    qint64      m_size;
    fileBody    m_body;


signals:
    void    sig_sendItem_pause(bool,QUrl,QUrl);//video_url pic_url
    void    sig_sendItem_play();//播放(播放地址)
    void    sig_sendItem_remove();
    void    sig_sendItem_finished(fileBody);
    void    sig_sendItem_statusChanged(FILESTATUS);
};

#endif // FILESITEM_H

#ifndef FILESITEM_H
#define FILESITEM_H

#include "database/dataBase.h"
#include <QUrl>
#include <QUrlQuery>
#include <QWidget>
#include <QMenu>
#include <QTimer>
#include <QAction>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QFileInfo>
#include <QLineEdit>
#include <QComboBox>
#include <QListView>
#include <QBuffer>
#include <QRegExp>
#include <QMovie>
#include <QMouseEvent>
#include <QRegExpValidator>
#include <QByteArray>
#include <QStringList>
#include <QFileDialog>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QDebug>

//以下ffmpeg获取视频信息使用
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

struct fileBody
{
    int     fid;        //文件id
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
Q_DECLARE_METATYPE(fileBody)

//ITEM类型
enum FILEEDIT
{
    CANWRITE,//可编辑
    CANEDIT, //只读
    DISPLAY //展示
};

//ITEM状态
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
    explicit FilesItem(const FILEEDIT edit, const int id, const QUrl& url, const qint64 size, const QString& picpath, QWidget *parent = nullptr);
    ~FilesItem();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    void        setInstallEventFilter();
    void        initFileItem(const fileBody& body);

    int         getItem_fid();
    QString     getItem_furl();

public slots:
    void        slot_setItemEdit(const FILEEDIT edit);
    void        slot_setItemStatus(FILESTATUS status);
    void        slot_setItemStatusText();
    void        slot_setItemStart(bool start);
    void        slot_setItemUrl(QUrl url);
    void        slot_setItemSize();
    void        slot_setItemName();
    void        slot_setItemPicture();
    void        slot_setItemDuration();
    void        slot_getVideoPicure(const char * file,QLabel* label);//如果是视频，获取视频第一帧
    void        slot_updateProgress(qint64 bytesSent, qint64 bytesTotal);
    void        slot_updateProgress_header(qint64 bytesSent, qint64 bytesTotal);
    void        slot_updateStatus(qint64 bytesSent, qint64 bytesTotal);
    void        slot_update_url_md5(bool sucess,const QString& url,const QString& md5);
    void        slot_update_header(bool success, const QString& url_header, const QString& md5);
    void        slot_pauseButtonClick();//模拟暂停按钮点击
    void        slot_statusButtonClick();//模拟状态按钮点击
    void        slot_setSelButtonChecked(const bool checked = false);//设置选择状态(默认不选中)

protected:
    bool        eventFilter(QObject *watched, QEvent *event)override;

private:
    QString    switchFormatTime(qint64 total);//秒转时分秒
    QString    calCurrentFileSize(qint64 bytesTotal);
    int        getCurtentComboBoxIndex(const QComboBox* combobox, const QString& itemtext);
    QString    getCurtentComboBoxText(const QComboBox* combobox, const QString& itemtext);
    void       file_insertItemDataTodb(const fileBody& body);//插入数据库媒体信息

    QString    QStrToBase64(QString str);
    QString    Base64ToQStr(QString base64Str);
    void       createContextMenu(const QStringList& menulist);

private slots:
    void       slot_replyCoverFinished(QNetworkReply *reply);

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
    QString     m_duration;
    QImage      m_cover;
    bool        m_rmenu = false;
    int         m_fid;
    QMovie      m_movie;

    QNetworkAccessManager   *manager    =   nullptr;
    QNetworkReply           *reply      =   nullptr;

    QStringList videoTypeList;

    QStringList menuList =
    {
        QString(u8"自定义合集1"),
        QString(u8"自定义合集2"),
        QString(u8"自定义合集3"),
        QString(u8"自定义合集4"),
        QString(u8"自定义合集5")
    };


signals:
    void    sig_sendItem_upload(bool,QUrlQuery,QByteArray&);//上传图片数据
    void    sig_sendItem_pause(bool,QUrl,QUrl);//video_url pic_url
    void    sig_sendItem_play();//播放(播放地址)
    void    sig_sendItem_remove();
    void    sig_sendItem_download(QUrlQuery);
    void    sig_sendItem_finished(fileBody);
    void    sig_sendItem_clicked();
    void    sig_sendItem_statusChanged(FILESTATUS);
};

#endif // FILESITEM_H

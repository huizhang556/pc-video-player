#ifndef WEBDOWNLOADLIST_H
#define WEBDOWNLOADLIST_H
#include "browser/DownLoadItem.h"

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QSound>
#include <QMetaType>
#include <QFileInfo>
#include <QSoundEffect>
#include <QMouseEvent>
#include <QProgressBar>
#include <QPushButton>
#include <QStackedWidget>
#include <QListWidgetItem>

namespace Ui {
class WebDownLoadList;
}

class WebDownLoadList : public QWidget
{
    Q_OBJECT

public:    
    ~WebDownLoadList();
    void initWorkUI();
    void chandleSignalsAndSLots();
    static  WebDownLoadList* getInstance();
    DownLoadItem*    getDownloadItem();
public slots:
    bool        slot_addDownLoadRecordToList(const QUrl &url, const QString &filename, const QString &savepath, bool openStatus);//添加下载记录
    void        slot_searchDownloadHirtory(QString text);
    void        slot_setDownloadProgressbar(qint64 bytesReceived, qint64 bytesTotal);
    void        slot_receivedNewWorkFinished();
    void        slot_setItemPicture();
    void        slot_setItemFileName();
    void        slot_setItemFileSize();

protected:
    void        mousePressEvent(QMouseEvent *event) override;
    void        mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void        on_pushButton_min_clicked();
    void        on_pushButton_close_clicked();
    void        slot_setStartStatus(QPushButton *button,bool status);
    void        slot_openLocalFile();
    void        slot_deleteFile();

    void        getButtonInfo();

signals:
    void        sig_setConfig();
    void        sig_open(int num,QString path);
    void        sig_cancel(int num);
    void        sig_pause(int num);
    void        sig_delete(int num);
    void        sig_download(int num);
    void        sig_receiveProgressbar(int value);
    void        sig_receiveFinished();
    void        sig_newDownloadRequest(const QString &address);
private:
    explicit WebDownLoadList(QWidget *parent = nullptr);
    Ui::WebDownLoadList *ui;
    QPoint              m_mvPos;
    bool                m_start;
    int                 m_count;
    qint64              m_fileSize;
    QString             m_fileSuffix;
    QString             m_fileName;
    QString             m_filePath;
//    QStackedWidget      *m_barStackWgt      =   nullptr;
//    QStackedWidget      *m_ctlStackWgt      =   nullptr;
    QLabel              *lab_num                =   nullptr;
    QProgressBar        *progressbar        =   nullptr;
    QLabel              *lab_fileName       =   nullptr;
    QLabel              *lab_fileSize       =   nullptr;
    QPushButton         *stopbtn            =   nullptr;
    QPushButton         *downloadlbtn       =   nullptr;
    QPushButton         *deletebtn          =   nullptr;
    QPushButton         *openbtn            =   nullptr;
    QVBoxLayout         *vblayout0          =   nullptr;
    QHBoxLayout         *hblayout0          =   nullptr;
    QHBoxLayout         *hblayout1          =   nullptr;
    QHBoxLayout         *hblayout2          =   nullptr;
    QWidget             *tempwdt            =   nullptr;
    QListWidgetItem     *item               =   nullptr;
    DownLoadItem        *m_downLoadItem     =   nullptr;
    static  WebDownLoadList* m_pInstance;

};

#endif // WEBDOWNLOADLIST_H

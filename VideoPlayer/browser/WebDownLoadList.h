#ifndef WEBDOWNLOADLIST_H
#define WEBDOWNLOADLIST_H
#include "mythread/Worker.h"
#include "browser/DownLoadItem.h"

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QSound>
#include <QThread>
#include <QMetaType>
#include <QFileInfo>
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
    void        initWorkUI();
    void        chandleSignalsAndSLots();
    static      WebDownLoadList* getInstance();
    static      int getWorkCounts();//获取任务数量
public slots:
    bool        slot_addDownLoadRecordToList(const QUrl &url, const QString &filename, const QString &savepath, bool openStatus);//创建下载

protected:
    void        mousePressEvent(QMouseEvent *event) override;
    void        mouseMoveEvent(QMouseEvent *event) override;
    bool        eventFilter(QObject *watched, QEvent *event) override;

signals:
    void        sig_setConfig();
    void        sig_newDownloadRequest(const QString &address);

private slots:
    void        slot_createNewDownloadWork();
    void        slot_receiveThreadStarted();
    void        slot_receiveThreadFinished();
    void        slot_searchDownloadHirtory(QString text);
    void        slot_itemRemove(DownLoadItem *item);
    void        slot_freeItem(QListWidget *listWidget, QWidget *itemWidget, QListWidgetItem *item);
    void        on_pushButton_min_clicked();
    void        on_pushButton_close_clicked();
    void        getButtonInfo();
    void        slot_findFileFromLineEdit( QString name);
    void        slot_setCurrentWorkCounts(int count);
    bool        slot_deleteFileOrFolder(const QString &strPath);//要删除的文件夹或文件的路径

private:
    explicit WebDownLoadList(QWidget *parent = nullptr);
    Ui::WebDownLoadList *ui;
    QPoint              m_mvPos;
    bool                m_start;
    qint64              m_fileSize;
    QString             m_fileSuffix;
    QString             m_fileName;
    QString             m_filePath;

    Worker              *m_worker           =   nullptr;//真正处理工作
    QThread             *m_workThread       =   nullptr;//工作线程
    static  WebDownLoadList* m_pInstance;
    static  int m_count;//任务数量
};

#endif // WEBDOWNLOADLIST_H

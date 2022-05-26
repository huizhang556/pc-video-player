#ifndef NEWWORK_H
#define NEWWORK_H
#include "global/Global.h"
#include "mythread/Worker.h"
#include "WebDownLoadList.h"

#include <QUrl>
#include <QFile>
#include <QDialog>
#include <QAction>
#include <QThread>
#include <QBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QListWidget>

namespace Ui {
class NewWork;
}

class NewWork : public QDialog
{
    Q_OBJECT

public:
    ~NewWork();
    void        initWorkUI();
    void        chandleSignalsAndSlots();
    static NewWork* getInstance();
public slots:
    QString     openLocalFileSystem();
    void        slot_receiveDownloadRequested(QWebEngineDownloadItem* item);//重载函数1
    void        slot_receiveDownloadRequested(const QUrl url);//重载函数2
    void        slot_createNewDownloadWork();
//    void slot_downLoad_progress(qint64 bytesReceived, qint64 bytesTotal);
//    void slot_downLoad_finished();
protected:
    bool        eventFilter(QObject *watched, QEvent *event) override;
    void        mousePressEvent(QMouseEvent *event) override;
    void        mouseMoveEvent(QMouseEvent *event) override;
    bool        isFileExist(QString fullFileName);
private slots:
    void        slot_addPathToList(const QString &path);
    void        slot_setLineEditText(QLineEdit *edit, const QString &text);
    bool        slot_judgePathExist(const QString &path);
    void        slot_updateShowListPathWidget();
    void        slot_receiveWorkerFinished();
    void        slot_receiveThreadStarted();
    void        slot_receiveThreadFinished();
private:
    explicit NewWork(QWidget *parent = nullptr);
    Ui::NewWork *ui;
    int                     m_count;
    QUrl                    m_fileUrl;
    QString                 m_savePath;
    QString                 m_fileName;
    QPoint                  m_mvPos;
    QAction                 *m_spaceSize            =   nullptr;
    QAction                 *m_fileSize             =   nullptr;
    QListWidget             *m_listWdgt_path        =   nullptr;
    QPushButton             *m_clearBtn             =   nullptr;
    QWidget                 *m_hisWdgt              =   nullptr;
    static  NewWork         *m_pInstance;
    Worker                  *m_worker;
    QThread                 *m_workThread;
signals:
    void        sig_download_start();
    void        sig_download(const QUrl& url,const QString& filename, const QString& savepath,bool open);
    void        sig_cancel();
};

#endif // NEWWORK_H

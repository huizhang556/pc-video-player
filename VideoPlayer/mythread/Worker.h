#ifndef WORKER_H
#define WORKER_H

#include <QDir>
#include <QUrl>
#include <QFile>
#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QWebEngineDownloadItem>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();
    static  int getWorkCounts();//获取现有任务
    bool    isDirExist(QString fullpath);
public slots:
    //以下函数进行重载
    void    slot_receiveData_accept(QWebEngineDownloadItem *item, QString filename, QString savepath);
    void    slot_receiveData_accept(QUrl url, QString filename, QString savepath);

    void    slot_receiveData_pause(int order,bool status);      //01---暂停/继续
    void    slot_receiveData_pause(bool status, QWebEngineDownloadItem *item);

    void    slot_receiveData_cancel(int order);                 //02---取消
    void    slot_receiveData_cancel(QWebEngineDownloadItem *item);

    void    slot_receiveData_deleteWork(int order);             //03---删除正在下载的任务
    void    slot_receiveData_deleteWork(QWebEngineDownloadItem *item);

    void    slot_receiveData_itemReDownload(int order);         //04---重新下载文件
    void    slot_receiveData_itemReDownload(QWebEngineDownloadItem *item);

    void    slot_receiveData_progressbar(qint64 bytesReceived, qint64 bytesTotal);
    void    slot_receiveData_finished();//项目完成


signals:
    void    sig_receiveData_progressbar(qint64 bytesReceived, qint64 bytesTotal);
    void    sig_receiveData_finished();
    void    sig_receiveData_pause();
    void    sig_receiveData_resume();
    void    sig_receiveData_cancel();

private:
    QWebEngineDownloadItem      *m_workItem     =   nullptr;
    QNetworkAccessManager       *m_netManager   =   nullptr;
    QFile                       m_file;
    QByteArray                  m_array;//临时存储
};

#endif // WORKER_H

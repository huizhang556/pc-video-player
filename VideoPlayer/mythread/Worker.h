#ifndef WORKER_H
#define WORKER_H

#include <QUrl>
#include <QFile>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QWebEngineDownloadItem>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();

public slots:
    void    slot_receiveData_accept(QWebEngineDownloadItem *item, QString filename, QString savepath);
    void    slot_receiveData_pause(QWebEngineDownloadItem *item);
    void    slot_receiveData_cancel(QWebEngineDownloadItem *item);
    void    slot_receiveData_resume(QWebEngineDownloadItem *item);

    void    slot_receiveData_accept(QUrl url, QString filename, QString savepath);
    void    slot_receiveData_pause();
    void    slot_receiveData_cancel();
    void    slot_receiveData_resume();

    void    slot_receiveData_progressbar(qint64 bytesReceived, qint64 bytesTotal);
    void    slot_receiveData_finished();

signals:
    void    sig_receiveData_progressbar(qint64 bytesReceived, qint64 bytesTotal);
    void    sig_receiveData_finished();
    void    sig_receiveData_pause();
    void    sig_receiveData_resume();
    void    sig_receiveData_cancel();

private:
    QWebEngineDownloadItem      *m_workItem     =   nullptr;
    QNetworkAccessManager       *m_netManager   =   nullptr;
    QFile                       *m_file         =   nullptr;
    int                         m_count;

};

#endif // WORKER_H

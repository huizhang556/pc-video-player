#ifndef WORKER_H
#define WORKER_H
#include "browser/NewWork.h"
#include <QObject>
#include <QWebEngineDownloadItem>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();

public slots:
    void    doWork(const QString &para);
    void    slot_createNewDownloadWorker(QWebEngineDownloadItem *item);
    void    slot_receiveData_progressbar(qint64 bytesReceived, qint64 bytesTotal);
    void    slot_receiveData_finished();
signals:
    void    sig_receiveData_progressbar(qint64 bytesReceived, qint64 bytesTotal);
    void    sig_receiveData_finished();

private:

};

#endif // WORKER_H

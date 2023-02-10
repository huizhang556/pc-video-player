#ifndef UPLOADWORK_H
#define UPLOADWORK_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QHttpPart>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QDebug>

class UploadWork : public QObject
{
    Q_OBJECT
public:
    explicit UploadWork(QObject *parent = nullptr);
    ~UploadWork();

public slots:

    void    slot_receiveData_accept(const QUrl& media_url);

signals:

private:
    QString getContentTypeHeader(const QString& suffix);
    void    getJson(QJsonObject &jsonObj);//解析返回json
    void    getStatusCode(QNetworkReply *reply);//解析状态值

private slots:
    void finshedSlot(QNetworkReply* reply);//用来接收返回的Json数据

private:
    QString                 m_fileName;
    QFile                   *m_file;
    QNetworkReply           *m_reply;
    QNetworkAccessManager   *m_manager  =   nullptr;

signals:
    void    sig_work_uploadprogress(qint64,qint64);
    void    sig_work_finished(QString,QString);

};

#endif // UPLOADWORK_H

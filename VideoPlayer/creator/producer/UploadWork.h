#ifndef UPLOADWORK_H
#define UPLOADWORK_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QUrlQuery>
#include <QDateTime>
#include <QByteArray>
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
    void    slot_receiveData_accept(const QByteArray &media_data);//建立下载请求，创建文件，并向外返回下载进度
    void    slot_receiveData_accept(const QString& media_url);//建立下载请求，创建文件，并向外返回下载进度
    void    slot_receiveData_accept(const QUrlQuery &media_url);//建立下载请求，创建文件，并向外返回下载进度
    void    slot_uploadFileData(QFile *file, const QString& suf, const QString& dirName);
    void    slot_receiveData_pause();//暂停
    void    slot_receiveData_close();//关闭

signals:

private:
    QString getContentTypeHeader(const QString& suffix);//获取文件类型
    void    getJson(QJsonObject &jsonObj);//解析返回json
    void    getStatusCode(QNetworkReply *reply);//解析状态值

private slots:
    void finshedSlot(QNetworkReply* reply);//用来接收返回的Json数据

private:
    bool                    m_isStopping;//是否处于已经下载状态（防止点击按钮多次请求）
    QString                 m_fileName;//文件名
    QFile                   *m_file     =   nullptr;//保存文件
    QNetworkReply           *m_reply    =   nullptr;
    QNetworkAccessManager   *m_manager  =   nullptr;

signals:
    void    sig_work_uploadprogress(qint64,qint64);
    void    sig_work_finished(bool,QString,QString);

};

#endif // UPLOADWORK_H

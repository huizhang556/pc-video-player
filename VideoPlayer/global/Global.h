#ifndef GLOBAL_H
#define GLOBAL_H
#include <QDir>
#include <QObject>
#include <QString>
#include <QProcess>
#include <QHostInfo>
#include <QApplication>
#include <QNetworkConfigurationManager>

class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);
    ~Global();
    static void registerLAVplayer();//注册播放器
    static void unRegisterLAVplayer();//卸载注册播放器
    bool    isNetWorkOnline();//判断是否在线
    void    checkNetWorkOnline();//判断是都连接互联网

    //声明共有静态变量
    static QString appDirPath;

public slots:
    void    onLookupHost(QHostInfo host);

signals:
    void    sig_sendLookUpHostResult(bool);
};

#endif // GLOBAL_H

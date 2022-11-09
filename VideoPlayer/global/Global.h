#ifndef GLOBAL_H
#define GLOBAL_H
#include <QDir>
#include <QObject>
#include <QString>
#include <QProcess>
#include <QLibrary>
#include <QHostInfo>
#include <QApplication>
#include <QNetworkConfigurationManager>

typedef bool(*ConnectFun)(int* lpdwFlags, int  dwReserved);

/*全局变量放在此处*/
class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);
    ~Global();
    static void         registerLAVplayer();//注册播放器
    static void         unRegisterLAVplayer();//卸载注册播放器
    bool                isNetWorkOnline();//判断是否在线
    static QString      readIni_exit();//读取配置文件（退出窗口）
    static QString      readIni_regis();//读取配置文件(播放器注册状态)
    static void         setIni_exit(bool on);//设置配置文件（退出窗口）
    static void         setIni_ungis(bool on);
    static bool         getRegisStatus();
    static void         checkNetWorkOnline();//检查网络在线

public:
    //声明共有静态变量
    static QString appDirPath;

public slots:
    void        onLookupHost(QHostInfo host);

signals:
    void        sig_sendLookUpHostResult(bool);
};

#endif // GLOBAL_H

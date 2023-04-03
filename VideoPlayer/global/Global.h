#ifndef GLOBAL_H
#define GLOBAL_H

#define UPDATTIME   5000

#include <QDir>
#include <QTimer>
#include <QObject>
#include <QString>
#include <QProcess>
#include <QLibrary>
#include <QHostInfo>
#include <QFileInfo>
#include <QApplication>
#include <QNetworkConfigurationManager>

typedef bool(*ConnectFun)(int* lpdwFlags, int  dwReserved);

/*全局变量放在此处*/
class Global : public QObject
{
    Q_OBJECT
    explicit Global(QObject *parent = nullptr);
public:
    ~Global();
    static void         registerLAVplayer();//注册播放器
    static void         unRegisterLAVplayer();//卸载注册播放器
    bool                isNetWorkOnline();//判断是否在线
    static QString      readIni_exit();//读取配置文件（退出窗口）
    static QString      readIni_regis();//读取配置文件(播放器注册状态)
    static void         setIni_exit(bool on);//设置配置文件（退出窗口）
    static bool         readCloseAction();//读取关闭行为配置
    static void         setCloseAction(bool on);//设置关闭行为
    static void         setIni_ungis(bool on);
    static bool         getRegisStatus();
    static void         checkNetWorkOnline();//检查网络在线
    static Global*      getInstance();
    static bool         getFileType(const QString& filepath);
public:
    //声明共有静态变量
    static QString  appDirPath;
    static QTimer   *m_globalTimer;
    static Global   *m_pInstance;
public slots:
    void        onLookupHost(QHostInfo host);

signals:
    void        sig_sendLookUpHostResult(bool);
    void        sig_sendGlobalTimeOut();

private:

};

#endif // GLOBAL_H

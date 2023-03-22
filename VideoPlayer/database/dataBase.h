#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QDomDocument>
#include <QSize>
#include <QPixmap>
#include <QSqlResult>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QDesktopWidget>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QDebug>


//用户信息结构体
struct UserInfo
{
    QString     m_userId;       //用户唯一标识
    QString     m_userName;     //用户名称
    QString     m_userPwd;      //用户密码
    QString     m_userEmails;   //用户邮箱
    QString     m_headPic;      //用户头像
    int         m_vipType;      //会员类型
    bool        m_userOnline;   //是否在线
    QString     m_LoginTime;    //最近登录时间
    QString     m_createTime;   //创建时间
};
Q_DECLARE_METATYPE(UserInfo)

//回应信息结构体
struct Message
{
    //消息类型
    //0 身份信息
    //1  登陆成功
    //2 用户名不存在
    //3 用户名不存在
    //4  密码不正确
    //5 在线
    //6 不在线
    //7 注册成功
    //8 已存在相同账户
    //9 邮箱被注册
    int        m_mType;
    QString    m_infoBody;
};
Q_DECLARE_METATYPE(Message)

class dataBase : public QObject
{
     Q_OBJECT
public:    
    ~dataBase();
    static  dataBase*       getInstance();
    static  QSqlDatabase    getSqlDataBase();
    static  bool            creatSqliteConnection();//创建sqlite连接
    static  bool            removeSqliteConnection();//移除sqlite连接
    static  bool            creatMysqlConnection();//创建mysql连接
    static  bool            removeMysqlConnection();//移除mysql连接
    bool                    initGlobalDate();//初始化全局数据
    bool                    initCurUserData();//初始化当前用户数据
    void                    initWorkUI();//初始化
    void                    handleSignalsAndSlots();//处理信号与槽函数
    //获取用户信息
    QString                 getCurrentUserID() const;
    QString                 getCurrentUserName() const;
    QString                 getCurrentUserHead() const;
    int                     getCurrentUserGrade() const;
    bool                    getCurrentUserOnline() const;
    const QPixmap&          getCurrentUserHeadPix();

    //读取cfg.xml信息
    static void             readXML(const QString& path);
    static void             writeXML(const QString& path);
    static void             deleteXML(const QString& path,const QString& node,const QString& newvalue);
    static void             addXML(const QString& path,const QString& node,const QString& newvalue);
    static void             updateXML(const QString& path, const QString& nodename, const QString& newvalue);

    //静态成员函数不能加const 修饰
    static QString          getWebDef_user();
    static QString          getWebDef_userId();
    static QString          getWebDef_url();
    static QString          getWebDef_title();
    static QString          getWebDef_savePath();

    static QString          getSkin_theme();//主题
    static bool             getSkin_switch();//开关
    static QString          getSkin_splash();//路径
    static QSize            getSize_splash();//大小

public slots:
    //通用

    //表通用查询
    int                     getTableRecordsCounts(const QString& tablename);//查询某张表记录总数
    bool                    getUserExists(const QString& tablename,const QString& username);//查询用户是否存在
    //关于个人信息部分
    //登录部分
    bool                    login_checked_usernameAndPasswd(const QString& name, const QString& pwd);//核查名称以及密码
    bool                    login_verification(const QString& name, const QString& pwd);//查找个人信息
    bool                    login_setLoginStatus(bool status);//设置在线状态
    bool                    login_setUserGrade(int grade);//设置用户等级

    //注册部分
    bool                    register_userInfo(const QString& name, const QString& pwd,const QString& emails);//注册个人信息

    //找回密码部分
    QString                 getback_userPasswd(const QString& name,const QString& emails);//找回个人密码

    //测试部分


    //关于浏览器
    //收藏记录操作
    void                    browser_loadAllRecordsToList();//获取数据库全部收藏记录
    void                    browser_addRecordToList(const QString &urlnick, const QString &url);//往数据库添加一条记录
    void                    browser_deleteRecordToList(const QString &url);//往数据库删除一条记录
    void                    browser_updateRecordToList(const QString &url,const QString &urlnick);//往数据库更新一条记录
    //历史记录操作
    void                    browser_loadAllHisRecordsToList();//获取数据库全部历史记录
    void                    browser_addHisRecordToList(const QString &url);//往数据库添加一条历史记录
    void                    browser_deleteHisRecordToList(const QString &url);//往数据库删除一条历史记录
    void                    browser_deleteAllHisRecordToList();//往数据库删除所有历史记录

    //推荐视频
    void                    video_insertRecDramaListDB(const QStringList& parma);//插入视频
    bool                    video_recDramaInfo();//查询推荐列表

    //查询作品
    bool                    creator_getdoneWorks(const QString& tags);//按标签查询作品
    int                     creator_getdoneWorkCounts(const QString& tags);//查询数量
    QStringList             creator_getAllTagsWorkCounts();//查询所有标签的媒体数量

protected:


private:
    dataBase();
    QNetworkAccessManager   *m_manager  =   nullptr;

    static  dataBase*       m_pInstance;//全局唯一
    QString                 m_curUserID;//当前用户唯一识别id
    QString                 m_curUserHead;//当前用户头像连接
    QString                 m_curUserName;//当前用户名称
    int                     m_curUserGrade;//当前用户等级 游客0 普通1 会员2 超级会员3
    bool                    m_online;//是否在线
    QPixmap                 m_curHeadPix;//用户头像

    //数据库连接
    static      QString     m_hostName;//主机ip
    static      QString     m_hostPort;//主机端口
    static      QString     m_userName;//用户名称
    static      QString     m_userPawd;//用户密码
    static      QString     m_dataName;//数据库名
    //浏览器
    static      QString     m_webDef_Url;//默认加载url
    static      QString     m_webDef_title;//默认标题
    static      QString     m_webDef_user;//默认用户
    static      QString     m_webDef_userId;//默认用户ID
    static      QString     m_webDef_savePath;//默认保存路径
    //皮肤
    static      QString     m_skin_theme;//默认皮肤主题
    static      bool        m_skin_switch;//开关
    static      QString     m_skin_splash;//加载缓冲界面
    static      int         m_splash_width;//加载缓冲界面宽度
    static      int         m_splash_height;//加载缓冲界面高度

private:
    static      QString     getHostName();
    static      QString     getHostPort();
    static      QString     getUserName();
    static      QString     getUserPawd();
    static      QString     getDataName();

    void        showResult(const QSqlQuery& query);//展示查询结果
    void        getUserHeaderPix(QNetworkReply* reply);//接收用户头像数据


signals:
    void        sig_loginStatusChanged(bool);//0下线 1登录
    void        sig_sendVideoDramaInfo(QVariant);//推荐剧集列表
    void        sig_sendUserDoneWorks(QVariant&);//已完成作品列表
    void        sig_sendUserDoneWorkCounts(int);//某种已完成作品数量
//    void        sig_sendVideoDramaUrl(int,QString);
    void        sig_sendRecordInfo(QString,QString,QString);//urlnick url createtiem
    void        sig_sendHisRecordInfo(QString,QString);//url createtime
    void        sig_sendMessage(int,QString);//信息类型 消息体

    void        sig_errorMessage_login(int,QString);//登录消息
    void        sig_errorMessage_register(int,QString);//注册消息
    void        sig_errorMessage_recover(int,QString);//找回消息
    void        sig_errorMessage_testing(int,QString);//测试消息
};

#endif // DATABASE_H

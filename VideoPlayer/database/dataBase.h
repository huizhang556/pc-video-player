#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QSize>
#include <QPixmap>
#include <QSqlResult>
#include <QSqlRecord>
#include <QVariant>
#include <QUrlQuery>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QStringList>
#include <QDomDocument>
#include <QSqlDatabase>
#include <QNetworkReply>
#include <QDesktopWidget>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QCryptographicHash>
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
    QString                 getCurrentUserPawd() const;
    QString                 getCurrentUserHead() const;
    QString                 getCurrentUserLoginTime() const;
    QString                 getCurrentUserCreateTime() const;
    int                     getCurrentUserGrade() const;
    bool                    getCurrentUserOnline() const;
    const QPixmap&          getCurrentUserHeadPix();


    //获取视频类型
    QStringList&            getVideoMediaType();

    //加密部分
    QString                 code_base64_To_QString(QString base_str);
    QString                 code_qstring_To_Base64(QString qstring_str);
    QString                 code_qstring_To_Hash(QString qstring_str);

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
    //关于某一个用户信息
    QUrlQuery               user_getCurMediaUserInfo(const QString& user_id);//查询用户信息
    bool                    user_operate_setToWatch(const int media_id);//播放量+1（watches）
    bool                    user_operate_updateFansCounts(bool up, const QString& follow_id);//更新粉丝数
    bool                    user_operate_updateLoveCounts(bool up, const QString& user_id);//更新收藏数
    bool                    user_operate_updateCareCounts(bool up, const QString& user_id);//更新关注数
    bool                    user_operate_updateVideoLoveCounts(bool up, const int media_id);//更新某个视频的收藏数
    bool                    user_operate_setToFollow(bool add, const QString& user_id,const QString& follow_id);//关注成为粉丝(fans)
    bool                    user_operate_setToUplove(bool love, const QString& user_id, const QString& love_id, const int media_id);//收藏点赞（uplove）
    bool                    user_operate_getFollow(const QString& user_id,const QString& follow_id);//某个用户是否为粉丝
    bool                    user_operate_getUplove(const QString& user_id, const int media_id);//某个用户是否关注某个视频

    QList<QUrlQuery>&       user_getCurUserAllFans(const QString &user_id);//获取用户下的所有粉丝用户
    QList<QUrlQuery>&       user_getCurUserAllWatches(const QString &user_id);//获取用户下的所有关注用户
    QList<QUrlQuery>&       user_getCurUserAllCollections(const QString &user_id);//获取用户下的所有收藏视频
    QList<QUrlQuery>&       user_getCurUserAllComments(const QString &user_id);//获取用户下的所有评论

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
    bool                    video_insertRecDramaListDB(const QStringList& parma);//插入视频
    bool                    video_recDramaInfo();//查询推荐列表
    bool                    video_recDrama_of_theme(const QString& theme,int start, int counts);//查询某个主题下的视频

    //广告推荐
    QList<QVariant>&        adv_getNext4Medais(const QString &theme,const int start,int counts);//获取接下来播放的4个视频
    QUrlQuery               adv_getCurMediaUserInfo(const int media_id);//根据当前媒体查询媒体拥者信息
    QString                 adv_getMediaUserHeader(const QString &user_id);//根据user_id获取某位用户头像
    QString                 adv_getMediaUserName(const QString &user_id);//根据user_id获取某位用户姓名
    QString                 adv_getMediaUserId(const int media_id);//根据media_id查找用户userid

    //视频类型
    bool                    video_getVideoMediaSortType();//获取视频分类

    //查询作品
    QList<QVariant>&        creator_getCurUserAllDramas(const QString &user_id);//获取用户下的所有上传视频列表
    QList<QUrlQuery>&       creator_getCurUserAllAlbums(const QString &user_id);//获取用户下的所有专辑列表
    QList<QUrlQuery>&       creator_getCurUserAllGroups(const QString &user_id);//获取用户下的所有合集列表

    bool                    creator_getdoneWorks(const QString& tags);//按标签查询作品  
    int                     creator_getdoneWorkCounts(const QString& tags);//查询数量
    QStringList             creator_getAllTagsWorkCounts();//查询所有标签的媒体数量
    bool                    creator_removeOneMediaFromSort(const QString& tags, const int media_id);//删除某个分类下的某个item

    //历史头像
    void                    header_initHeader();//初始化
    bool                    header_getUserHistory();//查询当前用户历史头像
    bool                    header_getManHeaderList();//查询男性头像
    bool                    header_getWomanHeaderList();//查询女性头像
    bool                    header_getGifHeaderList();//查询情侣头像
    bool                    header_inserUsrHeaderToDB(const QString &pix_url,const QString& pix_type);//插入头像图片数据
    bool                    header_updateUserHeader(const QString &user_id,const QString& pix_url);//更新用户头像
    bool                    header_deleteUserHisHeader(const QString &user_id, const QString& pix_id);//删除用户历史头像

    //用户专辑
    bool                    album_getCurUserAlbums(const QString &user_id);//获取当前用户的所有专辑（信号槽发送）
    QList<QUrlQuery>&       album_getCurUserAllAlbums(const QString &user_id);//获取某个用户所有的专辑
    bool                    album_getCurUserAlbumMedias(const QString& album_id);//获取当前用户的某个专辑下所有媒体（信号槽发送）
    QList<QVariant>&        album_getCurUserOneAlbumAllMedias(const QString& album_id);//获取某个用户某个专集所有的items
    QString                 album_insertAlbums(const QString& user_id, const QString& album_name, const QString& album_pix);//添加某一个专集
    bool                    album_removeAlbums(const QString& album_id);//删除某个专辑及其专辑下面的媒体
    bool                    album_updateAlbumsName(const QString& album_id,const QString& albumName);//更新某个专集名称
    bool                    album_updateAlbumsCover(const QString& album_id,const QString& albumCover);//更新某个专辑封面
    bool                    album_insertOneToAlbums(const QString& album_id,const int media_id);//将某个媒体添加到专集当中
    bool                    album_removeOneFromAlbums(const QString& album_id,const int media_id);//从某个专集中删除某个媒体

    //用户合集
    bool                    group_getCurUserGroups(const QString &user_id);//获取当前用户的所有合集（信号槽发送）
    QList<QUrlQuery>&       group_getCurUserAllGroups(const QString &user_id);//获取某个用户所有的合集
    bool                    group_getCurUserGroupMedias(const QString& group_id);//获取当前用户的某个合集下所有媒体（信号槽发送）
    QList<QVariant>&        group_getCurUserOneGroupAllMedias(const QString& group_id);//获取某个用户某个合集所有的items
    QString                 group_insertGroups(const QString& user_id, const QString& group_name, const QString& group_pix);//添加某个合集
    bool                    group_removeGroups(const QString& group_id);//删除某个合集及其专辑下面的媒体
    bool                    group_updateGroupsName(const QString& group_id,const QString& groupName);//更新合集名称
    bool                    group_updateGroupsCover(const QString& group_id,const QString& groupCover);//更新合集封面
    bool                    group_insertOneToGroups(const QString& group_id,const int media_id);//将某个媒体添加到合集当中
    bool                    group_removeOneFromGroups(const QString& group_id,const int media_id);//从合集中删除某个媒体

    //分类--媒体分类
    QList<QVariant>&        sort_getCurUserOneSortAllMedias(const QString& tags);//查询某个分类下的所有媒体

    //用户收益数据
    QList<QStringList>&     income_getUserIncomeRecords(const QString& user_id,const QString& data_start,const QString& data_end);//获取用户收益

protected:


private:
    dataBase();
    static      QString     getHostName();
    static      QString     getHostPort();
    static      QString     getUserName();
    static      QString     getUserPawd();
    static      QString     getDataName();

    void        showResult(const QSqlQuery& query);//展示查询结果
    void        getUserHeaderPix(QNetworkReply* reply);//接收用户头像数据

private:
    QNetworkAccessManager   *m_manager  =   nullptr;

    static  dataBase*       m_pInstance;//全局唯一
    QString                 m_curUserID;//当前用户唯一识别id
    QString                 m_curUserHead;//当前用户头像连接
    QString                 m_curUserName;//当前用户名称
    QString                 m_curUserPawd;//当前用户密码
    int                     m_curUserGrade;//当前用户等级 游客0 普通1 会员2 超级会员3
    QString                 m_time_login;  //最近一次登录
    QString                 m_time_create; // 创建时间
    bool                    m_online;//是否在线
    QPixmap                 m_curHeadPix;//用户头像

    //所有视频作品
    QList<QVariant>        m_videos;

    //专辑
    QList<QUrlQuery>       m_albums;//所有合集
    QList<QVariant>        m_albumItems;//某个合集所有item

    //合集
    QList<QUrlQuery>       m_groups;//所有合集
    QList<QVariant>        m_groupItems;//某个合集所有item

    //媒体分类
    QList<QVariant>        m_sortItems;//某个分类类型下所有item
    //广告
    QList<QVariant>        m_advItems;

    //收益
    QList<QStringList>     m_incomeRecords;

    //数据分析
    QList<QUrlQuery>       m_fans;//所有粉丝
    QList<QUrlQuery>       m_watches;//所有关注
    QList<QUrlQuery>       m_collections;//所有收藏视频
    QList<QUrlQuery>       m_commits;//所有评论

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

    //视频类型
    QStringList videoTypeList;//视频分类

signals:
    void        sig_loginStatusChanged(bool);//0下线 1登录
    void        sig_sendVideoDramaInfo(QVariant&);//推荐剧集列表
    void        sig_sendRecThemeVideos(QVariant&);//相关主题视频
    void        sig_sendRecThemeVideocounts(int);//相关主题视频数量
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

    void        sig_header_history(QString,QString);// id +url
    void        sig_header_man(QString);
    void        sig_header_woman(QString);
    void        sig_header_gif(QString);

    //合集
    void        sig_group_allgroups(QString,QString,QString);//name + pix + id
    void        sig_group_groupMedias(QVariant&);//返回媒体信息

    //专辑
    void        sig_album_allalbums(QString,QString,QString);//name + pix + id
    void        sig_album_albumMedias(QVariant&);//返回媒体信息
};

#endif // DATABASE_H

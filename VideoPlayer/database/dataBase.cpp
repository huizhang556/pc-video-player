#include "dataBase.h"
#include "global/Global.h"
#include "videomodels/RecomVideoTab.h" //引入结构体
#include "creator/producer/FilesItem.h"//引入结构体
#include <QMetaType>
#include <QDateTime>
#include <QDebug>

//静态成员类外初始化
QString   dataBase::m_hostName = "";
QString   dataBase::m_hostPort = "";
QString   dataBase::m_userName = "";
QString   dataBase::m_userPawd = "";
QString   dataBase::m_dataName = "";

QString  dataBase::m_webDef_Url = "";
QString  dataBase::m_webDef_title = "";
QString  dataBase::m_webDef_user = "";
QString  dataBase::m_webDef_userId = "";
QString  dataBase::m_webDef_savePath = "";

QString  dataBase::m_skin_theme = "";
bool     dataBase::m_skin_switch = true;
QString  dataBase::m_skin_splash = "";
int      dataBase::m_splash_width = 900;//默认宽度
int      dataBase::m_splash_height = 500;//默认高度
dataBase* dataBase::m_pInstance = nullptr;

dataBase::dataBase():
    m_online(true),
    m_curUserID("0000000001"),
    m_curUserHead(""),
    m_curUserName(""),
    m_curUserGrade(1)
{
    qRegisterMetaType<UserInfo>("UserInfo"); //构造函数注册自定义结构体
    qRegisterMetaType<Message>("Message"); //构造函数注册自定义结构体
    qRegisterMetaType<QVariant>("QVariant"); //构造函数注册自定义结构体
    initWorkUI();
    handleSignalsAndSlots();
}

QString dataBase::getHostName()
{
    return m_hostName;
}

QString dataBase::getHostPort()
{
    return  m_hostPort;
}

QString dataBase::getUserName()
{
    return m_userName;
}

QString dataBase::getUserPawd()
{
    return m_userPawd;
}

QString dataBase::getDataName()
{
    return m_dataName;
}

void dataBase::showResult(const QSqlQuery &query)
{
    QSqlRecord rec = query.record();
    qDebug() << QString(u8"查询结果集展示：结果条数：%1 每条列数：%2").arg(query.size()).arg(rec.count());
}

void dataBase::getUserHeaderPix(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        m_curHeadPix.loadFromData(reply->readAll());
        qDebug() <<QString::fromLocal8Bit("[数据库：]网络请求图片成功！");
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("[数据库]请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/user/default_failed.png");//默认图标
        m_curHeadPix = pixmap;
    }
}


dataBase::~dataBase()
{
    if(m_pInstance != nullptr)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

dataBase *dataBase::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new dataBase();
    }
    return m_pInstance;
}

void dataBase::handleSignalsAndSlots()
{
    //登录状态改变
    connect(this,&dataBase::sig_loginStatusChanged,[=](bool status){
       qDebug() << "login status = "<< status;
    });

    connect(m_manager,&QNetworkAccessManager::finished,this,&dataBase::getUserHeaderPix,Qt::UniqueConnection);
}

QSqlDatabase dataBase::getSqlDataBase()
{
    return QSqlDatabase::database("connect_mysql");//根据连接名获取
}

/*连接mysql数据库，创建数据库表*/
bool dataBase::creatMysqlConnection()
{
    qDebug() << QString::fromLocal8Bit("Qt现在支持的驱动：")<<QSqlDatabase::drivers();
    QSqlDatabase db_mysql = QSqlDatabase::addDatabase("QMYSQL","connect_mysql");//连接数据库类型
    db_mysql.setHostName(m_hostName);
    db_mysql.setUserName(m_userName);
    db_mysql.setPassword(m_userPawd);
    db_mysql.setPort(m_hostPort.toInt());
    db_mysql.setDatabaseName(m_dataName);//给数据库起名字
//    db_mysql.setConnectOptions(QString(u8'MYSQL_OPT_RECONNECT=1;init_command="SET NAMES UTF8"'));
    if(!db_mysql.open())
    {
       qDebug()<<"mysql database is not open!"<<db_mysql.lastError();
       return false;
    }
    else
    {
        qDebug()<<"database is open!";
        qDebug() <<"this DB hasFeature:Transaction:" <<getSqlDataBase().driver()->hasFeature(QSqlDriver::Transactions);
        QSqlQuery query_user(getSqlDataBase());
        //sqlite2.3.4 版本开始,主键自动为自增，但是主键不能设置字符长度，否则失效

        //建表---用户信息表
        QString table_user = R"(
                             CREATE TABLE IF NOT EXISTS `userinfo`  (
                               `id` int(255) NOT NULL,
                               `userid` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                               `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                               `passwd` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                               `emalis` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                               `headpic` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                               `viptype` int(1) NOT NULL,
                               `online` tinyint(1) NOT NULL,
                               `logintime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                               `createtime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                               PRIMARY KEY (`userid`) USING BTREE
                             ) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;)";
        if(query_user.exec(table_user))
            qDebug() << "create table user successfull";
        else
            qDebug() << "create table user failed";

        //建表---收藏记录表
        QSqlQuery query_record(getSqlDataBase());
        QString table_record = R"(
                               CREATE TABLE IF NOT EXISTS `collectrecords`  (
                                 `id` int(20) NOT NULL AUTO_INCREMENT,
                                 `userid` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                 `urlnick` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                 `url` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                 `createtime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                                 PRIMARY KEY (`id`) USING BTREE
                               ) ENGINE = InnoDB AUTO_INCREMENT = 34 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;)";
        if(query_record.exec(table_record))
            qDebug() << "create table collectrecords successfull";
        else
            qDebug() << "create table collectrecords failed";

        //创建历史记录表
        QSqlQuery query_history(getSqlDataBase());
        QString table_history = R"(
                                CREATE TABLE IF NOT EXISTS `historyrecords`  (
                                  `id` int(20) NOT NULL AUTO_INCREMENT,
                                  `userid` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                  `url` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                  `createtime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                                  PRIMARY KEY (`id`) USING BTREE
                                ) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;)";
        if(query_history.exec(table_history))
            qDebug() << "create table historyrecords successfull";
        else
            qDebug() << "create table historyrecords failed";

        //创建本地音乐表
        QSqlQuery query_music(getSqlDataBase());
        QString table_music = R"(
                              CREATE TABLE IF NOT EXISTS `localmusic`  (
                                `id` int(20) NOT NULL AUTO_INCREMENT,
                                `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                `path` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                `quality` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                                PRIMARY KEY (`id`) USING BTREE
                              ) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;)";
        if(query_music.exec(table_music))
            qDebug() << "create table localmusic successfull";
        else
            qDebug() << "create table localmusic failed";


        //创建剧集列表
        QSqlQuery query_dramalist(getSqlDataBase());
        QString table_dramalist = R"(
                              CREATE TABLE IF NOT EXISTS `dramalist`  (
                              `id` int(20) NOT NULL AUTO_INCREMENT,
                                `userid` int(20) NOT NULL,
                                `alias` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                                `url` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                `duration` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                                `cover` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                                `uplove` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                                `type` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                `theme` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                `size` int(20) NULL DEFAULT NULL,
                                PRIMARY KEY (`id`) USING BTREE
                              ) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;)";
        if(query_dramalist.exec(table_dramalist))
            qDebug() << "create table dramalist successfull!";
        else
            qDebug() << "create table dramalist failed!";
         return true;

         //创建user_header表
         QSqlQuery query_header(getSqlDataBase());
         QString user_header = R"(
                               CREATE TABLE IF NOT EXISTS `user_header`  (
                                 `user_id` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
                                 `pix_id` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
                                 `pix_url` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
                                 `pix_type` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
                                 PRIMARY KEY (`pix_id`) USING BTREE
                               ) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;)";
         if(query_header.exec(user_header))
             qDebug() << "create table user_header successfull!";
         else
             qDebug() << "create table user_header failed!";

         //创建user_groups表
         QSqlQuery query_group(getSqlDataBase());
         QString user_group = R"(
                              CREATE TABLE IF NOT EXISTS `user_groups`  (
                                `user_id` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
                                `group_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
                                `group_pix` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
                                `group_id` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
                                PRIMARY KEY (`group_id`) USING BTREE
                              ) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;)";
         if(query_group.exec(user_group))
             qDebug() << "create table user_group successfull";
         else
             qDebug() << "create table user_group failed";

         //创建groups_drama表
         QSqlQuery query_groups_drama(getSqlDataBase());
         QString groups_drama = R"(
                               CREATE TABLE IF NOT EXISTS `groups_drama`  (
                                `group_id` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
                                  `media_id` int(255) NOT NULL
                                ) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;)";
         if(query_groups_drama.exec(groups_drama))
             qDebug() << "create table groups_drama successfull";
         else
             qDebug() << "create table groups_drama failed";

    }
}

//移出连接
bool dataBase::removeMysqlConnection()
{
    if(getSqlDataBase().isOpen())
    {
        getSqlDataBase().close();
        //这里有个问题：QSqlDatabasePrivate::removeDatabase: connection 'connect_mysql' is still in use, all queries will cease to work.
        //在你关闭它之后，m_db仍然持有你在connect()中配置的数据库的引用,你可以通过分配一个默认构造的QSqlDatabase来重置m_db
        getSqlDataBase() = QSqlDatabase();//构造一个空的，解除占用
        QSqlDatabase::removeDatabase("connect_mysql");
        qDebug() << QString::fromLocal8Bit("mysql数据库已关闭，连接已移除！");
    }
    return true;
}

/*连接QSQLITE数据库*/
bool dataBase::creatSqliteConnection()
{
    qDebug() << QString::fromLocal8Bit("Qt现在支持的驱动：")<<QSqlDatabase::drivers();
    QSqlDatabase db_sqlite = QSqlDatabase::addDatabase("QSQLITE","connect_sqlite");//指定驱动 创建自己的连接名
    db_sqlite.setDatabaseName("mymusic.db");//给数据库起名字
    if(!db_sqlite.open())
    {
       qDebug()<<"sqlite database is not open!"<<db_sqlite.lastError();
       return false;
    }
    else
    {
        qDebug()<<"database is open!";
        QSqlQuery query(getSqlDataBase());
        //sqlite2.3.4 版本开始,主键自动为自增，但是主键不能设置字符长度，否则失效
        query.exec(QString("CREATE TABLE IF NOT EXISTS 'LocalMusic' (S_id INTEGER PRIMARY KEY AUTOINCREMENT, MusicName varchar(50), FileName varchar(50), SongQuality varchar(50));"));
//        query.exec(QString("CREATE TABLE IF NOT EXISTS 'LocalMusic' (序号 int,歌曲名称 varchar,文件路径 varchar,"
//                            "primary key(序号,歌曲名称,文件路径))"));//不能使用中文名
        //创建收藏记录表
        query.exec(QString("CREATE TABLE IF NOT EXISTS 'CollectRecords' (S_id INTEGER PRIMARY KEY AUTOINCREMENT, urlnick varchar(50), url varchar(50));"));
        //创建历史记录表
        query.exec(QString("CREATE TABLE IF NOT EXISTS 'HistoryRecords' (S_id INTEGER PRIMARY KEY AUTOINCREMENT, url varchar(50));"));

        query.exec(QString("CREATE TABLE IF NOT EXISTS 'LoginInfo' (LoginName varchar(30),LoginPwd varchar(20),"
                            "primary key(LoginName))"));//本地音乐列表数据，把歌曲名和歌曲路径给存起来

         return true;
    }
}

bool dataBase::removeSqliteConnection()
{
    if(getSqlDataBase().isOpen())
    {
        getSqlDataBase().close();
        getSqlDataBase() = QSqlDatabase();//构造一个空的，解除占用
        QSqlDatabase::removeDatabase("connect_sqlite");
        qDebug() <<QString(u8"sqlite移出");
    }
    return true;
}



//初始化全局数据
bool dataBase::initGlobalDate()
{
    video_getVideoMediaSortType();//获取视频分类
    browser_loadAllRecordsToList();//收藏记录
    browser_loadAllHisRecordsToList();//历史记录
    video_recDramaInfo();//推荐视频（限制10条加载）
    return true;
}

//更新某个用户的信息
bool dataBase::initCurUserData()
{
    browser_loadAllRecordsToList();//收藏记录
    browser_loadAllHisRecordsToList();
    return true;
}

void dataBase::initWorkUI()
{
    m_manager = new QNetworkAccessManager(this);
}

QString dataBase::getCurrentUserID() const
{
    return m_curUserID;
}

QString dataBase::getCurrentUserName() const
{
    return m_curUserName;
}

QString dataBase::getCurrentUserPawd() const
{
    return m_curUserPawd;
}

QString dataBase::getCurrentUserHead() const
{
    return m_curUserHead;
}

QString dataBase::getCurrentUserLoginTime() const
{
    return m_time_login;
}

QString dataBase::getCurrentUserCreateTime() const
{
    return m_time_create;
}

const QPixmap &dataBase::getCurrentUserHeadPix()
{
    return m_curHeadPix;
}

QStringList &dataBase::getVideoMediaType()
{
    return videoTypeList;
}

int dataBase::getCurrentUserGrade() const
{
    return m_curUserGrade;
}

bool dataBase::getCurrentUserOnline() const
{
    return m_online;
}

void dataBase::readXML(const QString &path)
{
    QFile file(path);
    if(!file.open(QFile::ReadOnly))//只读打开
        return;
    QDomDocument doc;
    if(!doc.setContent(&file))//file转为QDomDocument文档
    {
        file.close();
        return;
    }
    file.close();//转换为文档后，就可以关闭文件
    QDomElement root = doc.documentElement();//返回根节点
    qDebug() << root.nodeName();//---> appconfig
    QDomNode node = root.firstChild();//获得第一个子节点
    while(!node.isNull())
    {
        if(node.isElement())//如果节点是元素
        {
            //节点转换为元素，节点和元素是两种数据结构
            QDomElement e = node.toElement();
            qDebug() << e.tagName();//-->database
            if(e.tagName() == "database")
            {
                QDomNodeList db_list = e.childNodes();//元素下子节点
                for(int i = 0; i < db_list.count(); i++) //遍历子元素，count和size都可以用,可用于标签数计数
                {
                    QDomNode n = db_list.at(i);
                    if(node.isElement())
                    {
                        qDebug()<<n.nodeName()<<":"<<n.toElement().text();
                        if(n.nodeName() == QString("hostName")) m_hostName = n.toElement().text();
                        if(n.nodeName() == QString("hostPort")) m_hostPort = n.toElement().text();
                        if(n.nodeName() == QString("userName")) m_userName = n.toElement().text();
                        if(n.nodeName() == QString("userPawd")) m_userPawd = n.toElement().text();
                        if(n.nodeName() == QString("dataName")) m_dataName = n.toElement().text();
                    }

                }
            }
            else if(e.tagName() == "browser")
            {
                qDebug() << "finded browser node";
                QDomNodeList bro_list = e.childNodes();
                for(int i = 0; i < bro_list.count(); i++)
                {
                    QDomNode node = bro_list.at(i);
                    if(node.isElement())
                    {
                        qDebug()<<node.nodeName()<<":"<<node.toElement().text();
                        if(node.nodeName() == QString("defaultUser"))       m_webDef_user = node.toElement().text();
                        if(node.nodeName() == QString("defaultUserID"))     m_webDef_userId = node.toElement().text();
                        if(node.nodeName() == QString("defaultUrl"))        m_webDef_Url = node.toElement().text();
                        if(node.nodeName() == QString("defaultTitle"))      m_webDef_title = node.toElement().text();
                        if(node.nodeName() == QString("downloadPath"))      m_webDef_savePath = node.toElement().text();
                    }
                }
            }
            else if(e.tagName() == "skin")
            {
                qDebug() << "finded skin node";
                QDomNodeList skin_list = e.childNodes();
                for(int i = 0; i < skin_list.count(); i++)
                {
                    QDomNode node = skin_list.at(i);
                    if(node.isElement())
                    {
                        qDebug()<<node.nodeName()<<":"<<node.toElement().text();
                        if(node.nodeName() == QString("defaultSkin"))      m_skin_theme = node.toElement().text();
                        if(node.nodeName() == QString("splashOn"))
                        {
                            if(node.toElement().text() == "true")
                                m_skin_switch = true;
                            else
                                m_skin_switch = false;
                        }
                        if(node.nodeName() == QString("defaultSplash"))    m_skin_splash = node.toElement().text();
                        if(node.nodeName() == QString("splashwidth"))      m_splash_width = node.toElement().text().toInt();
                        if(node.nodeName() == QString("splashheight"))     m_splash_height = node.toElement().text().toInt();
                    }
                }
            }
            else
            {
                break;
            }
        }
        node = node.nextSibling();//下一个兄弟节点,nextSiblingElement()是下一个兄弟元素
    }
    file.close();//读完记得关闭文件
}

void dataBase::writeXML(const QString &path)
{
    //打开或创建文件
       QFile file("./config/cfg.xml"); //相对路径、绝对路径、资源路径都可以
       if(!file.open(QFile::WriteOnly|QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
           return;

       QDomDocument doc;
       //写入xml头部
       QDomProcessingInstruction instruction; //添加处理命令
       instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
       doc.appendChild(instruction);
       //添加根节点
       QDomElement root=doc.createElement("appconfig");
       doc.appendChild(root);
       //添加第一个子节点及其子元素
       QDomElement book =doc.createElement("book");
       book.setAttribute("id",1); //方式一：创建属性  其中键值对的值可以是各种类型
       QDomAttr time=doc.createAttribute("time"); //方式二：创建属性 值必须是字符串
       time.setValue("2013/6/13");
       book.setAttributeNode(time);
       QDomElement title=doc.createElement("title"); //创建子元素
       QDomText text; //设置括号标签中间的值
       text=doc.createTextNode("C++ primer");
       book.appendChild(title);
       title.appendChild(text);
       QDomElement author=doc.createElement("author"); //创建子元素
       text=doc.createTextNode("Stanley Lippman");
       author.appendChild(text);
       book.appendChild(author);
       root.appendChild(book);

       //添加第二个子节点及其子元素，部分变量只需重新赋值
       book=doc.createElement("book");
       book.setAttribute("id",2);
       time=doc.createAttribute("time");
       time.setValue("2007/5/25");
       book.setAttributeNode(time);
       title=doc.createElement("title");
       text=doc.createTextNode("Thinking in Java");
       book.appendChild(title);
       title.appendChild(text);
       author=doc.createElement("author");
       text=doc.createTextNode("Bruce Eckel");
       author.appendChild(text);
       book.appendChild(author);
       root.appendChild(book);

       //输出到文件
       QTextStream out_stream(&file);
       doc.save(out_stream,4); //缩进4格
       file.close();
}

void dataBase::deleteXML(const QString &path, const QString &node, const QString &newvalue)
{
    //打开文件
        QFile file("test.xml"); //相对路径、绝对路径、资源路径都可以
        if(!file.open(QFile::ReadOnly))
            return;

        //删除一个一级子节点及其元素，外层节点删除内层节点于此相同
        QDomDocument doc;
        if(!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();  //一定要记得关掉啊，不然无法完成操作

        QDomElement root=doc.documentElement();
        QDomNodeList list=doc.elementsByTagName("book"); //由标签名定位
        for(int i=0;i<list.count();i++)
        {
            QDomElement e=list.at(i).toElement();
            if(e.attribute("time")=="2007/5/25")  //以属性名定位，类似于hash的方式，warning：这里仅仅删除一个节点，其实可以加个break
                root.removeChild(list.at(i));
        }

        if(!file.open(QFile::WriteOnly|QFile::Truncate))
            return;
        //输出到文件
        QTextStream out_stream(&file);
        doc.save(out_stream,4); //缩进4格
        file.close();
}

void dataBase::addXML(const QString &path, const QString &node, const QString &newvalue)
{
    //打开文件
        QFile file("test.xml"); //相对路径、绝对路径、资源路径都可以
        if(!file.open(QFile::ReadOnly))
            return;

        //增加一个一级子节点以及元素
        QDomDocument doc;
        if(!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();

        QDomElement root=doc.documentElement();
        QDomElement book=doc.createElement("book");
        book.setAttribute("id",3);
        book.setAttribute("time","1813/1/27");
        QDomElement title=doc.createElement("title");
        QDomText text;
        text=doc.createTextNode("Pride and Prejudice");
        title.appendChild(text);
        book.appendChild(title);
        QDomElement author=doc.createElement("author");
        text=doc.createTextNode("Jane Austen");
        author.appendChild(text);
        book.appendChild(author);
        root.appendChild(book);

        if(!file.open(QFile::WriteOnly|QFile::Truncate)) //先读进来，再重写，如果不用truncate就是在后面追加内容，就无效了
            return;
        //输出到文件
        QTextStream out_stream(&file);
        doc.save(out_stream,4); //缩进4格
        file.close();
}

void dataBase::updateXML(const QString &path, const QString &nodename, const QString &newvalue)
{
    //打开文件
        QFile file("test.xml"); //相对路径、绝对路径、资源路径都可以
        if(!file.open(QFile::ReadOnly))
            return;

        //更新一个标签项,如果知道xml的结构，直接定位到那个标签上定点更新
        //或者用遍历的方法去匹配tagname或者attribut，value来更新
        QDomDocument doc;
        if(!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();

        QDomElement root=doc.documentElement();
        QDomNodeList list=root.elementsByTagName("book");
        QDomNode node=list.at(list.size()-1).firstChild(); //定位到第三个一级子节点的子元素
        QDomNode oldnode=node.firstChild(); //标签之间的内容作为节点的子节点出现,当前是Pride and Projudice
        node.firstChild().setNodeValue("Emma");
        QDomNode newnode=node.firstChild();
        node.replaceChild(newnode,oldnode);

        if(!file.open(QFile::WriteOnly|QFile::Truncate))
            return;
        //输出到文件
        QTextStream out_stream(&file);
        doc.save(out_stream,4); //缩进4格
        file.close();
}

QString dataBase::getWebDef_user()
{
    return m_webDef_user;
}

QString dataBase::getWebDef_userId()
{
    return m_webDef_userId;
}

QString dataBase::getWebDef_url()
{
    return m_webDef_Url;
}

QString dataBase::getWebDef_title()
{
    return m_webDef_title;
}

QString dataBase::getWebDef_savePath()
{
    return m_webDef_savePath;
}

QString dataBase::getSkin_theme()
{
    return m_skin_theme;
}

bool dataBase::getSkin_switch()
{
    return m_skin_switch;
}

QString dataBase::getSkin_splash()
{
    return m_skin_splash;
}

QSize dataBase::getSize_splash()
{
    return QSize(m_splash_width,m_splash_height);
}

//查询某表记录总数
int dataBase::getTableRecordsCounts(const QString &tablename)
{
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select count(*) from %1;").arg(tablename));
    if(isOK)
    {
        if (query.next())
        {
            int counts = query.value(0).toInt();
            qDebug() << "table counts = " << counts;
            return counts;
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找表'%1'总数错误：").arg(tablename) << query.lastError();
        return false;
    }
}

//查询用户是否存在
bool dataBase::getUserExists(const QString &tablename, const QString &username)
{
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select count(name) from %1 where name = '%2';").arg(tablename).arg(username));//count 最好某个字段，效率高
    if(isOK)
    {
        showResult(query);
        if (query.next())
        {
            int counts = query.value(0).toInt();
            qDebug() << "[FIND_DB] user counts = " << counts;
            if(counts > 0)
                return true;//找到用户
            else
                return  false;
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找表'%1'总数错误：").arg(tablename) << query.lastError();
        return false;//没有找到用户
    }
}

//注册个人信息
bool dataBase::register_userInfo(const QString &name, const QString &pwd, const QString &emails)
{
    //注册插入消息
    QSqlQuery query(getSqlDataBase());
    int counts = getTableRecordsCounts("userinfo"); qDebug() << "table all counts =" << counts;
    query.prepare(QString("insert into userinfo(id, userid, name, passwd, emalis, headpic, viptype, online, logintime, createtime) values(?,?,?,?,?,?,?,?,?,?)"));
    query.bindValue(0,counts+1);//id
    QString userid   = QString("%1").arg(counts+1,10,10,QLatin1Char('0')); qDebug() <<"full userid = " << userid;
    query.bindValue(1,userid);//userid
    query.bindValue(2,name);//名称
    query.bindValue(3,pwd);//密码
    query.bindValue(4,emails);//邮箱
    query.bindValue(5,"http://43.143.226.251:8080/group1/user_header/header9.jpg");//默认头像
    query.bindValue(6,1);//VIP类型--普通
    query.bindValue(7,false);//不在线
    query.bindValue(8,QDateTime::currentDateTime().toString("yyyy-MM-dd:hh-mm-ss"));//登陆时间
    query.bindValue(9,QDateTime::currentDateTime().toString("yyyy-MM-dd"));//创建账号时间
    bool isOK = query.exec();
    if(isOK)
    {
         qDebug() <<"register successfull";
//         emit sig_sendMessage();
         return  true;
    }
    else
    {
        return false;
    }

}

//核查名称以及密码
bool dataBase::login_checked_usernameAndPasswd(const QString &name, const QString &pwd)
{
    bool isvaliable = getUserExists("userinfo",name);//1 找到用户 0 没有找到用户
    if(!isvaliable)//没有找到登录用户信息（查无此账号）
    {
        qDebug() << "user account is not finded!";
        return false;
    }
    else//用户找到了
    {
        QSqlQuery query(getSqlDataBase());
        //此举保证肯定有一条用户数据
        bool isOK = query.exec(QString("select passwd from %1 where name = '%2';").arg("userinfo").arg(name));//同一行语句，第一个之后都要使用''
        if(isOK)
        {
            query.first();//QSqlQuery返回的数据集，record是停在第一条记录之前的。所以，在获得数据集后，必须执行next()或first()到第一条记录，这时候record才是有效的。
            QString user_pwd = query.value(0).toString();
            qDebug() << "[FIND_DB] user passwd = " << user_pwd;
            if(user_pwd == pwd)
            {
                qDebug() << "[INPUT] user info passwd is right!";
                return true;
            }
            else
            {
                qDebug() << "[INPUT] user passwd is unright!";
                return false;
            }
        }
        else
        {
            qDebug()<< QString::fromLocal8Bit("查找表'%1'总数错误：").arg("userinfo") << query.lastError();
            return false;
        }
    }
}

//查询个人信息并保存
bool dataBase::login_verification(const QString &name, const QString &pwd)
{
    qDebug() << QString::fromLocal8Bit("要查询的用户名为%1,用户密码为：%2").arg(name).arg(pwd);
    //登录界面传过来的信息不会为空(已做过滤)
    QSqlQuery query(getSqlDataBase());
    //查询注意：所有的字符串在使用arg()方法的时候，都要加'',这个是sql一部分，除非字符串直接写死在sql中；数字不需要加
    bool isOK = query.exec(QString("select userid, passwd, emalis, headpic, viptype, logintime, createtime from userinfo where name = '%1' and passwd = '%2';").arg(name).arg(pwd));
    if(isOK)
    {
        while(query.next())
        {
            QString     m_userId        =   query.value(0).toString();
            QString     m_userPWD       =   query.value(1).toString();
            QString     m_userEmails    =   query.value(2).toString();
            QString     m_headPic       =   query.value(3).toString();
            int         m_vipType       =   query.value(4).toInt();
            QString     m_loginTime     =   query.value(5).toString();
            QString     m_createTime    =   query.value(6).toString();
            //外部使用
            m_curUserID     =   m_userId;
            m_curUserName   =   name;
            m_curUserPawd   =   m_userPWD;
            m_curUserHead   =   m_headPic;
            m_curUserGrade  =   m_vipType;
            m_time_login    =   m_loginTime;
            m_time_create   =   m_createTime;

            qDebug() << QString::fromLocal8Bit("用户：'%1'的信息如下：").arg(name)<<endl
                     <<QString::fromLocal8Bit("唯一id:")<<m_userId<<endl
                     <<QString::fromLocal8Bit("密码：")<<m_userPWD<<endl
                     <<QString::fromLocal8Bit("邮箱：")<<m_userEmails<<endl
                     <<QString::fromLocal8Bit("头像：")<<m_headPic<<endl
                     <<QString::fromLocal8Bit("vip类型：")<<m_vipType<<endl
                     <<QString::fromLocal8Bit("账号登录时间：")<<m_loginTime<<endl
                     <<QString::fromLocal8Bit("账号创建时间：")<<m_createTime<<endl;

    //        m_userDatda.m_userId        =   m_userId;
    //        m_userDatda.m_userName      =   name;
    //        m_userDatda.m_userPwd       =   pwd;
    //        m_userDatda.m_userEmails    =   m_userEmails;
    //        m_userDatda.m_headPic       =   m_headPic;
    //        m_userDatda.m_vipType       =   m_vipType;
    //        m_userDatda.m_userOnline    =   true;//在线
    //        m_userDatda.m_LoginTime     =   QDateTime::currentDateTime().toString("yyyy-MM-dd:hh-mm-ss");//2022-12-23:11:12:36
    //        m_userDatda.m_createTime    =   m_createTime;
            //发射信号(头像和名称)

            login_setLoginStatus(true);//先设置状态，发送信号
            initCurUserData();//初始化要用到状态值
            return true;
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找用户个人所有错误：") << query.lastError();
        return false;
    }

}

//设置在线状态
bool dataBase::login_setLoginStatus(bool status)
{
    if(status)//在线
    {
        QSqlQuery query(getSqlDataBase());
        bool isOK = query.exec(QString("update userinfo set online = %1, logintime = '%2' where userid = '%3';").arg(1).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd:hh-mm-ss")).arg(m_curUserID));
        if(isOK)
        {
            emit sig_loginStatusChanged(true);//上线
            m_online = true;//在线状态
            m_manager->get(QNetworkRequest(QUrl(m_curUserHead)));//每设置一次登陆状态，就请求一次头像
            qDebug()<<"user sign in status data update successful，m_online is true!";
            return true;
        }
        else
        {
            qDebug()<< QString::fromLocal8Bit("更新在线状态失败：") << query.lastError();
            return false;
        }

    }
    else//离线
    {
        QSqlQuery query(getSqlDataBase());
        bool isOK = query.exec(QString("update userinfo set online = %1, logintime = '%2' where userid = '%3';").arg(0).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd:hh-mm-ss")).arg(m_curUserID));
        if(isOK)
        {
            emit sig_loginStatusChanged(false);//离线
            m_online = false;//离线状态
            m_curUserID      = "";
            m_curUserHead    = "";
            m_curUserName    = "";
            m_curUserGrade   =  1;
            qDebug()<<"user sign out status data update successful. m_online is false;";
            return true;
        }
        else
        {
            qDebug()<< QString::fromLocal8Bit("更新离线状态失败：") << query.lastError();
            return false;
        }

    }
}

//设置用户等级
bool dataBase::login_setUserGrade(int grade)
{
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("update userinfo set viptype = %1 where userid = '%2';").arg(grade).arg(m_curUserID));
    if(isOK)
    {
        qDebug()<<"user grade data update successful!";
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("更新用户等级失败：") << query.lastError();
        return false;
    }

}

//找回个人密码
QString dataBase::getback_userPasswd(const QString &name, const QString &emails)
{
    return "";
}

//获取数据库全部收藏记录
void dataBase::browser_loadAllRecordsToList()
{
    if(!m_online)
    {
        qDebug() << QString::fromLocal8Bit("不是在线状态！用户ID:")<< m_curUserID;
        return;
    }
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select urlnick, url, createtime from collectrecords where userid = '%1' order by createtime asc;").arg(m_curUserID));
    if(isOK)
    {
        while (query.next())
        {
            QString urlnick = query.value(0).toString();//nick
            QString url     = query.value(1).toString();//url
            QString ctime   = query.value(2).toString();//time
            emit sig_sendRecordInfo(urlnick,url,ctime);//向外发送
            qDebug() << "database finded data,urlnick =="<<urlnick<< "url =="<<url<<"createtime =="<<ctime;
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找所有收藏记录错误：") << query.lastError();
    }

}

//往数据库添加一条收藏记录
void dataBase::browser_addRecordToList(const QString &urlnick, const QString &url)
{
    if(!m_online)
    {
        qDebug() << QString::fromLocal8Bit("不是在线状态！用户ID:")<< m_curUserID;
        return;
    }
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("insert into collectrecords values(%1,'%2','%3','%4','%5')").arg(0).arg(m_curUserID).arg(urlnick).arg(url).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));//id自增，插入时置为0
    if(isOK)
    {
        qDebug()<<"one data insert successful!";
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("插入记录错误：") << query.lastError();
    }

}

//往数据库删除一条收藏记录
void dataBase::browser_deleteRecordToList(const QString &url)
{
    if(!m_online)
    {
        qDebug() << QString::fromLocal8Bit("不是在线状态！用户ID:")<< m_curUserID;
        return;
    }
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("delete from collectrecords where url = '%1' and userid = '%2';").arg(url).arg(m_curUserID));
    if(isOK)
    {
        qDebug()<<"one data delete successful!";
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("删除记录错误：") << query.lastError();
    }

}

//往数据库更新一条收藏记录
void dataBase::browser_updateRecordToList(const QString &url, const QString &urlnick)
{
    if(!m_online)
    {
        qDebug() << QString::fromLocal8Bit("不是在线状态！用户ID:")<< m_curUserID;
        return;
    }
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("update collectrecords set urlnick='%1' where url = '%2' and userid = '%3';").arg(urlnick).arg(url).arg(m_curUserID));
    if(isOK)
    {
        qDebug()<<"one data update successful!";
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("更新记录错误：") << query.lastError();
    }

}

//获取数据库全部历史记录
void dataBase::browser_loadAllHisRecordsToList()
{
    if(!m_online)
    {
        qDebug() << QString::fromLocal8Bit("不是在线状态！用户ID:")<< m_curUserID;
        return;
    }
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select url, createtime from historyrecords where userid = '%1' order by createtime asc;").arg(m_curUserID));
    if(isOK)
    {
        while (query.next())
        {
            QString url     = query.value(0).toString();
            QString ctime   = query.value(1).toString();
            emit sig_sendHisRecordInfo(url,ctime);//向外发送
            qDebug() << "database finded history data---->" << "url=="<<url << "createtime =="<<ctime;
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找所有历史记录错误：") << query.lastError();
    }

}

//往数据库添加一条历史记录
void dataBase::browser_addHisRecordToList(const QString &url)
{
    if(!m_online)
    {
        qDebug() << QString::fromLocal8Bit("不是在线状态！用户ID:")<< m_curUserID;
        return;
    }
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("insert into historyrecords values(%1,'%2','%3','%4');").arg(0).arg(m_curUserID).arg(url).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    if(isOK)
    {
        qDebug()<<"one history data insert successful!";
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("插入记录错误：") << query.lastError();
    }

}

//往数据库删除一条历史记录
void dataBase::browser_deleteHisRecordToList(const QString &url)
{
    if(!m_online)
    {
        qDebug() << QString::fromLocal8Bit("不是在线状态！用户ID:")<< m_curUserID;
        return;
    }
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("delete from historyrecords where url= '%1' and userid = '%2';").arg(url).arg(m_curUserID));
    if(isOK)
    {
        qDebug()<<"one history data delete successful!";
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("删除记录错误：") << query.lastError();
    }

}

//往数据库删除所有历史记录
void dataBase::browser_deleteAllHisRecordToList()
{
    if(!m_online)
    {
        qDebug() << QString::fromLocal8Bit("不是在线状态！用户ID:")<< m_curUserID;
        return;
    }
    QSqlQuery query(getSqlDataBase());
    bool isOK1 = query.exec(QString("delete from historyrecords where userid = '%1';").arg(m_curUserID));
//    bool isOK1 = query.exec(QString("truncate table historyrecords;"));//清除表所有记录,主键重新设置递增
//    bool isOK2 = query.exec(QString("delete from sqlite_sequence where name = 'historyrecords';"));//重新设置主键自增
    if(isOK1)
    {
        qDebug()<<"all history data truncate successful!";
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("删除所有历史记录错误：") << query.lastError();
    }

}

//推荐列表插入视频
bool dataBase::video_insertRecDramaListDB(const QStringList &parma)
{
    QSqlQuery query(getSqlDataBase());
    //自增id插入时，id为0 参数：记录id 用户id 时长 介绍 url 封面 点赞数 类型 主题
    QString  insert_sql = QString("insert into dramalist values (%1, '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10');").arg(0).arg(m_curUserID).arg(parma.at(0)).arg(parma.at(1)).arg(parma.at(2)).arg(parma.at(3)).arg(parma.at(4)).arg(parma.at(5)).arg(parma.at(6)).arg(parma.at(7));
    bool isOK = query.exec(insert_sql);
    if(isOK)
    {
        qDebug()<< QString::fromLocal8Bit("插入剧集信息成功~");
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("插入剧集信息错误：") << query.lastError();
        return false;
    }

}

//查询推荐列表
bool dataBase::video_recDramaInfo()
{
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select id, alias, url, duration, cover, uplove from dramalist limit 20;"));//限制在20条
    if(isOK)
    {
        while (query.next())
        {
            int id              =   query.value(0).toInt();     //id
            QString alias       =   query.value(1).toString();  //标题说明
            QString url         =   query.value(2).toString();  //播放地址url
            QString duration    =   query.value(3).toString();  //时长
            QString cover       =   query.value(4).toString();  //封面url
            QString uplove      =   query.value(5).toString();  //点赞
            MusicData musicData;//结构体定义的头文件一定要添加进来
            musicData.id        =   id;
            musicData.alias     =   alias;
            musicData.url       =   url;
            musicData.duration  =   duration;
            musicData.cover     =   cover;
            musicData.uplove    =   uplove;
            QVariant musicdata;
            musicdata.setValue(musicData);
//            qDebug() << "finded drama video info = "
//                     << id << alias <<url <<duration << cover << uplove;
            emit sig_sendVideoDramaInfo(musicdata);//主播放器推荐视频+热点资讯推荐视频用
//            emit sig_sendVideoDramaUrl(id,url);//主界面播放用（弃用）
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找所有剧集信息记录错误：") << query.lastError();
        return false;
    }

}

//查询某个主题下的视频
bool dataBase::video_recDrama_of_theme(const QString &theme, int start, int counts)
{
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select id, alias, url, duration, cover, uplove from dramalist where theme = '%1' limit %2,%3;").arg(theme).arg(start).arg(counts));
    if(isOK)
    {
        emit sig_sendRecThemeVideocounts(query.size());
        qDebug() << QString(u8"查找到主题：%1下有%2个视频").arg(theme).arg(query.size());
        while (query.next())
        {
            int id              =   query.value(0).toInt();     //id
            QString alias       =   query.value(1).toString();  //标题说明
            QString url         =   query.value(2).toString();  //播放地址url
            QString duration    =   query.value(3).toString();  //时长
            QString cover       =   query.value(4).toString();  //封面url
            QString uplove      =   query.value(5).toString();  //点赞
            MusicData musicData;//结构体定义的头文件一定要添加进来
            musicData.id        =   id;
            musicData.alias     =   alias;
            musicData.url       =   url;
            musicData.duration  =   duration;
            musicData.cover     =   cover;
            musicData.uplove    =   uplove;
            QVariant musicdata;
            musicdata.setValue(musicData);
            emit sig_sendRecThemeVideos(musicdata);
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找所有剧集信息记录错误：") << query.lastError();
        return false;
    }
}

//获取接下来播放的4个视频
QList<QVariant> &dataBase::adv_getNext4Medais(const QString& theme, const int start, int counts)
{
    m_advItems.clear();
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select id, alias, url, duration, cover, uplove from dramalist where theme = '%1' limit %2,%3;").arg(theme).arg(start).arg(counts));
    if(isOK)
    {
        while (query.next())
        {
            int id              =   query.value(0).toInt();     //id
            QString alias       =   query.value(1).toString();  //标题说明
            QString url         =   query.value(2).toString();  //播放地址url
            QString duration    =   query.value(3).toString();  //时长
            QString cover       =   query.value(4).toString();  //封面url
            QString uplove      =   query.value(5).toString();  //点赞
            MusicData musicData;//结构体定义的头文件一定要添加进来
            musicData.id        =   id;
            musicData.alias     =   alias;
            musicData.url       =   url;
            musicData.duration  =   duration;
            musicData.cover     =   cover;
            musicData.uplove    =   uplove;
            QVariant musicdata;
            musicdata.setValue(musicData);
            m_advItems.append(musicdata);
        }
        return m_advItems;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找广告推荐剧集信息记录错误：") << query.lastError();
        return m_advItems;;
    }
}

QUrlQuery dataBase::adv_getCurMediaUserInfo(const int media_id)
{
    QSqlQuery query(getSqlDataBase());
    QUrlQuery   query_media;
    bool isOK = query.exec(QString("select userid, url, alias,theme from dramalist where id = %1;").arg(media_id));
    if(isOK)
    {
        while (query.next())
        {
            int         m_id     = media_id;
            QString     m_userId = query.value(0).toString();
            QString     m_url    = query.value(1).toString();
            QString     m_alias  = query.value(2).toString();
            QString     m_theme  = query.value(3).toString();
            QString     username = adv_getMediaUserName(m_userId);
            QString     userhead = adv_getMediaUserHeader(m_userId);

            qDebug() << QString(u8"数据库查询到的关于视频：%1 的一些信息如下：").arg(media_id) << endl;
            qDebug() << QString(u8"用户ID:") << m_userId;
            qDebug() << QString(u8"用户名称:") << username;
            qDebug() << QString(u8"用户头像:") << userhead;
            qDebug() << QString(u8"视频ID:") << m_id;
            qDebug() << QString(u8"视频URL:") << m_url;
            qDebug() << QString(u8"视频介绍:") << m_alias;
            qDebug() << QString(u8"视频主题:") << m_theme;



            query_media.addQueryItem(u8"username",username);
            query_media.addQueryItem(u8"userhead",userhead);
            query_media.addQueryItem(u8"userid",m_userId);
            query_media.addQueryItem(u8"url",m_url);
            query_media.addQueryItem(u8"alias",m_alias);
            query_media.addQueryItem(u8"theme",m_theme);

            return query_media;
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找当前广告视频拥有者信息错误：") << query.lastError();
        return query_media;
    }
}

//获取视频分类
bool dataBase::video_getVideoMediaSortType()
{
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select video_type from video_sort;"));
    if(isOK)
    {
        qDebug() << QString(u8"查找到视频主题数量：%1个分类。").arg(query.size());
        while (query.next())
        {

            QString video_type   =   query.value(0).toString();  //标题说明
            videoTypeList.append(video_type);
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找视频主题分类错误：") << query.lastError();
        return false;
    }
}

bool dataBase::creator_getdoneWorks(const QString &tags)
{
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select id, url, alias, duration, cover, type, theme, size from dramalist where userid = %1 and type = '%2';").arg(m_curUserID).arg(tags));
    if(isOK)
    {
        while (query.next())
        {
            fileBody    body;
            body.fid                =   query.value(0).toInt();//id
            body.furl               =   query.value(1).toString();//url
            body.fnick              =   query.value(2).toString();//alias
            body.fduration          =   query.value(3).toString();//duration
            body.fcover             =   query.value(4).toString();//cover
            body.fmedtype           =   query.value(5).toString();//type(音乐，电影等)
            body.fmedtheme          =   query.value(6).toString();//theme(古装，科技等)
            body.fsize              =   query.value(7).toInt();//size
            QVariant    doneMedia;
            doneMedia.setValue(body);
            emit sig_sendUserDoneWorks(doneMedia);//完成作品展示用
            qDebug() << QString(u8"查询到用户：%1 指定类型： %2 的视频集合,且已发出信号！").arg(m_curUserID).arg(tags);
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找 %1 用户拥有剧集信息记录错误").arg(m_curUserID)<< query.lastError();
        return false;
    }
}

//查询某个用户某种类型标签下视频数量
int dataBase::creator_getdoneWorkCounts(const QString &tags)
{
    QSqlQuery query(getSqlDataBase());
    //按某个字段统计效率高
    bool isOK = query.exec(QString("select count(url) from dramalist where userid = %1 and type = '%2';").arg(m_curUserID).arg(tags));
    if(isOK)
    {
        if (query.next())
        {
            int counts = query.value(0).toInt();
            qDebug() << QString(u8"用户：%1 在标签： %2 类型下，有 %3 个文件数量。").arg(m_curUserID).arg(tags).arg(counts);
            return counts;
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找 %1 用户拥有 %2 类型剧集信息记录错误").arg(m_curUserID).arg(tags) << query.lastError();
        return -1;
    }
}

QStringList dataBase::creator_getAllTagsWorkCounts()
{
    QSqlQuery query(getSqlDataBase());
//    getSqlDataBase().transaction();//开启事务
//    getSqlDataBase().commit();//提交事务

    bool isOK = query.exec(QString("select sum(case when type = '%1' then 1 else 0 end) as movie_count,"
                                "sum(case when type = '%2' then 1 else 0 end) as drama_count,"
                                "sum(case when type = '%3' then 1 else 0 end) as short_count,"
                                "sum(case when type = '%4' then 1 else 0 end) as midmov_count,"
                                "sum(case when type = '%5' then 1 else 0 end) as music_count,"
                                "sum(case when type = '%6' then 1 else 0 end) as pic_count"
                                " from dramalist where userid = '%7';").arg("movies").arg("netdrama").arg("shortvideos").arg("midvideos").arg("musics").arg("pictures").arg(m_curUserID));
    if(isOK)
    {
        if(query.next())
        {
            int movie_count     = query.value(0).toInt();   qDebug() << QString(u8"movie_count: %1").arg(movie_count);
            int drama_count     = query.value(1).toInt();   qDebug() << QString(u8"drama_count: %1").arg(drama_count);
            int short_count     = query.value(2).toInt();   qDebug() << QString(u8"short_count: %1").arg(short_count);
            int midmov_count    = query.value(3).toInt();   qDebug() << QString(u8"midmov_count: %1").arg(midmov_count);
            int music_count     = query.value(4).toInt();   qDebug() << QString(u8"music_count: %1").arg(music_count);
            int pic_count       = query.value(5).toInt();   qDebug() << QString(u8"pic_count: %1").arg(pic_count);
            qDebug() << QString(u8"查询到用户：%1 指定各个类型的视频集合数量,且已发出信号！").arg(m_curUserID);
            return QStringList{QString::number(movie_count),
                        QString::number(drama_count),
                        QString::number(short_count),
                        QString::number(midmov_count),
                        QString::number(music_count),
                        QString::number(pic_count)};
        }
    }
    else
    {
        qDebug() <<QString(u8"没有查询到用户：%1 指定各个类型的视频集合数量,且已发出信号！").arg(m_curUserID);
        return QStringList();
    }
}

//从dramalist根据id删除媒体(1.判断是否其他人有引用2.本地删除文件)
bool dataBase::creator_removeOneMediaFromSort(const QString& tags, const int media_id)
{
    QSqlQuery query(getSqlDataBase());
    //字符串一定要以单引号括起来，数字可以不用
    bool isOK = query.exec(QString("delete from dramalist where userid = '%1' and type = '%2' and id =  %3;").arg(m_curUserID).arg(tags).arg(media_id));
    if(isOK)
    {
        qDebug()<<"delete one data from dramalist successful!";
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("delete one data from dramalist failed！because：") << query.lastError();
        return false;
    }
}

//头像部分初始化
void dataBase::header_initHeader()
{
    header_getUserHistory();
    header_getManHeaderList();
    header_getWomanHeaderList();
    header_getGifHeaderList();
}

//查询当前用户历史头像
bool dataBase::header_getUserHistory()
{
    QSqlQuery query(getSqlDataBase());
    //按某个字段统计效率高
    bool isOK = query.exec(QString("select pix_id, pix_url from user_header where user_id = %1 and pix_type = '%2'; ").arg(m_curUserID).arg("custom"));
    if(isOK)
    {
        while (query.next())
        {
            QString pix_id = query.value(0).toString();
            QString pix_url = query.value(1).toString();
            emit sig_header_history(pix_id,pix_url);
//            qDebug() << QString(u8"用户：%1 在标签： %2 类型下找到文件。").arg(m_curUserID).arg("custom");
        }
    }
    else
    {
        qDebug() << QString(u8"用户：%1 在标签： %2 类型下未查找到文件。").arg(m_curUserID).arg("custom");
        return -1;
    }
}

//查询男性头像
bool dataBase::header_getManHeaderList()
{
    QSqlQuery query(getSqlDataBase());
    //按某个字段统计效率高
    bool isOK = query.exec(QString("select pix_url from user_header where user_id = %1 and pix_type = '%2'; ").arg("0000000000").arg("man"));
    if(isOK)
    {
        while (query.next())
        {
            QString pix_url = query.value(0).toString();
            emit sig_header_man(pix_url);
//            qDebug() << QString(u8"用户：%1 在标签： %2 类型下找到文件。").arg("0000000000").arg("man");
        }
    }
    else
    {
        qDebug() << QString(u8"用户：%1 在标签： %2 类型下未查找到文件。").arg("0000000000").arg("man");
        return -1;
    }
}

//查询女性头像
bool dataBase::header_getWomanHeaderList()
{
    QSqlQuery query(getSqlDataBase());
    //按某个字段统计效率高
    bool isOK = query.exec(QString("select pix_url from user_header where user_id = %1 and pix_type = '%2'; ").arg("0000000000").arg("woman"));
    if(isOK)
    {
        while (query.next())
        {
            QString pix_url = query.value(0).toString();
            emit sig_header_woman(pix_url);
//            qDebug() << QString(u8"用户：%1 在标签： %2 类型下找到文件。").arg("0000000000").arg("woman");
        }
    }
    else
    {
        qDebug() << QString(u8"用户：%1 在标签： %2 类型下未查找到文件。").arg("0000000000").arg("woman");
        return -1;
    }
}

//查询动态头像
bool dataBase::header_getGifHeaderList()
{
    QSqlQuery query(getSqlDataBase());
    //按某个字段统计效率高
    bool isOK = query.exec(QString("select pix_url from user_header where user_id = %1 and pix_type = '%2'; ").arg("0000000000").arg("gif"));
    if(isOK)
    {
        while (query.next())
        {
            QString pix_url = query.value(0).toString();
            emit sig_header_gif(pix_url);
//            qDebug() << QString(u8"用户：%1 在标签： %2 类型下找到文件。").arg("0000000000").arg("gif");
        }
    }
    else
    {
        qDebug() << QString(u8"用户：%1 在标签： %2 类型下未查找到文件。").arg("0000000000").arg("gif");
        return -1;
    }
}

//获取某位用户的头像
QString dataBase::adv_getMediaUserHeader(const QString &user_id)
{
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select headpic from userinfo where userid = '%1';").arg(user_id));
    if(isOK)
    {
        while (query.next())
        {
            QString pix_url   = query.value(0).toString();
            qDebug() << QString(u8"在用户：%1 下找到头像资源：%2").arg(user_id).arg(pix_url);
            return pix_url;
        }
    }
    else
    {
        qDebug() << QString(u8"在用户：%1 下查找用户头像资源失败！").arg(user_id);
        return "";
    }
}

QString dataBase::adv_getMediaUserName(const QString &user_id)
{
    QSqlQuery query(getSqlDataBase());
    //按某个字段统计效率高
    bool isOK = query.exec(QString("select name from userinfo where userid = '%1';").arg(user_id));
    if(isOK)
    {
        while (query.next())
        {
            QString user_name   = query.value(0).toString();
            qDebug() << QString(u8"在用户：%1 下找到用户姓名为：%2").arg(user_id).arg(user_name);
            return user_name;
        }
    }
    else
    {
        qDebug() << QString(u8"在用户：%1 下查找用户姓名资源失败！").arg(user_id);
        return "";
    }
}

QString dataBase::adv_getMediaUserId(const int media_id)
{
    QSqlQuery query(getSqlDataBase());
    //按某个字段统计效率高
    bool isOK = query.exec(QString("select userid from dramalist where id = %1;").arg(media_id));
    if(isOK)
    {
        while (query.next())
        {
            QString user_id   = query.value(0).toString();
            qDebug() << QString(u8"根据媒体ID：%1 找到用户ID为：%2").arg(media_id).arg(user_id);
            return user_id;
        }
    }
    else
    {
        qDebug() << QString(u8"根据媒体ID：%1 找到用户ID失败！") << query.lastError();
        return "";
    }
}

bool dataBase::header_inserUsrHeaderToDB(const QString &pix_url, const QString &pix_type)
{
    QSqlQuery query(getSqlDataBase());
    int counts = getTableRecordsCounts("user_header");//先求总数量
    QString pix_id   = QString("%1").arg(counts+1,10,10,QLatin1Char('0'));
    //自增id插入时，id为0 参数： user_id  pix_id  pix_url pix_type
    QString  insert_sql = QString("insert into user_header values ('%1', '%2', '%3', '%4');").arg(m_curUserID).arg(pix_id).arg(pix_url).arg(pix_type);
    bool isOK = query.exec(insert_sql);
    if(isOK)
    {
        qDebug()<< QString::fromLocal8Bit("插入用户头像信息成功~");
        header_updateUserHeader(m_curUserID,pix_url);
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("插入用户头像信息错误：") << query.lastError();
        return false;
    }
}

//更新用户头像
bool dataBase::header_updateUserHeader(const QString &user_id, const QString &pix_url)
{
    QSqlQuery query(getSqlDataBase());
    //字符串一定要以单引号括起来，数字可以不用
    bool isOK = query.exec(QString("update userinfo set headpic = '%1' where userid = '%2';").arg(pix_url).arg(user_id));
    if(isOK)
    {
        qDebug()<<"one header_data update successful!";
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("header_data更新记录错误：") << query.lastError();
        return false;
    }
}

//删除用户历史头像
bool dataBase::header_deleteUserHisHeader(const QString &user_id, const QString &pix_id)
{
    QSqlQuery query(getSqlDataBase());
    //字符串一定要以单引号括起来，数字可以不用
    bool isOK = query.exec(QString("delete from user_header where pix_id = '%1' and user_id = '%2';").arg(pix_id).arg(user_id));
    if(isOK)
    {
        qDebug()<<"one header_data delete successful!";
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("header_data删除记录错误：") << query.lastError();
        return false;
    }
}

//查询当前用户下所有的合集
bool dataBase::group_getCurUserGroups(const QString &user_id)
{
    QSqlQuery query(getSqlDataBase());
    //按某个字段统计效率高
    bool isOK = query.exec(QString("select group_name, group_pix, group_id from user_groups where user_id = '%1';").arg(user_id));
    if(isOK)
    {
        qDebug() << QString(u8"在用户：%1 下找到 %2 个合集。").arg(user_id).arg(query.size());
        while (query.next())
        {
            QString group_name  = query.value(0).toString();
            QString group_pix   = query.value(1).toString();
            QString group_id    = query.value(2).toString();
            emit sig_group_allgroups(group_name,group_pix,group_id);
        }
    }
    else
    {
        qDebug() << QString(u8"用户：%1 下查找到合集失败！").arg(user_id);
        return -1;
    }
}

//获取某个用户所有的合集
QList<QUrlQuery> &dataBase::group_getCurUserAllGroups(const QString &user_id)
{
    m_groups.clear();
    QSqlQuery query(getSqlDataBase());
    //按某个字段统计效率高
    bool isOK = query.exec(QString("select group_name, group_pix, group_id from user_groups where user_id = '%1';").arg(user_id));
    if(isOK)
    {
        qDebug() << QString(u8"在用户：%1 下找到 %2 个合集。").arg(user_id).arg(query.size());
        if(query.size() == 0)
        {
            return m_groups;
        }
        while (query.next())
        {
            QString group_name  = query.value(0).toString();
            QString group_pix   = query.value(1).toString();
            QString group_id    = query.value(2).toString();

            QUrlQuery querys;
            querys.addQueryItem(QString(u8"group_name"),group_name);
            querys.addQueryItem(QString(u8"group_pix"),group_pix);
            querys.addQueryItem(QString(u8"group_id"),group_id);
            m_groups.append(querys);
        }
        qDebug() << QString(u8"用户：%1 下查找到合集已发出！").arg(user_id);
        return m_groups;
    }
    else
    {
        qDebug() << QString(u8"用户：%1 下查找到合集失败！").arg(user_id);
        return m_groups;
    }
}

//查询某个合集下的所有媒体id
bool dataBase::group_getCurUserGroupMedias(const QString &group_id)
{
    QSqlQuery query1(getSqlDataBase());

    bool isOK = query1.exec(QString("select media_id from groups_drama where group_id = '%1';").arg(group_id));
    if(isOK)
    {
        qDebug() << QString(u8"在合集id：%1 下找到 %2 个媒体。").arg(group_id).arg(query1.size());
        while (query1.next())//遍历合集下的media_id
        {
            int media_id = query1.value(0).toInt();//某个media_id
            qDebug() << QString(u8"遍历获取到的group_id:") << media_id;
            //根据id 获取到媒体的详细信息
            QSqlQuery query2(getSqlDataBase());
            bool isOK2 = query2.exec(QString("select url, alias, duration, cover, type, theme, size from dramalist where id = %1;").arg(media_id));
            if(isOK2)
            {
                while (query2.next())
                {
                    fileBody    body;
                    body.fid                =   media_id;                 //id
                    body.furl               =   query2.value(0).toString();//url
                    body.fnick              =   query2.value(1).toString();//alias
                    body.fduration          =   query2.value(2).toString();//duration
                    body.fcover             =   query2.value(3).toString();//cover
                    body.fmedtype           =   query2.value(4).toString();//type(音乐，电影等)
                    body.fmedtheme          =   query2.value(5).toString();//theme(古装，科技等)
                    body.fsize              =   query2.value(6).toInt();//size
                    QVariant    doneMedia;
                    doneMedia.setValue(body);
                    emit sig_group_groupMedias(doneMedia);
                }
            }
            else
            {
                qDebug()<< QString::fromLocal8Bit("查找关于媒体id： %1 信息失败！").arg(media_id) << query1.lastError();
                return false;
            }
        }
    }
    else
    {
        qDebug() << QString(u8"在合集id：%1 下查找文件失败！").arg(group_id);
        return false;
    }
}

//获取某个用户某个合集所有的items
QList<QVariant> &dataBase::group_getCurUserOneGroupAllMedias(const QString &group_id)
{
    m_groupItems.clear();
    QSqlQuery query1(getSqlDataBase());

    bool isOK = query1.exec(QString("select media_id from groups_drama where group_id = '%1';").arg(group_id));
    if(isOK)
    {
        qDebug() << QString(u8"在合集id：%1 下找到 %2 个媒体。").arg(group_id).arg(query1.size());
        if(query1.size() == 0)
        {
            return m_groupItems;
        }
        while (query1.next())//遍历合集下的media_id
        {
            int media_id = query1.value(0).toInt();//某个media_id
            qDebug() << QString(u8"遍历获取到的group_id:") << media_id;
            //根据id 获取到媒体的详细信息
            QSqlQuery query2(getSqlDataBase());
            bool isOK2 = query2.exec(QString("select url, alias, duration, cover, type, theme, size from dramalist where id = %1;").arg(media_id));
            if(isOK2)
            {
                while (query2.next())
                {
                    fileBody    body;
                    body.fid                =   media_id;                 //id
                    body.furl               =   query2.value(0).toString();//url
                    body.fnick              =   query2.value(1).toString();//alias
                    body.fduration          =   query2.value(2).toString();//duration
                    body.fcover             =   query2.value(3).toString();//cover
                    body.fmedtype           =   query2.value(4).toString();//type(音乐，电影等)
                    body.fmedtheme          =   query2.value(5).toString();//theme(古装，科技等)
                    body.fsize              =   query2.value(6).toInt();//size
                    QVariant    doneMedia;
                    doneMedia.setValue(body);
                    m_groupItems.append(doneMedia);
                }

            }
            else
            {
                qDebug()<< QString::fromLocal8Bit("查找关于媒体id： %1 信息失败！").arg(media_id) << query1.lastError();
                return m_groupItems;
            }
        }
        return m_groupItems;
    }
    else
    {
        qDebug() << QString(u8"在合集id：%1 下查找文件失败！").arg(group_id);
        return m_groupItems;
    }
}

//查询某个分类下的所有媒体
QList<QVariant> &dataBase::group_getCurUserOneSortAllMedias(const QString &tags)
{
    m_sortItems.clear();
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select id, url, alias, duration, cover, type, theme, size from dramalist where userid = %1 and type = '%2';").arg(m_curUserID).arg(tags));
    if(isOK)
    {
        qDebug() << QString(u8"查询到用户：%1 指定类型： %2 的视频集合 %3个,且已发出信号！").arg(m_curUserID).arg(tags).arg(query.size());
        while (query.next())
        {
            fileBody    body;
            body.fid                =   query.value(0).toInt();//id
            body.furl               =   query.value(1).toString();//url
            body.fnick              =   query.value(2).toString();//alias
            body.fduration          =   query.value(3).toString();//duration
            body.fcover             =   query.value(4).toString();//cover
            body.fmedtype           =   query.value(5).toString();//type(音乐，电影等)
            body.fmedtheme          =   query.value(6).toString();//theme(古装，科技等)
            body.fsize              =   query.value(7).toInt();//size
            QVariant    doneMedia;
            doneMedia.setValue(body);
            m_sortItems.append(doneMedia);

        }
        return m_sortItems;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找 %1 用户拥有剧集信息记录错误").arg(m_curUserID)<< query.lastError();
        return m_sortItems;
    }
}

//添加某个合集
QString dataBase::group_insertGroups(const QString &user_id, const QString &group_name, const QString &group_pix)
{
    QSqlQuery query(getSqlDataBase());
    QString count_sql = QString("select count(1) from user_groups where user_id = '%1';").arg(user_id);
    bool ok1 = query.exec(count_sql);
    if(ok1)
    {
//        int counts;
//        if(query.next())//必须先选中一条数据
//        {
//            counts = query.value(0).toInt(); qDebug() <<QString(u8"插入前已有：%1个合集").arg(QString::number(counts));
//        }
//        QString group_id   = user_id + QString("_%1").arg(counts+1,3,10,QLatin1Char('0'));//列表3位置：如：0000000002 + 001
        //使用user_id + 随即日期yyMMddhhmmss
        QString group_id   = user_id + QString("_%1").arg(QDateTime::currentDateTime().toString("yyMMddhhmmss"));
        qDebug() << QString(u8"将要插入的列表id:") << group_id;
        QString  insert_sql = QString("insert into user_groups values ('%1', '%2', '%3', '%4');").arg(m_curUserID).arg(group_name).arg(group_pix).arg(group_id);
        bool isOK = query.exec(insert_sql);
        if(isOK)
        {
            qDebug()<< QString::fromLocal8Bit("新建合集group_id：%1 ，name: %2 插入数据成功！").arg(group_id).arg(group_name);
            return group_id;
        }
        else
        {
            qDebug()<< QString::fromLocal8Bit("新建合集group_id：%1 ，name: %2 插入数据失败！").arg(group_id).arg(group_name) << query.lastError();
            return "";
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("新建合集：name: %1 查询合集数量失败！").arg(group_name) << query.lastError();
        return "";
    }
}

//将媒体添加到合集当中
bool dataBase::group_insertOneToGroups(const QString& group_id,const int media_id)
{
    QSqlQuery query_check(getSqlDataBase());
    bool isOK0 = query_check.exec(QString("select * from groups_drama where group_id = '%1' and media_id = %2;").arg(group_id).arg(media_id));
    if(isOK0)
    {
        int counts = query_check.size();
        qDebug() <<QString(u8"插入新数据前查询的结果为：%1个。").arg(counts);
        if(counts != 0)//查到有相同的数据
        {
            return false;//直接返回，不执行任何操作
        }
    }
    //如果没有相同的数据则执行以下语句：
    QSqlQuery query(getSqlDataBase());
    QString  insert_sql = QString("insert into groups_drama values ('%1', %2);").arg(group_id).arg(media_id);
    bool isOK1 = query.exec(insert_sql);
    if(isOK1)
    {
        qDebug()<< QString::fromLocal8Bit("向合集： %1 插入media_id为：%2 的媒体成功!").arg(group_id).arg(media_id);
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("向合集： %1 插入media_id为：%2 的媒体失败!").arg(group_id).arg(media_id) << query.lastError();
        return false;
    }
}

//删除某个合集
bool dataBase::group_removeGroups(const QString &group_id)
{
    QSqlQuery query(getSqlDataBase());
    //1.先删除合集中的item
    bool isOK = query.exec(QString("delete from groups_drama where group_id = '%1';").arg(group_id));
    if(isOK)
    {
        qDebug()<< QString(u8"删除合集：%1 下所有的item成功！").arg(group_id);
        //2.再删除合集
        bool isOK2 = query.exec(QString("delete from user_groups where group_id = '%1';").arg(group_id));
        if(isOK2)
        {
            qDebug()<< QString(u8"从合集列表中删除合集：%1 成功！").arg(group_id);
            return true;
        }
        else
        {
            qDebug()<< QString(u8"从合集列表中删除合集：%1 失败！").arg(group_id) << query.lastError();
            return false;
        }
    }
    else
    {
        qDebug()<< QString(u8"删除合集：%1 下所有的item失败！").arg(group_id) << query.lastError();
        return false;
    }
}

//从合集中删除一条媒体
bool dataBase::group_removeOneFromGroups(const QString &group_id, const int media_id)
{
    QSqlQuery query(getSqlDataBase());
    //字符串一定要以单引号括起来，数字可以不用
    bool isOK = query.exec(QString("delete from groups_drama where group_id = '%1' and media_id = %2;").arg(group_id).arg(media_id));
    if(isOK)
    {
        qDebug()<<"delete one data from groups_drama successful!";
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("delete one data from groups_drama failed！because：") << query.lastError();
        return false;
    }
}

//查询收益记录
QList<QStringList>& dataBase::income_getUserIncomeRecords(const QString &user_id, const QString &data_start, const QString &data_end)
{
    m_incomeRecords.clear();
    QSqlQuery query(getSqlDataBase());
    bool isOK0 = query.exec(QString("select * from income where userid = '%1' and time >= '%2' AND time < '%3';").arg(user_id).arg(data_start).arg(data_end));
    if(isOK0)
    {
        qDebug() <<QString(u8"查询用户：'%1' 在时间段：'%2' - '%3' 之间的记录成功，查到个数为：'%4'！").arg(user_id).arg(data_start).arg(data_end).arg(query.size());
            while (query.next())
            {
                QString time    = query.value(u8"time").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
                QString type    = query.value(u8"type").toString();
                QString amount  = query.value(u8"amount").toString();
                QString status  = query.value(u8"status").toString();
                QString operate = query.value(u8"operate").toString();
                QStringList recordlist;
                recordlist.append(time);
                recordlist.append(type);
                recordlist.append(amount);
                recordlist.append(status);
                recordlist.append(operate);
                m_incomeRecords.append(recordlist);
            }
            return m_incomeRecords;//直接返回，不执行任何操作
    }
    else
    {
        qDebug() <<QString(u8"查询用户：%1 在时间段：%2 - %3 之间的记录失败！").arg(user_id).arg(data_start).arg(data_end);
    }
}

//更新合集名称
bool dataBase::group_updateGroupsName(const QString &group_id, const QString &groupName)
{
    QSqlQuery query(getSqlDataBase());
    //字符串一定要以单引号括起来，数字可以不用
    bool isOK = query.exec(QString("update user_groups set group_name = '%1' where group_id = '%2';").arg(groupName).arg(group_id));
    if(isOK)
    {
        qDebug()<<QString(u8"更新合集id: %1 的名称为： %2 成功！").arg(group_id).arg(groupName);
        return true;
    }
    else
    {
        qDebug()<<QString(u8"更新合集id: %1 的名称为： %2 失败！").arg(group_id).arg(groupName) << query.lastError();
        return false;
    }
}

//更新合集封面
bool dataBase::group_updateGroupsCover(const QString & group_id, const QString & groupCover)
{
    QSqlQuery query(getSqlDataBase());
    //字符串一定要以单引号括起来，数字可以不用
    bool isOK = query.exec(QString("update user_groups set group_pix = '%1' where group_id = '%2';").arg(groupCover).arg(group_id));
    if(isOK)
    {
        qDebug()<<QString(u8"更新合集id: %1 的封面为： %2 成功！").arg(group_id).arg(groupCover);
        return true;
    }
    else
    {
        qDebug()<<QString(u8"更新合集id: %1 的封面为： %2 失败！").arg(group_id).arg(groupCover) << query.lastError();
        return false;
    }
}




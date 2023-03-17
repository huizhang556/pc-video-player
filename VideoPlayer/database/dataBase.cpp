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
    m_online(false),
    m_curUserID("0000000000"),
    m_curUserHead(""),
    m_curUserName(""),
    m_curUserGrade(1)
{
    qRegisterMetaType<UserInfo>("UserInfo"); //构造函数注册自定义结构体
    qRegisterMetaType<Message>("Message"); //构造函数注册自定义结构体
    qRegisterMetaType<QVariant>("QVariant"); //构造函数注册自定义结构体
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
    if(!db_mysql.open())
    {
       qDebug()<<"mysql database is not open!"<<db_mysql.lastError();
       return false;
    }
    else
    {
        qDebug()<<"database is open!";
        QSqlQuery query(getSqlDataBase());
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
        if(query.exec(table_user))
            qDebug() << "create table user successfull";
        else
            qDebug() << "create table user failed";

        //建表---收藏记录表
        QString table_record = R"(
                               CREATE TABLE IF NOT EXISTS `collectrecords`  (
                                 `id` int(20) NOT NULL AUTO_INCREMENT,
                                 `userid` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                 `urlnick` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                 `url` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                 `createtime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                                 PRIMARY KEY (`id`) USING BTREE
                               ) ENGINE = InnoDB AUTO_INCREMENT = 34 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;)";
        if(query.exec(table_record))
            qDebug() << "create table collectrecords successfull";
        else
            qDebug() << "create table collectrecords failed";

        //创建历史记录表
        QString table_history = R"(
                                CREATE TABLE IF NOT EXISTS `historyrecords`  (
                                  `id` int(20) NOT NULL AUTO_INCREMENT,
                                  `userid` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                  `url` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                  `createtime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                                  PRIMARY KEY (`id`) USING BTREE
                                ) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;)";
        if(query.exec(table_history))
            qDebug() << "create table historyrecords successfull";
        else
            qDebug() << "create table historyrecords failed";

        //创建本地音乐表
        QString table_music = R"(
                              CREATE TABLE IF NOT EXISTS `localmusic`  (
                                `id` int(20) NOT NULL AUTO_INCREMENT,
                                `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                `path` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
                                `quality` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
                                PRIMARY KEY (`id`) USING BTREE
                              ) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;)";
        if(query.exec(table_music))
            qDebug() << "create table localmusic successfull";
        else
            qDebug() << "create table localmusic failed";


        //创建剧集列表
        QString table_drama = R"(
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
        if(query.exec(table_drama))
            qDebug() << "create table dramalist successfull";
        else
            qDebug() << "create table dramalist failed";
         return true;
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
    browser_loadAllRecordsToList();
    browser_loadAllHisRecordsToList();
    video_recDramaInfo();
    return true;
}

QString dataBase::getCurrentUserID() const
{
    return m_curUserID;
}

QString dataBase::getCurrentUserName() const
{
    return m_curUserName;
}

QString dataBase::getCurrentUserHead() const
{
    return m_curUserHead;
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
    query.bindValue(5,"http://43.143.226.251:8080/group1/header/header9.jpg");//默认头像
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
    bool isOK = query.exec(QString("select userid, passwd, emalis, headpic, viptype, createtime from userinfo where name = '%1' and passwd = '%2';").arg(name).arg(pwd));
    if(isOK)
    {
        while(query.next())
        {
            QString     m_userId        =   query.value(0).toString();
            QString     m_userPwd       =   query.value(1).toString();
            QString     m_userEmails    =   query.value(2).toString();
            QString     m_headPic       =   query.value(3).toString();
            int         m_vipType       =   query.value(4).toInt();
            QString     m_createTime    =   query.value(5).toString();
            //外部使用
            m_curUserID     =   m_userId;
            m_curUserName   =   name;
            m_curUserHead   =   m_headPic;
            m_curUserGrade  =   m_vipType;

            qDebug() << QString::fromLocal8Bit("用户：'%1'的信息如下：").arg(name)<<endl
                     <<QString::fromLocal8Bit("唯一id:")<<m_userId<<endl
                     <<QString::fromLocal8Bit("密码：")<<m_userPwd<<endl
                     <<QString::fromLocal8Bit("邮箱：")<<m_userEmails<<endl
                     <<QString::fromLocal8Bit("头像：")<<m_headPic<<endl
                     <<QString::fromLocal8Bit("vip类型：")<<m_vipType<<endl
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
            initGlobalDate();//初始化要用到状态值
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
void dataBase::video_insertRecDramaListDB(const QStringList &parma)
{
    QSqlQuery query(getSqlDataBase());
    //自增id插入时，id为0 参数：记录id 用户id 时长 介绍 url 封面 点赞数 类型 主题
    QString  insert_sql = QString("insert into dramalist values (%1, '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10');").arg(0).arg(m_curUserID).arg(parma.at(0)).arg(parma.at(1)).arg(parma.at(2)).arg(parma.at(3)).arg(parma.at(4)).arg(parma.at(5)).arg(parma.at(6)).arg(parma.at(7));
    bool isOK = query.exec(insert_sql);
    if(isOK)
    {
        qDebug()<< QString::fromLocal8Bit("插入剧集信息成功~");
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("插入剧集信息错误：") << query.lastError();
    }

}

//查询推荐列表
bool dataBase::video_recDramaInfo()
{
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select id, alias, url, duration, cover, uplove from dramalist;"));
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
            emit sig_sendVideoDramaUrl(id,url);//主界面播放用
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找所有剧集信息记录错误：") << query.lastError();
        return false;
    }

}

bool dataBase::creator_getdoneWorks(const QString &tags)
{
    QSqlQuery query(getSqlDataBase());
    bool isOK = query.exec(QString("select url, alias, duration, cover, type, theme, size from dramalist where userid = %1 and type = '%2';").arg(m_curUserID).arg(tags));
    if(isOK)
    {
        while (query.next())
        {
            fileBody    body;
            body.furl               =   query.value(0).toString();//url
            body.fnick              =   query.value(1).toString();//alias
            body.fduration          =   query.value(2).toString();//duration
            body.fcover             =   query.value(3).toString();//cover
            body.fmedtype           =   query.value(4).toString();//type(音乐，电影等)
            body.fmedtheme          =   query.value(5).toString();//theme(古装，科技等)
            body.fsize              =   query.value(6).toInt();//size
            QVariant    doneMedia;
            doneMedia.setValue(body);
            emit sig_sendUserDoneWorks(doneMedia);//主播放器推荐视频+热点资讯推荐视频用
            qDebug() << QString(u8"查询到用户：%1 指定类型的视频集合,且已发出信号！").arg(m_curUserID);
        }
        if(!query.next())
        {
            qDebug() << QString(u8"根据查找条件：用户：%1 -- 类型：%2 没有找到数据！").arg(m_curUserID).arg(tags);
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找 %1 用户拥有剧集信息记录错误").arg(m_curUserID)<< query.lastError();
        return false;
    }
}




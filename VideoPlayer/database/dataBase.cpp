#include "dataBase.h"

dataBase* dataBase::m_pInstance = nullptr;

dataBase::dataBase(QObject *parent)
{
    browser_loadAllRecordsToList();
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

/*连接数据库*/
bool dataBase::creatConnection()
{
    QSqlDatabase db_sqlite = QSqlDatabase::addDatabase("QSQLITE");//建库
    db_sqlite.setDatabaseName("mymusic.db");//给数据库起名字
    if(!db_sqlite.open())
    {
       qDebug()<<"database is not open!"<<db_sqlite.lastError();
       return false;
    }
    else
    {
        qDebug()<<"database is open!";
        QSqlQuery query;
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

//初始化全局数据
bool dataBase::initGlobalDate()
{
    bool isOK1 = browser_loadAllRecordsToList();
    bool isOK2 = browser_loadAllHisRecordsToList();
    return true;
}

//获取数据库全部记录
bool dataBase::browser_loadAllRecordsToList()
{
    QSqlQuery query;
    bool isOK = query.exec(QString("select urlnick, url from CollectRecords;"));
    if(isOK)
    {
        while (query.next())
        {
            QString urlnick = query.value(0).toString();
            QString url     = query.value(1).toString();
            emit sig_sendRecordInfo(urlnick,url);//向外发送
            qDebug() << "database finded data,urlnick=="<<urlnick<< "url=="<<url;
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找所有收藏记录错误：") << query.lastError();
        return false;
    }
}

//往数据库添加一条记录
bool dataBase::browser_addRecordToList(const QString &urlnick, const QString &url)
{
    QSqlQuery query;
    bool isOK = query.exec(QString("insert into CollectRecords values(%1,'%2','%3')").arg("NULL").arg(urlnick).arg(url));
    if(isOK)
    {
        qDebug()<<"one data insert successful!";
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("插入记录错误：") << query.lastError();
        return false;
    }
}

//往数据库删除一条记录
bool dataBase::browser_deleteRecordToList(const QString &url)
{
    QSqlQuery query;
    bool isOK = query.exec(QString("delete from CollectRecords where url= '%1';").arg(url));
    if(isOK)
    {
        qDebug()<<"one data delete successful!";
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("删除记录错误：") << query.lastError();
        return false;
    }
}

//往数据库更新一条记录
bool dataBase::browser_updateRecordToList(const QString &url, const QString &urlnick)
{
    QSqlQuery query;
    bool isOK = query.exec(QString("update CollectRecords set urlnick='%1' where url = '%2';").arg(urlnick).arg(url));
    if(isOK)
    {
        qDebug()<<"one data update successful!";
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("更新记录错误：") << query.lastError();
        return false;
    }
}

//获取数据库全部历史记录
bool dataBase::browser_loadAllHisRecordsToList()
{
    QSqlQuery query;
    bool isOK = query.exec(QString("select url from HistoryRecords;"));
    if(isOK)
    {
        while (query.next())
        {
            QString url     = query.value(0).toString();
            emit sig_sendHisRecordInfo(url);//向外发送
            qDebug() << "database finded history data---->" << "url=="<<url;
        }
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("查找所有历史记录错误：") << query.lastError();
        return false;
    }
}

//往数据库添加一条历史记录
bool dataBase::browser_addHisRecordToList(const QString &url)
{
    QSqlQuery query;
    bool isOK = query.exec(QString("insert into HistoryRecords values(%1,'%2');").arg("NULL").arg(url));
    if(isOK)
    {
        qDebug()<<"one history data insert successful!";
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("插入记录错误：") << query.lastError();
        return false;
    }
}

//往数据库删除一条历史记录
bool dataBase::browser_deleteHisRecordToList(const QString &url)
{
    QSqlQuery query;
    bool isOK = query.exec(QString("delete from HistoryRecords where url= '%1';").arg(url));
    if(isOK)
    {
        qDebug()<<"one history data delete successful!";
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("删除记录错误：") << query.lastError();
        return false;
    }
}

//往数据库删除所有历史记录
bool dataBase::browser_deleteAllHisRecordToList()
{
    QSqlQuery query;
    bool isOK1 = query.exec(QString("delete from HistoryRecords;"));//清除表所有记录
    bool isOK2 = query.exec(QString("delete from sqlite_sequence where name = 'HistoryRecords';"));//重新设置主键自增
    if(isOK1 && isOK2)
    {
        qDebug()<<"all history data delete successful!";
        return true;
    }
    else
    {
        qDebug()<< QString::fromLocal8Bit("删除所有历史记录错误：") << query.lastError();
        return false;
    }
}




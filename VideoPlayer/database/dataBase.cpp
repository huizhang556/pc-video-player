#include "dataBase.h"

dataBase::dataBase()
{

}



/*连接数据库*/
bool dataBase::creatConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//建库
    db.setDatabaseName("mymusic.db");//给数据库起名字
    if(!db.open())
    {
       qDebug()<<"database is not open!"<<db.lastError();
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

        query.exec(QString("CREATE TABLE IF NOT EXISTS 'LoginInfo' (LoginName varchar(30),LoginPwd varchar(20),"
                            "primary key(LoginName))"));//本地音乐列表数据，把歌曲名和歌曲路径给存起来
         return true;
    }
}




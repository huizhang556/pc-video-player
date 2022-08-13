#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QSqlDatabase>
#include <QDesktopWidget>
#include <QDebug>


class dataBase
{
public:
    dataBase();

    static  bool    creatConnection();//创建连接
    //关于浏览器
    static  bool    browser_addRecordToList(const QString &ulr);//往数据库添加一条记录

protected:


private:

};

#endif // DATABASE_H

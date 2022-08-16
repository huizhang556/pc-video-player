#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QSqlDatabase>
#include <QDesktopWidget>
#include <QDebug>


class dataBase : public QObject
{
     Q_OBJECT
public:    
    ~dataBase();
    static  dataBase*       getInstance();
    static  QSqlDatabase    getSqlDataBase();
    static  bool            creatConnection();//创建连接
    bool                    initGlobalDate();//初始化全局数据
    //关于浏览器
    //收藏记录操作
    bool                    browser_loadAllRecordsToList();//获取数据库全部收藏记录
    static  bool            browser_addRecordToList(const QString &urlnick,const QString &url);//往数据库添加一条记录
    static  bool            browser_deleteRecordToList(const QString &url);//往数据库删除一条记录
    static  bool            browser_updateRecordToList(const QString &url,const QString &urlnick);//往数据库更新一条记录
    //历史记录操作
    bool                    browser_loadAllHisRecordsToList();//获取数据库全部历史记录
    static  bool            browser_addHisRecordToList(const QString &url);//往数据库添加一条历史记录
    static  bool            browser_deleteHisRecordToList(const QString &url);//往数据库删除一条历史记录
    static  bool            browser_deleteAllHisRecordToList();//往数据库删除所有历史记录

public:
protected:


private:
    dataBase(QObject *parent = nullptr);
    static  dataBase*       m_pInstance;


signals:
    void        sig_sendRecordInfo(QString,QString);
    void        sig_sendHisRecordInfo(QString);
};

#endif // DATABASE_H

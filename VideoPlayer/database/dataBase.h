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
    static  bool            creatConnection();//创建连接
    //关于浏览器
    bool                    browser_loadAllRecordsToList();//获取数据库全部记录
    static  bool            browser_addRecordToList(const QString &urlnick,const QString &url);//往数据库添加一条记录
    static  bool            browser_deleteRecordToList(const QString &url);//往数据库删除一条记录
    static  bool            browser_updateRecordToList(const QString &url,const QString &urlnick);//往数据库更新一条记录

protected:


private:
    dataBase(QObject *parent = nullptr);
    static  dataBase* m_pInstance;

signals:
    void        sig_sendRecordInfo(QString,QString);

};

#endif // DATABASE_H

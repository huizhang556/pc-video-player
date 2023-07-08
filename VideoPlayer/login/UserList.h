#ifndef USERLIST_H
#define USERLIST_H
#include "global/Global.h"
#include "login/UserItem.h"
#include <QWidget>
#include <QFile>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QTextStream>
#include <QDebug>


//item操作类型
enum UITEMACT
{
    ITEM_ADD,//添加item
    ITEM_ADJ//只调整顺序
};

namespace Ui {
class UserList;
}

class UserList : public QWidget
{
    Q_OBJECT
public:
    explicit UserList(QWidget *parent = nullptr);
    ~UserList();
    void    initWorkUI();

public slots:
    void            slot_addItem(UITEMACT TYPE,const QString& user_nick, const QString& user_pwd, const QString& user_header);
    void            slot_removeItem(const QString& userName);
    void            slot_findUserListResult(const QString& name);


protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::UserList *ui;
    QWidget *m_curWidget = nullptr;
    QStringList nameList = {
        QString(u8"2493920797"),
        QString(u8"天空之城8020"),
        QString(u8"test_guest"),
        QString(u8"风华古城823"),
        QString(u8"美好的明天2023")
    };

private:
    QPushButton* getItemNameButton(const QString& objName, const QString& userName);

public slots:
    //动态计算列表的高度
    void            checkedItemsCounts();

    //本地解析配置文件初始化用户登录列表
    bool            config_initUser();
    //配置文件添加一条用户信息
    bool            config_addNewUser(const QString user_nick, const QString user_pwd, const QString user_header);
    const UITEMACT  config_addUserToJson(QJsonDocument &doc, const QString user_nick, const QString user_pwd, const QString user_header);
    //配置文件移除一条用户信息
    bool            config_removeUser(const QString& user_nick);
    //获取对应用户相应的加密密码
    const QString   config_getUserPwd(const QString& user_nick);

signals:
    void    sig_list_username(QString);
};

#endif // USERLIST_H

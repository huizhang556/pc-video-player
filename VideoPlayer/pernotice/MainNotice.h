#ifndef MAINNOTICE_H
#define MAINNOTICE_H

#define DEF_ITEM_SIZE QSize(396,72)

#include "pernotice/CusItemMsg.h"
#include "pernotice/CusMessage.h"

#include <QWidget>
#include <QSize>
#include <QMenu>
#include <QAction>
#include <QVariant>
#include <QScrollBar>
#include <QDateTime>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QButtonGroup>
#include <QDebug>

//消息类型
enum MSGTYPE
{
    MSG_SYS,//系统消息 0
    MSG_NOR,//非系统（个人号） 1
    MSG_REPLY,//回复的消息 2
    MSG_ABOUT,//@我的消息 3
    MSG_LIKE//点赞我的消息 4
};

//notice 类型
enum NOTICETYPE
{
    NOTICE_SYS,
    NOTICE_L,
    NOTICE_R
};

struct MSGBODY
{
    MSGTYPE type;//消息类型
    QString header;//头像
    QString title;//标题
    QString content;//内容
    QString date;//日期

    bool isTop;//是否置顶
    bool isDisturb;//免打扰
    bool isPush;//是否推送
    bool isBackList;//是否黑名单
};
//以下声明必须加上，否则识别不了结构体
Q_DECLARE_METATYPE(MSGBODY)

namespace Ui {
class MainNotice;
}

class MainNotice : public QWidget
{
    Q_OBJECT

public:
    explicit MainNotice(QWidget *parent = nullptr);
    ~MainNotice();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    static  MainNotice* getInstance();

public slots:
    void    slot_addAboutUserMessages(MSGTYPE type);//添加消息
    void    slot_message_setTop();//置顶
    void    slot_message_donotDisturb();//免打扰
    void    slot_message_closePush();//关闭推送
    void    slot_message_addBlackList();//加入黑名单
    void    slot_message_clearListContent();//清除对话
    void    slot_message_exposeCurUser();//举报当前用户

private:
    void    createSettingRmenu();//创建右键菜单内容
    void    switchStackPageof_notice(QAbstractButton* button);
    void    switchToDetailMessageList(NOTICETYPE type,const QString& authorName);
    void    switchToDetailMessage(const QString& title, const QString& datatime,const QString& content);
    void    switchToDetailMessage(NOTICETYPE type,const QString& header, const QString& datatime,const QString& content);
    QString &imgPathToHtml(QString &path);//图片路径转换为html语言
private:
    Ui::MainNotice *ui;
    static  MainNotice* m_pInstance;
    QButtonGroup    *m_buttonGroup1 =   nullptr;

    bool    array[10] = {true,false,true,false,true,false,true,false,true,false};

signals:
    void    sig_sendSetting();
    void    sig_item_scroll_top();
    void    sig_item_disturb();
    void    sig_item_closepush();
    void    sig_item_blacklist();
    void    sig_item_exposeuser();
};

#endif // MAINNOTICE_H

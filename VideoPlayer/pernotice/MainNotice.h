#ifndef MAINNOTICE_H
#define MAINNOTICE_H

#define DEF_ITEM_SIZE QSize(396,72)

#include "pernotice/CusItemMsg.h"
#include "pernotice/CusMessage.h"
#include <QWidget>
#include <QSize>
#include <QScrollBar>
#include <QDateTime>
#include <QListWidgetItem>
#include <QButtonGroup>
#include <QDebug>

//消息类型
enum MSGTYPE
{
    MSG_SYS,//系统消息
    MSG_NOR,//非系统（个人号）
    MSG_REPLY,//回复的消息
    MSG_ABOUT,//@我的消息
    MSG_LIKE//点赞我的消息
};

//notice 类型
enum NOTICETYPE
{
    NOTICE_SYS,
    NOTICE_L,
    NOTICE_R
};

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

private:
    void    switchStackPageof_notice(QAbstractButton* button);
    void    switchToDetailMessageList(NOTICETYPE type,const QString& authorName);
    void    switchToDetailMessage(const QString& title, const QString& datatime,const QString& content);
    void    switchToDetailMessage(NOTICETYPE type,const QString& header, const QString& datatime,const QString& content);
private:
    Ui::MainNotice *ui;
    static  MainNotice* m_pInstance;
    QButtonGroup    *m_buttonGroup1     =   nullptr;

    bool    array[10] = {true,false,true,false,true,false,true,false,true,false};
};

#endif // MAINNOTICE_H

#ifndef PERCENTER_H
#define PERCENTER_H

#include "database/dataBase.h"
#include "login/ChangeHead.h"
#include <QWidget>
#include <QScrollBar>
#include <QDebug>

namespace Ui {
class PerCenter;
}

class PerCenter : public QWidget
{
    Q_OBJECT

public:
    explicit PerCenter(QWidget *parent = nullptr);
    ~PerCenter();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();


public slots:
    void    setCurUserInfo(const QString& name, const QPixmap& pix);

private:
    Ui::PerCenter *ui;
    QStringList manager = {
        QString(u8"我的首页"),
        QString(u8"账号数据"),
        QString(u8"等级权益"),
        QString(u8"视频管理"),
        QString(u8"专辑管理"),
        QString(u8"合集管理"),
        QString(u8"视频数据"),
        QString(u8"收益数据")
    };

signals:
    void    sig_person_createguid();//新手创作
    void    sig_person_polish();//发布视频
    void    sig_person_topage(int);//页面转换
};

#endif // PERCENTER_H

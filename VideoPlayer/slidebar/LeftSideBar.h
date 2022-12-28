#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H
#define BTN_HEIGHT   40
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>

namespace Ui {
class LeftSideBar;
}

class LeftSideBar : public QWidget
{
    Q_OBJECT

public:
    explicit LeftSideBar(QWidget *parent = nullptr);
    ~LeftSideBar();
    void    setSlideBarListText(QStringList strList);
    void    setLeftSliderFixedWidth(const int width);

public  slots:
    void    slot_setCurrentIndex(int index);

private:
    //私有函数
    void    initWidgetUi();
    void    handleSignalAndSLots();

private:
    QPushButton         *m_msgBtn       = nullptr;     //底部消息按钮
    QPushButton         *m_setBtn       = nullptr;     //底部设置按钮
    QPushButton         *m_modeBtn      = nullptr;     //底部模式转换
    QPushButton         *m_moreBtn      = nullptr;     //底部展开按钮
    QListWidget         *m_listWidget   = nullptr;    //侧边栏节目列表

signals:
    void    sig_sendPersonMessage(bool);
    void    sig_sendSetting(bool);
    void    sig_sendSkinMode(bool);
    void    sig_sendMore();
    void    sig_sidebarItemChange(int);//item发生改变是发出的信号

};

#endif // LEFTSIDEBAR_H

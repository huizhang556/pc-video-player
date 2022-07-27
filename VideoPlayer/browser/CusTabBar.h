#ifndef CUSTABBAR_H
#define CUSTABBAR_H
#include "customer/CustomTabStyle.h"
#include <QWidget>
#include <QLayout>
#include <QTabBar>
#include <QPushButton>

class CusTabBar : public QWidget
{
    Q_OBJECT

public:
    explicit CusTabBar(QWidget *parent = nullptr);
    ~CusTabBar();
    void            initWorkUI();
    void            chandleSignalsAndSlots();

public slots:
    void            slot_addMarkToTabBar(const QString &icon, const QString &nickname, const QString &address);//添加标签到标签栏
    void            slot_deleteMarkOfTabBar(int index);//删除标签栏的标签
    void            slot_setMarksHidden(bool hide);//隐藏标签栏
    QString         slot_getTabText(int index);//获取标签真实地址
    void            slot_setTabText(const int index, const QString &rename);//设置标签别名
    QIcon           slot_getTabIcon(int index);//获取标签左边图标
    void            slot_setTabIcon(const int index, const QIcon &icon);//设置标签图标
private:
    QTabBar         *m_tabBar       =   nullptr;
//    QPushButton     *m_addTabBtn    =   nullptr;//添加空白标签按钮
    QPushButton     *m_expandBtn    =   nullptr;//展开收藏标签按钮
    QPushButton     *m_hideBtn      =   nullptr;//隐藏标签栏按钮
    QHBoxLayout     *m_hblayout     =   nullptr;

signals:
    void            sig_sendTabAddWebTabBar();
    void            sig_sendTabShowRecords();
};

#endif // CUSTABBAR_H

#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H

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
    void setSlideBarListText();


private:
    //私有函数
    void initWidgetUi();
    void chandleSignalAndSlots();
private:
    QVBoxLayout         *m_vbayout = nullptr;
    QPushButton         *m_expandBtn = nullptr;     //底部展开按钮
    QListWidget         *m_listWidget = nullptr;    //侧边栏节目列表

signals:
    void sig_sidebarItemChange(int index);

};

#endif // LEFTSIDEBAR_H

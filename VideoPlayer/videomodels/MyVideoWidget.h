#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QMenu>
#include <QAction>
#include <QVideoWidget>
#include <QMouseEvent>
#include <QContextMenuEvent>

namespace Ui {
class MyVideoWidget;
}

class MyVideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    explicit MyVideoWidget(QWidget *parent = nullptr);
    ~MyVideoWidget();

protected:
    void    enterEvent(QEvent *e) override;

    void    leaveEvent(QEvent *e) override;

    void    mouseDoubleClickEvent(QMouseEvent *event) override;



public slots:
//    void updatePlayAdustForm();//更新播放栏目位置

private:
    QMenu   *m_videoMenu    =   nullptr;

private slots:
    void    createRightMenu();
    void    slot_menu_mainPlayer();
    void    slot_menu_download();
    void    slot_menu_fullscreen();
    void    slot_menu_scale();
    void    slot_menu_videoinfo();
    void    slot_menu_setting();

signals:
    void    mouseEnterToVideoUI();
    void    mouseLeaveFromVideoUI();


};

#endif // MYVIDEOWIDGET_H

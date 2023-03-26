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
    bool    eventFilter(QObject *watched, QEvent *event)override;


public slots:

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
    void    sig_video_clicked();
    void    mouseEnterToVideoUI();
    void    mouseLeaveFromVideoUI();


};

#endif // MYVIDEOWIDGET_H

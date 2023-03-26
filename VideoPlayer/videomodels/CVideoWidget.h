#ifndef CVIDEOWIDGET_H
#define CVIDEOWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QMenu>
#include <QAction>
#include <QVideoWidget>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QDebug>

namespace Ui {
class CVideoWidget;
}

class CVideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    explicit CVideoWidget(QWidget *parent = nullptr);
    ~CVideoWidget();

public slots:
    void    setCurPlayStatus(bool play);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    QMenu   *m_videoMenu    =   nullptr;

private:
    Ui::CVideoWidget *ui;

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

#endif // CVIDEOWIDGET_H

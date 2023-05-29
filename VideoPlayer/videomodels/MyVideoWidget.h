#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

#include <QWidget>
#include <QWidget>
#include <QEvent>
#include <QMenu>
#include <QAction>
#include <QVideoWidget>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QDebug>

namespace Ui {
class MyVideoWidget;
}

class MyVideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    explicit MyVideoWidget(QWidget *parent = nullptr);
    ~MyVideoWidget();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::MyVideoWidget *ui;
    QMenu   *m_videoMenu    =   nullptr;

private slots:

signals:
    void    sig_video_clicked();
    void    mouseEnterToVideoUI();
    void    mouseLeaveFromVideoUI();
};

#endif // MYVIDEOWIDGET_H

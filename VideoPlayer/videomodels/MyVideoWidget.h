#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QVideoWidget>
#include <QMouseEvent>

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
    void enterEvent(QEvent *e) override;

    void leaveEvent(QEvent *e) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;


public slots:
//    void updatePlayAdustForm();//更新播放栏目位置

private:

signals:
    void mouseEnterToVideoUI();
    void mouseLeaveFromVideoUI();


};

#endif // MYVIDEOWIDGET_H

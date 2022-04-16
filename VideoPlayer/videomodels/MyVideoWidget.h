#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QVideoWidget>

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

public slots:

private:

signals:
    void mouseEnterToVideoUI();
    void mouseLeaveFromVideoUI();


};

#endif // MYVIDEOWIDGET_H

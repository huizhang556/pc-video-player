#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

#include <QWidget>
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

public slots:


};

#endif // MYVIDEOWIDGET_H

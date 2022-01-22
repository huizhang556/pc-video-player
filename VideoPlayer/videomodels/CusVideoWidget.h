#ifndef CUSVIDEOWIDGET_H
#define CUSVIDEOWIDGET_H

#include <QWidget>

namespace Ui {
class CusVideoWidget;
}

class CusVideoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CusVideoWidget(QWidget *parent = nullptr);
    ~CusVideoWidget();

private:
    Ui::CusVideoWidget *ui;
};

#endif // CUSVIDEOWIDGET_H

#ifndef CUSTABWIDGET_H
#define CUSTABWIDGET_H

#include <QWidget>

namespace Ui {
class CusTabWidget;
}

class CusTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CusTabWidget(QWidget *parent = nullptr);
    ~CusTabWidget();

private:
    Ui::CusTabWidget *ui;
};

#endif // CUSTABWIDGET_H

#ifndef CUSLISTWIDGET_H
#define CUSLISTWIDGET_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class CusListWidget;
}

class CusListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit CusListWidget(QWidget *parent = nullptr);
    ~CusListWidget();
    void        handleSignalsAndSlots();

private:
    Ui::CusListWidget *ui;
};

#endif // CUSLISTWIDGET_H

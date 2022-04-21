#ifndef MYSKIN_H
#define MYSKIN_H

#include <QDialog>
#include "MySkinItem.h"
#include <QListWidget>

namespace Ui {
class MySkin;
}

class MySkin : public QDialog
{
    Q_OBJECT

public:
    explicit MySkin(QWidget *parent = nullptr);
    ~MySkin();
    void initWorkUI();
    void chandleSignalAndSlot();

protected:
    bool eventFilter(QObject *watch, QEvent *event) override;

private:
    Ui::MySkin *ui;
};

#endif // MYSKIN_H

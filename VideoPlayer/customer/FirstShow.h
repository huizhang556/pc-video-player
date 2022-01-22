#ifndef FIRSTSHOW_H
#define FIRSTSHOW_H

#include <QWidget>

namespace Ui {
class FirstShow;
}

class FirstShow : public QWidget
{
    Q_OBJECT

public:
    explicit FirstShow(QWidget *parent = nullptr);
    ~FirstShow();

private:
    Ui::FirstShow *ui;
};

#endif // FIRSTSHOW_H

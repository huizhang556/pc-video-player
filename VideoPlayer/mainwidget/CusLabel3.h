#ifndef CUSLABEL3_H
#define CUSLABEL3_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class CusLabel3;
}

class CusLabel3 : public QLabel
{
    Q_OBJECT

public:
    explicit CusLabel3(QWidget *parent = nullptr);
    ~CusLabel3();
    void    initWorkUI();
    void    handleSignalsAndSlots();

private:
    Ui::CusLabel3 *ui;

signals:
    void    sig_send_play();
    void    sig_send_start();
};

#endif // CUSLABEL3_H

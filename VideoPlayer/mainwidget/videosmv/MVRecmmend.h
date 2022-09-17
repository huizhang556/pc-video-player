#ifndef MVRECMMEND_H
#define MVRECMMEND_H

#include <QWidget>

namespace Ui {
class MVRecmmend;
}

class MVRecmmend : public QWidget
{
    Q_OBJECT

public:
    explicit MVRecmmend(QWidget *parent = nullptr);
    ~MVRecmmend();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:

private slots:

private:
    Ui::MVRecmmend *ui;
};

#endif // MVRECMMEND_H

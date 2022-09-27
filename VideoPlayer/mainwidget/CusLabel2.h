#ifndef CUSLABEL2_H
#define CUSLABEL2_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class CusLabel2;
}

class CusLabel2 : public QLabel
{
    Q_OBJECT

public:
    explicit CusLabel2(QWidget *parent = nullptr);
    ~CusLabel2();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::CusLabel2 *ui;

signals:
    void    sig_buttonClicked();
};

#endif // CUSLABEL2_H

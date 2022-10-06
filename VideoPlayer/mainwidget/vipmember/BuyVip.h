#ifndef BUYVIP_H
#define BUYVIP_H

#include <QDialog>

namespace Ui {
class BuyVip;
}

class BuyVip : public QDialog
{
    Q_OBJECT

public:
    ~BuyVip();
    static BuyVip*    getInstance();
protected:
   void  mousePressEvent(QMouseEvent *event) override;

private:
    explicit BuyVip(QWidget *parent = nullptr);
    Ui::BuyVip *ui;
    static BuyVip* m_pInstance;
};

#endif // BUYVIP_H

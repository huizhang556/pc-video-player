#ifndef BUYVIP_H
#define BUYVIP_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class BuyVip;
}

class BuyVip : public QDialog
{
    Q_OBJECT

public:
    ~BuyVip();
    static BuyVip*    getInstance();
    void    initWorkUI();
    void    handleSignalsAndSlots();

protected:
   void  mousePressEvent(QMouseEvent *event) override;

private:
    explicit BuyVip(QWidget *parent = nullptr);
    Ui::BuyVip *ui;
    static BuyVip* m_pInstance;

    QStringList     m_yearVip =
    {
        QString(u8"连续包年"),
        QString(u8"¥298"),
        QString(u8"¥263"),
        QString(u8"¥21.9/月")
    };
    QStringList     m_quarterVip =
    {
        QString(u8"连续包季"),
        QString(u8"¥88"),
        QString(u8"¥68"),
        QString(u8"¥22.7/月")
    };
    QStringList     m_monthVip =
    {
        QString(u8"连续包月"),
        QString(u8"¥30"),
        QString(u8"¥25"),
        QString(u8"¥25/月")
    };
    QStringList     m_freeTimeVip =
    {
        QString(u8"闲时会员"),
        QString(u8"¥18"),
        QString(u8"¥16.5"),
        QString(u8"¥16.5/月")
    };

    QList<QStringList>  m_strList;
};

#endif // BUYVIP_H

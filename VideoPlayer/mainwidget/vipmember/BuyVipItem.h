#ifndef BUYVIPITEM_H
#define BUYVIPITEM_H

#include <QWidget>
#include <QEvent>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class BuyVipItem;
}

class BuyVipItem : public QWidget
{
    Q_OBJECT

public:
    explicit BuyVipItem(QWidget *parent = nullptr);
    ~BuyVipItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setItemMark(const QString& path);

protected:
    bool        eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::BuyVipItem *ui;
    QPushButton     *m_itemMarkButton = nullptr;

signals:
    void    sig_sendMouseClicked(QString);
};

#endif // BUYVIPITEM_H

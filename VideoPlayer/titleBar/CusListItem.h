#ifndef CUSLISTITEM_H
#define CUSLISTITEM_H

#include <QWidget>
#include <QEvent>
#include <QDebug>

namespace Ui {
class CusListItem;
}

class CusListItem : public QWidget
{
    Q_OBJECT

public:
    explicit CusListItem(QWidget *parent = nullptr);
    explicit CusListItem(const QString& icon, const QString& content,QWidget *parent = nullptr);
    ~CusListItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::CusListItem *ui;

signals:
    void    sig_sendItemClose();
    void    sig_sendItemText(QString);
};

#endif // CUSLISTITEM_H

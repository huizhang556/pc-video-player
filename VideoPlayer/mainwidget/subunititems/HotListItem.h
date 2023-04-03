#ifndef HOTLISTITEM_H
#define HOTLISTITEM_H

#include <QWidget>
#include <QStyle>
#include <QScrollBar>
#include <QDebug>

namespace Ui {
class HotListItem;
}

class HotListItem : public QWidget
{
    Q_OBJECT

public:
    explicit HotListItem(QWidget *parent = nullptr);
    explicit HotListItem(const QString& num,const QString& picpath,const QString& maininfo,const QString& info, const QString& hotvalue, QWidget *parent = nullptr);
    ~HotListItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::HotListItem *ui;

private:
    void    setItemOrderText(const QString& num);

signals:

};

#endif // HOTLISTITEM_H

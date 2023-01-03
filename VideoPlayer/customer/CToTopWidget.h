#ifndef CTOTOPWIDGET_H
#define CTOTOPWIDGET_H

#include <QWidget>
#include <QScrollBar>
#include <QLayout>
#include <QDebug>

namespace Ui {
class CToTopWidget;
}

class CToTopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CToTopWidget(QWidget *parent = nullptr);
    ~CToTopWidget();
    void    initWorkUI();
    void    handleSignalsAndSlots();

public slots:
    void    setScrollBarToTop();
    void    setFlushContent();

protected:
    void    addItemToWidget(QWidget* itemWidget);//添加
    void    addItemToWidget(QLayout* layout);//添加
    void    removeItemFromWidget(QWidget *itemWidget);//移除
    void    removeItemFromWidget(QLayoutItem *layout);//移除
private:
    Ui::CToTopWidget *ui;

signals:
    void    sig_scroll_verticalbar(bool);
};

#endif // CTOTOPWIDGET_H

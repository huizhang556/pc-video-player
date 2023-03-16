/*自定义可进行拖动的ListWidget*/
#ifndef CLISTWIDGET_H
#define CLISTWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>

namespace Ui {
class CListWidget;
}

class CListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit CListWidget(QWidget *parent = nullptr);
    ~CListWidget();
    void    initWorkUI();
    void    handleSignalsAndSLots();

protected:
    void    dragEnterEvent();
    void    dropEvent(QDropEvent *event) override;
private:
    Ui::CListWidget *ui;
};

#endif // CLISTWIDGET_H

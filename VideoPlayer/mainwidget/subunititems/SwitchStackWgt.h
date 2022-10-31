#ifndef SWITCHSTACKWGT_H
#define SWITCHSTACKWGT_H
#include "mainwidget/subunititems/SwitchButtons.h"

#include <QWidget>
#include <QEvent>
#include <QStackedWidget>
#include <QLabel>
#include <QDebug>

namespace Ui {
class SwitchStackWgt;
}

class SwitchStackWgt : public QStackedWidget
{
    Q_OBJECT

public:
    explicit SwitchStackWgt(QWidget *parent = nullptr);
    ~SwitchStackWgt();
    void    initWorkUI();
    void    handleSignalsAndSlots();

public slots:
    void    slot_addToStackItemPicture(const QString& list_pic);
    void    slot_addToStackItemPictures(const QStringList & list_pic);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::SwitchStackWgt *ui;
    SwitchButtons       *m_switchButton     =   nullptr;

private:
    void    resizeSwitchButtonSize();
};

#endif // SWITCHSTACKWGT_H

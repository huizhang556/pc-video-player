#ifndef SWITCHSTACKWGT_H
#define SWITCHSTACKWGT_H

#define SACLWIDTH   1200 //开始放大最小宽度1200
#define FIXEDHEIGHT 360  //小于放大宽度设置为固定高 360
#define SCALSIZE    0.28 //放大时 高/宽 比例
#define MINWINSIZE  QSize(830,FIXEDHEIGHT)  //界面最小size
#define RESIZESIZE  QSize(1160,360)     //默认加载是size（一般会被重置）

#include "mainwidget/CusLabel3.h"
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
    void    update_W_H_scale();
};

#endif // SWITCHSTACKWGT_H

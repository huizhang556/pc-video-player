#ifndef CUSVIDEOBOX5_H
#define CUSVIDEOBOX5_H

#include "global/Global.h"
#include "mainwidget/CusVerStackWgt.h"
#include "mainwidget/videomember/CusStackWidget.h"
#include "mainwidget/subunititems/SwitchStackWgt.h"
#include "mainwidget/subunititems/Container00.h"
#include "mainwidget/subunititems/Container01.h"
#include "mainwidget/videomember/VideoSortType.h"
#include <QWidget>
#include <QDebug>

namespace Ui {
class CusVideoBox5;
}

class CusVideoBox5 : public QWidget
{
    Q_OBJECT

public:
    explicit CusVideoBox5(QWidget *parent = nullptr);
    ~CusVideoBox5();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();
    void    addItemToVideosBox(QWidget* widget);
    void    removeItemToVideosBox(QWidget *widget);

private:
    Ui::CusVideoBox5 *ui;
    CusStackWidget      *m_switchStackWgt   =   nullptr;
};

#endif // CUSVIDEOBOX5_H

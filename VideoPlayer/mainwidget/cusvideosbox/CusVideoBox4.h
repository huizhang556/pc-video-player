#ifndef CUSVIDEOBOX4_H
#define CUSVIDEOBOX4_H

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
class CusVideoBox4;
}

class CusVideoBox4 : public QWidget
{
    Q_OBJECT

public:
    explicit CusVideoBox4(QWidget *parent = nullptr);
    ~CusVideoBox4();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();
    void    addItemToVideosBox(QWidget* widget);
    void    removeItemToVideosBox(QWidget *widget);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::CusVideoBox4 *ui;
    CusVerStackWgt      *m_switchStackWgt   =   nullptr;
};

#endif // CUSVIDEOBOX4_H

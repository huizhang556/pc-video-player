#ifndef CUSVIDEOBOX3_H
#define CUSVIDEOBOX3_H
#include "global/Global.h"
#include "customer/CToTopWidget.h"
#include "mainwidget/videomember/CusStackWidget.h"
#include "mainwidget/subunititems/SwitchStackWgt.h"
#include "mainwidget/subunititems/Container00.h"
#include "mainwidget/subunititems/Container01.h"
#include "mainwidget/videomember/VideoSortType.h"
#include <QWidget>
#include <QDebug>


class CusVideoBox3 : public CToTopWidget
{
    Q_OBJECT

public:
    explicit CusVideoBox3(QWidget *parent = nullptr);
    ~CusVideoBox3();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();
    void    addItemToVideosBox(QWidget* widget);
    void    removeItemToVideosBox(QWidget *widget);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:

    CusStackWidget      *m_switchStackWgt   =   nullptr;
};

#endif // CUSVIDEOBOX3_H

#ifndef CUSVIDEOBOX6_H
#define CUSVIDEOBOX6_H
#include "customer/CToTopWidget.h"
#include "global/Global.h"
#include "mainwidget/CusVerStackWgt.h"
#include "mainwidget/subunititems/HotRankList.h"
#include "mainwidget/subunititems/Container00.h"
#include "mainwidget/subunititems/Container01.h"
#include "mainwidget/videomember/VideoSortType.h"
#include <QWidget>
#include <QLayout>
#include <QDebug>

class CusVideoBox6 : public CToTopWidget
{
    Q_OBJECT

public:
    explicit CusVideoBox6(QWidget *parent = nullptr);
    ~CusVideoBox6();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();
    void    addItemToVideosBox(QWidget* widget);
    void    removeItemToVideosBox(QWidget *widget);
    void    addItemToVideosBox(QLayout *layout);
    void    removeItemToVideosBox(QLayoutItem *layout);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:

    CusVerStackWgt      *m_switchStackWgt   =   nullptr;
};

#endif // CUSVIDEOBOX6_H

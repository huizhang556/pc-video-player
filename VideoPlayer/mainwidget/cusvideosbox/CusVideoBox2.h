#ifndef CUSVIDEOBOX2_H
#define CUSVIDEOBOX2_H
#include "customer/CToTopWidget.h"

#include "mainwidget/subunititems/SwitchStackWgt.h"
#include "mainwidget/subunititems/Container00.h"
#include "mainwidget/subunititems/Container01.h"
#include "mainwidget/videomember/VideoSortType.h"
#include <QWidget>

class CusVideoBox2 : public CToTopWidget
{
    Q_OBJECT

public:
    explicit CusVideoBox2(QWidget *parent = nullptr);
    ~CusVideoBox2();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();
    void    addItemToVideosBox(QWidget* widget);
    void    removeItemToVideosBox(QWidget *widget);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:

    SwitchStackWgt      *m_switchStackWgt   =   nullptr;
};


#endif // CUSVIDEOBOX2_H

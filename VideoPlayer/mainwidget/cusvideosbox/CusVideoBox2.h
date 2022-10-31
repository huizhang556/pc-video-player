#ifndef CUSVIDEOBOX2_H
#define CUSVIDEOBOX2_H
#include "mainwidget/subunititems/SwitchStackWgt.h"
#include "mainwidget/subunititems/Container00.h"
#include "mainwidget/subunititems/Container01.h"
#include "mainwidget/videomember/VideoSortType.h"
#include <QWidget>

namespace Ui {
class CusVideoBox2;
}

class CusVideoBox2 : public QWidget
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

private:
    Ui::CusVideoBox2 *ui;
    SwitchStackWgt      *m_switchStackWgt   =   nullptr;
};


#endif // CUSVIDEOBOX2_H

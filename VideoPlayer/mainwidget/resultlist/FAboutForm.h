#ifndef FABOUTFORM_H
#define FABOUTFORM_H

#include "mainwidget/videomember/MemberVideoItem.h"
#include "global/Global.h"
#include <QWidget>

namespace Ui {
class FAboutForm;
}

class FAboutForm : public QWidget
{
    Q_OBJECT

public:
    explicit FAboutForm(QWidget *parent = nullptr);
    ~FAboutForm();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

private:
    Ui::FAboutForm *ui;
};

#endif // FABOUTFORM_H

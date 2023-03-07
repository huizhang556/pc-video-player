#ifndef FUSERFORM_H
#define FUSERFORM_H
#include "global/Global.h"
#include "mainwidget/subunititems/SubModules.h"
#include <QWidget>

namespace Ui {
class FUserForm;
}

class FUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit FUserForm(QWidget *parent = nullptr);
    ~FUserForm();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
    void    slot_addItemToListWidget(const QString& url, const QString& picpath,const QString& info1,const QString& info2);

private:
    Ui::FUserForm *ui;
};

#endif // FUSERFORM_H

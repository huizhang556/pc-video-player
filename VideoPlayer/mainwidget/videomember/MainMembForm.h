#ifndef MAINMEMBFORM_H
#define MAINMEMBFORM_H
#include "customer/CToTopWidget.h"
#include <QWidget>
#include <QLayout>
#include <QListWidget>
#include <QScrollArea>
#include <QListWidgetItem>


class MainMembForm : public CToTopWidget
{
    Q_OBJECT

public:
    explicit MainMembForm(QWidget *parent = nullptr);
    ~MainMembForm();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

private:

};

#endif // MAINMEMBFORM_H

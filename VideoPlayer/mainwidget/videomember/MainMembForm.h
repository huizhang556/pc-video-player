#ifndef MAINMEMBFORM_H
#define MAINMEMBFORM_H

#include <QWidget>
#include <QLayout>
#include <QListWidget>
#include <QScrollArea>
#include <QListWidgetItem>

namespace Ui {
class MainMembForm;
}

class MainMembForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainMembForm(QWidget *parent = nullptr);
    ~MainMembForm();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

private:
    Ui::MainMembForm *ui;
};

#endif // MAINMEMBFORM_H

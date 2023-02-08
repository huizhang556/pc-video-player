#ifndef UPDATER_H
#define UPDATER_H

#include <QDialog>
#include <QButtonGroup>
#include <QDebug>

namespace Ui {
class Updater;
}

class Updater : public QDialog
{
    Q_OBJECT

public:
    explicit Updater(QWidget *parent = nullptr);
    ~Updater();
    static Updater* getInstance();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    exec_();


protected:

private:
    Ui::Updater *ui;
    static Updater* m_pInstance;
    QButtonGroup *buttonGroup   =   nullptr;
};

#endif // UPDATER_H

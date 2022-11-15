#ifndef UPDATER_H
#define UPDATER_H

#include <QDialog>

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

protected:

private:
    Ui::Updater *ui;
    static Updater* m_pInstance;
};

#endif // UPDATER_H

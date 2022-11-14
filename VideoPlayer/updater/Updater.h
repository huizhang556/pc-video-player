#ifndef UPDATER_H
#define UPDATER_H

#include <QDialog>
#include <QMouseEvent>

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
   void  mousePressEvent(QMouseEvent *event) override;

private:
    Ui::Updater *ui;
    static Updater* m_pInstance;
};

#endif // UPDATER_H

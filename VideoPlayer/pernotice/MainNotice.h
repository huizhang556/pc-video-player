#ifndef MAINNOTICE_H
#define MAINNOTICE_H

#include <QWidget>
#include <QButtonGroup>
#include <QDebug>

namespace Ui {
class MainNotice;
}

class MainNotice : public QWidget
{
    Q_OBJECT

public:
    explicit MainNotice(QWidget *parent = nullptr);
    ~MainNotice();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    static  MainNotice* getInstance();

private:
    void    switchStackPageof_notice(QAbstractButton* button);

private:
    Ui::MainNotice *ui;
    static  MainNotice* m_pInstance;
    QButtonGroup    *m_buttonGroup1     =   nullptr;
};

#endif // MAINNOTICE_H

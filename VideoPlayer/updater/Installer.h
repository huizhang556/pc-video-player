#ifndef INSTALLER_H
#define INSTALLER_H

#include <QDialog>
#include <QFileDialog>
#include <QButtonGroup>
#include <QTreeWidgetItem>
#include <QDebug>

namespace Ui {
class Installer;
}

class Installer : public QDialog
{
    Q_OBJECT

public:
    explicit Installer(QWidget *parent = nullptr);
    ~Installer();
    static Installer* getInstance();
    void    initWorkUI();
    void    handleSignalsAndSlots();

private:
    Ui::Installer *ui;
     static Installer* m_pInstance;
     int    m_curPageIndex;
     QButtonGroup   *m_buttonGroup  =   nullptr;

signals:
     void   sig_sendFinished();
};

#endif // INSTALLER_H

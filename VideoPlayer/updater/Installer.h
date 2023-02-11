#ifndef INSTALLER_H
#define INSTALLER_H
#include "customer/BaseDialog.h"
#include <QDialog>
#include <QFileDialog>
#include <QButtonGroup>
#include <QMouseEvent>
#include <QTreeWidgetItem>
#include <QDebug>

namespace Ui {
class Installer;
}

class Installer : public BaseDialog
{
    Q_OBJECT

public:
    explicit Installer(QWidget *parent = nullptr);
    ~Installer();
    static Installer* getInstance();
    void    initWorkUI();
    void    handleSignalsAndSlots();

protected:
//   void  mousePressEvent(QMouseEvent *event) override;
//   void  mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::Installer *ui;
     static         Installer* m_pInstance;
     int            m_curPageIndex;
     QButtonGroup   *m_buttonGroup  =   nullptr;
//     QPoint          m_mvPos;

signals:
     void   sig_sendFinished();
};

#endif // INSTALLER_H

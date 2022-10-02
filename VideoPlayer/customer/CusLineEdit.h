#ifndef CUSLINEEDIT_H
#define CUSLINEEDIT_H
#include "customer/CPushButton.h"
#include <QLineEdit>
#include <QEvent>
#include <QDebug>

namespace Ui {
class CusLineEdit;
}

class CusLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    CusLineEdit(QWidget *parent = nullptr);
    ~CusLineEdit();
    void initWorkUI();
    void handleSignalsAndSLots();

protected:
    void    leaveEvent(QEvent* event) override;
    void    enterEvent(QEvent* event) override;

private:    
    CPushButton* m_pBtn = nullptr;

signals:
    void sig_Search(const QString&);
};

#endif // CUSLINEEDIT_H

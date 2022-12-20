#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QDebug>

namespace Ui {
class CloseButton;
}

class CloseButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CloseButton(QWidget *parent = nullptr);
    ~CloseButton();
    void    initWorkUI();
    void    handleSignalsAndSLots();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    void    resizeRemoveButtonGeometry();

private:
    QPushButton     *m_remButton =  nullptr;
};

#endif // CLOSEBUTTON_H

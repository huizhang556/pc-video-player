#ifndef SELECTBUTTONS_H
#define SELECTBUTTONS_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class SelectButtons;
}

class SelectButtons : public QWidget
{
    Q_OBJECT

public:
    explicit SelectButtons(QWidget *parent = nullptr);
    ~SelectButtons();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    void        setSelectButtonText();
    void        setSelectButton(int num);
private:
    Ui::SelectButtons *ui;
    QButtonGroup        *m_buttonGroup      =   nullptr;
    int                 m_curPageIndex;
private:
    void addPage();
    void subPage();
private slots:
    void    slot_buttonGroupClicked(QAbstractButton *button);

signals:
    void    sig_buttonItemChanged(int);
    void    sig_buttonItemChanged(QString);
};

#endif // SELECTBUTTONS_H

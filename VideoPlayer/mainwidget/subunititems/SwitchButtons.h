#ifndef SWITCHBUTTONS_H
#define SWITCHBUTTONS_H

/*功能：选择转换功能按钮*/
#include <QWidget>
#include <QEvent>
#include <QTimer>
#include <QButtonGroup>
#include <QDebug>

namespace Ui {
class SwitchButtons;
}

class SwitchButtons : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchButtons(QWidget *parent = nullptr);
    ~SwitchButtons();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
    void    slot_setHoverButton(int index);
    void    slot_setCheckedButton(int index);
    void    slot_setUNCheckedButton();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;


private:
    Ui::SwitchButtons *ui;
    QTimer          *m_countDownTimer   =   nullptr;
    QButtonGroup    *m_buttonGroup1     = nullptr;
    int             m_allCounts;
    int             m_curIndex;
signals:
    void    sig_sendButtonNumber(int);
};

#endif // SWITCHBUTTONS_H

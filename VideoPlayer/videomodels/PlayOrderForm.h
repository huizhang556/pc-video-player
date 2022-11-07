#ifndef PLAYORDERFORM_H
#define PLAYORDERFORM_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class PlayOrderForm;
}

class PlayOrderForm : public QWidget
{
    Q_OBJECT

public:
    ~PlayOrderForm();
    void    initWorkUI();
    void    chandleSignalsAndSlots();
    static  PlayOrderForm* getInstance();
public slots:
    bool    clearAndSetButtonCheckedStatus(int index);

protected:
    void    leaveEvent(QEvent *event) override;
private:
    bool    clearButtonCheckedStatus();
    bool    setButtonChedkedStatus(int index);


private:
    explicit PlayOrderForm(QWidget *parent = nullptr);
    Ui::PlayOrderForm *ui;
    QButtonGroup    *m_btnGroup     = nullptr;
    static PlayOrderForm    *m_pInstance;

signals:
    void sig_playerOrder(int index);


};

#endif // PLAYORDERFORM_H

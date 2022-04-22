#ifndef PLAYORDERFORM_H
#define PLAYORDERFORM_H

#include <QWidget>

namespace Ui {
class PlayOrderForm;
}

class PlayOrderForm : public QWidget
{
    Q_OBJECT

public:
    explicit PlayOrderForm(QWidget *parent = nullptr);
    ~PlayOrderForm();
    void initWorkUI();
    void chandleSignalsAndSlots();

public slots:

protected:
    void leaveEvent(QEvent *event) override;
private:
    bool clearButtonCheckedStatus();
    bool setButtonChedkedStatus(int index);

private:
    Ui::PlayOrderForm *ui;


signals:
    void sig_playerOrder(int index);


};

#endif // PLAYORDERFORM_H

#ifndef PLAYCTLADJUSTFORM_H
#define PLAYCTLADJUSTFORM_H

#include <QWidget>

namespace Ui {
class PlayCtlAdjustForm;
}

class PlayCtlAdjustForm : public QWidget
{
    Q_OBJECT

public:
    explicit PlayCtlAdjustForm(QWidget *parent = nullptr);
    ~PlayCtlAdjustForm();

private:
    Ui::PlayCtlAdjustForm *ui;
};

#endif // PLAYCTLADJUSTFORM_H

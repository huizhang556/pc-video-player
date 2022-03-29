#ifndef CONTROLFORM_H
#define CONTROLFORM_H

#include <QWidget>
#include "videomodels/muteDialog.h"
namespace Ui {
class ControlForm;
}

class ControlForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlForm(QWidget *parent = nullptr);
    ~ControlForm();

private slots:
    void on_pushButton_sound_clicked();

private:
    Ui::ControlForm *ui;
    muteDialog                  *m_muteDlg          = nullptr;
};

#endif // CONTROLFORM_H

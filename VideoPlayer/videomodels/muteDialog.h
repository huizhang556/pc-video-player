#ifndef MUTEDIALOG_H
#define MUTEDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QSlider>

namespace Ui {
class muteDialog;
}


class muteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit muteDialog(QWidget *parent = nullptr);
    ~muteDialog();

    void setSpliderValue(int value);

    int  getSpliderValue();


protected:
    void leaveEvent(QEvent *event) override;

private:
    Ui::muteDialog *ui;

signals:
    void sig_SpliderValueChange(int value);
};

#endif // MUTEDIALOG_H

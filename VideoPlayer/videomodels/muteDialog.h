#ifndef MUTEDIALOG_H
#define MUTEDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

namespace Ui {
class muteDialog;
}


class muteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit muteDialog(QWidget *parent = nullptr);
    ~muteDialog();
public slots:
    void setSpliderValue(int value);
    void slot_setSoundValue(bool add);
    int  getSpliderValue();

//    static muteDialog* getInstance();

protected:
    void leaveEvent(QEvent *event) override;
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::muteDialog *ui;
//    static   muteDialog* m_pInstance;

signals:
    void sig_SpliderValueChange(int value);
};

#endif // MUTEDIALOG_H

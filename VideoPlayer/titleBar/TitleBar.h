#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void chandleMainWinStatus(bool status);

private:
    Ui::TitleBar *ui;

signals:
    void sig_winClose();
    void sig_winNormal();
    void sig_winMinimum();
    void sig_doubleClick();
};

#endif // TITLEBAR_H

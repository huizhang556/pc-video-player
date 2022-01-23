#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QTimer>
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
    void initWorker();


protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void chandleMainWinStatus(bool status);
    void getSystemTimeShow();

private:
    void chandleSignalAndSLots();
    void setShowToolTip();

private:
    QTimer          *m_timer1 = nullptr;
    QTimer          *m_timer2 = nullptr;
    QTimer          *m_timer3 = nullptr;
    Ui::TitleBar     *ui;

signals:
    void sig_winClose();
    void sig_winNormal();
    void sig_winMinimum();
    void sig_doubleClick();
};

#endif // TITLEBAR_H

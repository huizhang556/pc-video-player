#ifndef ADVCOVERLAB_H
#define ADVCOVERLAB_H

#include <QLabel>
#include <QStyle>
#include <QDebug>

namespace Ui {
class AdvCoverLab;
}

class AdvCoverLab : public QLabel
{
    Q_OBJECT

public:
    explicit AdvCoverLab(QWidget *parent = nullptr);
    ~AdvCoverLab();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setContinuePlay(const QString& text);
    void    setDuration(const QString& duration);
    void    setCountDown(const QString& num);
    void    setPlayButtonCtl(bool show);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::AdvCoverLab *ui;
    bool    m_clicked = false;

signals:
    void    sig_play();
    void    sig_cancel();
};

#endif // ADVCOVERLAB_H

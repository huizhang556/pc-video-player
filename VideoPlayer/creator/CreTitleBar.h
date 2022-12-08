#ifndef CRETITLEBAR_H
#define CRETITLEBAR_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class CreTitleBar;
}

class CreTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit CreTitleBar(QWidget *parent = nullptr);
    ~CreTitleBar();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();

protected:
    void    mousePressEvent(QMouseEvent *event)override;

private:
    Ui::CreTitleBar *ui;
    bool    m_winMax = false;//默认非最大化

signals:
    void    sig_win_close();
    void    sig_win_min();
    void    sig_win_restore(bool);
};

#endif // CRETITLEBAR_H

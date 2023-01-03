#ifndef SCROLLTOTOP_H
#define SCROLLTOTOP_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class ScrollToTop;
}

class ScrollToTop : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollToTop(QWidget *parent = nullptr);
    ~ScrollToTop();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    static  ScrollToTop* getInstance();

public slots:
    void    scrollToTopShow();
    void    scrollToTopHide();


private:
    Ui::ScrollToTop *ui;
    static  ScrollToTop* m_pInstance;

signals:
    void    sig_sendToTop();//置顶
    void    sig_sendToFlush();//刷新
};

#endif // SCROLLTOTOP_H

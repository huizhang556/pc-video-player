#ifndef HOVERMASK_H
#define HOVERMASK_H

#include <QFrame>

namespace Ui {
class HoverMask;
}

class HoverMask : public QFrame
{
    Q_OBJECT

public:
    explicit HoverMask(QWidget *parent = nullptr);
//    static      HoverMask* getInstance();
    ~HoverMask();
protected:
    void    leaveEvent(QEvent *event) override;


private:
//    static  HoverMask* m_pInstance;

signals:
    void    sig_sendLeave();
};

#endif // HOVERMASK_H

#ifndef HOVERMASK_H
#define HOVERMASK_H

#include <QWidget>

namespace Ui {
class HoverMask;
}

class HoverMask : public QWidget
{
    Q_OBJECT

public:
    static      HoverMask* getInstance();
    ~HoverMask();
protected:
    void    leaveEvent(QEvent *event) override;


private:
    explicit HoverMask(QWidget *parent = nullptr);
    static  HoverMask* m_pInstance;

signals:
    void    sig_sendLeave();
};

#endif // HOVERMASK_H

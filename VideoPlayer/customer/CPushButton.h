#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H
#define DEFSIZE QSize(32,32)
#include <QObject>
#include <QSize>
#include <QPushButton>
#include <QDebug>

class CPushButton : public QPushButton
{
    Q_OBJECT
public:
    CPushButton(QWidget *parent = nullptr);
    ~CPushButton();

public slots:
    void    enterStyle();
    void    leaveStyle();

protected:
//    void    enterEvent(QEvent *event) override;
//    void    leaveEvent(QEvent *event) override;

private:
//    void normalStyle();

signals:

};

#endif // CPUSHBUTTON_H

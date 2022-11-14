#ifndef ELLIPBUTTON_H
#define ELLIPBUTTON_H

#include <QPushButton>

namespace Ui {
class EllipButton;
}

class EllipButton : public QPushButton
{
    Q_OBJECT

public:
    explicit EllipButton(QWidget *parent = nullptr);
    ~EllipButton();

private:

};

#endif // ELLIPBUTTON_H

#ifndef TRIANBUTTON_H
#define TRIANBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>

enum ButtonType
{
    RoundRect,//圆角矩形
    LeftType,
    MidType,
    rightType
};

namespace Ui {
class TrianButton;
}

class TrianButton : public QPushButton
{
    Q_OBJECT

public:
    explicit TrianButton(QWidget *parent = nullptr);
    ~TrianButton();
    void        initWorkUI();
    void        handleSignalsAndSlots();

public slots:
    void        setButtonType(ButtonType type);
    void        setButtonPicture(const QString&path);

protected:
    void    paintEvent(QPaintEvent*event) override;

private slots:


private:
    Ui::TrianButton *ui;
    int     m_offset;
    int     m_triangleWidth;//小三角宽度
    int     m_triangleHeight;//小三角高度
    ButtonType m_type;
};

#endif // TRIANBUTTON_H

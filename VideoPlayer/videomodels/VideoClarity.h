#ifndef VIDEOCLARITY_H
#define VIDEOCLARITY_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QButtonGroup>

namespace Ui {
class VideoClarity;
}

class VideoClarity : public QWidget
{
    Q_OBJECT

public:
    explicit VideoClarity(QWidget *parent = nullptr);
    ~VideoClarity();
    void initWorkUI();
    void handleChandleSignalsAndSlots();

protected:
    void    paintEvent(QPaintEvent* event) override;
    void    leaveEvent(QEvent *event) override;

private:
    Ui::VideoClarity *ui;
    QButtonGroup    *m_buttonGroup;
    int     m_offset;
    int     m_triangleWidth;//小三角宽度
    int     m_triangleHeight;//小三角高度

signals:
    void    sig_clarityChanged(QString);
};

#endif // VIDEOCLARITY_H

#ifndef MASKLABEL_H
#define MASKLABEL_H

#include <QLabel>
#include <QPen>
#include <QStyle>
#include <QBrush>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QDebug>

namespace Ui {
class MaskLabel;
}

class MaskLabel : public QLabel
{
    Q_OBJECT

public:
    explicit MaskLabel(QWidget *parent = nullptr);
    ~MaskLabel();

public slots:
    void    slot_setMask();
    void    slot_clearMask();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;
//    void    paintEvent(QPaintEvent* event)override;

private:
    Ui::MaskLabel *ui;
    bool    m_isMask;

signals:
    void    sig_item_clicked();
};

#endif // MASKLABEL_H

#ifndef ROUNDLAB_H
#define ROUNDLAB_H

#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QDebug>

class RoundLab : public QLabel
{
    Q_OBJECT

public:
    explicit RoundLab(QWidget *parent = nullptr);
    explicit RoundLab(const QPixmap& path = QPixmap(), const QColor& bordercolor = QColor(Qt::red), int border = 6, int padding = 0, QWidget *parent = nullptr);
    ~RoundLab();
    void    initRoundLabel(const QPixmap& path, const QColor& bordercolor, int border, int padding);
    void    setPixmap_(const QPixmap& path);
    void    setPadding(int padding);
    void    setBorderColor(const QColor& color);
    void    setBorderWidth(int width);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;
    void    paintEvent(QPaintEvent* event)override;


private:
    QPixmap m_picpath;
    QColor  m_borberColor   = Qt::red;
    int     m_border        = 6;
    int     m_border_t      = 0;
    int     m_padding       = 0;

signals:
    void    sig_clicked();
};

#endif // ROUNDLAB_H

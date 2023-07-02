#ifndef ROUNDLAB_H
#define ROUNDLAB_H

#include <QPen>
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
    void    setZoom(bool zoom, const int radius = 3);
    void    setPadding(int padding);
    void    setBorderColor(const QColor& color);
    void    setBorderWidth(bool open = false,int width = 0);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;
    void    paintEvent(QPaintEvent* event)override;


private:
    QPixmap m_picpath;
    QPen    m_pen;
    QColor  m_borberColor   = QColor(192, 255, 2);
    bool    m_openBorder    = false;
    bool    m_zoom          = false;
    int     m_radius        = 3;
    int     m_border        = 10;
    int     m_border_t      = 0;
    int     m_padding       = 10;

signals:
    void    sig_clicked();
};

#endif // ROUNDLAB_H

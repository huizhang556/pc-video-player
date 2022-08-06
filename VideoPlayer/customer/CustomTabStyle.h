#ifndef CUSTOMTABSTYLE_H
#define CUSTOMTABSTYLE_H

#include <QPainter>
#include <QProxyStyle>
#include <QStyleOptionTab>

class CustomTabStyle : public QProxyStyle
{
    Q_OBJECT

public:
    explicit CustomTabStyle();
    ~CustomTabStyle();
    void    drawItemText(QPainter *painter, const QRect &rect, int flags, const QPalette &pal,
                         bool enabled, const QString &text, QPalette::ColorRole textRole) const;

private:

};

#endif // CUSTOMTABSTYLE_H

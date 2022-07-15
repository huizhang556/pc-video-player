#include "CustomTabStyle.h"

CustomTabStyle::CustomTabStyle()
{
}

CustomTabStyle::~CustomTabStyle()
{

}

void CustomTabStyle::drawItemText(QPainter *painter,
                                  const QRect &rect,
                                  int flags,
                                  const QPalette &pal,
                                  bool enabled,
                                  const QString &text,
                                  QPalette::ColorRole textRole) const
{
    painter->save();
            flags = Qt::AlignLeft | Qt::AlignVCenter;
            painter->translate(5, 0);
            QCommonStyle::drawItemText(painter, rect,
                                  flags,
                                  pal,
                                  enabled,
                                  text,
                                  textRole);

            painter->restore();
}

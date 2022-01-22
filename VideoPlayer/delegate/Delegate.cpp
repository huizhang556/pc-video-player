#include "Delegate.h"
#include <QDebug>
Delegate::Delegate(QObject *parent) : QItemDelegate(parent)
{
//    QPixmap pixmap(":/123.png");
    QColor color(247,33,33,100);//R G B A
    kHoverItemBackgroundcColor = QBrush(color);
}

void Delegate::onHoverIndexChanged(const QModelIndex &index)
{
    m_hoverrow = index.row();

}
void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->drawText(option.rect,index.data().toString());
    if(index.row() == m_hoverrow)
    {
        painter->fillRect(option.rect, kHoverItemBackgroundcColor);
    }
}



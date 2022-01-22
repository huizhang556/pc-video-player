#ifndef DELEGATE_H
#define DELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QAbstractItemView>
#include <QPainter>
class Delegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit Delegate(QObject *parent = nullptr);

    void onHoverIndexChanged(const QModelIndex& index);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:
private:
    int m_hoverrow;
    QBrush kHoverItemBackgroundcColor;

public slots:
};

#endif // DELEGATE_H


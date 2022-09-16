#ifndef RANKITEM_H
#define RANKITEM_H

#include <QWidget>

namespace Ui {
class RankItem;
}

class RankItem : public QWidget
{
    Q_OBJECT

public:
    explicit RankItem(QWidget *parent = nullptr);
    ~RankItem();

private:
    Ui::RankItem *ui;
};

#endif // RANKITEM_H

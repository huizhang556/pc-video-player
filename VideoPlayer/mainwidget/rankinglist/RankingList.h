#ifndef RANKINGLIST_H
#define RANKINGLIST_H

#include <QWidget>

namespace Ui {
class RankingList;
}

class RankingList : public QWidget
{
    Q_OBJECT

public:
    explicit RankingList(QWidget *parent = nullptr);
    ~RankingList();
    void        initWorkUI();
    void        handleSignalsAndSlots();

private:
    Ui::RankingList *ui;
};

#endif // RANKINGLIST_H

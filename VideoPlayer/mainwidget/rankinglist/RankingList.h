#ifndef RANKINGLIST_H
#define RANKINGLIST_H

#include <QSize>
#include <QWidget>
#include <QButtonGroup>

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
    void        setInstallEventFilter();

public slots:
    void    slot_addRankListItem();
    void    slot_addSongItem_recommend();
    void    slot_setCheckedButton(QAbstractButton *button);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    void        resizeListWidgetItemWidget();//动态更新item大小

private:
    Ui::RankingList *ui;
    QButtonGroup        *m_buttonGroup1;

signals:

};

#endif // RANKINGLIST_H

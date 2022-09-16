#ifndef RANKLISTITEM_H
#define RANKLISTITEM_H

#define MINSIZE QSize(186,218) //默认最小宽高，不能动态调整比这个值小
#define SCALE   MINSIZE.height()/MINSIZE.width() // 高/宽 比例

#include <QWidget>
#include <QSize>

namespace Ui {
class RankListItem;
}

class RankListItem : public QWidget
{
    Q_OBJECT

public:
    explicit RankListItem(QWidget *parent = nullptr);
    ~RankListItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEvevtFilter();



public slots:
    void    slot_addRankListItem();
    void    slot_addSongItem_recommend(const QString& url,const QString&path, const QString& tags, const QString& mark);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    void        resizeListWidgetItemWidget();//动态更新item大小
    int        calculateItemWidth(int width);

private:
    Ui::RankListItem *ui;

signals:
    void    sig_itemSizeChanged(QSize);

};

#endif // RANKLISTITEM_H

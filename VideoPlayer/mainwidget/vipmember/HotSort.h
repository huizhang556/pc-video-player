#ifndef HOTSORT_H
#define HOTSORT_H
#define MINSIZE QSize(186,218) //默认最小宽高，不能动态调整比这个值小
#define SCALE   MINSIZE.height()/MINSIZE.width() // 高/宽 比例
#include <QWidget>

namespace Ui {
class HotSort;
}

class HotSort : public QWidget
{
    Q_OBJECT

public:
    explicit HotSort(QWidget *parent = nullptr);
    ~HotSort();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
    void        slot_addSongItem(const QString& url,const QString&path, const QString& tags, const QString& mark);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::HotSort *ui;

private:
    void        resizeListWidgetItemWidget();//动态更新item大小
    int         calculateItemWidth(int width);
signals:
    void    sig_sendTags(QString);
};

#endif // HOTSORT_H

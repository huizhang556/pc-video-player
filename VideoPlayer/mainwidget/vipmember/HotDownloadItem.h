#ifndef HOTDOWNLOADITEM_H
#define HOTDOWNLOADITEM_H

#include <QWidget>

namespace Ui {
class HotDownloadItem;
}

class HotDownloadItem : public QWidget
{
    Q_OBJECT

public:
    explicit HotDownloadItem(QWidget *parent = nullptr);
    ~HotDownloadItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::HotDownloadItem *ui;

signals:
    void    sig_itemDownload(QString);
};

#endif // HOTDOWNLOADITEM_H

#ifndef HOTDOWNLOAD_H
#define HOTDOWNLOAD_H

#define MINSIZE QSize(400,82)
#define SCALE MINSIZE.width()/MINSIZE.height()

#include <QWidget>
#include <QSize>

namespace Ui {
class HotDownload;
}

class HotDownload : public QWidget
{
    Q_OBJECT

public:
    explicit HotDownload(QWidget *parent = nullptr);
    ~HotDownload();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
    void    slot_addItem();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;
    void    resizeEvent(QResizeEvent *event) override;
private:
    Ui::HotDownload *ui;

private:
    void    resizeListWidgetItemWidget();

signals:
    void    sig_itemSizeChanged(QSize);
};

#endif // HOTDOWNLOAD_H

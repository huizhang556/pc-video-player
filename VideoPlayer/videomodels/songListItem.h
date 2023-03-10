#ifndef SONGLISTITEM_H
#define SONGLISTITEM_H
#include <QTimer>
#include <QWidget>
#include <QFontMetrics>
#include <QFontMetricsF>
#include <QFileInfo>
#include <QDebug>

namespace Ui {
class songListItem;
}

class songListItem : public QWidget
{
    Q_OBJECT

public:
    explicit songListItem(QWidget *parent = nullptr);
    explicit songListItem(const QString& filepath, QWidget *parent = nullptr);
    ~songListItem();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    void        setInstallEventFilter();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::songListItem *ui;
    QString     m_name;

private:
    void    setItemName();

signals:
    void    sig_item_selected(QString);
    void    sig_item_addtolist();
};


#endif // SONGLISTITEM_H

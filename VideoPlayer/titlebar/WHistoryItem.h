#ifndef WHISTORYITEM_H
#define WHISTORYITEM_H

#include <QWidget>

namespace Ui {
class WHistoryItem;
}

class WHistoryItem : public QWidget
{
    Q_OBJECT

public:
    explicit WHistoryItem(QWidget *parent = nullptr);
    explicit WHistoryItem(const QString& picpath, const QString& info, const QString& progress, QWidget *parent = nullptr);
    ~WHistoryItem();
    void    setItemPicture();
    void    setItemInfo();
    void    setItemProgress();

private:
    Ui::WHistoryItem *ui;
    QString     m_picpath;
    QString     m_info;
    QString     m_progress;
};

#endif // WHISTORYITEM_H

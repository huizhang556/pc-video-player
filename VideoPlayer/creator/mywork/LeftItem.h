#ifndef LEFTITEM_H
#define LEFTITEM_H

#include <QWidget>
#include <QStyle>
#include <QDebug>

namespace Ui {
class LeftItem;
}

class LeftItem : public QWidget
{
    Q_OBJECT

public:
    explicit LeftItem(QWidget *parent = nullptr);
    explicit LeftItem(const QString& text, const int counts, QWidget *parent = nullptr);
    ~LeftItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();

public slots:
    void    setItemText(const QString& text);
    void    setItemCounts(int counts);


private:
    Ui::LeftItem *ui;
    QString m_text;
    QString m_counts;

signals:
    void    sig_item_selected(QString);
};

#endif // LEFTITEM_H

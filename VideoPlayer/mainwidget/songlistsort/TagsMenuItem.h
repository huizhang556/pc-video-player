#ifndef TAGSMENUITEM_H
#define TAGSMENUITEM_H


#include <QSize>
#include <QWidget>
#include <QStringList>

namespace Ui {
class TagsMenuItem;
}

class TagsMenuItem : public QWidget
{
    Q_OBJECT

public:
    explicit TagsMenuItem(QWidget *parent = nullptr);
    explicit TagsMenuItem(const QString&titleicon, const QString&title, const QStringList& items, QWidget *parent = nullptr);
    ~TagsMenuItem();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    void        setMenuListWidgetHeight(int counts);
    QSize       getMenuListWidgetHeight();

public  slots:
    void        slot_setTagMenuItemHead(const QString& iconpath,const QString& title);
    void        slot_addTagMenuItem(const QStringList&list);

protected:
    bool        eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::TagsMenuItem *ui;
    QSize           m_size;
    QString         m_titleicon;
    QString         m_title;
    QStringList     m_items;

signals:
    void        sig_sendItemTextChanged(QString);

};

#endif // TAGSMENUITEM_H

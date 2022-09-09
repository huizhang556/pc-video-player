#ifndef SONGLISTSORT_H
#define SONGLISTSORT_H

#include "mainwidget/songlistsort/TagsMenu.h"
#include "mainwidget/songlistsort/TagsItem.h"

#include <QWidget>
#include <QButtonGroup>
#include <QWidgetAction>
#include <QAbstractButton>
#include <QMenu>

namespace Ui {
class SonglistSort;
}

class SonglistSort : public QWidget
{
    Q_OBJECT

public:
    explicit SonglistSort(QWidget *parent = nullptr);
    ~SonglistSort();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    void        clearAllFocusWidgets();
public slots:
    void        slot_addSongItem(const QString& url,const QString&path, const QString& tags, const QString& mark);
    void        slot_emitHotAndNewTags(QAbstractButton* button);
    void        slot_setCheckedButton(QAbstractButton* button);
    void        slot_showTagsMenu();

protected:
    bool        eventFilter(QObject *watched, QEvent *event) override;
    void        resizeEvent(QResizeEvent *event) override;
private:
    Ui::SonglistSort *ui;
    QButtonGroup        *m_buttonGroup1;
    QButtonGroup        *m_buttonGroup2;
    QMenu               *m_menu;
    TagsMenu            *m_tags;
    QWidgetAction       *m_action;

private:
     void       updateMenuGeometry();

signals:
    void    sig_sendSelectTags(QString);
    void    sig_sendTags(QString);
    void    sig_sendToolButtonFocusOut();

};

#endif // SONGLISTSORT_H

#ifndef SONGLISTSORT_H
#define SONGLISTSORT_H

#include <QWidget>
#include <QButtonGroup>

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
public slots:
    void        slot_addSongItem(const QString& url,const QString&path, const QString& tags, const QString& mark);
    void        slot_emitHotAndNewTags(QAbstractButton* button);
    void        slot_setCheckedButton(QAbstractButton* button);
    void        slot_showTagsMenu();

private:
    Ui::SonglistSort *ui;
    QButtonGroup        *m_buttonGroup1;
    QButtonGroup        *m_buttonGroup2;

signals:
    void sig_sendSelectTags(QString);
    void sig_sendTags(QString);

};

#endif // SONGLISTSORT_H

#ifndef SONGLISTSORT_H
#define SONGLISTSORT_H

#include <QWidget>

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

private:
    Ui::SonglistSort *ui;
};

#endif // SONGLISTSORT_H

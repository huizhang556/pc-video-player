#ifndef MYALLFILE_H
#define MYALLFILE_H

#include <QWidget>
#include <QListView>
#include <QFileSystemModel>
#include <QTreeWidgetItem>
#include <QDebug>

namespace Ui {
class MyAllFile;
}

class MyAllFile : public QWidget
{
    Q_OBJECT

public:
    explicit MyAllFile(QWidget *parent = nullptr);
    ~MyAllFile();
    void    initWorkUI();
    void    handleSignalsAndSlots();

private:
    void    setItemHideOrShow(QTreeWidgetItem* item, bool show);


private:
    Ui::MyAllFile *ui;
    QFileSystemModel    *m_fileSysModel     =   nullptr;

};

#endif // MYALLFILE_H

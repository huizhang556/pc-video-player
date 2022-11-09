#ifndef MYALLFILE_H
#define MYALLFILE_H

#include <QWidget>

namespace Ui {
class MyAllFile;
}

class MyAllFile : public QWidget
{
    Q_OBJECT

public:
    explicit MyAllFile(QWidget *parent = nullptr);
    ~MyAllFile();

private:
    Ui::MyAllFile *ui;
};

#endif // MYALLFILE_H

#ifndef MYDOCFILE_H
#define MYDOCFILE_H

#include <QWidget>

namespace Ui {
class MyDocFile;
}

class MyDocFile : public QWidget
{
    Q_OBJECT

public:
    explicit MyDocFile(QWidget *parent = nullptr);
    ~MyDocFile();

private:
    Ui::MyDocFile *ui;
};

#endif // MYDOCFILE_H

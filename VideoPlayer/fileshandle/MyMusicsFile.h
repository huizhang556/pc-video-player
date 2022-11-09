#ifndef MYMUSICSFILE_H
#define MYMUSICSFILE_H

#include <QWidget>

namespace Ui {
class MyMusicsFile;
}

class MyMusicsFile : public QWidget
{
    Q_OBJECT

public:
    explicit MyMusicsFile(QWidget *parent = nullptr);
    ~MyMusicsFile();

private:
    Ui::MyMusicsFile *ui;
};

#endif // MYMUSICSFILE_H

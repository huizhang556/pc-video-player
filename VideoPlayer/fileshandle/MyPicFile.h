#ifndef MYPICFILE_H
#define MYPICFILE_H

#include <QWidget>

namespace Ui {
class MyPicFile;
}

class MyPicFile : public QWidget
{
    Q_OBJECT

public:
    explicit MyPicFile(QWidget *parent = nullptr);
    ~MyPicFile();

private:
    Ui::MyPicFile *ui;
};

#endif // MYPICFILE_H

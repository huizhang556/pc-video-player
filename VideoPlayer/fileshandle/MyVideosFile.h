#ifndef MYVIDEOSFILE_H
#define MYVIDEOSFILE_H

#include <QWidget>

namespace Ui {
class MyVideosFile;
}

class MyVideosFile : public QWidget
{
    Q_OBJECT

public:
    explicit MyVideosFile(QWidget *parent = nullptr);
    ~MyVideosFile();

private:
    Ui::MyVideosFile *ui;
};

#endif // MYVIDEOSFILE_H

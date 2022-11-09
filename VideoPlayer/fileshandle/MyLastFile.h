#ifndef MYLASTFILE_H
#define MYLASTFILE_H

#include <QWidget>

namespace Ui {
class MyLastFile;
}

class MyLastFile : public QWidget
{
    Q_OBJECT

public:
    explicit MyLastFile(QWidget *parent = nullptr);
    ~MyLastFile();

private:
    Ui::MyLastFile *ui;
};

#endif // MYLASTFILE_H

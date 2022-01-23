#ifndef FILECHANDLE_H
#define FILECHANDLE_H

#include <QWidget>

namespace Ui {
class FileChandle;
}

class FileChandle : public QWidget
{
    Q_OBJECT

public:
    explicit FileChandle(QWidget *parent = nullptr);
    ~FileChandle();

private:

};

#endif // FILECHANDLE_H

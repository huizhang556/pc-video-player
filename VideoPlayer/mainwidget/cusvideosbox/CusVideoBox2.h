#ifndef CUSVIDEOBOX2_H
#define CUSVIDEOBOX2_H

#include <QWidget>

namespace Ui {
class CusVideoBox2;
}

class CusVideoBox2 : public QWidget
{
    Q_OBJECT

public:
    explicit CusVideoBox2(QWidget *parent = nullptr);
    ~CusVideoBox2();

private:
    Ui::CusVideoBox2 *ui;
};

#endif // CUSVIDEOBOX2_H

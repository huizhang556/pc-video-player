#ifndef CUSLABEL3_H
#define CUSLABEL3_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class CusLabel3;
}

class CusLabel3 : public QLabel
{
    Q_OBJECT

public:
    explicit CusLabel3(QWidget *parent = nullptr);
    ~CusLabel3();

private:
    Ui::CusLabel3 *ui;
};

#endif // CUSLABEL3_H

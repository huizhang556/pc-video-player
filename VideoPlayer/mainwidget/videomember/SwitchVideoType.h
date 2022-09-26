#ifndef SWITCHVIDEOTYPE_H
#define SWITCHVIDEOTYPE_H

#include <QWidget>

namespace Ui {
class SwitchVideoType;
}

class SwitchVideoType : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchVideoType(QWidget *parent = nullptr);
    ~SwitchVideoType();

private:
    Ui::SwitchVideoType *ui;
};

#endif // SWITCHVIDEOTYPE_H

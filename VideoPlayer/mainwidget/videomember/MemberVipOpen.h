#ifndef MEMBERVIPOPEN_H
#define MEMBERVIPOPEN_H

#include <QWidget>

namespace Ui {
class MemberVipOpen;
}

class MemberVipOpen : public QWidget
{
    Q_OBJECT

public:
    explicit MemberVipOpen(QWidget *parent = nullptr);
    ~MemberVipOpen();

private:
    Ui::MemberVipOpen *ui;
};

#endif // MEMBERVIPOPEN_H

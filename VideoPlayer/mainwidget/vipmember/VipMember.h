#ifndef VIPMEMBER_H
#define VIPMEMBER_H

#include <QWidget>

namespace Ui {
class VipMember;
}

class VipMember : public QWidget
{
    Q_OBJECT

public:
    explicit VipMember(QWidget *parent = nullptr);
    ~VipMember();
    void        initWorkUI();
    void        handleSignalsAndSlots();

private:
    Ui::VipMember *ui;
};

#endif // VIPMEMBER_H

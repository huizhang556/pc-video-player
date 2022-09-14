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
    void        setInstallEventFilter();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::VipMember *ui;

private slots:
    void     resizeListWidgetItemWidget(const QSize& size);//动态更新item大小

};

#endif // VIPMEMBER_H

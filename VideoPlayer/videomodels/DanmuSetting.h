#ifndef DANMUSETTING_H
#define DANMUSETTING_H

#include <QDialog>

namespace Ui {
class DanmuSetting;
}

class DanmuSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DanmuSetting(QWidget *parent = nullptr);
    ~DanmuSetting();

protected:
    void        leaveEvent(QEvent *event) override;

private:
    Ui::DanmuSetting *ui;
};

#endif // DANMUSETTING_H

#ifndef PERCENTER_H
#define PERCENTER_H

#include <QWidget>

namespace Ui {
class PerCenter;
}

class PerCenter : public QWidget
{
    Q_OBJECT

public:
    explicit PerCenter(QWidget *parent = nullptr);
    ~PerCenter();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();

private:
    Ui::PerCenter *ui;
};

#endif // PERCENTER_H

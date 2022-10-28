#ifndef RADIOHOST_H
#define RADIOHOST_H

#include <QWidget>
#include <QScrollBar>
#include <QDebug>

namespace Ui {
class RadioHost;
}

class RadioHost : public QWidget
{
    Q_OBJECT

public:
    explicit RadioHost(QWidget *parent = nullptr);
    ~RadioHost();
    void        initWorkUI();
    void        handleSignalsAndSlots();

private:
    Ui::RadioHost *ui;
};

#endif // RADIOHOST_H

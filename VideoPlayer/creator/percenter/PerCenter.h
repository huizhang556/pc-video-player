#ifndef PERCENTER_H
#define PERCENTER_H

#include "database/dataBase.h"

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


public slots:
    void    setCurUserInfo(const QString& name, const QPixmap& pix);

private:
    Ui::PerCenter *ui;
};

#endif // PERCENTER_H

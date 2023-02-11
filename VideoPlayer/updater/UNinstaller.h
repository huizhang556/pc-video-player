#ifndef UNINSTALLER_H
#define UNINSTALLER_H

#include <QDialog>

namespace Ui {
class UNinstaller;
}

class UNinstaller : public QDialog
{
    Q_OBJECT

public:
    explicit UNinstaller(QWidget *parent = nullptr);
    ~UNinstaller();

private:
    Ui::UNinstaller *ui;
};

#endif // UNINSTALLER_H

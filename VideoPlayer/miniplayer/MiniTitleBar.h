#ifndef MINITITLEBAR_H
#define MINITITLEBAR_H

#include <QWidget>

namespace Ui {
class MiniTitleBar;
}

class MiniTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit MiniTitleBar(QWidget *parent = nullptr);
    ~MiniTitleBar();

public slots:
    void    slot_setCurrentTitle(const QString& title);
    void    slot_clearTitle();

private:
    Ui::MiniTitleBar *ui;

signals:
    void    sig_mini_close();
};

#endif // MINITITLEBAR_H

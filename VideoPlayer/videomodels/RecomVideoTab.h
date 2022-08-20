#ifndef RECOMVIDEOTAB_H
#define RECOMVIDEOTAB_H

#include <QWidget>

namespace Ui {
class RecomVideoTab;
}

class RecomVideoTab : public QWidget
{
    Q_OBJECT

public:
    explicit RecomVideoTab(QWidget *parent = nullptr);
    ~RecomVideoTab();
    void    initWorkUI();
    void    handleSignalsAndSLots();

private slots:
    void slots_switchTurn();

private:
    bool        m_turnOnStatus;
    Ui::RecomVideoTab *ui;
};

#endif // RECOMVIDEOTAB_H

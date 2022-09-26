#ifndef CUSPUSGBUTTON_H
#define CUSPUSGBUTTON_H

#include <QEvent>
#include <QWidget>
#include <QPushButton>

namespace Ui {
class CusPusgButton;
}

class CusPusgButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CusPusgButton(QWidget *parent = nullptr);
    ~CusPusgButton();
    void    setButtonId(int id);

public slots:
    int    slot_getButtonId();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    int     m_id = 0;

signals:
    void    sig_buttonHover(QString);
    void    sig_buttonHover(int);

};

#endif // CUSPUSGBUTTON_H

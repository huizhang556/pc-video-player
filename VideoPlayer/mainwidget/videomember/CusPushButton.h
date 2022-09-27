#ifndef CusPushButton_H
#define CusPushButton_H

#include <QEvent>
#include <QWidget>
#include <QPushButton>

namespace Ui {
class CusPushButton;
}

class CusPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CusPushButton(QWidget *parent = nullptr);
    explicit CusPushButton(const QString& text, const int id, QWidget *parent = nullptr);
    ~CusPushButton();
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

#endif // CusPushButton_H

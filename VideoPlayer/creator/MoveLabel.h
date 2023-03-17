#ifndef MOVELABEL_H
#define MOVELABEL_H

#include <QLabel>
#include <QMovie>
#include <QDebug>

namespace Ui {
class MoveLabel;
}

class MoveLabel : public QLabel
{
    Q_OBJECT

public:
    explicit MoveLabel(QWidget *parent = nullptr);
    ~MoveLabel();

    void    setLoginTips(bool online);

private:
    Ui::MoveLabel *ui;
    QString m_gifpath;
    QMovie  *m_movie    =   nullptr;

signals:
    void    sig_sendClose();
    void    sig_sendLogin();
};

#endif // MOVELABEL_H

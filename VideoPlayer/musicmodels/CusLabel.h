#ifndef CUSLABEL_H
#define CUSLABEL_H

#include <QLabel>
#include <QTimer>
#include <QTextCursor>

namespace Ui {
class CusLabel;
}

class CusLabel : public QLabel
{
    Q_OBJECT

public:
    explicit CusLabel(QWidget *parent = nullptr);
    ~CusLabel();
    void        initWorkUI();
    void        chandleSinalsAndSlots();
private:
    Ui::CusLabel *ui;
    QTimer          *m_timer;
    int             m_pos;
    QTextCursor     m_textCursor;

private slots:
    void        slot_setCurPosition(int pos);

};

#endif // CUSLABEL_H

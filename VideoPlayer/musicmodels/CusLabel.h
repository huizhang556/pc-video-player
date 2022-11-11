#ifndef CUSLABEL_H
#define CUSLABEL_H

#include <QFont>
#include <QLabel>
#include <QTimer>
#include <QColor>
#include <QPalette>
#include <QTextCursor>
#include <QTextCharFormat>

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
    void        setCurrentTextFontSize(int size);
    void        setCurrentTextFontColor(const QString &color);

private:
    Ui::CusLabel *ui;
    QTimer          *m_timer;
    int             m_pos;
    QTextCursor     m_textCursor;
    QFont           m_font;
private slots:
    void        slot_setCurPosition(int pos);

};

#endif // CUSLABEL_H

#ifndef CUSLABEL_H
#define CUSLABEL_H

#include <QFont>
#include <QLabel>
#include <QTimer>
#include <QColor>
#include <QPalette>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextDocument>
#include <QTextBlock>
#include <QAudioBuffer>
#include <QDebug>

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
    void        getCurPostionLyricText(int pos);

public  slots:
    void        slot_setLyricShowed(bool showed);
    void        slot_drawMediaAudioWave(const QAudioBuffer &buffer);
    void        slot_setWaveStyle(const QString &style);

private:
    Ui::CusLabel *ui;
    QTimer          *m_timer;
    int             m_pos;
    QTextCursor     m_textCursor;
    QFont           m_font;
private slots:
    void        slot_setCurPosition(int pos);

signals:
    void    sig_curLyricText(QString);

};

#endif // CUSLABEL_H

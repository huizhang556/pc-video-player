#ifndef FONTCOLOR_H
#define FONTCOLOR_H

#include <QWidget>
#include <QEvent>
#include <QColor>

namespace Ui {
class FontColor;
}

class FontColor : public QWidget
{
    Q_OBJECT

    explicit FontColor(QWidget *parent = nullptr);
public:
    ~FontColor();
    void    initWorkUI();
    void    handleSinalsAndSlots();
    void    setCurrentStackWdtIndex(const int index);
    static  FontColor* getInstance();

protected:
    void    leaveEvent(QEvent *event) override;

private:
    Ui::FontColor *ui;
    static FontColor* m_pInstance;

signals:
    void    sig_send_fontsize(int);
    void    sig_send_fontcolor(QString);
};

#endif // FONTCOLOR_H

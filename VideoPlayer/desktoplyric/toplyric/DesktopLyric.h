#ifndef DESKTOPLYRIC_H
#define DESKTOPLYRIC_H

#include <QWidget>
#include <QEvent>
#include <QFont>
#include <QPoint>
#include <QMouseEvent>
#include <QRadialGradient>
#include <QDebug>

namespace Ui {
class DesktopLyric;
}

class DesktopLyric : public QWidget
{
    Q_OBJECT

public:
    ~DesktopLyric();
    static DesktopLyric* getInstance();
    void    initWorkUI();
    void    handleSignalsAndSlots();

public slots:
    void    slot_setCurrentPlayStatus(bool status);

protected:
   void  mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
   bool  eventFilter(QObject *watched, QEvent *event) override;

private:
    explicit DesktopLyric(QWidget *parent = nullptr);
    Ui::DesktopLyric *ui;
    static DesktopLyric* m_pInstance;

private:
    QPoint              m_mvPos;
signals:
    void    sig_sendSetting();
    void    sig_sendPrevious();
    void    sig_sendPlay();
    void    sig_sendNext();
    void    sig_sendSound(bool);

};

#endif // DESKTOPLYRIC_H

#ifndef CSPLASHSCREEN_H
#define CSPLASHSCREEN_H

#include <QSplashScreen>
#include <QMovie>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QLayout>
#include <QProgressBar>

class QPixmap;
class QPainter;

class CSplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    CSplashScreen(const QPixmap & pixmap);
    CSplashScreen(const QString gifname);

    ~CSplashScreen();
    void setGif(QString filename);
public slots:
    void            slot_updateProgressbarValue(int value);

protected:
    virtual void    drawContents(QPainter *painter);

private slots:
    void slot_update();

private:
    int             roate = 0;
    QMovie          *m_move;
    QTimer          *timer;
    QProgressBar    *m_progressbar;

};
#endif // CSPLASHSCREEN_H

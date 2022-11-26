#ifndef PLAYSTATECONTROL_H
#define PLAYSTATECONTROL_H

#include <QWidget>
#include <QTimer>

class PlayStateControl : public QWidget
{
    Q_OBJECT

public:
    PlayStateControl(QWidget *parent = nullptr);
    ~PlayStateControl()override;

public slots:
    void    slot_setPlayingStatus(bool paying);//设置播放/暂停

protected:
    void paintEvent(QPaintEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;

private:
    QPixmap diskPixmap;
    QPixmap polePixmap;
    QPixmap centerPixmap;

    bool isPlaying{true};
    qreal angle{0};
    QTimer angleTimer;
    qreal poleSpinAngle{0};
    bool poleIsSpin{false};
    QTimer poleSpinTimer;
};
#endif // PLAYSTATECONTROL_H

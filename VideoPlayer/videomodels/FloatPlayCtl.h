#ifndef FLOATPLAYCTL_H
#define FLOATPLAYCTL_H

#include <QWidget>

namespace Ui {
class FloatPlayCtl;
}

class FloatPlayCtl : public QWidget
{
    Q_OBJECT

public:
    ~FloatPlayCtl();

    void    initWorkUI();
    void    chandleSignalsAndSlots();
    static  FloatPlayCtl* getInstance();
    void    setHorzontalSlider_PlayerRange(int start,int end);
    void    setHorzontalSlider_VoiceRange(int start,int end);

public slots:
    void    slot_setProgressbar_player(int value);
    void    slot_setProgressbar_voice(int value);
    void    slot_setPlayer_mute(bool mute);
    void    slot_setMediaPlayName(QString name);
    void    slot_setMediaPlayTime(QString time);
    void    slot_setCurrentPlayStatus(bool status);
    void    slot_setCurrentMediaMutedStyleSheet(bool status);
    void    slot_setCurrentPlayMutedStatus(int value);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;


private:
    Ui::FloatPlayCtl *ui;
    explicit FloatPlayCtl(QWidget *parent = nullptr);
    static  FloatPlayCtl    *m_pInstance;
    bool                    m_playStatus;
    bool                    m_soundStatus;
    bool                    m_bPress         =      false;//默认没有按下
signals:
    void    sig_sendExitFullscreen();
    void    sig_sendPlayPrevious();
    void    sig_sendPlayStartPause();
    void    sig_sendPlayNext();
    void    sig_sendPlayMute(bool);
    void    sig_sendProgress_player(int);
    void    sig_sendProgress_voice(int);
};

#endif // FLOATPLAYCTL_H

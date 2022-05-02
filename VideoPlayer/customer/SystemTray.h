#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QWidget>

namespace Ui {
class SystemTray;
}

class SystemTray : public QWidget
{
    Q_OBJECT

public:
    explicit SystemTray(QWidget *parent = nullptr);
    ~SystemTray();
//    static  SystemTray* getInstance();
    void initWorkUI();
    void chandleSignalsAndSlots();
public slots:
    void slot_setCurrentPlayStatus(bool status);//当前播放状态样式设置
    void slot_setCurrentPlaySoundValue(int value);//声音值
    void slot_setCurrentMediaMutedStyleSheet();//设置静音
    void slot_setCurrentPlayMutedStatus(int value);//声音样式
    void slot_setCurrentMediaSoundShowToop(int value);
    void slot_updatePlayButtonStatusStyleSheet();
private:
    Ui::SystemTray *ui;
//    static  SystemTray      *m_pInstance;
    bool        m_playStatus;
    bool        m_soundStatus;
signals:
    void sig_playStatusPrevious();
    void sig_playStatusPause(bool status);
    void sig_playStatusNext();
    void sig_playStatusMuted(bool muted);
    void sig_playProgressValue(int value);
};

#endif // SYSTEMTRAY_H

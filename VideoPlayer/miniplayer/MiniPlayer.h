#ifndef MINIPLAYER_H
#define MINIPLAYER_H
#define FIXEDHEIGHT 36
#include <QResizeEvent>
#include <QVideoWidget>
#include <QPushButton>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QActionGroup>
#include <QListWidget>
#include <QSlider>
#include <QMenu>
#include <QAction>
#include <QEvent>
#include <QTimer>
#include <QFrame>
#include <QLabel>
#include <QLayout>
#include <QDebug>

namespace Ui {
class MiniPlayer;
}

class MiniPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MiniPlayer(QWidget *parent = nullptr);
    ~MiniPlayer();
    void    initWorkUI();
    void    handleSignalsAndSlots();

public  slots:
    void    slot_receivePlayMediaFile(const QString& mediaUrl,const QString& mediaName);
    void    slot_mouseEnter();
    void    slot_mouseLeave();
    void    slot_player_on();
protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;
    void    enterEvent(QEvent *event) override;
    void    leaveEvent(QEvent *event) override;
    void    resizeEvent(QResizeEvent *event) override;

private:
    QVideoWidget    *m_videoWidget      =   nullptr;
    QMediaPlayer    *m_player           =   nullptr;//播放器
    QMediaPlaylist  *m_playlist         =   nullptr;//播放列表
    QAction         *m_screenAction     =   nullptr;//全屏/退出全屏
    QFrame          *m_frameTitle       =   nullptr;//标题栏
    QFrame          *m_frameControl     =   nullptr;//底部控制栏
    QListWidget     *m_clityListWgt     =   nullptr;//清晰度
    QFrame          *m_frameSound       =   nullptr;//音量调节
    QSlider         *m_verSlider        =   nullptr;//音量进度
    QSlider         *m_horSlider        =   nullptr;//视频进度
    QPushButton     *m_buttonTitle      =   nullptr;//标题
    QPushButton     *m_buttonPlayer     =   nullptr;//播放
    QPushButton     *m_buttonNext       =   nullptr;//下一首
    QLabel          *m_labelProgress    =   nullptr;//进度显示
    QPushButton     *m_buttonClarity    =   nullptr;//清晰度
    QPushButton     *m_buttonSound      =   nullptr;//音量
    QTimer          *m_timer            =   nullptr;
    QActionGroup    *m_actionGroup1     =   nullptr;
    QActionGroup    *m_actionGroup2     =   nullptr;
    QMenu           *m_videoMenu        =   nullptr;
    QMenu           *m_subMenu1         =   nullptr;
    QMenu           *m_subMenu2         =   nullptr;
    qint64          m_times;//总时长
    qint64          m_position;//播放点

private slots:
    void    createRightMenu();
    void    on_updatePosition();
    void    slot_menu_mainPlayer();
    void    slot_menu_download();
    void    slot_menu_fullscreen();
    void    slot_menu_scale(QAction *action);
    void    slot_menu_playrate(QAction *action);
    void    slot_menu_videoinfo();
    void    slot_menu_setting();

signals:
    void    sig_player_toMainPlayer();
    void    sig_player_next();
    void    sig_player_download();
    void    sig_player_status(bool);
    void    sig_player_videoInfo();
    void    sig_player_videoSetting();
};

#endif // MINIPLAYER_H

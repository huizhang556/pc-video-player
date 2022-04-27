#ifndef MULTIPPLAYER_H
#define MULTIPPLAYER_H
#define MARWIDTH 2 //窗口边距
#include "network/MyHttp.h"

#include "videomodels/VideoBlank.h"
#include "videomodels/muteDialog.h"
#include "videomodels/CommentTab.h"
#include "videomodels/AdjustBright.h"
#include "musicmodels/MusicPlayShow.h"
#include "videomodels/MyVideoWidget.h"
#include "musicmodels/MusicPlaylist.h"
#include "videomodels/VideoTitleBar.h"
#include "videomodels/RecomVideoTab.h"
#include "videomodels/IntroduceForm.h"
#include "videomodels/PlayOrderForm.h"

#include <QMap>
#include <QPoint>
#include <QTimer>
#include <QAction>
#include <QToolBox>
#include <QLineEdit>
#include <QKeyEvent>
//#include <windows.h>
//#include <windowsx.h>
#include <QShowEvent>
#include <QMainWindow>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QPushButton>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QWidgetAction>
#include <QDesktopWidget>
#include <QStackedWidget>
#include <QMediaPlaylist>
#include <QSystemTrayIcon>
#include <QDesktopServices>


namespace Ui {
class MultipPlayer;
}


class MultipPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MultipPlayer(QWidget *parent = nullptr);
    ~MultipPlayer();

    void initMainWindow();

    void chandleSignalAndSLots();

    void addToPlaylist(const QStringList& fileNames);

    void createLoginMenu();//登录菜单

    void createSwitchSkinMenu();//切换皮肤

    void addFileToList(const QStringList &strList);//浮动歌曲列表

    bool fileType(int index);// 重载函数1

    bool fileType(QStringList &filenames,int index);// 重载函数2

    void get_fileFromServer();

    void removeTabwidgetTabBar(QTabWidget *tabwidget);

    void set_showTwoTabBar(QTabWidget *tabwidget, int index1, QWidget *obj1,QString tabtext1);

    void set_showTwoTabBar(QTabWidget *tabwidget, int index1, QWidget *obj1,QString tabtext1, int index2, QWidget *obj2, QString tabtext2);

    void set_fileTolistWidget(QString item);//将服务器获取到的文件列表显

    void showMediaCommentTab();

    QString getCurrentMediaPlayFileName();

    QRect getDesktopScreenGeometry();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void changeEvent(QEvent *event) override;

    void showEvent(QShowEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void loadFileInfoToWinTitle(int index);//标题栏显示视频名称

    void findFileFromLineEdit( QString name);//浮动曲库查找搜索内容

    void itemDoubleClick(QListWidgetItem *item);

    void openLocalFile();

    void setMainCurrentIndex(const int index);

    void closeCurrentWindow();

//    void clearListWidgetList_user();//清空用户信息

    void clearListWidgetList_playlist();//清空播放列表

    void clearListWidgetList_collection();//清空收藏列表

    void clearListWidgetList_history();//清空历史记录

    void clearUserInputSearchInfo();//清空用户输入的搜索字

    void setCurrentMediaName(QString name);//进度条上显示媒体名称

    void setCurrentMediaNamePicture(const QPixmap &pix);//进度条上显示媒体图片

    void updateFoldButtonGeometry();//更显显示/隐藏按钮的位置

    void setFoldButtonStyle();//判断箭头的方向

    void judgeFoldBtnOfRightDockList();//判断右侧停靠栏指示按钮位置

    void setLeftCurrentListSHowHide();

    void setPlayOrderButtonStyleSheet(int index);

    void setVideTitleBar(int index);

private slots:
    void on_time();

    void checkChandleMediaPlayerStatus();//监测处理媒体播放状态

    void checkChandleMediaStatus();//监测处理媒体状态

    void loadDefaultLogo();//加载默认图标

    void on_pushButton_pauseStart_clicked();//暂停、播放

    void on_pushButton_5_clicked();//打开文件

    void on_pushButton_previous_clicked();//上一首

    void on_pushButton_next_clicked();//下一首

    void on_pushButton_6_clicked();//重新打开

    void switchListPage(int index);

    void setVideoRate(int value);

    void updateRateTypeUiLayout(int str);

    void on_moreBtn_clicked();

    void set_adjustBright();

    void searchMouseEnterLeaveShow(QObject *watched, QEvent *event);

    bool videoDouleExit(QObject *watched, QEvent *event);

    void volumeAdjustShowUi(QObject *watched, QEvent *event);

    void stackWidgetSliderButtonEventFilter(QObject *watched, QEvent *event);

    void playlistMouseEnterLeave(QObject *watched, QEvent *event);


    //帮助菜单槽函数
    void help_aboutLocalFile();//本地文件

    void adjust_playBackMode(int index);//调节播放模式

    void adjust_aspectRatioMode(int index);//调节屏幕占比

    void update_adjustBright();

    void downloadInternetPathRecource();

    void playHttpRequireRecourse(const QString &url);

//    void on_pushButton_danmu_clicked();//弹幕按钮

    void chandleRestoreWindow();

    bool loadCollectListWidgetList();//加载收藏菜单

    bool setCollectBtnShowStatus();//设置收藏按钮显示状态

    bool findCollectListStatus(QString name);//遍历列表，没有则添加

    int getCurrentMediaRowOfCollectList(QString name);

signals:
    void sig_sendSwitchToMusicPage(QString name);

    void sig_startCloseAppliction();

    void sig_sendToMusicList();

    void sig_winVStatus(bool);
private:
    Ui::MultipPlayer *ui;
    QDesktopWidget              *system_screen      = nullptr;
    QTimer                      *m_pTimer           = nullptr; //进度滚动条更新
    QTimer                      *m_pTimer2          = nullptr; //延迟ui界面
    QWidget                     *m_widget1          = nullptr;
    QWidget                     *m_widget2          = nullptr; //暂时不用
    QToolBox                    *m_toolBox          = nullptr;
    QLineEdit                   *m_lineEdit         = nullptr;
    muteDialog                  *m_muteDlg          = nullptr;
    VideoBlank                  *m_videoBlank       = nullptr;
    QTabWidget                  *m_tabWidget1        = nullptr; //节目列表选项
    CommentTab                  *m_commentTab       = nullptr;
//    QListWidget                 *m_listWisget1      = nullptr;
    QListWidget                 *m_listWisget2      = nullptr;
    QListWidget                 *m_listWisget3      = nullptr;
    QListWidget                 *m_listWisget4      = nullptr;
    QHBoxLayout                 *m_hLayout          = nullptr; //搜索按钮和搜索框布局
    QHBoxLayout                 *m_hboxlayout_rlist = nullptr; //右侧播放列表
    QVBoxLayout                 *m_vHlayout         = nullptr; //布局listwidget和m_hLayout
    QVBoxLayout                 *m_vHlayout_jianjie = nullptr; //视频简介布局
    QVBoxLayout                 *m_vHlayout_jieshao = nullptr; //视频介绍布局
    QPushButton                 *m_searchBtn        = nullptr;
    QPushButton                 *m_foldBtn          = nullptr;
    QMediaPlayer                *player             = nullptr;
    AdjustBright                *m_adjustBright     = nullptr;
    MusicPlayShow               *m_musicUi          = nullptr;
    MusicPlaylist               *m_musicShowList    = nullptr;
    VideoTitleBar               *m_videoTitleBar    = nullptr;
    IntroduceForm               *m_introduceForm    = nullptr;
    RecomVideoTab               *m_recomTab         = nullptr;
    PlayOrderForm               *m_playOrderForm    = nullptr;
    MyVideoWidget               *videoWidget        = nullptr;
    QMediaPlaylist              *playlist           = nullptr;
    QStackedWidget              *m_introStack       = nullptr;
    int                         m_voice;                        //静音之前的值
    bool                        m_winMax;                       //默认非最大化
    bool                        m_isClose;
    bool                        m_orderStatus       = false;
    bool                        m_isHide            = false;    //侧边栏显示/隐藏按钮，默认没隐藏
    bool                        m_newStart          = false;    //可以打开新文件按钮标识
    bool                        m_bPress            = false;
    bool                        m_muteShow          = false;    //默认不显示
    bool                        m_jiemuShow         = false;    //默认不显示
    bool                        m_danmuStatus       = false;    //默认不显示
    bool                        m_collectStatus     = false;    //默认不显示
    qint64                      m_times;                        //文件长度
    QPoint                      m_mvPos;
    QPoint                      m_videoPos;
    QStringList                 m_fileNames;                    //文件名称列表
    QMap<int,QString>           m_mapList;                      //存储歌名路径
    QMap<int,QString>           m_mapList2;                     //存储歌名带后缀
    QMap<int,QString>           m_mapList_collect;
    QMap<int,QString>           m_mapList_history;
    QMediaPlayer::State         m_playerState;
    QStringList                 list_temp;
    QString                     m_curMediaName;
/*以下为界面拉伸所用*/
    bool                        _isleftpressed      = false;    //判断是否是左键点击
    int                         _curpos = 0;                    //鼠标左键按下时光标所在区域
    QPoint                      _plast;                         //获取鼠标左键按下时光标在全局(屏幕而非窗口)的位置
    int                         countRow(QPoint p);             //获取光标在窗口所在区域的 行   返回行数
    int                         countFlag(QPoint p,int row);    //获取光标在窗口所在区域的 列  返回行列坐标
    void                        setCursorType(int flag);        //根据传入的坐标，设置光标样式
};

#endif // MULTIPPLAYER_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MARGIN 10 //窗口边距

#include "login/Login.h"
#include "AdjustBright.h"
#include "SystemSetting.h"
#include "network/MyHttp.h"
#include "footer/ExitDialog.h"
#include "customer/CusTabWidget.h"
#include "browser/CusWebBrowser.h"
#include "videomodels/muteDialog.h"
#include "musicmodels/MusicPlayShow.h"
#include "videomodels/MyVideoWidget.h"
#include "musicmodels/MusicPlaylist.h"
#include "videomodels/CusVideoWidget.h"

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
#include <QMediaPlaylist>
#include <QSystemTrayIcon>
#include <QDesktopServices>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addToPlaylist(const QStringList& fileNames);

    void createTrayMenu();//托盘菜单

    void createHelpMenu();//帮助菜单

    void createLoginMenu();//登录菜单

    void createSwitchSkinMenu();//切换皮肤

    void addFileToList(const QStringList &strList);//浮动歌曲列表

    void addFileToPlayList();//节目列表

    bool fileType(int index);// 重载函数1

    bool fileType(QStringList &filenames,int index);// 重载函数2

    void get_fileFromServer();

    void set_fileTolistWidget(QString item);//将服务器获取到的文件列表显示

//    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

public slots:
    void loadFileInfoToWinTitle(int index);

    void findFileFromLineEdit( QString name);//浮动曲库查找搜索内容

    void getAndShowCurTime();

    void itemDoubleClick(QListWidgetItem *item);
protected:
//    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

//    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void changeEvent(QEvent *event) override;

    void showEvent(QShowEvent *event) override;

private slots:
//    void on_pushButton_clicked();

//    void on_openfile(QStringList fileNames);

    void on_time();

    void showPlayerUi();//显示播放器界面

    void showPlayerList();//显示播放列表

    void loadDefaultLogo();//加载默认图标

    void loadAllUIQss();//加载UI样式文件

    void on_pushButton_2_clicked();//停止

//    void on_pushButton_1_clicked();//静音

    void on_pushButton_4_clicked();//暂停、播放

    void on_pushButton_5_clicked();//打开文件

    void on_pushButton_7_clicked();//上一首

    void on_pushButton_8_clicked();//下一首

    void on_pushButton_6_clicked();//重新打开

    void on_frameHidden();

    void on_enterShowFrame();

    void switchListPage(int index);

    void setVideoRate(int value);

    void updateRateTypeUiLayout(int str);

    void on_moreBtn_clicked();

    void searchMouseEnterLeaveShow(QObject *watched, QEvent *event);

    bool videoDouleExit(QObject *watched, QEvent *event);

    void volumeAdjustShowUi(QObject *watched, QEvent *event);

    void playlistMouseEnterLeave(QObject *watched, QEvent *event);

    void showCaptureScreen();

    void showJieMuListWidget();


    //帮助菜单槽函数
    void help_stemAboutSetting();//系统设置

    void help_questionAnswer();//问题帮助

    void help_aboutLocalFile();//本地文件

    void help_openWebSite();//门户网站

    void set_adjustBright();

    void set_adjustLogin();

    void adjust_playBackMode(int index);//调节播放模式

    void adjust_aspectRatioMode(int index);//调节屏幕占比

    void update_adjustBright();

    void downloadInternetPathRecource();

    void playHttpRequireRecourse(const QString &url);

    void on_pushButton_danmu_clicked();

signals:
    void sig_sendSwitchToMusicPage(QString name);

    void sig_startCloseAppliction();

    void sig_sendToMusicList();


private:
    Ui::MainWindow *ui;
    ExitDialog                  *m_pExitDlg = nullptr;
    Login                       *m_login = nullptr;
    muteDialog                  *m_muteDlg = nullptr;
    CusTabWidget                *m_cusTabWidget = nullptr;
    AdjustBright                *m_adjustBright = nullptr;
    CusWebBrowser               *m_cusWebBrowser = nullptr;//网页显示
    CusVideoWidget              *m_cusVideoWidget = nullptr;
    MusicPlayShow               *m_musicUi = nullptr;
    MusicPlaylist               *m_musicShowList = nullptr;
    SystemSetting               *m_systemSetting = nullptr;
    int                         m_voice;//静音之前的值
    bool                        m_winMax;//默认非最大化
    bool                        m_isClose;
    bool                        m_isEnter = false;
    bool                        m_newStart = false;//可以打开新文件按钮标识
    bool                        m_bPress = false;
    bool                        m_muteShow = false;//默认不显示
    bool                        m_jiemuShow = false;//默认不显示
    bool                        m_danmuStatus = false;//默认不显示
    QTimer                      *m_pTimer = nullptr;//进度滚动条更新
    QTimer                      *m_pTimer2 = nullptr;//延迟ui界面
    QTimer                      *m_pTimer3 = nullptr;//实时获取系统时间
    qint64                      m_times;//文件长度
    QPoint                      m_mvPos;
    QPoint                      m_videoPos;
    QAction                     *clearAction;
    QWidget                     *widget1 = nullptr;
    QWidget                     *widget2 = nullptr;//暂时不用
    QToolBox                    *m_toolBox = nullptr;
    QLineEdit                   *m_lineEdit = nullptr;
    QDockWidget                 *m_dockWidget = nullptr;
    QListWidget                 *m_listWisget1 = nullptr;
    QListWidget                 *m_listWisget2 = nullptr;
    QListWidget                 *m_listWisget3 = nullptr;
    QListWidget                 *m_listWisget4 = nullptr;
    QHBoxLayout                 *m_hLayout = nullptr;//搜索按钮和搜索框布局
    QHBoxLayout                 *hboxlayout_rlist = nullptr;//右侧播放列表
    QVBoxLayout                 *m_vHlayout = nullptr;//布局listwidget和m_hLayout
    QPushButton                 *m_searchBtn = nullptr;
    QStringList                 m_fileNames;//文件名称列表
    QMediaPlayer                *player = nullptr;
    MyVideoWidget               *videoWidget = nullptr;
    QMediaPlaylist              *playlist = nullptr;
    QSystemTrayIcon             *m_tray = nullptr;
    QMap<int,QString>           m_mapList;//声明为指针记得分配空间！！！否则，虽然可以以指针方式调用，却会报错。
    QMap<int,QString>           m_mapList2;
    QMediaPlayer::State         m_playerState;
    QStringList                 list_temp;

//界面拉伸所用
    bool                        _isleftpressed = false; //判断是否是左键点击
    int                         _curpos = 0;    //鼠标左键按下时光标所在区域
    QPoint                      _plast;      //获取鼠标左键按下时光标在全局(屏幕而非窗口)的位置
    int                         countRow(QPoint p);            //获取光标在窗口所在区域的 行   返回行数
    int                         countFlag(QPoint p,int row);    //获取光标在窗口所在区域的 列  返回行列坐标
    void                        setCursorType(int flag);          //根据传入的坐标，设置光标样式

};

#endif // MAINWINDOW_H

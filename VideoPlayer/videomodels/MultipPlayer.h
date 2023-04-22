#ifndef MULTIPPLAYER_H
#define MULTIPPLAYER_H

#define MARWIDTH 2 //窗口边距宽
#define LISTWIDTH_R   280 //右侧停靠列表宽度
#define ITEMSIZE    QSize(280,30)

#include "network/MyHttp.h"
#include "database/dataBase.h"
#include "videomodels/Danmu.h"
#include "customer/BaseWidget.h"
#include "videomodels/AdvDialog.h"
#include "videomodels/MediaItem.h"
#include "videomodels/VideoBlank.h"
#include "videomodels/muteDialog.h"
#include "videomodels/CommentTab.h"
#include "videomodels/VideoSurface.h"
#include "videomodels/ListManager.h"
#include "videomodels/FloatPlayCtl.h"
#include "videomodels/VideoClarity.h"
#include "videomodels/AdjustBright.h"
#include "customer/CustomFileDialog.h"
#include "musicmodels/MusicPlayShow.h"
#include "videomodels/MyVideoWidget.h"
#include "videomodels/CVideoWidget.h"
#include "videomodels/VideoTitleBar.h"
#include "videomodels/RecomVideoTab.h"
#include "videomodels/DramaListForm.h"
#include "videomodels/PlayOrderForm.h"
#include "videomodels/DanmuSetting.h"
#include "capturepix/CaptureScreen.h"
#include "videomodels/VideoProgressBar.h"
#include "fileshandle/DownloadType.h"
#include "mainwidget/vipmember/BuyVip.h"
#include "desktoplyric/toplyric/DesktopLyric.h"


#include <QMap>
#include <QMenu>
#include <QPoint>
#include <QTimer>
#include <QAction>
#include <QVariant>
#include <QToolBox>
#include <QLineEdit>
#include <QKeyEvent>
//#include <windows.h>
//#include <windowsx.h>
#include <QScreen>
#include <QUrlQuery>
#include <QVideoFrame>
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
#include <QImageWriter>
#include <QWidgetAction>
#include <QDesktopWidget>
#include <QStackedWidget>
#include <QMediaPlaylist>
#include <QMediaContent>
#include <QSystemTrayIcon>
#include <QDesktopServices>
#include <QPropertyAnimation>
#include <QAbstractVideoSurface>

/**唯一的播放器对象--单例**/

struct mediaBody
{
    MEDTYPE type;
    QString url;
    QString icon;
    QString name;
    QString duration;
    bool    isLove;//是否收藏
};

namespace Ui {
class MultipPlayer;
}


class MultipPlayer : public BaseWidget
{
    Q_OBJECT

private:
    explicit MultipPlayer(QWidget *parent = nullptr);
    static MultipPlayer* m_pInstance;

public:
    ~MultipPlayer();

    static  MultipPlayer* getInstance();//获取单例

    void    initMainWindow();

    void    handleSignalAndSLots();

    void    setInstallEventFilter();

    void    addToPlaylist(QMediaPlaylist* mylist,const QStringList& fileNames);//重载1

    void    addToPlaylist(QMediaPlaylist* mylist,const QString& fileName);//重载2

    void    addFileToList(const QStringList &strList);//浮动歌曲列表

    const QString switchFileIconType(const QString& filename);//判断文件图标类型

    bool    getCurrentFileType(const QString &fpath_name);//重载函数1 视频 or 音乐

    bool    getFileType2(const QString& fileName);//根据文件名判断是音乐还是视频

    bool    getFileType(const QString& fileSuffix);//重载函数1 视频 or 音乐

    bool    fileType(int index);// 重载函数1  判断文件类型显示视频还是音乐

    bool    fileType(QUrl furl);// 重载函数2  判断文件类型显示视频还是音乐

    bool    fileType(QStringList &filenames,int index);// 重载函数3  判断文件类型显示视频还是音乐


    void    removeTabwidgetTabBar(QTabWidget *tabwidget);

    void    set_showTwoTabBar(QTabWidget *tabwidget, int index1, QWidget *obj1,QString tabtext1);

    void    set_showTwoTabBar(QTabWidget *tabwidget, int index1, QWidget *obj1,QString tabtext1, int index2, QWidget *obj2, QString tabtext2);

    void    set_fileTolistWidget(QString item);//将服务器获取到的文件列表显

    QString getCurrentMediaPlayFileName();

    QString getCurrentMediaPlayFileUrl();

    QRect   getDesktopScreenGeometry();

    int     getMapKeyFromValue(const QString& value);//map-->根据value找id

protected:
//    bool    nativeEvent(const QByteArray& eventType, void* message, long* result) override;//拉升

    bool    eventFilter(QObject *watched, QEvent *event) override;

//    void    mousePressEvent(QMouseEvent *event) override;

//    void    mouseMoveEvent(QMouseEvent *event) override;

//    void    mouseReleaseEvent(QMouseEvent *event) override;

    void    changeEvent(QEvent *event) override;

    void    showEvent(QShowEvent *event) override;

    void    resizeEvent(QResizeEvent *event) override;

    void    keyPressEvent(QKeyEvent *event) override;

public slots:
    void    slot_clearRecItemLists();

    void    slot_setDanmuOpenClose(bool on);//设置弹幕开关

    void    slot_sendDanmuTextToScreen(QString danmuText);//发送弹幕

    void    slot_findFileFromLineEdit( QString name);//浮动曲库查找搜索内容

    void    slot_itemDoubleClick(QListWidgetItem *item);

    void    slot_openLocalFile();

    void    slot_setMainCurrentIndex(const int index);

    void    slot_closeCurrentWindow();

    void    slot_showNormalWindows();

//    void  clearListWidgetList_user();//清空用户信息

    void    slot_addPlayTempMedia(const QString url);//播放临时点击添加的媒体

    void    slot_clearListWidgetList_playlist();//清空播放列表

    void    slot_clearListWidgetList_collection();//清空收藏列表

    void    slot_clearListWidgetList_history();//清空历史记录

    void    slot_clearUserInputSearchInfo();//清空用户输入的搜索字

    void    slot_setCurrentMediaName(QString name);//进度条上显示媒体名称

    void    slot_setCurrentMediaNamePicture(const QPixmap &pix);//进度条上显示媒体图片

    void    slot_updateFoldButtonGeometry();//更显显示/隐藏按钮的位置

    void    slot_setFoldButtonStyle();//判断箭头的方向

    void    slot_judgeFoldBtnOfRightDockList();//判断右侧停靠栏指示按钮位置

    void    slot_setMainWindowShowFullgreen();

    void    slot_setPlayOrderButtonStyleSheet(int index);

    void    slot_setVideTitleBar(int index);

    void    slot_addTempPlaylist(const int list_id, const QStringList& list, const QUrlQuery &media);//切换播放列表

    void    on_pushButton_pauseStart_clicked();//暂停、播放

    void    slot_updateRateTypeUiLayout();

    void    on_pushButton_next_clicked();//下一首

    void    on_pushButton_previous_clicked();//上一首

    void    slot_receiveSystemTraySendSoundValue(int value);//接收托盘发过来的音量信号

    void    slot_receiveDesktopSoundValueChanged(bool add);//歌词桌面音量改变

    void    slot_setCurrentMediaSoundSatus(bool status);//设置静音样式状态

    void    slot_setCurrentMediaMuted();//设置静音

    void    slot_showPlayerErrot(QMediaPlayer::Error error);//播放错误提示

    void    slot_clearAllPopupUi();//清理所有弹出的界面

private slots:

    QMediaPlaylist *    slot_getCurrentPlayList();//获取当前正在播放的列表

    void    slot_switchPlayerList(QMediaPlaylist *list);//切换播放列表

    void    on_time();

    void    slot_setMediaPlayPosition(int value);//设置播放点

    void    checkChandleMediaPlayerStatus(QMediaPlayer::State newState);//监测处理媒体播放状态

    void    checkChandleMediaStatus();//监测处理媒体状态

    void    loadDefaultLogo();//加载默认图标

    void    slot_firstOpen_clicked();//打开文件

    void    slot_secondOpen_clicked();//重新打开

    void    switchListPage(int index);

    void    setVideoRate(int value);

//    void    on_moreBtn_clicked();

    void    set_adjustBright();

    void    slot_setPlayStatusStyle_main(bool status);//设置主界面的播放按钮样式

    void    slot_hideFloatPlayCtl();

    void    slot_showAdvCtl(bool show);

    void    searchMouseEnterLeaveShow(QObject *watched, QEvent *event);

    bool    videoDouleExit(QObject *watched, QEvent *event);

    void    volumeAdjustShowUi(QObject *watched, QEvent *event);

    void    stackWidgetSliderButtonEventFilter(QObject *watched, QEvent *event);

    void    floatPlayCtrlEnterLeave(QObject *watched, QMouseEvent *mousevent);

    void   slot_showDanmuSettingForm(QObject *watched, QMouseEvent *mousevent);

    void    playlistMouseEnterLeave(QObject *watched, QEvent *event);

    void    stackWidget_player_enter(QObject *watched, QEvent *event);


    //帮助菜单槽函数
    void    help_aboutLocalFile();//本地文件

    void    adjust_playBackMode(int index);//调节播放模式

    void    adjust_aspectRatioMode(int index);//调节屏幕占比

    void    update_adjustBright();

    void    downloadInternetPathRecource();

    void    playHttpRequireRecourse(const QString &url);

//    void  on_pushButton_danmu_clicked();//弹幕按钮

    void    chandleRestoreWindow();

    bool    loadCollectListWidgetList();//加载收藏菜单

    bool    setCollectBtnShowStatus();//设置收藏按钮显示状态

    bool    findCollectListStatus(QListWidget* listdgt, QString name);//遍历列表，没有则添加

    int     getCurrentMediaRowOfCollectList(QListWidget* listdgt,QString name);

    void    addCurrentMediaToList_Collect(QListWidget *destList);//重载函数1：添加进收藏列表1

    void    addCurrentMediaToList_Collect(QListWidget *destList,QString text);//重载函数2：添加进收藏列表1

    void    addCurrentMediaToList_Collect(QListWidget *destList,QListWidgetItem *item);//重载函数3：添加进收藏列表1

    void    addCurrentMediaToList_History(QListWidget *destList);//添加进历史记录

    void    mediaLoadingStatusProgressBar_Start();

    void    mediaLoadingStatusProgressBar_End();

    bool    updateProgressBarGeometry();//加载进度条

    void    updateADVGeomotry();//广告

    void    slot_createRight_playListTable(const QPoint &pos);//播放列表右键菜单

    void    slot_createRight_playCollectTable(const QPoint &pos);//收藏列表右键菜单

    void    slot_createRight_playHistoryTable(const QPoint &pos);//历史列表右键菜单

    void    slot_clearListAllRecords(QListWidget *obj);//清空列表

    void    slot_deleteListRecords(QListWidget *obj,int start,int end);//多选删除

    void    slot_deleteListRecord(QListWidget *obj,int index);//删除某条记录

    void    slot_addListRecordItems(QListWidget *obj);//批量添加

    void    slot_addListRecordItem(QListWidget *obj);//单个添加

    void    slot_playCurrentListItem(QListWidget *obj,int index);//播放选中的某条记录

    void    slot_playNextListItem(QListWidget *obj,int index);//播放选中的某条记录的吓一条

    void    slot_downloadListItem(QListWidget *obj,int index);//下载选中的某条记录

    void    slot_collectListItem(QListWidget *obj,QString text);//收藏选中的某条记录

    void    slot_selectAllListItem(QListWidget *obj);//全选

    void    slot_saveCapturePixmap(QVideoFrame& frame);

private:
    QString         Base64ToQStr(QString base64Str);

    QString         Base64UrlToString(QUrl base64Url);

    void    setAnyFrameMediaUrl(const QUrl& url);//设置求取任意帧的资源路径

    //弹幕位置
    QRect    calUpdateDanmuGeometry();//计算更新弹幕显示位置

    void     setDanmuInfo(Danmu* danmu, const QString &color, const QFont &danmuFont, double transDepth);//设置弹幕颜色，字体宽度，透明度

signals:
    void    sig_sendSwitchToMusicPage(QString name);

    void    sig_startCloseAppliction();

    void    sig_sendToMusicList();

    void    sig_winVStatus(bool);

    void    sig_mediaIsMuted(bool);

    void    sig_currentMediaPlayStatus(bool status);

    void    sig_currentMediaSoundValueChange(int value);

    void    sig_currentMediaSoundChanged(bool);

    void    sig_mainPlayerClose(bool);

    void    sig_playerIsMutedStatus(bool);

    void    sig_playlistCurrentIndex(int);//临时列表当前索引

    void    sig_userLogin();

    void    sig_videoDanmuStatus(bool);

    void    sig_videoDanmuAnim(bool);//弹幕动画

    void    sig_winResize();

    void    sig_mediaListIndex(int);

    void    sig_showMainForm();


private:
    Ui::MultipPlayer *ui;
//    QRect                       m_oldScreen;
    QAction                     *m_actionBullet     = nullptr;//弹幕登录开关
    QTimer                      *m_pTimer           = nullptr; //进度滚动条更新
    QTimer                      *m_pTimer2          = nullptr; //延迟ui界面
    QTimer                      *m_showFloat        = nullptr;//定时显示浮动界面
    QWidget                     *m_widget1          = nullptr;
    QWidget                     *m_widget2          = nullptr;
    QToolBox                    *m_toolBox          = nullptr;
    QLineEdit                   *m_lineEdit         = nullptr;
    muteDialog                  *m_muteDlg          = nullptr;
    VideoBlank                  *m_videoBlank       = nullptr;
    QTabWidget                  *m_tabWidget1       = nullptr; //节目列表选项
    CommentTab                  *m_commentTab       = nullptr;
    CustomFileDialog            *m_cusDialog        = nullptr;//自定义选择框界面
    ListManager                 *m_listManager      = nullptr;//列表管理器
    QListWidget                 *m_listWisget1      = nullptr;
    QListWidget                 *m_listWisget2      = nullptr;//本地打开文件
    QListWidget                 *m_listWisget3      = nullptr;
    QListWidget                 *m_listWisget4      = nullptr;
    QHBoxLayout                 *m_hLayout          = nullptr; //搜索按钮和搜索框布局
    QHBoxLayout                 *m_hboxlayout_rlist = nullptr; //右侧播放列表
    QVBoxLayout                 *m_vHlayout         = nullptr; //布局listwidget和m_hLayout
    QVBoxLayout                 *m_vHlayout_jianjie = nullptr; //视频简介布局
    QVBoxLayout                 *m_vHlayout_jieshao = nullptr; //视频介绍布局
    QPushButton                 *m_searchBtn        = nullptr;
    QPushButton                 *m_foldBtn          = nullptr;
    AdjustBright                *m_adjustBright     = nullptr;//参数调整界面
    VideoClarity                *m_videoClarity     = nullptr;//清晰度调整界面
    MusicPlayShow               *m_musicUi          = nullptr;
    VideoTitleBar               *m_videoTitleBar    = nullptr;
    DanmuSetting                *m_danmuSetting     = nullptr;//弹幕设置
    DramaListForm               *m_dramaList        = nullptr;//系列推荐
    RecomVideoTab               *m_recomTab         = nullptr;
    QMediaPlayer                *m_player           = nullptr;
    QMediaPlayer                *m_player2          = nullptr;
    MyVideoWidget               *videoWidget        = nullptr;//视频播放界面
    QMediaPlaylist              *playlist           = nullptr;//播放列表1 正式
    QMediaPlaylist              *playlist_t         = nullptr;//播放列表2 临时
    VideoSurface                *m_videoSurface     = nullptr;//获取视频任意帧

    int                         m_voice;                        //静音之前的值
    bool                        m_winMax;                       //默认非最大化
    bool                        m_extraFlag         = false;    //是否为外部拖动文件打开的播放器（默认不是）
    bool                        m_isClose;
    bool                        m_orderStatus       = false;
    bool                        m_isHide            = false;    //侧边栏显示/隐藏按钮，默认没隐藏
    bool                        m_newStart          = false;    //可以打开新文件按钮标识
    bool                        m_bPress            = false;
    bool                        m_muteShow          = false;    //默认不显示
    bool                        m_jiemuShow         = false;    //默认不显示
    bool                        m_danmuStatus       = false;    //默认不显示
    bool                        m_collectStatus     = false;    //默认不显示
    bool                        m_selectAllStatus1  = false;    //全选状态 默认没有全选
    bool                        m_selectAllStatus2  = false;    //全选状态 默认没有全选
    qint64                      m_times;                        //文件长度
    QPoint                      m_mvPos;
    QPoint                      m_videoPos;

    QStringList                 m_fileNames;                    //文件名称列表
    QStringList                 m_tempList;                    //临时播放列表
    QStringList                 list_temp;

    int                         m_playlist_id = -1;//默认-1
    QMap<int,QString>           m_mapList;                      //存储歌名路径
    QMap<int,QString>           m_mapList2;                     //存储歌名带后缀
    QMap<int,QString>           m_t_MapList;                     //临时存储歌名带后缀
    QMap<int,QString>           m_mapList_collect;
    QMap<int,QString>           m_mapList_history;
    QMediaPlayer::State         m_playerState;
    int                         m_curMediaId = 0;
    QString                     m_curMediaName;
    QString                     m_curMediaUrl;
    QUrl                        m_anyFrameMediaUrl;

/*以下为界面拉伸所用*/
    bool                        _isleftpressed      = false;    //判断是否是左键点击
    int                         _curpos = 0;                    //鼠标左键按下时光标所在区域
    QPoint                      _plast;                         //获取鼠标左键按下时光标在全局(屏幕而非窗口)的位置
    int                         countRow(QPoint p);             //获取光标在窗口所在区域的 行   返回行数
    int                         countFlag(QPoint p,int row);    //获取光标在窗口所在区域的 列  返回行列坐标
    void                        setCursorType(int flag);        //根据传入的坐标，设置光标样式
};

#endif // MULTIPPLAYER_H

#-------------------------------------------------
#
#Project created by QtCreator 2022-01-23T05:25:36
#音视频播放器
#-------------------------------------------------

QT       += core gui xml  multimediawidgets multimedia sql network webenginewidgets concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += C++11 ##使用C++11某些新语法
TARGET = VideoPlayer
TEMPLATE = app
RC_ICONS = favicon.ico

# 以管理员运行(msvc方式)
#mingw需要通过加入文件的形式
#QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"

DEFINES += QT_DEPRECATED_WARNINGS
#禁用qdebug打印输出
#DEFINES     += QT_NO_DEBUG_OUTPUT
#调试窗口必须要release才能生效，而后再使用debug
#CONFIG += console pro
#关闭编译警告提示
CONFIG      += warn_off

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#DESTDIR  = $$PWD/bin

SOURCES += \
        main.cpp \
        MainWidget.cpp
HEADERS += \
        MainWidget.h

#此处添加模块
include($$PWD/skin/skin.pri)                #皮肤管理模块
include($$PWD/style/style.pri)              #全局样式
include($$PWD/login/login.pri)              #登录注册模块
include($$PWD/qrcode/qrcode.pri)            #二维码
include($$PWD/global/global.pri)            #全局相关（程序路径等）
include($$PWD/updater/updater.pri)          #程序更新器模块
include($$PWD/lunbotu/lunbotu.pri)          #轮播图模块
include($$PWD/network/network.pri)          #网络请求
include($$PWD/browser/browser.pri)          #浏览器
include($$PWD/mythread/mythread.pri)        #工作线程处理
include($$PWD/database/database.pri)        #数据库
include($$PWD/delegate/delegate.pri)        #代理相关
include($$PWD/slidebar/slidebar.pri)        #左侧边栏
include($$PWD/titlebar/titlebar.pri)        #主界面标题栏
include($$PWD/customer/customer.pri)        #自定义控件
include($$PWD/ffmpeg/ffmpeg.pri)            #视频处理相关
include($$PWD/creator/creator.pri)          #创作中心
include($$PWD/pixviewer/pixviewer.pri)      #
#include($$PWD/facebread/facebread.pri)     #表情包
include($$PWD/pernotice/pernotice.pri)      #消息栏
include($$PWD/desktoplyric/desktop.pri)     #桌面歌词
include($$PWD/miniplayer/miniplayer.pri)    #迷你播放器
include($$PWD/mainwidget/mainwidget.pri)    #承载主界面
include($$PWD/qcustomplot/qcustomplot.pri)  #
include($$PWD/musicmodels/musicmodels.pri)  #音乐模块
include($$PWD/videomodels/videomodels.pri)  #视频模块
include($$PWD/fileshandle/fileshandle.pri)  #文件处理
include($$PWD/messagebox/messagebox.pri)    #消息盒子
include($$PWD/splashscreen/splashscreen.pri)#开机屏保

#指定可执行程序输出目录（此配置需重编译生效）
CONFIG(debug, debug|release){
    DESTDIR = $$PWD/bin/debug
}else{
    DESTDIR = $$PWD/bin/release
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



RESOURCES += \
    res_audio.qrc \
    res_image.qrc \
    res_font.qrc \
    res_style.qrc \
    res_config.qrc

FORMS +=

#说明：
#引入头文件和库文件只是在调试的时候进行查找调用，
#打包后，程序执行时，只需要找到真正执行的动态库即可，与下面配置无关

win32{
#引入第三方库头文件(ffmpeg)
DEPENDPATH += $$PWD/library/ffmpeg/include
INCLUDEPATH += $$PWD/library/ffmpeg/include
#添加静态库
LIBS += -L$$PWD/library/ffmpeg/lib -lavutil -lavformat -lavcodec -lavfilter -lswscale -lswresample
#添加动态库
LIBS += -L$$PWD/library/ffmpeg/bin -lavutil -lavformat -lavcodec -lavfilter -lswscale -lswresample
}

#-------------------------------------------------
#
# Project created by QtCreator 2022-01-23T05:25:36
#音视频播放器
#-------------------------------------------------

QT       += core gui xml  multimediawidgets multimedia sql network webenginewidgets

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


SOURCES += \
        main.cpp \
        MainWidget.cpp
HEADERS += \
        MainWidget.h

#此处添加模块
include($$PWD/skin/skin.pri)
include($$PWD/style/style.pri)
include($$PWD/login/login.pri)
include($$PWD/global/global.pri)
include($$PWD/updater/updater.pri)
include($$PWD/lunbotu/lunbotu.pri)
include($$PWD/network/network.pri)
include($$PWD/browser/browser.pri)
include($$PWD/mythread/mythread.pri)
include($$PWD/database/database.pri)
include($$PWD/delegate/delegate.pri)
include($$PWD/slidebar/slidebar.pri)
include($$PWD/titlebar/titlebar.pri)
include($$PWD/customer/customer.pri)
include($$PWD/creator/creator.pri)
include($$PWD/facebread/facebread.pri)
include($$PWD/pernotice/pernotice.pri)
include($$PWD/desktoplyric/desktop.pri)
include($$PWD/miniplayer/miniplayer.pri)
include($$PWD/mainwidget/mainwidget.pri)
include($$PWD/qcustomplot/qcustomplot.pri)
include($$PWD/musicmodels/musicmodels.pri)
include($$PWD/videomodels/videomodels.pri)
include($$PWD/fileshandle/fileshandle.pri)
include($$PWD/messagebox/messagebox.pri)
include($$PWD/splashscreen/splashscreen.pri)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    titleBar

RESOURCES += \
    res_audio.qrc \
    res_image.qrc \
    res_font.qrc

FORMS +=


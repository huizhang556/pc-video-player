#ifndef CUSWEBBROWSER_H
#define CUSWEBBROWSER_H
#include "global/Global.h"
#include <QUrl>
#include <QMenu>
#include <QCursor>
#include <QAction>
#include <QWidget>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QChildEvent>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineHistory>
#include <QWebEngineSettings>
#include <QWebEngineCookieStore>
#include <QWebEngineDownloadItem>

class CusWebBrowser : public QWebEngineView
{
    Q_OBJECT

public:
    explicit CusWebBrowser(QWidget *parent = nullptr);
    ~CusWebBrowser();
    QUrl getCurrentWebPageUrl();

protected:
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    bool event(QEvent *et) override;
    void contextMenuEvent(QContextMenuEvent*) override;//重写右键菜单内容
public slots:
    void slots_createNewWindows(const QUrl url);
    void slots_loadNewUrl(QString path);
    void slot_makeDir();
    void slots_back();
    void slots_refreshen();
    void slots_advance();
    void slots_home();
    void slots_sendToNewAddress();
    void slot_createCustomRightMenu();//右键菜单内容

signals:
    void sig_sendToNewUrl(QUrl &url);
    void sig_currentPageSwitch(QUrl &url);
private slots:
    void slot_back();
    void slot_forward();
    void slot_reload();
    void slot_selectall();
    void slot_find();
    void slot_copy();
    void slot_copyWebUrl();
    void slot_paste();
    void slot_cut();
    void slot_undo();
    void slot_copyImageUrl();
    void slot_saveImage();
    void slot_savePage();
    void slot_browserPageSource();
private:
    QUrl     newUrl;
    QObject         *m_child        =   nullptr;
};

#endif // CUSWEBBROWSER_H

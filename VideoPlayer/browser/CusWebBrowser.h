#ifndef CUSWEBBROWSER_H
#define CUSWEBBROWSER_H

#include <QUrl>
#include <QWidget>
#include <QWebEngineView>

class CusWebBrowser : public QWebEngineView
{
    Q_OBJECT

public:
    explicit CusWebBrowser(QWidget *parent = nullptr);
    ~CusWebBrowser();
    QUrl getCurrentWebPageUrl();

protected:
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override;

public slots:
    void slots_createNewWindows(const QUrl url);
    void slots_loadNewUrl(QString path);
    void slots_back();
    void slots_refreshen();
    void slots_advance();
    void slots_home();
    void slots_sendToNewAddress();
signals:
    void sig_sendToNewUrl(QUrl &url);
    void sig_currentPageSwitch(QUrl &url);
private:
    QUrl     newUrl;
};

#endif // CUSWEBBROWSER_H

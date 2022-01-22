#ifndef CUSWEBBROWSER_H
#define CUSWEBBROWSER_H

#include <QWidget>
#include <QWebEngineView>
#include <QUrl>

class CusWebBrowser : public QWebEngineView
{
    Q_OBJECT

public:
    explicit CusWebBrowser(QWidget *parent = nullptr);
    ~CusWebBrowser();

protected:
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override;

private slots:
    void slots_createNewWindows(const QUrl url);
private:
    QUrl        newUrl;
};

#endif // CUSWEBBROWSER_H

#include "CusWebBrowser.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEngineCookieStore>
#include <QDebug>

CusWebBrowser::CusWebBrowser(QWidget *parent) :
    QWebEngineView(parent)
{
    this->showMaximized();
//    this->load(QUrl("https://v.qq.com/"));
    this->load(QUrl("https://www.baidu.com/"));
//    this->page()->settings()->setAttribute(QWebEngineSettings::ShowScrollBars,false);//不显示滚动条    
    //这两个信号槽要配合使用，有先后顺序之分，一个触发会导致另一个触发
    connect(this->page(),&QWebEnginePage::linkHovered,this,&CusWebBrowser::slots_createNewWindows);//就是鼠标放上去的操作
//    connect(this,SIGNAL(urlChanged(QUrl)),this,SLOT(slots_sendToNewAddress()));
}

CusWebBrowser::~CusWebBrowser()
{
//    this->page()->profile()->clearHttpCache();//清除缓存
//    this->page()->profile()->cookieStore()->deleteAllCookies();//清除cookies
}

QUrl CusWebBrowser::getCurrentWebPageUrl()
{
    return this->page()->url().toString();
    qDebug() << this->page()->url().toString();
}

QWebEngineView *CusWebBrowser::createWindow(QWebEnginePage::WebWindowType type)
{
    if(type == QWebEnginePage::WebBrowserTab)
    {
        emit sig_sendToNewUrl(newUrl);
    }
    else if(type == QWebEnginePage::WebBrowserWindow)
    {
    this->load(newUrl);
    }
    else if(type == QWebEnginePage::WebDialog)
    {
        QMessageBox::information(this,
                                 QString::fromLocal8Bit("提示"),
                                 QString::fromLocal8Bit("这是一个网页弹框WebDialog！")
                                 );
    }
    else if(type == QWebEnginePage::WebBrowserWindow)
    {
        QMessageBox::information(this,
                                 QString::fromLocal8Bit("提示"),
                                 QString::fromLocal8Bit("这是WebBrowserWindow！")
                                 );
    }
    return 0;
}

void CusWebBrowser::slots_createNewWindows(const QUrl url)
{
    newUrl = url;
    getCurrentWebPageUrl();
    qDebug() << "emit sig_sendToNewUrl(newUrl)" << newUrl;
}

/*处理输入框传过来的url*/
void CusWebBrowser::slots_loadNewUrl(QString path)
{
//    qDebug() << path;
    if(!path.isEmpty())
    {
        this->load(path);
        newUrl = QUrl(path);
        qDebug() << "NEW URL = " << newUrl;
    }
    else
    {
        qDebug() << path;
    }
}

/*返回*/
void CusWebBrowser::slots_back()
{
    qDebug() << "received slots_back signal!";
    this->back();
}

/*后退*/
void CusWebBrowser::slots_refreshen()
{
    qDebug() << "received slots_refreshen signal!";
    this->reload();
}

/*前进*/
void CusWebBrowser::slots_advance()
{
    qDebug() << "received slots_advance signal!";
    this->forward();
}

/*返回主页*/
void CusWebBrowser::slots_home()
{
    this->load(QUrl("https://www.baidu.com/"));
    newUrl = QUrl("https://www.baidu.com/");
}

void CusWebBrowser::slots_sendToNewAddress()
{
    emit sig_sendToNewUrl(newUrl);
}

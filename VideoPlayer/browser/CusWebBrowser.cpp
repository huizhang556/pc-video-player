#include "CusWebBrowser.h"
#include <QHBoxLayout>
#include <QWebEngineSettings>
#include <QWebEnginePage>
#include <QDebug>

CusWebBrowser::CusWebBrowser(QWidget *parent) :
    QWebEngineView(parent)
{
    this->showMaximized();
//    this->load(QUrl("https://v.qq.com/"));
    this->load(QUrl("https://www.baidu.com/"));
//    this->page()->settings()->setAttribute(QWebEngineSettings::ShowScrollBars,false);//不显示滚动条    
    //这两个信号槽要配合使用，有先后顺序之分，一个触发会导致另一个触发
    connect(this->page(),&QWebEnginePage::linkHovered,this,&CusWebBrowser::slots_createNewWindows);
    connect(this,SIGNAL(urlChanged(QUrl)),this,SLOT(slots_createNewWindows(QUrl)));
}

CusWebBrowser::~CusWebBrowser()
{

}

QWebEngineView *CusWebBrowser::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type);
//    CusWebBrowser *webbrowser = new CusWebBrowser(this);
//    QWidget *newWeb =  new QWidget(this) ;
//    QHBoxLayout *layout = new QHBoxLayout(this);
//    layout->setMargin(0);
//    layout->addWidget(webbrowser);
//    newWeb->setLayout(layout);
//    webbrowser->showMaximized();
//    newWeb->showMaximized();
    this->load(newUrl);
    return 0;
}

void CusWebBrowser::slots_createNewWindows(const QUrl url)
{
    newUrl = url;
}

/*处理输入框传过来的url*/
void CusWebBrowser::slots_loadNewUrl(QString path)
{
//    qDebug() << path;
    if(!path.isEmpty())
    {
        this->load(path);
        newUrl = QUrl(path);
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

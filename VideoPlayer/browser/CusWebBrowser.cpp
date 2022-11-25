#include "CusWebBrowser.h"
#include <QDebug>

CusWebBrowser::CusWebBrowser(QWidget *parent) :
    QWebEngineView(parent)
{
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING","8999"); //调试窗口, 需重新编译生效
    this->showMaximized();
    installEventFilter(this);
//    this->load(QUrl("http://www.baidu.com"));
//    this->load(QUrl("http://82.156.175.81/study/index.html"));// 不设置一个默认url,默认什么都不显示
    //加载外部文件方法1
//    QString htmlPath = Global::appDirPath + QString::fromLocal8Bit("/html/study/index.html");
//    QFile file(htmlPath);//直接加载本地html文件，外部对象由本地文件的相对路径查找，因此不需要设置
//    if (!file.exists())
//    {
//        return;
//    }
//    this->load(QUrl("file:///" + htmlPath));

    //加载外部文件方法2
//    QString htmlPath = Global::appDirPath + QString::fromLocal8Bit("/html/Qt__Key键盘按键详细说明.html");//从此html文件中读取内容后写入webview
//    QUrl baseUrl = Global::appDirPath + "/html/";//外部对象，包括以下CSS和js文件
//    QFile file(htmlPath);
//    if (!file.open(QIODevice::ReadOnly))
//    {
//        return;
//    }
//    QString htmlData = file.readAll().constData();
//    file.close();
//    this->setHtml(htmlData, baseUrl);

    this->page()->setAudioMuted(false);//不自动静音
    this->settings()->setAttribute(QWebEngineSettings::PluginsEnabled,true);//支持插件
    this->settings()->setAttribute(QWebEngineSettings::SpatialNavigationEnabled, true);
    this->setContextMenuPolicy(Qt::DefaultContextMenu);
    this->page()->setBackgroundColor(QColor(38,40,41));

//    this->page()->settings()->setAttribute(QWebEngineSettings::ShowScrollBars,false);//不显示滚动条    
    //这两个信号槽要配合使用，有先后顺序之分，一个触发会导致另一个触发
//    connect(this,&CusWebBrowser::customContextMenuRequested,this,&CusWebBrowser::slot_createCustomRightMenu);
    connect(this->page(),&QWebEnginePage::linkHovered,this,&CusWebBrowser::slots_createNewWindows);//就是鼠标放上去的操作
//    connect(this,SIGNAL(urlChanged(QUrl)),this,SLOT(slots_sendToNewAddress()));

//    this->pageAction(QWebEnginePage::Back)->setText(QString::fromLocal8Bit("后退"));
//    this->pageAction(QWebEnginePage::Forward)->setText(QString::fromLocal8Bit("前进"));
//    this->pageAction(QWebEnginePage::Reload)->setText(QString::fromLocal8Bit("刷新"));
//    this->pageAction(QWebEnginePage::SavePage)->setText(QString::fromLocal8Bit("保存页面"));
//    this->pageAction(QWebEnginePage::ViewSource)->setText(QString::fromLocal8Bit("查看源码"));
//    this->pageAction(QWebEnginePage::Undo)->setText(QString::fromLocal8Bit("撤退"));
//    this->pageAction(QWebEnginePage::Redo)->setText(QString::fromLocal8Bit("重做"));
//    this->pageAction(QWebEnginePage::Cut)->setText(QString::fromLocal8Bit("剪切"));
//    this->pageAction(QWebEnginePage::Copy)->setText(QString::fromLocal8Bit("复制"));
//    this->pageAction(QWebEnginePage::Paste)->setText(QString::fromLocal8Bit("粘贴"));
//    this->pageAction(QWebEnginePage::PasteAndMatchStyle)->setText(QString::fromLocal8Bit("按样式粘贴"));
//    this->pageAction(QWebEnginePage::SelectAll)->setText(QString::fromLocal8Bit("全选"));
//    qDebug()<< QString::fromLocal8Bit("标题--->") <<this->title();
//    qDebug()<< QString::fromLocal8Bit("图标--->") <<this->icon();
}

CusWebBrowser::~CusWebBrowser()
{
    //注意：清除后，每删掉一个网页，原先的登录信息全部清除
//    this->page()->profile()->clearHttpCache();//清除缓存
//    this->page()->profile()->cookieStore()->deleteAllCookies();//清除cookies
}

QString CusWebBrowser::getCurrentWebPageUrl()
{
    return this->page()->url().toString();
    qDebug() << this->page()->url().toString();
}

QString CusWebBrowser::getCurrentWebPageIconUrl()
{
    return this->page()->iconUrl().toString();
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
       emit sig_currentPageSwitch(newUrl);
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



bool CusWebBrowser::eventFilter(QObject *watched, QEvent *event)
{
    QWheelEvent *wevent = static_cast<QWheelEvent*>(event);
    if(event->type() == QEvent::Wheel)
    {
        if(QApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            if(wevent->delta() > 0)//范围值：[0.25,5]
            {
                this->setZoomFactor(this->zoomFactor()+0.05);
                qDebug() <<this->zoomFactor();
            }
            else
            {
                this->setZoomFactor(this->zoomFactor()-0.05);
                qDebug() <<this->zoomFactor();
            }
        }

    }
    return QWebEngineView::eventFilter(watched,event);
}

bool CusWebBrowser::event(QEvent *et)
{
    if(et->type() == QEvent::ChildPolished)
    {
        QChildEvent *chet = static_cast<QChildEvent*>(et);
        m_child = chet->child();
       if(m_child)
       {
           chet->child()->installEventFilter(this);
       }
    }
    return QWebEngineView::event(et);
}

void CusWebBrowser::contextMenuEvent(QContextMenuEvent *)
{
    slot_createCustomRightMenu();
}

void CusWebBrowser::setCurrentDefaultUrl(const QString &url)
{
    this->load(QUrl(url));
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

void CusWebBrowser::slot_makeDir()
{

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

//自定义右键菜单
void CusWebBrowser::slot_createCustomRightMenu()
{
    QMenu *rmenu = new QMenu(this);
    rmenu->setObjectName(QString::fromLocal8Bit("browser_rmenu"));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("返回"),this,SLOT(slot_back()));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("前进"),this,SLOT(slot_forward()));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("重新加载"),this,SLOT(slot_reload()));
    rmenu->addSeparator();
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("复制"),this,SLOT(slot_copy()));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("粘贴"),this,SLOT(slot_paste()));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("剪贴"),this,SLOT(slot_cut()));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("撤回"),this,SLOT(slot_undo()));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("全选"),this,SLOT(slot_selectall()));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("查找"),this,SLOT(slot_find()));
    rmenu->addSeparator();
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("复制网页地址"),this,SLOT(slot_copyWebUrl()));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("复制图片链接"),this,SLOT(slot_copyImageUrl()));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("复制图片至剪切板"),this,SLOT(slot_saveImage()));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("保存网页"),this,SLOT(slot_savePage()));
    rmenu->addAction(QIcon(""),QString::fromLocal8Bit("审查源码"),this,SLOT(slot_browserPageSource()));
    rmenu->exec(QCursor::pos());
    delete rmenu;
}


void CusWebBrowser::slot_back()
{
    this->pageAction(QWebEnginePage::WebAction::Back)->trigger();
}

void CusWebBrowser::slot_forward()
{
    this->pageAction(QWebEnginePage::WebAction::Forward)->trigger();
}

void CusWebBrowser::slot_reload()
{
    this->pageAction(QWebEnginePage::WebAction::Reload)->trigger();
}

void CusWebBrowser::slot_selectall()
{
    this->pageAction(QWebEnginePage::WebAction::SelectAll)->trigger();
}

void CusWebBrowser::slot_find()
{

}

void CusWebBrowser::slot_copy()
{
    this->pageAction(QWebEnginePage::WebAction::Copy)->trigger();
}

void CusWebBrowser::slot_copyWebUrl()
{
    this->pageAction(QWebEnginePage::WebAction::CopyLinkToClipboard)->trigger();
}

void CusWebBrowser::slot_paste()
{

    this->pageAction(QWebEnginePage::WebAction::Paste)->trigger();
}

void CusWebBrowser::slot_cut()
{
    this->pageAction(QWebEnginePage::WebAction::Cut)->trigger();
}

void CusWebBrowser::slot_undo()
{
    this->pageAction(QWebEnginePage::WebAction::Undo)->trigger();
}

void CusWebBrowser::slot_copyImageUrl()
{
    this->pageAction(QWebEnginePage::WebAction::CopyImageUrlToClipboard)->trigger();
}

void CusWebBrowser::slot_saveImage()
{
    this->pageAction(QWebEnginePage::WebAction::CopyImageToClipboard)->trigger();
}

void CusWebBrowser::slot_savePage()
{
    this->pageAction(QWebEnginePage::WebAction::SavePage)->trigger();
}

void CusWebBrowser::slot_browserPageSource()
{
//    this->pageAction(QWebEnginePage::WebAction::InspectElement)->trigger();
    QUrl url("http://127.0.0.1:8999");//进入调试界面
    emit sig_sendToNewUrl(url);
}

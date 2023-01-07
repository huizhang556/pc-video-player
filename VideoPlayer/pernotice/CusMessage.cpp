#include "CusMessage.h"
#include "ui_CusMessage.h"

//系统通知类型
CusMessage::CusMessage(const QString &title, const QString &datatime, const QString &content, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusMessage)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    ui->label_systitle->setText(title);
    ui->label_sysPubTime->setText(datatime);
    QString html = QString(R"(<span style=" font-family:'FangSong'; font-size:17px; color:#757a81;">%1</span>)").arg(content);
    ui->textBrowser_SYScontent->insertHtml(html);
    ui->stackedWidget_MSG->setCurrentWidget(ui->page_systemMsg);
    setFixedHeight(getDynamicHeight(ui->textBrowser_SYScontent));
}

//聊天类型
CusMessage::CusMessage(NEWSTYPE type, const QString &header, const QString &datatime, const QString &cotent, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusMessage)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    selectType(type,header,datatime,cotent);
}

CusMessage::~CusMessage()
{
    delete ui;
}

void CusMessage::initWorkUI()
{
    ui->label_systitle->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->label_sysPubTime->setAlignment(Qt::AlignCenter);
    ui->label_Ltime->setAlignment(Qt::AlignCenter);
    ui->label_Rtime->setAlignment(Qt::AlignCenter);

    ui->textBrowser_SYScontent->setFixedWidth(370);
    ui->textBrowser_Lcontent->setFixedWidth(265);
    ui->textBrowser_Rcontent->setFixedWidth(265);

    ui->textBrowser_SYScontent->setOpenExternalLinks(false);
    ui->textBrowser_Lcontent->setOpenExternalLinks(false);
    ui->textBrowser_Rcontent->setOpenExternalLinks(false);

    ui->textBrowser_SYScontent->setAlignment(Qt::AlignCenter);
    ui->textBrowser_Lcontent->setAlignment(Qt::AlignCenter);
    ui->textBrowser_Rcontent->setAlignment(Qt::AlignCenter);

    ui->textBrowser_SYScontent->setContextMenuPolicy(Qt::NoContextMenu);
    ui->textBrowser_Lcontent->setContextMenuPolicy(Qt::NoContextMenu);
    ui->textBrowser_Rcontent->setContextMenuPolicy(Qt::NoContextMenu);

    ui->textBrowser_SYScontent->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser_Lcontent->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser_Rcontent->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->textBrowser_SYScontent->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser_Lcontent->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser_Rcontent->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void CusMessage::handleSignalsAndSlots()
{
    connect(ui->pushButton_sysSetMenu,&QPushButton::clicked,[=](){emit sig_item_delete();});
//    connect(ui->textBrowser_SYScontent->document(),SIGNAL(contentsChanged()),this,SLOT(textAreaChanged()));
    connect(ui->textBrowser_SYScontent,&QTextBrowser::anchorClicked,[=](const QUrl& url){
        QDesktopServices::openUrl(url);
    });

    connect(ui->textBrowser_Lcontent,&QTextBrowser::anchorClicked,[=](const QUrl& url){
        QDesktopServices::openUrl(url);
    });

    connect(ui->textBrowser_Rcontent,&QTextBrowser::anchorClicked,[=](const QUrl& url){
        QDesktopServices::openUrl(url);
    });
}

void CusMessage::selectType(NEWSTYPE type, const QString &header, const QString &datatime, const QString &cotent)
{
    switch (type) {
    case NEWS_LEFT:
    {
        ui->label_Ltime->setText(datatime);
        QString html = QString(R"(<span style=" font-family:'FangSong'; font-size:17px; color:#757a81;">%1</span>)").arg(cotent);
        ui->textBrowser_Lcontent->insertHtml(html);
        ui->stackedWidget_MSG->setCurrentWidget(ui->page_perMsg_L);
        setFixedHeight(getDynamicHeight(ui->textBrowser_Lcontent));
    }
        break;
    case NEWS_RIGHT:
    {
        ui->label_Rtime->setText(datatime);
        QString html = QString(R"(<span style=" font-family:'FangSong'; font-size:17px; color:#757a81;">%1</span>)").arg(cotent);
        ui->textBrowser_Rcontent->insertHtml(html);
//        ui->textBrowser_Rcontent->setPlainText(cotent);
//        ui->textBrowser_Rcontent->setText(cotent);
        ui->stackedWidget_MSG->setCurrentWidget(ui->page_perMsg_R);
        setFixedHeight(getDynamicHeight(ui->textBrowser_Rcontent));
    }
        break;
    default:
        break;
    }
}

int CusMessage::getDynamicHeight(QTextBrowser* browser)
{
//    qDebug() <<QString(u8"当前滚动条最大值：%1").arg(browser->verticalScrollBar()->value());
//    QTextCursor cursor = browser->textCursor();
//    cursor.movePosition(QTextCursor::End);
//    QString textContent = browser->toPlainText();
//    int length = textContent.count();
//    int mulnum = 0;//默认给1行
////    qDebug() << QString(u8"目前字数：%1").arg(length);
//    int num1 = length / 18;//商
//    int num2 = length % 18;//余数
////    qDebug() << QString(u8"18的倍数%1").arg(num1);
////    qDebug() << QString(u8"18的余数%1").arg(num2);
//    if(num2 == 0)//整除
//    {
//        if(num1 != 0)
//        {
//            mulnum =  num1;
//        }
//        else
//        {
//            mulnum = 1;
//        }
//    }
//    else//非整除
//    {
//        if(num1 != 0)
//        {
//           mulnum = num1+1;
//        }
//        else
//        {
//            mulnum = 1;
//        }
//    }
////    qDebug() <<QString(u8"最后求的真实的行数：%1").arg(mulnum);
//    //单行20px 默认留出3行高度60px 标题28px 上下margin 6px 不知名10px
//    int realHeight = 88;//default height
//    if(mulnum > 2)
//    {
//        realHeight = 20*(mulnum-2)+88;
//    }
//    else
//    {
//        realHeight = 88;
//    }
////    qDebug() <<QString(u8"最后求的真实的高度：%1").arg(realHeight);
//    return realHeight;

    //第二种方法
//    int height = browser->verticalScrollBar()->maximum() - browser->verticalScrollBar()->minimum() + browser->verticalScrollBar()->pageStep();
    browser->document()->adjustSize();//将文档调整到合理的大小
    int newheight = browser->document()->size().height();
    if (newheight != browser->height())
    {
        browser->setFixedHeight(newheight);//1.自己先扩展自己的高度2.整体设置窗口高度
    }
//    qDebug() << QString(u8"文本区域高度：") <<  newheight;
    if(newheight < 50)//小于头像高度：按照头像高度+38算
    {
        browser->setFixedHeight(36);
        return 88;
    }
    else
    {
        return newheight + 36;
    }

}

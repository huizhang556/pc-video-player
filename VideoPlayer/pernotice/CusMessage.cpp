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
    QString html = QString(R"(<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;
                            -qt-block-indent:0; text-indent:0px;"><span style=" font-family:'SimSun'; font-size:14px; color:#757a81;">%1</span><br/></p>)").arg(content);
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
    ui->label_systitle->setAlignment(Qt::AlignLeft);
    ui->label_sysPubTime->setAlignment(Qt::AlignRight);
    ui->label_Ltime->setAlignment(Qt::AlignCenter);
    ui->label_Rtime->setAlignment(Qt::AlignCenter);

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

}

void CusMessage::selectType(NEWSTYPE type, const QString &header, const QString &datatime, const QString &cotent)
{
    switch (type) {
    case NEWS_LEFT:
    {
        ui->label_Ltime->setText(datatime);
        QString html = QString(R"(<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;
                                -qt-block-indent:0; text-indent:0px;"><span style=" font-family:'SimSun'; font-size:14px; color:#757a81;">%1</span><br/></p>)").arg(cotent);
        ui->textBrowser_Lcontent->insertHtml(html);
        ui->stackedWidget_MSG->setCurrentWidget(ui->page_perMsg_L);
        setFixedHeight(getDynamicHeight(ui->textBrowser_Lcontent));
    }
        break;
    case NEWS_RIGHT:
    {
        ui->label_Rtime->setText(datatime);
        QString html = QString(R"(<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;
                                -qt-block-indent:0; text-indent:0px;"><span style=" font-family:'SimSun'; font-size:14px; color:#757a81;">%1</span><br/></p>)").arg(cotent);
        ui->textBrowser_Rcontent->insertHtml(html);
//        ui->textBrowser_Rcontent->setPlainText(cotent);
        ui->stackedWidget_MSG->setCurrentWidget(ui->page_perMsg_R);
        setFixedHeight(getDynamicHeight(ui->textBrowser_Rcontent));
    }
        break;
    default:
        break;
    }
}

int CusMessage::getDynamicHeight(const QTextBrowser* browser)
{
//    qDebug() <<QString(u8"当前滚动条最大值：%1").arg(browser->verticalScrollBar()->value());
    QTextCursor cursor = browser->textCursor();
    cursor.movePosition(QTextCursor::End);
    QString textContent = browser->toPlainText();
    int length = textContent.count();
    int mulnum = 0;//默认给1行
//    qDebug() << QString(u8"目前字数：%1").arg(length);
    int num1 = length / 18;//商
    int num2 = length % 18;//余数
//    qDebug() << QString(u8"18的倍数%1").arg(num1);
//    qDebug() << QString(u8"18的余数%1").arg(num2);
    if(num2 == 0)//整除
    {
        if(num1 != 0)
        {
            mulnum =  num1;
        }
        else
        {
            mulnum = 1;
        }
    }
    else//非整除
    {
        if(num1 != 0)
        {
           mulnum = num1+1;
        }
        else
        {
            mulnum = 1;
        }
    }
//    qDebug() <<QString(u8"最后求的真实的行数：%1").arg(mulnum);
    //单行20px 默认留出3行高度60px 标题28px 上下margin 6px 不知名10px
    int realHeight = 88;//default height
    if(mulnum > 2)
    {
        realHeight = 20*(mulnum-2)+88;
    }
    else
    {
        realHeight = 88;
    }
//    qDebug() <<QString(u8"最后求的真实的高度：%1").arg(realHeight);
    return realHeight;
}

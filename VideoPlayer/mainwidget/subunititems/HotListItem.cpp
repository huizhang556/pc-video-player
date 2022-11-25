#include "HotListItem.h"
#include "ui_HotListItem.h"

HotListItem::HotListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotListItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

HotListItem::HotListItem(const QString &num, const QString &picpath, const QString &maininfo, const QString &info, const QString &hotvalue, QWidget *parent):
    QWidget(parent),
    ui(new Ui::HotListItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    ui->pushButton_order->setText(num);
    ui->label_itemicon->setPixmap(QPixmap(picpath));
    ui->label_itemicon->setScaledContents(true);
    QString html1 = QString(R"(<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;
                            -qt-block-indent:0; text-indent:0px;"><span style=" font-family:'微软雅黑'; font-size:16px; color:#37d5ff;">%1</span><br/></p>)").arg(maininfo);
    QString html2 = QString(R"(<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;
                            -qt-block-indent:0; text-indent:0px;"><span style=" font-family:'微软雅黑'; font-size:14px; color:#616f71;">%1</span></p>)").arg(info);
    ui->textEdit_iteminfo->insertHtml(html1);
    ui->textEdit_iteminfo->insertHtml(html2);
    ui->pushButton_hotvalue->setText(hotvalue);
    ui->pushButton_hotvalue->setIcon(QIcon("://images/icon/hot0.png"));
}

HotListItem::~HotListItem()
{
    delete ui;
}

void HotListItem::initWorkUI()
{
    this->setMinimumSize(QSize(240,45));
    ui->stackedWidget_order->setCurrentIndex(0);
    ui->textEdit_iteminfo->setReadOnly(true);
    ui->textEdit_iteminfo->setAttribute(Qt::WA_TransparentForMouseEvents);//鼠标穿透, 设置后所有控件点击失效
    ui->textEdit_iteminfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit_iteminfo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void HotListItem::handleSignalsAndSlots()
{

}

void HotListItem::setInstallEventFilter()
{
    this->installEventFilter(this);
}

bool HotListItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->stackedWidget_order->setCurrentIndex(1);
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->stackedWidget_order->setCurrentIndex(0);
        }
    }
    return QWidget::eventFilter(watched,event);
}

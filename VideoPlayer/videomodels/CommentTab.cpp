#include "CommentTab.h"
#include "ui_CommentTab.h"
#include <QDebug>
#include <QPixmap>
#include <QDateTime>

CommentTab::CommentTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentTab)
{
    ui->setupUi(this);
    initWorkUI();
    chandleSignalsAndSLots();
}

CommentTab::~CommentTab()
{
    delete ui;
}

void CommentTab::initWorkUI()
{
    ui->textEdit_comment->setPlaceholderText(QString::fromLocal8Bit("美好的评论由你而生^_^"));
    ui->listWidget_comlist->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->pushButton_hotcomment->setFlat(true);
    ui->pushButton_hotcomment->setCheckable(true);
    ui->pushButton_newcomment->setFlat(true);
    ui->pushButton_newcomment->setCheckable(true);

    m_btnGroup = new QButtonGroup(this);
    m_btnGroup->setObjectName(QString::fromLocal8Bit("m_btnGroup"));
    m_btnGroup->setExclusive(true);//互斥
    m_btnGroup->addButton(ui->pushButton_hotcomment);
    m_btnGroup->addButton(ui->pushButton_newcomment);

    QIcon icon_publish(":/images/icon/clear.png");
    m_publishAction = new QAction(icon_publish,"");
    m_publishAction->setObjectName(QString::fromLocal8Bit("m_publishAction"));

//    for(int i = 0; i< 50; i++)
//    {
//        QListWidgetItem *item = new QListWidgetItem();
//        CommentForm *commentForm = new CommentForm(this);
//        commentForm->setUserNick(QString::fromLocal8Bit("伟大的评论家%1").arg(i+1));
//        commentForm->setCommentZanCount(i+1);
//        item->setSizeHint(QSize(commentForm->width(),commentForm->height()));
//        ui->listWidget_comlist->addItem(item);
//        ui->listWidget_comlist->setItemWidget(item,commentForm);
//    }
//    setLabelCommentCounts(ui->listWidget_comlist->count());
}

void CommentTab::chandleSignalsAndSLots()
{
    //上传图片
    connect(ui->pushButton_loadpic,&QPushButton::clicked,[=]()
    {
        qDebug() << "comment load pic";
    });
    //提交评论
    connect(ui->pushButton_publish,&QPushButton::clicked,[=]()
    {
        QPixmap             pix(":/images/icon/collect_title.png");
        pix = pix.scaled(40,40,Qt::KeepAspectRatio);
        QString nick        = QString::fromLocal8Bit("伟大的评论家");
        QString datetime    = QDateTime::currentDateTime().toString("yyyy-MM-dd");
        qDebug()            << "current time =" << datetime;
        QString comdata     = ui->textEdit_comment->toPlainText();
        qDebug()            << comdata;
        int count           = 1;
        if(!comdata.isEmpty())
        slot_insertNewCommentForm(pix,nick,datetime,comdata,count);
        qDebug() << "comment new publish";
    });
}

void CommentTab::setLabelCommentCounts(int count)
{
    ui->label_comment->setText(QString::fromLocal8Bit("全部评论（%1）").arg(count));
}

/*插入一个新的评论*/
void CommentTab::slot_insertNewCommentForm(QPixmap &pic, QString &nick, QString &date, QString &data, int count)
{
    QListWidgetItem *item = new QListWidgetItem();
    CommentForm *commentForm = new CommentForm(this);
    commentForm->setUserPicture(pic);//头像
    commentForm->setUserNick(nick);//昵称
    commentForm->setUserCommitDataTime(date);//时间
    commentForm->setUserCommentData(data);//内容
    commentForm->setCommentZanCount(count);//点赞
    item->setSizeHint(QSize(commentForm->width(),commentForm->height()));
//    ui->listWidget_comlist->addItem(item);
    ui->listWidget_comlist->insertItem(0,item);
    ui->listWidget_comlist->setItemWidget(item,commentForm);
    setLabelCommentCounts(ui->listWidget_comlist->count());//总评论数更新
}

bool CommentTab::eventFilter(QObject *watched, QEvent *event)
{

    return QWidget::eventFilter(watched,event);
}



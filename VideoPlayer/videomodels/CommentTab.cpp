#include "CommentTab.h"
#include "ui_CommentTab.h"


CommentTab::CommentTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentTab)
{
    ui->setupUi(this);
    initWorkUI();
}

CommentTab::~CommentTab()
{
    delete ui;
}

void CommentTab::initWorkUI()
{
    ui->pushButton_hotcomment->setFlat(true);
    ui->pushButton_hotcomment->setCheckable(true);
    ui->pushButton_newcomment->setFlat(true);
    ui->pushButton_newcomment->setCheckable(true);
    ui->lineEdit_comsearch->setPlaceholderText(QString::fromLocal8Bit("说两句吧..."));
    m_btnGroup = new QButtonGroup(this);
    m_btnGroup->setObjectName(QString::fromLocal8Bit("m_btnGroup"));
    m_btnGroup->setExclusive(true);//互斥
    m_btnGroup->addButton(ui->pushButton_hotcomment);
    m_btnGroup->addButton(ui->pushButton_newcomment);

    for(int i = 0; i< 20; i++)
    {
        QListWidgetItem *item = new QListWidgetItem(QString("this %1 comment").arg(i+1));
        CommentForm *commentForm = new CommentForm(this);
        commentForm->setUserNick(QString("this person %1").arg(i+1));
        commentForm->setCommentZanCount(i+1);
        item->setSizeHint(QSize(commentForm->width()-50,commentForm->height()));
        ui->listWidget_comlist->addItem(item);
        ui->listWidget_comlist->setItemWidget(item,commentForm);
    }
}

bool CommentTab::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_comsearch)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->lineEdit_comsearch->setMinimumHeight(70);
            update();
        }
    }
    return QWidget::eventFilter(watched,event);
}



#include "CommentForm.h"
#include "ui_CommentForm.h"

CommentForm::CommentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentForm)
{
    ui->setupUi(this);
    ui->pushButton_zan->setFlat(true);
    ui->pushButton_huifu->setFlat(true);
    ui->pushButton_more->setFlat(true);
}

CommentForm::~CommentForm()
{
    delete ui;
}

void CommentForm::setUserPicture(QPixmap pix)
{
    ui->label_touxiang->setPixmap(pix);
}

void CommentForm::setUserNick(QString nick)
{
    ui->label_name->setText(nick);
}

void CommentForm::setUserCommitDataTime(QString datatime)
{
    ui->label_datatime->setText(datatime);
}

void CommentForm::setCommentZanCount(int count)
{
    ui->pushButton_zan->setText(QString::number(count));
}

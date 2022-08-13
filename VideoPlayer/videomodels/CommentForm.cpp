#include "CommentForm.h"
#include "ui_CommentForm.h"
#include <QDebug>

CommentForm::CommentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentForm)
{
    ui->setupUi(this);
    this->setFixedHeight(150);
    ui->pushButton_zan->setFlat(true);
    ui->pushButton_huifu->setFlat(true);
    ui->pushButton_jubao->setFlat(true);
    chandleSignalsAndSLots();
}

CommentForm::~CommentForm()
{
    delete ui;
}

void CommentForm::chandleSignalsAndSLots()
{
    //点赞按钮
    connect(ui->pushButton_zan,&QPushButton::clicked,[=]()
    {
        qDebug() << "ZAN CLICKED!";
    });
    //回复按钮
    connect(ui->pushButton_huifu,&QPushButton::clicked,[=]()
    {
        qDebug() << "HUIFU CLICKED!";
    });
    //举报按钮
    connect(ui->pushButton_jubao,&QPushButton::clicked,[=]()
    {
        qDebug() << "JUBAO CLICKED!";
    });
}

void CommentForm::setUserPicture(QPixmap &pix)
{
    ui->label_touxiang->setPixmap(pix);
}

void CommentForm::setUserNick(QString &nick)
{
    ui->label_name->setText(nick);
}

void CommentForm::setUserCommitDataTime(QString &datatime)
{
    ui->label_datatime->setText(datatime);
}

void CommentForm::setUserCommentData(QString &data)
{
    ui->textBrowser->setText(data);
}

void CommentForm::setCommentZanCount(int count)
{
    ui->pushButton_zan->setText(QString::number(count));
}

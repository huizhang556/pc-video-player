#include "CommentForm.h"
#include "ui_CommentForm.h"
#include <QDebug>

CommentForm::CommentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentForm)
{
    ui->setupUi(this);
    this->setFixedHeight(150);
    initWorkUI();
    chandleSignalsAndSLots();
}

CommentForm::~CommentForm()
{
    delete ui;
}

void CommentForm::initWorkUI()
{
    ui->pushButton_zan->setFlat(true);
    ui->pushButton_zan->setCheckable(true);
    ui->pushButton_zan->setChecked(false);

    ui->pushButton_huifu->setFlat(true);
    ui->pushButton_jubao->setFlat(true);
    ui->textBrowser->setContextMenuPolicy(Qt::NoContextMenu);//禁止右键菜单
//    ui->pushButton_name->setLayoutDirection(Qt::RightToLeft);
    ui->pushButton_name->setFlat(true);
    ui->pushButton_name->setIcon(QIcon("://images/icon/comment_vip.png"));
    ui->pushButton_name->setIconSize(QSize(30,20));
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
    ui->pushButton_name->setText(nick);
}

void CommentForm::setUserCommitDataTime(QString &datatime)
{
    ui->label_datatime->setText(datatime);
}

void CommentForm::setUserCommentData(QString &data)
{
//    ui->textBrowser->setText(data);
    QString html = QString(R"(<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;
                            -qt-block-indent:0; text-indent:0px;"><span style=" font-family:'微软雅黑'; font-size:12px; color:#ffffff;">%1</span><br/></p>)").arg(data);
    ui->textBrowser->insertHtml(html);
}

void CommentForm::setCommentZanCount(int count)
{
//    ui->pushButton_zan->setText(QString::number(count));
}

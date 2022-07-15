#include "CusMessageBox.h"
#include "ui_CusMessageBox.h"

CusMessageBox::CusMessageBox(QWidget *parent) :
    QMessageBox(parent),
    ui(new Ui::CusMessageBox)
{
    ui->setupUi(this);
}

//自定义消息框
//参数：类型 标题 提示信息 勾选信息 按钮1文字 按钮2文字
CusMessageBox::CusMessageBox(int type, QString title,QString checktext, QString prompt, QString btntext2, QWidget *parent):
    QMessageBox(parent),
    ui(new Ui::CusMessageBox)
{
    ui->setupUi(this);
}


CusMessageBox::~CusMessageBox()
{
    delete ui;
}

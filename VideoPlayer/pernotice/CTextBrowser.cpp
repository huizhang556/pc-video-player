#include "CTextBrowser.h"
#include "ui_CTextBrowser.h"

CTextBrowser::CTextBrowser(QWidget *parent) :
    QTextBrowser(parent),
    ui(new Ui::CTextBrowser)
{
    ui->setupUi(this);
}

CTextBrowser::~CTextBrowser()
{
    delete ui;
}

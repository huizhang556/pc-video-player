#include "RankItem.h"
#include "ui_RankItem.h"

RankItem::RankItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RankItem)
{
    ui->setupUi(this);
}

RankItem::~RankItem()
{
    delete ui;
}

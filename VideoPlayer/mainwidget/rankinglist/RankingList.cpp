#include "RankingList.h"
#include "ui_RankingList.h"

RankingList::RankingList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RankingList)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

RankingList::~RankingList()
{
    delete ui;
}

void RankingList::initWorkUI()
{

}

void RankingList::handleSignalsAndSlots()
{

}

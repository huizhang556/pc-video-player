#include "SonglistSort.h"
#include "ui_SonglistSort.h"

SonglistSort::SonglistSort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SonglistSort)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

SonglistSort::~SonglistSort()
{
    delete ui;
}

void SonglistSort::initWorkUI()
{

}

void SonglistSort::handleSignalsAndSlots()
{

}

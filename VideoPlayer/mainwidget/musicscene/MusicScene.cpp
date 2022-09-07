#include "MusicScene.h"
#include "ui_MusicScene.h"

MusicScene::MusicScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicScene)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

MusicScene::~MusicScene()
{
    delete ui;
}

void MusicScene::initWorkUI()
{

}

void MusicScene::handleSignalsAndSlots()
{

}

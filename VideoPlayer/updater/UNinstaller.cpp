#include "UNinstaller.h"
#include "ui_UNinstaller.h"

UNinstaller::UNinstaller(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UNinstaller)
{
    ui->setupUi(this);
}

UNinstaller::~UNinstaller()
{
    delete ui;
}

#include "DesktopLyric.h"
#include "ui_DesktopLyric.h"

DesktopLyric::DesktopLyric(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesktopLyric)
{
    ui->setupUi(this);
}

DesktopLyric::~DesktopLyric()
{
    delete ui;
}

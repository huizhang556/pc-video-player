#include "TextImageLab.h"
#include "ui_TextImageLab.h"

TextImageLab::TextImageLab(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::TextImageLab)
{
    ui->setupUi(this);
    ui->label_text->setAlignment(Qt::AlignCenter);
}

TextImageLab::~TextImageLab()
{
    delete ui;
}

void TextImageLab::setLabWarnText(const QString &text)
{
    ui->label_text->setText(text);
}

void TextImageLab::clearLabWarnText()
{
    ui->label_text->clear();
}

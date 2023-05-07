#include "FontColor.h"
#include "ui_FontColor.h"
#include <QDebug>

FontColor* FontColor::m_pInstance = nullptr;

FontColor::FontColor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontColor)
{
    ui->setupUi(this);
    setFixedSize(180,70);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    initWorkUI();
    handleSinalsAndSlots();
}

FontColor::~FontColor()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void FontColor::initWorkUI()
{
    ui->horizontalSlider_font->setRange(10,40);
    ui->horizontalSlider_font->setValue(23);
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setExclusive(true);
    m_buttonGroup->addButton(ui->pushButton_localpic,0);
    m_buttonGroup->addButton(ui->pushButton_skin,1);
    m_buttonGroup->addButton(ui->pushButton_songer,2);

    m_buttonGroup_wave = new QButtonGroup(this);
    m_buttonGroup_wave->setExclusive(true);
    m_buttonGroup_wave->addButton(ui->pushButton_closewave,0);
    m_buttonGroup_wave->addButton(ui->pushButton_wave1,1);
    m_buttonGroup_wave->addButton(ui->pushButton_wave2,2);
    m_buttonGroup_wave->addButton(ui->pushButton_wave3,3);
}

void FontColor::handleSinalsAndSlots()
{
    connect(m_buttonGroup,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        if(button->text().isEmpty()) return;
        emit sig_send_switchskin(button->text());
    });

    connect(m_buttonGroup_wave,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        if(button->text().isEmpty()) return;
        emit sig_send_wave(button->text());
        if(button->text() == QString(u8"关闭频谱"))
        {
            button->setText(QString(u8"开启频谱"));
        }
        else if(button->text() == QString(u8"开启频谱"))
        {
            button->setText(QString(u8"关闭频谱"));
        }

    });

    //放大
    connect(ui->pushButton_fontIn,&QPushButton::clicked,[=](){
        int size = ui->horizontalSlider_font->value() + 3;
        if(size > ui->horizontalSlider_font->maximum())
            size = ui->horizontalSlider_font->maximum();
        emit sig_send_fontsize(size);
        ui->horizontalSlider_font->setValue(size);
    });
    //缩小
    connect(ui->pushButton_fontOut,&QPushButton::clicked,[=](){
        int size = ui->horizontalSlider_font->value() - 3;
        if(size < ui->horizontalSlider_font->minimum())
            size = ui->horizontalSlider_font->minimum();
        emit sig_send_fontsize(size);
        ui->horizontalSlider_font->setValue(size);
    });

    connect(ui->horizontalSlider_font,&QSlider::valueChanged,[=](int value){
        emit sig_send_fontsize(value);
    });

    connect(ui->pushButton_color1,&QPushButton::clicked,[=](){
        emit sig_send_fontcolor("255,0,0");
    });

    connect(ui->pushButton_color2,&QPushButton::clicked,[=](){
        emit sig_send_fontcolor("255,0,255");
    });

    connect(ui->pushButton_color3,&QPushButton::clicked,[=](){
        emit sig_send_fontcolor("85,255,127");
    });

    connect(ui->pushButton_color4,&QPushButton::clicked,[=](){
        emit sig_send_fontcolor("0,170,127");
    });

    connect(ui->pushButton_color5,&QPushButton::clicked,[=](){
        emit sig_send_fontcolor("0,255,255");
    });
}

void FontColor::setCurrentStackWdtIndex(const int index)
{
    ui->stackedWidget_switch->setCurrentIndex(index);
}

FontColor *FontColor::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new FontColor();
    }
    return m_pInstance;
}

void FontColor::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->close();
}

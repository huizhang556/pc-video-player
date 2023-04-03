#include "CusLabel.h"
#include "ui_CusLabel.h"

#include <QDebug>
#include <QScrollBar>
#include <QTextDocument>

CusLabel::CusLabel(QWidget *parent) :
    QLabel(parent),
    m_pos(0),
    m_font("Microsoft YaHei",23,75),
    ui(new Ui::CusLabel)
{
    ui->setupUi(this);
    initWorkUI();
    chandleSinalsAndSlots();
}

CusLabel::~CusLabel()
{
    delete ui;
}

void CusLabel::initWorkUI()
{
    m_timer = new QTimer(this);
    m_timer->start(1500);
    ui->plainTextEdit->setReadOnly(true);//只读模式
    ui->plainTextEdit->setContextMenuPolicy(Qt::NoContextMenu);//不弹出菜单
    ui->plainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->plainTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->plainTextEdit->setFont(m_font);
    ui->plainTextEdit->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));//设置字体居中显示
}

void CusLabel::chandleSinalsAndSlots()
{
    connect(m_timer,&QTimer::timeout,[=](){
        m_pos++;
        slot_setCurPosition(m_pos);
    });
}

void CusLabel::setCurrentTextFontSize(int size)
{
//    qDebug() << QString(u8"接收到的字体大小：")<<size;
    m_font.setPointSize(size);
    ui->plainTextEdit->setFont(m_font);
}

void CusLabel::setCurrentTextFontColor(const QString &color)
{
//    qDebug() << QString(u8"接收到的字体颜色：")<<color;
//    m_palette.setColor(QPalette::Text,m_color);
//    ui->plainTextEdit->setPalette(m_palette);
    //测试采用样式才会生效
    QString style = QString("#plainTextEdit{border:none;background-color: transparent;font-weight:800; color:rgb(%1);}").arg(color);
    ui->plainTextEdit->setStyleSheet(style);
}

void CusLabel::getCurPostionLyricText(int pos)
{
    QString lyric = ui->plainTextEdit->document()->findBlockByLineNumber(pos).text();
//    qDebug() << QString(u8"当前获取到的歌词：") << lyric;
    if(!lyric.isEmpty())
    {
        emit sig_curLyricText(ui->plainTextEdit->document()->findBlockByLineNumber(pos).text());
    }
}

void CusLabel::slot_setCurPosition(int pos)
{
//    m_textCursor.setPosition(pos);
//    ui->plainTextEdit->setTextCursor(m_textCursor);
    ui->plainTextEdit->verticalScrollBar()->setValue(pos);
//    int lineCount = ui->plainTextEdit->document()->lineCount();
//    qDebug() << QString::fromLocal8Bit("行数：")<< lineCount;
    if(m_pos == ui->plainTextEdit->verticalScrollBar()->maximum())
        m_pos = 0;
//        m_timer->stop();
    getCurPostionLyricText(pos);
}

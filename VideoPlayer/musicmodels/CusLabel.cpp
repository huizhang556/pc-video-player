#include "CusLabel.h"
#include "ui_CusLabel.h"

#include <QDebug>
#include <QScrollBar>
#include <QTextDocument>

CusLabel::CusLabel(QWidget *parent) :
    QLabel(parent),
    m_pos(0),
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
    ui->plainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->plainTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->plainTextEdit->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));//设置字体居中显示
}

void CusLabel::chandleSinalsAndSlots()
{
    connect(m_timer,&QTimer::timeout,[=](){
        m_pos++;
        slot_setCurPosition(m_pos);
    });
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
}

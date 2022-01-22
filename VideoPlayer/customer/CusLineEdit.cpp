#include "CusLineEdit.h"
#include <QMargins>
#include <QDebug>
#include <QRegExpValidator>
#include <QListWidget>
#include <QPoint>
#include <QCursor>

CusLineEdit::CusLineEdit(QWidget *parent) :
    QWidget(parent)
{
    widget = new QWidget(this);
    widget->setObjectName(QString::fromLocal8Bit("widget"));
    m_lineEdit = new QLineEdit(this);
    m_lineEdit->clearFocus();//清除焦点
    m_lineEdit->setObjectName(QString::fromLocal8Bit("m_lineEdit"));
    m_lineEdit->installEventFilter(this);
    m_button = new QPushButton(this);
    m_button->setObjectName(QString::fromLocal8Bit("m_button"));
    m_button->installEventFilter(this);

    //防止文本框输入内容位于按钮之下
    QMargins margins = m_lineEdit->textMargins();
    m_lineEdit->setTextMargins(margins.left(), margins.top(), m_button->width(), margins.bottom());

    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->addStretch();
    pSearchLayout->addWidget(m_button);
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0, 0, 0, 0);
    m_lineEdit->setLayout(pSearchLayout);
    vlayout = new QVBoxLayout(this);
    vlayout->addWidget(m_lineEdit);

    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setMargin(0);
    this->setLayout(vlayout);

    QRegExp rgex("^[\u4E00-\u9FA5A-Za-z0-9_]{0,50}$");//中文、英文、数字包括下划线,最长50字符
    this->setLineEditValidator(new QRegExpValidator(rgex,this));
    this->setSearchButtonText(QString::fromLocal8Bit("搜索"));
    this->setLineEditPlaceholderText(QString::fromLocal8Bit("请输入搜索内容"));
    this->setLineEditMinSize(QSize(800,36));
    this->setButtonMinSize(QSize(100,36));
    this->initHistoryUI();//初始化历史第记录UI

    connect(m_lineEdit,&QLineEdit::textChanged,[=](QString str)
    {
        slots_lineEditTextChange(str);
    });

    connect(m_lineEdit,&QLineEdit::textEdited,[=]()
    {
//        showLineEditHistory(true);
    });

}

CusLineEdit::~CusLineEdit()
{

}

void CusLineEdit::initHistoryUI()
{
    QFrame *frame1 = new QFrame(widget);
    //如何调整显示的高度
    QIcon icon1("");
    QPushButton *hisBtn = new QPushButton(icon1,QString::fromLocal8Bit("历史搜索"));
    QPushButton *clearBtn = new QPushButton(icon1,QString::fromLocal8Bit("清除"));
    QHBoxLayout *hblayout2 = new QHBoxLayout;
    QListWidget *listwidget = new QListWidget;

    QStringList slist;
    slist<<"1111111111"<<"2222222"<<"33333333"<<"33333333";
    listwidget->addItems(slist);
    hblayout2->addWidget(hisBtn);
    hblayout2->addStretch(200);
    hblayout2->addWidget(clearBtn);
    hblayout2->setSpacing(0);
    QVBoxLayout *vblayout2 = new QVBoxLayout;
    vblayout2->addLayout(hblayout2);
    vblayout2->addWidget(listwidget);
    vblayout2->setSpacing(0);
    frame1->setLayout(vblayout2);
    QHBoxLayout *hblayout3 = new QHBoxLayout;
    hblayout3->addWidget(frame1);
    hblayout3->setSpacing(0);
    hblayout3->setMargin(0);
    widget->setLayout(hblayout3);
    widget->resize(m_lineEdit->size()+m_button->size());
    QPoint point = QCursor::pos();
    widget->move(point);
    widget->show();

//    QFrame *frame2 = new QFrame(widget);
////    frame2->resize(m_lineEdit->size()+m_button->size());
//    QIcon icon2("");
//    QPushButton *hisBtn2 = new QPushButton(icon2,QString::fromLocal8Bit("历史搜索"));
//    QPushButton *clearBtn2 = new QPushButton(icon2,QString::fromLocal8Bit("清除"));
//    QHBoxLayout *hblayout3 = new QHBoxLayout;
//    QListWidget *listwidget2 = new QListWidget;
//    listwidget2->addItems(slist);
//    hblayout3->addWidget(hisBtn2);
//    hblayout3->addStretch(200);
//    hblayout3->addWidget(clearBtn2);
//    hblayout3->setSpacing(0);
//    QVBoxLayout *vblayout3 = new QVBoxLayout;
//    vblayout3->addLayout(hblayout3);
//    vblayout3->addWidget(listwidget2);
//    vblayout3->setSpacing(0);
//    frame2->setLayout(vblayout3);

//    QVBoxLayout *vblayout4 = new QVBoxLayout;
//    vblayout4->addWidget(frame1);
//    vblayout4->addWidget(frame2);
//    vblayout4->setSpacing(0);
//    vblayout4->setMargin(0);
//    widget->setLayout(vblayout4);
//    widget->resize(m_lineEdit->size()+m_button->size());
//    vlayout->addWidget(widget);
}

void CusLineEdit::setLineEditText(QString str)
{
    m_lineEdit->setText(str);
}

QString CusLineEdit::getLineEditText()
{
    return m_lineEdit->text();
}

void CusLineEdit::setFixSize(QSize size)
{
    this->setFixedSize(size);
}

void CusLineEdit::setLineEditSize(QSize size)
{
    m_lineEdit->setFixedSize(size);
}

void CusLineEdit::setLineEditMinSize(QSize size)
{
    m_lineEdit->setMinimumSize(size);
}

void CusLineEdit::setButtonSize(QSize size)
{
    m_button->setFixedSize(size);
}

void CusLineEdit::setButtonMinSize(QSize size)
{
    m_button->setMinimumSize(size);
}

void CusLineEdit::setSearchButtonText(QString str)
{
    m_button->setText(str);
}

void CusLineEdit::setSearchLineEditText(const QString text)
{
    m_lineEdit->setText(text);
}

void CusLineEdit::setSearchHidden(bool hide)
{
    m_button->setHidden(hide);
    m_button->setEnabled(hide);
}

void CusLineEdit::setLineEditHidden(bool hide)
{
    this->setHidden(hide);
}

void CusLineEdit::addLineEditAction(QIcon icon, QString str)
{
    QAction *action = new QAction(icon,str);
    m_lineEdit->addAction(action, QLineEdit::TrailingPosition);// 右侧显示
}

void CusLineEdit::setLineEditPlaceholderText(QString str)
{
    m_lineEdit->setPlaceholderText(str);
}

void CusLineEdit::setLineEditValidator(const QValidator *regx)
{
    m_lineEdit->setValidator(regx);
}

void CusLineEdit::lineEditClear()
{
    m_lineEdit->clear();

}



/*过滤事件*/
bool CusLineEdit::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_lineEdit)
    {
        if(event->type()==QEvent::FocusIn)
        {
            setHistoryUiHidden(false);
        }
        else if(event->type()==QEvent::FocusOut)
        {
            setHistoryUiHidden(true);
        }

    }
    return QWidget::eventFilter(watched,event);
}

void CusLineEdit::setHistoryUiHidden(bool hide)
{
    if(!hide)
    {
        widget->show();
    }
    else
    {
        widget->hide();
    }
}


QString CusLineEdit::slots_lineEditTextChange(const QString &str)
{
    qDebug()<<str;
    return str;
}

void CusLineEdit::setLineEditStyleSheet(const QString str)
{
    m_lineEdit->setStyleSheet(str);
}

void CusLineEdit::setButtonStyleSheet(const QString str)
{
    m_button->setStyleSheet(str);
}

//void CusLineEdit::showLineEditHistory(bool show)
//{
//    if(show)
//    {

//        QFrame *frame1 = new QFrame(widget);
//        frame1->resize(m_lineEdit->size()+m_button->size());
//        //如何调整显示的高度
//        QIcon icon1("");
//        QPushButton *hisBtn = new QPushButton(icon1,QString::fromLocal8Bit("历史搜索"));
//        QPushButton *clearBtn = new QPushButton(icon1,QString::fromLocal8Bit("清除"));
//        QHBoxLayout *hblayout2 = new QHBoxLayout;
//        QListWidget *listwidget = new QListWidget;

//        QStringList slist;
//        slist<<"1111111111"<<"2222222"<<"33333333"<<"33333333";
//        listwidget->addItems(slist);
//        hblayout2->addWidget(hisBtn);
//        hblayout2->addStretch(200);
//        hblayout2->addWidget(clearBtn);
//        hblayout2->setSpacing(0);
//        QVBoxLayout *vblayout2 = new QVBoxLayout;
//        vblayout2->addLayout(hblayout2);
//        vblayout2->addWidget(listwidget);
//        vblayout2->setSpacing(0);
//        frame1->setLayout(vblayout2);

//        QFrame *frame2 = new QFrame(widget);
//        frame2->resize(m_lineEdit->size()+m_button->size());
//        QIcon icon2("");
//        QPushButton *hisBtn2 = new QPushButton(icon2,QString::fromLocal8Bit("历史搜索"));
//        QPushButton *clearBtn2 = new QPushButton(icon2,QString::fromLocal8Bit("清除"));
//        QHBoxLayout *hblayout3 = new QHBoxLayout;
//        QListWidget *listwidget2 = new QListWidget;
//        listwidget2->addItems(slist);
//        hblayout3->addWidget(hisBtn2);
//        hblayout3->addStretch(200);
//        hblayout3->addWidget(clearBtn2);
//        hblayout3->setSpacing(0);
//        QVBoxLayout *vblayout3 = new QVBoxLayout;
//        vblayout3->addLayout(hblayout3);
//        vblayout3->addWidget(listwidget2);
//        vblayout3->setSpacing(0);
//        frame2->setLayout(vblayout3);

//        QVBoxLayout *vblayout4 = new QVBoxLayout;
//        vblayout4->addWidget(frame1);
//        vblayout4->addWidget(frame2);
//        vblayout4->setSpacing(0);
//        vblayout4->setMargin(0);
//        widget->setLayout(vblayout4);
//        widget->resize(m_lineEdit->size()+m_button->size());
//        vlayout->addWidget(widget);
////        widget->show();
////        qDebug()<<"widget is show!";
//    }
//    else
//    {
////        widget->setHidden(show);
//    }

//}

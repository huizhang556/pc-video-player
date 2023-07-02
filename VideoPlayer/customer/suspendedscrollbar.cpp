#include "suspendedscrollbar.h"
#include <QScrollBar>
#include <QFile>

SuspendedScrollBar::SuspendedScrollBar(Qt::Orientation t ,  QWidget *parent) :
    QScrollBar(parent)
{
    this->setOrientation(t);
    QString style_file = R"(QScrollBar{
                         border:none;
                         background:transparent;
                     }
                     QScrollBar:vertical
                     {
                         width:8px;
                         background:transparent;
                         margin:0px,0px,0px,0px;
                         padding-top:0px;
                         padding-bottom:0px;
                     }
                     QScrollBar::handle:vertical
                     {
                         width:8px;
                         background:rgba(0,0,0,10%);
                         border-radius:4px;
                         min-height:60;
                     }
                     QScrollBar::handle:vertical:hover
                     {
                         width:8px;
                         background:rgba(0,0,0,20%);
                         border-radius:4px;
                         min-height:60;
                     }
                     QScrollBar::add-line:vertical
                     {
                         height:0px;width:0px;
                         subcontrol-position:bottom;
                     }
                     QScrollBar::sub-line:vertical
                     {
                         height:0px;width:0px;
                         subcontrol-position:top;
                     }
                     QScrollBar::add-line:vertical:hover
                     {
                         height:0px;width:0px;
                         subcontrol-position:bottom;
                     }
                     QScrollBar::sub-line:vertical:hover
                     {
                         height:0px;width:0px;
                         subcontrol-position:top;
                     }
                     QScrollBar::sub-page:vertical{
                         background: none;
                     }
                     QScrollBar::add-page:vertical
                     {
                         background: none;
                     }
)";

//    QFile styleFile(style_file);//路径名
//    if(styleFile.open( QFile::ReadOnly )){
//        QString style( styleFile.readAll());
        this->setStyleSheet(style_file);
//    }

    this->setRange(0 , 0);
    this->hide();
}

void SuspendedScrollBar::slt_rangeChanged(int min,int max){
    this->setMinimum(min);
    this->setRange(0 , max);
    this->setPageStep(0.75 * (this->height() + max));
    if(max <= 0)
        this->hide();
}

void SuspendedScrollBar::slt_valueChange_scrollBar(int value){
    this->setValue(value);
}

SuspendedScrollBar_ListWidget::SuspendedScrollBar_ListWidget(QWidget * parent)
    : QListWidget(parent)
{
    this->setVerticalScrollMode(ScrollPerPixel);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_pVertScrollBar = new SuspendedScrollBar(Qt::Vertical,this);
    connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),m_pVertScrollBar,SLOT(slt_valueChange_scrollBar(int)));
    connect(m_pVertScrollBar,SIGNAL(valueChanged(int)),this,SLOT(slt_valueChange_widget(int)));
    connect(this->verticalScrollBar(),SIGNAL(rangeChanged(int,int)),m_pVertScrollBar,SLOT(slt_rangeChanged(int,int)));

}

void SuspendedScrollBar_ListWidget::slt_valueChange_widget(int value){
    this->verticalScrollBar()->setValue(value);
}

void SuspendedScrollBar_ListWidget::resizeEvent(QResizeEvent *e){
    int iX = this->width() - 8;
    m_pVertScrollBar->setGeometry(iX,1,8,this->height()-2);
    return QListWidget::resizeEvent(e);
}

void SuspendedScrollBar_ListWidget::enterEvent(QEvent * e){
    if(m_pVertScrollBar->maximum() > 0)
        m_pVertScrollBar->show();
    return QListWidget::enterEvent(e);
}
void SuspendedScrollBar_ListWidget::leaveEvent(QEvent * e){
    m_pVertScrollBar->hide();
    return QListWidget::leaveEvent(e);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
SuspendedScrollBar_Area::SuspendedScrollBar_Area(QWidget * parent)
    : QScrollArea(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_pVertScrollBar = new SuspendedScrollBar(Qt::Vertical , this);
    connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),m_pVertScrollBar,SLOT(slt_valueChange_scrollBar(int)));
    connect(m_pVertScrollBar,SIGNAL(valueChanged(int)),this,SLOT(slt_valueChange_widget(int)));
    connect(this->verticalScrollBar(),SIGNAL(rangeChanged(int,int)),m_pVertScrollBar,SLOT(slt_rangeChanged(int,int)));
}

void SuspendedScrollBar_Area::slt_valueChange_widget(int value){
    this->verticalScrollBar()->setValue(value);
}


void SuspendedScrollBar_Area::resizeEvent(QResizeEvent *e){
    int iX = this->width() - 8;
    m_pVertScrollBar->setGeometry(iX,1,8,this->height()-2);
    return QWidget::resizeEvent(e);
}

void SuspendedScrollBar_Area::enterEvent(QEvent * e){
    if(m_pVertScrollBar->maximum() > 0)
        m_pVertScrollBar->show();
    return QWidget::enterEvent(e);
}
void SuspendedScrollBar_Area::leaveEvent(QEvent * e){
    m_pVertScrollBar->hide();
    return QWidget::leaveEvent(e);
}

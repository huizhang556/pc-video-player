#include "SwitchStackWgt.h"
#include "ui_SwitchStackWgt.h"
#include "global/Global.h"

SwitchStackWgt::SwitchStackWgt(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::SwitchStackWgt)
{
    ui->setupUi(this);
    setMinimumSize(MINWINSIZE);
    resize(RESIZESIZE);
    initWorkUI();
    handleSignalsAndSlots();
}

SwitchStackWgt::~SwitchStackWgt()
{
    delete ui;
}

void SwitchStackWgt::initWorkUI()
{
    this->installEventFilter(this);

//    for(int i = 0; i < 6; i++)
//    {
//        QString path = Global::appDirPath + QString("/pictures/stackwall/stack%1.png").arg(i);
//        this->slot_addToStackItemPicture(path);
//    }

    m_switchButton = new SwitchButtons(this);
    m_switchButton->setFixedHeight(40);
    m_switchButton->setObjectName(QString::fromLocal8Bit("m_switchButton"));
}

void SwitchStackWgt::handleSignalsAndSlots()
{
    //每次currentChanged改变都要更新一下，否则会被隐藏(无用)
    connect(this,&SwitchStackWgt::currentChanged,[=](int index){
//        m_switchButton->slot_setUNCheckedButton(index);
    });

    connect(m_switchButton,&SwitchButtons::sig_sendButtonNumber,[=](int num){
        this->setCurrentIndex(num);
        resizeSwitchButtonSize();//必须要更新
//        qDebug() << QString(u8"当前第%1页").arg(num);
    });


}

void SwitchStackWgt::slot_addToStackItemPicture(const QString &list_pic)
{
    //添加图片
    QLabel *label_pic = new QLabel(this);//此处需用指针，临时对象不行
    label_pic->setPixmap(QPixmap(list_pic));
    label_pic->setScaledContents(true);
    this->insertWidget(this->count(),label_pic);
}

void SwitchStackWgt::slot_addToStackItemPictures(const QStringList &list_pic)
{
    for(int i = 0; i < list_pic.count(); i++)
    {
        //添加图片
        QLabel *label_pic = new QLabel(this);//此处需用指针，临时对象不行
        label_pic->setPixmap(QPixmap(list_pic.at(i)));
        label_pic->setScaledContents(true);
        this->insertWidget(this->count(),label_pic);
    }
}

bool SwitchStackWgt::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Resize)
        {
            update_W_H_scale();
            resizeSwitchButtonSize();
//            qDebug() << QString(u8"选择stackwgt界面resize");
        }
    }
    return QWidget::eventFilter(watched,event);
}

void SwitchStackWgt::resizeSwitchButtonSize()
{
    m_switchButton->setGeometry(width()/2 - m_switchButton->width()/2,
                                height() - m_switchButton->height() - 0,
                                m_switchButton->width(),m_switchButton->height());
    m_switchButton->raise();//非常重要，否则显示不了
}

void SwitchStackWgt::update_W_H_scale()
{
    //图片标准大小（1920,670）
    if(this->width() > SACLWIDTH)
    {
        this->setMinimumHeight((int)(this->width()*SCALSIZE));
    }
    else
    {
        this->setMinimumHeight(FIXEDHEIGHT);
    }
}

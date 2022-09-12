#include "TagsItem.h"
#include "ui_TagsItem.h"

#include <QDebug>

TagsItem::TagsItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsItem)
{
    ui->setupUi(this);
    setMinimumSize(186,218);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

TagsItem::TagsItem(const QString &picture, const QString &name, const QString &counts, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsItem)
{
    ui->setupUi(this);
    setMinimumSize(186,218);
    initWorkUI();
    slot_setHeadPicture(picture);
    slot_setSongerTages(name);
    slot_setSongerMark(counts);
    handleSignalsAndSlots();
    setInstallEventFilter();
}

TagsItem::~TagsItem()
{
    delete ui;
}

void TagsItem::initWorkUI()
{

    m_tagBtn = new QPushButton(ui->label_head);
    m_tagBtn->setFixedSize(40,30);
    m_tagBtn->setObjectName(QString::fromLocal8Bit("m_tagBtn"));

    m_countBtn = new QPushButton(QIcon("://images/icon/recvideo_amount.png"), QString::fromLocal8Bit("累计播放6.6万"),ui->label_head);
    m_countBtn->setFixedSize(120,24);
//    m_countBtn->setLayoutDirection(Qt::RightToLeft);
    m_countBtn->setHidden(true);
    m_countBtn->setObjectName(QString::fromLocal8Bit("m_tagsCountBtn"));

    m_playBtn = new QPushButton(ui->label_head);
    m_playBtn->setFixedSize(36,36);
    m_playBtn->setHidden(true);
    m_playBtn->setObjectName(QString::fromLocal8Bit("m_tagsPlayBtn"));
}

void TagsItem::handleSignalsAndSlots()
{
//    connect(HoverMask::getInstance(),&HoverMask::sig_sendLeave,[=](){setMask(false);});
    connect(ui->pushButton_tags,&QPushButton::clicked,[=](){  emit sig_sendMarkItem(); });
    connect(ui->pushButton_mark,&QPushButton::clicked,[=](){  emit sig_sendMarkItem(); });
    connect(m_playBtn,&QPushButton::clicked,[=](){ emit sig_sendMarkItem(); });
}

void TagsItem::setInstallEventFilter()
{
    this->installEventFilter(this);
    ui->label_head->installEventFilter(this);
    ui->pushButton_tags->installEventFilter(this);
    ui->pushButton_mark->installEventFilter(this);
}

void TagsItem::slot_setHeadPicture(const QString &path)
{
    if(path.isEmpty()) return;
    QPixmap pix(path);
    ui->label_head->setPixmap(pix);
    ui->label_head->setScaledContents(true);
}

void TagsItem::slot_setSongerTages(const QString &name)
{
    ui->pushButton_tags->setText(name);
}

void TagsItem::slot_setSongerMark(const QString &counts)
{
    ui->pushButton_mark->setText(counts);
}

bool TagsItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label_head)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            emit sig_sendMarkItem();
        }
        else if(event->type() == QEvent::Enter)
        {
            m_countBtn->move(0,ui->label_head->height()-30);
            m_countBtn->show();
            m_playBtn->move(ui->label_head->width()-40,ui->label_head->height()-40);
            m_playBtn->show();
//            setHeadMask(true);
        }
        else if(event->type() == QEvent::Leave)
        {
            m_countBtn->hide();
            m_playBtn->hide();
//            setHeadMask(false);
        }

    }

    return QWidget::eventFilter(watched,event);
}

void TagsItem::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
//    setHeadPictureMskRegion();
}

void TagsItem::setHeadPictureMskRegion()
{
    int radius = qMin(ui->label_head->width(),ui->label_head->height());
//    ui->label_head->move((ui->label_head->width()-radius + 8)/2,(ui->label_head->height()-radius + 28)/2);
    ui->label_head->resize(QSize(radius,radius));
//    QRegion maskRegion(ui->label_head->rect(),QRegion::Ellipse);//创建圆形遮罩
    //    ui->label_head->setMask(maskRegion);//设置圆形遮罩
}

void TagsItem::setHeadMask(bool mask)
{
    if(mask)
    {
//        QPainterPath path;
//        path.addRoundedRect(ui->label_head->rect(), 1.0f, 1.0f, Qt::AbsoluteSize);
//        QRegion maskRegion = QRegion(path.toFillPolygon().toPolygon());
//        ui->label_head->setMask(maskRegion);//设置遮罩
//        int x = ui->label_head->mapToGlobal(ui->label_head->pos()).x();
//        int y = ui->label_head->mapToGlobal(ui->label_head->pos()).y();
//        HoverMask::getInstance()->setGeometry(x-5,y-5,ui->label_head->width(),ui->label_head->height());
//        HoverMask::getInstance()->setAttribute(Qt::WA_TransparentForMouseEvents,true);
//        HoverMask::getInstance()->show();
//        qDebug() <<QString::fromLocal8Bit("遮罩显示");
    }
    else
    {
//        ui->label_head->clearMask();
//        if(!HoverMask::getInstance()->isHidden())
//        HoverMask::getInstance()->hide();
//        qDebug() <<QString::fromLocal8Bit("遮罩隐藏");
    }
}

#include "TagsItem.h"
#include "ui_TagsItem.h"

TagsItem::TagsItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsItem)
{
    ui->setupUi(this);
    setMinimumSize(186,218);
    handleSignalsAndSlots();
    setInstallEventFilter();
}

TagsItem::TagsItem(const QString &picture, const QString &name, const QString &counts, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsItem)
{
    ui->setupUi(this);
    setMinimumSize(186,218);
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

void TagsItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_tags,&QPushButton::clicked,[=](){  emit sig_sendMarkItem(); });
    connect(ui->pushButton_mark,&QPushButton::clicked,[=](){  emit sig_sendMarkItem(); });
}

void TagsItem::setInstallEventFilter()
{
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

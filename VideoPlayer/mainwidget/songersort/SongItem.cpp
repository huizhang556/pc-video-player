#include "SongItem.h"
#include "ui_SongItem.h"


#include <QRegion>

SongItem::SongItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SongItem)
{
    ui->setupUi(this);
    setFixedSize(162,214);
    QRegion maskRegion(ui->label_songhead->rect(),QRegion::Ellipse);//创建圆形遮罩
    ui->label_songhead->setMask(maskRegion);//设置圆形遮罩
    setInstallEventFilter();
    handleSignalsAndSlots();
}

SongItem::SongItem(const QString &picture, const QString &name, const QString &counts, int alignFlag, QWidget *parent) :
    QWidget(parent),
    m_path(picture),
    m_name(name),
    m_counts(counts),
    ui(new Ui::SongItem)
{
    ui->setupUi(this);
    setFixedSize(162,214);
    slot_setHeadPicture(picture);
    slot_setSongerName(name);
    slot_setSongerCounts(counts);
    slot_setAlignText(alignFlag);
    setInstallEventFilter();
    handleSignalsAndSlots();
    QRegion maskRegion(ui->label_songhead->rect(),QRegion::Ellipse);//创建圆形遮罩
    ui->label_songhead->setMask(maskRegion);//设置圆形遮罩
}

SongItem::~SongItem()
{
    delete ui;
}

void SongItem::setInstallEventFilter()
{
    ui->label_songhead->installEventFilter(this);
    ui->pushButton_name->installEventFilter(this);
    ui->pushButton_counts->installEventFilter(this);
}

void SongItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_name,&QPushButton::clicked,[=](){  emit sig_sendSonger(m_name); });
    connect(ui->pushButton_counts,&QPushButton::clicked,[=](){  emit sig_sendSonger(m_name); });
}

void SongItem::slot_setHeadPicture(const QString &path)
{
    if(path.isEmpty()) return;
    QPixmap pix(path);
    ui->label_songhead->setPixmap(pix);
    ui->label_songhead->setScaledContents(true);
}

void SongItem::slot_setSongerName(const QString &name)
{
    ui->pushButton_name->setText(name);
}

void SongItem::slot_setSongerCounts(const QString &counts)
{
    ui->pushButton_counts->setText(QString::fromLocal8Bit("%1首歌曲").arg(counts));
}

void SongItem::slot_setAlignText(int index)
{
    if(index == 0)
    {

    }
    else if(index == 1)
    {

    }
    else
    {

    }
}

bool SongItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label_songhead)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            emit sig_sendSonger(m_name);
        }
    }
    return QWidget::eventFilter(watched,event);
}

void SongItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
//    int w = ui->label_songhead->width();
//    int h = ui->label_songhead->height();

//    QPixmap pixmapa(":/images/bgpic/dieji2.png");
//    QPixmap pixmap(w,h);
//    pixmap.fill(Qt::transparent);
//    QPainter painter(&pixmap);
//    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//    QPainterPath path;
//    path.addEllipse(0, 0, w, h);    //绘制椭圆
//    painter.setClipPath(path);
//    painter.drawPixmap(0, 0, w, h, pixmapa);

//#if 1
//    // 绘制自定义形状的窗口
//    QBitmap bitMap(this->width(),this->height()); // 定义一个窗口大小的位图
//    bitMap.fill();                                // 填充整个位图
//    QPainter painter(&bitMap);                    // 定义绘图设备
//    painter.setBrush(Qt::black);                  // 必须定义为黑色,不知道为啥,知道的麻烦在评论区说一下
//    painter.setPen(Qt::NoPen);                    // 只能为黑色或者不设置画笔
//    painter.setRenderHint(QPainter::Antialiasing);// 反走样
////    painter.drawRoundedRect(bitMap.rect(),30,30); // 绘制圆角矩形
////    painter.drawEllipse(bitMap.rect());           // 绘制椭圆
//    QPainterPath path;
//    path.moveTo(0,0);
//    path.lineTo(bitMap.width(),0);
//    path.lineTo(bitMap.width()/2,bitMap.height());
//    path.lineTo(0,0);
//    painter.drawPath(path);                         // 绘制三角形
//    setMask(bitMap);                              // 将圆角作为遮罩
//#else
//    // 绘制图片形状的窗口切使用图片
//    QPixmap pixmap(":/jidelogo.png");
//    QPalette palette;
//    palette.setBrush(QPalette::Background, QBrush(pixmap));
//    setPalette(palette);
//    resize(pixmap.size());
//    setMask(pixmap.mask());

//#endif

}

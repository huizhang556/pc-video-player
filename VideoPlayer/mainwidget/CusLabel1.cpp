#include "CusLabel1.h"
#include "ui_CusLabel1.h"

CusLabel1::CusLabel1(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::CusLabel1)
{
    ui->setupUi(this);
    installEventFilter(this);
    initWorkUI();
    handleSignalsAndSlots();
}

CusLabel1::CusLabel1(const QString &picpath, const QColor &bgcolor, const int radius, const bool collect_on, QWidget *parent):
    QLabel(parent),
    m_picPath(picpath),
    m_bgColor(bgcolor),
    m_radius(radius),
    m_collect(collect_on),
    ui(new Ui::CusLabel1)
{
    ui->setupUi(this);
    installEventFilter(this);
    initWorkUI();
    handleSignalsAndSlots();
}


CusLabel1::~CusLabel1()
{
    delete ui;
}

void CusLabel1::initWorkUI()
{
//    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);
    ui->pushButton_itemCollect->setCheckable(true);
    setItemColStatus(m_collect);
}

void CusLabel1::handleSignalsAndSlots()
{
    connect(ui->pushButton_itemCollect,&QPushButton::clicked,[=](){
        if(m_collect)
        {
            ui->pushButton_itemCollect->setChecked(false);
        }
        else
        {
            ui->pushButton_itemCollect->setChecked(true);
        }
        m_collect = !m_collect;
        emit sig_item_collect(m_collect);
    });
}

void CusLabel1::setItemPicture(const QString &path)
{
    m_picPath = path;
}

void CusLabel1::setItemBGColor(const QColor &color)
{
    m_bgColor = color;
}

void CusLabel1::setItemColStatus(const bool &on)
{
    if(on)
        ui->pushButton_itemCollect->setChecked(true);
    else
        ui->pushButton_itemCollect->setChecked(false);
}

bool CusLabel1::eventFilter(QObject *watched, QEvent *event)
{

    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            emit sig_item_enter();
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            emit sig_item_click();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void CusLabel1::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::transparent);
    QPixmap pixmap(m_picPath);
//    pixmap.setMask(QBitmap(pixmap.mask()));

    QPainterPath drawPath;
    drawPath.addRoundedRect(this->rect(),m_radius,m_radius);//添加 一个圆角矩形的绘制路线区域
//    drawPath.addRect(this->rect());
    //如果不绘制图片（其上面叠加的部分会被覆盖），通过setPixmap添加的图片，圆角失效，只能重绘（但是通过样式设置的图片是圆角生效的）
    painter.drawPixmap(0,0,width(),height(),pixmap);
    painter.fillPath(drawPath,QBrush(Qt::transparent));

    //绘制一个多边形（椭圆）区域，且区域内透明（不被遮盖），区域外被遮盖
//    QRegion maskedRegion(0, 0, width(),height(), QRegion::Ellipse);
    QPolygon maskedRegion = drawPath.toFillPolygon().toPolygon();
     setMask(maskedRegion);

//    QRegion region(polygon);//指定一个裁剪区域
//    this->setMask(region);// 设置蒙版遮罩
//    painter.setClipRegion(region);
}


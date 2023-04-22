#include "Danmu.h"
#include "ui_Danmu.h"

Danmu::Danmu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Danmu)
{
    ui->setupUi(this);
}

Danmu::Danmu(QWidget *parent, QString text, ColorType color, int type, QRect rect, QFont danmuFont, double Transparency, int runTime):
    QWidget(parent),
    ui(new Ui::Danmu)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
//    SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    //设置弹幕为无窗口无工具栏且呆在窗口顶端,但是会导致坐标错乱，尤其是丢掉了标题栏
//    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
    DText = text;
    this->setType(type);        //设置类型
    this->setQFont(danmuFont);      //弹幕字体
    this->setTransparency(Transparency);        //弹幕透明度
    this->setRunTime(runTime);
    this->setScreenRect(rect);//这里设置只是为了获取矩形用，无实质作用
    QFontMetrics metrics(this->getQFont());
    QPalette palll = this->palette();

    anim2 = NULL;

    //颜色字符串转化为特定的颜色
    switch (color)
    {
    case ColorType::VIPBlue:
    {
        palll.setColor(QPalette::WindowText,QColor(12, 134, 141,255));
        this->setQColor(QColor(12, 134, 141,255));
    }
        break;
    case ColorType::VIPGolden:
    {
        palll.setColor(QPalette::WindowText,QColor(250, 216, 142,255));
        this->setQColor(QColor(250, 216, 142,255));
    }
        break;
    case ColorType::VIPPink:
    {
        palll.setColor(QPalette::WindowText,QColor(255, 7, 143,255));
        this->setQColor(QColor(255, 7, 143,255));
    }
        break;
    case ColorType::NVIPDefault:
    {
        palll.setColor(QPalette::WindowText,QColor(12, 134, 141,255));
        this->setQColor(QColor(12, 134, 141,255));
    }
        break;
    case ColorType::NVIPGreen:
    {
        palll.setColor(QPalette::WindowText,QColor(7, 180, 130,255));
        this->setQColor(QColor(7, 180, 130,255));
    }
        break;
    case ColorType::NVIPBlue:
    {
        palll.setColor(QPalette::WindowText,QColor(32, 139, 213,255));
        this->setQColor(QColor(32, 139, 213,255));
    }
        break;
    case ColorType::NVIPOrange:
    {
        palll.setColor(QPalette::WindowText,QColor(210, 115, 52,255));
        this->setQColor(QColor(210, 115, 52,255));
    }
        break;
    case ColorType::NVIPRed:
    {
        palll.setColor(QPalette::WindowText,QColor(202, 35, 79,255));
        this->setQColor(QColor(202, 35, 79,255));
    }
        break;
    case ColorType::NVIPViolet:
    {
        palll.setColor(QPalette::WindowText,QColor(157, 117, 202,255));
        this->setQColor(QColor(157, 117, 202,255));
    }
        break;
    default:
    {
        palll.setColor(QPalette::WindowText,QColor(255,255,246,255));
        this->setQColor(QColor(255,255,246,255));
    }
        break;
    }

    //弹幕的屏幕坐标全部都是绝对坐标（相对于桌面坐标而言），传进来的rect变量就是绝对坐标
    this->setFixedHeight(metrics.height()+5);
    this->setFixedWidth(metrics.width(DText)+4);

    palll.setColor(QPalette::Background, QColor(0,0,0));
    palll.setBrush(this->backgroundRole(), QBrush(QColor(0,0,0)));
    this->setPalette(palll);//设置调色盘（主要设置WindowText字体颜色）

    int yy = qrand()%(rect.height());//在这里使用了矩形这个变量的范围
    qDebug() << QString(u8"随机的起始高度+60：") << yy;//外部传进来的矩形已经处理过高度（这个高度是加上标题栏的高度）
    int y = yy<(rect.height()-metrics.height()-5)?(yy):(rect.height()-metrics.height()-5);//随机值小于窗口高度-字体像素高度则真
    if(y < rect.y())
    {
        y = rect.y()+80 + metrics.height()+5;//显示在标题栏以下
    }
    else if(y > rect.y() + rect.height())
    {
        y = rect.y() + rect.height() - metrics.height()-5 - 90;//最底部减去文字高度,减去控制栏高度
    }

    qDebug() << QString(u8"显示的屏幕高度：") << rect.height() << QString(u8"计算后确定的起始高度：") << y;
//    int xx = rect.width()+qrand()%500;
//    int xx = rect.x() + rect.width() - metrics.width(DText);//实际上不应留出文字的长度，直接所有的文字都是从最右侧边缘出现
    int xx = rect.x() + rect.width();
    qDebug() << QString(u8"计算后确定的起始横坐标：") << xx;
    this->move(xx,y);
    this->setPosX(xx);//设置弹幕水平的位置（动画用）
    this->setPosY(y);//设置弹幕垂直位置（动画用）

    this->installEventFilter(this);
    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::NoFocus);
    this->hide();
    anim2 = new QPropertyAnimation(this, "pos");
    anim2->setDuration(this->getRunTime());
    //每个弹幕的开始位置都是随机的（主要是高度不一致，x都是一致的）
    //依赖动画，使x值变小（动画往最左侧移动），y值不变
    anim2->setStartValue(QPoint(this->getPosX(),this->getPosY()));
    anim2->setEndValue(QPoint(rect.x(), this->getPosY()));
    qDebug() <<QString(u8"传进来的rect")<< rect<< QString(u8"结束位置：")<< rect.x()<<","<<getPosY();
    anim2->setEasingCurve(QEasingCurve::Linear);//线型变化
    this->setWindowOpacity(this->getTransparency());
    this->show();
    this->repaint();//绘制一次，绘制出文字
    anim2->start();
    connect(anim2,SIGNAL(finished()),this,SLOT(deleteLater()));//动画结束，this本身自动析构
}

Danmu::~Danmu()
{
    delete ui;
    qDebug()<<QString(u8"弹幕被析构")<<endl;
}

void Danmu::paintEvent(QPaintEvent *)
{  //弹幕字体绘制函数
        QPainter painter(this);//以弹幕窗口为画布
//        painter.setCompositionMode(QPainter::CompositionMode_Clear);
//        painter.eraseRect(this->rect());
        painter.save();
        QFontMetrics metrics(this->getQFont());     //获取弹幕字体
        QPainterPath path;      //描绘路径用
        QPen pen(QColor(0, 0, 0, 233));       //自定义画笔的样式，让文字周围有边框
        painter.setRenderHint(QPainter::Antialiasing);
        int penwidth = 4;
        pen.setWidth(penwidth);
        int len = metrics.width(DText);
        int w = this->width();
        int px = (len - w) / 2;
        if(px < 0)
        {
            px = -px;
        }
        int py = (height() - metrics.height()) / 2 + metrics.ascent();
        if(py < 0)
        {
            py = -py;
        }
        path.addText(px+2,py+2,this->getQFont(),DText);//画字体轮廓
        painter.strokePath(path, pen);//给字描边
        painter.drawPath(path);//绘制描边颜色
        painter.fillPath(path,QBrush(this->getQColor()));//用画刷填充字体中间颜色
        painter.restore();

}

bool Danmu::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && checkOpen == false)
        if(event->type() == QEvent::Enter)
        {
            anim2->pause();
        }
    else if(event->type() == QEvent::Leave)
        {
            anim2->resume();
        }
    return QWidget::eventFilter(watched,event);
}

void Danmu::setScreenRect(QRect screenRect)
{
    this->screenrect = screenRect;
}

QRect Danmu::getScreenRect()
{
    return this->screenrect;
}

int Danmu::getPosX()
{
    return PosX;
}

int Danmu::getPosY()
{
    return PosY;
}

void Danmu::setPosX(int posx)
{
    this->PosX = posx;
}

void Danmu::setPosY(int posy)
{
    this->PosY = posy;
}

QString Danmu::getColor()
{
    return color;
}

int Danmu::getType()
{
    return type;
}

void Danmu::setColor(QString color)
{
    this->color = color;
}

void Danmu::setType(int type)
{
    this->type = type;
}

QColor Danmu::getQColor()
{
    return qcolor;
}

void Danmu::setQColor(QColor qcolor)
{
    this->qcolor = qcolor;
}

QFont Danmu::getQFont()
{
    return danmuFont;
}

void Danmu::setQFont(QFont danmuFont)
{
    this->danmuFont = danmuFont;
}

void Danmu::setTransparency(double Transparency)
{
    this->Transparency = Transparency;
}

double Danmu::getTransparency()
{
    return Transparency;
}

void Danmu::setRunTime(int runTime)
{
    this->runTime = runTime;
}

int Danmu::getRunTime()
{
    return this->runTime;
}

QPropertyAnimation * Danmu::getanimation()
{
    return anim2;
}

void Danmu::release()
{
//    this->hide();
    this->close();
}

void Danmu::anim_ctl(bool open)
{
    if(!open)
    {
        anim2->resume();
        checkOpen = false;
    }
    else
    {
        anim2->pause();
        checkOpen = true;
    }

}

void Danmu::remove(bool open)
{
    if(open)
    {
        this->show();
    }
    else
    {
        this->hide();
    }
}

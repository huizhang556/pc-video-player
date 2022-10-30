#include "CusLabel2.h"
#include "ui_CusLabel2.h"

CusLabel2::CusLabel2(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::CusLabel2)
{
    ui->setupUi(this);
    installEventFilter(this);
    initWorkUI();
    handleSignalsAndSlots();
}

CusLabel2::CusLabel2(const QString &picpath, const QString &mainPic, const QString &topRightMark, const QString &playCounts, const bool play_on, QWidget *parent):
    QLabel(parent),
    m_playOn(play_on),
    m_picPath(picpath),
    ui(new Ui::CusLabel2)
{
    ui->setupUi(this);
    installEventFilter(this);
    initWorkUI();
    handleSignalsAndSlots();
    this->setPixmap(QPixmap(mainPic));
    this->setScaledContents(true);
    ui->pushButton_rightMark->setIcon(QIcon(topRightMark));
    ui->pushButton_playcounts->setText(playCounts);
}

CusLabel2::~CusLabel2()
{
    delete ui;
}

void CusLabel2::initWorkUI()
{
    ui->pushButton_play->hide();
}

void CusLabel2::handleSignalsAndSlots()
{
    connect(ui->pushButton_play,&QPushButton::clicked,[=](){
        emit sig_buttonClicked();
    });
}

void CusLabel2::setItemPicture(const QString& path)
{
    m_picPath = path;
}

void CusLabel2::setItemBGColor(const QColor &color)
{
    m_bgColor = color;
}

bool CusLabel2::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->pushButton_play->show();
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->pushButton_play->hide();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void CusLabel2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(14, 27, 44,10));//rgba 背景色一致

        QPainterPath drawPath;
        drawPath.addRoundedRect(this->rect(),8,8);
        drawPath.addRect(this->rect());
        //如果不绘制图片（其上面叠加的部分会被覆盖），通过setPixmap添加的图片，圆角失效，只能重绘（但是通过样式设置的图片是圆角生效的）
        painter.drawPixmap(0,0,width(),height(),QPixmap(m_picPath));
        painter.fillPath(drawPath,QBrush(QColor(14, 27, 44)));
}

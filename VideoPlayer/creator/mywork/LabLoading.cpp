#include "LabLoading.h"

LabLoading::LabLoading(QWidget *parent):
    QLabel(parent)
{
    BgColor = QColor(255,255,255,0);
    BarColor = QColor(Qt::red);
    TextColor = QColor(Qt::black);
    BarColor.setAlpha(50);
    rColor.resize(5);
    for (int i = 0; i < 5; i++) {
        rColor[i] = QColor(BarColor);
        rColor[i].setAlpha(100 + i * 20);
    }
    startAngle = 45;
    ProgressNum = 0;
    ProgressRun = false;
    timerrun = new QTimer(this);
    connect(timerrun, SIGNAL(timeout()), this, SLOT(prorun()));
    timerrun->setInterval(100);
}

LabLoading::~LabLoading()
{

}

void LabLoading::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    drawBg(&painter);
    drawBar(&painter);
//    drawText(&painter);
}

//绘制背景
void LabLoading::drawBg(QPainter *painter)
{
    int radius = 50;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(BgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

//绘制进度条
void LabLoading::drawBar(QPainter *painter)
{
    int radius = 95;
    painter->save();
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(10.0);
    painter->setBrush(Qt::NoBrush);
    if (ProgressRun == false)//stop
    {
        for (int i = 0; i < 8; i++)
        {
            pen.setColor(Qt::transparent);
            painter->setPen(pen);
            float x = qCos(double(startAngle + 45 * i) * M_PI / 180) * radius;
            float y = qSin(double(startAngle + 45 * i) * M_PI / 180) * radius;
            float x1 = qCos(double(startAngle + 45 * i) * M_PI / 180) * 50;
            float y1 = qSin(double(startAngle + 45 * i) * M_PI / 180) * 50;
            QLineF line(x1, y1, x, y);
            painter->drawLine(line);
        }
    }
    else//start
    {
        for (int i = 0; i < 5; i++) {
            pen.setColor(rColor[i]);
            painter->setPen(pen);
            float x = qCos(double(startAngle + 45 * i) * M_PI / 180) * radius;
            float y = qSin(double(startAngle + 45 * i) * M_PI / 180) * radius;
            float x1 = qCos(double(startAngle + 45 * i) * M_PI / 180) * 60;
            float y1 = qSin(double(startAngle + 45 * i) * M_PI / 180) * 60;
            QLineF line(x1, y1, x, y);
            painter->drawLine(line);
        }
        for (int i = 0; i < 3; i++) {
            pen.setColor(BarColor);
            painter->setPen(pen);
            float x = qCos(double(startAngle + 45 * (i + 5)) * M_PI / 180) * radius;
            float y = qSin(double(startAngle + 45 * (i + 5)) * M_PI / 180) * radius;
            float x1 = qCos(double(startAngle + 45 * (i + 5)) * M_PI / 180) * 50;
            float y1 = qSin(double(startAngle + 45 * (i + 5)) * M_PI / 180) * 50;
            QLineF line(x1, y1, x, y);
            painter->drawLine(line);
        }
    }
    painter->restore();
}

//绘制文字
void LabLoading::drawText(QPainter *painter)
{
    int radius = 50;
    painter->save();
    QString text = QString::number(ProgressNum) + "%";
    QFont font;
    font.setPixelSize(35);
    painter->setFont(font);
    painter->setPen(TextColor);
    QRect rect(-40, -25, 80 , 50 );
    painter->drawText(rect, Qt::AlignCenter, text);
    painter->restore();
}

void LabLoading::prorun()
{
    startAngle += 45;
    this->update();
}

QColor LabLoading::getBarColor() const
{
    return this->BarColor;
}

QColor LabLoading::getBgColor() const
{
    return this->BgColor;
}

QColor LabLoading::getTextColor() const
{
    return this->TextColor;
}

void LabLoading::setBarColor(const QColor &BarColor)
{
    if (this->BarColor != BarColor) {
        this->BarColor = BarColor;
        for (int i = 0; i < 5; i++) {
            rColor[i] = QColor(BarColor);
            rColor[i].setAlpha(100 + i * 20);
        }
        this->update();
    }
}

void LabLoading::setBgColor(const QColor &BgColor)
{
    if (this->BgColor != BgColor) {
        this->BgColor = BgColor;
        this->update();
    }
}

void LabLoading::setTextColor(const QColor &TextColor)
{
    if (this->TextColor != TextColor) {
        this->TextColor = TextColor;
        this->update();
    }
}

void LabLoading::setProgressNum(const int &ProgressNum)
{
    if (this->ProgressNum != ProgressNum) {
        this->ProgressNum = ProgressNum;
        this->update();
    }
}

void LabLoading::startRun()
{
    if (!timerrun->isActive()) {
        timerrun->start();
        ProgressRun = true;
        this->update();
    }
}

void LabLoading::stopRun()
{
    if (timerrun->isActive()) {
        timerrun->stop();
        ProgressRun = false;
        this->update();
    }
}

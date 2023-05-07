#include "WaveLabel.h"

WaveLabel::WaveLabel(QWidget *parent) :
QLabel(parent)
{
    m_waveStyle = GraphicStyle::ZhuZhuangTu;
    m_layout = GraphicLayout::LAY_LeftToRight;
}

WaveLabel::~WaveLabel()
{

}

void WaveLabel::slot_drawAudioPxm(const GraphicLayout &layout, const QAudioBuffer &buffer)
{
    m_layout = layout;
    m_buffer = buffer;
    this->update();
//    qDebug() << QString(u8"音频数据已绘制~！");
}

void WaveLabel::setGraphicStyle(const GraphicStyle &value)
{
    m_waveStyle = value;
    this->update();
}

void WaveLabel::paintEvent(QPaintEvent *event)
{
    int count = m_buffer.sampleCount() / 2;
    if(count <= 0) return;

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);//抗锯齿

    if(m_waveStyle == GraphicStyle::PingPu)
    {
        drawWaveformFigure(painter);
    }
    else if(m_waveStyle == GraphicStyle::ZhuZhuangTu)
    {
        drawHistogram(painter);
    }
    else if(m_waveStyle == GraphicStyle::ZhengTi)
    {
        drawOverallVolatility(painter);
    }
}

bool WaveLabel::eventFilter(QObject *watched, QEvent *event)
{
    return QLabel::eventFilter(watched,event);
}

//频谱效果
void WaveLabel::drawWaveformFigure(QPainter &painter)
{
    const qint32 *data = m_buffer.constData<qint32>();
        int count = m_buffer.sampleCount() / 2;

        QPen pen = painter.pen();
        pen.setWidth(1);
        pen.setColor(QColor(230, 80, 229));
        painter.setPen(pen);

        float xScale = (float)this->width() / count;
        float center = (float)this->height() / 2;
        for(int i = 1; i < count; i++)
        {
            painter.drawLine(
                        (i - 1) * xScale,
                        center + ((float)(data[i-1]) / INT_MAX * center),
                        i * xScale,
                        center + ((float)(data[i]) / INT_MAX * center) );

        }
}

//柱状图效果
void WaveLabel::drawHistogram(QPainter &painter)
{
    const qint32 *data = m_buffer.constData<qint32>();
         int count = m_buffer.sampleCount() / 2;

         int step = count / BEAMCOUNT;
         QVector <qreal> vecData;
         for(int i = 0; i < BEAMCOUNT+1; i++)
         {
             int number = 0;
             qreal sum = 0;
             for (int j = 0; j < step; j++)
             {
                 if(i * BEAMCOUNT + j >= count)
                     break;

                 qreal value = (qreal)(data[i * BEAMCOUNT + j]) / INT_MAX * this->height();

                 if(value > 0)
                 {
                     sum += value;
                     number++;
                 }
             }

             if(number > 0)
                 vecData.push_back(sum / number);
             else
                 vecData.push_back(0);
         }

         qreal rectangleWidth = (qreal)this->width() / vecData.count();// 图形加间隙的宽度
         qreal clearanceWidth = rectangleWidth / 4;    // 间隙宽度
         qreal shapeWidth = rectangleWidth - clearanceWidth; // 图形宽度

         QPen pen = painter.pen();
         pen.setWidth(shapeWidth);
         pen.setCapStyle(Qt::RoundCap);
         pen.setJoinStyle(Qt::RoundJoin);//圆角
//         pen.setColor(QColor(43, 222, 87,255));
//         painter.setPen(pen);

         if(m_layout == GraphicLayout::LAY_LeftToRight)
         {
//             this->setLayoutDirection(Qt::LeftToRight);
             for(int i = 0; i < vecData.count(); i++)
             {
                 pen.setColor(QColor(244, 220, 0));
                 painter.setPen(pen);
                 painter.drawLine(
                             i * rectangleWidth + rectangleWidth* 0.5,
                             this->height() - vecData[i],
                             i * rectangleWidth + rectangleWidth* 0.5,
                             this->height());
             }
         }
         else if(m_layout == GraphicLayout::LAY_RightToLeft)
         {
//             this->setLayoutDirection(Qt::RightToLeft);
             for(int i = 0; i < vecData.count(); i++)
             {
                 pen.setColor(QColor(244, 220, 0));//前面不够
                 painter.setPen(pen);
                 painter.drawLine(
                             i * rectangleWidth + rectangleWidth* 0.5,
                             this->height() - vecData[i],
                             i * rectangleWidth + rectangleWidth* 0.5,
                             this->height());
             }
         }
}

//整体效果
void WaveLabel::drawOverallVolatility(QPainter &painter)
{
    const qint32 *data = m_buffer.constData<qint32>();
        int count = m_buffer.sampleCount() / 2;

        qreal maxValue = 0;  // 取最大值
        for(int i = 1; i < count; i++)
        {
            qreal value = (qreal)(data[i]) / INT_MAX * this->height();
            maxValue = qMax(value,maxValue);
        }

        qreal rectangleWidth = (qreal)this->width() / 10;   // 图形加间隙的宽度
        qreal clearanceWidth = rectangleWidth / 4;    // 间隙宽度
        qreal shapeWidth = rectangleWidth - clearanceWidth; // 图形宽度

        for(int i = 0; i < 10; i++)
        {
            QRect rect(i * rectangleWidth + clearanceWidth*0.5, 0, shapeWidth, this->height());

            QLinearGradient gradient(rect.x(), rect.y(),rect.x(), rect.y() + rect.height());
            gradient.setColorAt(0.0, Qt::red);
            gradient.setColorAt(0.3, Qt::green);
            gradient.setColorAt(0.6, Qt::yellow);
            gradient.setColorAt(1.0, Qt::blue);

            painter.setPen(Qt::NoPen);
            gradient.setSpread(QGradient::ReflectSpread);
            painter.setBrush(gradient); // QBrush(const QGradient &gradient)
            painter.drawRect(rect);

            // 去掉顶部
            QBrush brush = painter.brush();
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::white);
            painter.setBrush(brush);

            painter.drawRect(i * rectangleWidth + clearanceWidth*0.5, 0, shapeWidth, this->height() - maxValue);
        }
}



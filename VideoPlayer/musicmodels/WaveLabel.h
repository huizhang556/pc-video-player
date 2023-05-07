#ifndef WAVELABEL_H
#define WAVELABEL_H
#define BEAMCOUNT 20
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QAudioBuffer>
#include <QDebug>

//频谱显示方向
enum GraphicLayout
{
    LAY_LeftToRight,
    LAY_RightToLeft
};

//频谱显示类型
enum GraphicStyle
{
    PingPu,
    ZhuZhuangTu,
    ZhengTi
};

class WaveLabel : public QLabel
{
    Q_OBJECT   
public:
    explicit WaveLabel(QWidget *parent = nullptr);
    ~WaveLabel();

public slots:
    void    setGraphicStyle(const GraphicStyle &value);
    void    slot_drawAudioPxm(const GraphicLayout& layout,const QAudioBuffer& buffer);

protected:
    void    paintEvent(QPaintEvent* event)override;
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    void    drawWaveformFigure(QPainter& painter);
    void    drawHistogram(QPainter& painter);
    void    drawOverallVolatility(QPainter& painter);


private:
    GraphicLayout   m_layout;//显示方向
    GraphicStyle    m_waveStyle;//枚举类型变量
    QAudioBuffer    m_buffer;
};

#endif // WAVELABEL_H

#ifndef TEXTMOVINGLABEL_H
#define TEXTMOVINGLABEL_H

#include <QEvent>
#include <QLabel>
#include <QTimer>
#include <QPainter>

enum MOVETYPE
{
    FIFO = 0,//末尾走完头部才出现
    FILO = 1//头部走到边界，反向移动
};

namespace Ui {
class TextMovingLabel;
}

class TextMovingLabel : public QLabel
{
    Q_OBJECT

public:
    TextMovingLabel(QWidget *parent = 0);
    ~TextMovingLabel();
    void            initMoveText(MOVETYPE type, const QString& text,const QFont& font,const QColor& color,const int& interval);//初始化
    void            setText(const QString&);//设置文本

protected:
    virtual void    paintEvent(QPaintEvent*);
    inline int      getDirection(const QString&);
    bool            eventFilter(QObject *watched, QEvent *event)override;

private slots:
    void            slot_UpdateTextGeometry();
    void            slot_controlTimer(bool start);

private:
    void            setTextColor(const QColor& color);//设置文本颜色
    void            setTextFont(const QFont& font); //设置文本人字体
    void            setTimerInterval(const int interval);//更新时间
    void            setTextMoveType(MOVETYPE type);//移动类型
    void            setTextMoveOffset(const int& offset_start, const int& offset_end);//设置开始和末尾的偏移量（主要是考虑连续显示否）

private:
    QTimer *m_timer   =  nullptr;
    MOVETYPE    m_moveType;//移动类型
    QString     m_text;
    QColor      m_color;
    QFont       m_font;
    int         m_upTime = 10;//默认30ms更新一次
    int         m_direction; //zero means left ,one means right;
    int         m_x;
    int         m_startOffset = 0;//开始位置的缩进量
    int         m_endOffset = 0;//结束位置的延伸量
};

#endif // TextMovingLabel_H

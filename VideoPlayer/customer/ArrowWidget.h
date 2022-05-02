#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class ArrowWidget : public QWidget
{
    Q_OBJECT

public:
    ~ArrowWidget();
    static  ArrowWidget* getInstance();
    // 设置小三角起始位置;
    void setStartPos(int startX);

    // 设置小三角宽和高;
    void setTriangleInfo(int width, int height);

    // 设置中间区域widget;
    void setCenterWidget(QWidget* widget);

protected:
    void paintEvent(QPaintEvent *);

private:
    ArrowWidget(QWidget *parent = 0);
    // 小三角起始位置;
    int m_startX;
    // 小三角的宽度;
    int m_triangleWidth;
    // 小三角高度;
    int m_triangleHeight;
    static ArrowWidget* m_pInstance;
};

#endif

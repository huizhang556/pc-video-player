#ifndef BASEWIDGET_H
#define BASEWIDGET_H

/***********自定义基础QWidget**********/
//功能：
//0.适配不同的操作系统（目前为:win和linux）
//1.自定义或保留系统标题栏
//2.自适应拖动改变大小或固定带小

#include <QWidget>
#include <QLayout>
#include <QMouseEvent>


class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    // 这里5距离是指窗口setContentsMargins的大小
    const int kMouseRegionLeft = 2;
    const int kMouseRegionTop = 2;
    const int kMouseRegionButtom = 2;
    const int kMouseRegionRight = 2;

    //九宫格法确定鼠标位置
    enum MousePosition
    {
        kMouseDrag = 0,  // 可拖拽
        kMousePositionLeftTop = 11,
        kMousePositionTop = 12,
        kMousePositionRightTop = 13,
        kMousePositionLeft = 21,
        kMousePositionMid = 22,
        kMousePositionRight = 23,
        kMousePositionLeftButtom = 31,
        kMousePositionButtom = 32,
        kMousePositionRightButtom = 33,
    };

public:
    explicit BaseWidget(QWidget *parent = nullptr);
    ~BaseWidget();

    virtual void    setTitleBarMoveArea(QWidget* titleBar, const int margin);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void SetMouseCursor(int x, int y);
    int GetMouseRegion(int x, int y);

private:
    QPoint           last_point_;             //记录放大之前的位置
    QPoint           last_position_;          //窗口上一次的位置
    bool             left_button_pressed_ = false;   //鼠标左键按下
    int              mouse_press_region_ = kMousePositionMid; //鼠标点击的区域

    int             title_margin = 0;//标题栏margin
    int             title_height = 0;//标题栏height

};

#endif // BASEWIDGET_H

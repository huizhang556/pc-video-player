#include "BaseWidget.h"

BaseWidget::BaseWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setMouseTracking(true);//设置鼠标跟踪，检测鼠标状态
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
//    this->setStyleSheet("background-color: yellow;");
}

BaseWidget::~BaseWidget()
{

}

void BaseWidget::setTitleBarMoveArea(QWidget *titleBar = nullptr, const int margin = 0)
{
    if(titleBar == nullptr)
    {
        title_margin = 0;
        title_height = 0;
    }
    else
    {
        titleBar->setFixedHeight(titleBar->height());
         title_margin = margin;
         title_height = titleBar->height();
    }
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event)
{
    //根据位置设置鼠标样式
    SetMouseCursor(event->pos().x(), event->pos().y());

    if ((event->buttons() == Qt::LeftButton) && left_button_pressed_)
    {
        QPoint point_offset = event->globalPos() - last_position_;

        if (mouse_press_region_ == kMouseDrag)
        {
            setCursor(Qt::ArrowCursor);
            move(point_offset + last_point_);
        }
        else
        {
            QRect rect = geometry();
            switch (mouse_press_region_)
            {
            case kMousePositionLeftTop:  // 左上角
                rect.setTopLeft(rect.topLeft() + point_offset);
                break;
            case kMousePositionTop:     // 上面
                rect.setTop(rect.top() + point_offset.y());
                break;
            case kMousePositionRightTop: // 右上角
                rect.setTopRight(rect.topRight() + point_offset);
                break;
            case kMousePositionRight:   // 右边
                rect.setRight(rect.right() + point_offset.x());
                break;
            case kMousePositionRightButtom: // 右下角
                rect.setBottomRight(rect.bottomRight() + point_offset);
                break;
            case kMousePositionButtom:     // 下面
                rect.setBottom(rect.bottom() + point_offset.y());
                break;
            case kMousePositionLeftButtom: // 左下角
                rect.setBottomLeft(rect.bottomLeft() + point_offset);
                break;
            case kMousePositionLeft:   // 左边
                rect.setLeft(rect.left() + point_offset.x());
                break;
            default:
                break;
            }
            setGeometry(rect);
            last_position_ = event->globalPos();
        }
    }
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    left_button_pressed_ = false;
}

void BaseWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint tempPos = event->pos();

    if (event->buttons() == Qt::LeftButton)
    {
        left_button_pressed_ = true;
        last_point_ = pos();
        last_position_ = event->globalPos();
        mouse_press_region_ = GetMouseRegion(tempPos.x(), tempPos.y());
    }
}

void BaseWidget::SetMouseCursor(int x, int y)
{
    Qt::CursorShape cursor = Qt::ArrowCursor;
    int region = GetMouseRegion(x, y);
    switch (region)
    {
    case kMousePositionLeftTop:
    case kMousePositionRightButtom:
        cursor = Qt::SizeFDiagCursor; break;//西北到东南方向
    case kMousePositionRightTop:
    case kMousePositionLeftButtom:
        cursor = Qt::SizeBDiagCursor; break;//东北到西南方向
    case kMousePositionLeft:
    case kMousePositionRight:
        cursor = Qt::SizeHorCursor; break;//左边界 右边界
    case kMousePositionTop:
    case kMousePositionButtom:
        cursor = Qt::SizeVerCursor; break;//上边界 下边界
    case kMousePositionMid:
        cursor = Qt::ArrowCursor; break;//中心区域
    default:
        break;
    }
    setCursor(cursor);
}

int BaseWidget::GetMouseRegion(int x, int y)
{
    int w = this->width();

    int region_x = 0, region_y = 0;
    if (x < kMouseRegionLeft)
    {
        region_x = 1;
    }
    else if (x > (width() - kMouseRegionRight))
    {
        region_x = 3;
    }
    else
    {
        region_x = 2;
    }
    if (y < kMouseRegionTop)
    {
        region_y = 1;
    }
    else if (y > (height() - kMouseRegionButtom))
    {
        region_y = 3;
    }
    else if(x > title_margin && x < w - title_margin && y > title_margin && y < title_height - title_margin)
    {
        // 拖拽区域
        return 0;
    }
    else
    {
        region_y = 2;
    }

    return region_y * 10 + region_x;
}

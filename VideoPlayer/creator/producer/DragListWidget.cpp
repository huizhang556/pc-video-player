#include "DragListWidget.h"

DragListWidget::DragListWidget(QWidget *parent) :
    QListWidget(parent)
{
    this->setDragEnabled(true);
    this->setAcceptDrops(true);//开启部件接受放下事件
//    this->viewport()->setAcceptDrops(true);
    this->setDragDropMode(QAbstractItemView::InternalMove);//设置拖放模式为移动项目，如果不设置，默认为复制项目
//    this->setDefaultDropAction(Qt::CopyAction);
    this->showDropIndicator();//设置显示将要被放置的位置
    this->installEventFilter(this);
    this->verticalScrollBar()->setFixedWidth(10);
}

DragListWidget::~DragListWidget()
{

}

void DragListWidget::initListWidget(bool on, const int item_W, const int item_H, const qreal rate_minW, const qreal rate_maxW)
{
    m_on = on;
    m_item_W = item_W;
    m_item_H = item_H;
    m_minRate_W = rate_minW;
    m_maxRate_W = rate_maxW;

}

void DragListWidget::resizeItemsSizeHint()
{
    //不符合条件情况1
    if(this->count() == 0) return;

    //符合条件
    if(this->count() > 0)
    {
        //宽度盛不下item才进行缩放
        if(this->count()*this->item(0)->sizeHint().width() > this->width())
        {
            int avgWidth = item_calAvg_W();

            for(int i = 0; i < this->count(); i++)
            {
                this->item(i)->setSizeHint(QSize(avgWidth,m_item_H));//只变化宽度，高度固定
            }
        }
        this->horizontalScrollBar()->setValue(0);//回到最顶端
    }
}


//拖动事件
void DragListWidget::dragEnterEvent(QDragEnterEvent *event)
{
//    qDebug() << QString(u8"dragEnterEvent text:%1").arg(event->mimeData()->text());
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
//        event->accept();
    }
}

//放下事件
void DragListWidget::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &url, event->mimeData()->urls())
    {
        QString filePath = url.toLocalFile();
//        qDebug() << QString(u8"URL = :%1").arg(filePath);
        QString itemName = QFileInfo(filePath).fileName();
//        QListWidgetItem *item = new QListWidgetItem(itemName, this);
//        this->addItem(item);
//        setCurrentItem(item);
        if(getFileType2(itemName))
        {
            emit sig_item_url_list(url);
        }
    }
}

//事件捕获过滤
bool DragListWidget::eventFilter(QObject *object, QEvent *event)
{
    if(object == this && event->type() == QEvent::Resize)
    {
        if(m_on)//打开情况下
            resizeItemsSizeHint();
    }
    return QListWidget::eventFilter(object,event);
}

bool DragListWidget::getFileType2(const QString &fileName)
{
    //判断一下文件类型，加载不同图标
    if(fileName.endsWith("mp4",Qt::CaseInsensitive))//返回的是mp4,而非 .mp4
    {
        return true;
    }
    else if(fileName.endsWith("mov",Qt::CaseInsensitive))
    {
        return true;
    }
    else if(fileName.endsWith("avi",Qt::CaseInsensitive))
    {
        return true;
    }
    else if(fileName.endsWith("flv",Qt::CaseInsensitive))
    {
        return true;
    }
    else if(fileName.endsWith("mp3",Qt::CaseInsensitive))
    {
        return true;
    }
    else if(fileName.endsWith("aac",Qt::CaseInsensitive))
    {
        return true;
    }
    else if(fileName.endsWith("wav",Qt::CaseInsensitive))
    {
        return true;
    }
    else if(fileName.endsWith("wma",Qt::CaseInsensitive))
    {
        return true;
    }
    else//后面有需要还可以添加文件类型判断
    {
        return false;
    }
}

//计算平均宽度
int DragListWidget::item_calAvg_W()
{
    int avg_w = 0;
    int Width = this->width() - this->verticalScrollBar()->width() - m_widthOffset;
    if (Width <= m_item_W*m_maxRate_W*1) //1个item最小宽度 和 最大宽度之间
    {
        //(200 - 215]
        m_colCount = 1;
    }
    else if(Width <= m_item_W*m_maxRate_W*2)
    {
        //(215,430]
        m_colCount = 2;
    }
    else if(Width <= m_item_W*m_maxRate_W*3)
    {
        //(430,645]
        m_colCount = 3;
    }
    else if(Width <= m_item_W*m_maxRate_W*4)
    {
        m_colCount = 4;
    }
    else if(Width <= m_item_W*m_maxRate_W*5)
    {
        m_colCount = 5;
    }
    else if(Width <= m_item_W*m_maxRate_W*6)
    {
        m_colCount = 6;
    }
    else if(Width <= m_item_W*m_maxRate_W*7)
    {
        m_colCount = 7;
    }
    else if(Width <= m_item_W*m_maxRate_W*8)
    {
        m_colCount = 8;
    }
    else if(Width <= m_item_W*m_maxRate_W*9)
    {
        m_colCount = 9;
    }
    else if(Width <= m_item_W*m_maxRate_W*10)
    {
        m_colCount = 10;
    }
    else if(Width <= m_item_W*m_maxRate_W*11)
    {
        m_colCount = 11;
    }
    else if(Width <= m_item_W*m_maxRate_W*12)
    {
        m_colCount = 12;
    }

    avg_w = (int)(Width/m_colCount);
    return avg_w;
}

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
}

DragListWidget::~DragListWidget()
{

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

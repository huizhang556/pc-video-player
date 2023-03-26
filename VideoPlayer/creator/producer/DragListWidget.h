#ifndef DRAGLISTWIDGET_H
#define DRAGLISTWIDGET_H

#include <QEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QListWidget>
#include <QFileInfo>
#include <QDebug>
#include <QDebug>

class DragListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit DragListWidget(QWidget *parent = nullptr);
    ~DragListWidget();

protected:
    void    dragEnterEvent(QDragEnterEvent *event) override;//拖动操作
    void    dropEvent(QDropEvent *event)override;//放下事件

private:
    bool    getFileType2(const QString &fileName);

signals:
    void    sig_item_url_list(QUrl);

};

#endif // DRAGLISTWIDGET_H

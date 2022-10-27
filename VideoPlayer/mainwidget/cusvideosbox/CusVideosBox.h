#ifndef CUSVIDEOSBOX_H
#define CUSVIDEOSBOX_H

#include <QWidget>
#include <QLayout>
#include <QListWidget>
#include <QScrollArea>
#include <QListWidgetItem>
#include <QDebug>

//单个item信息
struct itemInfo
{
    QString sourceUrl;//资源路径
    QString picPath;//图片路径
    QString info1;//介绍信息1
    QString info2;//介绍信息2
    QString topMark;//右上标志显示
    QString bottomMark;//右下标志显示
};

//item1结构体
struct item1Info
{
    QString title;//标题
    itemInfo item;
};

//item2结构体
struct item2Info
{
    QString title;//标题
    QString sourceUrlLeft;//资源url
    QString leftPicPath;
    QString leftInfo1;//介绍信息1
    QString leftInfo2;//介绍信息2
    itemInfo item;
};

namespace Ui {
class CusVideosBox;
}

class CusVideosBox : public QWidget
{
    Q_OBJECT

public:
    explicit CusVideosBox(QWidget *parent = nullptr);
    ~CusVideosBox();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

private:
    Ui::CusVideosBox *ui;
};

#endif // CUSVIDEOSBOX_H

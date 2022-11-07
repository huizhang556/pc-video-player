#ifndef CUSVERSTACKWGT_H
#define CUSVERSTACKWGT_H

#define SACLWIDTH   1200 //开始放大最小宽度1200
#define FIXEDHEIGHT 360  //小于放大宽度设置为固定高 360
#define SCALSIZE    0.28 //放大时 高/宽 比例
#define MINWINSIZE  QSize(830,FIXEDHEIGHT)  //界面最小size
#define RESIZESIZE  QSize(1160,360)     //默认加载是size（一般会被重置）

#define RDEFSIZE    QSize(260,320)
#define RSACLE_H  0.88  //放大时 右侧列表高占整体高 比例
#define RSACLE_W  0.20  //放大时 右侧列表宽占整体宽 比例

#include <QWidget>
#include <QEvent>
#include <QLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QListWidget>
#include <QStringList>
#include <QDebug>

namespace Ui {
class CusVerStackWgt;
}

class CusVerStackWgt : public QStackedWidget
{
    Q_OBJECT

public:
    explicit CusVerStackWgt(QWidget *parent = nullptr);
    ~CusVerStackWgt();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
    void    slot_addItemToCusVerStackWgt(const QString& picpath);
    void    slot_addToStackPictures(const QStringList & introduce,const QStringList & list_pic);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    QListWidget             *m_rightListWidget  =   nullptr;
    QStringList             m_pictureList;

    QStringList             m_itemsTextList =
                                            {
                                                QString(u8"戏剧大赛2"),
                                                QString(u8"谢谢你医生"),
                                                QString(u8"谁都知道我爱你"),
                                                QString(u8"爸爸去哪了？"),
                                                QString(u8"世界上另一个你"),
                                                QString(u8"唐朝诡事录"),
                                            };

   private:
    void    updateListWidgetGeometry();
    void    update_W_H_scale();
};

#endif // CUSVERSTACKWGT_H

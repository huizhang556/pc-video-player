#ifndef RANKLIST_H
#define RANKLIST_H
#define ITEMHEIGHT  50
#include "mainwidget/subunititems/HotListItem.h"
#include <QWidget>
#include <QLayout>
#include <QEvent>
#include <QScrollBar>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>

namespace Ui {
class RankList;
}

class RankList : public QWidget
{
    Q_OBJECT

public:
    explicit RankList(QWidget *parent = nullptr);
    explicit RankList(const QString& title,const int num, QWidget *parent = nullptr);
    ~RankList();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
    void    slot_addItemToRankList(const QString &url, const QString &num, const QString &picpath, const QString &maininfo, const QString &info, const QString &hotvalue);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    void    resizeListGeometry();

private:
    QVBoxLayout     *m_vblayout1    =   nullptr;
    QPushButton     *m_buttonTitle  =   nullptr;//头部
    QListWidget     *m_rankListWgt  =   nullptr;//排行榜

    QStringList     mainInfo = {
        QString(u8"火隐忍者"),
        QString(u8"名侦探柯南"),
        QString(u8"万古剑神"),
        QString(u8"冰火魔厨"),
        QString(u8"重启之深渊疑冢"),
        QString(u8"搜救"),
        QString(u8"大话女儿国"),
        QString(u8"独行月球"),
        QString(u8"宝贝老板"),
        QString(u8"境界 新篇章")
    };

    QStringList     Info     = {
        QString(u8"纷繁忍界非凡物语"),
        QString(u8"天才少年推理秀"),
        QString(u8"剑客诞生之路"),
        QString(u8"少年探寻厨艺巅峰"),
        QString(u8"丛林地宫探险之旅"),
        QString(u8"甄子丹舍身救援"),
        QString(u8"天降之神拯救女儿国"),
        QString(u8"宇宙最后的人类"),
        QString(u8"小婴儿变宝贝总裁"),
        QString(u8"黑崎一护最终决战")
    };
};

#endif // RANKLIST_H

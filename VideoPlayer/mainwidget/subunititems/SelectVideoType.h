#ifndef SELECTVIDEOTYPE_H
#define SELECTVIDEOTYPE_H
#define BTNSIZE QSize(66,26)
#include <QSize>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QDebug>

//视频选择类型
enum   VSItemType
{
    VIDEO_STYLE,    //分类
    VIDEO_AREA,     //全部地区
    VIDEO_TYPE,     //全部类型
    VIDEO_YEAR,     //全部年份
    VIDEO_RANGE,    //全部规格
    VIDEO_FEETYPE,  //付费类型
    VIDEO_SORT      //综合排序
};

namespace Ui {
class SelectVideoType;
}

class SelectVideoType : public QWidget
{
    Q_OBJECT

public:
    explicit SelectVideoType(QWidget *parent = nullptr);
    ~SelectVideoType();
    void    initWorkUI();
    void    handleSignalsAndSlots();

public slots:
    void    slot_addSelectTypeItemsToFrame(VSItemType itemType, const QStringList& list);
    void    slot_setSortHidden(bool hide);
signals:
    void    sig_selectResult(QString);

private:
    Ui::SelectVideoType *ui;
    QButtonGroup *m_buttonGroup0 = nullptr;
    QButtonGroup *m_buttonGroup1 = nullptr;
    QButtonGroup *m_buttonGroup2 = nullptr;
    QButtonGroup *m_buttonGroup3 = nullptr;
    QButtonGroup *m_buttonGroup4 = nullptr;
    QButtonGroup *m_buttonGroup5 = nullptr;
    QButtonGroup *m_buttonGroup6 = nullptr;
    QButtonGroup *m_buttonGroup7 = nullptr;
    //分类
    QStringList list_videostyle =
    {
        QString(u8"分类"),
        QString(u8"电视剧"),
        QString(u8"电影"),
        QString(u8"综艺"),
        QString(u8"纪录片"),
        QString(u8"教育"),
        QString(u8"生活"),
        QString(u8"体育"),
        QString(u8"游戏")
    };
    //全部地区
    QStringList list_videoarea =
    {
        QString(u8"全部地区"),
        QString(u8"内地剧"),
        QString(u8"港剧"),
        QString(u8"台剧"),
        QString(u8"韩剧"),
        QString(u8"美剧"),
        QString(u8"英剧"),
        QString(u8"日剧"),
        QString(u8"泰剧")
    };
    //全部类型
    QStringList list_videotype =
    {
        QString(u8"全部类型"),
        QString(u8"青春"),
        QString(u8"古装"),
        QString(u8"都市"),
        QString(u8"喜剧"),
        QString(u8"战争"),
        QString(u8"军旅"),
        QString(u8"偶像"),
        QString(u8"冒险")
    };
    //全部年份
    QStringList list_videoyear =
    {
        QString(u8"全部年份"),
        QString(u8"2022"),
        QString(u8"2021"),
        QString(u8"2020"),
        QString(u8"2019"),
        QString(u8"2018"),
        QString(u8"2017"),
        QString(u8"2016-2011"),
        QString(u8"更早")
    };
    //全部规格
    QStringList list_videorange =
    {
        QString(u8"全部规格"),
        QString(u8"全网独播"),
        QString(u8"优酷自制"),
        QString(u8"已完结"),
        QString(u8"即将上线"),
        QString(u8"短剧")
    };
    //付费类型
    QStringList list_videofeetype =
    {
        QString(u8"付费类型"),
        QString(u8"免费"),
        QString(u8"VIP")
    };
    //综合排序
    QStringList list_videosort =
    {
        QString(u8"综合排序"),
        QString(u8"热度最高"),
        QString(u8"最新上线"),
        QString(u8"最好评"),
        QString(u8"最多播放")
    };
};

#endif // SELECTVIDEOTYPE_H

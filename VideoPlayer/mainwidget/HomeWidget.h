#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H
#include "mainwidget/SelectButtons.h"
#include "mainwidget/recommend/CentralHomeForm.h"
#include "mainwidget/songersort/SongerSort.h"
#include "mainwidget/rankinglist/RankingList.h"
#include "mainwidget/songlistsort/SonglistSort.h"
#include "mainwidget/radiohost/RadioHost.h"
#include "mainwidget/musicscene/MusicScene.h"
#include "mainwidget/vipmember/VipMember.h"

#include <QWidget>
#include <QLayout>
#include <QStackedWidget>


namespace Ui {
class HomeWidget;
}

class HomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);
    ~HomeWidget();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    void        addToStackWidget();

private slots:
    void        slot_setCurrentCenterStackWidget(int index);//设置中心区域

private:
    Ui::HomeWidget *ui;
    SelectButtons       *m_selectButton            = nullptr;//选择切换
    CentralHomeForm     *m_homeWdgt                = nullptr;//推荐专区
    SongerSort          *m_songerSort              = nullptr;//歌手排行
    RankingList         *m_rankList                = nullptr;//排行榜
    SonglistSort        *m_songlistSort            = nullptr;//歌单分类
    RadioHost           *m_radioHost               = nullptr;//主播电台
    MusicScene          *m_musicScene              = nullptr;//音乐现场
    VipMember           *m_vipMember               = nullptr;//会员专区
    QStackedWidget      *m_stackWgt_center         = nullptr;//承载区域
    QVBoxLayout         *m_vbHlayout               = nullptr;
};

#endif // HOMEWIDGET_H

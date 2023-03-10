#ifndef RECOMVIDEOTAB_H
#define RECOMVIDEOTAB_H
#include <QList>
#include <QWidget>
#include <QVariant>
#include <QListWidget>
#include <QPushButton>
#include <QStringList>

typedef struct MusicInfo //定义结构体
{
    int id;                 //id
    QString     nick;       //别名
    QString     alias;      //标题
    QString     url;        //视频地址
    QString     duration;   //时长
    QString     cover;      //封面
    QString     uplove;     //播放量
} MusicData;
//声明元对象 MusicData，让元对象系统知道这个变量类型的存在
//在哪解析结构体，就在哪里的头文件(xxx.h)文件中定义结构体
Q_DECLARE_METATYPE(MusicData)

namespace Ui {
class RecomVideoTab;
}

class RecomVideoTab : public QWidget
{
    Q_OBJECT

public:
    explicit RecomVideoTab(QWidget *parent = nullptr);
    ~RecomVideoTab();
    void            initWorkUI();
    void            handleSignalsAndSLots();
    QStringList     slot_getDramaList();

public slots:
    void    slot_setCurrentVideoPicture(const QString& path);//设置当前正在播放视频图片
    void    slot_setCurrentVideoInfo(QString info);//设置介绍
    bool    slot_addRecVideoItem(QVariant   musicVariant);//通过结构体传递信息
    bool    slot_addRecVideoItem(QString url, QString path,QString time,QString info,QString count);//添加item
    void    slot_setListWidgetCurrentIndex(int index);//设置当前选中行

private slots:
    void slots_switchTurn();

private:
    bool        m_turnOnStatus;
    Ui::RecomVideoTab *ui;

    QStringList             m_tempVideoList;//临时视频播放列表
    QStringList             m_tempInfoList;//临时视频信息列表
    QList<QString>          m_recplayList;//推荐播放列表

private:
    QPushButton*    getListWidgetItemButton(QListWidgetItem* item, QString objname);//在item中查找指定按钮

signals:
    void    sig_sendVideoUrl(QString);
    void    sig_recom_playlist(int,QStringList,QString);
};

#endif // RECOMVIDEOTAB_H

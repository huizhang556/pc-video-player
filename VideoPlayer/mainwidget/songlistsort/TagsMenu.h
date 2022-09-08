#ifndef TAGSMENU_H
#define TAGSMENU_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QStringList>
#include <QPaintEvent>

namespace Ui {
class TagsMenu;
}

class TagsMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TagsMenu(QWidget *parent = nullptr);
    ~TagsMenu();

    void        initWorkUI();
    void        handleSignalsAndSlots();

public slots:
    void        slot_addSongItem(const QString& titleIcon,const QString& titleText,const QStringList& list);

protected:
    void        paintEvent(QPaintEvent* event);

signals:
    void        sig_sendCurrentItemText(QString);

private:
    Ui::TagsMenu *ui;
    int     m_startX;
    int     m_startY;
    int     m_triangleWidth;//小三角宽度
    int     m_triangleHeight;//小三角高度

    QStringList     m_theme = {
        QString::fromLocal8Bit("专区"),
        QString::fromLocal8Bit("主题"),
        QString::fromLocal8Bit("心情"),
        QString::fromLocal8Bit("场景"),
        QString::fromLocal8Bit("年代"),
        QString::fromLocal8Bit("语言"),
        QString::fromLocal8Bit("流派")
    };

    QStringList     m_area = {
        QString::fromLocal8Bit("抖音专区"),
        QString::fromLocal8Bit("网红专区"),
        QString::fromLocal8Bit("DJ专区"),
        QString::fromLocal8Bit("国风专区"),
        QString::fromLocal8Bit("小说专区"),
        QString::fromLocal8Bit("佛乐专区"),
        QString::fromLocal8Bit("影视专区"),
        QString::fromLocal8Bit("铃声专区"),
        QString::fromLocal8Bit("动漫专区"),
        QString::fromLocal8Bit("老歌专区"),
        QString::fromLocal8Bit("首发专区"),
        QString::fromLocal8Bit("K歌专区"),
        QString::fromLocal8Bit("DJ专区"),
        QString::fromLocal8Bit("古典专区"),
        QString::fromLocal8Bit("Vlog专区"),
        QString::fromLocal8Bit("综艺专区"),
        QString::fromLocal8Bit("轻音乐专区"),
        QString::fromLocal8Bit("铃声专区")
    };
    QStringList     m_subject = {
        QString::fromLocal8Bit("抖音"),
        QString::fromLocal8Bit("情歌"),
        QString::fromLocal8Bit("DJ"),
        QString::fromLocal8Bit("经典"),
        QString::fromLocal8Bit("BGM"),
        QString::fromLocal8Bit("古风"),
        QString::fromLocal8Bit("喊麦"),
        QString::fromLocal8Bit("游戏"),
        QString::fromLocal8Bit("轻音乐"),
        QString::fromLocal8Bit("佛教"),
        QString::fromLocal8Bit("合唱"),
        QString::fromLocal8Bit("网络"),
        QString::fromLocal8Bit("儿童"),
        QString::fromLocal8Bit("影视"),
        QString::fromLocal8Bit("说唱"),
        QString::fromLocal8Bit("翻唱"),
        QString::fromLocal8Bit("3D")
    };
    QStringList     m_feeling = {
        QString::fromLocal8Bit("伤感"),
        QString::fromLocal8Bit("放松"),
        QString::fromLocal8Bit("励志"),
        QString::fromLocal8Bit("开心"),
        QString::fromLocal8Bit("甜蜜"),
        QString::fromLocal8Bit("兴奋"),
        QString::fromLocal8Bit("安静"),
        QString::fromLocal8Bit("治愈"),
        QString::fromLocal8Bit("思念")
    };

    QStringList     m_scene = {
        QString::fromLocal8Bit("开车"),
        QString::fromLocal8Bit("运动"),
        QString::fromLocal8Bit("学习"),
        QString::fromLocal8Bit("清晨"),
        QString::fromLocal8Bit("旅行"),
        QString::fromLocal8Bit("工作"),
        QString::fromLocal8Bit("广场舞"),
        QString::fromLocal8Bit("校园"),
        QString::fromLocal8Bit("夜店")
    };

    QStringList     m_years = {
        QString::fromLocal8Bit("60后"),
        QString::fromLocal8Bit("70后"),
        QString::fromLocal8Bit("80后"),
        QString::fromLocal8Bit("90后"),
        QString::fromLocal8Bit("00后"),
        QString::fromLocal8Bit("10后")
    };

    QStringList     m_language = {
        QString::fromLocal8Bit("华语"),
        QString::fromLocal8Bit("欧美"),
        QString::fromLocal8Bit("日语"),
        QString::fromLocal8Bit("韩语"),
        QString::fromLocal8Bit("粤语"),
        QString::fromLocal8Bit("小语种")
    };

    QStringList     m_style = {
        QString::fromLocal8Bit("流行"),
        QString::fromLocal8Bit("电子"),
        QString::fromLocal8Bit("摇滚"),
        QString::fromLocal8Bit("民歌"),
        QString::fromLocal8Bit("古典"),
        QString::fromLocal8Bit("嘻哈"),
        QString::fromLocal8Bit("乡村"),
        QString::fromLocal8Bit("爵士")
    };

    QVector<QStringList>     m_vector;
    QVector<QString>         m_vectorPic;
};

#endif // TAGSMENU_H

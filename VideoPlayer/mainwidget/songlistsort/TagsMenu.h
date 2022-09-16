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
    void        paintEvent(QPaintEvent* event) override;

signals:
    void        sig_sendCurrentItemText(QString);

private:
    Ui::TagsMenu *ui;
    int     m_startX;
    int     m_startY;
    int     m_triangleWidth;//小三角宽度
    int     m_triangleHeight;//小三角高度

    QStringList     m_theme = {
        QString(u8"专区"),
        QString(u8"主题"),
        QString(u8"心情"),
        QString(u8"场景"),
        QString(u8"年代"),
        QString(u8"语言"),
        QString(u8"流派"),
        QString(u8"有声")
    };

    QStringList     m_area = {
        QString(u8"抖音专区"),
        QString(u8"网红专区"),
        QString(u8"DJ专区"),
        QString(u8"国风专区"),
        QString(u8"小说专区"),
        QString(u8"佛乐专区"),
        QString(u8"影视专区"),
        QString(u8"铃声专区"),
        QString(u8"动漫专区"),
        QString(u8"老歌专区"),
        QString(u8"首发专区"),
        QString(u8"K歌专区"),
        QString(u8"DJ专区"),
        QString(u8"古典专区"),
        QString(u8"Vlog专区"),
        QString(u8"综艺专区"),
        QString(u8"轻音乐专区"),
        QString(u8"创新专区"),
        QString(u8"铃声专区")
    };
    QStringList     m_subject = {
        QString(u8"抖音"),
        QString(u8"情歌"),
        QString(u8"DJ"),
        QString(u8"经典"),
        QString(u8"BGM"),
        QString(u8"古风"),
        QString(u8"喊麦"),
        QString(u8"游戏"),
        QString(u8"轻音乐"),
        QString(u8"佛教"),
        QString(u8"合唱"),
        QString(u8"网络"),
        QString(u8"儿童"),
        QString(u8"影视"),
        QString(u8"说唱"),
        QString(u8"翻唱"),
        QString(u8"3D")
    };
    QStringList     m_feeling = {
        QString(u8"伤感"),
        QString(u8"放松"),
        QString(u8"励志"),
        QString(u8"开心"),
        QString(u8"甜蜜"),
        QString(u8"兴奋"),
        QString(u8"安静"),
        QString(u8"治愈"),
        QString(u8"思念")
    };

    QStringList     m_scene = {
        QString(u8"开车"),
        QString(u8"运动"),
        QString(u8"学习"),
        QString(u8"清晨"),
        QString(u8"旅行"),
        QString(u8"工作"),
        QString(u8"广场舞"),
        QString(u8"校园"),
        QString(u8"夜店")
    };

    QStringList     m_years = {
        QString(u8"60后"),
        QString(u8"70后"),
        QString(u8"80后"),
        QString(u8"90后"),
        QString(u8"00后"),
        QString(u8"10后")
    };

    QStringList     m_language = {
        QString(u8"华语"),
        QString(u8"欧美"),
        QString(u8"日语"),
        QString(u8"韩语"),
        QString(u8"粤语"),
        QString(u8"俄语"),
        QString(u8"小语种")
    };

    QStringList     m_style = {
        QString(u8"流行"),
        QString(u8"电子"),
        QString(u8"摇滚"),
        QString(u8"民歌"),
        QString(u8"古典"),
        QString(u8"嘻哈"),
        QString(u8"乡村"),
        QString(u8"爵士")
    };

    QStringList     m_voice = {
        QString(u8"相声"),
        QString(u8"评书"),
        QString(u8"戏曲"),
        QString(u8"二人转")
    };

    QVector<QStringList>     m_vector;
    QVector<QString>         m_vectorPic;
};

#endif // TAGSMENU_H

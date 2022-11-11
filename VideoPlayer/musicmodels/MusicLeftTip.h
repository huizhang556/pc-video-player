#ifndef MUSICLEFTTIP_H
#define MUSICLEFTTIP_H

#include <QWidget>
#include <QMenu>
#include <QEvent>
#include <QTimer>
#include <QPushButton>
#include <QStringList>

namespace Ui {
class MusicLeftTip;
}

class MusicLeftTip : public QWidget
{
    Q_OBJECT

    explicit MusicLeftTip(QWidget *parent = nullptr);
public:
    ~MusicLeftTip();
    void    initWorkUI();
    void    handleSinalsAndSlots();

    static  MusicLeftTip* getInstance();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void    slot_switchBgPicture_songer();
    void    slot_switchBgPicture_skin();
    void    slot_switchBgPicture_localPic();

private:
    Ui::MusicLeftTip *ui;
    static          MusicLeftTip* m_pInstance;
    QStringList     songList =
    {
        QString(u8"歌词写真"),
        QString(u8"推荐评论"),
        QString(u8"MV"),
        QString(u8"桌面写真"),
        QString(u8"歌词背景"),
        QString(u8"字体颜色"),
        QString(u8"搜索歌词"),
        QString(u8"歌词设置"),
        QString(u8"固定底栏")
    };
};

#endif // MUSICLEFTTIP_H

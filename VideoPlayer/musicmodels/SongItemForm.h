#ifndef SONGITEMFORM_H
#define SONGITEMFORM_H

#include <QWidget>
#include <QPushbutton>

namespace Ui {
class SongItemForm;
}

class SongItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit SongItemForm(QWidget *parent = nullptr);
    explicit SongItemForm(const QString& num, const QString& son_name,bool vip, bool col, const QString& songer, const QString& album, const QString& quality, QWidget *parent = nullptr);

    ~SongItemForm();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();
    QString addPrefixNum(QString num);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:


private:
    Ui::SongItemForm *ui;
        bool        m_vip;//是否会员歌曲
        QString     m_number;//序号
        QString     m_songName;//歌曲名称
        bool        m_colStatus;//收藏状态
        QString     m_songerName;//歌手名称
        QString     m_album;//所属专辑
        QString     m_quality;//品质

private:
    void    setItemNumber(const QString& num);
    void    setItemSongNameAndVip(const QString& name,bool vip);
    void    setItemSongCollectStatus(bool collect);
    void    setItemSongSonger(const QString& songer);
    void    setItemSongAlbum(const QString& album);
    void    setItemSongQuality(const QString& quality);

signals:
    void    sig_son_playbtn_clicked(int index);
    void    sig_son_mvbtn_clicked(int index);
    void    sig_son_collectbtn_clicked(int index);
    void    sig_son_downloadbtn_clicked(int index);
    void    sig_son_deletebtn_clicked(int index);
    void    sig_son_morebtn_clicked(int index);
    void    sig_son_qualityBtn_clicked(int index);

};

#endif // SONGITEMFORM_H

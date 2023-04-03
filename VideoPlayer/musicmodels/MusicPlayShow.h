#ifndef MUSICPLAYSHOW_H
#define MUSICPLAYSHOW_H
#include "global/Global.h"

#include <QWidget>
#include <QMenu>
#include <QTimer>
#include <QEvent>
#include <QPixmap>

namespace Ui {
class MusicPlayShow;
}

class MusicPlayShow : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayShow(QWidget *parent = nullptr);
    ~MusicPlayShow();
    void            initWorkUI();
    void            handleSignalsAndSlots();
    void            setInstallEventFilter();
    void            loadPictures(QString &path) const;
    void            changeTimeCout();

public slots:
    //公共函数可以再类外访问，私有只能在类内
    void receiveMainWinData(QString name);
    void slot_controlPlayStatus(bool status);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

signals:
    void    sig_curLyric(QString&);

private:
    Ui::MusicPlayShow *ui;
    QPixmap     *photo;
    QString     fileName;
    QString     m_skinPath;
    int         i = 1;

private:
    const QString    switchSkin(const QString& text);//切换皮肤
};

#endif // MUSICPLAYSHOW_H

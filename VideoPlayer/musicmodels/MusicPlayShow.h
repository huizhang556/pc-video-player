#ifndef MUSICPLAYSHOW_H
#define MUSICPLAYSHOW_H

#include <QWidget>
#include <QTimer>
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

    void loadPictures(QString &path) const;
    void changeTimeCout();

public slots:
    //公共函数可以再类外访问，私有只能在类内
    void receiveMainWinData(QString name);
signals:

private:
    Ui::MusicPlayShow *ui;
    QTimer      *time;
    QPixmap     *photo;
    QString     fileName;
    int i = 1;

};

#endif // MUSICPLAYSHOW_H

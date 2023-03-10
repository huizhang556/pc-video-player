#ifndef VALUETOIMAGE_H
#define VALUETOIMAGE_H

#include <QLabel>
#include <QMovie>
#include <QDebug>

namespace Ui {
class ValueToImage;
}

class ValueToImage : public QLabel
{
    Q_OBJECT

public:
    explicit ValueToImage(QWidget *parent = nullptr);
    ~ValueToImage();
    void    initWoruUI();

public slots:
    void    slot_setValueImageTime(const int time);
    void    slot_setValueImage(QImage& image);
    void    slot_setWaitingStatus(const QString &text);

private:
    Ui::ValueToImage *ui;
//    QMovie  *m_waitingMovie;
};

#endif // VALUETOIMAGE_H

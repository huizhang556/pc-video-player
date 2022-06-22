#ifndef ROTATEPIC_H
#define ROTATEPIC_H

#include <QPainter>
#include <QWidget>
#include <QPixmap>
#include <QBitmap>
#include <QLayout>
#include <QTimer>
#include <QLabel>

namespace Ui {
class RotatePic;
}

class RotatePic : public QWidget
{
    Q_OBJECT

public:
    explicit RotatePic(QWidget *parent = nullptr);
    ~RotatePic();
    int     getRoate();
    void    resetRoate(int roate);
public slots:
    void    start();
    void    pause();
    void    setSize(int width, int height);
    void    setPicture(QString path);
protected:
    void    paintEvent(QPaintEvent *event) override;
private:
    QTimer      *m_timer    =   nullptr;
    QLabel      *m_labelpic =   nullptr;
    QPixmap     pix;
    int         m_roate;
    int         m_tempRoate;
};

#endif // ROTATEPIC_H

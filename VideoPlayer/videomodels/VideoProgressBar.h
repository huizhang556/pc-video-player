#ifndef VIDEOPROGRESSBAR_H
#define VIDEOPROGRESSBAR_H

#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class VideoProgressBar;
}

class VideoProgressBar : public QWidget
{
    Q_OBJECT

public:
    ~VideoProgressBar();
    static  VideoProgressBar* getInstance();
public slots:


protected:
    void paintEvent(QPaintEvent * event) override;

private slots:
    void slot_updaterRotation();

private:
    explicit VideoProgressBar(QWidget *parent = nullptr);
    Ui::VideoProgressBar *ui;
    int    rotation;
    static  VideoProgressBar* m_pInstance;
};

#endif // VIDEOPROGRESSBAR_H

#ifndef VIDEOPROGRESSBAR_H
#define VIDEOPROGRESSBAR_H

#include <QWidget>

namespace Ui {
class VideoProgressBar;
}

class VideoProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit VideoProgressBar(QWidget *parent = nullptr);
    ~VideoProgressBar();

private:
    Ui::VideoProgressBar *ui;
};

#endif // VIDEOPROGRESSBAR_H

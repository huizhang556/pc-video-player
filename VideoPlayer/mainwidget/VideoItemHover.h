#ifndef VIDEOITEMHOVER_H
#define VIDEOITEMHOVER_H

#include <QWidget>
#include <QEvent>

namespace Ui {
class VideoItemHover;
}

class VideoItemHover : public QWidget
{
    Q_OBJECT

public:
    explicit VideoItemHover(QWidget *parent = nullptr);
    ~VideoItemHover();

protected:
    void leaveEvent(QEvent *event) override;
private:
    Ui::VideoItemHover *ui;
};

#endif // VIDEOITEMHOVER_H

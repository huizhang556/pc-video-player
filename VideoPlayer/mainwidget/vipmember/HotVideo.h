#ifndef HOTVIDEO_H
#define HOTVIDEO_H

#include <QWidget>

namespace Ui {
class HotVideo;
}

class HotVideo : public QWidget
{
    Q_OBJECT

public:
    explicit HotVideo(QWidget *parent = nullptr);
    ~HotVideo();

private:
    Ui::HotVideo *ui;
};

#endif // HOTVIDEO_H

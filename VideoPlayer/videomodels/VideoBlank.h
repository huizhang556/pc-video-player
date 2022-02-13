#ifndef VIDEOBLANK_H
#define VIDEOBLANK_H

#include <QWidget>

namespace Ui {
class VideoBlank;
}

class VideoBlank : public QWidget
{
    Q_OBJECT

public:
    explicit VideoBlank(QWidget *parent = nullptr);
    ~VideoBlank();

private slots:


private:
    Ui::VideoBlank *ui;

signals:
    void sig_openLocalFile();
};

#endif // VIDEOBLANK_H

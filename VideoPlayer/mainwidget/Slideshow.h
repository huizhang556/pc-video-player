#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include <QWidget>

namespace Ui {
class Slideshow;
}

class Slideshow : public QWidget
{
    Q_OBJECT

public:
    explicit Slideshow(QWidget *parent = nullptr);
    ~Slideshow();

private slots:
    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

private:
    Ui::Slideshow *ui;
};

#endif // SLIDESHOW_H

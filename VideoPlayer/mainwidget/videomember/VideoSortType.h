#ifndef VIDEOSORTTYPE_H
#define VIDEOSORTTYPE_H

#include <QWidget>

namespace Ui {
class VideoSortType;
}

class VideoSortType : public QWidget
{
    Q_OBJECT

public:
    explicit VideoSortType(QWidget *parent = nullptr);
    ~VideoSortType();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

private:
    Ui::VideoSortType *ui;

};

#endif // VIDEOSORTTYPE_H

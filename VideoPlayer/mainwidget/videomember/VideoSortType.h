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

protected:
//    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::VideoSortType *ui;

private:
    void    autoResizeListItems();

};

#endif // VIDEOSORTTYPE_H

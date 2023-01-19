#ifndef VIDEOTYPESELECT_H
#define VIDEOTYPESELECT_H
#include "mainwidget/subunititems/SelectVideoType.h"
#include <QWidget>
#include <QLayout>
#include <QEvent>
#include <QScrollBar>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>

class VideoTypeSelect : public QWidget
{
    Q_OBJECT

public:
    explicit VideoTypeSelect(QWidget *parent = nullptr);
    ~VideoTypeSelect();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    QVBoxLayout     *m_vblayout           = nullptr;
    QListWidget     *m_listWgt_sortResult = nullptr;
    SelectVideoType *m_sortVideoForm      = nullptr;

private:
    void    resizeListWgt_result();

};

#endif // VIDEOTYPESELECT_H

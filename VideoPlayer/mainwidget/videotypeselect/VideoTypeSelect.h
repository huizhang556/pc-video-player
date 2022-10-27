#ifndef VIDEOTYPESELECT_H
#define VIDEOTYPESELECT_H
#include "mainwidget/subunititems/SelectVideoType.h"
#include <QWidget>
#include <QLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>

namespace Ui {
class VideoTypeSelect;
}

class VideoTypeSelect : public QWidget
{
    Q_OBJECT

public:
    explicit VideoTypeSelect(QWidget *parent = nullptr);
    ~VideoTypeSelect();

private:
    QVBoxLayout     *m_vblayout           = nullptr;
    QListWidget     *m_listWgt_sortResult = nullptr;
    SelectVideoType *m_sortVideoForm      = nullptr;

};

#endif // VIDEOTYPESELECT_H

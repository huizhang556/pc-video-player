#ifndef GALLERYITEMFORM_H
#define GALLERYITEMFORM_H
#include "mainwidget/PicWallItem.h"
#include <QWidget>

namespace Ui {
class GalleryItemForm;
}

class GalleryItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryItemForm(QWidget *parent = nullptr);
    ~GalleryItemForm();
    void initWorkUI();
    void chandleSignalsAndSlots();
    void setHeaderTitle(QString title);
    void adjustListWidgetItemsSize();
protected:
    void resizeEvent(QResizeEvent *event) override;
public slots:

private:
    Ui::GalleryItemForm *ui;
};

#endif // GALLERYITEMFORM_H

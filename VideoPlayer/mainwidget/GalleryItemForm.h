#ifndef GALLERYITEMFORM_H
#define GALLERYITEMFORM_H
#include "mainwidget/PicWallItem.h"
#include <QWidget>
#include <QPushButton>
#include <QAbstractItemView>

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

private slots:

    void on_pushButton_itemnext_clicked();

    void on_pushButton_itemprevious_clicked();

private:
    Ui::GalleryItemForm *ui;

};

#endif // GALLERYITEMFORM_H

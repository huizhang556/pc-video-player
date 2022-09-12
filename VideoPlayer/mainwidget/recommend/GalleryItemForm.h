#ifndef GALLERYITEMFORM_H
#define GALLERYITEMFORM_H

#define MINSIZE QSize(150,350)
#define SCALE MINSIZE.height()/MINSIZE.width()

#include "global/Global.h"
#include "mainwidget/recommend/PicWallItem.h"

#include <QWidget>
#include <QPushButton>
#include <QListWidgetItem>
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
    void createItems(int size,QString path);

public slots:
    void    slot_addGalleryItem(const QString& url,const QString& pic1,const QString& pic2,const QString& text1,const QString& text2);

protected:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;


private slots:

    void on_pushButton_itemnext_clicked();

    void on_pushButton_itemprevious_clicked();

private:
    void    resizeGalleryItemSize();//重新计算item的size

private:
    Ui::GalleryItemForm *ui;

signals:
    void    sig_itemResizeChanged(QSize);
};

#endif // GALLERYITEMFORM_H

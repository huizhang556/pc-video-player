#ifndef RECOMMENDFORM_H
#define RECOMMENDFORM_H
#include "lunbotu/PictureWidget.h"
#include "mainwidget/StackItemForm.h"
#include "mainwidget/GalleryItemForm.h"
#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QResizeEvent>

namespace Ui {
class RecommendForm;
}

class RecommendForm : public QWidget
{
    Q_OBJECT

public:
    explicit RecommendForm(QWidget *parent = nullptr);
    ~RecommendForm();
    void initWorkUI();
    void chandleSignalsAndSlots();
    void addToStackWidgetPage();
    void setSelectButtonText();
    void setSelectButton(int num);
    void updataAdjustButton_LR();//随着窗口变化调节左右按钮的位置
public slots:
    void slot_buttonGroupClicked(QAbstractButton *button);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;
    void    resizeEvent(QResizeEvent *event) override;
    void    moveEvent(QMoveEvent *event) override;
private slots:
    void addPage();
    void subPage();
    void showCurrentPage(int index);
signals:
    void sig_sizeChange(QSize size);
private:
    Ui::RecommendForm *ui;
    PictureWidget       *m_picWidget        =   nullptr;
    StackItemForm       *m_stackItem        =   nullptr;
    QButtonGroup        *m_buttonGroup      =   nullptr;
    QPushButton         *m_recLeftBtn       =   nullptr;
    QPushButton         *m_recRightBtn      =   nullptr;
    int                 m_titleBtnIndex;
    int                 m_curPageIndex;
};

#endif // RECOMMENDFORM_H

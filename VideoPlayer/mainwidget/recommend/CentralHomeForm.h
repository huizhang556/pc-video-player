#ifndef CENTRALHOMEFORM_H
#define CENTRALHOMEFORM_H

#include "mainwidget/recommend/RecommendForm.h"
#include "mainwidget/recommend/GalleryItemForm.h"

#include <QWidget>
#include <QListWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidgetItem>

class CentralHomeForm : public QWidget
{
    Q_OBJECT

public:
    explicit CentralHomeForm(QWidget *parent = nullptr);
    ~CentralHomeForm();
    void initWorkUI();
    void chandleSignalsAndSLots();
    void addWidgetToListWidget();

public slots:
    void    slot_globalResize();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void    makeBottomButton(int value);//判断滚动条位置，适时出现
    void    updateBottomButtonGeometry();
    void    resizeHomeListWidgetSize(QListWidgetItem* item, QSize size);

private:
    RecommendForm   *m_recommend        = nullptr;
    QListWidget     *m_homeListWidget   = nullptr;
    QVBoxLayout     *m_vBlayout         = nullptr;
    QPushButton     *m_bottomBtn        = nullptr;//底部返回按钮

private:

};

#endif // CENTRALHOMEFORM_H

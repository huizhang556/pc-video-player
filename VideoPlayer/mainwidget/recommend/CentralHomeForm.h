#ifndef CENTRALHOMEFORM_H
#define CENTRALHOMEFORM_H
#include "mainwidget/recommend/RecommendForm.h"
#include "mainwidget/recommend/GalleryItemForm.h"

#include <QWidget>
#include <QListWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class CentralHomeForm;
}

class CentralHomeForm : public QWidget
{
    Q_OBJECT

public:
    explicit CentralHomeForm(QWidget *parent = nullptr);
    ~CentralHomeForm();
    void initWorkUI();
    void chandleSignalsAndSLots();
    void addWidgetToListWidget();
protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void makeBottomButton(int value);//判断滚动条位置，适时出现
    void updateBottomButtonGeometry();
private:
    RecommendForm   *m_recommend        = nullptr;
    QListWidget     *m_homeListWidget   = nullptr;
    QVBoxLayout     *m_vBlayout         = nullptr;
    QPushButton     *m_bottomBtn        = nullptr;//底部返回按钮

};

#endif // CENTRALHOMEFORM_H

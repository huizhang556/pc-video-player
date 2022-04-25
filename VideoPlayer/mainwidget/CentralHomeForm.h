#ifndef CENTRALHOMEFORM_H
#define CENTRALHOMEFORM_H
#include "mainwidget/RecommendForm.h"
#include "mainwidget/GalleryItemForm.h"

#include <QWidget>
#include <QListWidget>
#include <QBoxLayout>

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
private:
    RecommendForm   *m_recommend        = nullptr;
    QListWidget     *m_homeListWidget   = nullptr;
    QVBoxLayout     *m_vBlayout         = nullptr;

};

#endif // CENTRALHOMEFORM_H

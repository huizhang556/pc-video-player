#ifndef FIRSTSHOW_H
#define FIRSTSHOW_H
#include "mainwidget/Slideshow.h"

#include <QWidget>
#include <QPushButton>
#include <QListWidget>

namespace Ui {
class FirstShow;
}

class FirstShow : public QWidget
{
    Q_OBJECT

public:
    explicit FirstShow(QWidget *parent = nullptr);
    ~FirstShow();
    void initUi();
public slots:

    void setRecomButtonText(const QString text1,const QString text2);

    void clearRecomButtonText();

    void setRecomListText(QStringList list);

private:
    Slideshow           *m_slideShow    = nullptr;
    QPushButton         *m_recoBtn1     = nullptr;
    QPushButton         *m_recoBtn2     = nullptr;
    QListWidget         *m_recomList    = nullptr;
};

#endif // FIRSTSHOW_H

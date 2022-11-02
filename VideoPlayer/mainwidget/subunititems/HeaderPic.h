#ifndef HEADERPIC_H
#define HEADERPIC_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

namespace Ui {
class HeaderPic;
}

class HeaderPic : public QLabel
{
    Q_OBJECT

public:
    explicit HeaderPic(QWidget *parent = nullptr);
    ~HeaderPic();
    void    setHeaderPicture(const QString& path);
    void    setHeaderBGColor(const QColor& color);
    void    setStatusButtonStatus(bool read);
    void    setHeaderRadius(int radius);

protected:
    void    paintEvent(QPaintEvent *event) override;

private:
    Ui::HeaderPic *ui;
    QString     m_picPath;//头像路径
    QColor      m_bgColor;//背景颜色
    int         m_radius;//倒角角度
};

#endif // HEADERPIC_H

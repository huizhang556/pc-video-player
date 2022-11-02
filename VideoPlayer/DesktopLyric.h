#ifndef DESKTOPLYRIC_H
#define DESKTOPLYRIC_H

#include <QWidget>

namespace Ui {
class DesktopLyric;
}

class DesktopLyric : public QWidget
{
    Q_OBJECT

public:
    explicit DesktopLyric(QWidget *parent = nullptr);
    ~DesktopLyric();

private:
    Ui::DesktopLyric *ui;
};

#endif // DESKTOPLYRIC_H

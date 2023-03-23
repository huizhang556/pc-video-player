#ifndef TEXTIMAGELAB_H
#define TEXTIMAGELAB_H

#include <QLabel>

namespace Ui {
class TextImageLab;
}

class TextImageLab : public QLabel
{
    Q_OBJECT

public:
    explicit TextImageLab(QWidget *parent = nullptr);
    ~TextImageLab();
    void    setLabWarnText(const QString& text);
    void    clearLabWarnText();

private:
    Ui::TextImageLab *ui;
};

#endif // TEXTIMAGELAB_H

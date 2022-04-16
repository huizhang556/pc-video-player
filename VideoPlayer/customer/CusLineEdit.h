#ifndef CUSLINEEDIT_H
#define CUSLINEEDIT_H

#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class CusLineEdit;
}

class CusLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit CusLineEdit(const QString &btnText, QWidget *parent = nullptr);
    explicit CusLineEdit(const QIcon &icon, QWidget *parent = nullptr);
    ~CusLineEdit();

private:    
    void setTextButton();// 设置文本按钮或图标按钮的大小和外观
    void setIconButton();
    void addButton();//将按钮添加到edit
    void setButtonSize(QPushButton *button, int width);
    QPushButton     *m_button = nullptr;
    const     int   buttonMargin = 3;// 按钮和输入内容的边距

signals:
    void buttonClicked(bool);
};

#endif // CUSLINEEDIT_H

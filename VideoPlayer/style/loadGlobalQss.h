#ifndef LOADGLOBALQSS_H
#define LOADGLOBALQSS_H

#include <QWidget>

//几种样式类型(可自行添加一套样式)
enum STYLETYPE
{
    STYLE_WHITE,
    STYLE_BLACK,
    STYLE_DARK,
    STYLE_PINK
};

namespace Ui {
class loadGlobalQss;
}

class loadGlobalQss : public QWidget
{
    Q_OBJECT

public:
    explicit loadGlobalQss(QWidget *parent = nullptr);
    ~loadGlobalQss();

    static void loadAllUIQss(STYLETYPE style);//加载UI样式文件

private:

};

#endif // LOADGLOBALQSS_H

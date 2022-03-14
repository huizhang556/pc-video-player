#ifndef LOADGLOBALQSS_H
#define LOADGLOBALQSS_H

#include <QWidget>

namespace Ui {
class loadGlobalQss;
}

class loadGlobalQss : public QWidget
{
    Q_OBJECT

public:
    explicit loadGlobalQss(QWidget *parent = nullptr);
    ~loadGlobalQss();

    static void loadAllUIQss();//加载UI样式文件

private:

};

#endif // LOADGLOBALQSS_H

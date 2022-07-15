#ifndef WEBMESSAGEBOX_H
#define WEBMESSAGEBOX_H

#include <QDialog>

namespace Ui {
class WebMessageBox;
}

class WebMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit WebMessageBox(QWidget *parent = nullptr);
    ~WebMessageBox();

private:
    Ui::WebMessageBox *ui;
};

#endif // WEBMESSAGEBOX_H

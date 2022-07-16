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

    void    chandleSignalsAndSLots();

private:
    Ui::WebMessageBox *ui;

signals:
//    void    sig_message_close();

};

#endif // WEBMESSAGEBOX_H

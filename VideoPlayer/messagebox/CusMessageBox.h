#ifndef CUSMESSAGEBOX_H
#define CUSMESSAGEBOX_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class CusMessageBox;
}

class CusMessageBox : public QMessageBox
{
    Q_OBJECT

public:
    explicit CusMessageBox(QWidget *parent = nullptr);
    explicit CusMessageBox(int type, QString title, QString checktext, QString prompt, QString btntext2, QWidget *parent = nullptr);
    ~CusMessageBox();

private:
    Ui::CusMessageBox *ui;
};

#endif // CUSMESSAGEBOX_H

#ifndef ADDMEDIAINFO_H
#define ADDMEDIAINFO_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
namespace Ui {
class AddMediaInfo;
}

class AddMediaInfo : public QDialog
{
    Q_OBJECT

public:
    explicit AddMediaInfo(QWidget *parent = nullptr);
    ~AddMediaInfo();
    void    initWorkUI();
    void    handleSignalsAndSLots();
    int c_exec(const QString& title);

private:
    Ui::AddMediaInfo *ui;

signals:
    void    sig_addMediaText(QString,QString);
};

#endif // ADDMEDIAINFO_H

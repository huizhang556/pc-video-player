#ifndef SONGITEMFORM_H
#define SONGITEMFORM_H

#include <QWidget>

namespace Ui {
class SongItemForm;
}

class SongItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit SongItemForm(QWidget *parent = nullptr);
    explicit SongItemForm(QString num, QString son_name, bool col, QString songer, QString zhuanji, QWidget *parent = nullptr);
    ~SongItemForm();
    QString addPrefixNum(QString num);
private slots:
    void slot_setSongCollectStatus(bool status);

private:
    Ui::SongItemForm *ui;

signals:
    void on_son_collectbtn_clicked(int index);
    void on_son_downloadbtn_clicked(int index);
    void on_son_deletebtn_clicked(int index);
    void on_son_morebtn_clicked(int index);

};

#endif // SONGITEMFORM_H

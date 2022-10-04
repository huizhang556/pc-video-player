#ifndef CMESSAGEBOX_H
#define CMESSAGEBOX_H

#include <QDialog>
#include <QMessageBox>
#include <QLayout>
#include <QDebug>

enum MessageType
{
    CNoIcon = 0,
    CError = 1,
    CWarning = 2,
    CQuestion = 3
};

namespace Ui {
class CMessageBox;
}

class CMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit CMessageBox(QWidget *parent = nullptr);
    explicit CMessageBox(MessageType mtype, const QString& title, const QString& query, const QString& button1Text="", const QString& button2Text="", QWidget *parent = nullptr);
    ~CMessageBox();
    void    initWorkUI();
    void    handleSignalsAndSlots();

private:
    Ui::CMessageBox *ui;
    MessageType     m_type;
    QString         m_titleText;
    QString         m_checkQuery;
    QString         m_btn1Text;
    QString         m_btn2Text;


private:
    void    setMessageType(MessageType mtype);
    void    setTitleText(const QString& title);
    void    setCheckQuery(const QString& query);
    void    setButton1Text(const QString& btn1text);
    void    setButton2Text(const QString& btn2text);

};

#endif // CMESSAGEBOX_H

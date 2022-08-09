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
    ~WebMessageBox();
    void    initWorkUI();
    void    chandleSignalsAndSLots();
    static WebMessageBox* getInstance();

protected:
    void    showEvent(QShowEvent *event) override;

public slots:
    void    setWebMessageInforation(QString address,QString name);
private:
    explicit WebMessageBox(QWidget *parent = nullptr);
    Ui::WebMessageBox *ui;

    static WebMessageBox* m_pInstance;

signals:
//    void    sig_message_close();
    void        sig_sendTitleChanged(QString,QString);

};

#endif // WEBMESSAGEBOX_H

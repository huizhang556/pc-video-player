#ifndef NEWWORK_H
#define NEWWORK_H

#include <QDialog>
#include <QAction>
#include <QBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QListWidget>

namespace Ui {
class NewWork;
}

class NewWork : public QDialog
{
    Q_OBJECT

public:
    explicit NewWork(QWidget *parent = nullptr);
    ~NewWork();
    void initWorkUI();
    void chandleSignalsAndSlots();
public slots:
    QString openLocalFileSystem();
    void slot_receivedNewWorkInfo(const QString &adress, const QString &filename);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void slot_addPathToList(const QString &path);
    void slot_setLineEditText(QLineEdit *edit, const QString &text);
    bool slot_judgePathExist(const QString &path);
    void slot_updateShowListPathWidget();

private:
    Ui::NewWork *ui;
    QPoint              m_mvPos;
    QAction         *m_spaceSize            = nullptr;
    QAction         *m_fileSize             = nullptr;
    QListWidget     *m_listWdgt_path        = nullptr;
    QPushButton     *m_clearBtn             = nullptr;
    QWidget         *m_hisWdgt              = nullptr;
signals:
    void sig_download(bool status);
    void sig_downloadOpen();
};

#endif // NEWWORK_H

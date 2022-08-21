#ifndef FILEITEM_H
#define FILEITEM_H

#include <QWidget>

namespace Ui {
class FileItem;
}

class FileItem : public QWidget
{
    Q_OBJECT

public:
    explicit FileItem(QWidget *parent = nullptr);
    ~FileItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

public slots:
    void    slot_setFilePicType(QString type);
    void    slot_setFileName(const QString name);
    void    slot_setFileSize(const QString size);
    void    slot_setFileTime(const QString time);
    void    slot_setProgressBarValue(qint64 received,qint64 total);
    void    slot_setFileSpeed(const QString speed);

private:
    Ui::FileItem *ui;

signals:
    void    sig_sendStartPause(bool);
    void    sig_sendCancel();
    void    sig_sendOpenDirectory();
    void    sig_sendOpenFileContent();
    void    sig_sendOpenLocalDirectory();
    void    sig_senDdeleteFile();
};

#endif // FILEITEM_H

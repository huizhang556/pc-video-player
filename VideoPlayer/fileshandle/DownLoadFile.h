#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include <QWidget>

namespace Ui {
class DownLoadFile;
}

class DownLoadFile : public QWidget
{
    Q_OBJECT

public:
    explicit DownLoadFile(QWidget *parent = nullptr);
    ~DownLoadFile();
    void    initWorkUI();
    void    handleSignalsAndSlots();

private:
    Ui::DownLoadFile *ui;
};

#endif // DOWNLOADFILE_H

#ifndef COMPLETEDFILES_H
#define COMPLETEDFILES_H

#include <QWidget>

namespace Ui {
class CompletedFiles;
}

class CompletedFiles : public QWidget
{
    Q_OBJECT

public:
    explicit CompletedFiles(QWidget *parent = nullptr);
    ~CompletedFiles();
    void    initWorkUI();
    void    handleSignalsAndSlots();

private:
    Ui::CompletedFiles *ui;
};

#endif // COMPLETEDFILES_H
